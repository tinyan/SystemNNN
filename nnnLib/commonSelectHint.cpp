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


#include "commonSelectHint.h"

#include "commonKeyList.h"



CCommonSelectHint::CCommonSelectHint(CGameCallBack* lpGame, int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTHINT_MODE);
	LoadSetupFile("SelectHint", 256);


	//	m_haveItem = new CHaveItemData();

	m_message = m_game->GetMyMessage();

	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;

	CreateBackButton();
//	CreateUpDownButton();
//	CreateUpDownBack();

	GetInitGameString(&m_filenameBG, "fileNameBG");

	m_groupNumber = 1;
	GetInitGameParam(&m_groupNumber, "groupNumber");
	m_selectButtonGroup = new CCommonButtonGroup(m_setup, m_groupNumber, NULL, "group");

	for (int i = 0; i < m_groupNumber; i++)
	{
		LPSTR filename = m_selectButtonGroup->GetFileName(i);
		CPicture* pic = m_game->GetSystemPicture(filename);
		m_selectButtonGroup->SetPicture(i, pic);
	}

	m_groupFlagVar = new int[m_groupNumber];
	for (int i = 0; i < m_groupNumber; i++)
	{
		int varNumber = -1;

		char name[256];
		sprintf_s(name, 256, "group%dFlag", i + 1);
		LPSTR varName = NULL;
		GetInitGameString(&varName, name);
		if (varName)
		{
			varNumber = m_game->GetVarNumber(varName);
		}

		m_groupFlagVar[i] = varNumber;
	}



	CreateBackButton();
	//	CreateUpDownButton();
	//	CreateUpDownBack();



	GetDisableQuickButtonSetup();
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
	GetAddLayerSetup();
	GetAnimeLayerSetup();
}

CCommonSelectHint::~CCommonSelectHint()
{
	End();
}

void CCommonSelectHint::End(void)
{
	ENDDELETECLASS(m_selectButtonGroup);
}


int CCommonSelectHint::Init(void)
{
	LoadBackBG();




	for (int i = 0; i < m_groupNumber; i++)
	{
		BOOL existFlag = FALSE;
		int varNumber = m_groupFlagVar[i];
		if (varNumber != -1)
		{
			if (m_game->GetVarData(varNumber) != 0)
			{
				existFlag = TRUE;
			}
		}

		m_selectButtonGroup->SetExist(i, existFlag);
		m_selectButtonGroup->SetEnable(i, TRUE);
	}

	//	char filename[256];
	//	sprintf_s(filename, 256, "sys\\%s", m_plateFilename);
	//	m_commonParts->LoadDWQ(filename);

	m_selectButtonGroup->Init();

	m_back->Init();
	LoadBackButtonPic();



	return -1;
}


int CCommonSelectHint::Calcu(void)
{
	int rt = m_back->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int st = ProcessCommonButton(rt);
		if (st >= 0)
		{
			m_game->FuqueAllEffectYoyaku();
			return ReturnFadeOut(m_backMode);
		}
	}
	int rt2 = m_selectButtonGroup->Calcu(m_inputStatus);
	if (rt2 != NNNBUTTON_NOTHING)
	{
		int st = ProcessCommonButton(rt2);
		if (st >= 0)
		{
			//set
			m_game->SetHintNumber(st);
			return ReturnFadeOut(PRINTHINT_MODE);
		}
	}

	return -1;
}

int CCommonSelectHint::Print(void)
{
	CAreaControl::SetNextAllPrint();

	PrintBackScriptOrBG();

	m_message->PrintMessage(100, 100, "‚r‚d‚k‚d‚b‚s‚g‚h‚m‚s");

	m_selectButtonGroup->Print(TRUE);


	m_back->Print(TRUE);

	return -1;
}


void CCommonSelectHint::CreateStartScreen(void)
{
	Print();
}
