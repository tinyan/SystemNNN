//
// commonSelectMessage.cpp
//


#include <windows.h>

#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"
#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"
#include "..\nnnUtilLib\suuji.h"
#include "..\nnnUtilLib\Myfont.h"

#include "..\nnnUtilLib\nnnButtonStatus.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonUpDownButtonGroup.h"

#include "..\nnnUtilLib\autoSelectControl.h"

#include "commonSystemSoundName.h"

#include "commonMode.h"
#include "commonSystemParamName.h"



#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonSelectMessage.h"



#include "commonKeyList.h"
#include "..\nnnUtilLib\myMessage.h"


char CCommonSelectMessage::m_defaultCursorFileName[] = "ta_select01";
char CCommonSelectMessage::m_defaultBackFileName[] = "sel_bg";
char CCommonSelectMessage::m_defaultWindowFileName[] = "ta_win_select";

char CCommonSelectMessage::m_defaultBacklogMessage[] = "#足選択肢";
char CCommonSelectMessage::m_defaultBacklogMessage_1byte[] = "#fselect";


CCommonSelectMessage::CCommonSelectMessage(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTMESSAGE_MODE);
	//m_classNumber = SELECTMESSAGE_MODE;
	LoadSetupFile("SelectMessage",128);

	int codeByte = CMyFont::m_codeByte;

	GetAllPrintSetup();
	m_mustAllPrintFlag = 1;

	m_scrollSelectFlag = 0;
	GetInitGameParam(&m_scrollSelectFlag,"useScrollFlag");
	if (m_scrollSelectFlag)
	{
		CreateUpDownButton();
		m_updown->SetBG(NULL);
	}

	m_autoSelectControl = m_game->GetAutoSelectControl();

	m_windowOffMouseButton = m_game->GetWindowOffMouseButton();

	m_timeLimit = 0;
	m_specialFlag =  0;

	m_firstAppearTime = 10;
	m_firstAppearType = 0;

	m_optionOk = 0;
	m_backLogOk = 1;

	GetInitGameParam(&m_optionOk,"optionOk");
	GetInitGameParam(&m_backLogOk,"backLogOk");

	if (m_optionOk) m_backLogOk = 1;

	if (m_backLogOk)
	{
		m_game->SetBackLogOk(SELECTMESSAGE_MODE);
	}

	m_windowPrintFlag = 1;
	GetInitGameParam(&m_windowPrintFlag,"windowPrintFlag");


	m_windowPrintX = 0;
	m_windowPrintY = 400;
	m_windowSizeX = 800;
	m_windowSizeY = 200;

	m_windowFileName = m_defaultWindowFileName;

	if (m_windowPrintFlag)
	{
		GetInitGameString(&m_windowFileName,"windowFileName");
	
		GetInitGameParam(&m_windowPrintX,"windowPrintX");
		GetInitGameParam(&m_windowPrintY,"windowPrintY");
		GetInitGameParam(&m_windowSizeX,"windowSizeX");
		GetInitGameParam(&m_windowSizeY,"windowSizeY");
	}

	m_timeLimitWindowPrintFlag = m_windowPrintFlag;
	GetInitGameParam(&m_timeLimitWindowPrintFlag,"timeLimitWindowPrintFlag");

	if (m_timeLimitWindowPrintFlag)
	{
		m_timeLimitWindowFileName = m_windowFileName;
		GetInitGameString(&m_timeLimitWindowFileName,"timeLimitWindowFileName");

		m_timeLimitWindowPrintX = m_windowPrintX;
		m_timeLimitWindowPrintY = m_windowPrintY;
		GetInitGameParam(&m_timeLimitWindowPrintX,"timeLimitWindowPrintX");
		GetInitGameParam(&m_timeLimitWindowPrintY,"timeLimitWindowPrintY");
		m_timeLimitWindowSizeX = m_windowSizeX;
		m_timeLimitWindowSizeY = m_windowSizeY;
		GetInitGameParam(&m_timeLimitWindowSizeX,"timeLimitWindowSizeX");
		GetInitGameParam(&m_timeLimitWindowSizeY,"timeLimitWindowSizeY");
	}



	GetInitGameParam(&m_firstAppearType,"firstAppearType");
	if (m_firstAppearType != 0)
	{
		GetInitGameParam(&m_firstAppearTime,"firstAppearTime");
	}

	m_clickingTime = 5;
	GetInitGameParam(&m_clickingTime,"clickingTime");

	m_animePatternKosuu = 8;
	GetInitGameParam(&m_animePatternKosuu,"animePatternNumber");
	if (m_animePatternKosuu < 1) m_animePatternKosuu = 1;



	m_animeFrame = 1;
	GetInitGameParam(&m_animeFrame,"animeFrame");
	if (m_animeFrame < 1) m_animeFrame = 1;

	m_animeReverse = 0;
	GetInitGameParam(&m_animeReverse,"animeReverse");

	m_animePrintType = 0;
	GetInitGameParam(&m_animePrintType,"animePrintType");

	m_cursorIsOnMessage = 0;
	GetInitGameParam(&m_cursorIsOnMessage,"cursorIsOnMessage");

	m_backPrintMode = 0;
	GetInitGameParam(&m_backPrintMode,"backPrintMode");
	
	m_backColorR = 0;
	m_backColorG = 0;
	m_backColorB = 0;
	m_filenameBack = m_defaultBackFileName;
	if (m_backPrintMode == 0)
	{
		GetInitGameParam(&m_backColorR,"backColorR");
		GetInitGameParam(&m_backColorG,"backColorG");
		GetInitGameParam(&m_backColorB,"backColorB");
	}

	if (m_backPrintMode == 1)
	{
		GetInitGameString(&m_filenameBack,"backFileName");
	}


	m_messagePrintX = 66;
	m_messagePrintY = 383;

	m_messageNextX = 0;
	m_messageNextY = 30;

	m_cursorSizeX = 469;
	m_cursorSizeY = 27;

	m_cursorDeltaX = -8;
	m_cursorDeltaY = -2;

	GetInitGameParam(&m_messagePrintX,"messagePrintX");
	GetInitGameParam(&m_messagePrintY,"messagePrintY");


	GetInitGameParam(&m_messageNextX,"messageNextX");
	GetInitGameParam(&m_messageNextY,"messageNextY");

	GetInitGameParam(&m_cursorSizeX,"cursorSizeX");
	GetInitGameParam(&m_cursorSizeY,"cursorSizeY");

	GetInitGameParam(&m_cursorDeltaX,"cursorDeltaX");
	GetInitGameParam(&m_cursorDeltaY,"cursorDeltaY");


	m_fontSize = 24;
	GetInitGameParam(&m_fontSize,"fontSize");



	LPSTR filename = m_defaultCursorFileName;
	GetInitGameString(&filename,"cursorFileName");
	m_selectPic = m_game->GetSystemPicture(filename);


	m_messagePrintGyo = 4;
	GetInitGameParam(&m_messagePrintGyo,"messagePrintGyo");


	if (codeByte == 2)
	{
		m_backlogMessage = m_defaultBacklogMessage;
	}
	else
	{
		m_backlogMessage = m_defaultBacklogMessage_1byte;
	}

	GetInitGameString(&m_backlogMessage,"backlogMessage");

	m_backlogMessageColorR = 64;
	m_backlogMessageColorG = 192;
	m_backlogMessageColorB = 255;
	GetInitGameParam(&m_backlogMessageColorR,"backlogMessageColorR");
	GetInitGameParam(&m_backlogMessageColorG,"backlogMessageColorG");
	GetInitGameParam(&m_backlogMessageColorB,"backlogMessageColorB");

	m_backlogSelectColorR = 192;
	m_backlogSelectColorG = 232;
	m_backlogSelectColorB = 255;

	GetInitGameParam(&m_backlogSelectColorR,"backlogSelectColorR");
	GetInitGameParam(&m_backlogSelectColorG,"backlogSelectColorG");
	GetInitGameParam(&m_backlogSelectColorB,"backlogSelectColorB");


	GetKeyMoveSetup();

	m_messageKosuu = 0;
	m_addMessageKosuu = 0;

	m_messageData[0][0] = 0;
	m_messageData[1][0] = 0;
	m_messageData[2][0] = 0;
	m_messageData[3][0] = 0;

	m_clickingFlag = FALSE;
	m_clickingCount = 5;

	m_message = m_game->GetMyMessage();


//	m_picBuffer = (int*)m_selectPic->GetBuffer();
//	RECT rc;
//	m_selectPic->GetPicSize(&rc);
//	m_selPiclPitch = rc.right;

	m_selectAnimeCount = 0;

	m_nowOptionSelectNumber = -1;




	m_windowOffSound = -1;
	m_windowOnSound = -1;
	m_selectSound = 0;
	m_backlogSound = -1;

	GetInitGameParam(&m_windowOffSound,"windowOffSound");
	GetInitGameParam(&m_windowOnSound,"windowOnSound");
	GetInitGameParam(&m_selectSound,"selectSound");
	GetInitGameParam(&m_backlogSound,"backlogSound");

	for (int i=0;i<64;i++)
	{
		m_messageData[i][0] = 0;
	}

	m_optionPrintX = 589;
	m_optionPrintY = 7;
	m_optionSizeX = 50;
	m_optionSizeY = 54;

//	m_appearingFlag = FALSE;


	m_timerColorR1 = 0;
	m_timerColorG1 = 255;
	m_timerColorB1 = 0;

	m_timerColorR2 = 255;
	m_timerColorG2 = 0;
	m_timerColorB2 = 0;

	m_timerPrintType = 1;	//0:none 1:color-bar 2:pic-bar 3:picAnime 4:picAnime(nameraka)

	m_timeLimitOptionOk = 0;
	GetInitGameParam(&m_timeLimitOptionOk,"timeLimitOptionOk");

	GetInitGameParam(&m_timerPrintType,"timerPrintType");
	if (m_timerPrintType == 1)
	{
		GetInitGameParam(&m_timerColorR1,"timerColorR1");
		GetInitGameParam(&m_timerColorG1,"timerColorG1");
		GetInitGameParam(&m_timerColorB1,"timerColorB1");
		GetInitGameParam(&m_timerColorR2,"timerColorR2");
		GetInitGameParam(&m_timerColorG2,"timerColorG2");
		GetInitGameParam(&m_timerColorB2,"timerColorB2");
		m_timerPicSizeX = 100;
		m_timerPicSizeY = 32;
		GetInitGameParam(&m_timerPicSizeX,"timerPicSizeX");
		GetInitGameParam(&m_timerPicSizeY,"timerPicSizeY");
	}

	m_timerPic = NULL;
	if (m_timerPrintType > 1)
	{
		m_timerPic = new CPicture();
		LPSTR name = NULL;
		GetInitGameString(&name,"fileNameTimer");
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		m_timerPic->LoadDWQ(filename);
		SIZE sz = m_timerPic->GetPicSize();
		m_timerPicSizeX = sz.cx;
		m_timerPicSizeY = sz.cy;
		GetInitGameParam(&m_timerPicSizeX,"timerPicSizeX");
		GetInitGameParam(&m_timerPicSizeY,"timerPicSizeY");
		m_timerPicKosuu = 1;
		GetInitGameParam(&m_timerPicKosuu,"timerPicNumber");
	}


	if (m_timerPrintType >= 1)
	{
		m_timerPrintX = 0;
		m_timerPrintY = 0;
		GetInitGameParam(&m_timerPrintX,"timerPrintX");
		GetInitGameParam(&m_timerPrintY,"timerPrintY");

		m_timerBarHoukou = 1;
		GetInitGameParam(&m_timerBarHoukou,"timerBarHoukou");
	}

	m_timerSuujiPrintFlag = 0;
	GetInitGameParam(&m_timerSuujiPrintFlag,"timerTimePrintFlag");
	m_timerSuuji = NULL;
	m_timerSuuji2 = NULL;

	if (m_timerSuujiPrintFlag)
	{
		int suujiSizeX = 16;
		int suujiSizeY = 16;
		GetInitGameParam(&suujiSizeX,"timerTimeFontSizeX");
		GetInitGameParam(&suujiSizeY,"timerTimeFontSizeY");
		LPSTR name = NULL;
		GetInitGameString(&name,"fileNameTimerTime");
		CPicture* lpPic = m_game->GetSystemPicture(name);
		int keta = 3;
		GetInitGameParam(&keta,"timerTimeKeta");
		int suujiNextX = suujiSizeX;
		GetInitGameParam(&suujiNextX,"timerTimeFontNextX");
		int leftFlag = 0;
		int upzeroFlag = 0;
		GetInitGameParam(&leftFlag,"timerTimeLeftFlag");
		GetInitGameParam(&upzeroFlag,"timerTimeUpzeroFlag");
		m_timerSuuji = new CSuuji(lpPic,suujiSizeX,suujiSizeY,keta,suujiNextX,upzeroFlag,TRUE,leftFlag);
		m_timerSuujiPrintX = 0;
		m_timerSuujiPrintY = 0;
		GetInitGameParam(&m_timerSuujiPrintX,"timerTimePrintX");
		GetInitGameParam(&m_timerSuujiPrintY,"timerTimePrintY");

		if (m_timerSuujiPrintFlag >= 3)
		{
			int suujiSizeX2 = suujiSizeX;
			int suujiSizeY2 = suujiSizeY;
			GetInitGameParam(&suujiSizeX2,"timerTimeFontSizeX2");
			GetInitGameParam(&suujiSizeY2,"timerTimeFontSizeY2");

			LPSTR name2 = name;
			GetInitGameString(&name2,"fileNameTimerTime2");
			CPicture* lpPic2 = m_game->GetSystemPicture(name2);
			
			int keta2 = m_timerSuujiPrintFlag - 2;
			GetInitGameParam(&keta2,"timerTimeKeta2");

			int suujiNextX2 = suujiSizeX2;
			GetInitGameParam(&suujiNextX2,"timerTimeFontNextX2");
			int leftFlag2 = 0;
			int upzeroFlag2 = 0;
			GetInitGameParam(&leftFlag,"timerTimeLeftFlag2");
			GetInitGameParam(&upzeroFlag,"timerTimeUpzeroFlag2");
			m_timerSuuji2 = new CSuuji(lpPic2,suujiSizeX2,suujiSizeY2,keta2,suujiNextX2,upzeroFlag2,TRUE,leftFlag2);
			
			m_timerSuujiPrintX2 = m_timerSuujiPrintX + keta*suujiSizeX;
			m_timerSuujiPrintY2 = m_timerSuujiPrintY;
			GetInitGameParam(&m_timerSuujiPrintX2,"timerTimePrintX2");
			GetInitGameParam(&m_timerSuujiPrintY2,"timerTimePrintY2");
		}
	}



	m_useSpecialFlagKosuu = 0;
	GetInitGameParam(&m_useSpecialFlagKosuu,"useSpecialNumber");
	
	m_specialWindowPrintX = NULL;
	m_specialWindowPrintY = NULL;

	m_specialMessagePrintX = 0;
	m_specialMessagePrintY = 0;
	m_specialWindowSizeX = 800;
	m_specialWindowSizeY = 60;

	m_specialCheckVar = NULL;
	m_specialSelectPic = NULL;


	m_specialFontSize = m_fontSize;

	m_specialWindowPic = NULL;

	m_centeringFlag = 0;

	if (m_useSpecialFlagKosuu)
	{
		LPSTR windowFileName = NULL;
		GetInitGameString(&windowFileName,"filenameSpecialWindow");
		m_specialWindowPic = m_game->GetSystemPicture(windowFileName);

		GetInitGameParam(&m_specialWindowSizeX,"specialWindowSizeX");
		GetInitGameParam(&m_specialWindowSizeY,"specialWindowSizeY");


		GetInitGameParam(&m_centeringFlag,"centeringFlag");

		m_specialWindowPrintX = new int[m_useSpecialFlagKosuu*m_useSpecialFlagKosuu];
		m_specialWindowPrintY = new int[m_useSpecialFlagKosuu*m_useSpecialFlagKosuu];
		m_specialCheckVar = new int[m_useSpecialFlagKosuu];
		if (m_centeringFlag)
		{
			m_centerAreaSizeX = m_specialWindowSizeX;
			GetInitGameParam(&m_centerAreaSizeX,"centerAreaSizeX");
		}




		for (int j=0;j<m_useSpecialFlagKosuu;j++)
		{
			char name[256];

			for (int i=0;i<j+1;i++)
			{
				wsprintf(name,"specialWindow%dprintX%d",j+1,i+1);
				int spx = 0;
				GetInitGameParam(&spx,name);
				m_specialWindowPrintX[j*m_useSpecialFlagKosuu+i] = spx;

				wsprintf(name,"specialWindow%dprintY%d",j+1,i+1);
				int spy = j * m_specialWindowSizeY;
				GetInitGameParam(&spy,name);
				m_specialWindowPrintY[j*m_useSpecialFlagKosuu+i] = spy;
			}

			LPSTR checkVarName = NULL;
			wsprintf(name,"specialWindowVarName%d",j+1);

			int varNumber = -1;
			if (GetInitGameString(&checkVarName,name))
			{
				varNumber = m_game->GetVarNumber(checkVarName);
			}
			m_specialCheckVar[j] = varNumber;
		}



		LPSTR filenameSpecialCurosrPic = NULL;

		m_specialAnimePatternKosuu = m_animePatternKosuu;
		m_specialAnimeFrame = m_animeFrame;
		m_specialAnimeReverse = m_animeReverse;
		m_specialAnimePrintType = m_animePrintType;
		m_specialCursorIsOnMessage = m_cursorIsOnMessage;

		GetInitGameParam(&m_specialAnimePatternKosuu,"specialAnimePatternNumber");
		GetInitGameParam(&m_specialAnimeFrame,"specialAnimeFrame");
		GetInitGameParam(&m_specialAnimeReverse,"specialAnimeReverse");
		GetInitGameParam(&m_specialAnimePrintType,"specialAnimePrintType");
		GetInitGameParam(&m_specialCursorIsOnMessage,"specialCursorIsOnMessage");


		if (GetInitGameString(&filenameSpecialCurosrPic,"filenameSpecialCursor"))
		{
			m_specialSelectPic = m_game->GetSystemPicture(filenameSpecialCurosrPic);
		}
		else
		{
			m_specialSelectPic = m_selectPic;
		}



		GetInitGameParam(&m_specialMessagePrintX,"specialmessagePrintX");
		GetInitGameParam(&m_specialMessagePrintY,"specialmessagePrintY");

		GetInitGameParam(&m_specialFontSize,"specialFontSize");

		m_specialCursorDeltaX = m_cursorDeltaX;
		m_specialCursorDeltaY = m_cursorDeltaY;
		m_specialCursorSizeX = m_cursorSizeX;
		m_specialCursorSizeY = m_cursorSizeY;
		GetInitGameParam(&m_specialCursorDeltaX,"specialCursorDeltaX");
		GetInitGameParam(&m_specialCursorDeltaY,"specialCursorDeltaY");
		GetInitGameParam(&m_specialCursorSizeX,"specialCursorSizeX");
		GetInitGameParam(&m_specialCursorSizeY,"specialCursorSizeY");
	}




	GetDisableQuickButtonSetup();
	GetDisableFreeButtonSetup();


//	GetInitGameParam(&m_fillColorR,"fillColorR");
//	GetInitGameParam(&m_fillColorG,"fillColorG");
//	GetInitGameParam(&m_fillColorB,"fillColorB");

//	GetInitGameParam(&m_nextMode,"nextMode");
	GetFadeInOutSetup();

	m_firstAppearCount = 0;
}


CCommonSelectMessage::~CCommonSelectMessage()
{
	End();
}

void CCommonSelectMessage::End(void)
{
//	ENDDELETECLASS(m_specialSelectPic);

	DELETEARRAY(m_specialCheckVar);
	DELETEARRAY(m_specialWindowPrintY);
	DELETEARRAY(m_specialWindowPrintX);

	ENDDELETECLASS(m_timerSuuji2);
	ENDDELETECLASS(m_timerSuuji);
	ENDDELETECLASS(m_timerPic);
}



int CCommonSelectMessage::Init(void)
{
	m_nowSelect = -1;
	m_maeSelect = -1;
	m_clickingFlag = FALSE;

	m_firstWait = 3;
	m_autoDebugWait = m_game->GetAutoDebugWait();

	m_selectAnimeCount = 0;

	m_windowOffFlag = FALSE;
	m_game->InitOptionButton();

//	m_firstAppearCount = 0;

	m_animePic1 = 0;
	m_animePic2 = 0;
	m_animePercent = 100;

	if (m_scrollSelectFlag)
	{
		m_page = 0;
		m_pageMax = m_addMessageKosuu + m_messageKosuu - m_messagePrintGyo + 1;
		if (m_pageMax<1) m_pageMax = 1;
		m_updown->SetPage(m_page);
		m_updown->SetPageMax(m_pageMax);
		m_updown->Init();
		LoadUpDownButtonPic();
	}


	if (m_timeLimit == 0)
	{
		if (m_windowPrintFlag)
		{
			char filename[256];
			wsprintf(filename,"sys\\%s",m_windowFileName);
			m_commonParts->LoadDWQ(filename);
		}
	}
	else
	{
		if (m_timeLimitWindowPrintFlag)
		{
			char filename[256];
			wsprintf(filename,"sys\\%s",m_timeLimitWindowFileName);
			m_commonParts->LoadDWQ(filename);
		}
	}


	//erase upper
///@@@	m_game->Erase();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (m_backPrintMode == 0)
	{
		CAllGraphics::FillScreen(m_backColorR,m_backColorG,m_backColorB);
	}
	else if (m_backPrintMode == 1)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s",m_filenameBack);
		m_commonBG->LoadDWQ(filename);
		m_commonBG->Put(0,0,FALSE);
	}

	m_commonBG->ReSize(screenSizeX,screenSizeY);
	m_commonBG->GetScreen();

	m_game->RestartLoopSoundAndVoice();

	m_lastKeyButton = -1;

	return -1;
}


int CCommonSelectMessage::Calcu(void)
{
	int codeByte = CMyFont::m_codeByte;

	if (m_firstAppearType != 0)
	{
		if (m_firstAppearCount < m_firstAppearTime)
		{
			m_firstAppearCount++;
			m_game->CalcuOptionButton();
			return -1;
		}
	}

	if (m_clickingFlag)
	{
		m_clickingCount--;
		if (m_clickingCount<=0)
		{
			int page = 0;
			if (m_scrollSelectFlag)
			{
				page = m_updown->GetPage();
			}

//			m_game->SearchCase(m_nowSelect);
			//m_game->SetYoyaku();
			m_exitModeFlag = TRUE;
			CheckAndAutoOff();
			return ReturnFadeOut(-1);
			return m_nowSelect;
		}
		else
		{
			return -1;
		}
	}



	int rt = NNNBUTTON_NOTHING;
	if (m_windowOffFlag == FALSE)
	{
		if (CheckOptionOk())
		{
			rt = m_game->CalcuOptionButton();
		}
	}



	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);
		if (nm == 0)
		{
			m_game->TaihiAllEffect();

//			m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_OK);
			m_game->SetSaveMode(SELECTMESSAGE_MODE);
			m_game->MakeMiniCG();
			m_game->SetCommonBackMode(SYSTEMMENU_MODE,SELECTMESSAGE_MODE);
			m_exitModeFlag = FALSE;
			return ReturnFadeOut(SYSTEMMENU_MODE);
		//	return SYSTEMMENU_MODE;
		}


		if (nm == 1)
		{
			m_exitModeFlag = FALSE;
			m_game->SetCommonBackMode(CONFIG_MODE,SELECTMESSAGE_MODE);
			return ReturnFadeOut(m_game->ChangeToSystemMode(CONFIG_MODE,m_classNumber));
		}

		if (nm == 2)
		{
			m_exitModeFlag = FALSE;
			m_game->SetCommonBackMode(BACKLOG_MODE,SELECTMESSAGE_MODE);
			return ReturnFadeOut(m_game->ChangeToSystemMode(BACKLOG_MODE,m_classNumber));
		}

		//free button
		if (nm == 3)
		{
			m_exitModeFlag = FALSE;
			m_game->SetCommonBackMode(SAVE_MODE,SELECTMESSAGE_MODE);
			return ReturnFadeOut(m_game->ChangeToSystemMode(SAVE_MODE,SELECTMESSAGE_MODE));
		}

		if (nm == 4)
		{
			m_exitModeFlag = FALSE;
			m_game->SetCommonBackMode(LOAD_MODE,SELECTMESSAGE_MODE);
			return ReturnFadeOut(m_game->ChangeToSystemMode(LOAD_MODE,SELECTMESSAGE_MODE));
		}
		
		if (nm == 5)//auto
		{
			int autoMode = m_game->GetSystemParam(NNNPARAM_AUTOMODE);
			m_game->SetSystemParam(NNNPARAM_AUTOMODE,1-autoMode);
		}
		if (nm == 6)//skip
		{
			m_game->SetMessageSkipFlag();
		}
		

		if (nm == 7)//windowoff
		{
			if (m_scrollSelectFlag)
			{
				if (m_pageMax>1)
				{
					m_updown->Init();
				}
			}

			if (m_windowOffSound != -1)
			{
				m_game->PlaySystemSound(m_windowOffSound-1);
			}
			m_windowOffFlag = !m_windowOffFlag;
			CAreaControl::SetNextAllPrint();

		}


		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_STARTCLICK) return -1;
		if (st == NNNBUTTON_CLICKING) return -1;
	}


	BOOL keyAction = FALSE;

	if (m_keyMoveEnable)
	{
		POINT pt = m_mouseStatus->GetZahyo();
		
		int keyDelta = 0;
		if (m_keyMoveUpDownEnable)
		{
			if (m_game->CheckClickKey(MYUP_KEY))
			{
				keyDelta = -1;
			}
			if (m_game->CheckClickKey(MYDOWN_KEY))
			{
				keyDelta = 1;
			}
		}

		if (m_keyMoveLeftRightEnable)
		{
			if (m_game->CheckClickKey(MYLEFT_KEY))
			{
				keyDelta = -1;
			}
			if (m_game->CheckClickKey(MYRIGHT_KEY))
			{
				keyDelta = 1;
			}
		}

		if (keyDelta == 1)
		{
			int mx = m_messagePrintGyo-1-m_addMessageKosuu;
			if (mx > m_messageKosuu - 1)
			{
				mx = m_messageKosuu - 1;
			}
			if (CheckSpecial())
			{
				mx = m_messageKosuu - 1;
			}


//			if (m_lastKeyButton < m_messagePrintGyo-1)
			if (m_lastKeyButton < mx)
			{
				m_lastKeyButton++;
				SetCursorToKeyArea(m_lastKeyButton);
				keyAction = TRUE;
			}
			else
			{
				if (m_scrollSelectFlag)
				{
					if (m_pageMax > 0)
					{
						if (m_page<m_pageMax-1)
						{
							m_page++;
							m_updown->SetPage(m_page);
							m_updown->Init();
							keyAction = TRUE;
						}
					}
				}

				SetCursorToKeyArea(m_lastKeyButton);
			}
		}
		else if (keyDelta == -1)
		{
			if (m_lastKeyButton > 0)
			{
				m_lastKeyButton--;
				SetCursorToKeyArea(m_lastKeyButton);
				keyAction = TRUE;
			}
			else
			{
				if (m_lastKeyButton < 0)
				{
					m_lastKeyButton = 0;
				}

				if (m_scrollSelectFlag)
				{
					if (m_pageMax > 0)
					{
						if (m_page>0)
						{
							m_page--;
							m_updown->SetPage(m_page);
							m_updown->Init();
							keyAction = TRUE;
						}
					}
				}

				SetCursorToKeyArea(m_lastKeyButton);
			}
		}
	}




	BOOL clickStart = FALSE;

	if (m_scrollSelectFlag)
	{
		if (CheckSpecial() == FALSE)
		{
			if (m_pageMax>0)
			{
				if (m_windowOffFlag == FALSE)
				{
					if (keyAction == FALSE)
					{
						int rt = m_updown->Calcu(m_inputStatus);
						if (rt != NNNBUTTON_NOTHING)
						{
							int nm = ProcessButtonGroup(rt);
							if (nm >= 0)
							{
								m_page = m_updown->GetPage();
								m_updown->Init();
								return -1;
							}

							int st = CCommonButton::GetButtonStatus(rt);
							if (st == NNNBUTTON_STARTCLICK)
							{
								clickStart = TRUE;
		//						return -1;
							}
							if (st == NNNBUTTON_CLICKING)
							{
								clickStart = TRUE;
		//						return -1;
							}
						}
					}
				}
			}
		}
	}

	POINT pt = m_mouseStatus->GetZahyo();
	int mouseX = pt.x;
	int mouseY = pt.y;
	int wheel = m_mouseStatus->GetWheel();


	if (m_scrollSelectFlag)
	{
//		int rt = m_updown->Calcu(m_mouseStatus);
	}

	m_maeSelect = m_nowSelect;

//	m_game->CalcuEffect();

	CalcuCursorAnime();



//	if (m_appearingFlag)
//	{
//		m_appearingCount--;
//		if (m_appearingCount>0) return -1;
//		m_appearingFlag = FALSE;
//	}



	if (m_windowOffFlag)
	{
		BOOL woff = CheckClick() || CheckClick(TRUE) || (m_game->CheckClickKey(WINDOWOFF_KEY));
		if (m_windowOffMouseButton != -1)
		{
			if (m_mouseStatus->CheckClick(m_windowOffMouseButton))
			{
				woff = TRUE;
			}
		}

//		if (CheckClick() || CheckClick(TRUE) || (m_game->CheckClickKey(WINDOWOFF_KEY)))
		if (woff)
		{

			if (m_scrollSelectFlag)
			{
				if (m_pageMax>1)
				{
					m_updown->Init();
				}
			}

			if (m_windowOnSound != -1)
			{
				m_game->PlaySystemSound(m_windowOnSound-1);
			}
			m_windowOffFlag = !m_windowOffFlag;
			CAreaControl::SetNextAllPrint();
		}
		return -1;
	}




//	m_maeOptionSelectNumber = m_nowOptionSelectNumber;
//	m_nowOptionSelectNumber = GetOnOptionButton(mouseX,mouseY);


	m_nowSelect = GetOnPlace(mouseX,mouseY);

	if (m_firstWait <= 0)
	{
		BOOL rtKey = FALSE;

		if (m_keyMoveEnable)
		{
			if (m_game->CheckClickKey(MESSAGEOKURI_KEY))
			{
				rtKey = TRUE;
			}
		}

		BOOL autoDebug = FALSE;
		int autoDebugSelect = m_game->GetAutoDebugMode();
		if (autoDebugSelect)
		{
			m_autoDebugWait--;
			if (m_autoDebugWait<=0)
			{
				int mx = m_messageKosuu;
				if (m_autoSelectControl != NULL)
				{

					autoDebug = TRUE;
					m_nowSelect = m_autoSelectControl->GetSelect(mx);

				}
			}
		}

		if (CheckClick() || rtKey || autoDebug)
		{
			if (m_nowSelect != -1)
			{
				int page = 0;
				if (m_scrollSelectFlag)
				{
					if (CheckSpecial() == FALSE)
					{
						page = m_updown->GetPage();
					}
				}

				if (autoDebug) page = 0;

	//			m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_OK);
				if (m_selectSound != -1)
				{
					m_game->PlaySystemSound(m_selectSound-1);
				}

				m_game->ChangePreColor(m_messageKosuu-m_nowSelect-page,m_backlogSelectColorR,m_backlogSelectColorG,m_backlogSelectColorB);
				if (codeByte == 2)
				{
					m_game->AddBackLogMessage("　　　　　　　　　　　　・",128,128,128);
					m_game->AddBackLogMessage("　　　　　　　　　　　　・",128,128,128);
					m_game->AddBackLogMessage("　　　　　　　　　　　　・",128,128,128);
				}
				else
				{
					m_game->AddBackLogMessage("                        .",128,128,128);
					m_game->AddBackLogMessage("                        .",128,128,128);
					m_game->AddBackLogMessage("                        .",128,128,128);
				}

				m_selected = m_nowSelect+1+page;

				m_clickingFlag = TRUE;
				m_clickingCount = m_clickingTime;

	//			m_game->SearchCase(m_nowSelect+1+page);
	//			m_game->SetYoyaku();

				CAreaControl::SetNextAllPrint();
				m_nowSelect = -1;
				return -1;
			}
		}




	///	int ms = m_messageWindow->Calcu();

		BOOL woff = m_game->CheckClickKey(WINDOWOFF_KEY);
		if (m_windowOffMouseButton != -1)
		{
			if (m_mouseStatus->CheckClick(m_windowOffMouseButton))
			{
				woff = TRUE;
			}
		}

//		if (CheckClick(TRUE) || (m_game->CheckClickKey(WINDOWOFF_KEY)))
		if (woff)
		{
			if (CheckTimeLimitActionOk())
			{
				if (m_windowOffSound != -1)
				{
					m_game->PlaySystemSound(m_windowOffSound-1);
				}

				m_windowOffFlag = !m_windowOffFlag;
				CAreaControl::SetNextAllPrint();
				return -1;
			}
		}
	}
	else
	{
		m_firstWait--;
	}

	if (m_windowOffFlag) return -1;
	
	if (m_backLogOk)
	{
		if (CheckTimeLimitActionOk())
		{
			if (m_windowOffFlag == FALSE)
			{
				if (wheel>0)
				{
					if (clickStart == FALSE)
					{
						if (keyAction == FALSE)
						{
							if (m_game->CheckWheelDisable() == FALSE)
							{
								m_game->TaihiAllEffect();
								if (m_backlogSound > 0)
								{
									m_game->PlaySystemSound(m_backlogSound-1);
								}
				//				m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_PON);
				//				if (m_back
								m_game->SetCommonBackMode(BACKLOG_MODE,SELECTMESSAGE_MODE);

								m_exitModeFlag = FALSE;
								return ReturnFadeOut(BACKLOG_MODE);
								//return BACKLOG_MODE;
							}
						}
					}
				}
			}
		}
	}

	m_nowSelectNumber = -1;
//	if (m_game->CheckSceneMode() == FALSE)
//	{
//		if (m_game->CheckOnOption(mouseX,mouseY)) m_nowSelectNumber = 0;
//	}


	//有効にする必要がある
	if (CheckOptionOk())
	{
		if (CheckTimeLimitActionOk())
		{
			int nextMode = m_game->ProcessGameKey(SELECTMESSAGE_MODE);
			if (nextMode != -1)
			{
				//fadeout?
				m_exitModeFlag = FALSE;
				return ReturnFadeOut(nextMode);
			}
		}
	}


	if (m_timeLimit>0)
	{
//		int frame = m_game->GetFrameTime();
//		if (frame == 0) frame = m_game->GetDefaultFrameTime();
//		if (frame <= 0) frame = 50;

//		m_timeLimitCount--;
//		m_timeLimitCount -= frame;
		m_timeLimitCount -= m_game->GetNowFrameCount();


		if (m_timeLimitCount<=0)
		{
			m_timeLimitCount = 0;
			if (m_autoSelect <= m_messageKosuu)
			{
				m_game->ChangePreColor(m_messageKosuu-(m_autoSelect-1),m_backlogSelectColorR,m_backlogSelectColorG,m_backlogSelectColorB);
			}

			if (codeByte == 2)
			{
				m_game->AddBackLogMessage("制限時間オーバー",255,64,128);
				m_game->AddBackLogMessage("　　　　　　　　　　　　・",128,128,128);
				m_game->AddBackLogMessage("　　　　　　　　　　　　・",128,128,128);
				m_game->AddBackLogMessage("　　　　　　　　　　　　・",128,128,128);
			}
			else
			{
				m_game->AddBackLogMessage("Time out",255,64,128);
				m_game->AddBackLogMessage("                        .",128,128,128);
				m_game->AddBackLogMessage("                        .",128,128,128);
				m_game->AddBackLogMessage("                        .",128,128,128);
			}

			m_exitModeFlag = TRUE;
			m_selected = m_autoSelect;
			CheckAndAutoOff();
			return ReturnFadeOut(-1);
//			m_game->SearchCase(m_autoSelect);
//			m_game->SetYoyaku();

//			CAreaControl::SetNextAllPrint();

		}
	}

	return -1;
}

int CCommonSelectMessage::Print(void)
{
	if (CheckSpecial())
	{
		CAreaControl::SetNextAllPrint();
	}
//	CAreaControl::SetNextAllPrint();

	if (m_scrollSelectFlag)
	{
		if (m_pageMax > 0)
		{
			CAreaControl::SetNextAllPrint();
		}
	}



	if (m_timeLimit>0)
	{
		CAreaControl::SetNextAllPrint();

//CAllGeo::BoxFill(0,0,m_timeLimit,30,255,0,0);
//CAllGeo::BoxFill(0,0,m_timeLimitCount,30,0,255,0);
	}


	BOOL b = CAreaControl::CheckAllPrintMode();

	if ((m_backPrintMode == 0) || (m_backPrintMode == 1))
	{
		if (b) m_commonBG->Put(0,0,FALSE);
	}
	else if (m_backPrintMode == 2)
	{
		m_game->CalcuEffectOnly();
		m_game->CountUpOnly();
		m_game->PrintEffect();
	}


#if defined _DEBUG
if (m_specialFlag)
{
	m_message->PrintMessage(0,0,"特殊選択肢モード");
}
#endif


//	if (m_windowOffFlag == FALSE)
//	{
//		m_game->PrintMessageWindow(b);
//	}

	if (m_windowOffFlag == FALSE)
	{
		int wps = 100 - m_game->GetSystemParam(NNNPARAM_WINDOWPERCENT);

		if (m_timeLimit == 0)
		{
			if (m_windowPrintFlag)
			{
				if (wps >= 100)
				{
					m_commonParts->Blt(m_windowPrintX,m_windowPrintY,0,0,m_windowSizeX,m_windowSizeY,TRUE);
				}
				else if (wps > 0)
				{
					m_commonParts->TransLucentBlt3(m_windowPrintX,m_windowPrintY,0,0,m_windowSizeX,m_windowSizeY,wps);
				}
			}
		}
		else
		{
			if (m_timeLimitWindowPrintFlag)
			{
				if (wps >= 100)
				{
					m_commonParts->Blt(m_timeLimitWindowPrintX,m_timeLimitWindowPrintY,0,0,m_timeLimitWindowSizeX,m_timeLimitWindowSizeY,TRUE);
				}
				else if (wps > 0)
				{
					m_commonParts->TransLucentBlt3(m_timeLimitWindowPrintX,m_timeLimitWindowPrintY,0,0,m_timeLimitWindowSizeX,m_timeLimitWindowSizeY,wps);
				}
			}
		}

		if (CheckSpecial())
		{
			//print special window
			for (int i=0;i<m_messageKosuu;i++)
			{
				int varNumber = m_specialCheckVar[i];
				int windowNumber = i;

				if (varNumber != -1)
				{
					int d = m_game->GetVarData(varNumber);
					if (d > 0)
					{
						windowNumber = d - 1;
					}
				}

				PrintSpecialWindow(i,windowNumber);
			}
		}
	}


	if (b)
	{
//		m_commonBG->GetScreen();
	}


	BOOL appearingFlag = FALSE;
	if (m_firstAppearType != 0)
	{
		if (m_firstAppearCount < m_firstAppearTime) appearingFlag = TRUE;
	}

	if (m_windowOffFlag == FALSE)
	{
		int page = 0;
		if (CheckSpecial() == FALSE)
		{
			if (m_scrollSelectFlag)
			{
				page = m_updown->GetPage();
			}
		}


		if (b || (m_clickingFlag) || appearingFlag)
		{
			int i = 0;
			for (i=0;i<m_addMessageKosuu;i++)
			{
				PrintMessageSub(i,i,TRUE,TRUE);
			}

			for (i=0;i<m_messageKosuu;i++)
			{
				if (((i+m_addMessageKosuu) < m_messagePrintGyo) || CheckSpecial())
				{
					PrintMessageSub(i,page+i);
				}
			}
		}
		else
		{
			//変更部分のみ

			if (m_nowSelect != m_maeSelect)
			{
				if (m_maeSelect != -1) PrintMessageSub(m_maeSelect,page+m_maeSelect,FALSE);
			}
			if (m_nowSelect != -1) PrintMessageSub(m_nowSelect,page+m_nowSelect);	//あにめするため
		}
	}


	int putX = m_optionPrintX;
	int putY = m_optionPrintY;
	int sizeX = m_optionSizeX;
	int sizeY = m_optionSizeY;
	int srcX = 0;
	int srcY = 0;

	if (m_nowOptionSelectNumber == 0)
	{
		srcX += sizeX;
	}


	if (appearingFlag == FALSE)
	{
		CalcuCursorAnime();
	}

	if (m_windowOffFlag == FALSE)
	{
//		m_optionPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
		CAreaControl::AddArea(putX,putY,sizeX,sizeY);
	}


	if (m_backPrintMode == 2)
	{
		m_game->PrintEffect(TRUE);
	}


	if (m_windowOffFlag == FALSE)
	{
//		m_game->SetCalendarFlag();
//		if (m_optionOk) m_game->SetOption();
		if (CheckTimeLimitActionOk())
		{
			m_game->PrintOptionButtonYoyaku();
		}
	}

	//test routine
	if (m_windowOffFlag == FALSE)
	{
		if (m_timeLimit>0)
		{
			if ((m_timerPrintType == 1) || (m_timerPrintType == 2))
			{
				int putX = m_timerPrintX;
				int putY = m_timerPrintY;
				int sizeX = m_timerPicSizeX;
				int sizeY = m_timerPicSizeY;
				int srcX = 0;
				int srcY = 0;

				int limDiv = m_timeLimit / 100;
				if (limDiv<1) limDiv = 1;

				if (m_timerBarHoukou == 0)
				{
					sizeY = (m_timerPicSizeY * (m_timeLimitCount/100)) / limDiv;
					int delta = m_timerPicSizeY - sizeY;
					srcY += delta;
					putY += delta;
				}
				else if (m_timerBarHoukou == 1)
				{
					sizeX = (m_timerPicSizeX * (m_timeLimitCount/100)) / limDiv;
				}
				else if (m_timerBarHoukou == 2)
				{
					sizeY = (m_timerPicSizeY * (m_timeLimitCount/100)) / limDiv;
				}
				else if (m_timerBarHoukou == 3)
				{
					sizeX = (m_timerPicSizeX * (m_timeLimitCount/100)) / limDiv;
					int delta = m_timerPicSizeX - sizeX;
					srcX += delta;
					putX += delta;
				}


				if (m_timerPrintType == 1)
				{
					int dv = m_timeLimit/100;
					int c = dv - m_timeLimitCount/100;
					if (c<0) c = 0;
					if (c>dv) c = dv;

					int r = m_timerColorR1 + ((m_timerColorR2 - m_timerColorR1) * c) / dv;
					int g = m_timerColorG1 + ((m_timerColorG2 - m_timerColorG1) * c) / dv;
					int b = m_timerColorB1 + ((m_timerColorB2 - m_timerColorB1) * c) / dv;

					if ((sizeX>0) && (sizeY>0))
					{
						CAllGeo::BoxFill(putX,putY,sizeX,sizeY,r,g,b);
					}
				}
				else
				{
					m_timerPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
				}
			}
			else if (m_timerPrintType == 3)
			{
				int dv = m_timeLimit/100;
				if (dv<1) dv = 1;
				int n = (m_timerPicKosuu * (m_timeLimitCount/100)) / dv;
				if (n<0) n = 0;
				if (n>=m_timerPicKosuu) n = m_timerPicKosuu-1;

				int sizeX = m_timerPicSizeX;
				int sizeY = m_timerPicSizeY;

				POINT block = GetSrcPoint(m_timerPic,n,sizeX,sizeY);
				
//				int srcX = sizeX * n;
//				int srcY = 0;
				int srcX = sizeX * block.x;
				int srcY = sizeY * block.y;

				m_timerPic->Blt(m_timerPrintX,m_timerPrintY,srcX,srcY,sizeX,sizeY,TRUE);
			}
			else if (m_timerPrintType == 4)
			{
				int haba = 1;
				if (m_timerPicKosuu>1)
				{
					haba = (m_timeLimit/100) / (m_timerPicKosuu-1);
				}
				if (haba<1) haba = 1;

				int n = (m_timeLimitCount/100) / haba;
				int amari = (m_timeLimitCount/100) % haba;
				if (n >= m_timerPicKosuu-1)
				{
					n = m_timerPicKosuu-1;
					amari = 0;
				}

				int sizeX = m_timerPicSizeX;
				int sizeY = m_timerPicSizeY;

				int n2 = n+1;
				if (amari == 0)
				{
					POINT block = GetSrcPoint(m_timerPic,n,sizeX,sizeY);

					m_timerPic->Blt(m_timerPrintX,m_timerPrintY,sizeX*block.x,sizeY*block.y,sizeX,sizeY,TRUE);
				}
				else
				{
					int ps = (100 * (haba-amari)) / haba;

					POINT block = GetSrcPoint(m_timerPic,n,sizeX,sizeY);
					POINT block2 = GetSrcPoint(m_timerPic,n2,sizeX,sizeY);


//					int srcY = 0;
//					int srcX1 = sizeX * n;
//					int srcX2 = sizeX * n2;
					int srcX1 = sizeX * block.x;
					int srcX2 = sizeX * block2.y;

					int srcY1 = sizeY * block.y;
					int srcY2 = sizeY * block2.y;


					int ps2 = 100 - ps;
					int* lpBuffer2 = (int*)(m_timerPic->GetBuffer());
					char* lpMask2 = (char*)(m_timerPic->GetMaskPic());
		
					int deltaX = srcX2 - srcX1;
//					int deltaY = 0;
					int deltaY = srcY2 - srcY1;

					SIZE sz = m_timerPic->GetPicSize();

					lpBuffer2 += deltaX;
					lpBuffer2 += deltaY * sz.cx;

					lpMask2 += deltaX;
					lpMask2 += deltaY * sz.cx;

//					m_timerPic->ChangeTranslateBlt(m_timerPrintX,m_timerPrintY,srcX1,srcY1,sizeX,sizeY,ps,ps2,lpBuffer2,lpMask2,m_timerPic);
					m_timerPic->ChangeTranslateBlt(m_timerPrintX,m_timerPrintY,srcX1,srcY1,sizeX,sizeY,ps,ps2,m_timerPic,srcX2,srcY2);

				}
			}

			if (m_timerSuujiPrintFlag == 1)
			{
				//フレーム数表示機能は削除
			}

			if (m_timerSuujiPrintFlag >= 2)
			{
				int d = m_timeLimitCount / 1000;
				int amari = m_timeLimitCount % 1000;

				m_timerSuuji->Print(m_timerSuujiPrintX,m_timerSuujiPrintY,d);

				if (m_timerSuujiPrintFlag >= 3)
				{
					int dv = 1;
					if (m_timerSuujiPrintFlag == 4) dv = 10;
					if (m_timerSuujiPrintFlag == 5) dv = 100;

					int sb = amari / dv;

					m_timerSuuji2->Print(m_timerSuujiPrintX2,m_timerSuujiPrintY2,sb);
				}
			}
		}
	}

	if (CheckSpecial() == FALSE)
	{
		if (m_scrollSelectFlag)
		{
			if (m_pageMax>0)
			{
				if (m_windowOffFlag == FALSE)
				{
					m_updown->Print();
				}
			}
		}
	}

	return -1;
}




void CCommonSelectMessage::CalcuCursorAnime(void)
{
	int animePatternKosuu = m_animePatternKosuu;
	int animeFrame = m_animeFrame;
	int animeReverse = m_animeReverse;
	if (CheckSpecial())
	{
		animePatternKosuu = m_specialAnimePatternKosuu;
		animeFrame = m_specialAnimeFrame;
		animeReverse = m_specialAnimeReverse;
	}


	m_selectAnimeCount++;

	int dv = animePatternKosuu;
	if (animeReverse) dv = (animePatternKosuu-1)*2;
	if (dv<1) dv = 1;

	m_selectAnimeCount %= (dv*animeFrame);

	int pic1 = m_selectAnimeCount / animeFrame;
	int pic2 = (pic1+1) % dv;

	if (animeReverse)
	{
		if (pic1>=animePatternKosuu) pic1 = (animePatternKosuu-1)*2 - pic1;
		if (pic2>=animePatternKosuu) pic2 = (animePatternKosuu-1)*2 - pic2;
	}

	m_animePic1 = pic1;
	m_animePic2 = pic2;

	int ps = (m_selectAnimeCount % animeFrame);
	ps *= 100;
	ps /= animeFrame;

	if (ps<0) ps = 0;
	if (ps>100) ps = 100;

	m_animePercent = 100-ps;
}






void CCommonSelectMessage::PrintMessageSub(int printN,int dataN,BOOL bAllFlag,BOOL addMessageFlag)
{
	if (dataN == -1) dataN = printN + m_addMessageKosuu;

	//erase

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	POINT messagePoint;
	POINT updatePoint;
	POINT cursorPoint;
	SIZE cursorSize = GetSelectCursorSize();

	if (addMessageFlag)
	{
		messagePoint = GetAddMessageZahyo(dataN);
		updatePoint = messagePoint;
		cursorPoint.x = 0;
		cursorPoint.y = 0;
	}
	else
	{
		messagePoint = GetMessageZahyo(printN);
		cursorPoint = GetSelectCursorZahyo(printN);
		updatePoint = cursorPoint;

		if (CheckSpecial())
		{
			if (m_centeringFlag)
			{
				int mesNum00 = dataN + m_addMessageKosuu;
				int lnln = m_message->GetMessageRealLength(m_messageData[mesNum00]);
				int mesSizeX = lnln * (m_specialFontSize + 1) - 1;

				int areaSizeX = m_centerAreaSizeX;//固定

				messagePoint.x += (areaSizeX - mesSizeX) / 2;
			}
		}
	}





	int putX = cursorPoint.x;
	int putY = cursorPoint.y;
//	if (addMessageFlag == FALSE)
//	{
//		putY += m_addMessageKosuu* m_messageNextY;
//	}

	int sizeX = cursorSize.cx;
	int sizeY = cursorSize.cy;

//	m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);


	if (addMessageFlag == FALSE)
	{
		if (printN == m_nowSelect)
		{
			int srcX = 0;
			int srcY1 = sizeY * m_animePic1;
			int srcY2= sizeY * m_animePic2;

			CPicture* lpPic = GetSelectCursorPic();

			if (lpPic != NULL)
			{
				if ((m_animePrintType == 0) || (m_animePercent == 100))
				{
					lpPic->Blt(putX,putY,srcX,srcY1,sizeX,sizeY,TRUE);
				}
				else
				{

					int ps2 = 100 - m_animePercent;
					int* lpBuffer2 = (int*)(lpPic->GetBuffer());
					char* lpMask2 = (char*)(lpPic->GetMaskPic());
			
					int deltaX = 0;
					int deltaY = srcY2 - srcY1;

					SIZE sz = m_selectPic->GetPicSize();

					lpBuffer2 += deltaX;
					lpBuffer2 += deltaY * sz.cx;

					lpMask2 += deltaX;
					lpMask2 += deltaY * sz.cx;

	//				m_selectPic->ChangeTranslateBlt(putX,putY,srcX,srcY1,sizeX,sizeY,m_animePercent,ps2,lpBuffer2,lpMask2,m_selectPic);
					lpPic->ChangeTranslateBlt(putX,putY,srcX,srcY1,sizeX,sizeY,m_animePercent,ps2,lpPic,srcX,srcY2);

				}
			}
		}
	}



//	putX -= m_cursorDeltaX;
//	putY -= m_cursorDeltaY; 

	putX = messagePoint.x;
	putY = messagePoint.y;
	int fontSize = m_fontSize;
	if (CheckSpecial())
	{
		if (addMessageFlag == FALSE)
		{
			fontSize = m_specialFontSize;
		}
	}

	int mesNum = dataN;
	if (addMessageFlag == FALSE) mesNum += m_addMessageKosuu;

	//print message
	if ((m_firstAppearCount >= m_firstAppearTime) || (m_firstAppearType == 0))
	{
		m_message->PrintMessage(putX,putY,&m_messageData[mesNum][0],fontSize,255,255,255,1,40,0,TRUE);
	}
	else
	{
		int startY = 0;
		int lengthY = fontSize;

		int dv = m_firstAppearTime;
		if (dv<1) dv = 1;
		int c = m_firstAppearCount;
		if (c>dv) c = dv;

		if (m_firstAppearType == 1)	//center
		{
			int dlt = ((fontSize / 2 ) * c) / dv;
			startY = fontSize / 2 - 1 - dlt;
			int endY = fontSize / 2 + dlt;

			if (startY<0) startY = 0;
			if (endY>=fontSize) endY = fontSize-1;

			lengthY = endY - startY + 1;
		}
		else if (m_firstAppearType == 2)		//upper
		{
			startY = 0;
			lengthY = (fontSize * c) / dv;
		}
		else if (m_firstAppearType == 3)		//lower
		{
			lengthY = (fontSize * c) / dv;
			startY = fontSize - lengthY;
		}

		m_message->PrintSelectMessage(startY,lengthY,putX,putY,&m_messageData[mesNum][0],fontSize,255,255,255,1,40,0,TRUE);
	}


	//updatearea
	//CAreaControl::AddArea(putX,putY,sizeX,sizeY);
	CAreaControl::AddArea(updatePoint.x, updatePoint.y, cursorSize.cx, cursorSize.cy);

}


int CCommonSelectMessage::GetOnPlace(int mouseX,int mouseY)
{
	int kosuu = m_messagePrintGyo - m_addMessageKosuu;
	if (CheckSpecial())
	{
		kosuu = m_messageKosuu;
	}


	SIZE sz = GetSelectCursorSize();
	for (int i=0;i<kosuu;i++)
	{
		POINT pt = GetSelectCursorZahyo(i);
		int x = mouseX - pt.x;
		int y = mouseY - pt.y;

		if ((x>=0) && (x<sz.cx) && (y>=0) && (y<sz.cy))
		{
			if (i<m_messageKosuu)
			{
				return i;
			}
		}
	}

	return -1;
}



LPSTR CCommonSelectMessage::GetMessagePointer(int n)
{
	return &m_messageData[n][0];
}

void CCommonSelectMessage::SetMessageData(int n,LPSTR mes)
{
	int ln = (int)strlen(mes);
	if (ln>254) ln = 254;
	if (ln<0) ln = 1;
	memcpy(&m_messageData[n][0],mes,ln);
	m_messageData[n][ln] = 0;
	m_messageData[n][ln+1] = 0;

	BOOL backlog = TRUE;

	if (CheckSpecial())
	{
		if (m_specialFlag == 2)
		{
			if (n<m_addMessageKosuu)
			{
				backlog = FALSE;
			}
		}
	}

	if (backlog)
	{
		m_game->AddBackLogMessage(mes);
	}


	m_firstAppearCount = 0;
}


/*
int CCommonSelectMessage::GetOnOptionButton(int mouseX, int mouseY)
{
	if (m_optionOk == 0) return -1;

	if (m_game->CheckOnOption(mouseX,mouseY)) return 0;

	return -1;

	int x,y;
	int sizeX,sizeY;
	int printX,printY;

	sizeX = m_optionSizeX;
	sizeY = m_optionSizeY;
	printX = m_optionPrintX;
	printY = m_optionPrintY;

	x = mouseX - printX;
	y = mouseY - printY;

	if ((x>=0) && (x<sizeX) && (y>=0) && (y<sizeY))
	{
//		if (m_optionPic->CheckOnPic(x,y)) return 0;
	}

	return -1;
}
*/



BOOL CCommonSelectMessage::CheckSpecial(void)
{
	if ((m_useSpecialFlagKosuu > 0) && (m_specialFlag))
	{
		return TRUE;
	}
	return FALSE;
}

POINT CCommonSelectMessage::GetSelectCursorZahyo(int place)
{
	POINT pt = GetMessageZahyo(place);
	POINT pt2 = GetSelectCursorDelta();
	pt.x += pt2.x;
	pt.y += pt2.y;
	return pt;
}


SIZE CCommonSelectMessage::GetSelectCursorSize(void)
{
	SIZE sz;
	if (CheckSpecial())
	{
		sz.cx = m_specialCursorSizeX;
		sz.cy = m_specialCursorSizeY;
	}
	else
	{
		sz.cx = m_cursorSizeX;
		sz.cy = m_cursorSizeY;
	}

	return sz;
}


POINT CCommonSelectMessage::GetSelectCursorDelta(void)
{
	POINT pt;
	if (CheckSpecial())
	{
		pt.x = m_specialCursorDeltaX;
		pt.y = m_specialCursorDeltaY;
	}
	else
	{
		pt.x = m_cursorDeltaX;
		pt.y = m_cursorDeltaY;
	}

	return pt;
}

POINT CCommonSelectMessage::GetSpecialWindowZahyo(int place)
{
	POINT pt;
	pt.x = m_specialWindowPrintX[(m_messageKosuu-1) * m_useSpecialFlagKosuu + place];
	pt.y = m_specialWindowPrintY[(m_messageKosuu-1) * m_useSpecialFlagKosuu + place];
	return pt;
}

POINT CCommonSelectMessage::GetMessageZahyo(int place)
{
	POINT pt;

	if (CheckSpecial())
	{
		pt = GetSpecialWindowZahyo(place);

		pt.x += m_specialMessagePrintX;
		pt.y += m_specialMessagePrintY;
	}
	else
	{
		pt.x = m_messagePrintX;
		pt.y = m_messagePrintY + (m_addMessageKosuu + place) * m_messageNextY;
	}

	return pt;
}


POINT CCommonSelectMessage::GetAddMessageZahyo(int place)
{
	POINT pt;

	pt.x = m_messagePrintX;
	pt.y = m_messagePrintY + place * m_messageNextY;

	return pt;
}

CPicture* CCommonSelectMessage::GetSelectCursorPic(void)
{
	if (CheckSpecial())
	{
		return m_specialSelectPic;
	}
	
	return m_selectPic;
}


void CCommonSelectMessage::SetBackLogMessage(void)
{
	int codeByte = CMyFont::m_codeByte;

	if (codeByte == 2)
	{
		m_game->AddBackLogMessage("　");
	}
	else
	{
		m_game->AddBackLogMessage(" ");
	}
	m_game->AddBackLogMessage(m_backlogMessage,m_backlogMessageColorR,m_backlogMessageColorG,m_backlogMessageColorB);
}


void CCommonSelectMessage::FinalExitRoutine(void)
{
	if (m_exitModeFlag)
	{
		m_game->SearchCase(m_selected);
		m_game->SetYoyaku();
	}
}

int CCommonSelectMessage::EndMode(void)
{
	return -1;

	if (m_exitModeFlag)
	{
		m_game->SearchCase(m_selected);
		m_game->SetYoyaku();
	}
	return -1;
}

void CCommonSelectMessage::SetTimeLimit(int timeLimit,int autoSelect)
{
	m_timeLimit = timeLimit;
	if (m_timeLimit < 0)
	{
		m_timeLimit = m_game->GetVarData(-m_timeLimit);
		if (m_timeLimit < 0) m_timeLimit = 0;
	}

	m_autoSelect = autoSelect;
	SetTimeLimitCount(m_timeLimit);
}

BOOL CCommonSelectMessage::CheckOptionOk(void)
{
	if (m_optionOk == 0) return FALSE;
	if (m_timeLimit == 0) return TRUE;
	
	if (m_timeLimitOptionOk) return TRUE;
	return FALSE;
}

void CCommonSelectMessage::PrintSpecialWindow(int place,int windowNumber)
{
	int sizeX = m_specialWindowSizeX;
	int sizeY = m_specialWindowSizeY;

	POINT src = GetSrcPoint2(m_specialWindowPic,windowNumber,sizeX,sizeY);

	int putX = m_specialWindowPrintX[(m_messageKosuu-1) * m_useSpecialFlagKosuu + place];
	int putY = m_specialWindowPrintY[(m_messageKosuu-1) * m_useSpecialFlagKosuu + place];

	m_specialWindowPic->Blt(putX,putY,src.x*sizeX,src.y*sizeY,sizeX,sizeY,TRUE);
}


POINT CCommonSelectMessage::GetSrcPoint(CPicture* lpPic,int n,int sizeX,int sizeY)
{
	POINT pt;
	SIZE sz = lpPic->GetPicSize();
	int dv = sizeX;
	if (dv<1) dv = 1;

	int dv2 = sizeY;
	if (dv2<1) dv2 = 1;

	int kosuuX = sz.cx / dv;
	int kosuuY = sz.cy / dv2;

	if (kosuuX<1) kosuuX = 1;
	if (kosuuY<1) kosuuY = 1;

	int nx = n % kosuuX;
	int ny = n / kosuuY;

	if (nx>=kosuuX) nx = kosuuX - 1;
	if (ny>=kosuuY) ny = kosuuY - 1;

	pt.x = nx;
	pt.y = ny;

	return pt;
}


POINT CCommonSelectMessage::GetSrcPoint2(CPicture* lpPic,int n,int sizeX,int sizeY)
{
	POINT pt;
	SIZE sz = lpPic->GetPicSize();
	int dv = sizeX;
	if (dv<1) dv = 1;

	int dv2 = sizeY;
	if (dv2<1) dv2 = 1;

	int kosuuX = sz.cx / dv;
	int kosuuY = sz.cy / dv2;

	if (kosuuX<1) kosuuX = 1;
	if (kosuuY<1) kosuuY = 1;

	int nx = n % kosuuX;
	int ny = (n / kosuuX) % kosuuY;

	if (nx>=kosuuX) nx = kosuuX - 1;
	if (ny>=kosuuY) ny = kosuuY - 1;

	pt.x = nx;
	pt.y = ny;

	return pt;
}

BOOL CCommonSelectMessage::CheckTimeLimitActionOk(void)
{
	if (m_timeLimit == 0)
	{
		return TRUE;
	}

	if (m_timeLimitOptionOk) return TRUE;
	return FALSE;

}

BOOL CCommonSelectMessage::CheckWindowOn(void)
{
	if (m_windowOffFlag) return FALSE;
	return TRUE;
}


void CCommonSelectMessage::SetCursorToKeyArea(int pl)
{
	POINT pt1 = GetSelectCursorZahyo(pl);
	SIZE sz = GetSelectCursorSize();


	int x = pt1.x + sz.cx / 2;
	int y = pt1.y + sz.cy / 2;

//	int x = m_messagePrintX + m_cursorDeltaX;
//	int y = m_messagePrintY + (pl + m_addMessageKosuu) * m_messageNextY + m_cursorDeltaY;
//	x += m_cursorSizeX / 2;
//	y += m_cursorSizeY / 2;

	POINT hotPoint = m_game->GetMouseHotPoint();
	POINT pt;
	pt.x = x - hotPoint.x;
	pt.y = y - hotPoint.y;

	ClientToScreen(m_game->GetGameHWND(),&pt);
	SetCursorPos(pt.x, pt.y);
}

int CCommonSelectMessage::GetOnKeyArea(POINT pt)
{
	return GetOnPlace(pt.x,pt.y);
}


int CCommonSelectMessage::KeyMoveAction(int delta,int deltaX,int deltaY)
{

	return -1;
}


void CCommonSelectMessage::CheckAndAutoOff(void)
{
	if (m_game->GetSystemParam(NNNPARAM_AUTOCONTINUESWITCH))
	{
		m_game->SetSystemParam(NNNPARAM_AUTOMODE,0);
	}
}

