//
//
//

#include <windows.h>

#include "..\nyanLib\include\\commonMacro.h"

#include "nameList.h"
#include "nameColor.h"

CNameColor::CNameColor()
{
	m_nameList = NULL;
	m_nameKosuu = 0;
	m_colorTable = NULL;
}

CNameColor::~CNameColor()
{
	End();
}

void CNameColor::End(void)
{
	ENDDELETECLASS(m_nameList);
	DELETEARRAY(m_colorTable);
}


BOOL CNameColor::Load(LPSTR filename)
{
	ENDDELETECLASS(m_nameList);
	DELETEARRAY(m_colorTable);

	m_nameList = new CNameList();
	m_nameKosuu = 0;
	if (m_nameList->LoadFile(filename) == FALSE) return FALSE;

	int n = m_nameList->GetNameKosuu();
	m_nameKosuu = n / 4;

	if (m_nameKosuu == 0) return FALSE;

	m_colorTable = new int[m_nameKosuu];

	for (int i=0;i<m_nameKosuu;i++)
	{
		int r = atoi(m_nameList->GetName(i*4+1)) & 0xff;
		int g = atoi(m_nameList->GetName(i*4+2)) & 0xff;
		int b = atoi(m_nameList->GetName(i*4+3)) & 0xff;

		m_colorTable[i] = (r << 16) | (g << 8) | b;
	}

	return TRUE;
}


int CNameColor::SearchName(LPSTR name)
{
	if (m_nameList == NULL) return -1;
	if (m_nameKosuu == 0) return -1;

	for (int i=0;i<m_nameKosuu;i++)
	{
		LPSTR checkName = m_nameList->GetName(i*4);
		if (strcmp(name,checkName) == 0) return i;
	}

	return -1;
}

int CNameColor::GetColor(int number)
{
	if (m_nameList == NULL) return 0xffffff;
	if (m_nameKosuu == 0) return 0xffffff;

	return m_colorTable[number];
}

int CNameColor::GetColor(LPSTR name)
{
	if (m_nameList == NULL) return 0xffffff;
	if (m_nameKosuu == 0) return 0xffffff;

	int n = SearchName(name);
	if (n == -1) return 0xffffff;

	return GetColor(n);
}

