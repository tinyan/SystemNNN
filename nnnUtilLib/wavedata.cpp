//
// waveData.cpp
//


#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myFile.h"

//#include "huffman.h"
#include "oggDecoder.h"
#include "waveData.h"

int CWaveData::m_refCount = 0;
COggDecoder* CWaveData::m_oggDecoder = NULL;
//CHuffMan* CWaveData::m_huffMan = NULL;
BOOL CWaveData::m_cdFlag = FALSE;
char CWaveData::m_dirName[] = "cdvaw";
char CWaveData::m_cdDirName[256] = "cdvaw";

char CWaveData::m_tableName[3*PACKWAVE_TABLE_KOSUU_MAX];
int CWaveData::m_tableKosuu = 0;
char* CWaveData::m_tableData[PACKWAVE_TABLE_KOSUU_MAX];
int CWaveData::m_tableSize[PACKWAVE_TABLE_KOSUU_MAX];

char* CWaveData::m_commonBuffer = NULL;
int CWaveData::m_commonBufferSize = 0;
BOOL CWaveData::m_commonBufferCreateFlag = FALSE;


CWaveData::CWaveData(int initBufferSize)
{
	m_data = NULL;
	m_bufferSize = initBufferSize;
	m_fileName[0] = 0;
	m_dataSize = 0;
	m_adjustWaveLevelFlag = FALSE;

	if (m_refCount == 0)
	{
		if (m_commonBuffer == NULL)
		{
			m_commonBufferCreateFlag = TRUE;
			m_commonBufferSize = 1024*1600;	//dummy
			m_commonBuffer = new char[m_commonBufferSize];
		}

		m_oggDecoder = new COggDecoder();
		m_tableKosuu = 0;
		for (int i=0;i<PACKWAVE_TABLE_KOSUU_MAX;i++)
		{
			m_tableName[3*i] = 0;
			m_tableName[3*i+1] = 0;
			m_tableName[3*i+2] = 0;
			m_tableData[i] = NULL;
			m_tableSize[i] = 0;
		}
	}
	m_refCount++;
}


CWaveData::~CWaveData()
{
	m_refCount--;
	End();
}

void CWaveData::End(void)
{
	DELETEARRAY(m_data);
	m_bufferSize = 0;
	if (m_refCount == 0)
	{
		ENDDELETECLASS(m_oggDecoder);
//		ENDDELETECLASS(m_huffMan);
		m_tableKosuu = 0;
		for (int i=0;i<PACKWAVE_TABLE_KOSUU_MAX;i++)
		{
			m_tableName[3*i] = 0;
			m_tableName[3*i+1] = 0;
			m_tableName[3*i+2] = 0;
			DELETEARRAY(m_tableData[i]);
		}
		if (m_commonBufferCreateFlag)
		{
			m_commonBufferCreateFlag = FALSE;
			DELETEARRAY(m_commonBuffer);
			m_commonBufferSize = 0;
		}
	}
}


BOOL CWaveData::CreateBuffer(int newSize)
{
	if (newSize<m_bufferSize) return TRUE;
	DELETEARRAY(m_data);
	m_data = new char[newSize];
	if (m_data == NULL)
	{
		MessageBox(NULL,"ƒƒ‚ƒŠ[•s‘«\nCWaveBuffer::CreateBuffer","ERROR",MB_OK | MB_ICONSTOP );
		m_bufferSize = 0;
		return FALSE;
	}

//char mes[256];
//sprintf(mes,"create=%dBytes",newSize);
//OutputDebugString(mes);
	m_bufferSize = newSize;

	return TRUE;
}



BOOL CWaveData::LoadSystemWave(LPSTR dirName, LPSTR filenameOnly)
{
//	if (stricmp(filenameOnly,m_fileName) == 0) return TRUE;
	if (filenameOnly == NULL) return FALSE;

	int fln = strlen(filenameOnly);
	memcpy(m_fileName,filenameOnly,fln+1);
	char filename[256];

	BOOL noDir = FALSE;

	if (dirName == NULL)
	{
		noDir = TRUE;
	}
	else
	{
		if ((*dirName) == 0) noDir = TRUE;
	}

	if (noDir == FALSE)
	{
		wsprintf(filename,"vaw\\%s\\%s.vaw",dirName,filenameOnly);
	}
	else
	{
		wsprintf(filename,"vaw\\%s.vaw",filenameOnly);
	}

	FILE* file = CMyFile::Open(filename,"rb");
	if (file == NULL) return FALSE;

	return LoadWaveRoutine(file);
}


BOOL CWaveData::LoadWave(LPSTR filenameOnly)
{
//	if (stricmp(filenameOnly,m_fileName) == 0) return TRUE;

	char tag[3];
	tag[0] = *(filenameOnly);
	tag[1] = *(filenameOnly+1);
	tag[2] = 0;

	int fln = strlen(filenameOnly);
	memcpy(m_fileName,filenameOnly,fln+1);
	
	char filename[256];

	if (m_cdFlag == FALSE)
	{
		wsprintf(filename,"%s\\%s\\%s.vaw",m_dirName,tag,filenameOnly);
	}
	else
	{
		wsprintf(filename,"%s\\%s\\%s.vaw",m_cdDirName,tag,filenameOnly);
	}

	FILE* file = CMyFile::Open(filename,"rb");
	if (file == NULL) return FALSE;

#if defined _DEBUG
	OutputDebugString("\n\nLoadWave:");
	OutputDebugString(filenameOnly);
#endif

	return LoadWaveRoutine(file);
}




BOOL CWaveData::LoadPackedWave(LPSTR filenameOnly)//,LPSTR packFile, LPSTR tableFile)
{
//	m_oggFlag = FALSE;
	if (_stricmp(filenameOnly,m_fileName) == 0) return TRUE;

	char tag[3];
	tag[0] = *(filenameOnly);
	tag[1] = *(filenameOnly+1);
	tag[2] = 0;

	int packNumber = LoadTable(tag);
	if (packNumber == -1) return FALSE;


	int fln = strlen(filenameOnly);
	memcpy(m_fileName,filenameOnly,fln+1);
	
	char filename[256];

//	if (m_cdFlag == FALSE)
//	{
//		sprintf(filename,"%s\\%s.vpk",m_dirName,tag);
//	}
//	else
//	{
		wsprintf(filename,"%s\\%s.vpk",m_cdDirName,tag);
//	}

	FILE* file = CMyFile::Open(filename,"rb");
	if (file == NULL) return FALSE;

	//seek
	int loadSize = 0;
	int seek = GetCDVAWSeekPointer(packNumber,filenameOnly,&loadSize);


	if (seek == -1)
	{
		fclose(file);
		return FALSE;
	}



	fpos_t nowPos;
	fgetpos(file,&nowPos);
	nowPos += seek;
	fsetpos(file,&nowPos);


#if defined _DEBUG
	char emes[1024];
	sprintf_s(emes,1024,"\n\nLoadPackedWave:seek=%d size=%d",seek,loadSize);
	OutputDebugString(emes);
	OutputDebugString(filenameOnly);

#endif

	return LoadWaveRoutine(file,loadSize);
}

BOOL CWaveData::LoadWaveRoutine(FILE* file,int loadSize)
{
	char myHeader[64];
	fread(myHeader,sizeof(char),64,file);

	char waveHeader[128];
	fread(waveHeader,sizeof(char),20,file);

	int headerSize = *((int*)(waveHeader+16));

	fread(waveHeader+20,sizeof(char),headerSize,file);

	WAVEFORMATEX* lpFormat = (WAVEFORMATEX*)(waveHeader + 20);
	
	memcpy(&m_waveformatex,waveHeader + 20,sizeof(WAVEFORMATEX));

	int makedDataSize = *((int*)(waveHeader + 4));
		
	makedDataSize += 8;

	int bufferSize = makedDataSize + 4096*2;
	CreateBuffer(bufferSize);

	m_realDataPtr = m_data + 20 + headerSize + 8;


	if (myHeader[57] == '0')	//nonpacke
	{
		fread(m_data+20+headerSize,sizeof(char),makedDataSize,file);
	}
	else if (myHeader[57] == '1')
	{
		//‚Í‚¸‚·
//		int readSize0 = m_game->GetCDVAWSize(filename);

		if (loadSize <= 0) loadSize = 1024*1600;
		int readSize = fread(m_commonBuffer,sizeof(char),loadSize,file);

//		m_huffMan->HuffManDecode(m_commonBuffer,m_data+20+headerSize,readSize);
	}
	else	//2
	{
fread(waveHeader+20+headerSize,sizeof(char),8,file);
makedDataSize -= 8;
//		int readSize0 = m_game->GetCDVAWSize(filename);

		if (loadSize <= 0) loadSize = 1024*1600;
	
		ReCreateCommonBuffer(loadSize);

		int readSize = fread(m_commonBuffer,sizeof(char),loadSize - 64 - 20 - headerSize - 8,file);


		//check and re-create common bufffer



//		m_oggDecoder->DecodeAll(m_commonBuffer,readSize,(short*)(m_data+20+headerSize));
		m_oggDecoder->DecodeAll(m_commonBuffer,readSize,(short*)(m_data + 20+headerSize+8));

		memcpy(m_data+20+headerSize,waveHeader+20+headerSize,8);
		//ogg decode
	}

		//move header
//MyErrorLog("[move]");
	memcpy(m_data,waveHeader,headerSize+20);


	m_realDataSize = *((int*)(m_data + headerSize + 20 + 4));


	m_dataSize = makedDataSize;

	m_adjustWaveLevelFlag = FALSE;

	fclose(file);
	return TRUE;
}

int CWaveData::LoadTable(LPSTR tableName)
{
	for (int i=0;i<m_tableKosuu;i++)
	{
		if (_stricmp(tableName,&m_tableName[i*3]) == 0)
		{
			return i;
		}
	}

	if (m_tableKosuu>=PACKWAVE_TABLE_KOSUU_MAX) return -1;

	//load
	char filename[256];
	wsprintf(filename,"cdvaw\\%s.vtb",tableName);
	INT64 fileSize = 0;
	FILE* file = CMyFile::Open(filename,"rb",&fileSize);
	if (file == NULL) return -1;

	int sz = (int)fileSize;

	m_tableData[m_tableKosuu] = new char[sz];
	if (m_tableData[m_tableKosuu] == NULL)
	{
		fclose(file);
		return -1;
	}

	fread(m_tableData[m_tableKosuu],sizeof(char),sz,file);
	fclose(file);

	m_tableSize[m_tableKosuu] = sz;

	memcpy(&m_tableName[m_tableKosuu*3],tableName,2);
	m_tableName[m_tableKosuu*3+2] = 0;

	m_tableKosuu++;
	return m_tableKosuu-1;
}


int CWaveData::GetCDVAWSeekPointer(int packNumber, LPSTR filename, int* lpSize)
{
	int kosuu = m_tableSize[packNumber] / 12;
	int found = -1;

	int filename1 = 0;
	int filename2 = 0;

	char filenamework[10];
	filenamework[8] = 0;
	filenamework[9] = 0;

	int ln = strlen(filename);
	if (ln>8) ln = 8;
	if (ln<4)
	{
		if (ln>0)
		{
			memcpy(&filename1,filename,ln);
		}
	}
	else
	{
		memcpy(&filename1,filename,4);
		if ((ln-4)>0)
		{
			memcpy(&filename2,filename+4,ln-4);
		}
	}


	int* table = (int*)m_tableData[packNumber];
	int* work1 = (int*)filenamework;
	int* work2 = (int*)(filenamework+4);

	for (int i=0;i<kosuu;i++)
	{
		*work1 = *table;
		*work2 = *(table+1);

//		if (strcmp(filename,m_tableData[packNumber] + i*12) == 0)
		if (_stricmp(filename,filenamework) == 0)
		{
			found = i;
			break;
		}

//		if (filename1 == (*table))
//		{
//			if (filename2 == (*(table+1)))
//			{
//				found = i;
//				break;
//			}
//		}

		table += 3;
	}

	if (found == -1)
	{
		*lpSize = 0;
#if defined _DEBUG
OutputDebugString(" Not found:");
OutputDebugString(filename);
//MessageBox(NULL,filename,"FILE NOT FOUND",MB_OK);
#endif
		return -1;
	}

	int seek  = *((int*)(m_tableData[packNumber] + found    *12+8));
	int seek2 = *((int*)(m_tableData[packNumber] + (found+1)*12+8));

	*lpSize = seek2 - seek;
	return seek;
}

void* CWaveData::GetData(void)
{
	return m_data;
}

void* CWaveData::GetRealDataPtr(void)
{
	return m_realDataPtr;
}

int CWaveData::GetDataSize(void)
{
	return m_dataSize;
}

int CWaveData::GetRealDataSize(void)
{
	return m_realDataSize;
}

LPSTR CWaveData::GetFileName(void)
{
	return m_fileName;
}


int CWaveData::GetLength(void)
{
    DWORD nAvgBytesPerSec = m_waveformatex.nAvgBytesPerSec; 
	if (nAvgBytesPerSec <= 0) return 0;

	double sz = (double)(GetRealDataSize());
	sz *= 1000.0;
	sz /= nAvgBytesPerSec;

	return (int)sz;
}


int CWaveData::GetChannel(void)
{
	return m_waveformatex.nChannels;
}

int CWaveData::GetBitRate(void)
{
	return m_waveformatex.wBitsPerSample;
}

int CWaveData::GetSampleRate(void)
{
	return m_waveformatex.nSamplesPerSec;
}

BOOL CWaveData::AdjustWaveLevel(int percent)
{
	if (m_adjustWaveLevelFlag) return TRUE;
	m_adjustPercent = percent;

	int sz = (m_realDataSize - 8) / sizeof(short);
	char* dataPtr = (char*)m_realDataPtr;



	int firstLoop = 0;
	int midLoop = 0;
	int lastLoop = 0;


	int tmp = (int)dataPtr;
	//first adjust
	if (tmp & 0x2)
	{
		int amari = tmp & 0x2;

		amari /= 2;
		amari = 2 - amari;

		firstLoop = amari;
		sz -= amari;
	}


	if (sz > 0)
	{
		if (sz & 1)
		{
			lastLoop = sz & 1;
			sz &= (~1);
		}
	}

	if (sz > 0)
	{
		midLoop = sz / 2;
	}


	int multiData = (percent * 256) / 100;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0
		mov eax,multiData
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7


		mov esi,dataPtr
		mov ecx,firstLoop
		or ecx,ecx
		jz SKIP1
LOOP1:
		xor eax,eax
		mov ax,[esi]
		movd mm1,eax
		pmaddwd mm1,mm7
		psrad mm1,8
		packssdw mm1,mm0
		movd eax,mm1
		mov [esi],ax

		add esi,2
		dec ecx
		jnz LOOP1
SKIP1:

		mov ecx,midLoop
		or ecx,ecx
		jz SKIP2
LOOP2:
		mov eax,[esi]
		movd mm1,eax
		punpcklwd mm1,mm0
		pmaddwd mm1,mm7
		psrad mm1,8
		packssdw mm1,mm0
		movd eax,mm1
		mov [esi],eax

		add esi,4
		dec ecx
		jnz LOOP2
SKIP2:



		mov ecx,lastLoop
		or ecx,ecx
		jz SKIP3
LOOP3:
		xor eax,eax
		mov ax,[esi]
		movd mm1,eax
		pmaddwd mm1,mm7
		psrad mm1,8
		packssdw mm1,mm0
		movd eax,mm1
		mov [esi],ax

		add esi,2
		dec ecx
		jnz LOOP3
SKIP3:

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax

		emms
	}

	m_adjustWaveLevelFlag = TRUE;


	return TRUE;
}


int CWaveData::GetAdjustPercent(void)
{
	if (CheckAdjusted() == FALSE) return 100;

	return m_adjustPercent;
}

BOOL CWaveData::CheckAdjusted(void)
{
	return m_adjustWaveLevelFlag;
}

BOOL CWaveData::ReCreateCommonBuffer(int size)
{
	if (m_commonBufferCreateFlag == FALSE)
	{
		m_commonBufferCreateFlag = TRUE;
		m_commonBufferSize = size;
		m_commonBuffer = new char[size];
		return TRUE;
	}

	if (m_commonBufferSize >= size) return TRUE;

	DELETEARRAY(m_commonBuffer);
	m_commonBufferSize = 0;
	m_commonBufferCreateFlag = FALSE;

	m_commonBuffer = new char[size];
	if (m_commonBuffer == NULL) return FALSE;//fatal error!!

	m_commonBufferSize = size;
	m_commonBufferCreateFlag = TRUE;
	return TRUE;
}

