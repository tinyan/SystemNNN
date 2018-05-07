//
// commongeneral.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\areacontrol.h"


#include "namelist.h"
#include "basicSetup.h"





CBasicSetup::CBasicSetup()
{
	m_setup = NULL;
}

CBasicSetup::~CBasicSetup()
{
	End();
}


void CBasicSetup::End(void)
{
	ENDDELETECLASS(m_setup);
}






BOOL CBasicSetup::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}


BOOL CBasicSetup::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}


BOOL CBasicSetup::LoadSetupFile(LPSTR filenameonly, int varKosuu)
{
	if (m_setup == NULL)
	{
		m_setup = new CNameList(varKosuu * 2);
	}

	if (m_setup == NULL) return FALSE;

	return m_setup->LoadInit(filenameonly);

//	char filename2[1024];
//	wsprintf(filename2,"init\\%s.xtx",filenameonly);	

//	return m_setup->LoadFile(filename2);
}





/*_*/

