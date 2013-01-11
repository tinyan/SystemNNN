//
// systempicture.cpp
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "systempicture.h"

CSystemPicture* CSystemPicture::m_this = NULL;

CSystemPicture::CSystemPicture()
{
	m_systemPictureWorkKosuu = SYSTEM_PICKOSUU_MAX;
	m_picKosuu = 0;

	m_ppPic = new CPicture* [m_systemPictureWorkKosuu];
	m_ppPicName = new char[m_systemPictureWorkKosuu * SYSTEMPICFILENAME_MAX];


	for (int i=0;i<SYSTEM_PICKOSUU_MAX;i++)
	{
		//m_pic[i] = NULL;
		//m_picName[i][0] = 0;
		m_ppPic[i] = NULL;
		m_ppPicName[i*SYSTEMPICFILENAME_MAX] = 0;
	}

	m_ppPic[0] = new CPicture("sys\\error");
	m_picKosuu = 1;
}


CSystemPicture::~CSystemPicture()
{
	End();
}

void CSystemPicture::End(void)
{
	if (m_ppPic != NULL)
	{
		for (int i=0;i<m_systemPictureWorkKosuu;i++)
		{
			ENDDELETECLASS(m_ppPic[i]);
		}
		DELETEARRAY(m_ppPic);
	}

	DELETEARRAY(m_ppPicName);
}


//static
CPicture* CSystemPicture::GetSystemPicture(LPSTR filename,BOOL b256Mode)
{
	CSystemPicture* obj = m_this;
	if (obj == NULL) return NULL;

	return obj->GetPicture(filename,b256Mode);
}


CPicture* CSystemPicture::GetPicture(LPSTR filename,BOOL b256Mode)
{
	if (filename == NULL) return m_ppPic[0];

	int found = -1;

	for (int i=0;i<m_picKosuu;i++)
	{
		if (strcmp(filename,&m_ppPicName[i*SYSTEMPICFILENAME_MAX]) == 0)
		{
			found = i;
			break;
		}
	}

	if (found != -1)
	{
		return m_ppPic[found];
	}

	if (m_picKosuu >= m_systemPictureWorkKosuu)
	{
		if (ExpandWork() == FALSE) return m_ppPic[0];
	}

	int ln = strlen(filename);
	if (ln >= SYSTEMPICFILENAME_MAX-2)
	{
		OutputDebugString("システムグラフィックのファイル名が長すぎます:");
		OutputDebugString(filename);
		ln = SYSTEMPICFILENAME_MAX - 2;
	}


	memcpy(&m_ppPicName[m_picKosuu * SYSTEMPICFILENAME_MAX],filename,ln);
	m_ppPicName[m_picKosuu * SYSTEMPICFILENAME_MAX + ln] = 0;
	m_ppPicName[m_picKosuu * SYSTEMPICFILENAME_MAX + ln+1] = 0;

	char makedfilename[64];
	wsprintf(makedfilename,"sys\\%s",&m_ppPicName[m_picKosuu*SYSTEMPICFILENAME_MAX]);

//256mode??
	m_ppPic[m_picKosuu] = new CPicture();
	if (b256Mode)
	{
		if (m_ppPic[m_picKosuu]->LoadDWQ(makedfilename) == FALSE)
		{
			OutputDebugString("Load SystemPicture Error:");
			OutputDebugString(filename);
//			return m_pic[0];
		}
	}
	else
	{
		if (m_ppPic[m_picKosuu]->LoadDWQ(makedfilename) == FALSE)
		{
			OutputDebugString("Load SystemPicture Error:");
			OutputDebugString(filename);
//			return m_pic[0];
		}
	}

//	if (b256Mode)
//	{
//		m_pic[m_picKosuu] = new CPicture(makedfilename);
//	}
//	else
//	{
//		m_pic[m_picKosuu] = new CPicture(makedfilename);
//	}

//	if (m_pic[m_picKosuu]->CheckDataExist() == FALSE)
//	{
//		OutputDebugString("Load SystemPicture Error:");
//		OutputDebugString(filename);
//	}

	m_picKosuu++;
	return m_ppPic[m_picKosuu-1];
}


BOOL CSystemPicture::ExpandWork(int n)
{
	char* lpNewName = new char[(m_systemPictureWorkKosuu + n) * SYSTEMPICFILENAME_MAX];
	if (lpNewName == NULL) return FALSE;

	CPicture** lpNewPic = new CPicture*[m_systemPictureWorkKosuu + n];
	if (lpNewPic == NULL)
	{
		DELETEARRAY(lpNewName);
		return FALSE;
	}

	memcpy(lpNewName,m_ppPicName,m_systemPictureWorkKosuu*SYSTEMPICFILENAME_MAX);
	int i = 0;
	for (i=0;i<n;i++)
	{
		lpNewName[(m_systemPictureWorkKosuu+i) * SYSTEMPICFILENAME_MAX] = 0;
	}

	DELETEARRAY(m_ppPicName);
	m_ppPicName = lpNewName;

	for (i=0;i<m_systemPictureWorkKosuu;i++)
	{
		lpNewPic[i] = m_ppPic[i];
	}
	for (i=0;i<n;i++)
	{
		lpNewPic[m_systemPictureWorkKosuu+i] = NULL;
	}

	DELETEARRAY(m_ppPic);
	m_ppPic = lpNewPic;

	m_systemPictureWorkKosuu += n;

	return TRUE;
}


/*_*/

