//
//
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"

#include "mmlControl.h"


CMMLControl::CMMLControl()
{
	m_mml = new char [1024];
	m_mmlBufferSize = 1024;
	m_mmlPointer = 0;
}


CMMLControl::~CMMLControl()
{
	End();
}

void CMMLControl::End(void)
{
	DELETEARRAY(m_mml);
	m_mmlBufferSize = 0;
}


BOOL CMMLControl::LoadMML(LPSTR filename)
{
	m_mmlPointer = 0;
	m_level = 0;

	char filename2[256];
	wsprintf(filename2,"wgq\\%s.mml",filename);
//	memcpy(filename2,"wgq\\",4);
//	int ln00 = strlen(filename);
//	memcpy(filename2+4,filename,ln00);
//	memcpy(filename2+4+ln00,".mml",5);

//	FILE* file = fopen(filename2,"rb");
//	if (file == NULL)

	HANDLE filea = CreateFile(filename2,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (filea == INVALID_HANDLE_VALUE)
	{
		char filename3[256];
		wsprintf(filename3,"wgq\\%s.wgq",filename);
//		memcpy(filename3,"wgq\\",4);
//		memcpy(filename3+4,filename,ln00);
//		memcpy(filename3+4+ln00,".wgq",5);

		HANDLE file3a = CreateFile(filename3,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
		if (file3a == INVALID_HANDLE_VALUE) return FALSE;
		CloseHandle(file3a);


//		FILE* file3 = fopen(filename3,"rb");
//		if (file3 == NULL) return FALSE;
//		fclose(file3);

		int ln = strlen(filename);	//さいてい256あるので再取得はチェックしない
		memcpy(m_mml,filename,ln);
		m_mmlSize = ln;
		m_mml[ln] = 0;
		return TRUE;
	}



//	fseek(file,0,SEEK_END);
//	int sz = ftell(file);
//	fseek(file,0,SEEK_SET);
//	int sz = SetFilePointer(filea,0,NULL,FILE_END);
//	SetFilePointer();

	int sz = GetFileSize(filea,NULL);
	if (sz+1 > m_mmlBufferSize)
	{
		DELETEARRAY(m_mml);
		m_mml = new char [sz+1];
		m_mmlBufferSize = sz + 1;
	}

	//fread(m_mml,sizeof(char),sz,file);
	ReadFile(filea,m_mml,sz,(DWORD*)&sz,NULL);

	m_mml[sz] = 0;
	m_mmlSize = sz;

	//fclose(file);
	CloseHandle(filea);

	return TRUE;
}


void CMMLControl::RestartMML(void)
{
	m_level = 0;
	m_mmlPointer = 0;
}


LPSTR CMMLControl::Kaiseki(void)	//if return NULL end of MML
{
	char c = m_mml[m_mmlPointer];

	//skip space [,]
	while ((c == ' ') || (c == ','))
	{
		m_mmlPointer++;
		c = m_mml[m_mmlPointer];
	}
	
	if (c == '[')
	{
		//get suuji
		m_mmlPointer++;

		c = m_mml[m_mmlPointer];
		int k = 0;
		char suuji[16];

		while ((c >= '0') && (c <= '9') && (k<15))
		{
			suuji[k] = c;
			k++;
			m_mmlPointer++;
			c = m_mml[m_mmlPointer];
		}
		suuji[k] = 0;

		if (c == ':') m_mmlPointer++;

		int loop = atoi(suuji);
		m_level++;
		m_mmlKakkoPointer[m_level] = m_mmlPointer;
		m_mmlLoop[m_level] = loop;
		return Kaiseki();
	}

	if (c == ']')
	{
		if (m_mmlLoop[m_level] == 0)	//無限るーぷ
		{
			m_mmlPointer = m_mmlKakkoPointer[m_level];
			return Kaiseki();
		}

		m_mmlLoop[m_level]--;
		if (m_mmlLoop[m_level]>0)
		{
			m_mmlPointer = m_mmlKakkoPointer[m_level];
			return Kaiseki();
		}

		m_level--;
		m_mmlPointer++;
		return Kaiseki();
	}

	//get name and inc pointer
	c = m_mml[m_mmlPointer];
	int f = 0;
	while ((c != 0) && (c != 0xd) && (c != ' ') && (c != ',') && (c != '[') && (c != ']') && (f<255))
	{
		m_filename[f] = c;
		f++;
		m_mmlPointer++;
		c = m_mml[m_mmlPointer];
	}

	m_filename[f] = 0;
	if (m_filename[0] == 0) return NULL;

	return m_filename;
}


/*_*/

