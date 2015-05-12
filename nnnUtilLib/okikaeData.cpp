#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\myFile.h"

#include "..\nnnUtilLib\nameList.h"

#include "autoSaveSubData.h"
#include "okikaeData.h"

#define OKIKAE_BUFFER_SIZE 64

COkikaeData::COkikaeData(int mx,int sysMax,BOOL useDefault) : CAutoSaveSubData(mx*OKIKAE_BUFFER_SIZE)
{
	m_okikaeMax = mx;
	m_systemOkikaeMax = sysMax;
	m_okikaeMessage = new char[mx*OKIKAE_BUFFER_SIZE];
	for (int i=0;i<mx;i++)
	{
		memcpy(m_okikaeMessage+i*OKIKAE_BUFFER_SIZE,"’u‚«Š·‚¦•¶Žš—ñ‚O‚O",19);
		*(m_okikaeMessage+i*OKIKAE_BUFFER_SIZE+15) = ((i / 10) % 10) + 0x4f;
		*(m_okikaeMessage+i*OKIKAE_BUFFER_SIZE+17) = (i % 10) + 0x4f;
	}

	m_systemOkikaeMessage = new char[m_systemOkikaeMax*OKIKAE_BUFFER_SIZE];
	for (int i=0;i<m_systemOkikaeMax;i++)
	{
		memcpy(m_systemOkikaeMessage+i*OKIKAE_BUFFER_SIZE,"ƒVƒXƒeƒ€’u‚«Š·‚¦•¶Žš—ñ‚O‚O",27);
		*(m_systemOkikaeMessage+i*OKIKAE_BUFFER_SIZE+23) = ((i / 10) % 10) + 0x4f;
		*(m_systemOkikaeMessage+i*OKIKAE_BUFFER_SIZE+25) = (i % 10) + 0x4f;
	}

	m_defaultText = NULL;
	if (useDefault)
	{
		m_defaultText = new CNameList();
		m_defaultText->LoadFile("nya\\okikae.xtx");
		int ln = m_defaultText->GetNameKosuu() / 2;
		for (int i=0;i<ln;i++)
		{
			int n = atoi(m_defaultText->GetName(i*2));
			LPSTR text = m_defaultText->GetName(i*2+1);
			SetOkikaeMessage(n,text);
		}
	}
}

COkikaeData::~COkikaeData()
{
	End();
}

void COkikaeData::End(void)
{
	ENDDELETECLASS(m_defaultText);
	DELETEARRAY(m_okikaeMessage);
}


char* COkikaeData::GetOkikaeMessage(int n)
{
	if ((n>=0) && (n<m_okikaeMax))
	{
		return m_okikaeMessage + n * OKIKAE_BUFFER_SIZE;
	}

	return NULL;
}

char* COkikaeData::GetSystemOkikaeMessage(int n)
{
	if ((n>=0) && (n<m_systemOkikaeMax))
	{
		return m_systemOkikaeMessage + n * OKIKAE_BUFFER_SIZE;
	}
	return NULL;
}


void COkikaeData::SetOkikaeMessage(int n,char* mes)
{
	if (mes == NULL) return;

	if ((n>=0) && (n<m_okikaeMax))
	{
		char* ptr = m_okikaeMessage + n * OKIKAE_BUFFER_SIZE;
		int ln = strlen(mes);
		if (ln>32) ln = 32;
		memcpy(ptr,mes,ln);
		*(ptr+ln) = 0;
		*(ptr+ln+1) = 0;
	}
}

void COkikaeData::SetSystemOkikaeMessage(int n,char* mes)
{
	if (mes == NULL) return;

	if ((n>=0) && (n<m_systemOkikaeMax))
	{
		char* ptr = m_systemOkikaeMessage + n * OKIKAE_BUFFER_SIZE;
		int ln = strlen(mes);
		if (ln>32) ln = 32;
		memcpy(ptr,mes,ln);
		*(ptr+ln) = 0;
		*(ptr+ln+1) = 0;
	}
}

void COkikaeData::GetExtDataForSave(LPVOID ptr,int extNumber)
{
	memcpy(ptr,m_okikaeMessage,m_okikaeMax*OKIKAE_BUFFER_SIZE);
}



void COkikaeData::SetExtDataByLoad(LPVOID ptr,int extNumber)
{
	memcpy(m_okikaeMessage,ptr,m_okikaeMax*OKIKAE_BUFFER_SIZE);
}


/*_*/

