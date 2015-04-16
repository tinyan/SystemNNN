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


#include "commonPrintTerm.h"

#include "commonKeyList.h"



CCommonPrintTerm::CCommonPrintTerm(CGameCallBack* lpGame,int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTTERM_MODE);
	LoadSetupFile("PrintTerm",256);


	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;



	GetDisableQuickButtonSetup();
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
	GetAddLayerSetup();
	GetAnimeLayerSetup();
}



CCommonPrintTerm::~CCommonPrintTerm()
{
	End();
}

void CCommonPrintTerm::End(void)
{

}


int CCommonPrintTerm::Init(void)
{

	return -1;
}


int CCommonPrintTerm::Calcu(void)
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






	return -1;
}

int CCommonPrintTerm::Print(void)
{
	CAreaControl::SetNextAllPrint();

	PrintBackScriptOrBG();


	m_game->PrintOptionButtonYoyaku();

	return -1;
}







void CCommonPrintTerm::FinalExitRoutine(void)
{

	if (m_exitModeFlag)
	{
		m_game->SetYoyaku();
	}
}

int CCommonPrintTerm::EndMode(void)
{
	return -1;

	/*
	if (m_exitModeFlag)
	{
		m_game->SetVarData(m_selectPlaceResultVarNumber,m_selectedNumber + 1);


		m_game->SetYoyaku();
	}
	*/

}




void CCommonPrintTerm::CreateStartScreen(void)
{
	Print();
}










