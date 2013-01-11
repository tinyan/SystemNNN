//
// commonGameVersion.cpp
//

#include <windows.h>
#include "..\nyanLib\include\commonMacro.h"

#include "commonGameVersion.h"


BOOL CCommonGameVersion::m_taikenVersion = FALSE;	//default
BOOL CCommonGameVersion::m_netVersion = FALSE;	//default
BOOL CCommonGameVersion::m_demoVersion = FALSE;	//default

BOOL CCommonGameVersion::m_loadOk = FALSE;
BOOL CCommonGameVersion::m_saveOk = FALSE;
BOOL CCommonGameVersion::m_omakeOk = FALSE;
BOOL CCommonGameVersion::m_listenBGMOk = FALSE;
BOOL CCommonGameVersion::m_cgOk = FALSE;
BOOL CCommonGameVersion::m_sceneOk = FALSE;
BOOL CCommonGameVersion::m_movieOk = FALSE;



CCommonGameVersion::CCommonGameVersion()
{
}


CCommonGameVersion::~CCommonGameVersion()
{
	End();
}


void CCommonGameVersion::End(void)
{
}

BOOL CCommonGameVersion::CheckTaikenOrNetVersion(void)
{
	if (CheckTaikenVersion()) return TRUE;
	if (CheckNetVersion()) return TRUE;

	return FALSE;
}

/*_*/


