//
// commonnopening.cpp
//


#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\namelist.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonOpening.h"




//char CCommonOpening::m_defaultOpeningVar[]="オープニング中フラグ";

//movie対応を


CCommonOpening::CCommonOpening(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(OPENING_MODE);
//	m_classNumber = OPENING_MODE;

	LoadSetupFile("opening",16);
	m_backScriptLoopFlag = 0;
	GetBackExecSetup();
	m_nextMode = TITLE_MODE;
	GetModeNumberBySetup("nextMode",&m_nextMode);
}


CCommonOpening::~CCommonOpening()
{
	End();
}

void CCommonOpening::End(void)
{
}



int CCommonOpening::Init(void)
{
	m_game->SetLayerOff();
	m_game->SetDefaultFrameRate();

//	m_openingVarNumber = m_game->GetVarNumber(m_openingVarName);
	return -1;
}


int CCommonOpening::Calcu(void)
{
	BOOL flg = FALSE;

	if (m_mouseStatus->CheckClick(0)) flg = TRUE;
	if (m_mouseStatus->CheckClick(1)) flg = TRUE;
	if (m_backScriptEndFlag) flg = TRUE;

	if (flg)
	{
		return m_nextMode;
	}

	return -1;
}


int CCommonOpening::Print(void)
{
	PrintBackScriptOrBG();
	return -1;
}



/*_*/

