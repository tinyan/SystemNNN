//
//
//

#include <windows.h>
#include <stdio.h>


#include "..\nyanlib\include\commonMacro.h"

#include "allPackData.h"
#include "allPackFile.h"
#include "allPackHash.h"





CAllPackFile::CAllPackFile(LPCSTR filename)
{

	m_allPackDataKosuu = 0;
	m_allPackData = NULL;
	m_header = NULL;



	FILE* file = NULL;
	fopen_s(&file,filename,"rb");

	if (file != NULL)
	{
		INT64 size;
		fread(&size,sizeof(INT64),1,file);
		m_header = (MYALLPACKHEADER*)(new char[(int)size]);
		m_header->size = size;
		fread(((char*)m_header) + sizeof(INT64),sizeof(char),(int)size-sizeof(INT64),file);

		m_allPackDataKosuu = m_header->blockCount;
		if (m_allPackDataKosuu > 0)
		{
			m_allPackData = new CAllPackData*[(int)m_allPackDataKosuu];
			for (int i=0;i<m_allPackDataKosuu;i++)
			{
				m_allPackData[i] = new CAllPackData(file);
			}
		}
		fclose(file);
	}
}

CAllPackFile::~CAllPackFile()
{
	End();
}

void CAllPackFile::End(void)
{
	if (m_allPackData != NULL)
	{
		for (int i=0;i<m_allPackDataKosuu;i++)
		{
			ENDDELETECLASS(m_allPackData[i]);
		}
		DELETEARRAY(m_allPackData);
	}

	if (m_header != NULL)
	{
		delete m_header;
		m_header = NULL;
	}
}

INT64 CAllPackFile::GetFileOffset(LPCSTR filename,INT64* lpSize)
{
	char dir[1024];
	char filenameOnly[1024];

	dir[0] = 0;
	filenameOnly[0] = 0;

	int ln = (int)strlen(filename);
	int n = 0;

	int found = -1;
	while (n<ln)
	{
		char c = *(filename+n);
		int d = (int)c;
		d &= 0xff;

		if (d == '\\')
		{
			found = n;
		}
		n++;

		if ((d >= 0x80) && (d<=0x9f))
		{
			n++;
		}

		if ((d >= 0xe0) && (d<=0xff))
		{
			n++;
		}
	}

	if (found == -1)
	{
		return -1;
	}

	memcpy(dir,filename,found+1);
	dir[found] = 0;
	memcpy(filenameOnly,filename+found+1,ln-found);

	for (int i=0;i<m_allPackDataKosuu;i++)
	{
		if (m_allPackData[i]->CheckDir(dir))
		{
			return m_allPackData[i]->SearchFile(filenameOnly,lpSize) + m_header->dataBlockPointer[i];
		}
	}

	return -1;
}

BOOL CAllPackFile::CheckExistFile(LPCSTR dir,LPCSTR filename,BOOL errorPrintFlag)
{
	for (int i=0;i<m_allPackDataKosuu;i++)
	{
		if (m_allPackData[i]->CheckDir(dir,errorPrintFlag))
		{
			if (m_allPackData[i]->SearchFile(filename,NULL,errorPrintFlag) == -1) return FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CAllPackFile::CheckExistPackDir(LPCSTR dir)
{
	for (int i=0;i<m_allPackDataKosuu;i++)
	{
		if (m_allPackData[i]->CheckDir(dir))
		{
			return TRUE;
		}
	}
	return FALSE;
}