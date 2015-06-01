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


#include "..\nnnUtilLib\commonPlayStatusData.h"
#include "commonPrintStatus.h"

#include "commonKeyList.h"



CCommonPrintStatus::CCommonPrintStatus(CGameCallBack* lpGame,int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTSTATUS_MODE);
	LoadSetupFile("PrintStatus",256);

	m_message = m_game->GetMyMessage();

	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;
	GetInitGameString(&m_filenameBG,"filenameBG");

	m_setNumber = 1;
	GetInitGameParam(&m_setNumber,"setNumber");

	m_playStatusData = new CCommonPlayStatusData*[m_setNumber];
	for (int i=0;i<m_setNumber;i++)
	{
		char name[256];
		sprintf_s(name,256,"set%d",i+1);
		m_playStatusData[i] = new CCommonPlayStatusData(m_setup,name);

		int graphNumber = m_playStatusData[i]->GetGraphNumber();
		for (int k=0;k<graphNumber;k++)
		{
			LPSTR varName = m_playStatusData[i]->GetVarName(k);
			int varNumber = m_game->GetVarNumber(varName);
			m_playStatusData[i]->SetVarNumber(k,varNumber);
		}
	}

	m_effectTime = 0;
	GetInitGameParam(&m_effectTime,"effectTime");




	CreateBackButton();


	GetDisableQuickButtonSetup();
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
	GetAddLayerSetup();
	GetAnimeLayerSetup();
}



CCommonPrintStatus::~CCommonPrintStatus()
{
	End();
}

void CCommonPrintStatus::End(void)
{
	if (m_playStatusData != NULL)
	{
		for (int i=0;i<m_setNumber;i++)
		{
			ENDDELETECLASS(m_playStatusData[i]);
		}
		DELETEARRAY(m_playStatusData);
	}
}


int CCommonPrintStatus::Init(void)
{
	LoadBackBG();
	m_effectCount = 0;

	for (int i=0;i<m_setNumber;i++)
	{
		int graphNumber = m_playStatusData[i]->GetGraphNumber();
		for (int k=0;k<graphNumber;k++)
		{
			int varNumber = m_playStatusData[i]->GetVarNumber(k);
			int varData = m_game->GetVarData(varNumber);
			m_playStatusData[i]->SetData(k,varData);
		}
	}

	m_back->Init();
	LoadBackButtonPic();


	return -1;
}


int CCommonPrintStatus::Calcu(void)
{
	int back = m_back->Calcu(m_inputStatus);

	if (back != NNNBUTTON_NOTHING)
	{
		int nm = ProcessUpDownBack(back);
		if (nm >= 0)
		{
			if (nm == 0)
			{
				return ReturnFadeOut(m_backMode);
			}
		}
	}




	return -1;
}

int CCommonPrintStatus::Print(void)
{
	CAreaControl::SetNextAllPrint();

	PrintBackScriptOrBG();

	int ps = 100;
	if (m_effectTime > 0)
	{
		ps = (100 * m_effectCount) / m_effectTime;
	}

	for (int i=0;i<m_setNumber;i++)
	{
		m_playStatusData[i]->Print(ps);
	}

	if (m_back != NULL)
	{
		m_back->Print(TRUE);
	}

	if (m_effectCount < m_effectTime)
	{
		m_effectCount++;
	}

	return -1;
}





void CCommonPrintStatus::FinalExitRoutine(void)
{

//	if (m_exitModeFlag)
//	{
//		m_game->SetYoyaku();
//	}

}

int CCommonPrintStatus::EndMode(void)
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




void CCommonPrintStatus::CreateStartScreen(void)
{
	Print();
}






