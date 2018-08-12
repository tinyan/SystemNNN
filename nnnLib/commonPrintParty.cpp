//
// CommonPrintItem.cpp
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
#include "..\nnnUtilLib\commonRadioButtonGroup.h"

#include "..\nnnUtilLib\commonBackButton.h"
#include "..\nnnUtilLib\commonUpDownButtonGroup.h"
#include "..\nnnUtilLib\commonUpDownBack.h"

#include "..\nnnUtilLib\superButtonPicture.h"
#include "..\nnnUtilLib\nameList.h"

#include "..\nnnUtilLib\mymessage.h"

#include "..\nnnUtilLib\commonAnimeParts.h"


#include "..\nnnUtilLib\printGameDate.h"
#include "..\nnnUtilLib\haveItemData.h"

#include "commonMode.h"
#include "commonSystemParamName.h"


#include "commonSystemSoundName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"


#include "..\nnnUtilLib\commonPartyStatusData.h"
#include "commonPrintParty.h"

#include "commonKeyList.h"



CCommonPrintParty::CCommonPrintParty(CGameCallBack* lpGame,int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTPARTY_MODE);
	LoadSetupFile("PrintParty",256);

	m_message = m_game->GetMyMessage();

	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;
	GetInitGameString(&m_filenameBG,"filenameBG");


	m_oldVersion = 0;
	GetInitGameParam(&m_oldVersion, "oldVersion");


	m_partyStatusData = NULL;


	m_partyStatusData = new CCommonPartyStatusData(m_setup,m_message);
	m_partyNumber = m_partyStatusData->GetPartyNumber();
	m_printNumberMax = m_partyStatusData->GetPrintNumberMax();
	m_statusNumber = m_partyStatusData->GetStatusNumber();
	m_etcNumber = m_partyStatusData->GetEtcNumber();

	for (int i=0;i<m_partyNumber;i++)
	{
		for (int k=1;k<=m_statusNumber;k++)
		{
			LPSTR varName = m_partyStatusData->GetVarName(i,k);
			int varNumber = -1;
			if (varName != NULL)
			{
				varNumber = m_game->GetVarNumber(varName);
			}
			m_partyStatusData->SetVarNumber(i,k,varNumber);
		}
	}

	for (int i=0;i<m_etcNumber;i++)
	{
		LPSTR varName = m_partyStatusData->GetEtcVarName(i);
		int varNumber = m_game->GetVarNumber(varName);
		m_partyStatusData->SetEtcVarNumber(i,varNumber);
	}

	for (int i=0;i<m_printNumberMax;i++)
	{
		LPSTR varName = m_partyStatusData->GetPrintVarName(i);
		if (varName != NULL)
		{
			int varNumber = m_game->GetVarNumber(varName);
			m_partyStatusData->SetPrintVarNumber(i,varNumber);
		}
	}

	//’Ç‰Áƒ{ƒ^ƒ“


	GetDokuritsuPrintMode();


//	m_effectTime = 0;
//	GetInitGameParam(&m_effectTime,"effectTime");

	



	CreateBackButton();


	GetDisableQuickButtonSetup();
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
	GetAddLayerSetup();
	GetAnimeLayerSetup();
}



CCommonPrintParty::~CCommonPrintParty()
{
	End();
}

void CCommonPrintParty::End(void)
{
	ENDDELETECLASS(m_partyStatusData);
}


int CCommonPrintParty::Init(void)
{
	LoadBackBG();
	m_effectCount = 0;

	if (m_oldVersion)
	{
		InitOldVersion();
	}
	else
	{
		InitNewVersion();
	}


	m_back->Init();
	LoadBackButtonPic();


	return -1;
}


int CCommonPrintParty::InitOldVersion(void)
{
	for (int i = 0; i<m_partyNumber; i++)
	{
		for (int k = 1; k <= m_statusNumber; k++)
		{
			int type = m_partyStatusData->GetType(i, k);
			if (type == 1)
			{
				int varNumber = m_partyStatusData->GetVarNumber(i, k);
				if (varNumber != -1)
				{
					int varData = m_game->GetVarData(varNumber);
					m_partyStatusData->SetData(i, k, varData);
				}
			}
		}
	}

	for (int i = 0; i<m_etcNumber; i++)
	{
		int varNumber = m_partyStatusData->GetEtcVarNumber(i);
		if (varNumber != -1)
		{
			int varData = m_game->GetVarData(varNumber);
			m_partyStatusData->SetEtcData(i, varData);
		}
	}

	for (int i = 0; i<m_printNumberMax; i++)
	{
		int varNumber = m_partyStatusData->GetPrintVarNumber(i);
		if (varNumber != -1)
		{
			int varData = m_game->GetVarData(varNumber);
			m_partyStatusData->SetPrintData(i, varData);
		}
	}

	return -1;
}

int CCommonPrintParty::InitNewVersion(void)
{
	return -1;
}

int CCommonPrintParty::Calcu(void)
{
	int back = m_back->Calcu(m_inputStatus);

	if (back != NNNBUTTON_NOTHING)
	{
		int nm = ProcessUpDownBack(back);
		if (nm >= 0)
		{
			if (nm == 0)
			{
				m_game->FuqueAllEffectYoyaku();
				return ReturnFadeOut(m_backMode);
			}
		}
	}

	if (m_oldVersion)
	{
		return CalcuOldVersion();
	}
	else
	{
		return CalcuNewVersion();
	}


	return -1;
}



int CCommonPrintParty::CalcuOldVersion(void)
{
	return -1;
}
int CCommonPrintParty::CalcuNewVersion(void)
{
	return -1;
}

int CCommonPrintParty::Print(void)
{
	CAreaControl::SetNextAllPrint();

	PrintBackScriptOrBG();

	if (m_oldVersion)
	{
		PrintOldVersion();
	}
	else
	{
		PrintNewVersion();
	}




	if (m_back != NULL)
	{
		m_back->Print(TRUE);
	}


	return -1;
}



int CCommonPrintParty::PrintOldVersion(void)
{
	int ps = 100;
	if (m_effectTime > 0)
	{
		ps = (100 * m_effectCount) / m_effectTime;
	}

	m_partyStatusData->Print(ps);

	if (m_effectCount < m_effectTime)
	{
		m_effectCount++;
	}

	return -1;
}
int CCommonPrintParty::PrintNewVersion(void)
{

	return -1;
}


void CCommonPrintParty::FinalExitRoutine(void)
{

//	if (m_exitModeFlag)
//	{
//		m_game->SetYoyaku();
//	}

}

int CCommonPrintParty::EndMode(void)
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




void CCommonPrintParty::CreateStartScreen(void)
{
	Print();
}




int CCommonPrintParty::PrintDokuristu(int nowMode)
{

	return -1;
}

