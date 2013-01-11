//
// commongeneral.cpp
//

#include <windows.h>


#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\areacontrol.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myMouseStruct.h"
//#include "..\nnnUtilLib\backButton.h"

#include "..\nnnUtilLib\namelist.h"

#include "..\nnnUtilLib\nnnButtonStatus.h"
#include "..\nnnUtilLib\CommonButton.h"
#include "..\nnnUtilLib\commonBackButton.h"

#include "..\nnnUtilLib\superButtonSetup.h"
//#include "..\nnnUtilLib\UpdownButtonGroup.h"
#include "..\nnnUtilLib\commonUpdownButtonGroup.h"
#include "..\nnnUtilLib\commonUpdownBack.h"

#include "..\nnnUtilLib\superButtonPicture.h"

#include "..\nnnUtilLib\inputStatus.h"

#include "..\nnnUtilLib\printGameDate.h"
#include "..\nnnUtilLib\printAnimeLayer.h"

#include "commonSystemModeList.h"

#include "commonMode.h"

#include "scriptCallBack.h"
#include "gameCallBack.h"

#include "commonGeneral.h"


/*
char CCommonGeneral::m_systemClassNameList[][32]=
{
	"",
	"nothing","logo","opening","title","load",
	"save","backlog","listenbgm","selectmessage","printmessage",
	"draw","config","systemmenu","printoverrap","omake",
	"selectcgchara","selectcg","selectscene","","selectscenechara",
	"cderror","selectplace","printcg","","selectmoviechara",
	"selectmovie","printmovie","","nameinput","printcalendar",
	"selectheroin","codecerror","","","",
	"","","","","minigame",
	"","","","","",
	"","","","","",
};
*/


char CCommonGeneral::m_defaultUpButtonFileName[] = "ta_upButton";
char CCommonGeneral::m_defaultDownButtonFileName[] = "ta_downButton";
char CCommonGeneral::m_defaultBackButtonFileName[] = "ta_backButton";

char CCommonGeneral::m_disableQuickButtonCheckMode[][64]=
{
	"save","load","config","backlog",
	""
};


CCommonGeneral::CCommonGeneral(CGameCallBack* lpGame)
{
	m_setup = NULL;
	m_game = lpGame;
	m_classNumber = -1;

	m_commonBG = NULL;
	m_commonParts = NULL;

	m_mustAllPrintFlag = 0;
	m_miniGameFlag = 0;

	m_disableQuickButtonWork = NULL;

	m_gameLayerFirst = 1;
	m_animeLayerFirst = 1;

//	m_kaeshita = 0;

//	m_superBackButtonSetup = NULL;
//	m_superUpButtonSetup = NULL;
//	m_superDownButtonSetup = NULL;

	m_backScriptFlag = 0;
	m_backScriptName = NULL;

	m_enterExitVoiceFlag = 0;
	m_enterVoiceFileName = NULL;
	m_exitVoiceFileName = NULL;
	m_enterVoiceWaitTime = 20;
	m_exitVoiceWaitTime = 20;
	m_enterVoiceCount = 0;
	m_exitVoiceCount = 0;

	m_dialogVoiceFlag = 0;
	m_dialogVoiceWaitTime = 20;
	m_dialogVoiceCount = 0;
	m_dialogVoiceFileName = NULL;
	m_dialogYesVoiceFileName = NULL;
	m_dialogNoVoiceFileName = NULL;

	m_enterFadeInType = 0;
	m_exitFadeOutType = 0;
	m_exitFadeOutTypeSpecial = 0;

	m_enterFadeInCount = 0;
	m_exitFadeOutCount = 0;
//	m_exitFadeOutCountSpecial = 0;

	m_enterFadeInTime = 10;
	m_exitFadeOutTime = 10;
	m_exitFadeOutTimeSpecial = 10;

	m_enterFadeInSkipOkFlag = 1;
	m_exitFadeOutSkipOkFlag = 1;
	m_exitFadeOutSkipOkFlagSpecial = 1;

	m_enterFadeInColorR = 0;
	m_enterFadeInColorG = 0;
	m_enterFadeInColorB = 0;

	m_exitFadeOutColorR = 0;
	m_exitFadeOutColorG = 0;
	m_exitFadeOutColorB = 0;

	m_exitFadeOutColorSpecialR = 0;
	m_exitFadeOutColorSpecialG = 0;
	m_exitFadeOutColorSpecialB = 0;

	m_createExitScreenFlag = 1;
	m_fillExitScreenFlag = 0;

	m_createExitScreenFlagSpecial = 0;
	m_fillExitScreenFlagSpecial = 0;

	m_exitFadeOutSpecialMode = -2;

//	m_commonButton = NULL;
//	m_commonUpDown = NULL;
//	m_commonBuffer = NULL;
	
	m_commonBG = m_game->GetCommonBG();
	m_commonParts = m_game->GetCommonParts();

	m_exitScreen = m_game->GetOverrapPic(0);
	m_enterScreen = m_game->GetOverrapPic(1);

//	m_commonParts = m_game->GetCommonParts();
//	m_commonButton = m_game->GetCommonButton();
//	m_commonBuffer = m_game->GetCommonBuffer();


//	m_returningFlag = FALSE;
//	m_returningCount = 0;

	m_returnFadeOutCode = -1;

	m_mouseStatus = m_game->GetMouseStatus();
	m_inputStatus = m_game->GetInputStatus();

	m_lastPrintExitScreenFlag = FALSE;

	m_backButtonPrintX = 0;
	m_backButtonPrintY = 0;	//dummy
	m_back = NULL;
	m_createBackButton = NULL;
//	m_createBackButton2 = NULL;
	m_createUpDownButton = NULL;
//	m_createUpDownButton2 = NULL;
	m_updown = NULL;

	m_updownBack = NULL;

	m_gameDateLayerPrintFlag = 0;
	m_printGameDate = NULL;

	m_animeLayerKosuu = 0;
	m_printAnimeLayer = NULL;

	m_modeBGMNumber = -1;
	m_modeBGMMustRestartFlag = 0;
	m_modeBGMVolume = 0;
	m_modeBGMLoop = 0;
	m_modeBGMFadeInTime = -1;

	m_backScriptLoopFlag = 1;

	m_keyMoveEnable = 0;

	m_systemModeList = m_game->GetSystemModeList();

//	m_wheel = 0;
//	m_trig1Mae = TRUE;
//	m_trig2Mae = TRUE;
//	m_trig1 = FALSE;
//	m_trig2 = FALSE;
//	m_mouseX = 0;
//	m_mouseY = 0;
}

CCommonGeneral::~CCommonGeneral()
{
	GeneralEnd();
}


void CCommonGeneral::GeneralEnd(void)
{
	if (m_printAnimeLayer != NULL)
	{
		for (int i=0;i<m_animeLayerKosuu;i++)
		{
			ENDDELETECLASS(m_printAnimeLayer[i]);
		}
		DELETEARRAY(m_printAnimeLayer);
	}
	ENDDELETECLASS(m_printGameDate);
//	ENDDELETECLASS(m_superDownButtonSetup);
//	ENDDELETECLASS(m_superUpButtonSetup);
//	ENDDELETECLASS(m_superBackButtonSetup);

	ENDDELETECLASS(m_updownBack);
//	ENDDELETECLASS(m_createUpDownButton2);
	ENDDELETECLASS(m_createUpDownButton);
	ENDDELETECLASS(m_createBackButton);
	ENDDELETECLASS(m_setup);
	DELETEARRAY(m_disableQuickButtonWork);
}



int CCommonGeneral::GeneralInit(void)
{
	m_finalExitFlag = FALSE;
	m_keyActionFlag = 0;
	m_lastKeyButton = -1;

	ClearKeyMove();

	m_mouseStatus->Init();

	m_enterVoiceCount = m_enterVoiceWaitTime;
	m_exitVoiceCount = 0;

//	m_trig1Mae = TRUE;
//	m_trig2Mae = TRUE;

//	m_returningFlag = FALSE;
//	m_returningCode = -1;		//dummy youjin

	m_game->PreInitGameCallBack(m_classNumber);


	//fadein fadeout 各種せってい

	m_enterFadeInCount = 0;
	m_exitFadeOutCount = 0;


	

//	if (m_exitFadeOutType != 0)
//	{
//		m_exitFadeOutCount = m_exitFadeOutTime;
//	}



	m_specialPrintMode = 0;

	m_lastPrintExitScreenFlag = FALSE;

	BeforeInit();

	if (m_backScriptFlag)
	{
		SetBackScriptLoopEnd(FALSE);
		m_game->SetBackScriptMode();
		m_game->LoadBackScript(m_backScriptName);
	}
	else
	{
		m_game->SetBackScriptMode(FALSE);
	}

	m_game->InitMiniGameButton(-1);

	int rt = Init();
	AfterInit();

	if (m_enterFadeInType != 0)
	{
		m_enterFadeInCount = m_enterFadeInTime;
		CreateEnterScreen();
	}

	PlayCommonBGM();

	return rt;
}


int CCommonGeneral::OmakeGeneralInit(void)
{
	int rt = Init();
	return rt;
}


int CCommonGeneral::GeneralCalcu(void)
{
	m_specialPrintMode = 0;

//	if (m_returningFlag)
//	{
//		m_returningCount--;
//		if (m_returningCount<=0) return m_returningCode;
//		return -1;
//	}

	if (m_enterExitVoiceFlag)
	{
		if (m_enterVoiceCount > 0)
		{
			m_enterVoiceCount--;
			if (m_enterVoiceCount == 0)
			{
				if (m_enterVoiceFileName != NULL)
				{
					m_game->PlaySystemVoiceByFileName(m_enterVoiceFileName);
				}
			}
		}


		if (m_exitVoiceCount > 0)
		{
			m_exitVoiceCount--;
			if (m_exitVoiceCount == 0)
			{
				if (m_exitVoiceFileName != NULL)
				{
					m_game->PlaySystemVoiceByFileName(m_exitVoiceFileName);
				}
			}
		}
	}


	if (m_enterFadeInType != 0)
	{
		if (m_enterFadeInCount > 0)
		{
			m_specialPrintMode = 1;

			m_enterFadeInCount--;
			if (m_enterFadeInSkipOkFlag)
			{
				if (m_mouseStatus->CheckSkipClick())
				{
					m_enterFadeInCount = 0;
				}
			}

			return -1;
		}
	}


	if (CheckSpecialFadeOutMode())
	{
		if (m_exitFadeOutTypeSpecial != 0)
		{
			if (m_exitFadeOutCount > 0)
			{
				m_specialPrintMode = 2;
				m_exitFadeOutCount--;
				if (m_exitFadeOutSkipOkFlagSpecial)
				{
					if (m_mouseStatus->CheckSkipClick())
					{
						m_exitFadeOutCount = 0;
					}
				}

				if (m_exitFadeOutCount <= 0)
				{
					if (m_fillExitScreenFlagSpecial) FillExitScreen();

					SetFinalExitRoutine();
					return m_returnFadeOutCode;
				}

				return -1;
			}
		}
	}
	else
	{
		if (m_exitFadeOutType != 0)
		{
			if (m_exitFadeOutCount > 0)
			{
				m_specialPrintMode = 2;
				m_exitFadeOutCount--;
				if (m_exitFadeOutSkipOkFlag)
				{
					if (m_mouseStatus->CheckSkipClick())
					{
						m_exitFadeOutCount = 0;
					}
				}

				if (m_exitFadeOutCount <= 0)
				{
					if (m_fillExitScreenFlag) FillExitScreen();
					SetFinalExitRoutine();
					return m_returnFadeOutCode;
				}

				return -1;
			}
		}
	}




//	m_game->GetMouseStatus(&m_mouseStatus);
//
//	m_mouseX = m_mouseStatus.mouseX;
//	m_mouseY = m_mouseStatus.mouseY;
//	m_trig1 = m_mouseStatus.trig1;
//	m_trig2 = m_mouseStatus.trig2;
//	m_trig3 = m_mouseStatus.trig3;
//	m_trig1Mae = m_mouseStatus.trig1Mae;
//	m_trig2Mae = m_mouseStatus.trig2Mae;
//	m_trig3Mae = m_mouseStatus.trig3Mae;
//	m_wheel = m_mouseStatus.wheel;
//	m_wheelMoveFlag = m_mouseStatus.wheelMoveFlag;
//
///////////@@@@@@	m_game->GetMouseStatus(&m_mouseX,&m_mouseY,&m_trig1,&m_trig2, &m_trig1Mae, &m_trig2Mae, &m_wheel);

	if (m_miniGameFlag)
	{
		if (m_game->CheckMiniGame(m_classNumber))
		{
			m_game->SetCommonBackMode(MINIGAME_MODE,m_classNumber);
		//	return MINIGAME_MODE;
			return ReturnFadeOut(MINIGAME_MODE);
		}
	}


	BeforeCalcu();

	if (m_backScriptFlag)
	{
		BOOL loopFlag = TRUE;
		if (m_backScriptLoopFlag == 0) loopFlag = FALSE;

		if (m_game->CheckBackScriptMode())
		{
			if (m_game->CalcuBackScript(loopFlag))
			{
				SetBackScriptLoopEnd();
			}
		}
	}

	if (m_keyMoveEnable)
	{
		CalcuKeyMove();

		POINT pt = m_mouseStatus->GetZahyo();
		int pl = GetOnKeyArea(pt);
		if (pl != -1)
		{
			m_lastKeyButton = pl;
		}
	}


	int rt = Calcu();
	AfterCalcu();
	return rt;
}



int CCommonGeneral::OmakeGeneralCalcu(BOOL mustFlag)
{
	if (mustFlag == FALSE)
	{
//		if (m_returningFlag)
//		{
//			return -1;
//		}

		if (m_enterFadeInType != 0)
		{
			if (m_enterFadeInCount > 0)
			{
				return -1;
			}
		}


		if (CheckSpecialFadeOutMode())
		{
			if (m_exitFadeOutTypeSpecial != 0)
			{
				if (m_exitFadeOutCount > 0)
				{
					return -1;
				}
			}
		}
		else
		{
			if (m_exitFadeOutType != 0)
			{
				if (m_exitFadeOutCount > 0)
				{
					return -1;
				}
			}
		}
	}

	int rt = Calcu();
	return rt;
}

int CCommonGeneral::GeneralPrint(void)
{
	if (m_specialPrintMode == 1)
	{
		CAreaControl::SetNextAllPrint();
		PrintEnterFadeIn();
		return -1;
	}

	if (m_specialPrintMode == 2)
	{
		CAreaControl::SetNextAllPrint();
		PrintExitFadeOut();
		return -1;
	}

	if (m_mustAllPrintFlag)	CAreaControl::SetNextAllPrint();

	BeforePrint();
	int rt = -1;

//	if (m_lastPrintExitScreenFlag)
	if (0)
	{
		m_exitScreen->Put(0,0,FALSE);
		m_lastPrintExitScreenFlag = FALSE;
	}
	else
	{
		rt = Print();
	}

	if (m_miniGameFlag)
	{
		m_game->PrintMiniGameButton();
	}

	AfterPrint();
	return rt;
}


int CCommonGeneral::OmakeGeneralPrint(BOOL mustFlag)
{
	if (mustFlag == FALSE)
	{
		if (m_specialPrintMode == 1)
		{
			return -1;
		}

		if (m_specialPrintMode == 2)
		{
			return -1;
		}
	}

	int rt = Print();
	return rt;
}

int CCommonGeneral::GeneralEndMode(void)
{
	return EndMode();
}

int CCommonGeneral::OmakeGeneralEndMode(void)
{
	return EndMode();
}

int CCommonGeneral::PrintEnterFadeIn(void)
{
//	void Overrap(CPicture* nextPic, int nowPercent, POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

//OutputDebugString("[General::fadein]");

//	if (m_enterFadeInType <= 2)	//1,2
	if (m_enterFadeInType == -1)
	{
		int dv = m_enterFadeInTime;
		if (dv < 1) dv = 1;

		int ps = ((m_enterFadeInTime - m_enterFadeInCount) * 100) / dv;
		if (ps < 0) ps = 0;
		if (ps>100) ps = 100;

		m_exitScreen->Overrap(m_enterScreen,ps);
	}
	else if (m_enterFadeInType >= 1)
	{
		int count = m_enterFadeInTime - m_enterFadeInCount;
		int countMax = m_enterFadeInTime;
		if (count < 0) count = 0;
		if (countMax < 1) countMax = 1;
		if (count > countMax) count = countMax;

		m_game->PrintSimpleWipe(count,countMax,m_enterFadeInType-1);
	}




	return -1;
}


int CCommonGeneral::PrintExitFadeOut(void)
{
	if (CheckSpecialFadeOutMode())
	{
		if (m_exitFadeOutTypeSpecial == -1)	
		{
			int dv = m_exitFadeOutTimeSpecial - 1;
			if (dv < 1) dv = 1;

			int ps = ((m_exitFadeOutTimeSpecial - m_exitFadeOutCount - 1) * 100) / dv;
			if (ps < 0) ps = 0;
			if (ps>100) ps = 100;

			m_exitScreen->Overrap(m_enterScreen,ps);
		}
		else if (m_exitFadeOutTypeSpecial >= 1)
		{
			int count = m_exitFadeOutTimeSpecial - m_exitFadeOutCount;
			int countMax = m_exitFadeOutTimeSpecial - 1;
			if (count < 0) count = 0;
			if (countMax < 1) countMax = 1;
			if (count > countMax) count = countMax;

			m_game->PrintSimpleWipe(count,countMax,m_exitFadeOutTypeSpecial-1);
		}
	}
	else
	{
		if (m_exitFadeOutType == -1)	
		{
			int dv = m_exitFadeOutTime - 1;
			if (dv < 1) dv = 1;

			int ps = ((m_exitFadeOutTime - m_exitFadeOutCount - 1) * 100) / dv;
			if (ps < 0) ps = 0;
			if (ps>100) ps = 100;

			m_exitScreen->Overrap(m_enterScreen,ps);
		}
		else if (m_exitFadeOutType >= 1)
		{
			int count = m_exitFadeOutTime - m_exitFadeOutCount;
			int countMax = m_exitFadeOutTime - 1;
			if (count < 0) count = 0;
			if (countMax < 1) countMax = 1;
			if (count > countMax) count = countMax;

			m_game->PrintSimpleWipe(count,countMax,m_exitFadeOutType-1);
		}
	}

	return -1;
}


BOOL CCommonGeneral::CheckClick(BOOL bTrig2Flag)
{
	if (bTrig2Flag == FALSE)
	{
		return m_mouseStatus->CheckClick();
	}
	else
	{
		return m_mouseStatus->CheckClick(1);
	}

	return FALSE;
}

/*
void CCommonGeneral::SetReturnCode(int cd, int cnt)
{
	m_game->PreChangeMode(cd);

	m_returningFlag = TRUE;
	m_returningCode = cd;
	m_returningCount = cnt;
}
*/

int CCommonGeneral::GeneralBack(void)
{
	return GeneralInit();
}

BOOL CCommonGeneral::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CCommonGeneral::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CCommonGeneral::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CCommonGeneral::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}


BOOL CCommonGeneral::LoadSetupFile(LPSTR filenameonly, int varKosuu)
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


void CCommonGeneral::SetBackMode(int mode)
{
	m_backMode = mode;
}


void CCommonGeneral::GetEnterExitVoiceFileName(void)
{
	if (m_setup == NULL) return;

	GetInitGameParam(&m_enterExitVoiceFlag,"enterExitVoiceFlag");
	if (m_enterExitVoiceFlag == 0) return;

	GetInitGameString(&m_enterVoiceFileName,"enterVoiceFileName");
	GetInitGameString(&m_exitVoiceFileName,"exitVoiceFileName");
	
	m_enterVoiceWaitTime = 20;
	GetInitGameParam(&m_enterVoiceWaitTime,"enterVoiceWaitTime");

	m_exitVoiceWaitTime = 5;
	GetInitGameParam(&m_exitVoiceWaitTime,"exitVoiceWaitTime");
}


void CCommonGeneral::GetDialogVoiceFileName(void)
{
	if (m_setup == NULL) return;

	GetInitGameParam(&m_dialogVoiceFlag,"dialogVoiceFlag");
	if (m_dialogVoiceFlag == 0) return;

	GetInitGameString(&m_dialogVoiceFileName,"dialogVoiceFileName");
	
	m_dialogVoiceWaitTime = 10;
	GetInitGameParam(&m_dialogVoiceWaitTime,"dialogVoiceWaitTime");

	GetInitGameString(&m_dialogYesVoiceFileName,"dialogYesVoiceFileName");
	GetInitGameString(&m_dialogNoVoiceFileName,"dialogNoVoiceFileName");
}



void CCommonGeneral::OnEnterExitAreaForVoice(void)
{
	if (m_enterExitVoiceFlag == 0) return;

	if (m_exitVoiceCount == 0)
	{
		m_exitVoiceCount = m_exitVoiceWaitTime;
	}

	m_enterVoiceCount = 0;
}

void CCommonGeneral::OnExitExitAreaForVoice(void)
{
	if (m_enterExitVoiceFlag == 0) return;

	m_exitVoiceCount = 0;
	m_enterVoiceCount = 0;
}


void CCommonGeneral::GetFadeInOutSetup(void)
{
	GetInitGameParam(&m_enterFadeInType,"enterFadeInType");
	if (m_enterFadeInType)
	{
		GetInitGameParam(&m_enterFadeInTime,"enterFadeInTime");
		if (m_enterFadeInType == -1)
		{
			GetInitGameParam(&m_enterFadeInColorR,"enterFadeInColorR");
			GetInitGameParam(&m_enterFadeInColorG,"enterFadeInColorG");
			GetInitGameParam(&m_enterFadeInColorB,"enterFadeInColorB");
		}
	}


	GetInitGameParam(&m_exitFadeOutType,"exitFadeOutType");
	if (m_exitFadeOutType)
	{
		GetInitGameParam(&m_exitFadeOutTime,"exitFadeOutTime");
		GetInitGameParam(&m_exitFadeOutColorR,"exitFadeOutColorR");
		GetInitGameParam(&m_exitFadeOutColorG,"exitFadeOutColorG");
		GetInitGameParam(&m_exitFadeOutColorB,"exitFadeOutColorB");
		m_fillExitScreenFlag = 1;
		GetInitGameParam(&m_fillExitScreenFlag,"fillExitScreenFlag");
	}

	GetInitGameParam(&m_createExitScreenFlag,"createExitScreenFlag");


//	int smd = GetModeNumberByName("exitFadeOutSpecialMode");
	int smd = -1;
	if (GetModeNumberBySetup("exitFadeOutSpecialMode",&smd))
	{
		if (smd != -1)
		{
			m_exitFadeOutSpecialMode = smd;
		}
	}


//	GetInitGameParam(&m_exitFadeOutSpecialMode,"exitFadeOutSpecialMode");


	if (m_exitFadeOutSpecialMode >= 0)
	{
		GetInitGameParam(&m_exitFadeOutTypeSpecial,"exitFadeOutTypeSpecial");
		if (m_exitFadeOutTypeSpecial)
		{
			GetInitGameParam(&m_exitFadeOutTimeSpecial,"exitFadeOutTimeSpecial");
			GetInitGameParam(&m_exitFadeOutColorSpecialR,"exitFadeOutColorSpecialR");
			GetInitGameParam(&m_exitFadeOutColorSpecialG,"exitFadeOutColorSpecialG");
			GetInitGameParam(&m_exitFadeOutColorSpecialB,"exitFadeOutColorSpecialB");

			m_createExitScreenFlagSpecial = 1;
			GetInitGameParam(&m_createExitScreenFlagSpecial,"createExitScreenFlagSpecial");
		}

		GetInitGameParam(&m_fillExitScreenFlagSpecial,"fillExitScreenFlagSpecial");
	}
}


void CCommonGeneral::GetBGMSetup(void)
{
	GetInitGameParam(&m_modeBGMNumber,"bgmNumber");
	GetInitGameParam(&m_modeBGMMustRestartFlag,"bgmRestartFlag");
	GetInitGameParam(&m_modeBGMVolume,"bgmVolume");
	GetInitGameParam(&m_modeBGMLoop,"bgmLoop");
	m_modeBGMFadeInTime = m_game->GetDefaultFadeInTime();
	GetInitGameParam(&m_modeBGMFadeInTime,"bgmFadeInTime");
}

void CCommonGeneral::GetAddLayerSetup(void)
{
	GetInitGameParam(&m_gameDateLayerPrintFlag,"gameDateLayerPrintFlag");
	if (m_gameDateLayerPrintFlag)
	{
		CPicture* lpBG = m_commonBG;
		if (m_mustAllPrintFlag)
		{
			lpBG = NULL;
		}
		if (m_backScriptFlag)
		{
			lpBG = NULL;
		}
		m_printGameDate = new CPrintGameDate(m_setup,"game",lpBG);


		m_generalGameYearVarNumber = m_game->GetVarNumber("year");
		m_generalGameDateVarNumber = m_game->GetVarNumber("date");

		GetInitGameParam(&m_gameLayerFirst,"gameLayerFirst");
	}
}

void CCommonGeneral::GetAnimeLayerSetup(void)
{
	GetInitGameParam(&m_animeLayerKosuu,"animeLayerNumber");
	if (m_animeLayerKosuu > 0)
	{
		if (m_printAnimeLayer == NULL)
		{
			if (m_classNumber == PRINTMESSAGE_MODE)
			{
				m_mustAllPrintFlag = 1;
			}

			m_printAnimeLayer = new CPrintAnimeLayer*[m_animeLayerKosuu];
			for (int i=0;i<m_animeLayerKosuu;i++)
			{
				char name[256];
				wsprintf(name,"animeLayer%d",i+1);
				CPicture* lpBG = m_commonBG;
				if (m_mustAllPrintFlag)
				{
					lpBG = NULL;
				}
				if (m_backScriptFlag)
				{
					lpBG = NULL;
				}

				m_printAnimeLayer[i] = new CPrintAnimeLayer(m_setup,name,lpBG);
				LPSTR picname = m_printAnimeLayer[i]->GetPictureFileName();
				CPicture* lpPic = m_game->GetSystemPicture(picname);
				m_printAnimeLayer[i]->SetPicture(lpPic);

				//var
				LPSTR varName = m_printAnimeLayer[i]->GetVarName();
				if (varName != NULL)
				{
					if ((*varName) != '@')
					{
						int varNumber = m_game->GetVarNumber(varName);
						m_printAnimeLayer[i]->SetVarNumber(varNumber);
					}
				}
			}
		}

		GetInitGameParam(&m_animeLayerFirst,"animeLayerFirst");
	}
}

void CCommonGeneral::GetDisableQuickButtonSetup(void)
{
	if (m_disableQuickButtonWork != NULL) return;

	m_disableQuickButtonWork = new int[256];
	ZeroMemory(m_disableQuickButtonWork,sizeof(int)*256);

	int n = 0;
	while (n<256)
	{
		LPSTR checkModeName = m_disableQuickButtonCheckMode[n];
		if ((*checkModeName) == 0)
		{
			break;
		}

		char name[256];
		wsprintf(name,"disableQuick%sButton",checkModeName);
		int st = 0;
		if (GetInitGameParam(&st,name))
		{
			if (st)
			{
				int checkMode = GetModeNumberByName(checkModeName);
				if (checkMode > 0)
				{
					m_disableQuickButtonWork[checkMode] = st;
				}
			}
		}
		n++;
	}
}

int CCommonGeneral::CheckOtherSetup(int para1,int para2,LPVOID lpParam)
{
	if (para2 == 0)
	{
		//disable button check
		if (m_disableQuickButtonWork != NULL)
		{
			return m_disableQuickButtonWork[para1];
		}
	}

	return 0;
}


void CCommonGeneral::CreateExitScreen(void)
{
//OutputDebugString("[General::CreateExit]");

#if defined _DEBUG
		OutputDebugString("\n\nCreateExitScreen\n");
#endif

	//eraseMouse
	//m_game->EraseMouse();
	m_game->Erase();

	ReCreateExitScreen();
//OutputDebugString("exitscreen::getscreen");

	m_exitScreen->GetScreen();
//OutputDebugString("[CreateExitScreen]\n");
	
	//必要ならenterScreenぬりつぶし
	if (CheckSpecialFadeOutMode())
	{
		if (m_exitFadeOutTypeSpecial >= 1)
		{
			FillPicture(m_enterScreen,m_exitFadeOutColorSpecialR,m_exitFadeOutColorSpecialG,m_exitFadeOutColorSpecialB);
		}
	}
	else
	{
		if (m_exitFadeOutType >= 1)
		{
			FillPicture(m_enterScreen,m_exitFadeOutColorR,m_exitFadeOutColorG,m_exitFadeOutColorB);
		}
	}
}

void CCommonGeneral::FillExitScreen(void)
{
	FillPicture(m_exitScreen,m_exitFadeOutColorR,m_exitFadeOutColorG,m_exitFadeOutColorB);
}



void CCommonGeneral::CreateEnterScreen(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CreateStartScreen();
OutputDebugString("[[commongeneral enterscreen::getscreen]]");
	m_enterScreen->GetScreen();

	//必要ならexitScreenぬりつぶし
	if (m_enterFadeInType == -1)
	{
		FillPicture(m_exitScreen,m_enterFadeInColorR,m_enterFadeInColorG,m_enterFadeInColorB);
	}
}



void CCommonGeneral::FillPicture(CPicture* lpPic, int colR, int colG, int colB)
{
	int* dst = (int*)(lpPic->GetBuffer());
	RECT rc;
	lpPic->GetPicSize(&rc);
	int sz = rc.right * rc.bottom;

	int col = (colR << 16) | (colG << 8) | colB;
#if defined _TINYAN3DLIB_
dst += 128 / sizeof(int);
#endif

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov edi,dst
		mov ecx,sz
		mov eax,col
		cld
		rep stosd

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}



void CCommonGeneral::CreateStartScreen(void)
{
	CAreaControl::SetNextAllPrint();
//	m_commonBG->Put(0,0,FALSE);
	Print();
}


int CCommonGeneral::ReturnFadeOut(int returnCode)
{
#if defined _DEBUG
	char mes[256];
	sprintf_s(mes,sizeof(mes),"\nReturnFadeOut:%d(from:%d)",returnCode,m_classNumber);
	OutputDebugString(mes);

#endif

	CAreaControl::SetNextAllPrint();

	m_game->PreChangeMode(returnCode);
	m_returnFadeOutCode = returnCode;

	BOOL createFlag = FALSE;

	if (CheckSpecialFadeOutMode())
	{
		if ((m_createExitScreenFlagSpecial != 0) || (m_exitFadeOutTypeSpecial != 0))
		{
			CreateExitScreen();
			createFlag = TRUE;
		}
	}
	else
	{
		if ((m_createExitScreenFlag != 0) || (m_exitFadeOutType != 0))
		{
			CreateExitScreen();
			createFlag = TRUE;
		}
	}


	if (CheckSpecialFadeOutMode())
	{
		if (m_exitFadeOutTypeSpecial != 0)
		{
			m_exitFadeOutCount = m_exitFadeOutTimeSpecial;
			return -1;
		}
	}
	else
	{
		if (m_exitFadeOutType != 0)
		{
			m_exitFadeOutCount = m_exitFadeOutTime;
			return -1;
		}
	}


	SetFinalExitRoutine();
	if (createFlag)
	{
		m_lastPrintExitScreenFlag = TRUE;
	}

//	m_game->SetBackScriptMode(FALSE);
//	m_game->SetNextBackScriptOff();

	return returnCode;
}



BOOL CCommonGeneral::CheckSpecialFadeOutMode(void)
{
//	if ((m_exitFadeOutSpecialMode >= 0) && (m_backMode == m_exitFadeOutSpecialMode)) return TRUE;

	if ((m_exitFadeOutSpecialMode >= 0) && (m_returnFadeOutCode == m_exitFadeOutSpecialMode)) return TRUE;


	return FALSE;
}

/*
void CCommonGeneral::GetBackButtonPara(void)
{
	GetInitGameParam(&m_backButtonPrintX,"backButtonPrintX");
	GetInitGameParam(&m_backButtonPrintY,"backButtonPrintY");

}
*/


void CCommonGeneral::CreateBackButton(void)
{
	m_backButtonType = 0;	//0:この設定でつくる 1:CGameからもらう
	GetInitGameParam(&m_backButtonType,"backButtonType");

	m_backButtonPrintX = 0;
	m_backButtonPrintY = 0;

	GetInitGameParam(&m_backButtonPrintX,"backPrintX");
	GetInitGameParam(&m_backButtonPrintY,"backPrintY");

	m_filenameBack = m_defaultBackButtonFileName;
	GetInitGameString(&m_filenameBack,"BackFileName");



	if (m_backButtonType == 0)
	{
		CPicture* bgPic = m_commonBG;
		if (m_backScriptFlag) bgPic = NULL;
		int backButtonBGUse = 1;
		GetInitGameParam(&backButtonBGUse,"backButtonBGUse");
		if (backButtonBGUse == 0)
		{
			bgPic = NULL;
		}

		int commonBackFlag = 0;
		GetInitGameParam(&commonBackFlag,"useCommonBackSetup");
		if (commonBackFlag)
		{
			CNameList* gameSetup = m_game->GetGameSetup();

			m_createBackButton = new CCommonBackButton(gameSetup,"back",bgPic);


			int rNum = gameSetup->SearchName2("backPrintX");
			if (rNum != -1)
			{
				m_backButtonPrintX = atoi(gameSetup->GetName(rNum + 1));
			}
			rNum = gameSetup->SearchName2("backPrintY");
			if (rNum != -1)
			{
				m_backButtonPrintY = atoi(gameSetup->GetName(rNum + 1));
			}

			GetInitGameParam(&m_backButtonPrintX,"backPrintX");
			GetInitGameParam(&m_backButtonPrintY,"backPrintY");

			rNum = gameSetup->SearchName2("BackFileName");
			if (rNum != -1)
			{
				m_filenameBack = gameSetup->GetName(rNum+1);
			}
			

		}
		else
		{
			m_createBackButton = new CCommonBackButton(m_setup,"back",bgPic);
		}
		
		m_createBackButton->SetPicture(CSuperButtonPicture::GetPicture(0));

		m_back = m_createBackButton;
	}
	else if (m_backButtonType == 1)
	{
		m_back = m_game->GetBackButton();

	}
}




void CCommonGeneral::CreateUpDownButton(void)
{
	m_updownButtonType = 0;	//0:この設定でつくる 1:CGameからもらう
	GetInitGameParam(&m_updownButtonType,"updownButtonType");

	m_upPrintX = 0;
	m_upPrintY = 0;
	m_downPrintX = 0;
	m_downPrintY = 0;

	GetInitGameParam(&m_upPrintX,"upPrintX");
	GetInitGameParam(&m_upPrintY,"upPrintY");
	GetInitGameParam(&m_downPrintX,"downPrintX");
	GetInitGameParam(&m_downPrintY,"downPrintY");

	m_filenameUp = m_defaultUpButtonFileName;
	m_filenameDown = m_defaultDownButtonFileName;

	GetInitGameString(&m_filenameUp,"UpFileName");
	GetInitGameString(&m_filenameDown,"DownFileName");


	if (m_updownButtonType == 0)
	{
		CPicture* bgPic = m_commonBG;
		if (m_backScriptFlag) bgPic = NULL;


		int commonUpDownFlag = 0;
		GetInitGameParam(&commonUpDownFlag,"useCommonUpDownSetup");
		if (commonUpDownFlag)
		{
			CNameList* gameSetup = m_game->GetGameSetup();

			m_createUpDownButton = new CCommonUpDownButtonGroup(gameSetup,bgPic);


			int rNum = gameSetup->SearchName2("upPrintX");
			if (rNum != -1)
			{
				m_upPrintX = atoi(gameSetup->GetName(rNum + 1));
			}
			rNum = gameSetup->SearchName2("upPrintY");
			if (rNum != -1)
			{
				m_upPrintY = atoi(gameSetup->GetName(rNum + 1));
			}
			rNum = gameSetup->SearchName2("downPrintX");
			if (rNum != -1)
			{
				m_downPrintX = atoi(gameSetup->GetName(rNum + 1));
			}
			rNum = gameSetup->SearchName2("downPrintY");
			if (rNum != -1)
			{
				m_downPrintY = atoi(gameSetup->GetName(rNum + 1));
			}

			GetInitGameParam(&m_upPrintX,"upPrintX");
			GetInitGameParam(&m_upPrintY,"upPrintY");
			GetInitGameParam(&m_downPrintX,"downPrintX");
			GetInitGameParam(&m_downPrintY,"downPrintY");


			rNum = gameSetup->SearchName2("upFileName");
			if (rNum != -1)
			{
				m_filenameUp = gameSetup->GetName(rNum+1);
			}
			rNum = gameSetup->SearchName2("downFileName");
			if (rNum != -1)
			{
				m_filenameDown = gameSetup->GetName(rNum+1);
			}
		}
		else
		{
			m_createUpDownButton = new CCommonUpDownButtonGroup(m_setup,bgPic);
		}
		
		m_createUpDownButton->SetPicture(0,CSuperButtonPicture::GetPicture(1));
		m_createUpDownButton->SetPicture(1,CSuperButtonPicture::GetPicture(2));


		m_updown = m_createUpDownButton;
	}
	else if (m_backButtonType == 1)
	{
		m_updown = m_game->GetCommonUpDown();
	}
}


void CCommonGeneral::CreateUpDownBack(void)
{
	m_updownBack = new CCommonUpdownBack(m_back,m_updown);
}



void CCommonGeneral::SetUpDownZahyo(void)
{
	if (m_updown != NULL)
	{
		m_updown->SetUpDownZahyo(m_upPrintX,m_upPrintY,m_downPrintX,m_downPrintY);
	}
}

void CCommonGeneral::SetBackButtonZahyo(void)
{
	POINT pt;
	pt.x = m_backButtonPrintX;
	pt.y = m_backButtonPrintY;
	m_back->SetZahyo(pt);
}


void CCommonGeneral::PlayCommonBGM(void)
{
	if (m_modeBGMMustRestartFlag)
	{
		m_game->StopMusic();
	}

	if (m_modeBGMNumber >= 1)
	{
		int nowBGM = m_game->GetNowMusicNumber();
		int newBGM = m_modeBGMNumber - 1;

		if (nowBGM != newBGM)
		{
			if (m_modeBGMFadeInTime == -1)
			{
				m_game->PlayMusic(newBGM,m_modeBGMLoop,m_modeBGMVolume);
			}
			else
			{
				m_game->PlayMusic(newBGM,m_modeBGMLoop,m_modeBGMVolume,m_modeBGMFadeInTime);
			}
		}
	}
}


void CCommonGeneral::GetBackExecSetup(void)
{
	GetInitGameParam(&m_backScriptFlag,"backScriptFlag");
	if (m_backScriptFlag)
	{
		GetInitGameString(&m_backScriptName,"backScriptName");
		GetInitGameParam(&m_backScriptLoopFlag,"backScriptLoopFlag");
	}
}



void CCommonGeneral::PlayButtonSound(CCommonButton* lpButton,int buttonReturnCode)
{
	if (buttonReturnCode == -1) return;
	int code = buttonReturnCode & NNNBUTTON_STATUSMASK;

	if (code == NNNBUTTON_STARTCLICK)
	{
		int sound = lpButton->GetClickSound();
		if (sound > 0)
		{
			int volumeType = lpButton->GetVolumeType();
			m_game->PlaySystemSound(sound - 1,volumeType);
		}
	}

	if (code == NNNBUTTON_CANNOTCLICK)
	{
		int sound = lpButton->GetCannotClickSound();
		if (sound > 0)
		{
			int volumeType = lpButton->GetVolumeType();
			m_game->PlaySystemSound(sound - 1,volumeType);
		}
	}


	if (code == NNNBUTTON_ENTER)
	{
		int sound = lpButton->GetEnterSound();
		if (sound > 0)
		{
			if (lpButton->GetEnterSoundWait() == 0)
			{
				int volumeType = lpButton->GetVolumeType();
				m_game->PlaySystemSound(sound - 1,volumeType);
			}
		}
	}

	if (code == NNNBUTTON_EXIT)
	{
		int sound = lpButton->GetExitSound();
		if (sound > 0)
		{
			if (lpButton->GetExitSoundWait() == 0)
			{
				int volumeType = lpButton->GetVolumeType();
				m_game->PlaySystemSound(sound - 1,volumeType);
			}
		}
	}

	if (code == NNNBUTTON_REQUESTSOUND)
	{
		int sound = buttonReturnCode & NNNBUTTON_DATAMASK;
		if (sound > 0)
		{
			int volumeType = lpButton->GetVolumeType();
			m_game->PlaySystemSound(sound - 1,volumeType);
		}
	}
}


void CCommonGeneral::PrintBackScriptOrBG(void)
{
	if (m_backScriptFlag)
	{
		CAreaControl::SetNextAllPrint();
		m_game->PrintBackScript();
	}
	else
	{
		BOOL b = CAreaControl::CheckAllPrintMode();
		if (b)
		{
			m_commonBG->Put(0,0,FALSE);
		}
	}
}


BOOL CCommonGeneral::GetModeNumberBySetup(LPSTR name, int* lpVar)
{
	LPSTR nameData = NULL;
	
	if (GetInitGameString(&nameData,name))
	{
		if (nameData != NULL)
		{
			if ((*nameData) != 0)
			{
				int dat = GetModeNumberByName(nameData);
				if (dat > 0)
				{
					*lpVar = dat;
					return TRUE;
				}
			}
		}
	}

	return FALSE;
}


int CCommonGeneral::GetModeNumberByName(LPSTR name)
{
	return m_systemModeList->GetModeNumberByName(name);
	/*
	int nm = -1;
	for (int i=1;i<51;i++)
	{
		LPSTR name2 = m_systemClassNameList[i];
		if ((*name2) != 0)
		{
			if (_stricmp(name,m_systemClassNameList[i]) == 0)
			{
				nm = i;
				break;
			}
		}
	}

	if (nm == -1)
	{
		nm = atoi(name);
	}

	return nm;
	*/

}

void CCommonGeneral::LoadBackBG(void)
{
	if (m_backScriptFlag == FALSE)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s",m_filenameBG);
		m_commonBG->LoadDWQ(filename);
	}
}


void CCommonGeneral::LoadUpDownButtonPic(void)
{
	if (m_updown == NULL) return;

	for (int i=0;i<2;i++)
	{
		CPicture* lpPic = m_updown->GetPicture(i);
		if (lpPic != NULL)
		{
			LPSTR name = m_updown->GetFileName(i);
			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);
		}
	}
}

void CCommonGeneral::LoadBackButtonPic(void)
{
	if (m_back == NULL) return;

	CPicture* lpPic = m_back->GetPicture();
	if (lpPic != NULL)
	{
		LPSTR name = m_back->GetFileName();
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}
}




int CCommonGeneral::ProcessUpDownBack(int rt)
{
	if (rt == NNNBUTTON_NOTHING) return -1;

	int st = CCommonButton::GetButtonStatus(rt);
	int requestSoundFlag = CCommonButton::CheckRequestSound(rt);
	int sound = 0;
	if (requestSoundFlag)
	{
		sound = CCommonButton::GetButtonSound(rt);
	}
	int existDataFlag = CCommonButton::CheckExistData(rt);
	int nm = -1;
	if (existDataFlag)
	{
		nm = CCommonButton::GetButtonData(rt);
	}

	if (requestSoundFlag)
	{
		if (sound > 0)
		{
			int volumeType = CCommonButton::GetVolumeTypeData(rt);
			m_game->PlaySystemSound(sound - 1,volumeType);
		}
	}

	if ((st == NNNBUTTON_NUMBER) && (existDataFlag))
	{
		return nm;
	}

	return -1;
}

//もしかしておんなじ??
int CCommonGeneral::ProcessButtonGroup(int rt)
{
	if (rt == NNNBUTTON_NOTHING) return -1;

	int st = CCommonButton::GetButtonStatus(rt);
	int requestSoundFlag = CCommonButton::CheckRequestSound(rt);
	int sound = 0;
	if (requestSoundFlag)
	{
		sound = CCommonButton::GetButtonSound(rt);
	}
	int existDataFlag = CCommonButton::CheckExistData(rt);
	int nm = -1;
	if (existDataFlag)
	{
		nm = CCommonButton::GetButtonData(rt);
	}

	if (requestSoundFlag)
	{
		if (sound > 0)
		{
			int volumeType = CCommonButton::GetVolumeTypeData(rt);
			m_game->PlaySystemSound(sound - 1,volumeType);
		}
	}

	if ((st == NNNBUTTON_NUMBER) && (existDataFlag))
	{
		return nm;
	}

	return -1;
}



int CCommonGeneral::ProcessCommonButton(int rt)
{
	if (rt == NNNBUTTON_NOTHING) return -1;

	int st = CCommonButton::GetButtonStatus(rt);
	int requestSoundFlag = CCommonButton::CheckRequestSound(rt);
	int sound = 0;
	if (requestSoundFlag)
	{
		sound = CCommonButton::GetButtonSound(rt);
	}
	int existDataFlag = CCommonButton::CheckExistData(rt);
	int nm = -1;
	if (existDataFlag)
	{
		nm = CCommonButton::GetButtonData(rt);
	}

	if (requestSoundFlag)
	{
		if (sound > 0)
		{
			int volumeType = CCommonButton::GetVolumeTypeData(rt);
			m_game->PlaySystemSound(sound - 1,volumeType);
		}
	}

	if ((st == NNNBUTTON_NUMBER) && (existDataFlag))
	{
		return nm;	//0
	}

	return -1;
}

void CCommonGeneral::GetAllPrintSetup(void)
{
	GetInitGameParam(&m_mustAllPrintFlag,"mustAllPrintFlag");
}


BOOL CCommonGeneral::CheckMiniGame(void)
{
	if (m_miniGameFlag == 0) return FALSE;
	return m_game->CheckMiniGame(m_classNumber);
}


void CCommonGeneral::SetFinalExitRoutine(void)
{
	m_finalExitFlag = TRUE;
}

int CCommonGeneral::GeneralFinalExitRoutine(void)
{

	if (m_finalExitFlag)
	{
		m_game->SetBackScriptMode(FALSE);

		ParentFinalExitRoutine();
		FinalExitRoutine();
		m_finalExitFlag = FALSE;
		return 0;
	}
	return -1;
}
void CCommonGeneral::GetKeyMoveSetup(int tateyoko,int updown,int leftRight)
{
	m_keyMoveEnable = 1;
	GetInitGameParam(&m_keyMoveEnable,"keyMoveEnable");

	m_keyMoveCannotSelectOk = 0;
	GetInitGameParam(&m_keyMoveCannotSelectOk,"keyMoveCannotSelectOk");

	m_keyMoveUpDownEnable = updown;
	m_keyMoveLeftRightEnable = leftRight;
	GetInitGameParam(&m_keyMoveUpDownEnable,"keyMoveUpDownEnable");
	GetInitGameParam(&m_keyMoveLeftRightEnable,"keyMoveLeftRightEnable");

	m_keyTateYoko = tateyoko;
	GetInitGameParam(&m_keyTateYoko,"keyMoveTateYoko");
}

void CCommonGeneral::ClearKeyMove(void)
{
	int up = GetAsyncKeyState(VK_UP);
	int down = GetAsyncKeyState(VK_DOWN);
	int left = GetAsyncKeyState(VK_LEFT);
	int right = GetAsyncKeyState(VK_RIGHT);
	int rt = GetAsyncKeyState(VK_RETURN);
	int sp = GetAsyncKeyState(VK_SPACE);
}

int CCommonGeneral::CalcuKeyMove(void)
{
	if (m_keyMoveEnable)
	{
		m_keyActionFlag = FALSE;

		int delta = 0;
		int deltaX = 0;
		int deltaY = 0;


		POINT pt = m_mouseStatus->GetZahyo();
		
		if (m_keyMoveUpDownEnable)
		{
			if (m_game->CheckClickKey(VK_UP))
			{
				delta = -1;
			}
			if (m_game->CheckClickKey(VK_DOWN))
			{
				delta = 1;
			}
			
			if (m_keyTateYoko)
			{
				deltaY = delta;
				delta = 0;
			}
		}

		if (m_keyMoveLeftRightEnable)
		{
			if (m_game->CheckClickKey(VK_LEFT))
			{
				delta = -1;
			}
			if (m_game->CheckClickKey(VK_RIGHT))
			{
				delta = 1;
			}
			if (m_keyTateYoko)
			{
				deltaX = delta;
				delta = 0;
			}
		}



		if ((delta != 0) || (deltaX != 0) || (deltaY != 0))
		{
			BOOL rt = KeyMoveAction(delta,deltaX,deltaY);
			if (rt != -1)
			{
				m_keyActionFlag = TRUE;
				
				if (rt == 0)
				{
					SetCursorToKeyArea(m_lastKeyButton);
				}
			}
		}
	}

	return -1;
}

void CCommonGeneral::PrintGameLayer(void)
{
	if (m_gameDateLayerPrintFlag)
	{
		int year = m_game->GetVarData(m_generalGameYearVarNumber);
		int date = m_game->GetVarData(m_generalGameDateVarNumber);
		int month = date / 100;
		int day = date % 100;
		m_printGameDate->Print(year,month,day);
	}
}

void CCommonGeneral::PrintAnimeLayer(void)
{
	if (m_animeLayerKosuu > 0)
	{
		BOOL dontErase = FALSE;
		if (m_classNumber == PRINTMESSAGE_MODE)
		{
			dontErase = TRUE;
		}

		for (int i=0;i<m_animeLayerKosuu;i++)
		{
			int anime = 1;
			int varNumber = m_printAnimeLayer[i]->GetVarNumber();
			if (varNumber != -1)
			{
				anime = m_game->GetVarData(varNumber);
			}
			m_printAnimeLayer[i]->Print(anime,dontErase);
		}
	}
}

void CCommonGeneral::SetClassNumber(int n)
{
	m_classNumber = n;
#if !defined _TINYAN3DLIB_
	CPicture::SetModeNumberForDebug(m_classNumber);
#endif
}

/*_*/

