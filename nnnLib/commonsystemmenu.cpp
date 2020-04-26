//
// commonSystemMenu.cpp
//


#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\nnnButtonStatus.h"
#include "commonSystemSoundName.h"

#include "..\\nnnUtilLib\superButtonPicture.h"

#include "..\nnnUtilLib\commonKeyList.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"

#include "..\nnnUtilLib\suuji.h"

#include "..\nnnUtilLib\commonGameVersion.h"

#include "..\nnnUtilLib\menuButtonGroup.h"
#include "..\nnnUtilLib\menuButtonSetup.h"


#include "commonMode.h"
#include "commonSystemParamName.h"

#include "commonGeneral.h"
#include "commonSystemMenu.h"

#include "gameCallBack.h"



int CCommonSystemMenu::m_checkKeyList[]={SAVE_KEY,LOAD_KEY,CONFIG_KEY,WINDOWOFF_KEY,VK_SHIFT,MYUP_KEY,AUTO_KEY,-1,-1,};
//save load config space(window off) shift backlog right_click exitgame



char CCommonSystemMenu::m_defaultDialogFileName[] = "ta_dialog3";
char CCommonSystemMenu::m_defaultBackScreenFileName[] = "bg_sysmenu";

//char CCommonSystemMenu::m_defaultDialogButtonFileName[] = "ta_dialog_bt1";
//char CCommonSystemMenu::m_defaultMenuFileName[] = "ta_menulist";
char CCommonSystemMenu::m_defaultMenuBaseFileName[] = "ta_menulistbase";



char CCommonSystemMenu::m_buttonName[][16]=
{
	"dialogOk","dialogCancel"
};

//save load confog windowoff skip backlog auto cancel exit
int CCommonSystemMenu::m_defaultAccelKey[] = 
{
	'S','L','C',VK_SPACE,VK_SHIFT,VK_UP,'A',-1,-1,
};



CCommonSystemMenu::CCommonSystemMenu(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	int i= 0;

	SetClassNumber(SYSTEMMENU_MODE);
//	m_classNumber = SYSTEMMENU_MODE;
	LoadSetupFile("SystemMenu",128);

	m_mustAllPrintFlag = 1;
	GetAllPrintSetup();


	GetBackExecSetup();

	m_optionKosuu = 9;
	GetInitGameParam(&m_optionKosuu,"optionNumber");

	m_menuButtonSetup = new CMenuButtonSetup(m_setup,m_optionKosuu);

	if (m_backScriptFlag)
	{
		m_menu = new CMenuButtonGroup(m_menuButtonSetup);
	}
	else
	{
		m_menu = new CMenuButtonGroup(m_menuButtonSetup,m_commonBG);
	}

	for (i=0;i<m_optionKosuu;i++)
	{
		m_menu->SetPicture(i,CSuperButtonPicture::GetPicture(5+i));
	}

	m_noSaveDataToMaskMenu = 0;
	GetInitGameParam(&m_noSaveDataToMaskMenu, "NoSaveDataToMaskMenu");


	m_sceneBackFileName = NULL;
	GetInitGameString(&m_sceneBackFileName,"systemMenuSceneBackFileName");

	m_sceneEndFileName = NULL;
	GetInitGameString(&m_sceneEndFileName,"systemMenuSceneEndFileName");

	m_warningPrintFlag = 1;
	GetInitGameParam(&m_warningPrintFlag,"warningPrintFlag");

	m_optionStartPrintType = 1;
	GetInitGameParam(&m_optionStartPrintType,"menuPrintType");

	m_optionStartPrintTime = 20;
	GetInitGameParam(&m_optionStartPrintTime,"menuPrintTime");

	m_optionStartSpeed100 = 10000;
	if (m_optionStartPrintTime > 0)
	{
		if (m_optionStartPrintType > 0)
		{
			m_optionStartSpeed100 = 10000 / m_optionStartPrintTime;
		}
	}


	m_warningMenuPrintFlag = 1;
	GetInitGameParam(&m_warningMenuPrintFlag,"warningMenuPrintFlag");


	m_dialogButton = NULL;
	if (m_warningPrintFlag)
	{
		m_filenameDialog = m_defaultDialogFileName;
		GetInitGameString(&m_filenameDialog,"fileNameDialog");

		//make button
		m_dialogSizeX = 340;
		m_dialogSizeY = 145;
		m_dialogX = 236;
		m_dialogY = 160;

		GetInitGameParam(&m_dialogX,"dialogX");
		GetInitGameParam(&m_dialogY,"dialogY");
		GetInitGameParam(&m_dialogSizeX,"dialogSizeX");
		GetInitGameParam(&m_dialogSizeY,"dialogSizeY");


		char* names[2];
		names[0] = m_buttonName[0];
		names[1] = m_buttonName[1];

		m_dialogButton = new CCommonButtonGroup(m_setup,2,NULL,NULL,names);
		//change zahyo
		for (int i=0;i<2;i++)
		{
			POINT pt = m_dialogButton->GetZahyo(i);
			pt.x += m_dialogX;
			pt.y += m_dialogY;
			m_dialogButton->SetZahyo(i,pt);

			m_dialogButton->SetPicture(i,CSuperButtonPicture::GetPicture(3+i));
		}
		m_dialogButton->SetCancelButton(1);
	}


	m_outClickReturnFlag = 0;
	GetInitGameParam(&m_outClickReturnFlag,"outClickReturnFlag");

	m_basePrintX = 536;
	m_basePrintY = 10;
	m_baseSizeX = 205;
	m_baseSizeY = 300;

	GetInitGameParam(&m_basePrintX,"basePrintX");
	GetInitGameParam(&m_basePrintY,"basePrintY");
	GetInitGameParam(&m_baseSizeX,"baseSizeX");
	GetInitGameParam(&m_baseSizeY,"baseSizeY");


	m_backScreenEffectNega = 0;
	GetInitGameParam(&m_backScreenEffectNega,"backScreenEffectNega");

	m_backScreenEffectGrey = 0;
	GetInitGameParam(&m_backScreenEffectGrey,"backScreenEffectGrey");

	m_backScreenEffectMulti = 0;
	GetInitGameParam(&m_backScreenEffectMulti,"backScreenEffectMulti");

	m_backScreenEffectAddSub = 0;
	GetInitGameParam(&m_backScreenEffectAddSub,"backScreenEffectAddSub");


	m_backScreenColorR = 0;
	m_backScreenColorG = 0;
	m_backScreenColorB = 0;
	if (m_backScreenEffectAddSub)
	{
		GetInitGameParam(&m_backScreenColorR,"backScreenColorR");
		GetInitGameParam(&m_backScreenColorG,"backScreenColorG");
		GetInitGameParam(&m_backScreenColorB,"backScreenColorB");
	}

	m_backScreenMultiR = 100;
	m_backScreenMultiG = 100;
	m_backScreenMultiB = 100;
	if (m_backScreenEffectMulti)
	{
		GetInitGameParam(&m_backScreenMultiR,"backScreenMultiR");
		GetInitGameParam(&m_backScreenMultiG,"backScreenMultiG");
		GetInitGameParam(&m_backScreenMultiB,"backScreenMultiB");
	}


	m_backScreenType = 2;//1:bg 2:get 3:script
	GetInitGameParam(&m_backScreenType,"backScreenType");
	if (m_backScriptFlag) m_backScreenType = 3;

	if (m_backScreenType == 1)
	{
		m_backScreenFileName = m_defaultBackScreenFileName;
		GetInitGameString(&m_backScreenFileName,"backScreenFileName");
	}

	m_screenToGetPutFlag = 0;
	GetInitGameParam(&m_screenToGetPutFlag,"screenToGetPutFlag");

	m_getWithMessageFlag = 1;
	GetInitGameParam(&m_getWithMessageFlag,"getWithMessageFlag");

	m_saveButtonNumber = 0;
	m_loadButtonNumber = 1;
	m_configButtonNumber = 2;
	m_windowButtonNumber = 3;
	m_messageSkipButtonNumber = 4;
	m_backlogButtonNumber = 5;
	m_autoModeButtonNumber = 6;
	m_cancelButtonNumber = 7;
	m_exitButtonNumber = 8;
	//m_messageSkipButtonNumber2 = 9;

	m_expOptionMode = new int[m_optionKosuu];
	m_expOptionCommand = new int[m_optionKosuu];
	m_expOptionSound = new int[m_optionKosuu];

	for (i=9;i<m_optionKosuu;i++)
	{
		char name[256];
		int md = 0;
		wsprintf(name,"expOptionMode%d",i+1);
		GetInitGameParam(&md,name);
		m_expOptionMode[i] = md;

		int cmd = 0;
		wsprintf(name,"expOptionCommand%d",i+1);
		GetInitGameParam(&cmd,name);
		m_expOptionCommand[i] = cmd;

		int snd = -1;
		CCommonButton* button = m_menu->GetButton(i);
		int s = button->GetClickSound();
		if (s > 0)
		{
			snd = s;
		}
		m_expOptionSound[i] = snd;
	}






	m_menu->SetCancelButton(m_cancelButtonNumber);



	//set menu defauly shortcut
	m_setDefaultShortCutFlag = 1;
	GetInitGameParam(&m_setDefaultShortCutFlag,"setDefaultShortCutFlag");
	if (m_setDefaultShortCutFlag)
	{
		for (i=0;i<m_optionKosuu;i++)
		{
			if (i<m_optionKosuu)
			{
				int key = m_defaultAccelKey[i];
				if (key != -1)
				{
					BOOL found = FALSE;
					int aki = -1;

					CCommonButton* button = m_menu->GetButton(i);

					for (int k=0;k<3;k++)
					{
						int accelKey = button->GetAccelKey(k);
						if (accelKey == key) found = TRUE;

						if (aki == -1)
						{
							if (accelKey == 0)
							{
								aki = k;
							}
						}
					}

					if (found == FALSE)
					{
						if (aki != -1)
						{
							button->SetAccelKey(key,aki);
						}
					}
				}
			}
		}
	}


	m_exitWarningSound = -1;
	GetInitGameParam(&m_exitWarningSound,"exitWarningSound");

	m_nextIsSceneMode = FALSE;
	m_sceneMode = FALSE;


	m_filenameMenuBase = m_defaultMenuBaseFileName;
	GetInitGameString(&m_filenameMenuBase,"filenameMenuBase");

//	m_disableMenuFlag = FALSE;
//	if (CCommonGameVersion::CheckTaikenOrNetVersion()) m_disableMenuFlag = TRUE;
	m_disableLoadFlag = FALSE;

//	if (m_game->CheckLoadCommandOk() == FALSE) m_disableLoadFlag = TRUE;
	if (CCommonGameVersion::CheckTaikenOrNetVersion())
	{
		if (CCommonGameVersion::CheckLoadCommandOk() == FALSE)
		{
			m_disableLoadFlag = TRUE;
		}
	}

	m_disableSaveFlag = FALSE;
//	if (m_game->CheckSaveCommandOk() == FALSE) m_disableSaveFlag = TRUE;
	if (CCommonGameVersion::CheckTaikenOrNetVersion())
	{
		if (CCommonGameVersion::CheckSaveCommandOk() == FALSE)
		{
			m_disableSaveFlag = TRUE;
		}
	}

//	if (m_game->CheckNetVersion()) m_disableMenuFlag = TRUE;
//	if (m_game->CheckTaikenVersion()) m_disableMenuFlag = TRUE;

	GetFadeInOutSetup();

	m_returnToGameFlag = FALSE;
}





CCommonSystemMenu::~CCommonSystemMenu()
{
	End();
}

void CCommonSystemMenu::End(void)
{
	DELETEARRAY(m_expOptionSound);
	DELETEARRAY(m_expOptionCommand);
	DELETEARRAY(m_expOptionMode);
	ENDDELETECLASS(m_menuButtonSetup);
	ENDDELETECLASS(m_menu);
	ENDDELETECLASS(m_dialogButton);
}

void CCommonSystemMenu::BeforeInit(void)
{
	if (m_backScriptFlag && m_screenToGetPutFlag)
	{
		//reprint screen
		m_game->Erase();

		CAreaControl::SetNextAllPrint();

		if (m_getWithMessageFlag == 0)
		{
			m_game->PrintEffect();
			m_game->PrintEffect(TRUE);
		}

		m_game->GetGetScreen();
	}
}


int CCommonSystemMenu::Init(void)
{
	int i;
	m_returnToGameFlag = FALSE;

OutputDebugString("[SystemMenu::Init()]");
	m_sceneMode = FALSE;
	if (m_nextIsSceneMode)
	{
		m_sceneMode = TRUE;
		m_nextIsSceneMode = FALSE;
OutputDebugString("[SystemMenu::sceneMode]");
	}


	m_game->StopScriptSoundAndVoice();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_optionPrintMode = 0;
	m_optionStartPercent100 = 0;
	m_menu->SetExtMode(0);

	CalcuCombine();


	for (i=0;i<m_optionKosuu;i++)
	{
		int minWait = (((100*100) / m_optionStartSpeed100) * i) / m_optionKosuu;

		m_optionWait[i] = minWait + (rand() % 3);



		m_optionPercent[i] = 0;
		m_optionSpeed[i] = 100*9 + (rand() % (100*18));
	}


//	m_mode = 1;

	m_clickingFlag = FALSE;

//	m_subMode = 0;
	m_commonBG->ReSize(screenSizeX,screenSizeY);
	m_game->Erase();



	if ((m_backScreenType == 2) || (m_backScriptFlag && m_screenToGetPutFlag))
	{

		if (m_backScreenEffectNega | m_backScreenEffectGrey | m_backScreenEffectMulti | m_backScreenEffectAddSub)
		{
			if (m_backScriptFlag && m_screenToGetPutFlag)
			{
				m_game->PutGetScreen();
			}

			if (m_backScreenEffectNega)
			{
				CAllGraphics::Nega();
			}

			if (m_backScreenEffectGrey)
			{
				CAllGraphics::Grey();
			}

			if (m_backScreenEffectMulti)
			{
				CAllGraphics::Multi(m_backScreenMultiR,m_backScreenMultiG,m_backScreenMultiB);
			}

			if (m_backScreenEffectAddSub)
			{
				CAllGraphics::AddSub(m_backScreenColorR,m_backScreenColorG,m_backScreenColorB);
			}


			if (m_backScriptFlag && m_screenToGetPutFlag)
			{
				m_game->GetGetScreen();
			}
		}
	}


	if (m_backScreenType == 1)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s",m_backScreenFileName);
		m_commonBG->LoadDWQ(filename);
	}


	char filename[256];
	wsprintf(filename,"sys\\%s",m_filenameMenuBase);
	m_commonParts->LoadDWQ(filename);
	m_commonParts->Put(m_basePrintX,m_basePrintY,TRUE);
	m_commonBG->GetScreen();


	//load all dialog pic
	for (i=0;i<2;i++)
	{
		CPicture* lpPic = m_dialogButton->GetPicture(i);
		LPSTR name = m_dialogButton->GetFileName(i);
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}


	//load all menu pic
	for (i=0;i<m_optionKosuu;i++)
	{
		CPicture* lpPic = m_menu->GetPicture(i);
		LPSTR name = m_menu->GetFileName(i);
		char filename[256];

		if (CheckSceneMode())	//シーン鑑賞中
		{
			if (i == m_cancelButtonNumber)
			{
				if (m_sceneBackFileName != NULL)
				{
					name = m_sceneBackFileName;
				}
			}

			if (i == m_exitButtonNumber)
			{
				if (m_sceneEndFileName != NULL)
				{
					name = m_sceneEndFileName;
				}
			}
		}

		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}







	//all enable
	for (i=0;i<m_optionKosuu;i++)
	{
		m_menu->SetExist(i);
		m_menu->SetEnable(i);
	}



//	if (m_game->GetSystemParam(SYSTEMPARAM_SKIPMODE) == 0)
	if (0)
	{
//		m_menu->SetExist(m_messageSkipButtonNumber,FALSE);
	}
	else
	{
//		m_menu->SetExist(m_messageSkipButtonNumber2,FALSE);
	}


	//save load config space(window off) shift backlog right_click exitgame
//	if (m_disableMenuFlag)
//	{
//		m_menu->SetEnable(m_loadButtonNumber,FALSE);
//		m_menu->SetEnable(m_saveButtonNumber,FALSE);
//	}


	//check expMode disable
	for (int i=9;i<m_optionKosuu;i++)
	{
		int md = m_expOptionMode[i];
		if (md > 0)
		{
			if (m_game->CheckExpModeByVar(md) == FALSE)
			{
				m_menu->SetEnable(i,FALSE);
			}
		}
	}


	if (m_disableLoadFlag)
	{
		m_menu->SetEnable(m_loadButtonNumber,FALSE);
	}
	else
	{
		if (m_noSaveDataToMaskMenu != 0)
		{
			bool bCannotLoad = true;
			if (m_game->CheckExistSaveData())
			{
				bCannotLoad = false;
			}
			if (bCannotLoad)
			{
				m_menu->SetEnable(m_loadButtonNumber, FALSE);
			}
			else
			{
				m_menu->SetEnable(m_loadButtonNumber, TRUE);
			}
		}

	}


	if (m_disableSaveFlag)
	{
		m_menu->SetEnable(m_saveButtonNumber,FALSE);
	}


	if ((m_backMode != PRINTMESSAGE_MODE) && (m_backMode != SELECTMESSAGE_MODE))
	{
		m_menu->SetEnable(m_windowButtonNumber,FALSE);
		m_menu->SetEnable(m_messageSkipButtonNumber,FALSE);
//		m_menu->SetEnable(m_messageSkipButtonNumber2,FALSE);
//		m_menu->SetEnable(m_backlogButtonNumber,FALSE);
		m_menu->SetEnable(m_autoModeButtonNumber,FALSE);
	}

	if (m_game->GetBackLogOk(m_backMode) == 0)
	{
		m_menu->SetEnable(m_backlogButtonNumber,FALSE);
	}

	//シーン鑑賞中
	if (CheckSceneMode())
	{
		m_menu->SetEnable(m_loadButtonNumber,FALSE);
		m_menu->SetEnable(m_saveButtonNumber,FALSE);

		for (int i=9;i<m_optionKosuu;i++)
		{
			m_menu->SetEnable(i,FALSE);
		}
	}
	else
	{
		//quick load set

		if (m_game->CheckUseQuickLoad())
		{
			//search quick load
			int found = -1;

			for (int i=9;i<m_optionKosuu;i++)
			{
				if (m_expOptionCommand[i] == LOAD_MODE)
				{
					found = i;
					break;
				}
			}

			if (found != -1)
			{
				if (m_game->CheckExistQuickLoadData())
				{
					m_menu->SetEnable(found);
				}
				else
				{
					m_menu->SetEnable(found,FALSE);
				}
			}
		}
	}




	m_menu->Init();
	m_dialogButton->Init();
	m_dialogButton->Calcu(NULL);

	m_warningFlag = FALSE;

	return -1;
}



int CCommonSystemMenu::Calcu(void)
{
	if (m_warningFlag)
	{
		int rt = m_dialogButton->Calcu(m_inputStatus);
		if (rt != NNNBUTTON_NOTHING)
		{
			int nm = ProcessButtonGroup(rt);

			if (nm == 0)
			{
				CreateExitScreen();
				if (CheckSceneMode() == FALSE)
				{
					return ReturnFadeOut(TITLE_MODE);
				}
				else
				{
					return ReturnFadeOut(SELECTSCENE_MODE);
				}
			}

			if (nm == 1)
			{
				m_returnToGameFlag = TRUE;
				//m_game->FuqueAllEffect();
				return ReturnFadeOut(m_backMode);
			}
		}

		return -1;
	}


	if (m_optionPrintMode == 0)
	{
		CalcuStartOption();
		if (CheckAllOptionPrint()) m_optionPrintMode = 1;

		if (m_mouseStatus->CheckClick(0)) m_optionPrintMode = 1;
		if (m_mouseStatus->CheckClick(1)) m_optionPrintMode = 1;

		if (m_optionPrintMode == 0) return -1;
		m_menu->Calcu(NULL);

		CAreaControl::SetNextAllPrint();
		return -1;
	}



	int rt = m_menu->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessButtonGroup(rt);
		if (nm >= 0)
		{
			m_menu->Init();

			if (nm == m_saveButtonNumber)
			{
				m_game->SetCommonBackMode(SAVE_MODE,m_backMode);
				CreateExitScreen();
				return ReturnFadeOut(SAVE_MODE);
			}

			if (nm == m_loadButtonNumber)
			{
				m_game->SetCommonBackMode(LOAD_MODE,m_backMode);
				CreateExitScreen();
				return ReturnFadeOut(LOAD_MODE);
			}

			if (nm == m_configButtonNumber)
			{
				m_game->SetCommonBackMode(CONFIG_MODE,m_backMode);
				CreateExitScreen();
				return ReturnFadeOut(CONFIG_MODE);
			}

			if (nm == m_windowButtonNumber)
			{
				m_game->WindowOn(FALSE);
//				m_game->FuqueAllEffect();
				m_returnToGameFlag = TRUE;
				return ReturnFadeOut(m_backMode);
				return m_backMode;
			}

			if (nm == m_messageSkipButtonNumber)
			{
				m_game->SetMessageSkipFlag();
//				m_game->FuqueAllEffect();
				m_returnToGameFlag = TRUE;
				return ReturnFadeOut(m_backMode);
				return m_backMode;
			}

//			if (nm == m_messageSkipButtonNumber2)
//			{
//				m_game->SetMessageSkipFlag(FALSE);
//				m_game->FuqueAllEffect();
//				return m_backMode;
//			}

			if (nm == m_backlogButtonNumber)
			{
				m_game->SetCommonBackMode(BACKLOG_MODE,m_backMode);
				return BACKLOG_MODE;
			}


			if (nm == m_autoModeButtonNumber)
			{
				m_game->SetSystemParam(NNNPARAM_AUTOMODE,1);
//				m_game->FuqueAllEffect();
				m_returnToGameFlag = TRUE;
				return ReturnFadeOut(m_backMode);
				return m_backMode;
			}


			if (nm == m_cancelButtonNumber)
			{
//				m_game->FuqueAllEffect();
				m_returnToGameFlag = TRUE;
				return ReturnFadeOut(m_backMode);

				//return m_backMode;
			}

			if (nm == m_exitButtonNumber)
			{
				if ((m_warningPrintFlag == 0) || CheckSceneMode())
				{
					CreateExitScreen();
					if (CheckSceneMode() == FALSE)
					{
						return ReturnFadeOut(TITLE_MODE);
					}
					else
					{
						return ReturnFadeOut(SELECTSCENE_MODE);
					}
				}

				if (m_exitWarningSound > 0)
				{
					m_game->PlaySystemSound(m_exitWarningSound-1);
				}

				m_warningFlag = TRUE;
				CAreaControl::SetNextAllPrint();

				m_game->Erase();

				if ((m_backScriptFlag == 0) && (m_mustAllPrintFlag == 1))
				{
					m_commonBG->Put(0,0,FALSE);
				}

				char filename[256];
				wsprintf(filename,"sys\\%s",m_filenameDialog);
				m_commonParts->LoadDWQ(filename);

				if (m_mustAllPrintFlag == 0)
				{
					m_commonParts->Put(m_dialogX,m_dialogY,TRUE);
				}
				m_commonBG->GetScreen();
				return -1;
			}

			if ((nm >= 9) && (nm < m_optionKosuu))
			{
				int md = m_expOptionMode[nm];
				if (md > 0)
				{
					m_game->SetCommonBackMode(md,m_backMode);
					CreateExitScreen();
					return ReturnFadeOut(md);
				}

				int cmd = m_expOptionCommand[nm];
				if (cmd > 0)
				{
					if (cmd == LOAD_MODE)
					{
						if (m_game->CheckQuickLoadDelay())
						{
							m_game->SetQuickLoadDelay();
							return -1;
						}
					}

					int cmdrt = m_game->ExpOptionCommand(cmd);
					if (cmdrt == -1)
					{
						m_returnToGameFlag = TRUE;
						return ReturnFadeOut(m_backMode);
					}

					return -1;
				}
			}

		}

		return -1;
	}

	//
	if (m_outClickReturnFlag)
	{
		if (m_mouseStatus->CheckClick(0))
		{
			//out?
			POINT pt = m_mouseStatus->GetZahyo();
			int dx = pt.x - m_basePrintX;
			int dy = pt.y - m_basePrintY;

			if ((dx<0) || (dx>=m_baseSizeX) || (dy<0) || (dy>=m_baseSizeY))
			{
				m_returnToGameFlag = TRUE;
				return ReturnFadeOut(m_backMode);
			}
		}
	}

	return -1;
}


BOOL CCommonSystemMenu::CheckAllOptionPrint(void)
{
	if (m_optionStartPercent100 < 100*100) return FALSE;

	for (int i=0;i<m_optionKosuu;i++)
	{
		if (m_optionPercent[i] < 100*100) return FALSE;
	}

	return TRUE;
}

int CCommonSystemMenu::Print(void)
{
	if (!m_warningFlag)
	{
		if (m_optionPrintMode == 0)
		{
			if (m_optionStartPrintType > 0)
			{
				CAreaControl::SetNextAllPrint();
			}
		}
	}


	BOOL b = CAreaControl::CheckAllPrintMode();

	PrintBackScriptOrBG();

/*
	if (m_subMode == 0)
	{
		if (m_optionPrintMode == 0)
		{
			int putX = m_basePrintX;
			int putY = m_basePrintY;
			int sizeX = m_baseSizeX;
			int sizeY = m_baseSizeY;

//			CAreaControl::AddArea(putX-44,putY-10,264,321);
			CAreaControl::AddArea(m_basePrintX,m_basePrintY,m_baseSizeX,m_baseSizeY);


			if (b == FALSE)
			{
				m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
///				PutUpMenu();
///				PutDownMenu(m_optionStartPercent100 / 100);
				PutMenuBase(m_optionStartPercent100 / 100);

				int psy = (m_optionStartPercent100 * m_optionSizeY * m_optionKosuu) / (100 * 100);

				for (int i=0;i<m_optionKosuu;i++)
				{
					int sizeY = psy - i * m_optionSizeY;
					if (sizeY>0)
					{
						if (sizeY>m_optionSizeY) sizeY = m_optionSizeY;
						PutOption(i,sizeY);
					}
				}
//m_commonParts->Put(0,0,FALSE);

			}

		}
		else
		{
			if (b)
			{
//				PutUpMenu();
//				PutDownMenu();
				PutMenuBase(m_optionStartPercent100 / 100);
			}
			m_menu->Print(b);
		}
	}
*/


	if (m_warningFlag)
	{
		if (m_warningMenuPrintFlag)
		{
//			m_dialogButton->Print(b);
			m_menu->Print(TRUE);
		}

		if (m_backScriptFlag)
		{
			if (m_warningMenuPrintFlag)
			{
				m_commonParts->Put(m_dialogX,m_dialogY,TRUE);
			}
		}
		else
		{
			if (m_mustAllPrintFlag == 0)
			{
				m_commonBG->Blt(m_dialogX,m_dialogY,m_dialogX,m_dialogY,m_dialogSizeX,m_dialogSizeY,FALSE);
			}
			else
			{
				m_commonParts->Put(m_dialogX,m_dialogY,TRUE);
			}
		}

		//
		if (m_warningMenuPrintFlag)
		{
			m_dialogButton->Print(b);
//			m_menu->Print(TRUE);
		}
	}
	else
	{
		if (m_optionPrintMode == 0)
		{
			if (m_optionStartPrintType > 0)
			{
				m_menu->SpecialPrint(m_optionStartPercent100,10000,m_optionStartPrintType-1);
			}
			else
			{
				m_menu->Print(TRUE);
			}
		}
		else
		{
			m_menu->Print(TRUE);
		}
	}

	return -1;
}

/*
void CCommonSystemMenu::PutOption(int n, int sizeY)
{
	int ps = m_optionPercent[n];
	int sizeX = (m_optionSizeX * ps) / (100*100);

	int srcX = m_optionSrcX[n] + m_optionSizeX - sizeX;
	int srcY = m_optionSrcY[n];

	int putX = m_basePrintX + m_optionPrintX;
	int putY = m_basePrintY + m_optionPrintY + n * m_optionNextY;

	BOOL grey = FALSE;
	CPicture* pic = m_commonParts;

	if (m_optionSrcMode[n]) grey = TRUE;


	if (m_superMenuFlag)
	{
		srcX = m_optionSizeX - sizeX;
		srcY = 0;

		int c = n;
		if (c == m_messageSkipButtonNumber)
		{
			if (m_game->GetSystemParam(SYSTEMPARAM_SKIPMODE) == 0) c = m_exitButtonNumber+1;
		}

		pic = m_superPic[c];

		if (grey)
		{
			srcX += m_optionSizeX * 3;
			grey = FALSE;
		}
	}


	if ((sizeX>0) && (sizeY>0))
	{
		if (grey == FALSE)
		{
			pic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
		}
		else
		{
			pic->GreyBlt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
		}
	}

}
*/


void CCommonSystemMenu::CalcuStartOption(void)
{
	if (m_optionStartPercent100 < 100*100)
	{
		m_optionStartPercent100 += m_optionStartSpeed100;
		if (m_optionStartPercent100 >= 100*100) m_optionStartPercent100 = 100*100;
	}

	for (int i=0;i<m_optionKosuu;i++)
	{
		int wait = m_optionWait[i];

		if (wait>0)
		{
			wait--;
			m_optionWait[i] = wait;
		}

		if (wait == 0)
		{
			int ps = m_optionPercent[i];
			int sp = m_optionSpeed[i];

			ps += sp;
			if (ps >= 100*100) ps = 100*100;

			m_optionPercent[i] = ps;
		}
	}
}

void CCommonSystemMenu::PutMenuBase(int ps)
{
	int upperSize = m_optionPrintY;

	int putX1 = m_basePrintX;
	int putY1 = m_basePrintY;
	int srcX1 = m_basePrintX;
	int srcY1 = m_basePrintY;
	int sizeX1 = m_baseSizeX;
	int sizeY1 = upperSize + ((m_optionKosuu * m_optionSizeY) * ps) / 100;

	int putX2 = putX1;
	int putY2 = putY1 + sizeY1;
	int srcX2 = srcX1;
	int srcY2 = upperSize + m_optionKosuu * m_optionSizeY;
	int sizeX2 = sizeX1;
	int sizeY2 = m_baseSizeY - upperSize - m_optionKosuu * m_optionSizeY;

	m_commonBG->Blt(putX1,putY1,putX1,putY1,sizeX1,sizeY1+sizeY2,FALSE);

//	m_menuBasePic->Blt(putX1,putY1,srcX1,srcY1,sizeX1,sizeY1,TRUE);
//	m_menuBasePic->Blt(putX2,putY2,srcX2,srcY2,sizeX2,sizeY2,TRUE);
}




void CCommonSystemMenu::CalcuCombine(void)
{
//	if (m_game->GetSystemParam(SYSTEMPARAM_SKIPMODE) == 1)
	if (0)
	{
//		m_menu->SetButtonCombine(m_messageSkipButtonNumber,m_messageSkipButtonNumber);
	}
	else
	{
//		m_menu->SetButtonCombine(m_messageSkipButtonNumber,m_exitButtonNumber+1);
	}
}


void CCommonSystemMenu::CreateStartScreen(void)
{
	Print();
}

void CCommonSystemMenu::SetSceneMode(BOOL flg)
{
	if (flg)
	{
		m_nextIsSceneMode = TRUE;
	}
	else
	{
		m_nextIsSceneMode = FALSE;
		m_sceneMode = FALSE;
	}
}


BOOL CCommonSystemMenu::CheckSceneMode(void)
{
	return m_sceneMode;
}

void CCommonSystemMenu::FinalExitRoutine(void)
{
	if (m_returnToGameFlag)
	{
		m_returnToGameFlag = FALSE;
		m_game->FuqueAllEffectYoyaku();
	}

	//m_game->FuqueAllEffect();
}

int CCommonSystemMenu::EndMode(void)
{
	return -1;
	//m_game->FuqueAllEffect();
}


int CCommonSystemMenu::GetExpShortCutKey(int n)
{
	CCommonButton* button = m_menu->GetButton(n);
	if (button != NULL)
	{
		return button->GetAccelKey();
	}

	return -1;
}


/*
void CCommonSystemMenu::ScreenEffectAddSub(void)
{
	int screenSizeX = CPicture::m_screenSizeX;
	int screenSizeY = CPicture::m_screenSizeY;
	int* dst = (int*)CPicture::m_lpScreenBuffer;

	int addR = m_backScreenColorR;
	int addG = m_backScreenColorG;
	int addB = m_backScreenColorB;

	if (addR<0) addR = 0;
	if (addG<0) addG = 0;
	if (addB<0) addB = 0;

	int subR = -m_backScreenColorR;
	int subG = -m_backScreenColorG;
	int subB = -m_backScreenColorB;

	if (subR<0) subR = 0;
	if (subG<0) subG = 0;
	if (subB<0) subB = 0;

	int addColor = (addR << 16) | (addG << 8) | addB;
	int subColor = (subR << 16) | (subG << 8) | subB;

	int loopSize = screenSizeX * screenSizeY / 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,addColor
		movd mm4,eax
		punpckldq mm4,mm4

		mov eax,subColor
		movd mm5,eax
		punpckldq mm5,mm5

		mov edi,dst
		mov ecx,loopSize
LOOP1:
		movq mm1,[edi]
		movq mm2,[edi+8]

		paddusb mm1,mm4
		paddusb mm2,mm4
		psubusb mm1,mm5
		psubusb mm2,mm5

		movq [edi],mm1
		movq [edi+8],mm2

		add edi,16
		dec ecx
		jnz LOOP1


		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}


void CCommonSystemMenu::ScreenEffectGrey(void)
{
	int screenSizeX = CPicture::m_screenSizeX;
	int screenSizeY = CPicture::m_screenSizeY;
	int* dst = (int*)CPicture::m_lpScreenBuffer;

	int addR = m_backScreenColorR;
	int addG = m_backScreenColorG;
	int addB = m_backScreenColorB;

	if (addR<0) addR = 0;
	if (addG<0) addG = 0;
	if (addB<0) addB = 0;

	int subR = -m_backScreenColorR;
	int subG = -m_backScreenColorG;
	int subB = -m_backScreenColorB;

	if (subR<0) subR = 0;
	if (subG<0) subG = 0;
	if (subB<0) subB = 0;

	int addColor = (addR << 16) | (addG << 8) | addB;
	int subColor = (subR << 16) | (subG << 8) | subB;


	int loopSize = screenSizeX * screenSizeY / 2;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,addColor
		movd mm4,eax
		punpckldq mm4,mm4

		mov eax,subColor
		movd mm5,eax
		punpckldq mm5,mm5

		mov eax,76*65536 + 150*256 + 29
		movd mm6,eax
		punpcklbw mm6,mm0


		mov edi,dst
		mov ecx,loopSize
LOOP1:
		movq mm1,[edi]
		movq mm2,mm1
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		pmaddwd mm1,mm6
		pmaddwd mm2,mm6
		//stall
		psrld mm1,8
		psrld mm2,8

		packssdw mm1,mm2


		movq mm3,mm1
		psrld mm3,16
		paddw mm1,mm3
		movq mm3,mm1

		punpcklbw mm1,mm1
		punpcklwd mm1,mm1

		punpckhbw mm3,mm3
		punpcklwd mm3,mm3

		punpckldq mm1,mm3

		pslld mm1,8
		psrld mm1,8


		paddusb mm1,mm4
		psubusb mm1,mm5

		movq [edi],mm1

		add edi,8
		dec ecx
		jnz LOOP1

		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax

	}
}


void CCommonSystemMenu::ScreenEffectNega(void)
{
	int screenSizeX = CPicture::m_screenSizeX;
	int screenSizeY = CPicture::m_screenSizeY;
	int* dst = (int*)CPicture::m_lpScreenBuffer;

	int addR = m_backScreenColorR;
	int addG = m_backScreenColorG;
	int addB = m_backScreenColorB;

	if (addR<0) addR = 0;
	if (addG<0) addG = 0;
	if (addB<0) addB = 0;

	int subR = -m_backScreenColorR;
	int subG = -m_backScreenColorG;
	int subB = -m_backScreenColorB;

	if (subR<0) subR = 0;
	if (subG<0) subG = 0;
	if (subB<0) subB = 0;

	int addColor = (addR << 16) | (addG << 8) | addB;
	int subColor = (subR << 16) | (subG << 8) | subB;


	int loopSize = screenSizeX * screenSizeY / 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,addColor
		movd mm4,eax
		punpckldq mm4,mm4

		mov eax,subColor
		movd mm5,eax
		punpckldq mm5,mm5

		mov eax,0ffffffh
		movd mm6,eax
		punpckldq mm6,mm6

		mov edi,dst
		mov ecx,loopSize
LOOP1:
		movq mm1,[edi]
		movq mm2,[edi+8]
		pxor mm1,mm6
		pxor mm2,mm6

		paddusb mm1,mm4
		paddusb mm2,mm4
		psubusb mm1,mm5
		psubusb mm2,mm5

		movq [edi],mm1
		movq [edi+8],mm2

		add edi,16
		dec ecx
		jnz LOOP1

		emms

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax

	}
}


*/