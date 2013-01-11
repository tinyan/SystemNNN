//
//
//

#include <windows.h>


#include "myKeyStatus.h"

CMyKeyStatus::CMyKeyStatus()
{
}

CMyKeyStatus::~CMyKeyStatus()
{
	End();
}

void CMyKeyStatus::End(void)
{
}


BOOL CMyKeyStatus::CheckKey(int key,BOOL clickFlag)
{
	if ((key>=0) && (key<=255))
	{
		if (clickFlag)
		{
			if (m_keyStatus[key] & 2) return TRUE;
		}
		else
		{
			if (m_keyStatus[key] & 1) return TRUE;
		}
	}

	return FALSE;
}


void CMyKeyStatus::ClearAllKey(void)
{
	for (int i=0;i<256;i++)
	{
		m_keyStatus[i] = 0;
	}
}

void CMyKeyStatus::SetKey(int key,BOOL flg)
{
	if ((key>=0) && (key<=255))
	{
		if (flg)
		{
			m_keyStatus[key] = 3;
		}
		else
		{
			m_keyStatus[key] &= ~1;
		}
	}
}

/*_*/


