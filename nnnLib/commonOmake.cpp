//
// commonOmake.cpp
//



#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\inputStatus.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"
#include "..\nnnUtilLib\menuButtonGroup.h"
#include "..\nnnUtilLib\menuButtonSetup.h"

#include "..\nnnUtilLib\superButtonPicture.h"

#include "..\nnnUtilLib\cgDataControl.h"
#include "..\nnnUtilLib\sceneDataControl.h"

#include "commonMode.h"
#include "commonSystemSoundName.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonOmake.h"





#include "..\nnnUtilLib\commonGameVersion.h"





char CCommonOmake::m_defaultBGFileName[] = "title_bg2";
char CCommonOmake::m_defaultButtonFileName[] = "ta_title_bt2";
char CCommonOmake::m_defaultAllOnDialogFileName[] = "ta_warning";

char CCommonOmake::m_buttonName[][32]=
{
	"allOnDialogOk","allOnDialogCancel",
};

CCommonOmake::CCommonOmake(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(OMAKE_MODE);
//	m_classNumber = OMAKE_MODE;
	LoadSetupFile("omake",256);

	m_cgDataControl = m_game->GetCGDataControl();
	m_sceneDataControl = m_game->GetSceneDataControl();

	m_basicButtonKosuu = 4;
	GetInitGameParam(&m_basicButtonKosuu,"basicButtonNumber");

	m_menuButtonSetup = new CMenuButtonSetup(m_setup,m_basicButtonKosuu);

	GetBackExecSetup();
	GetAllPrintSetup();

	GetInitGameParam(&m_miniGameFlag,"miniGameFlag");
	if (m_miniGameFlag)
	{
		m_mustAllPrintFlag = 1;
	}

	m_menuStartWaitTime = 0;
	m_menuStartEffectTime = 0;
	m_menuStartEffectType = 0;

	GetInitGameParam(&m_menuStartWaitTime,"menuStartWaitTime");
	GetInitGameParam(&m_menuStartEffectTime,"menuStartEffectTime");
	GetInitGameParam(&m_menuStartEffectType,"menuStartEffectType");

	m_menuStartDeltaX = 0;
	m_menuStartDeltaY = 0;
	GetInitGameParam(&m_menuStartDeltaX,"menuStartDeltaX");
	GetInitGameParam(&m_menuStartDeltaY,"menuStartDeltaY");



	m_extModeKosuu = m_menuButtonSetup->GetExtModeKosuu();
	m_basicButtonKosuu = m_menuButtonSetup->GetBasicButtonKosuu();
	m_extButtonKosuu = m_menuButtonSetup->GetExtButtonKosuu();


//	m_useSpecialButtonFlag = 0;
//	GetInitGameParam(&m_useSpecialButtonFlag,"useSpecialButtonFlag");



	m_extModeCheckVar = -1;
	m_extModeReturnVar = -1;

	if (m_extModeKosuu > 0)
	{
		LPSTR name = m_menuButtonSetup->GetExtModeCheckVarName();
		if (name != NULL)
		{
			m_extModeCheckVar = m_game->GetVarNumber(name);
		}

		name = m_menuButtonSetup->GetExtModeReturnVarName();
		if (name != NULL)
		{
			m_extModeReturnVar = m_game->GetVarNumber(name);
		}
	}


	m_autoCGCharaFlag = 0;
	m_autoSceneCharaFlag = 0;
	GetInitGameParam(&m_autoCGCharaFlag,"autoCGCharaFlag");
	GetInitGameParam(&m_autoSceneCharaFlag,"autoSceneCharaFlag");



	int i = 0;
	for (i=0;i<4;i++)
	{
		m_existFlag[i] = 1;
	}
	m_existFlag[4] = 0;


	GetInitGameParam(&m_existFlag[0],"cgModeExistFlag");
	GetInitGameParam(&m_existFlag[1],"sceneModeExistFlag");
	GetInitGameParam(&m_existFlag[2],"bgmModeExistFlag");
	GetInitGameParam(&m_existFlag[4], "movieModeExistFlag");


	if (m_backScriptFlag)
	{
		m_menu2 = new CMenuButtonGroup(m_menuButtonSetup);
	}
	else
	{
		m_menu2 = new CMenuButtonGroup(m_menuButtonSetup,m_commonBG);
	}

	int superStart = 3;
	if (m_game->GetMiniGameAreaButtomMode())
	{
		superStart += m_game->GetMiniGameCheckKosuu();
	}

	for (i=0;i<m_basicButtonKosuu + m_extButtonKosuu;i++)
	{
		m_menu2->SetPicture(i,CSuperButtonPicture::GetPicture(superStart+i));
	}

	superStart += m_basicButtonKosuu + m_extButtonKosuu;

	m_superMode = m_menu2->GetSuperMode();
	m_menu2->SetCancelButton(3);

	m_filenameBG = m_defaultBGFileName;
	GetInitGameString(&m_filenameBG,"filenameBG");

	m_modeBGMNumber = 1;
	m_modeBGMMustRestartFlag = 1;

	m_allOnWarningPrintFlag = 0;
	m_allOnButtonUseFlag = 0;
	m_allOnButtonFlag = 0;
	m_allOnButtonCheckVar = -1;
	m_allOnDialogButton = NULL;
	m_allOnButton = NULL;
	m_allOnType = 0;
	
	if (CCommonGameVersion::CheckAllOnOk())
	{
		GetInitGameParam(&m_allOnButtonUseFlag,"allOnButtonUseFlag");	//dummy for my debug
	}


	if (m_allOnButtonUseFlag)
	{
		GetInitGameParam(&m_allOnType,"allOnType");

		m_allOnButton = new CCommonButton(m_setup,"allOnButton");
		m_allOnButton->SetPicture(CSuperButtonPicture::GetPicture(superStart));
		superStart++;


		LPSTR varName = NULL;
		if (GetInitGameString(&varName,"allOnCheckVar"))
		{
			if (varName != NULL)
			{
				m_allOnButtonCheckVar = m_game->GetVarNumber(varName);
			}
		}

		GetInitGameParam(&m_allOnWarningPrintFlag,"allOnWarningPrintFlag");


		if (m_allOnWarningPrintFlag)
		{
			m_allOnDialogFileName = m_defaultAllOnDialogFileName;
			GetInitGameString(&m_allOnDialogFileName,"fileNameAllOnDialog");

		//make button
			m_allOnDialogSizeX = 340;
			m_allOnDialogSizeY = 145;
			m_allOnDialogX = 236;
			m_allOnDialogY = 160;

			GetInitGameParam(&m_allOnDialogX,"allOnDialogX");
			GetInitGameParam(&m_allOnDialogY,"allOnDialogY");
			GetInitGameParam(&m_allOnDialogSizeX,"allOnDialogSizeX");
			GetInitGameParam(&m_allOnDialogSizeY,"allOnDialogSizeY");


			char* names[2];
			names[0] = m_buttonName[0];
			names[1] = m_buttonName[1];

			m_allOnDialogButton = new CCommonButtonGroup(m_setup,2,NULL,NULL,names);
		//change zahyo
			for (int i=0;i<2;i++)
			{
				POINT pt = m_allOnDialogButton->GetZahyo(i);
				pt.x += m_allOnDialogX;
				pt.y += m_allOnDialogY;
				m_allOnDialogButton->SetZahyo(i,pt);

				m_allOnDialogButton->SetPicture(i,CSuperButtonPicture::GetPicture(superStart+i));
			}
			m_allOnDialogButton->SetCancelButton(1);
		}
	}
//	m_miniGameAreaKosuu = 0;
//	GetInitGameParam(&m_miniGameAreaKosuu,"miniGame");
//	m_miniGameArea = NULL;
/*
	if (m_miniGameAreaKosuu>0)
	{
		m_miniGameArea = new RECT[m_miniGameAreaKosuu];

		int screenSizeX = CMyGraphics::GetScreenSizeX();
		int screenSizeY = CMyGraphics::GetScreenSizeY();

		for (i=0;i<m_miniGameAreaKosuu;i++)
		{
			int miniX = rand() % (screenSizeX-8);
			int miniY = rand() % (screenSizeY-8);
			int miniSizeX = 8;
			int miniSizeY = 8;

			char names[256];
			
			sprintf(names,"miniGameCheckX%d",i+1);
			GetInitGameParam(&miniX,names);
			sprintf(names,"miniGameCheckY%d",i+1);
			GetInitGameParam(&miniY,names);
			sprintf(names,"miniGameCheckSizeX%d",i+1);
			GetInitGameParam(&miniSizeX,names);
			sprintf(names,"miniGameCheckSizeY%d",i+1);
			GetInitGameParam(&miniSizeY,names);

			SetRect(&m_miniGameArea[i],miniX,miniY,miniSizeX,miniSizeY);
		}
	}

	m_miniGameCheckVar = -1;
	LPSTR varName = NULL;
	if (GetInitGameString(&varName,"miniGameCheckVarName"))
	{
		if (varName != NULL)
		{
			m_miniGameCheckVar = m_game->GetVarNumber(varName);
		}
	}
*/

//	GetInitGameParam(&m_miniGameFlag,"miniGameFlag");


	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();

//	m_noMidiFlag = m_game->CheckNoMidi();




/*
	m_menuPrintX = 32;
	m_menuPrintY = 32;
	m_menuSizeX = 164;
	m_menuSizeY = 36;
	m_menuNextX = 0;
	m_menuNextY = 0;

	m_menuKosuuX = 1;
	m_menuKosuuY = 4;

	m_filenameBG = m_defaultBGFileName;
	m_filenameButton = m_defaultButtonFileName;


	GetInitGameParam(&m_menuKosuuX,"menuNumberX");
	GetInitGameParam(&m_menuKosuuX,"menuNumberY");

	GetInitGameParam(&m_menuPrintX,"menuPrintX");
	GetInitGameParam(&m_menuPrintY,"menuPrintY");
	GetInitGameParam(&m_menuSizeX,"menuSizeX");
	GetInitGameParam(&m_menuSizeY,"menuSizeY");

	if (m_menuKosuuX == 0) m_menuNextX = m_menuSizeX;
	if (m_menuKosuuY == 0) m_menuNextY = m_menuSizeY;

	GetInitGameParam(&m_menuNextX,"menuNextX");
	GetInitGameParam(&m_menuNextY,"menuNextY");

	m_autoCGCharaFlag = 0;
	m_autoSceneCharaFlag = 0;
	GetInitGameParam(&m_autoCGCharaFlag,"autoCGCharaFlag");
	GetInitGameParam(&m_autoSceneCharaFlag,"autoSceneCharaFlag");


	GetInitGameString(&m_filenameBG,"filenameBG");
	GetInitGameString(&m_filenameButton,"filenameButton");

	for (int i=0;i<4;i++)
	{
		m_existFlag[i] = 1;
	}

	GetInitGameParam(&m_existFlag[0],"cgModeExistFlag");
	GetInitGameParam(&m_existFlag[1],"sceneModeExistFlag");
	GetInitGameParam(&m_existFlag[2],"bgmModeExistFlag");


	m_menu = new CMyButtonGroup(4);
	m_menu->CreateButtonGroup(m_commonParts,m_menuPrintX,m_menuPrintY, m_menuNextX,m_menuNextY, m_menuSizeX,m_menuSizeY, TRUE, m_commonBG, FALSE,-1);

	m_menu->SetCancelButton(3);

	for (i=0;i<3;i++)
	{
		if (m_existFlag[i] == 0)
		{
			m_menu->SetExist(i,FALSE);
		}
	}

//	m_modeBGMNumber = COMMONBGM_TITLE;
	GetBGMSetup();
	GetFadeInOutSetup();
	GetBackExecSetup();
	GetEnterExitVoiceFileName();
	*/



}


CCommonOmake::~CCommonOmake()
{
	End();
}


void CCommonOmake::End(void)
{
	ENDDELETECLASS(m_allOnDialogButton);
	ENDDELETECLASS(m_allOnButton);

//	DELETEARRAY(m_miniGameArea);
	ENDDELETECLASS(m_menu2);
	ENDDELETECLASS(m_menuButtonSetup);

//	ENDDELETECLASS(m_menu);
}

int CCommonOmake::Init(void)
{
	m_menuStartCount = 0;

	m_game->SetDefaultFrameRate();

	m_extMode = 0;
	if (m_extModeKosuu > 0)
	{
		if (m_extModeCheckVar != -1)
		{
			m_extMode = m_game->GetVarData(m_extModeCheckVar);
		}
	}

	m_menu2->SetExtMode(m_extMode);



	m_game->ClearF5();
	m_game->SetOpeningMode(FALSE);

	LoadBackBG();

//	m_menu2->Init();

	int i = 0;
	for (i=0;i<5;i++)
	{
		if (i != 3)
		{
			if (m_existFlag[i] == 0)
			{
				m_menu2->SetExist(i, FALSE);
			}
		}
	}

	m_menu2->Init();

	//load pic
	for (i=0;i<m_basicButtonKosuu+m_extButtonKosuu;i++)
	{
		CPicture* lpPic = m_menu2->GetPicture(i,m_extMode);
		LPSTR name = m_menu2->GetFileName(i,m_extMode);
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}

//	m_miniGameOkKosuu = m_miniGameAreaKosuu;
//	if (m_miniGameCheckVar != -1)
//	{
//		m_miniGameOkKosuu = m_game->GetVarData(m_miniGameCheckVar);
//		if (m_miniGameOkKosuu > m_miniGameAreaKosuu) m_miniGameOkKosuu = m_miniGameAreaKosuu;
//	}

//	m_menu2->SetEnable(2);
//	if (m_noMidiFlag)
//	{
//		if (m_game->GetSystemParam(NNNPARAM_BGMMODE) == 0)
//		{
//			m_menu2->SetEnable(2,FALSE);
//		}
//	}

	if (GetStartWaitMode() == 0)
	{
		m_game->InitMiniGameButton(OMAKE_MODE);
	}

	m_allOnWarningMode = 0;


	m_allOnButtonFlag = 0;
	if (m_allOnButtonUseFlag)
	{
		if (m_allOnButtonCheckVar != -1)
		{
			if (m_game->GetVarData(m_allOnButtonCheckVar) != 0)
			{
				m_allOnButtonFlag = 1;
			}
		}
		else
		{
			m_allOnButtonFlag = 1;
		}
	}

	if (m_allOnButtonFlag)
	{
		//load pic
		char filename[256];
		wsprintf(filename,"sys\\%s",m_allOnButton->GetFileName());
		(m_allOnButton->GetPicture())->LoadDWQ(filename);

		if (m_allOnWarningPrintFlag)
		{
			char filename[256];
			wsprintf(filename,"sys\\%s",m_allOnDialogFileName);
			m_commonParts->LoadDWQ(filename);

			for (i=0;i<2;i++)
			{
				CPicture* lpPic = m_allOnDialogButton->GetPicture(i);
				LPSTR name = m_allOnDialogButton->GetFileName(i);
				char filename[256];
				wsprintf(filename,"sys\\%s",name);
				lpPic->LoadDWQ(filename);
			}
		}
	}

	m_game->StopVoice();

	return -1;
}


int CCommonOmake::Calcu(void)
{
	if (m_allOnWarningMode == 1)
	{
		CAreaControl::SetNextAllPrint();
		return CalcuAllOnWarning();
	}




//	if (m_backScriptFlag)
//	{
//		m_game->CalcuBackScript();
//	}
	
/*
	m_miniGameAreaNumber = -1;
	if (m_miniGameAreaKosuu > 0)
	{
		if (m_miniGameOkKosuu > 0)
		{
			POINT pt = m_mouseStatus->GetZahyo();
			m_miniGameAreaNumber = CheckInMiniGameArea(pt);

			if (m_miniGameAreaNumber != -1)
			{
				m_game->SetOnMiniGameArea();
				if (m_mouseStatus->CheckClick())
				{
					m_game->SetMiniGameNumber(m_miniGameAreaNumber);
					return MINIGAME_MODE;
				}
			}
		}
	}
*/


	int startMode = GetStartWaitMode();
	if (startMode != 0)
	{
		m_menuStartCount++;
		if (m_menuStartCount >= m_menuStartWaitTime + m_menuStartEffectTime)
		{
			EndStartWaitMode();
		}
		else
		{
			if (m_mouseStatus->CheckClick()) EndStartWaitMode();
			if (m_mouseStatus->CheckClick(1)) EndStartWaitMode();
		}
	}
	else
	{
		int rt = m_menu2->Calcu(m_inputStatus);


		int st = CCommonButton::GetButtonStatus(rt);
		int requestSoundFlag = CCommonButton::CheckRequestSound(rt);
		int sound = 0;
		int voice = 0;

		if (requestSoundFlag)
		{
			sound = CCommonButton::GetButtonSound(rt);
			voice = CCommonButton::GetButtonVoice(rt);

		}
		int rt2 = NNNBUTTON_NOTHING;
		if (m_allOnButtonFlag)
		{
			rt2 = m_allOnButton->Calcu(m_inputStatus);
			if (CCommonButton::CheckRequestSound(rt2))
			{
				requestSoundFlag = 1;
				sound = CCommonButton::GetButtonSound(rt2);
				voice = CCommonButton::GetButtonVoice(rt);
			}
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
				m_game->PlaySystemSound(sound - 1);
			}
			if (voice > 0)
			{
				m_game->PlayButtonVoice(voice);
			}
		}

		if ((st == NNNBUTTON_NUMBER) && (existDataFlag))
		{
			m_game->SetBackScriptMode(FALSE);
			m_game->SetDefaultFrameRate();

			if (nm == 0)
			{
	//			m_game->SetSceneMode();

				if (m_autoCGCharaFlag)
				{
					if (m_cgDataControl != NULL)
					{
						m_cgDataControl->SetCGCharaNumber(0);
					}
					m_game->SetCommonBackMode(SELECTCG_MODE,OMAKE_MODE);
					return ReturnFadeOut(SELECTCG_MODE);
				}
				else
				{
					return ReturnFadeOut(SELECTCGCHARA_MODE);
				}
			}


			if (nm == 1)
			{
//return ReturnFadeOut(SELECTMOVIE_MODE);


	//			m_game->SetSceneMode();
				
				if (m_autoSceneCharaFlag)
				{
//					m_game->SetSceneCharaNumber(0);
					if (m_sceneDataControl != NULL)
					{
						m_sceneDataControl->SetSceneCharaNumber(0);
					}
					m_game->SetCommonBackMode(SELECTSCENE_MODE,OMAKE_MODE);
					return ReturnFadeOut(SELECTSCENE_MODE);
				}
				else
				{
					return ReturnFadeOut(SELECTSCENECHARA_MODE);
				}


	//			return SELECTSCENECHARA_MODE;
			}

			if (nm == 2)
			{
				return ReturnFadeOut(LISTENBGM_MODE);
	//			return LISTENBGM_MODE;
			}

			if (nm == 3)
			{
				return ReturnFadeOut(TITLE_MODE);
	//			return TITLE_MODE;
			}

			if (m_basicButtonKosuu >= 5)
			{
				if (nm == 4)
				{
					return ReturnFadeOut(SELECTMOVIE_MODE);
					//			return TITLE_MODE;
				}
			}

			//通常追加ボタン
			if (nm < m_basicButtonKosuu)
			{
				//特殊モードへのいこうかスクリプト実行かをチェック
				int nextMode = m_menuButtonSetup->GetBasicSpecialMode(nm);

				int varNumber = m_extModeReturnVar;
				m_game->SetSceneMode(FALSE);
//				m_game->StartLog();

				if (nextMode > 0)
				{
					m_game->SetCommonBackMode(nextMode,OMAKE_MODE);
					return ReturnFadeOut(nextMode);
				}
				else
				{
					m_game->InitNewGame(FALSE,FALSE,varNumber,-(nm - 4 + 1));
					m_game->SetYoyaku();
					return -1;
				}

			}

			//拡張ボタン
			if (nm >= m_basicButtonKosuu)
			{
				//特殊モードへのいこうかスクリプト実行かをチェック
				int nextMode = m_menuButtonSetup->GetExtSpecialMode(nm - m_basicButtonKosuu);
				int varNumber = m_extModeReturnVar;
				m_game->SetSceneMode(FALSE);
//				m_game->StartLog();

				if (nextMode > 0)
				{
					m_game->SetCommonBackMode(nextMode,OMAKE_MODE);
					return ReturnFadeOut(nextMode);
				}
				else
				{
					CreateExitScreen();
					m_game->InitNewGame(FALSE,FALSE,varNumber,nm - m_basicButtonKosuu + 1);
					m_game->SetYoyaku();
					return -1;
				}
			}


			return -1;
		}

		if (m_allOnButtonFlag)
		{
			int st2 = CCommonButton::GetButtonStatus(rt2);

			int existDataFlag2 = CCommonButton::CheckExistData(rt2);
			int nm2 = -1;
			if (existDataFlag2)
			{
				nm2 = CCommonButton::GetButtonData(rt2);
			}

			if ((st2 == NNNBUTTON_NUMBER) && (existDataFlag2))
			{
				m_allOnWarningMode = 1;
				m_allOnDialogButton->Init();
			}
		}
	}

	return -1;
}


int CCommonOmake::Print(void)
{
	if (m_allOnWarningMode)
	{
		CAreaControl::SetNextAllPrint();
	}

	PrintBackScriptOrBG();
	BOOL b = CAreaControl::CheckAllPrintMode();

	int startMode = GetStartWaitMode();
	if (startMode == 0)
	{
		m_menu2->Print(b);
		if (m_allOnButtonFlag)
		{
			m_allOnButton->Print(b);

			if (m_allOnWarningPrintFlag)
			{
				if (m_allOnWarningMode == 1)
				{
					m_commonParts->Blt(m_allOnDialogX,m_allOnDialogY,0,0,m_allOnDialogSizeX,m_allOnDialogSizeY,TRUE);
					m_allOnDialogButton->Print(b);
				}
			}
		}
	}
	else if (startMode == 2)
	{
		//effect
		int count = m_menuStartCount - m_menuStartWaitTime;
		int countMax = m_menuStartEffectTime;
		int type = m_menuStartEffectType;	//move,半透明,etc
		POINT pt;
		pt.x = m_menuStartDeltaX;
		pt.y = m_menuStartDeltaY;
		m_menu2->AppearPrint(count,countMax,type,pt);
	}

	return -1;
}



void CCommonOmake::ReCreateExitScreen(void)
{
	Print();
}


void CCommonOmake::CreateStartScreen(void)
{
	//menu setup?

	//script exec?

//	m_menu2->SetEnable(2);
//	if (m_noMidiFlag)
//	{
//		if (m_game->GetSystemParam(NNNPARAM_BGMMODE) == 0)
//		{
//			m_menu2->SetEnable(2,FALSE);
//		}
//	}

	m_menu2->Calcu(NULL);

	Print();
}

int CCommonOmake::GetStartWaitMode(void)
{
	if (m_menuStartCount < m_menuStartWaitTime) return 1;
	if (m_menuStartCount < m_menuStartWaitTime+m_menuStartEffectTime) return 2;

	return 0;
}

void CCommonOmake::EndStartWaitMode(void)
{
	m_menuStartCount = m_menuStartWaitTime+m_menuStartEffectTime;
	m_game->InitMiniGameButton(OMAKE_MODE);
}


int CCommonOmake::CalcuAllOnWarning(void)
{
	int rt = m_allOnDialogButton->Calcu(m_inputStatus);
	if (rt == NNNBUTTON_NOTHING) return -1;

	int nm = ProcessButtonGroup(rt);
	
	if (nm == 0)
	{
		//allon!!@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


		m_game->AllOnOmakeFlag(m_allOnType);

//		SaveNowData();

//		m_warningFlag = 0;
//		m_clickingFlag = FALSE;

//		InitPageButton();

//		m_updownBack->Init();
//		InitAnime();
		CAreaControl::SetNextAllPrint();
		m_allOnWarningMode = 0;
		m_menu2->Init();
		m_allOnButton->Init();

	}
	else if (nm == 1)
	{
		m_allOnWarningMode = 0;
		m_menu2->Init();
		m_allOnButton->Init();

//		InitPageButton();

//		m_updownBack->Init();
//		InitAnime();
		CAreaControl::SetNextAllPrint();
	}

	return -1;
}

/*
int CCommonOmake::CheckInMiniGameArea(POINT pt)
{
	int x = pt.x;
	int y = pt.y;

//	for (int i=0;i<m_miniGameAreaKosuu;i++)
	for (int i=0;i<m_miniGameOkKosuu;i++)
	{
		RECT rc = *(m_miniGameArea+i);
		int cx = x - rc.left;
		int cy = y - rc.top;
		int sx = rc.right;
		int sy = rc.bottom;
		if ((cx>=0) && (cx<sx) && (cy>=0) && (cy<sy))
		{
			return i;
		}
	}

	return -1;
}

*/


/*_*/

