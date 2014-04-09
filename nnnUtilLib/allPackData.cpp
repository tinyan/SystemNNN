//
//
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanlib\include\commonMacro.h"

#include "allPackData.h"
#include "allPackHash.h"

/*
typedef struct _tagMYALLPACKHEADER
{
	INT64 size;
	char headerName[16];
	INT64 blockCount;
	INT64 filesize;//use??
	INT64 dataBlockOffset;//==size
	INT64 pad[2];
	INT64 dataBlockPointer[1];//blockCountŒÂ”
} MYALLPACKHEADER;



typedef struct _tagMYALLPACKDATA
{
	INT64 size;
	char headerName[16];
	INT64 totalSize;//MYALLPACKDATA +  MYFILENAMESTRUCT + MYFILENAMESTRUCT + MYFILESTARTSTRUCT
	INT64 fileNumber;
	INT64 folderNameStructOffset;
	INT64 filenameStructOffset;
	INT64 fileStartStructOffset;
	INT64 pad[4];
}MYALLPACKDATA;

typedef struct _tagMYFOLDERNAMESTRUCT
{
	INT64 size;
	char headerName[16];
	INT64 folderLevelNumber;
	INT64 fullFolderLength;
	INT64 pad[3];
	char fullFolder[64];
	char folder[1][16];//folderLevelNumberŒÂ”
}MYFOLDERNAMESTRUCT;

typedef struct _tagMYFILENAMESTRUCT
{
	INT64 size;
	char headerNamr[16];
	INT64 filenameOffset;
	INT64 pad[4];
	INT64 filenameTableOffset[1];//fileNumberŒÂ”
	//data
}MYFILENAMESTRUCT;

typedef struct _tagMYHASHSTRUCT
{
	INT64 size;
	char headerName[16];
	INT64 hashCount;
	INT64 pad[4];
	int hashData[1];//4*hashCount allbit,number,next dummy=0
}MYHASHSTRUCT;

typedef struct _tagMYFILESTARTSTRUCT
{
	INT64 size;
	char headerName[16];
	INT64 dataOffset;
	INT64 pad[4];
	INT64 dataStart[1];//fileNumber+1ŒÂ”
	//data
}MYFILESTARTSTRUCT;

*/



CAllPackData::CAllPackData(FILE* file)
{
	INT64 size;
	fread(&size,sizeof(INT64),1,file);
	m_allPackData = (MYALLPACKDATA*)(new char[(int)size]);
	m_allPackData->size = size;
	fread(((char*)m_allPackData) + sizeof(INT64),sizeof(char),(int)size - sizeof(INT64),file);
	m_fileNumber = m_allPackData->fileNumber;

	INT64 size2;
	fread(&size2,sizeof(INT64),1,file);
	m_folderNameStruct = (MYFOLDERNAMESTRUCT*)(new char[(int)size2]);
	m_folderNameStruct->size = size2;
	fread(((char*)m_folderNameStruct) + sizeof(INT64),sizeof(char),(int)size2 - sizeof(INT64),file);

	INT64 size3;
	fread(&size3,sizeof(INT64),1,file);
	m_fileNameStruct = (MYFILENAMESTRUCT*)(new char[(int)size3]);
	m_fileNameStruct->size = size3;
	fread(((char*)m_fileNameStruct) + sizeof(INT64),sizeof(char),(int)size3 - sizeof(INT64),file);

	INT64 size4;
	fread(&size4,sizeof(INT64),1,file);
	m_hashStruct = (MYHASHSTRUCT*)(new char[(int)size4]);
	m_hashStruct->size = size4;
	fread(((char*)m_hashStruct) + sizeof(INT64),sizeof(char),(int)size4 - sizeof(INT64),file);

	INT64 size5;
	fread(&size5,sizeof(INT64),1,file);
	m_fileStartStruct = (MYFILESTARTSTRUCT*)(new char[sizeof(MYFILESTARTSTRUCT) + sizeof(INT64)*((int)m_fileNumber + 1 -1)]);//
	m_fileStartStruct->size = size5;
	fread(((char*)m_fileStartStruct) + sizeof(INT64),sizeof(char),sizeof(MYFILESTARTSTRUCT) + sizeof(INT64)*((int)m_fileNumber + 1 -1 -1),file);

	INT64 seekSize = m_fileStartStruct->dataSize;

	fpos_t seek;
	fgetpos(file,&seek);
	seek += seekSize;
	fsetpos(file,&seek);
}



CAllPackData::~CAllPackData()
{
	End();
}

void CAllPackData::End(void)
{
	if (m_fileStartStruct != NULL)
	{
		delete m_fileStartStruct;
		m_fileStartStruct = NULL;
	}

	if (m_fileNameStruct != NULL)
	{
		delete m_fileNameStruct;
		m_fileNameStruct = NULL;
	}

	if (m_folderNameStruct != NULL)
	{
		delete m_folderNameStruct;
		m_folderNameStruct = NULL;
	}

	if (m_allPackData != NULL)
	{
		delete m_allPackData;
		m_allPackData = NULL;
	}
}

BOOL CAllPackData::CheckDir(LPCSTR dir,BOOL errorPrintFlag)
{
	if (_stricmp(m_folderNameStruct->fullFolder,dir) == 0) return TRUE;
	return FALSE;
}

INT64 CAllPackData::SearchFile(LPCSTR filename,INT64* lpFileSize,BOOL errorPrintFlag)
{
	INT64 fileStart = -1;

	int hash = CAllPackHash::CreateHash(filename);
//	int hash1024 = hash & 0x3ff;
	int found = -1;
	int pointer = hash & 0x3ff;
	int hashCount = (int)(m_hashStruct->hashCount);
	INT64 fileSize = 0;

	int limit = 10000;

	while ((pointer<hashCount) && (pointer >= 0))
	{
		if (hash == m_hashStruct->hashData[4*pointer])
		{
			//check file name
			int n = m_hashStruct->hashData[4*pointer+1];
			int offset = (int)(m_fileNameStruct->filenameOffset + m_fileNameStruct->filenameTableOffset[n]);
			LPCSTR checkName = ((char*)m_fileNameStruct) + offset;
			if (_stricmp(filename,checkName) == 0)
			{
				found = pointer;
				break;
			}
		}


		pointer = m_hashStruct->hashData[4*pointer+2];
		limit--;
		if (limit<=0) break;//error mugen loop kaihi
	}

	if (found != -1)
	{
		int n = m_hashStruct->hashData[4*found+1];
		INT64 start = m_fileStartStruct->dataStart[n];
		INT64 end = m_fileStartStruct->dataStart[n+1];
		fileSize = end - start;

		fileStart = m_allPackData->size + m_folderNameStruct->size + m_fileNameStruct->size + m_hashStruct->size;
		fileStart += m_fileStartStruct->dataOffset;
		fileStart += start;
	}

	if (lpFileSize != NULL)
	{
		*lpFileSize = fileSize;
	}

	return fileStart;
}

