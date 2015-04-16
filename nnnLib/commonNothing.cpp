//
// commonnothing.cpp
//


#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"
#include "..\nnnUtilLib\inputStatus.h"

#include "..\nnnUtilLib\namelist.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonNothing.h"



CCommonNothing::CCommonNothing(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(NOTHING_MODE);
//	m_classNumber = NOTHING_MODE;

	m_fillColorR = 255;
	m_fillColorG = 255;
	m_fillColorB = 255;
	m_nextMode = LOGO_MODE;

	LoadSetupFile("nothing",16);

	GetInitGameParam(&m_fillColorR,"fillColorR");
	GetInitGameParam(&m_fillColorG,"fillColorG");
	GetInitGameParam(&m_fillColorB,"fillColorB");

//	GetInitGameParam(&m_nextMode,"nextMode");
	GetModeNumberBySetup("nextMode",&m_nextMode);

//	m_cdCheckFlag = 0;
//	GetInitGameParam(&m_cdCheckFlag,"cdCheckFlag");
	m_codecCheckFlag = 0;
	GetInitGameParam(&m_codecCheckFlag,"codecCheckFlag");
	m_codecChecked = -1;

	m_codecLimit = 4;
	GetInitGameParam(&m_codecLimit,"codecLimit");

	m_startupJumpScriptFlag = 0;
	GetInitGameParam(&m_startupJumpScriptFlag,"startupJumpScriptFlag");

	LPSTR limitVarName = NULL;
	if (GetInitGameString(&limitVarName,"limitVar1"))
	{
		int var = m_game->GetVarNumber(limitVarName);
		if (var != -1)
		{
			int limitVarData = 1;
			GetInitGameParam(&limitVarData,"limitData1");
			int old = m_game->GetVarData(var);
			if (limitVarData > old)
			{
				m_game->SetVarData(var,limitVarData);
				char mes[256];
				sprintf_s(mes,256,"limitvar %d %d",var,limitVarData);
				OutputDebugString(mes);
			}
		}
	}

}



CCommonNothing::~CCommonNothing()
{
	End();
}

void CCommonNothing::End(void)
{
}



int CCommonNothing::Init(void)
{
	return -1;
}

int CCommonNothing::Calcu(void)
{
	if (m_startupJumpScriptFlag)
	{
		m_game->SetSceneMode(FALSE);
//		m_game->StartLog();
		return m_game->InitNewGame();
//		m_game->SetYoyaku();
//		return -1;
	}

	if (GetAsyncKeyState(VK_SHIFT) & 0x80000000)
	{
		if (GetAsyncKeyState(VK_CONTROL) & 0x80000000)
		{
			m_game->SetCodecError(3);
		}
	}

	if (m_codecCheckFlag != 0)
	{
		if (m_codecChecked == -1)
		{
			//check codec
			m_codecChecked = m_game->CheckCodec();

			//m_codecChecked = 1;	//0:bad 1-2•”•ªok 3:ok
#if defined _DEBUG
char mes[256];
wsprintf(mes,"[codec = %d]",m_codecChecked);
OutputDebugString(mes);
#endif

			if (m_codecChecked < m_codecLimit)
			{
				//m_game->SetCommonBackMode(CODECERROR_MODE,NOTHING_MODE);
				return CODECERROR_MODE;	//(Šm”F‚Ì‚Ý)
			}
		}
	}

/*

	if (m_cdCheckFlag != 0)
	{
		if (m_game->GetSystemParam(NNNPARAM_BGMMODE) == NNNBGMMODE_CDDA)
		{
//			if (m_game->CheckCD())
			if (1)
			{
				return m_nextMode;
			}

			m_game->SetCommonBackMode(CDERROR_MODE,m_nextMode);
			return CDERROR_MODE;
		}
	}
*/


	return m_nextMode;
}

int CCommonNothing::Print(void)
{
	CAreaControl::SetNextAllPrint();
	CAllGraphics::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
//	CPicture::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
	return 0;
}




/*_*/


