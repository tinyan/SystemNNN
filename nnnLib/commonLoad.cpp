//
// commonLoad.cpp
//

#include <windows.h>
#include <stdio.h>



#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanEffectLib\effectstruct.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"

#include "commonGeneral.h"

#include "commonDataFile.h"

#include "commonSystemSoundName.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\scriptcommand.h"

#include "..\nnnUtilLib\commonKeyList.h"

#include "..\nnnUtilLib\myMessage.h"


#include "commonLoadSave.h"
#include "commonLoad.h"

#include "gameCallBack.h"



//char CCommonSave::m_defaultSuujiFileName[] = "ta_sl_font3";



CCommonLoad::CCommonLoad(CGameCallBack* lpGame) : CCommonLoadSave(lpGame,"load")
{
	SetClassNumber(LOAD_MODE);
//	m_classNumber = LOAD_MODE;

	m_loadSound = 1;
	m_cannotLoadSound = -1;
	GetInitGameParam(&m_loadSound,"loadSound");
	GetInitGameParam(&m_cannotLoadSound,"cannotLoadSound");

	m_loadVoiceKosuu = 0;
	m_cannotLoadVoiceKosuu = 0;
	GetInitGameParam(&m_loadVoiceKosuu,"loadVoiceNumber");
	GetInitGameParam(&m_cannotLoadVoiceKosuu,"cannotLoadVoiceNumber");
	m_loadVoice = NULL;
	m_cannotLoadVoice = NULL;
	
	if (m_loadVoiceKosuu > 0)
	{
		m_loadVoice = new LPSTR[m_loadVoiceKosuu];
		for (int i=0;i<m_loadVoiceKosuu;i++)
		{
			char name[256];
			wsprintf(name,"loadVoice%d",i+1);
			LPSTR filename = NULL;
			GetInitGameString(&filename,name);
			m_loadVoice[i] = filename;
		}
	}

	if (m_cannotLoadVoiceKosuu > 0)
	{
		m_cannotLoadVoice = new LPSTR[m_cannotLoadVoiceKosuu];
		for (int i=0;i<m_cannotLoadVoiceKosuu;i++)
		{
			char name[256];
			wsprintf(name,"cannotLoadVoice%d",i+1);
			LPSTR filename = NULL;
			GetInitGameString(&filename,name);
			m_cannotLoadVoice[i] = filename;
		}
	}



	GetInitGameParam(&m_quickLoadSelectOk,"quickLoadSelectOk");
}





CCommonLoad::~CCommonLoad()
{
	End();
}

void CCommonLoad::End(void)
{
	DELETEARRAY(m_cannotLoadVoice);
	DELETEARRAY(m_loadVoice);
}

int CCommonLoad::Init(void)
{
	m_lastPrintFlag = FALSE;
	return CCommonLoadSave::Init();
}

int CCommonLoad::Calcu(void)
{
//OutputDebugString("[calcu]");
	return CCommonLoadSave::Calcu();
}

int CCommonLoad::Print(void)
{
//OutputDebugString("[print]");
	if (m_loadCommandFlag && m_lastPrintFlag)
	{
//OutputDebugString("[lastprint]");

		CCommonLoadSave::Print();

//		CreateExitScreen();

//		m_exitScreen->Put(0,0,FALSE);

//		m_ppDataFile[m_clickButtonNumber]->Load(m_clickButtonNumber+m_page*m_blockX*m_blockY);
//		m_game->InitLoadGame();
//		CAreaControl::SetNextAllPrint();

		return -1;
	}

	return CCommonLoadSave::Print();
}

void CCommonLoad::CreateStartScreen(void)
{
	Print();
}


/*
int CCommonLoad::Init(void)
{
	char filename[256];

	if (m_backScriptFlag == FALSE)
	{
		LoadBG();
	}

	sprintf(filename,"sys\\%s",m_dialogFileName);
	m_commonParts->LoadDWQ(filename);

	m_upDownBack->Init();

	m_clickingFlag = FALSE;
	m_clickingCount = 0;
	m_warningFlag = FALSE;

	return -1;
}
*/

/*
int CCommonLoad::Calcu(void)
{
	if (m_warningFlag)
	{
		int wrt = m_button->Calcu(m_mouseStatus);
		if (wrt == MYBUTTON_NOTHING) return -1;

		//sound???
		int wst = wrt & MYBUTTON_STATUSMASK;
		int wnm = wrt & MYBUTTON_DATAMASK;

		if (wst == MYBUTTON_STARTCLICK)
		{
			if (wnm == 0)
			{
			}
			if (wnm == 1)
			{
			}
			
			return -1;
		}


		if (wst == MYBUTTON_NUMBER)
		{
			m_warningFlag = FALSE;

			m_button->Init();

			if (wnm == 0)
			{
//				m_fileControl->Load(m_LoadNumber);
				LoadBG();
				CAreaControl::SetNextAllPrint();
				return -1;
			}

			if (wnm == 1)
			{
				LoadBG();
				CAreaControl::SetNextAllPrint();
				return -1;
			}
		}

		return -1;
	}


//	int rt = m_fileControl->Calcu();

	int rt = -1;

	if (rt == 0)
	{
		m_game->FuqueAllEffect();
		return ReturnFadeOut(m_backMode);
	}

	if (rt > 0)
	{
		if (m_fileControl->CheckDataExist(rt-1))
		{
//@@@			m_game->PlayDialogVoice(1);

			m_LoadNumber = rt - 1;
			m_warningFlag = TRUE;
			m_game->Erase();
			m_commonParts->Blt(m_dialogX,m_dialogY,0,0,m_dialogSizeX,m_dialogSizeY,TRUE);
			m_commonBG->GetScreen();
			CAreaControl::SetNextAllPrint();
		}
		else
		{
			m_fileControl->Load(rt-1);
			m_game->LoadSystemFile();
			CAreaControl::SetNextAllPrint();
		}


	}

	return -1;
}

int CCommonLoad::Print(void)
{
	PrintBackScriptOrBG();

	BOOL b = CAreaControl::CheckAllPrintMode();

	if (m_warningFlag == FALSE)
	{
//		m_fileControl->Print(b);
	}
	else
	{
//		if (b)
		if (1)
		{
//			m_commonParts->Put(m_dialogX,m_dialogY,TRUE);
//			m_commonParts->Blt(m_dialogX,m_dialogY,0,0,m_dialogSizeX,m_dialogSizeY,TRUE);
		}

		if (b)
		{
//			m_commonBG->Blt(0,0,0,0,800,600,FALSE);
			m_commonBG->Put(0,0,FALSE);
		}

		m_button->Print(TRUE);
		CAreaControl::AddArea(m_dialogX,m_dialogY,m_dialogSizeX,m_dialogSizeY);
	}

	return -1;
}
*/

/*
void CCommonLoad::LoadBG(void)
{
	char filename[256];

	sprintf(filename,"sys\\%s",m_bgFileName);
	m_commonBG->LoadDWQ(filename);

}
*/



void CCommonLoad::FinalExitRoutine(void)
{
//OutputDebugString("[finalexit]");

	if (m_loadCommandFlag)
	{
//OutputDebugString("[finalexit::load]");

		CreateExitScreen();

		m_ppDataFile[m_clickButtonNumber]->Load(m_clickButtonNumber+m_page*m_blockX*m_blockY);
		m_game->SetLastSelectSaveLoad(m_clickButtonNumber + m_page * m_blockX*m_blockY);
		m_game->InitLoadGame();
		m_exitScreen->Put(0,0,FALSE);

		CAreaControl::SetNextAllPrint();
		m_lastPrintFlag = TRUE;
	}
//	return -1;
}

int CCommonLoad::EndMode(void)
{
	return -1;

	if (m_loadCommandFlag)
	{
		m_ppDataFile[m_clickButtonNumber]->Load(m_clickButtonNumber+m_page*m_blockX*m_blockY);
		m_game->InitLoadGame();
		CAreaControl::SetNextAllPrint();
		m_lastPrintFlag = TRUE;
	}
	return -1;
}

//not used
int CCommonLoad::ProcessDataClicked(int n)
{
	m_ppDataFile[m_clickButtonNumber]->Load(n+m_page*m_blockX*m_blockY);
	m_game->InitLoadGame();
	m_game->SetLastSelectSaveLoad(n + m_page * m_blockX*m_blockY);

	CAreaControl::SetNextAllPrint();
	return -1;
}

int CCommonLoad::ProcessStartClickExistData(int n)
{
	m_clickButtonNumber = n;
	m_clickingCount = 0;
	m_clickingFlag = TRUE;

	if (m_loadSound != -1)
	{
		m_game->PlaySystemSound(m_loadSound-1);
	}

	if (m_loadVoiceKosuu > 0)
	{
		int r = rand() % m_loadVoiceKosuu;
		LPSTR voice = m_loadVoice[r];
		if (voice != NULL)
		{
			m_game->ReplayVoice(voice);
		}
	}

	return -1;
}

int CCommonLoad::ProcessStartClickNotExistData(int n)
{
	if (m_cannotLoadSound != -1)
	{
		m_game->PlaySystemSound(m_cannotLoadSound-1);
	}

	if (m_cannotLoadVoiceKosuu > 0)
	{
		int r = rand() % m_cannotLoadVoiceKosuu;
		LPSTR voice = m_cannotLoadVoice[r];
		if (voice != NULL)
		{
			m_game->ReplayVoice(voice);
		}
	}


	return -1;
}

BOOL CCommonLoad::QuickLoad(void)
{
	m_ppDataFile[0]->LoadHeaderAndPic(m_quickLoadSlotNumber);
	if (m_ppDataFile[0]->CheckDataExist() == FALSE)
	{
		return FALSE;
	}

	if (m_ppDataFile[0]->CheckLoadOkVersion() == FALSE)
	{
		return FALSE;
	}


	//stop sound and music
	m_game->StopScriptSoundAndVoice();



	CreateExitScreen();
	
	m_game->SetLastSelectSaveLoad(m_quickLoadSlotNumber);

	m_ppDataFile[0]->Load(m_quickLoadSlotNumber);
	m_game->InitLoadGame();
	m_exitScreen->Put(0,0,FALSE);

	CAreaControl::SetNextAllPrint();

	return TRUE;
}


BOOL CCommonLoad::CheckQuickLoadDataExist(void)
{
	m_ppDataFile[0]->LoadHeaderAndPic(m_quickLoadSlotNumber);
	if (m_ppDataFile[0]->CheckDataExist() == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}

bool CCommonLoad::CheckExistSaveData(void)
{
	int n = m_pageMax * m_blockX * m_blockY;
	for (int i = 0; i < n; i++)
	{
		m_ppDataFile[0]->LoadHeaderAndPic(i);
		if (m_ppDataFile[0]->CheckDataExist())
		{
			return true;
		}
	}

	return false;
}

bool CCommonLoad::CheckExistSaveDataOne(int n)
{
//	int n = m_pageMax * m_blockX * m_blockY;
	m_ppDataFile[0]->LoadHeaderAndPic(n);
	if (m_ppDataFile[0]->CheckDataExist())
	{
		return true;
	}
	return false;
}


bool CCommonLoad::LoadDataOnly(int n)
{
	//stop sound and music
//	m_game->StopScriptSoundAndVoice();

//	CreateExitScreen();

//	m_game->SetLastSelectSaveLoad(m_quickLoadSlotNumber);

	m_ppDataFile[0]->Load(n);
//	m_game->InitLoadGame();

//	m_exitScreen->Put(0, 0, FALSE);

	CAreaControl::SetNextAllPrint();

	return true;
}

/*_*/

