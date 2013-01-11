//
// setupList.cpp
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"

#include "namelist.h"
#include "setupList.h"


CSetupList::CSetupList()
{
	m_setup = NULL;
	m_createSetup = NULL;
}

CSetupList::~CSetupList()
{
	End();
}

void CSetupList::End(void)
{
	ENDDELETECLASS(m_createSetup);
}



BOOL CSetupList::GetInitGameParam(int* lpVar, LPSTR name)
{
	if (m_setup == NULL) return FALSE;

	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;
	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}


BOOL CSetupList::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	if (m_setup == NULL) return FALSE;

	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}


BOOL CSetupList::LoadSetupFile(LPSTR filenameonly, int varKosuu)
{
	if (m_createSetup == NULL)
	{
		m_createSetup = new CNameList(varKosuu * 2);
	}

	if (m_createSetup == NULL) return FALSE;

//	char filename2[1024];
//	wsprintf(filename2,"init\\%s.xtx",filenameonly);	

//	BOOL b = m_createSetup->LoadFile(filename2);
	BOOL b = m_createSetup->LoadInit(filenameonly);
	m_setup = m_createSetup;
	return b;
}


void CSetupList::SetSetup(CNameList* setup)
{
	m_setup = setup;
}