//
// commonTitle.cpp
//



#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\allGeo.h"

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\inputStatus.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"

#include "..\nnnUtilLib\menuButtonGroup.h"
#include "..\nnnUtilLib\menuButtonSetup.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\autoSelectControl.h"

#include "..\nnnUtilLib\commonGameVersion.h"
#include "commonMode.h"
#include "commonSystemSoundName.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\superButtonPicture.h"


#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonTitle.h"





//#include "commonGameVersion.h"





char CCommonTitle::m_defaultBGFileName[] = "title_bg";
char CCommonTitle::m_defaultHTML[] = "http://www2s.biglobe.ne.jp/~tinyan/index.htm";


//char CCommonTitle::m_defaultButtonFileName[] = "ta_title_bt1";

//char CCommonTitle::m_defaultSpecialButtonFileNameTag[] = "ta_title_bt";

CCommonTitle::CCommonTitle(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(TITLE_MODE);
//	m_classNumber = TITLE_MODE;
	LoadSetupFile("title",64);

	m_basicButtonKosuu = 5;
	GetInitGameParam(&m_basicButtonKosuu,"basicButtonNumber");
	m_menuButtonSetup = new CMenuButtonSetup(m_setup,m_basicButtonKosuu);

	GetBackExecSetup();
	GetAllPrintSetup();

	GetInitGameParam(&m_miniGameFlag,"miniGameFlag");
	if (m_miniGameFlag)
	{
		m_mustAllPrintFlag = 1;
	}


	m_noSaveDataToMaskMenu = 0;
	GetInitGameParam(&m_noSaveDataToMaskMenu, "NoSaveDataToMaskMenu");


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


	m_autoSelectControl = m_game->GetAutoSelectControl();

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

	if (m_backScriptFlag)
	{
		m_menu2 = new CMenuButtonGroup(m_menuButtonSetup);
	}
	else
	{
		m_menu2 = new CMenuButtonGroup(m_menuButtonSetup,m_commonBG);
	}
	m_superMode = m_menu2->GetSuperMode();
//	m_menu2->SetupButtonStatus();

	int superStart = 3;
	if (m_game->GetMiniGameAreaButtomMode())
	{
		superStart += m_game->GetMiniGameCheckKosuu();
	}

	for (int i=0;i<m_basicButtonKosuu + m_extButtonKosuu;i++)
	{
		m_menu2->SetPicture(i,CSuperButtonPicture::GetPicture(superStart+i));
	}

	superStart += m_basicButtonKosuu + m_extButtonKosuu;
	m_htmlButtonEnable = 0;
	GetInitGameParam(&m_htmlButtonEnable, "EnableHtmlButton");
	m_htmlButton = nullptr;
	m_HTMLaddr = m_defaultHTML;
	if (m_htmlButtonEnable > 0)
	{
		m_htmlButton = new CCommonButton(m_setup, "HTML");
		m_htmlButton->SetPicture(CSuperButtonPicture::GetPicture(superStart));
		GetInitGameString(&m_HTMLaddr, "HTMLaddr");
		superStart++;
	}

	m_lastLoadButtonEnable = 0;
	GetInitGameParam(&m_lastLoadButtonEnable, "EnableLastLoadButton");
	m_lastLoadButton = nullptr;
	if (m_lastLoadButtonEnable > 0)
	{
		m_lastLoadButton = new CCommonButton(m_setup, "LastLoad");
		m_lastLoadButton->SetPicture(CSuperButtonPicture::GetPicture(superStart));
		superStart++;
	}


	m_htmlButtonWithMenu = 0;
	GetInitGameParam(&m_htmlButtonWithMenu,"htmlButtonWithMenu");
	m_lastLoadButtonWithMenu = 0;
	GetInitGameParam(&m_lastLoadButtonWithMenu, "lastLoadButtonWithMenu");


	m_autoRestartTime = 0;
	GetInitGameParam(&m_autoRestartTime,"autoRestartTime");

	m_filenameBG = m_defaultBGFileName;
	GetInitGameString(&m_filenameBG,"filenameBG");

	m_scriptEndIsModeEnd = 0;
	GetInitGameParam(&m_scriptEndIsModeEnd,"scriptEndIsModeEnd");


	m_restartNextMode = NOTHING_MODE;
	GetModeNumberBySetup("restartNextMode",&m_restartNextMode);


	m_disableLoadFlag = FALSE;
//	if (m_game->CheckLoadCommandOk() == FALSE) m_disableLoadFlag = TRUE;
	if (CCommonGameVersion::CheckTaikenOrNetVersion())
	{
		if (CCommonGameVersion::CheckLoadCommandOk() == FALSE)
		{
			m_disableLoadFlag = TRUE;
		}
	}

	m_disableOmakeFlag = FALSE;
//	if (m_game->CheckOmakeOk() == FALSE) m_disableOmakeFlag = TRUE;
	if (CCommonGameVersion::CheckTaikenOrNetVersion())
	{
		if (CCommonGameVersion::CheckOmakeOk() == FALSE)
		{
			m_disableOmakeFlag = TRUE;
		}
	}


	m_modeBGMNumber = 1;
	m_modeBGMMustRestartFlag = 1;
	m_newGameFlag = FALSE;


	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
}


CCommonTitle::~CCommonTitle()
{
	End();
}


void CCommonTitle::End(void)
{
	ENDDELETECLASS(m_lastLoadButton);
	ENDDELETECLASS(m_htmlButton);
	ENDDELETECLASS(m_menu2);

//	DELETEARRAY(m_printZahyoY);
//	DELETEARRAY(m_printZahyoX);
//	DELETEARRAY(m_addButtonExeType);
//	DELETEARRAY(m_addButtonVarNumber);
//	ENDDELETECLASS(m_menu);
	ENDDELETECLASS(m_menuButtonSetup);
}

int CCommonTitle::Init(void)
{
	m_newGameFlag = FALSE;
	m_lastLoadFlag = false;

	m_game->SetupNameDefault();
	m_game->ClearBackLog();
	m_game->SetLayerOff();

	m_menuStartCount = 0;
	m_game->LaunchCountUp();
	m_game->StopScriptSoundAndVoice();

	m_game->ClearWork();

	for (int i=100;i<200;i++)
	{
		m_game->SetVarData(i,0);
	}

	int varType = m_game->GetVarType();
	if (varType == 0)
	{
		for (int i = 300; i < 1000; i++)
		{
			m_game->SetVarData(i, 0);
		}
	}
	else
	{
		for (int i = 1200; i < 2200; i++)
		{
			m_game->SetVarData(i, 0);
		}
	}

	m_extMode = 0;
	if (m_extModeKosuu > 0)
	{
		if (m_extModeCheckVar != -1)
		{
			m_extMode = m_game->GetVarData(m_extModeCheckVar);
		}
	}
	m_menu2->SetExtMode(m_extMode);

	//個別exist on/off 拡張ボタン







	m_autoRestartCount = 0;
	m_game->SetDefaultFrameRate();

	m_autoDebugWait = m_game->GetAutoDebugWait();


	if (m_backScriptFlag == FALSE)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s",m_filenameBG);
		m_commonBG->LoadDWQ(filename);
	}


	//load all menu pic
//	m_menu2->SetAllButtonZahyo(m_extMode);
	for (int i=0;i<m_basicButtonKosuu+m_extButtonKosuu;i++)
	{
		CPicture* lpPic = m_menu2->GetPicture(i,m_extMode);
		LPSTR name = m_menu2->GetFileName(i,m_extMode);
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}

	m_menu2->Init();

	if (m_htmlButtonEnable > 0)
	{
		CPicture* lpPic = m_htmlButton->GetPicture();
		LPSTR name = m_htmlButton->GetFileName();
		char filename[256];
		wsprintf(filename, "sys\\%s", name);
		lpPic->LoadDWQ(filename);
		m_htmlButton->Init();
		SetHTMPButtonMode();
	}

	if (m_lastLoadButtonEnable > 0)
	{
		CPicture* lpPic = m_lastLoadButton->GetPicture();
		LPSTR name = m_lastLoadButton->GetFileName();
		char filename[256];
		wsprintf(filename, "sys\\%s", name);
		lpPic->LoadDWQ(filename);
		m_lastLoadButton->Init();
		SetLastLoadButtonMode();
	}



//	体験版、ネット版でload omakeのマスク
	if (m_disableLoadFlag)
	{
		m_menu2->SetEnable(1,FALSE);	//disabel load
	}


//Dataがない場合Loadをマスク
	if (m_noSaveDataToMaskMenu != 0)
	{
		bool bCannotLoad = true;
		if (m_game->CheckExistSaveData())
		{
			bCannotLoad = false;
		}
		if (bCannotLoad)
		{
			m_menu2->SetEnable(1, FALSE);	//disabel load
		}
		else
		{
			m_menu2->SetEnable(1, TRUE);
		}
	}



	if (m_disableOmakeFlag)
	{
		m_menu2->SetEnable(3,FALSE);	//disable omake
	}

	m_menu2->Init();

	//start appear によっては、ここで
	if (GetStartWaitMode() == 0)
	{
		m_game->InitMiniGameButton(TITLE_MODE);
	}

	m_game->StopVoice();

	return -1;
}


int CCommonTitle::Calcu(void)
{
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
			ProcessButtonGroup(rt);
//			if (sound > 0)
//			{
//				m_game->PlaySystemSound(sound - 1);
//			}
		}


		if (m_game->GetAutoDebugMode())
		{
			BOOL autoDebugOk = TRUE;

			if (m_autoSelectControl != NULL)
			{
				if (m_autoSelectControl->CheckAllEnd())
				{
					autoDebugOk = FALSE;
				}
			}

			if (autoDebugOk)
			{
				m_autoDebugWait--;
				if (m_autoDebugWait <= 0)
				{
					m_game->SetBackScriptMode(FALSE);
					m_game->SetDefaultFrameRate();
					m_newGameFlag = TRUE;
					m_extScenario = 0;
					return ReturnFadeOut(-1);
				}
			}
		}

		int HTMLrt = NNNBUTTON_NOTHING;
		if (m_htmlButtonEnable > 0)
		{
			HTMLrt = m_htmlButton->Calcu(m_inputStatus);

			int HTMLst = CCommonButton::GetButtonStatus(HTMLrt);
			int HTMLrequestSoundFlag = CCommonButton::CheckRequestSound(HTMLrt);
//			int HTMLsound = 0;
			if (HTMLrequestSoundFlag)
			{
				ProcessCommonButton(HTMLrt);
			//	sound = CCommonButton::GetButtonSound(HTMLrt);
			//	if (sound > 0)
			//	{
			//		m_game->PlaySystemSound(sound - 1);
			//	}
			}
			int HTMLexistDataFlag = CCommonButton::CheckExistData(HTMLrt);
			int HTMLnm = -1;
			if (HTMLexistDataFlag)
			{
				HTMLnm = CCommonButton::GetButtonData(HTMLrt);
			}


			if (HTMLnm >= 0)
			{
				m_htmlButton->Init();

				//ShellExecute(m_game->GetGameHWND(), "open", "http://www2s.biglobe.ne.jp/~tinyan/index.htm");
				
				//once?

				ShellExecute(nullptr, "open",m_HTMLaddr,NULL,NULL,SW_SHOW);

			}
		}

		int lastLoadrt = NNNBUTTON_NOTHING;
		if (m_lastLoadButtonEnable > 0)
		{
			lastLoadrt = m_lastLoadButton->Calcu(m_inputStatus);

			int lastLoadst = CCommonButton::GetButtonStatus(lastLoadrt);
			int lastLoadrequestSoundFlag = CCommonButton::CheckRequestSound(lastLoadrt);
//			int lastLoadsound = 0;
			if (lastLoadrequestSoundFlag)
			{
				ProcessCommonButton(lastLoadrt);
//				sound = CCommonButton::GetButtonSound(lastLoadrt);
//				if (sound > 0)
//				{
//					m_game->PlaySystemSound(sound - 1);
//				}
			}
			int lastLoadexistDataFlag = CCommonButton::CheckExistData(lastLoadrt);
			int lastLoadnm = -1;
			if (lastLoadexistDataFlag)
			{
				lastLoadnm = CCommonButton::GetButtonData(lastLoadrt);
			}

			if (lastLoadnm >= 0)
			{

			//	m_game->SetBackScriptMode(FALSE);
			//	m_game->SetDefaultFrameRate();

				m_lastLoadFlag = TRUE;
				return ReturnFadeOut(-1);
			}
		}


		if ((st == NNNBUTTON_NUMBER) && (existDataFlag))
		{
			m_game->SetBackScriptMode(FALSE);
			m_game->SetDefaultFrameRate();

			if (nm == 0)
			{
				m_newGameFlag = TRUE;
				m_extScenario = 0;
				return ReturnFadeOut(-1);
			}

			if (nm == 1)
			{
				m_game->TaihiAllEffect();
				m_game->SetSceneMode(FALSE);
				m_game->SetCommonBackMode(LOAD_MODE,TITLE_MODE);
				m_newGameFlag = FALSE;
				return ReturnFadeOut(LOAD_MODE);
			}

			if (nm == 2)
			{
				m_game->TaihiAllEffect();
				m_game->SetCommonBackMode(CONFIG_MODE,TITLE_MODE);
				m_newGameFlag = FALSE;
				return ReturnFadeOut(CONFIG_MODE);
			}

			if (nm == 3)
			{
	//			m_game->SetSceneMode();
				m_newGameFlag = FALSE;
				return ReturnFadeOut(OMAKE_MODE);
			}

			if (nm == 4)
			{
				m_newGameFlag = FALSE;
				m_game->PostCloseMessage();
				return -1;
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
					m_game->SetCommonBackMode(nextMode,TITLE_MODE);
					return ReturnFadeOut(nextMode);
				}
				else
				{
					m_newGameFlag = TRUE;
					m_extScenario = -(nm - 5 + 1);
					return ReturnFadeOut(-1);
				}
			}


			//拡張ボタン
			if (nm >= 5)
			{
				//特殊モードへのいこうかスクリプト実行かをチェック
				int nextMode = m_menuButtonSetup->GetExtSpecialMode(nm - 5);
				int varNumber = m_extModeReturnVar;
				m_game->SetSceneMode(FALSE);
//				m_game->StartLog();

				if (nextMode > 0)
				{
					m_game->SetCommonBackMode(nextMode,TITLE_MODE);
					return ReturnFadeOut(nextMode);
				}
				else
				{
					m_newGameFlag = TRUE;
					m_extScenario = nm - 5 + 1;
					return ReturnFadeOut(-1);

//					m_game->InitNewGame(FALSE,FALSE,varNumber,nm - 5 + 1);
//					m_game->SetYoyaku();
					return -1;
				}
			}

			return -1;
		}
	}


	if (m_autoRestartTime > 0)
	{
		m_autoRestartCount++;
		if (m_autoRestartCount >= m_autoRestartTime)
		{
			return ReturnFadeOut(m_restartNextMode);
		}
	}

	if (m_scriptEndIsModeEnd)
	{
		if (m_backScriptFlag)
		{
			if (m_backScriptEndFlag)
			{
				return ReturnFadeOut(m_restartNextMode);
			}
		}
	}

	return -1;
}


int CCommonTitle::Print(void)
{
	PrintBackScriptOrBG();

	BOOL b = CAreaControl::CheckAllPrintMode();

	int startMode = GetStartWaitMode();
	if (startMode == 0)
	{
		m_menu2->Print(b);
		if (m_htmlButtonEnable > 0)
		{
			m_htmlButton->Print(b);
		}
		if (m_lastLoadButtonEnable > 0)
		{
			m_lastLoadButton->Print(b);
		}
	}
	else if (startMode == 2)
	{
		CAreaControl::SetNextAllPrint();

		//effect
		int count = m_menuStartCount - m_menuStartWaitTime;
		int countMax = m_menuStartEffectTime;
		int type = m_menuStartEffectType;	//move,半透明,etc
		POINT pt;
		pt.x = m_menuStartDeltaX;
		pt.y = m_menuStartDeltaY;
		m_menu2->AppearPrint(count,countMax,type,pt);

		POINT delta;
		delta.x = 0;
		delta.y = 0;

		int ps = (count * 100) / countMax;
		if (ps < 0) ps = 0;
		if (ps > 100) ps = 100;


		if (m_htmlButtonEnable > 0)
		{
			if (m_htmlButtonWithMenu == 0)
			{
				m_htmlButton->Put(delta, ps);
			}
			else
			{
				int mx = m_basicButtonKosuu + m_extButtonKosuu + 1;
				if (m_lastLoadButtonEnable > 0) mx++;
				m_htmlButton->AppearPrint(count, countMax, type,delta,0+ m_basicButtonKosuu + m_extButtonKosuu, mx);
			}
		}

		if (m_lastLoadButtonEnable > 0)
		{
			if (m_lastLoadButtonWithMenu == 0)
			{
				m_lastLoadButton->Put(delta, ps);
			}
			else
			{
				int mx = m_basicButtonKosuu + m_extButtonKosuu + 2;
				int st = 1;
				if (m_lastLoadButtonEnable == 0)
				{
					mx--;
					st--;
				}
				m_lastLoadButton->AppearPrint(count, countMax, type, delta, 0 + m_basicButtonKosuu + m_extButtonKosuu, mx);
			}
		}
	}

//	CAllGeo::BoxFill(100,100,300,300,127,192,64);



	return -1;
}



void CCommonTitle::ReCreateExitScreen(void)
{
	Print();
}


void CCommonTitle::CreateStartScreen(void)
{
	//menu setup?

	//script exec?
	CAreaControl::SetNextAllPrint();
	m_menu2->Calcu(NULL);
	Print();
}


int CCommonTitle::GetStartWaitMode(void)
{
	if (m_menuStartCount < m_menuStartWaitTime) return 1;
	if (m_menuStartCount < m_menuStartWaitTime+m_menuStartEffectTime) return 2;

	return 0;
}

void CCommonTitle::EndStartWaitMode(void)
{
	m_menuStartCount = m_menuStartWaitTime+m_menuStartEffectTime;
	m_game->InitMiniGameButton(TITLE_MODE);
}

void CCommonTitle::FinalExitRoutine(void)
{
	if (m_lastLoadFlag)
	{
//		if (m_createExitScreenFlag)
		{
			CreateExitScreen();
		}

		m_game->SetSceneMode(FALSE);



		int lastSaveDataNumber = m_game->GetLastSelectSaveLoad();

		m_game->ExecSaveData(lastSaveDataNumber);

		m_exitScreen->Put(0, 0, FALSE);
		CAreaControl::SetNextAllPrint();

//		m_game->SetYoyaku();
		m_lastLoadFlag = FALSE;

		return;
	}

	if (m_newGameFlag)
	{
		if (m_createExitScreenFlag)
		{
	//		OutputDebugString("\n[title::finalexit::call createexitscreen]\n");
			CreateExitScreen();
	//		OutputDebugString("\n[title::finalexit::end call createexitscreen]\n");
		}

		m_game->SetSceneMode(FALSE);
//		m_game->StartLog();
		
		if (m_extScenario == 0)
		{
	//		OutputDebugString("\n[title::finalexit::call initnewgame]\n");
			m_game->InitNewGame();
	//		OutputDebugString("\n[title::finalexit::end call initnewgame]\n");
		}
		else
		{
			int varNumber = m_extModeReturnVar;
			m_game->InitNewGame(FALSE,FALSE,varNumber,m_extScenario);
		}
		
		m_game->SetYoyaku();
		m_newGameFlag = FALSE;
	}
}

int CCommonTitle::EndMode(void)
{
	return -1;
}

void CCommonTitle::OnScreenModeChanged(void)
{
	SetHTMPButtonMode();
}

void CCommonTitle::SetHTMPButtonMode(void)
{
	if (m_htmlButtonEnable > 0)
	{
		int md = m_game->GetSystemParam(NNNPARAM_SCREENMODE);
		if (md != 0)
		{
			m_htmlButton->SetEnable(false);
		}
		else
		{
			m_htmlButton->SetEnable(true);
		}
		m_htmlButton->Init();
	}
}

void CCommonTitle::SetLastLoadButtonMode(void)
{
	if (m_lastLoadButtonEnable > 0)
	{
		bool b = false;


		if (m_game->CheckExistLastSaveData())
		{
			b = true;
		}
		if (b)
		{
			m_lastLoadButton->SetEnable();
		}
		else
		{
			m_lastLoadButton->SetEnable(FALSE);
		}

		m_lastLoadButton->Init();
	}
}

/*_*/

