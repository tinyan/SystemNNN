//
// CommonSelectObject.cpp
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
#include "..\nnnUtilLib\selectObjectSetup.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"

#include "..\nnnUtilLib\superButtonPicture.h"

#include "..\nnnUtilLib\printGameDate.h"

#include "commonMode.h"
#include "commonSystemParamName.h"


#include "commonSystemSoundName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"


#include "commonSelectObject.h"

#include "commonKeyList.h"

char m_defaultTypeVarName[] = "汎用選択種類";

char CCommonSelectObject::m_defaultAnswerName[] = "汎用選択番号";
char CCommonSelectObject::m_defaultAnswerCharaName[] = "汎用追加選択番号";


char CCommonSelectObject::m_defaultFileNameBG[] = "idou_bg";
char CCommonSelectObject::m_defaultFileNameChara[] = "ta_allchara";
char CCommonSelectObject::m_defaultFileNameCharaBase[] = "ta_chara";



CCommonSelectObject::CCommonSelectObject(CGameCallBack* lpGame,int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTOBJECT_MODE);
	LoadSetupFile("SelectObject",256);


	m_selectObjectMax = 256;

	m_selectObjectTypeVarNumber = -1;
	m_selectObjectResultVarNumber = -1;
	m_selectObjectAddResultVarNumber = -1;

	m_lastType = -1;




	m_existFlag = NULL;
	m_placeExistVarNumber = NULL;
	m_placeSelectOkVarNumber = NULL;
//	m_selectOkFlagWork = NULL;
	m_chara = NULL;
	m_placeCharaVarNumber = NULL;
	m_selectOk = NULL;
	m_placeButtonGroup = NULL;
	m_charaButtonGroup = NULL;
	m_onButtonVarNumber = -1;
//	m_printGameDate = NULL;


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


	GetInitGameParam(&m_selectObjectMax,"selectObjectMax");
	m_selectObjectSetup = new CSelectObjectSetup*[m_selectObjectMax+1];
	for (int i=0;i<m_selectObjectMax+1;i++)
	{
		m_selectObjectSetup[i] = NULL;
	}
	m_selectObjectType = -1;


	m_selectObjectTypeVarNumber = -1;
	LPSTR typeVarName = m_defaultTypeVarName;
	if (GetInitGameString(&typeVarName,"objectTypeVarName"))
	{
		m_selectObjectTypeVarNumber = m_game->GetVarNumber(typeVarName);
	}
	
	LPSTR onButtonVarName = NULL;
	if (GetInitGameString(&onButtonVarName,"onButtonVarName"))
	{
		m_onButtonVarNumber = m_game->GetVarNumber(onButtonVarName);
	}
	m_lastOnButton = -1;


	m_objectPictureMax = 0;
	m_addPictureMax = 0;
	m_objectPicture = NULL;
	m_addPicture = NULL;
	ExpandObjectPicture(64);
	ExpandAddPicture(64);


	m_chara = new int[1024];
	m_selectOk = new BOOL[1024];


	m_addPrintX = 0;
	m_addPrintY = 0;
	GetInitGameParam(&m_addPrintX,"addPrintX");
	GetInitGameParam(&m_addPrintY,"addPrintY");

//	m_placeKosuu = 1;
	//GetInitGameParam(&m_placeKosuu,"placeNumber");

//	m_placeAppearFlag = 0;
//	GetInitGameParam(&m_placeAppearFlag,"objectAppearFlag");

	m_charaFlag = 1;
//	GetInitGameParam(&m_charaFlag,"addObjectFlag");

	//m_returnCharaNumberFlag = 0;
	m_selectCharaOnlyFlag = 1;
	GetInitGameParam(&m_selectCharaOnlyFlag,"charaOnlyFlag");

	m_selectObjectResultVarNumber = -1;
	GetInitGameParam(&m_selectObjectResultVarNumber,"resultVarNumber");


	m_selectObjectAddResultVarNumber = -1;
	if (TRUE)
	{
		LPSTR name = m_defaultAnswerCharaName;
		GetInitGameString(&name,"resultAddVarName");
		m_selectObjectAddResultVarNumber = m_game->GetVarNumber(name);
	}

	m_charaPrintUpper = 1;
	GetInitGameParam(&m_charaPrintUpper,"charaPrintUpper");

//	m_selectOkFlag = 0;
//	GetInitGameParam(&m_selectOkFlag,"selectFlag");


	LPSTR name = m_defaultAnswerName;
	GetInitGameString(&name,"resultVarName");
	m_selectObjectResultVarNumber = m_game->GetVarNumber(name);





	m_placeExistVarNumber = NULL;
	m_placeCharaVarNumber = NULL;





	m_existFlag = NULL;



	m_placeSelectOkVarNumber = NULL;
//	m_selectOkFlagWork = NULL;
//	if (m_selectOkFlag)
//	{
//	}


//	m_chara = NULL;
//	m_charaMove = NULL;

//	m_allCharaFlag = 0;
//	m_charaPic = NULL;
//	m_charaPicPattern = NULL;


	m_onButtonChangeToRestartBackScript = 0;
	GetInitGameParam(&m_onButtonChangeToRestartBackScript,"onButtonChangeToRestartBackScript");


	m_filenameBG = m_defaultFileNameBG;
	GetInitGameString(&m_filenameBG,"filenameBG");



	m_placeButtonGroup = NULL;

	m_autoPicLoad = 0;
	m_lastAutoPic = -1;
	m_autoPicRestartBackScript = 0;
	GetInitGameParam(&m_autoPicLoad,"autoPicLoad");
	if (m_autoPicLoad)
	{
		m_autoCannotOk = 0;
		GetInitGameParam(&m_autoCannotOk,"autoPicCannotOk");
		GetInitGameParam(&m_autoPicRestartBackScript,"autoPicRestartBackScript");
		for (int i=0;i<32;i++)
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



CCommonSelectObject::~CCommonSelectObject()
{
	End();
}

void CCommonSelectObject::End(void)
{

	ENDDELETECLASS(m_charaButtonGroup);
	ENDDELETECLASS(m_placeButtonGroup);


	DELETEARRAY(m_selectOk);
	DELETEARRAY(m_chara);


//	DELETEARRAY(m_existFlag);

	ENDDELETECLASS(m_printGameDate);


	if (m_addPicture != NULL)
	{
		for (int i=0;i<m_addPictureMax;i++)
		{
			ENDDELETECLASS(m_addPicture[i]);
		}
		DELETEARRAY(m_addPicture);
	}

	if (m_objectPicture != NULL)
	{
		for (int i=0;i<m_objectPictureMax;i++)
		{
			ENDDELETECLASS(m_objectPicture[i]);
		}

		DELETEARRAY(m_objectPicture);
	}



	if (m_selectObjectSetup != NULL)
	{
		for (int i=0;i<m_selectObjectMax+1;i++)
		{
			ENDDELETECLASS(m_selectObjectSetup[i]);
		}

		DELETEARRAY(m_selectObjectSetup);
	}
}

void CCommonSelectObject::StartUserCommand(int paraKosuu,int* paraPtr)
{
	if (paraKosuu > 0)
	{
		int type = *paraPtr;
		//set var data
		if (m_selectObjectTypeVarNumber != -1)
		{
			m_game->SetVarData(m_selectObjectTypeVarNumber,type);
		}
	}
}


int CCommonSelectObject::Init(void)
{
	m_selectObjectType = m_game->GetVarData(m_selectObjectTypeVarNumber);
	if ((m_selectObjectType < 1) && (m_selectObjectType > m_selectObjectMax))
	{
		//error
		m_selectObjectType = 1;
	}


	CSelectObjectSetup* setup = NULL;
	if (m_selectObjectSetup[m_selectObjectType] == NULL)
	{
		m_selectObjectSetup[m_selectObjectType] = new CSelectObjectSetup(m_selectObjectType);
		setup = m_selectObjectSetup[m_selectObjectType];

		int objectNumber = setup->m_objectNumber;
		for (int i=0;i<objectNumber;i++)
		{
			char name[256];
			wsprintf(name,"objectAppearVarName%d",i+1);

			LPSTR varName = NULL;
			if (setup->GetInitGameString(&varName,name))
			{
				int var = m_game->GetVarNumber(varName);
				setup->m_placeExistVarNumber[i] = var;
			}

			wsprintf(name,"objectSelectOkVarName%d",i+1);
			if (setup->GetInitGameString(&varName,name))
			{
				int var = m_game->GetVarNumber(varName);
				setup->m_placeSelectOkVarNumber[i] = var;
			}
		}

		int addNumber = setup->m_addObjectNumber;
		for (int i=0;i<addNumber;i++)
		{
			char name[256];
			wsprintf(name,"addVarName%d",i+1);

			LPSTR varName = NULL;
			if (setup->GetInitGameString(&varName,name))
			{
				int var = m_game->GetVarNumber(varName);
				setup->m_addVarNumber[i] = var;
			}

		}


	}




	setup = m_selectObjectSetup[m_selectObjectType];

	if (m_lastType != m_selectObjectType)
	{
		//re create button and addButton
		ENDDELETECLASS(m_placeButtonGroup);
		ENDDELETECLASS(m_charaButtonGroup);


		int objectNumber = setup->m_objectNumber;
		m_placeButtonGroup = new CCommonButtonGroup(setup->m_nameList,objectNumber,NULL,"object");

		for (int i=0;i<objectNumber;i++)
		{
			CPicture* lpPic = GetObjectPicture(i);

			m_placeButtonGroup->SetPicture(i,lpPic);
		}

		int addNumber = setup->m_addObjectNumber;
		if (addNumber > 0)
		{
			m_charaButtonGroup = new CCommonButtonGroup(setup->m_nameList,addNumber,NULL,"add");
		}

		for (int i=0;i<addNumber;i++)
		{
			CPicture* lpPic = GetAddPicture(i);

			m_charaButtonGroup->SetPicture(i,lpPic);
		}

		m_lastType = m_selectObjectType;
	}

	int objectNumber = setup->m_objectNumber;
	int addNumber = setup->m_addObjectNumber;
	
	for (int i=0;i<objectNumber;i++)
	{
		m_chara[i] = 0;
	}

	for (int i=0;i<addNumber;i++)
	{
		BOOL existFlag = FALSE;

		int var = setup->m_addVarNumber[i];
		if (var != -1)
		{
			int place = m_game->GetVarData(var);
			if ((place > 0) && (place <= objectNumber))
			{
				m_chara[place-1] = i+1;
				existFlag = TRUE;

				//zahyo
				POINT pt = m_placeButtonGroup->GetZahyo(place-1);
				POINT pt2 = setup->GetAddPrint(i);
				pt.x += m_addPrintX;
				pt.y += m_addPrintY;
				pt.x += pt2.x;
				pt.y += pt2.y;
				m_charaButtonGroup->SetZahyo(i,pt);

				//enable
				int var2 = setup->m_placeExistVarNumber[place-1];
				BOOL enableFlag = TRUE;
				if (var2 != -1)
				{
					if (m_game->GetVarData(var2) == 0)
					{
						enableFlag = FALSE;
					}
				}
				m_charaButtonGroup->SetEnable(i,enableFlag);
			}
		}

		m_charaButtonGroup->SetExist(i,existFlag);

		
	}



	for (int i=0;i<objectNumber;i++)
	{
		BOOL existFlag = TRUE;
		int var = setup->m_placeExistVarNumber[i];
		if (var != -1)
		{
			if (m_game->GetVarData(var) == 0)
			{
				existFlag = FALSE;
			}
		}

		BOOL flag = TRUE;
		var = setup->m_placeSelectOkVarNumber[i];
		if (var != -1)
		{
			if (m_game->GetVarData(var) == 0)
			{
				flag = FALSE;
			}
		}

		BOOL f = flag && existFlag;
		if (setup->m_addOnlyFlag)
		{
			if (m_chara[i] == 0)
			{
				f = FALSE;
			}
		}

		m_placeButtonGroup->SetExist(i,existFlag);
		m_placeButtonGroup->SetEnable(i,f);

		m_selectOk[i] = f;
	}


	m_firstWait = 3;
	m_lastOnButton = -1;
	if (m_autoPicLoad)
	{
		for (int i=0;i<32;i++)
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
		LPSTR bg2 = setup->m_filenameBG;
		if (bg2 != NULL)
		{
			wsprintf(filename,"sys\\%s",bg2);
		}
		else
		{
			wsprintf(filename,"sys\\%s",m_filenameBG);
		}

		m_commonBG->LoadDWQ(filename);
	}

	m_game->InitOptionButton();


	for (int i=0;i<objectNumber;i++)
	{
		CCommonButton* button = m_placeButtonGroup->GetButton(i);
		if (button->GetExist())
		{
			CPicture* lpPic = m_placeButtonGroup->GetPicture(i);
			LPSTR name = m_placeButtonGroup->GetFileName(i);
			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);
		}
	}

	m_placeButtonGroup->Init();

	for (int i=0;i<addNumber;i++)
	{
		CCommonButton* button = m_charaButtonGroup->GetButton(i);
		if (button->GetExist())
		{
			CPicture* lpPic = m_charaButtonGroup->GetPicture(i);
			LPSTR name = m_charaButtonGroup->GetFileName(i);
			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);
		}
	}

	m_selectedNumber = -1;

	if (m_charaButtonGroup != NULL)
	{
		m_charaButtonGroup->Init();
	}

	m_lastKeyButton = 0;
	if (m_keyMoveEnable)
	{
		for (int i=0;i<objectNumber;i++)
		{
			if (m_selectOk[i])
			{
				m_lastKeyButton = i;
				break;
			}
		}
	}

	if (objectNumber>0)
	{
		m_lastKeyButton -= 1;
		m_lastKeyButton += objectNumber;
		m_lastKeyButton %= objectNumber;
	}


//	m_game->SetOptionVarOn();

	return -1;
}


int CCommonSelectObject::Calcu(void)
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





	rt = -1;

	if (m_firstWait <= 0)
	{
		if (m_charaButtonGroup != NULL)
		{
			rt = m_charaButtonGroup->Calcu(m_inputStatus);
		}
	}
	else
	{
		m_firstWait--;
	}

	if (rt != NNNBUTTON_NOTHING)
	{

		int nm = ProcessButtonGroup(rt);
		if (nm >= 0)
		{
			CSelectObjectSetup* setup = m_selectObjectSetup[m_selectObjectType];
			int objectNumber = setup->m_objectNumber;
			for (int i=0;i<objectNumber;i++)
			{
				if (m_chara[i] == nm + 1)
				{
					m_selectedNumber = i;
					m_exitModeFlag = TRUE;
					return ReturnFadeOut(-1);
				}
			}
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

	/*
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
	*/


	return -1;
}

int CCommonSelectObject::Print(void)
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

	m_placeButtonGroup->Print(TRUE);
	if (m_charaButtonGroup != NULL)
	{
		m_charaButtonGroup->Print(TRUE);
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


/*
POINT CCommonSelectObject::GetAreaZahyo(int n)
{
	POINT pt = m_areaZahyo[n];
	return pt;
}
*/



/*
BOOL CCommonSelectObject::CheckSelectOk(int n)
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
*/



void CCommonSelectObject::ParentFinalExitRoutine(void)
{
	if (m_autoPicLoad)
	{
		for (int i=0;i<32;i++)
		{
			if (m_autoPicLayer[i])
			{
				m_game->SetDontLoadDWQ(i,0);
			}
		}
	}
}


void CCommonSelectObject::FinalExitRoutine(void)
{

	if (m_exitModeFlag)
	{
		m_game->SetVarData(m_selectObjectResultVarNumber,m_selectedNumber + 1);
		if (m_selectObjectAddResultVarNumber != -1)
		{
			m_game->SetVarData(m_selectObjectAddResultVarNumber,m_chara[m_selectedNumber]);
		}


//		m_game->ShakinHensai();

		m_game->SetYoyaku();
	}
}

int CCommonSelectObject::EndMode(void)
{
	return -1;

	/*
	if (m_exitModeFlag)
	{
		m_game->SetVarData(m_selectPlaceResultVarNumber,m_selectedNumber + 1);


		m_game->SetYoyaku();
	}
	*/

	return -1;
}




void CCommonSelectObject::CreateStartScreen(void)
{
	Print();
}






int CCommonSelectObject::GetOnPlace(POINT pt,BOOL cannotOk)
{
	CSelectObjectSetup* setup = m_selectObjectSetup[m_selectObjectType];

	int objectNumber = setup->m_objectNumber;


	for (int i=0;i<objectNumber;i++)
	{
		BOOL f = cannotOk;
		if (f == FALSE)
		{
//			if (CheckSelectOk(i))
			if (m_selectOk[i])
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

void CCommonSelectObject::MoveCursorToPlaceButton(int pl)
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

void CCommonSelectObject::LoadAutoPic(int place,BOOL checkRestartFlag)
{
	if (m_autoPicLoad == 0) return;
	if (place == m_lastAutoPic) return;

	for (int i=0;i<32;i++)
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

CPicture* CCommonSelectObject::GetObjectPicture(int n)
{
	if (n >= m_objectPictureMax)
	{
		int delta = n - m_objectPictureMax + 1;
		if (delta < 64) delta = 64;
		ExpandObjectPicture(delta);
	}
	
	if (m_objectPicture[n] == NULL)
	{
		m_objectPicture[n] = new CPicture();
	}

	return m_objectPicture[n];
}

CPicture* CCommonSelectObject::GetAddPicture(int n)
{
	if (n >= m_addPictureMax)
	{
		int delta = n - m_addPictureMax + 1;
		if (delta < 64) delta = 64;
		ExpandAddPicture(delta);
	}

	if (m_addPicture[n] == NULL)
	{
		m_addPicture[n] = new CPicture();
	}

	return m_addPicture[n];
}

void CCommonSelectObject::ExpandObjectPicture(int n)
{
	int newNumber = m_objectPictureMax + n;
	CPicture** tmp = new CPicture*[newNumber];
	for (int i = m_objectPictureMax;i < newNumber;i++)
	{
		tmp[i] = NULL;
	}
	if (m_objectPicture != NULL)
	{
		for (int i=0;i<m_objectPictureMax;i++)
		{
			tmp[i] = m_objectPicture[i];
		}
		delete [] m_objectPicture;
	}
	m_objectPicture = tmp;
	m_objectPictureMax = newNumber;
}

void CCommonSelectObject::ExpandAddPicture(int n)
{
	int newNumber = m_addPictureMax + n;
	CPicture** tmp = new CPicture*[newNumber];
	for (int i = m_addPictureMax;i < newNumber;i++)
	{
		tmp[i] = NULL;
	}
	if (m_addPicture != NULL)
	{
		for (int i=0;i<m_addPictureMax;i++)
		{
			tmp[i] = m_addPicture[i];
		}
		delete [] m_addPicture;
	}
	m_addPicture = tmp;
	m_addPictureMax = newNumber;
}





