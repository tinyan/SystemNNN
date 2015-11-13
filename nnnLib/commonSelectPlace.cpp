//
// commonSelectPlace.cpp
//


#include <windows.h>



#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"

#include "..\nnnUtilLib\superButtonPicture.h"

#include "..\nnnUtilLib\printGameDate.h"

#include "commonMode.h"
#include "commonSystemParamName.h"


#include "commonSystemSoundName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"


#include "commonSelectPlace.h"

#include "commonKeyList.h"


char CCommonSelectPlace::m_defaultAnswerName[] = "場所選択番号";
char CCommonSelectPlace::m_defaultAnswerCharaName[] = "キャラ選択番号";

char CCommonSelectPlace::m_defaultFileNameBG[] = "idou_bg";
char CCommonSelectPlace::m_defaultFileNameChara[] = "ta_allchara";
char CCommonSelectPlace::m_defaultFileNameCharaBase[] = "ta_chara";



CCommonSelectPlace::CCommonSelectPlace(CGameCallBack* lpGame,int extMode) : CCommonGeneral(lpGame)
{
	int i = 0;

	m_existFlag = NULL;
	m_placeExistVarNumber = NULL;
	m_placeSelectOkVarNumber = NULL;
	m_selectOkFlagWork = NULL;
	m_charaPic = NULL;
	m_chara = NULL;
	m_placeCharaVarNumber = NULL;
	m_placeCharaVarNumber = NULL;
	m_charaMove = NULL;
	m_charaPicPattern = NULL;
	m_selectOk = NULL;
	m_areaZahyo = NULL;
	m_charaDelta = NULL;
	m_placeButtonGroup = NULL;
	m_onButtonVarNumber = -1;
//	m_printGameDate = NULL;


	if (extMode == 0)
	{
		SetClassNumber(SELECTPLACE_MODE);
//		m_classNumber = SELECTPLACE_MODE;
		LoadSetupFile("SelectPlace",256);
	}
	else
	{
		SetClassNumber(SELECTPLACE2_MODE + (extMode - 1));
//		m_classNumber = SELECTPLACE2_MODE + (extMode - 1);
		char sname[256];
		wsprintf(sname,"SelectPlace%d",extMode+1);
		LoadSetupFile(sname,256);
	}

	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;


	GetKeyMoveSetup();

	m_backLogOk = 0;
	GetInitGameParam(&m_backLogOk,"backLogOk");
	if (m_backLogOk)
	{
		m_game->SetBackLogOk(m_classNumber);
	}



	LPSTR onButtonVarName = NULL;
	if (GetInitGameString(&onButtonVarName,"onButtonVarName"))
	{
		m_onButtonVarNumber = m_game->GetVarNumber(onButtonVarName);
	}



	m_lastOnButton = -1;

//for programmer and scripter setup
	m_placeKosuu = 1;
	GetInitGameParam(&m_placeKosuu,"placeNumber");

	m_placeAppearFlag = 0;
	GetInitGameParam(&m_placeAppearFlag,"placeAppearFlag");

	m_charaFlag = 0;
	GetInitGameParam(&m_charaFlag,"charaFlag");
	m_returnCharaNumberFlag = 0;
	m_selectCharaOnlyFlag = 1;
	GetInitGameParam(&m_selectCharaOnlyFlag,"charaOnlyFlag");

	if (m_charaFlag)
	{
		GetInitGameParam(&m_returnCharaNumberFlag,"returnCharaNumberFlag");
		if (m_returnCharaNumberFlag)
		{
			LPSTR name = m_defaultAnswerCharaName;
			GetInitGameString(&name,"selectedCharaVarName");
			m_selectCharaResultVarNumber = m_game->GetVarNumber(name);
		}

		m_charaPrintUpper = 1;
		GetInitGameParam(&m_charaPrintUpper,"charaPrintUpper");
	}

	m_selectOkFlag = 0;
	GetInitGameParam(&m_selectOkFlag,"selectFlag");




	LPSTR name = m_defaultAnswerName;	//場所選択番号
	GetInitGameString(&name,"selectedPlaceVarName");
	m_selectPlaceResultVarNumber = m_game->GetVarNumber(name);


	m_placeExistVarNumber = NULL;
	m_placeCharaVarNumber = NULL;


//	m_placeName = new LPSTR [m_placeKosuu];


	m_buttonMode = 1;
	GetInitGameParam(&m_buttonMode,"buttonMode");	//0:normal(old type) :1:superButton
	m_buttonMode = 1;	//1のみサポート


	m_existFlag = NULL;
	if (m_placeAppearFlag)
	{
		m_existFlag = new BOOL[m_placeKosuu];
		m_placeExistVarNumber = new int[m_placeKosuu];
		for (int i=0;i<m_placeKosuu;i++)
		{
			m_placeExistVarNumber[i] = -1;
			char name[256];
			wsprintf(name,"placeAppearVarName%d",i+1);

			LPSTR defaultName = NULL;
			GetInitGameString(&defaultName,name);

			if (defaultName != NULL)
			{
				m_placeExistVarNumber[i] = m_game->GetVarNumber(defaultName);
			}
		}
	}



	m_placeSelectOkVarNumber = NULL;
	m_selectOkFlagWork = NULL;
	if (m_selectOkFlag)
	{
		m_placeSelectOkVarNumber = new int[m_placeKosuu];
		m_selectOkFlagWork = new BOOL[m_placeKosuu];
		
		for (int i=0;i<m_placeKosuu;i++)
		{
			m_placeSelectOkVarNumber[i] = -1;


			char name[256];
			wsprintf(name,"placeSelectOkVarName%d",i+1);

			LPSTR defaultName = NULL;

			GetInitGameString(&defaultName,name);

			if (defaultName != NULL)
			{
				m_placeSelectOkVarNumber[i] = m_game->GetVarNumber(defaultName);
			}
		}
	}


	m_chara = NULL;
	m_charaMove = NULL;

	m_allCharaFlag = 0;
	m_charaPic = NULL;
	m_charaPicPattern = NULL;

	m_onButtonChangeToRestartBackScript = 0;
	GetInitGameParam(&m_onButtonChangeToRestartBackScript,"onButtonChangeToRestartBackScript");


	if (m_charaFlag)
	{
		GetInitGameParam(&m_allCharaFlag,"allCharaFlag");
		if (m_allCharaFlag == 0)
		{
			m_charaPic = new CPicture*[m_placeKosuu];
			for (int i=0;i<m_placeKosuu;i++)
			{
				m_charaPic[i] = new CPicture();
			}

			m_charaPicName = m_defaultFileNameCharaBase;
			GetInitGameString(&m_charaPicName,"fileNameCharaBase");
		}

		m_chara = new int [m_placeKosuu];
		m_placeCharaVarNumber = new int[m_placeKosuu];
		m_charaMove = new POINT[m_placeKosuu];
		m_charaPicPattern = new int[m_placeKosuu];

		for (int i=0;i<m_placeKosuu;i++)
		{
			m_charaPicPattern[i] = 0;
			m_charaMove[i].x = 0;
			m_charaMove[i].y = 0;

			m_placeCharaVarNumber[i] = -1;

			char name[256];
			wsprintf(name,"placeCharaVarName%d",i+1);


			LPSTR defaultName = NULL;
			GetInitGameString(&defaultName,name);

			if (defaultName != NULL)
			{
				m_placeCharaVarNumber[i] = m_game->GetVarNumber(defaultName);
			}
		}

	}


	m_allCharaFileName = m_defaultFileNameChara;
	GetInitGameString(&m_allCharaFileName,"fileNameAllChara");

	m_selectOk = new BOOL[m_placeKosuu];


	m_filenameBG = m_defaultFileNameBG;
	GetInitGameString(&m_filenameBG,"filenameBG");


	m_areaZahyo = new POINT[m_placeKosuu];
	m_charaDelta = new POINT[m_placeKosuu];

	//chara
	m_charaDeltaX = 0;
	m_charaDeltaY = 0;
	m_charaSizeX = 32;
	m_charaSizeY = 32;
	m_charaCustomFlag = 0;
	m_charaAnimePattern = 1;
	m_charaAnimeSpeed = 1;
	m_charaAnimeType = 1;

	if (m_charaFlag)
	{
		GetInitGameParam(&m_charaDeltaX,"charaX");
		GetInitGameParam(&m_charaDeltaY,"charaY");
		GetInitGameParam(&m_charaSizeX,"charaSizeX");
		GetInitGameParam(&m_charaSizeY,"charaSizeY");
		GetInitGameParam(&m_charaCustomFlag,"charaCustomFlag");
		GetInitGameParam(&m_charaAnimePattern,"charaAnimePattern");
		GetInitGameParam(&m_charaAnimeSpeed,"charaAnimeSpeed");
		GetInitGameParam(&m_charaAnimeType,"charaAnimeType");
	}



	for (i=0;i<m_placeKosuu;i++)
	{
		m_areaZahyo[i].x = 0;
		m_areaZahyo[i].y = 0;
		m_charaDelta[i].x = m_charaDeltaX;
		m_charaDelta[i].y = m_charaDeltaY;

		//area
		char name[256];
		wsprintf(name,"areaX%d",i+1);
		int xx = 0;
		GetInitGameParam(&xx,name);
		m_areaZahyo[i].x = xx;

		wsprintf(name,"areaY%d",i+1);
		int yy = 0;
		GetInitGameParam(&yy,name);
		m_areaZahyo[i].y = yy;


		//chara
		if (m_charaCustomFlag)
		{
			wsprintf(name,"charaX%d",i+1);
			int x = m_charaDelta[i].x;
			GetInitGameParam(&x,name);
			m_charaDelta[i].x = x;

			wsprintf(name,"charaY%d",i+1);
			int y = m_charaDelta[i].y;
			GetInitGameParam(&y,name);
			m_charaDelta[i].y = y;
		}
	}


	m_placeButtonGroup = NULL;
	m_useEffectPicKosuu = 3;
	m_useSuperPicKosuu = 0;
	if (m_backScriptFlag) m_useEffectPicKosuu = 16;

	if (m_buttonMode)
	{
		CPicture* lpBG = m_commonBG;
		if (m_backScriptFlag || m_mustAllPrintFlag) lpBG = NULL;

		m_placeButtonGroup = new CCommonButtonGroup(m_setup,m_placeKosuu,lpBG,"place");

		for (int i=0;i<m_placeKosuu;i++)
		{
			CPicture* lpPic = GetUseOkPicture();
			m_placeButtonGroup->SetPicture(i,lpPic);
		}
	}

	m_autoPicLoad = 0;
	m_lastAutoPic = -1;
	m_autoPicRestartBackScript = 0;
	GetInitGameParam(&m_autoPicLoad,"autoPicLoad");
	if (m_autoPicLoad)
	{
		m_autoCannotOk = 0;
		GetInitGameParam(&m_autoCannotOk,"autoPicCannotOk");
		GetInitGameParam(&m_autoPicRestartBackScript,"autoPicRestartBackScript");
		for (int i=0;i<16;i++)
		{
			m_autoPicLayer[i] = 0;
			m_autoPicTag[i] = NULL;

			char name[256];
			wsprintf(name,"autoPicLayerTag%d",i);
			LPSTR tagName = NULL;
			if (GetInitGameString(&tagName,name))
			{
				if ((*tagName) != 0)
				{
					m_autoPicTag[i] = tagName;
					m_autoPicLayer[i] = 1;
				}
			}
		}
	}

	GetDisableQuickButtonSetup();
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
	GetAddLayerSetup();
	GetAnimeLayerSetup();
}



CCommonSelectPlace::~CCommonSelectPlace()
{
	End();
}

void CCommonSelectPlace::End(void)
{


	ENDDELETECLASS(m_placeButtonGroup);




	DELETEARRAY(m_charaDelta);
	DELETEARRAY(m_areaZahyo);
	DELETEARRAY(m_selectOk);


	DELETEARRAY(m_charaPicPattern);
	DELETEARRAY(m_charaMove);
	DELETEARRAY(m_placeCharaVarNumber);
	DELETEARRAY(m_chara);


	if (m_charaPic != NULL)
	{
		for (int i=0;i<m_placeKosuu;i++)
		{
			ENDDELETECLASS(m_charaPic[i]);
		}
		DELETEARRAY(m_charaPic);
	}


	DELETEARRAY(m_selectOkFlagWork);
	DELETEARRAY(m_placeSelectOkVarNumber);

	DELETEARRAY(m_placeExistVarNumber);
	DELETEARRAY(m_existFlag);

	ENDDELETECLASS(m_printGameDate);
}


int CCommonSelectPlace::Init(void)
{
	m_firstWait = 3;
	m_lastOnButton = -1;
	if (m_autoPicLoad)
	{
		for (int i=0;i<16;i++)
		{
			if (m_autoPicLayer[i])
			{
				m_game->SetDontLoadDWQ(i);
			}
		}

		m_lastAutoPic = -1;
		if (m_onButtonVarNumber != -1)
		{
			m_game->SetVarData(m_onButtonVarNumber,m_lastOnButton+1);
		}

		LoadAutoPic(0,FALSE);
	}
	else
	{
		if (m_onButtonVarNumber != -1)
		{
			m_game->SetVarData(m_onButtonVarNumber,m_lastOnButton+1);
		}
	}

	char filename[256];
	if (m_backScriptFlag == FALSE)
	{
		wsprintf(filename,"sys\\%s",m_filenameBG);
		m_commonBG->LoadDWQ(filename);
	}

	if (m_charaFlag)
	{
		if (m_allCharaFlag)
		{
			wsprintf(filename,"sys\\%s",m_allCharaFileName);
			m_commonParts->LoadDWQ(filename);
		}
	}

	m_game->InitOptionButton();


	int i = 0;
	for (i=0;i<m_placeKosuu;i++)
	{
		if (m_placeAppearFlag)
		{
			m_existFlag[i] = m_game->GetVarData(m_placeExistVarNumber[i]);
		}

		if (m_selectOkFlag)
		{
			m_selectOkFlagWork[i] = m_game->GetVarData(m_placeSelectOkVarNumber[i]);
		}

		if (m_charaFlag)
		{
			m_chara[i] = -1;
			BOOL b = TRUE;
			if (m_placeAppearFlag)
			{
				if (m_existFlag[i] == FALSE)
				{
					b = FALSE;
				}
			}

			if (m_selectOkFlag)
			{
				if (m_selectOkFlagWork[i] == FALSE)
				{
					b = FALSE;
				}
			}


			if (b)
			{
				m_chara[i] = m_game->GetVarData(m_placeCharaVarNumber[i]);

				if (m_chara[i] > 0)
				{
					if (m_allCharaFlag == 0)
					{
						char filename[256];
						wsprintf(filename,"sys\\%s%d",m_charaPicName,m_chara[i]);
						m_charaPic[i]->LoadDWQ(filename);
					}
				}
			}
		}

		m_selectOk[i] = CheckSelectOk(i);
	}


	if (m_buttonMode)
	{
		for (i=0;i<m_placeKosuu;i++)
		{
			CPicture* lpPic = m_placeButtonGroup->GetPicture(i);
			LPSTR name = m_placeButtonGroup->GetFileName(i);
			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);

			BOOL b = TRUE;
			if (m_placeAppearFlag)
			{
				if (m_existFlag[i] == 0)
				{
					b = FALSE;
				}
			}

			if (b)
			{
				m_placeButtonGroup->SetExist(i,TRUE);
				if (m_selectOk[i])
				{
					m_placeButtonGroup->SetEnable(i,TRUE);
				}
				else
				{
					m_placeButtonGroup->SetEnable(i,FALSE);
				}
			}
			else
			{
				m_placeButtonGroup->SetExist(i,FALSE);
			}
		}

		m_placeButtonGroup->Init();
	}

	m_charaAnimeCount = 0;

//	m_maeSelectNumber = -1;
//	m_nowSelectNumber = -1;
	m_selectedNumber = -1;

	m_lastKeyButton = 0;
	if (m_keyMoveEnable)
	{
		for (i=0;i<m_placeKosuu;i++)
		{
			if (CheckSelectOk(i))
			{
				m_lastKeyButton = i;
				break;
			}
		}
	}
	if (m_placeKosuu>0)
	{
		m_lastKeyButton -= 1;
		m_lastKeyButton += m_placeKosuu;
		m_lastKeyButton %= m_placeKosuu;
	}


//	m_game->SetOptionVarOn();

	return -1;
}


int CCommonSelectPlace::Calcu(void)
{
	int rt = m_game->CalcuOptionButton();

	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);
		if (nm == 0)
		{
		//	return m_game->ChangeToSystemMode(SYSTEMMENU_MODE,m_classNumber);
			m_exitModeFlag = FALSE;
			return ReturnFadeOut(m_game->ChangeToSystemMode(SYSTEMMENU_MODE,m_classNumber));
	//		m_game->TaihiAllEffect();

//			m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_OK);
	//		m_game->SetSaveMode(m_classNumber);
	//		m_game->MakeMiniCG();
	//		m_game->SetCommonBackMode(SYSTEMMENU_MODE,m_classNumber);
	//		return ReturnFadeOut(SYSTEMMENU_MODE);
		}

		if (nm == 1)
		{
			m_exitModeFlag = FALSE;
			m_game->SetCommonBackMode(CONFIG_MODE,m_classNumber);
			return ReturnFadeOut(m_game->ChangeToSystemMode(CONFIG_MODE,m_classNumber));
		}
		if (nm == 2)
		{
			m_exitModeFlag = FALSE;
			m_game->SetCommonBackMode(BACKLOG_MODE,m_classNumber);
			return ReturnFadeOut(m_game->ChangeToSystemMode(BACKLOG_MODE,m_classNumber));
		}



		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_STARTCLICK) return -1;
		if (st == NNNBUTTON_CLICKING) return -1;
	}




	rt = -1;

	if (m_firstWait <= 0)
	{
		rt = m_placeButtonGroup->Calcu(m_inputStatus);
	}
	else
	{
		m_firstWait--;
	}

	if ((m_autoPicLoad) || (m_onButtonVarNumber != -1))
	{
		POINT pt = m_mouseStatus->GetZahyo();
		int old = m_lastOnButton;
		m_lastOnButton = GetOnPlace(pt,m_autoCannotOk);


		if (m_onButtonChangeToRestartBackScript)
		{
			if (old != m_lastOnButton)
			{
				if (m_onButtonVarNumber != -1)
				{
					m_game->SetVarData(m_onButtonVarNumber,m_lastOnButton+1);
					m_game->RestartBackScript();
				}
			}
		}

	}


	if (rt != NNNBUTTON_NOTHING)
	{




		int nm = ProcessButtonGroup(rt);
		if (nm >= 0)
		{
			m_selectedNumber = nm;
			m_exitModeFlag = TRUE;
			return ReturnFadeOut(-1);
		}
	}

	if (m_backLogOk)
	{
		int wheel = m_mouseStatus->GetWheel();
		if (wheel > 0)
		{
			if (m_game->CheckWheelDisable() == FALSE)
			{
				m_exitModeFlag = FALSE;
				m_game->SetCommonBackMode(BACKLOG_MODE,m_classNumber);
				return ReturnFadeOut(m_game->ChangeToSystemMode(BACKLOG_MODE,m_classNumber));
			}
		}
	}

	int nextMode = m_game->ProcessGameKey(m_classNumber);
	if (nextMode != -1)
	{
		m_exitModeFlag = FALSE;
		return ReturnFadeOut(nextMode);
	}

	if (m_keyMoveEnable)
	{
		POINT pt = m_mouseStatus->GetZahyo();
		int pl = GetOnPlace(pt,m_keyMoveCannotSelectOk);

		if (m_game->CheckClickKey(MESSAGEOKURI_KEY))
		{
			if (pl >= 0)
			{
				if (CheckSelectOk(pl))
				{
					CCommonButton* button = m_placeButtonGroup->GetButton(pl);
					button->StartClick();
					return -1;
				}
			}
		}

		if (pl>=0)
		{
			m_lastKeyButton = pl;
		}

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

		if (keyDelta != 0)
		{
			int pl2 = m_lastKeyButton;
			BOOL found = FALSE;

			for (int i=0;i<m_placeKosuu;i++)
			{
				if (m_placeKosuu > 0)
				{
					pl2 += keyDelta;
					pl2 += m_placeKosuu;
					pl2 %= m_placeKosuu;
				}

				if (m_placeAppearFlag)
				{
					if (m_existFlag[pl2] == FALSE)
					{
						continue;
					}
				}

				if (m_keyMoveCannotSelectOk == 0)
				{
					if (CheckSelectOk(pl2))
					{
						found = TRUE;
						break;
					}
				}

			}

			if (found)
			{
				m_lastKeyButton = pl2;
				MoveCursorToPlaceButton(pl2);
			}
		}
	}

	return -1;
}

int CCommonSelectPlace::Print(void)
{
	CAreaControl::SetNextAllPrint();

	if (m_onButtonVarNumber != -1)
	{
		m_game->SetVarData(m_onButtonVarNumber,m_lastOnButton+1);
	}

	if (m_autoPicLoad)
	{
		if (m_lastOnButton == -1)
		{
			LoadAutoPic(0);
		}
		else
		{
			LoadAutoPic(m_lastOnButton+1);
		}
	}



	PrintBackScriptOrBG();

	PrintBeforeButton();

	if (m_gameLayerFirst)
	{
		PrintGameLayer();
	}
	if (m_animeLayerFirst)
	{
		PrintAnimeLayer();
	}

	if (m_charaFlag)
	{
		if (m_charaPrintUpper == 0)
		{
			PrintAllChara();
		}
	}

	m_placeButtonGroup->Print(TRUE);

	if (m_charaFlag)
	{
		if (m_charaPrintUpper)
		{
			PrintAllChara();
		}
	}

	if (!m_gameLayerFirst)
	{
		PrintGameLayer();
	}
	if (!m_animeLayerFirst)
	{
		PrintAnimeLayer();
	}


	PrintAfterButton();

	m_game->PrintOptionButtonYoyaku();

	return -1;
}



POINT CCommonSelectPlace::GetAreaZahyo(int n)
{
	POINT pt = m_areaZahyo[n];
	return pt;
}


POINT CCommonSelectPlace::GetCharaZahyo(int n)
{
	POINT pt = GetAreaZahyo(n);
	POINT pt2 = m_charaDelta[n];

	pt.x += pt2.x;
	pt.y += pt2.y;

	if (m_charaMove != NULL)
	{
		POINT pt3 = m_charaMove[n];
		pt.x += pt3.x;
		pt.y += pt3.y;
	}

	return pt;
}



BOOL CCommonSelectPlace::CheckSelectOk(int n)
{
	if (m_placeAppearFlag)
	{
		if (m_existFlag[n] == FALSE) return FALSE;
	}

	if (m_selectOkFlag)
	{
		if (m_selectOkFlagWork[n] == FALSE) return FALSE;
	}

	if (m_charaFlag)
	{
		if (m_selectCharaOnlyFlag)
		{
			if (m_chara[n] <= 0) return FALSE;
		}
	}

	return TRUE;
}



void CCommonSelectPlace::ParentFinalExitRoutine(void)
{
	if (m_autoPicLoad)
	{
		for (int i=0;i<16;i++)
		{
			if (m_autoPicLayer[i])
			{
				m_game->SetDontLoadDWQ(i,0);
			}
		}
	}
}


void CCommonSelectPlace::FinalExitRoutine(void)
{

	if (m_exitModeFlag)
	{
		m_game->SetVarData(m_selectPlaceResultVarNumber,m_selectedNumber + 1);


//		m_game->ShakinHensai();

		m_game->SetYoyaku();
	}
}

int CCommonSelectPlace::EndMode(void)
{
	return -1;

	if (m_exitModeFlag)
	{
		m_game->SetVarData(m_selectPlaceResultVarNumber,m_selectedNumber + 1);


		m_game->SetYoyaku();
	}
	return -1;
}


CPicture* CCommonSelectPlace::GetUseOkPicture(void)
{
	CPicture* lpPic = NULL;
	if (m_useEffectPicKosuu < 16)
	{
		lpPic = m_game->GetEffectPicture(m_useEffectPicKosuu);
		m_useEffectPicKosuu++;
	}
	else
	{
		lpPic = CSuperButtonPicture::GetPicture(m_useSuperPicKosuu);
		m_useSuperPicKosuu++;
	}
	return lpPic;
}


void CCommonSelectPlace::CreateStartScreen(void)
{
	Print();
}



void CCommonSelectPlace::PrintAllChara(void)
{
	int type = m_charaAnimeType;
	int speed = m_charaAnimeSpeed;
	int count = m_charaAnimeCount;
	int pattern = m_charaAnimePattern;


	if (speed<1) speed = 1;

	int revFlag = 0;
	int dv = pattern;

	if ((type == 3) || (type == 4) || (type == 7) || (type == 8))
	{
		dv = (pattern-1) * 2;
		if (dv<1) dv = 1;
		revFlag = 1;
	}

	dv *= speed;

	int limitFlag = 0;
	if ((type == 2) || (type == 4) || (type == 6) || (type == 8))
	{
		limitFlag = 1;
	}

	count += 1;
	if (limitFlag)
	{
		if (count >= dv) count = dv;
		if ((type == 2) || (type == 6))
		{
			if (count >= (dv-speed))
			{
				count = dv - speed;
				if (count<0) count = 0;
			}
		}
	}
	else
	{
		count %= dv;
	}

	m_charaAnimeCount = count;




	int pic1 = count / speed;
	int pic2 = pic1+1;
	
	if (limitFlag)
	{
		int limData = dv-1;
		if (revFlag) limData = dv;

		if (pic1>=dv) pic1 = limData;
		if (pic2>=dv) pic2 = limData;
	}

//	pic1 %= dv;
//	pic2 %= dv;

	int percent = 100;


	if (revFlag)
	{
		if (pic1 >= pattern) pic1 = (pattern-1)*2 - pic1;
		if (pic2 >= pattern) pic2 = (pattern-1)*2 - pic2;
	}

	if (type >= 5)
	{
		percent = 100 * (speed - (count - ((count / speed) * speed)));
		percent /= speed;
	}

	pic1 %= pattern;
	pic2 %= pattern;

	int sizeX = m_charaSizeX;
	int sizeY = m_charaSizeY;

	for (int i=0;i<m_placeKosuu;i++)
	{
		if (m_selectOk[i])
		{
			int ch = m_chara[i];
			if (ch > 0)
			{
				POINT pt = GetCharaZahyo(i);
				int putX = pt.x;
				int putY = pt.y;



				CPicture* lpPic = m_commonParts;
				
				ch--;
				int srcX1 = sizeX * ch;
				int srcX2 = srcX1;
				int srcY1 = sizeY * (pic1 + m_charaAnimePattern*m_charaPicPattern[i]);
				int srcY2 = sizeY * (pic2 + m_charaAnimePattern*m_charaPicPattern[i]);

				if (m_allCharaFlag)
				{
				}
				else
				{
					lpPic = m_charaPic[i];
					srcX1 = sizeX * pic1;
					srcX2 = sizeX * pic2;
					srcY1 = sizeY * m_charaPicPattern[i];
					srcY2 = sizeY * m_charaPicPattern[i];
				}



				if (percent == 100)
				{
					lpPic->Blt(putX,putY,srcX1,srcY1,sizeX,sizeY,TRUE);
				}
				else if (percent == 0)
				{
					lpPic->Blt(putX,putY,srcX2,srcY2,sizeX,sizeY,TRUE);
				}
				else
				{
					int ps2 = 100 - percent;
//					int* lpBuffer2 = (int*)(lpPic->GetBuffer());
//					char* lpMask2 = (char*)(lpPic->GetMaskPic());
	
				//	int deltaX = 0;
				//	int deltaY = srcY2 - srcY1;

					if (m_allCharaFlag == 0)
					{
				//		deltaX = srcX2 - srcX1;
				//		deltaY = 0;
					}

//					SIZE sz = lpPic->GetPicSize();

//					lpBuffer2 += deltaX;
//					lpBuffer2 += deltaY * sz.cx;

//					lpMask2 += deltaX;
//					lpMask2 += deltaY * sz.cx;


//					m_commonParts->ChangeTranslateBlt(putX,putY,srcX,srcY1,sizeX,sizeY,percent,ps2,lpBuffer2,lpMask2,m_commonParts);
					lpPic->ChangeTranslateBlt(putX,putY,srcX1,srcY1,sizeX,sizeY,percent,ps2,lpPic,srcX2,srcY2);

				}
			}
		}
	}
}

void CCommonSelectPlace::SetCharaPicPattern(int n,int pat)
{
	if (m_charaPicPattern != NULL)
	{
		m_charaPicPattern[n] = pat;
	}
}

void CCommonSelectPlace::SetCharaMoveDelta(int n,POINT pt)
{
	if (m_charaMove != NULL)
	{
		m_charaMove[n] = pt;
	}
}



int CCommonSelectPlace::GetOnPlace(POINT pt,BOOL cannotOk)
{
	for (int i=0;i<m_placeKosuu;i++)
	{
		BOOL f = cannotOk;
		if (f == FALSE)
		{
			if (CheckSelectOk(i))
			{
				f = TRUE;
			}
		}

		if (f)
		{
			CCommonButton* button = m_placeButtonGroup->GetButton(i);
			if (button != NULL)
			{
				if (button->CheckOnButtonPic(pt))
				{
					return i;
				}
			}
		}
	}

	return -1;
}

void CCommonSelectPlace::MoveCursorToPlaceButton(int pl)
{
	POINT pt = m_placeButtonGroup->GetZahyo(pl);
	CCommonButton* button = m_placeButtonGroup->GetButton(pl);

	SIZE sz = button->GetSize();

	POINT pt2;
	pt2.x = pt.x + sz.cx / 2;
	pt2.y = pt.y + sz.cy / 2;


	POINT hotPoint = m_game->GetMouseHotPoint();

	pt2.x -= hotPoint.x;
	pt2.y -= hotPoint.y;

	ClientToScreen(m_game->GetGameHWND(),&pt2);

	SetCursorPos(pt2.x, pt2.y);
}

void CCommonSelectPlace::LoadAutoPic(int place,BOOL checkRestartFlag)
{
	if (m_autoPicLoad == 0) return;
	if (place == m_lastAutoPic) return;

	for (int i=0;i<16;i++)
	{
		if (m_autoPicLayer[i])
		{
			LPSTR tagName = m_autoPicTag[i];
			if (tagName != NULL)
			{
				char filename[1024];
				char dirName[3];
				dirName[2] = 0;
				memcpy(dirName,tagName,2);
				wsprintf(filename,"%s\\%s%d",dirName,tagName,place);
				CPicture* lpPic = m_game->GetEffectPicture(i);
				if (lpPic != NULL)
				{
					lpPic->LoadDWQ(filename);
				}
			}
		}
	}

	m_lastAutoPic = place;
	if (checkRestartFlag)
	{
		if (m_autoPicRestartBackScript)
		{
			m_game->RestartBackScript();
		}
	}
}




