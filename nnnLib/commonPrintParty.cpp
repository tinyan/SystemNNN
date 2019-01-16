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
#include "..\nnnUtilLib\commonMultiStateButton.h"
#include "..\nnnUtilLib\commonCheckButton.h"

#include "..\nnnUtilLib\superButtonPicture.h"


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

#include "../nnnUtilLib/printPlayerStatus.h"

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
	
	CPicture* lpBG = m_commonBG;
	if (m_backScriptFlag) lpBG = NULL;

	m_partyStatusData = NULL;

	m_partyNumber = 0;
	m_printNumberMax = 0;
	m_statusNumber = 0;
	m_etcNumber = 0;
	if (m_oldVersion)
	{
		m_partyStatusData = new CCommonPartyStatusData(m_setup, m_message);
		m_partyNumber = m_partyStatusData->GetPartyNumber();
		m_printNumberMax = m_partyStatusData->GetPrintNumberMax();
		m_statusNumber = m_partyStatusData->GetStatusNumber();
		m_etcNumber = m_partyStatusData->GetEtcNumber();

		for (int i = 0; i < m_partyNumber; i++)
		{
			for (int k = 1; k <= m_statusNumber; k++)
			{
				LPSTR varName = m_partyStatusData->GetVarName(i, k);
				int varNumber = -1;
				if (varName != NULL)
				{
					varNumber = m_game->GetVarNumber(varName);
				}
				m_partyStatusData->SetVarNumber(i, k, varNumber);
			}
		}

		for (int i = 0; i < m_etcNumber; i++)
		{
			LPSTR varName = m_partyStatusData->GetEtcVarName(i);
			int varNumber = m_game->GetVarNumber(varName);
			m_partyStatusData->SetEtcVarNumber(i, varNumber);
		}

		for (int i = 0; i < m_printNumberMax; i++)
		{
			LPSTR varName = m_partyStatusData->GetPrintVarName(i);
			if (varName != NULL)
			{
				int varNumber = m_game->GetVarNumber(varName);
				m_partyStatusData->SetPrintVarNumber(i, varNumber);
			}
		}
	}



	m_printPlayerStatus = NULL;

	m_paramNumber = 0;
	m_paramOnOffWork = NULL;
	m_paramOnOffButton = NULL;
	m_paramOnOffVar = NULL;
	m_param = NULL;


	m_setNumber = 0;
	m_setPlaceSetData = NULL;
	m_radio = NULL;


	m_placeUpDown = NULL;
	m_onOffButton = NULL;

	m_onOffVar = NULL;
	m_place = NULL;
	m_useRadioFlag = 0;



	m_setPlaceSetNumber = 0;
	m_setPlaceSetData = NULL;
	

	m_etcOnOffVar = NULL;
	m_etcOnOffButton = NULL;
	m_etcPrintZahyo = NULL;
	m_etcOnOffWork = NULL;
	m_etcPlaceWork = NULL;


	if (m_oldVersion == 0)
	{
		GetInitGameParam(&m_setNumber, "setNumber");

		m_printPlayerStatus = new CPrintPlayerStatus(m_message);

		m_etcNumber = m_printPlayerStatus->GetEtcNumber();


		m_printPlayerStatus->StartRequestVarNumberName();
		while (TRUE)
		{
			LPSTR varName = NULL;
			BOOL b = m_printPlayerStatus->RequestVarNumberName(&varName);
			if (varName != NULL)
			{
				int varNumber = m_game->GetVarNumber(varName);
				m_printPlayerStatus->SetVarNumber(varNumber, varName);
			}

			if (!b)
			{
				break;
			}
		}

		m_place = new int[m_setNumber];

		m_paramNumber = m_printPlayerStatus->GetStatusTypeNumber();
		m_paramOnOffWork = new int[m_paramNumber];

		m_paramOnOffButton = new CCommonCheckButton*[m_paramNumber];
		m_paramOnOffVar = new int[m_paramNumber];
		m_param = new int[m_paramNumber];

		int useSuperButtonPic = 1;

		for (int i = 0; i < m_paramNumber;i++)
		{
			int varNumber = -1;
			CCommonCheckButton* button = NULL;
			LPSTR varName = NULL;
			char name[256];
			sprintf_s(name, 256, "paramOffVarName%d", i + 1);

			if (GetInitGameString(&varName, name))
			{
				varNumber = m_game->GetVarNumber(varName);
			}

			if (varNumber != -1)
			{
				sprintf_s(name, 256, "paramOff%dButton", i + 1);
				button = new CCommonCheckButton(m_setup, lpBG, name);

				CPicture* lpPic1 = CSuperButtonPicture::GetPicture(useSuperButtonPic);
				CPicture* lpPic2 = CSuperButtonPicture::GetPicture(useSuperButtonPic+1);
				useSuperButtonPic += 2;
				button->SetPicture(lpPic1, 0);
				button->SetPicture(lpPic2, 1);
			}

			m_paramOnOffVar[i] = varNumber;
			m_paramOnOffButton[i] = button;
		}



		m_setPlaceSetWork = new POINT[m_setNumber];


		//check
		//updown
		m_onOffVar = new int[m_setNumber];
		m_onOffButton = new CCommonCheckButton*[m_setNumber];
		m_placeUpDown = new CCommonUpDownButtonGroup*[m_setNumber];


		for (int i = 0; i < m_setNumber; i++)
		{
			char name[256];
			LPSTR varName = NULL;
			sprintf_s(name, 256, "controlVarName%d", i + 1);
			GetInitGameString(&varName, name);
			m_onOffButton[i] = NULL;
			m_placeUpDown[i] = NULL;

			if (varName != NULL)
			{
				m_onOffVar[i] = m_game->GetVarNumber(varName);
				if (m_onOffVar[i] != -1)
				{
					char buttonName[256];
					sprintf_s(buttonName, 256, "onOff%dButton", i + 1);

					m_onOffButton[i] = new CCommonCheckButton(m_setup, lpBG, buttonName);
					m_onOffButton[i]->SetPicture(CSuperButtonPicture::GetPicture(useSuperButtonPic),0);
					m_onOffButton[i]->SetPicture(CSuperButtonPicture::GetPicture(useSuperButtonPic+1),1);
					useSuperButtonPic += 2;

					char buttonName2[256];
					sprintf_s(buttonName, 256, "up%d", i + 1);
					sprintf_s(buttonName2, 256, "down%d", i + 1);
					m_placeUpDown[i] = new CCommonUpDownButtonGroup(buttonName, buttonName2, m_setup, lpBG);
					m_placeUpDown[i]->SetPicture(0, CSuperButtonPicture::GetPicture(useSuperButtonPic));
					m_placeUpDown[i]->SetPicture(1, CSuperButtonPicture::GetPicture(useSuperButtonPic+1));
					useSuperButtonPic += 2;

					m_placeUpDown[i]->ClearAccelKey();
				}
			}
		}

		//placeset
		m_setPlaceSetNumber = 1;
		GetInitGameParam(&m_setPlaceSetNumber, "setPlaceSetNumber");
		m_setPlaceSetData = new POINT[m_setPlaceSetNumber * m_setNumber];
		for (int i = 0; i < m_setPlaceSetNumber; i++)
		{
			for (int k = 0; k < m_setNumber; k++)
			{
				int x = 100*i;
				int y = 100*k;

				char name[256];
				sprintf_s(name, 256, "set%d_%dPrintX", i + 1, k + 1);
				GetInitGameParam(&x, name);
				sprintf_s(name, 256, "set%d_%dPrintY", i + 1, k + 1);
				GetInitGameParam(&y, name);
				m_setPlaceSetData[i*m_setNumber + k].x = x;
				m_setPlaceSetData[i*m_setNumber + k].y = y;
			}

			for (int k = 0; k < m_etcNumber; k++)
			{

			}
		}

		m_setPlaceSetSelectVar = -1;
		{
			LPSTR varName = NULL;
			if (GetInitGameString(&varName, "setPlaceSelectVarName"))
			{
				if (varName != NULL)
				{
					m_setPlaceSetSelectVar = m_game->GetVarNumber(varName);
				}
			}
		}


		m_useRadioFlag = 0;
		GetInitGameParam(&m_useRadioFlag, "useRadio");
		m_radio = NULL;
		if (m_useRadioFlag && m_setPlaceSetNumber > 1)
		{
			m_radio = new CCommonRadioButtonGroup(m_setup, "radio", NULL, m_setPlaceSetNumber, NULL);


			for (int n = 0; n < m_setPlaceSetNumber; n++)
			{
				CPicture* lpPic = CSuperButtonPicture::GetPicture(useSuperButtonPic);
				m_radio->SetPicture(lpPic, n, 0);
				lpPic = CSuperButtonPicture::GetPicture(useSuperButtonPic+1);
				m_radio->SetPicture(lpPic, n, 1);
				useSuperButtonPic += 2;
			}
		}



		m_checkPrintDeltaX = 100;
		m_checkPrintDeltaY = 0;
		m_upPrintDeltaX = 150;
		m_upPrintDeltaY = 0;
		m_downPrintDeltaX = 150;
		m_downPrintDeltaY = 50;
		m_etcPrintDeltaX = 100;
		m_etcPrintDeltaY = 0;
		GetInitGameParam(&m_checkPrintDeltaX, "checkPrintDeltaX");
		GetInitGameParam(&m_checkPrintDeltaY, "checkPrintDeltaY");
		GetInitGameParam(&m_upPrintDeltaX, "upPrintDeltaX");
		GetInitGameParam(&m_upPrintDeltaY, "upPrintDeltaY");
		GetInitGameParam(&m_downPrintDeltaX, "downPrintDeltaX");
		GetInitGameParam(&m_downPrintDeltaY, "downPrintDeltaY");
		GetInitGameParam(&m_etcPrintDeltaY, "etcPrintDeltaY");
		GetInitGameParam(&m_etcPrintDeltaY, "etcPrintDeltaY");


		m_etcOnOffVar = new int[m_etcNumber+1];
		m_etcPrintZahyo = new POINT[(m_etcNumber+1)*(m_setPlaceSetNumber+1)];
		m_etcOnOffButton = new CCommonCheckButton*[m_etcNumber + 1];
		m_etcOnOffWork = new int[m_etcNumber + 1];
		m_etcPlaceWork = new POINT[m_etcNumber + 1];

		for (int i = 0; i < m_etcNumber; i++)
		{
			m_etcOnOffVar[i] = -1;
			m_etcOnOffButton[i] = NULL;
		}

		for (int i = 0; i < m_etcNumber; i++)
		{
			char name[256];
			LPSTR varName = NULL;
			sprintf_s(name, 256, "etc%dControlVarName", i + 1);
			GetInitGameString(&varName, name);

			if (varName != NULL)
			{
				m_etcOnOffVar[i] = m_game->GetVarNumber(varName);
				if (m_etcOnOffVar[i] != -1)
				{
					char buttonName[256];
					sprintf_s(buttonName, 256, "etc%dOnOffButton", i + 1);

					m_etcOnOffButton[i] = new CCommonCheckButton(m_setup, lpBG, buttonName);
					m_etcOnOffButton[i]->SetPicture(CSuperButtonPicture::GetPicture(useSuperButtonPic), 0);
					m_etcOnOffButton[i]->SetPicture(CSuperButtonPicture::GetPicture(useSuperButtonPic + 1), 1);
					useSuperButtonPic += 2;
				}
			}
		}

		for (int i = 0; i < m_setPlaceSetNumber; i++)
		{
			for (int k = 0; k < m_etcNumber; k++)
			{
				int x = 50+100 * i;
				int y = 50+100 * k;

				char name[256];
				sprintf_s(name, 256, "set%d_etc%dPrintX", i + 1, k + 1);
				GetInitGameParam(&x, name);
				sprintf_s(name, 256, "set%d_etc%dPrintY", i + 1, k + 1);
				GetInitGameParam(&y, name);
				m_etcPrintZahyo[i*m_etcNumber + k].x = x;
				m_etcPrintZahyo[i*m_etcNumber + k].y = y;
			}

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
	DELETEARRAY(m_etcPlaceWork);
	DELETEARRAY(m_etcOnOffWork);
	DELETEARRAY(m_etcOnOffVar);
	DELETEARRAY(m_etcPrintZahyo);
	if (m_etcOnOffButton)
	{
		for (int i = 0; i < m_etcNumber; i++)
		{
			ENDDELETECLASS(m_etcOnOffButton[i]);
		}
		DELETEARRAY(m_etcOnOffButton);
	}


	ENDDELETECLASS(m_partyStatusData);
	ENDDELETECLASS(m_printPlayerStatus);


	DELETEARRAY(m_setPlaceSetWork);

	DELETEARRAY(m_paramOnOffWork);
	DELETEARRAY(m_paramOnOffVar);
	if (m_paramOnOffButton)
	{
		for (int i = 0; i < m_paramNumber; i++)
		{
			ENDDELETECLASS(m_paramOnOffButton[i]);
		}
		DELETEARRAY(m_paramOnOffButton);
	}


	if (m_placeUpDown)
	{
		for (int i = 0; i < m_setNumber; i++)
		{
			ENDDELETECLASS(m_placeUpDown[i]);
		}
		DELETEARRAY(m_placeUpDown);
	}
	DELETEARRAY(m_onOffVar);
	if (m_onOffButton)
	{
		for (int i = 0; i < m_setNumber; i++)
		{
			ENDDELETECLASS(m_onOffButton[i]);
		}
		DELETEARRAY(m_onOffButton);
		m_onOffButton = NULL;
	}

	DELETEARRAY(m_place);

	DELETEARRAY(m_setPlaceSetData);
	ENDDELETECLASS(m_radio);
}


int CCommonPrintParty::Init(void)
{
	LoadBackBG();
	m_effectCount = 0;
	GetPlaceList();

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
	GetPlaceList();
	GetVarToParam();
	SetDataToPlayerStatus();
	SetPlaceSetPointList();
	//SetEtcPlaceSetPointList();

	LoadCheckButtonPic();
	LoadUpdownButtonPic();
	LoadRadioButtonPic();
	LoadParamButtonPic();
	LoadEtcCheckButtonPic();

	InitCheckButton();
	InitUpdownButton();
	InitRadioButton();
	InitParamButton();
	InitEtcCheckButton();

	return -1;
}



void CCommonPrintParty::LoadCheckButtonPic(void)
{
	for (int i = 0; i<m_setNumber; i++)
	{
		if (m_onOffButton[i])
		{
			char filename[256];

			for (int k = 0; k < 2; k++)
			{
				CPicture* lpPic = m_onOffButton[i]->GetPicture(k);
				LPSTR name = m_onOffButton[i]->GetFileName(k);
				sprintf_s(filename, "sys\\%s", name);
				lpPic->LoadDWQ(filename);
			}
		}
	}


}

void CCommonPrintParty::LoadUpdownButtonPic(void)
{
	for (int i = 0; i<m_setNumber; i++)
	{
		if (m_placeUpDown[i])
		{
			char filename[256];

			for (int k = 0; k < 2; k++)
			{
				CPicture* lpPic = m_placeUpDown[i]->GetPicture(k);
				LPSTR name = m_placeUpDown[i]->GetFileName(k);
				sprintf_s(filename, "sys\\%s", name);
				lpPic->LoadDWQ(filename);
			}
		}
	}


}


void CCommonPrintParty::LoadRadioButtonPic(void)
{
	if (m_radio == NULL) return;

	int select = GetSetSelectSetNumber();

	for (int i = 0; i < m_setPlaceSetNumber; i++)
	{

		char filename[256];

		for (int k = 0; k < 2; k++)
		{
			CPicture* lpPic = m_radio->GetPicture(i, k);
			LPSTR name = m_radio->GetFileName(i, k);
			sprintf_s(filename, "sys\\%s", name);
			lpPic->LoadDWQ(filename);
		}

	}
}

void CCommonPrintParty::LoadParamButtonPic(void)
{
	for (int i = 0; i<m_paramNumber; i++)
	{
		CCommonCheckButton* button = m_paramOnOffButton[i];
		if (button)
		{
			char filename[256];

			for (int k = 0; k < 2; k++)
			{
				CPicture* lpPic = button->GetPicture(k);
				LPSTR name = button->GetFileName(k);
				sprintf_s(filename, "sys\\%s", name);
				lpPic->LoadDWQ(filename);
			}
		}
	}
}

void CCommonPrintParty::LoadEtcCheckButtonPic(void)
{
	for (int i = 0; i<m_etcNumber; i++)
	{
		if (m_etcOnOffButton[i])
		{
			char filename[256];

			for (int k = 0; k < 2; k++)
			{
				CPicture* lpPic = m_etcOnOffButton[i]->GetPicture(k);
				LPSTR name = m_etcOnOffButton[i]->GetFileName(k);
				sprintf_s(filename, "sys\\%s", name);
				lpPic->LoadDWQ(filename);
			}
		}
	}
}



int CCommonPrintParty::GetSetSelectSetNumber(void)
{
	int varData = 0;
	if (m_setPlaceSetSelectVar != -1)
	{
		varData = m_game->GetVarData(m_setPlaceSetSelectVar);
	}
	if (varData < 0) varData = 0;
	return varData;
}
void CCommonPrintParty::SetSetSelectSetNumber(int n)
{
	if (m_setPlaceSetSelectVar != -1)
	{
		m_game->SetVarData(m_setPlaceSetSelectVar, n);
	}
}

void CCommonPrintParty::InitCheckButton(void)
{
	for (int i = 0; i < m_setNumber; i++)
	{
		if (m_onOffButton[i])
		{
			//zahyo
			int pl = m_place[i];
			if (pl < 0) pl *= -1;
			if (pl > 0) pl--;
			POINT p = GetBaseZahyo(pl);
			int x = p.x;
			int y = p.y;

			//			int x = m_printZahyo[pl].x;
			//			int y = m_printZahyo[pl].y;
			x += m_checkPrintDeltaX;
			y += m_checkPrintDeltaY;
			POINT point;
			point.x = x;
			point.y = y;
			m_onOffButton[i]->SetZahyo(point);


			int state = 0;
			if (m_place[i] > 0)
			{
				state = 1;
			}

			m_onOffButton[i]->SetState(state);
			m_onOffButton[i]->Init();
		}
	}

}

void CCommonPrintParty::InitUpdownButton(void)
{
	for (int i = 0; i < m_setNumber; i++)
	{
		if (m_placeUpDown[i])
		{
			//zahyo

			int pl = m_place[i];
			if (pl < 0) pl *= -1;
			if (pl > 0) pl--;
			POINT p = GetBaseZahyo(pl);
			int x = p.x;
			int y = p.y;

			//int x = m_printZahyo[pl].x;
			//int y = m_printZahyo[pl].y;
			int upX = x + m_upPrintDeltaX;
			int upY = y + m_upPrintDeltaY;
			int downX = x + m_downPrintDeltaX;
			int downY = y + m_downPrintDeltaY;

			m_placeUpDown[i]->SetUpDownZahyo(upX, upY, downX, downY);



			int page = m_place[i];
			if (page < 0) page *= -1;
			if (page > 0) page--;
			int pageMax = m_setNumber;
			m_placeUpDown[i]->SetPageMax(pageMax);
			m_placeUpDown[i]->SetPage(page);
			m_placeUpDown[i]->Init();
		}
	}
}


void CCommonPrintParty::InitRadioButton(void)
{
	if (m_radio == NULL) return;

	int select = GetSetSelectSetNumber();
	m_radio->SetRadio(select);
	m_radio->Init(select);
}


void CCommonPrintParty::InitParamButton(void)
{
	for (int i = 0; i < m_paramNumber; i++)
	{
		CCommonCheckButton* button = m_paramOnOffButton[i];
		if (button)
		{
			int state = 1;
			if (m_param[i] > 0)
			{
				state = 0;
			}

			button->SetState(state);
			button->Init();
		}
	}

}


void CCommonPrintParty::InitEtcCheckButton(void)
{
	for (int i = 0; i < m_etcNumber; i++)
	{
		if (m_etcOnOffButton[i])
		{
			//zahyo
			POINT p = GetEtcBaseZahyo(i);
			p.x += m_etcPrintDeltaX;
			p.y += m_etcPrintDeltaY;

			m_etcOnOffButton[i]->SetZahyo(p);

			int state = 1;
			int varNumber = m_etcOnOffVar[i];
			if (varNumber != -1)
			{
				if (m_game->GetVarData(varNumber) > 0)
				{
					state = 0;
				}
			}

			m_etcOnOffButton[i]->SetState(state);
			m_etcOnOffButton[i]->Init();
		}
	}

}



int CCommonPrintParty::Calcu(void)
{

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

	return -1;
}
int CCommonPrintParty::CalcuNewVersion(void)
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

	if (m_effectCount < m_effectTime)
	{
		return -1;
	}


	for (int i = 0; i < m_setNumber; i++)
	{
		CCommonCheckButton* button = m_onOffButton[i];
		if (button)
		{
			int st = button->Calcu(m_inputStatus);
			if (st != NNNBUTTON_NOTHING)
			{
				int nm = ProcessButtonGroup(st);
				if (nm >= 0)
				{
					ChangeOnOff(i);
					SetPlaceToVar();
					InitCheckButton();
					InitUpdownButton();
					InitRadioButton();
					InitParamButton();
					InitEtcCheckButton();
					return -1;
				}
			}
		}
	}

	for (int i = 0; i < m_setNumber; i++)
	{
		CCommonUpDownButtonGroup* button = m_placeUpDown[i];
		if (button)
		{
			int st = button->Calcu(m_inputStatus);
			if (st != NNNBUTTON_NOTHING)
			{
				int nm = ProcessButtonGroup(st);
				if (nm >= 0)
				{
					int pl = m_place[i];
					if (pl < 0) pl *= -1;
					if (pl > 0) pl--;

					int delta = nm - pl;
					ChangePlace(i, delta);

					SetPlaceToVar();
					InitCheckButton();
					InitUpdownButton();
					InitRadioButton();
					InitParamButton();
					InitEtcCheckButton();
					return -1;
				}
			}
		}
	}

	if (m_radio)
	{
		int st = m_radio->Calcu(m_inputStatus);
		if (st != NNNBUTTON_NOTHING)
		{
			int nm = ProcessButtonGroup(st);
			if (nm >= 0)
			{
				SetSetSelectSetNumber(nm);
				InitCheckButton();
				InitUpdownButton();
				InitRadioButton();
				InitParamButton();
				InitEtcCheckButton();
				return -1;
			}
		}
	}

	for (int i = 0; i < m_paramNumber; i++)
	{
		CCommonCheckButton* button = m_paramOnOffButton[i];
		if (button)
		{
			int st = button->Calcu(m_inputStatus);
			if (st != NNNBUTTON_NOTHING)
			{
				int nm = ProcessButtonGroup(st);
				if (nm >= 0)
				{

					ChangeParamOnOff(i);
					SetParamToVar();

					InitCheckButton();
					InitUpdownButton();
					InitRadioButton();
					InitParamButton();
					InitEtcCheckButton();

					return -1;
				}
			}
		}
	}

	for (int i = 0; i < m_etcNumber; i++)
	{
		CCommonCheckButton* button = m_etcOnOffButton[i];
		if (button)
		{
			int st = button->Calcu(m_inputStatus);
			if (st != NNNBUTTON_NOTHING)
			{
				int nm = ProcessButtonGroup(st);
				if (nm >= 0)
				{
					ChangeEtcOnOff(i);
					SetPlaceToVar();
					InitCheckButton();
					InitUpdownButton();
					InitRadioButton();
					InitParamButton();
					InitEtcCheckButton();
					return -1;
				}
			}
		}
	}


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
	PrintBackScriptOrBG();

	GetPlaceList();
	SetDataToPlayerStatus();



	int ps = 100;
	if (m_effectTime > 0)
	{
		ps = (100 * m_effectCount) / m_effectTime;
	}

	PrintStatusSub(ps, TRUE);


	if (m_back != NULL)
	{
		m_back->Print(TRUE);
	}

	for (int i = 0; i < m_setNumber; i++)
	{
		if (m_onOffButton[i])
		{
			m_onOffButton[i]->Print(TRUE);
		}
	}

	for (int i = 0; i < m_setNumber; i++)
	{
		if (m_onOffButton[i])
		{
			m_placeUpDown[i]->Print(TRUE);
		}
	}

	if (m_radio)
	{
		m_radio->Print(TRUE);
	}


	for (int i = 0; i < m_paramNumber; i++)
	{
		if (m_paramOnOffButton[i])
		{
			m_paramOnOffButton[i]->Print(TRUE);
		}
	}

	for (int i = 0; i < m_etcNumber; i++)
	{
		if (m_etcOnOffButton[i])
		{
			m_etcOnOffButton[i]->Print(TRUE);
		}
	}


	if (m_effectCount < m_effectTime)
	{
		m_effectCount++;
	}



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


void CCommonPrintParty::SetDataToPlayerStatus(void)
{
	m_printPlayerStatus->StartRequestVarData();
	while (TRUE)
	{
		int varNumber = -1;
		BOOL b = m_printPlayerStatus->RequestVarData(&varNumber);
		if (varNumber != -1)
		{
			int varData = m_game->GetVarData(varNumber);
			m_printPlayerStatus->SetVarData(varData, varNumber);
		}

		if (!b)
		{
			break;
		}
	}

	SetPlaceSetPointList();
	SetParamOnOffWork();
}


void CCommonPrintParty::SetPlaceSetPointList(void)
{
//	int select = GetSetSelectSetNumber();

	for (int i = 0; i < m_setNumber; i++)
	{
		int place = m_place[i];
		if (place < 0) place *= -1;
		place--;
		if (place < 0) place = 0;

		m_setPlaceSetWork[i] = GetBaseZahyo(place);
	}
}
void CCommonPrintParty::SetParamOnOffWork(void)
{
	for (int i = 0; i < m_paramNumber; i++)
	{
		int data = 1;
		if (m_param[i] > 0)
		{
			data = 0;
		}
		m_paramOnOffWork[i] = data;
	}
}



int CCommonPrintParty::PrintDokuristu(int nowMode)
{
	GetVarToParam();
	GetPlaceList();
	SetDataToPlayerStatus();



	PrintStatusSub(100);
	
	return -1;
}


void CCommonPrintParty::PrintStatusSub(int ps, BOOL mustPrint)
{
	/*
	for (int i = 0; i < m_setNumber; i++)
	{
	int onOff = 0;
	if (m_place[i] > 0)
	{
	onOff = 1;
	}


	if (onOff || mustPrint)
	{
	int pl = m_place[i];
	if (pl < 0) pl *= -1;
	if (pl > 0) pl--;

	POINT p = GetBaseZahyo(pl);

	m_playStatusData[i]->Print(p, ps);
	//			m_playStatusData[i]->Print(m_printZahyo[pl], ps);
	}
	}
	*/


	for (int i = 0; i < m_etcNumber; i++)
	{
		int st = 1;
		int varNumber = m_etcOnOffVar[i];
		if (varNumber != -1)
		{
			if (m_game->GetVarData(varNumber) != 0)
			{
				st = 0;
			}
		}
		m_etcOnOffWork[i] = st;
		m_etcPlaceWork[i] = GetEtcBaseZahyo(i);
	}


	m_printPlayerStatus->Calcu();
	m_printPlayerStatus->Print(m_setNumber, mustPrint, m_paramOnOffWork, m_place, m_setPlaceSetWork,m_etcOnOffWork,m_etcPlaceWork);
}

void CCommonPrintParty::GetPlaceList(void)
{
	for (int i = 0; i < m_setNumber; i++)
	{
		m_place[i] = i + 1;
		if (m_onOffVar)
		{
			int varNumber = m_onOffVar[i];
			if (varNumber != -1)
			{
				int varData = m_game->GetVarData(varNumber);
				if (varData != 0)
				{
					m_place[i] = varData;
				}
			}
		}
	}

}



void CCommonPrintParty::ChangePlace(int set, int delta)
{
	int from = m_place[set];
	if (from < 0) from *= -1;

	int to = from + delta;

	if ((to >= 1) && (to <= m_setNumber))
	{
		int found = -1;
		for (int i = 0; i < m_setNumber; i++)
		{
			int p = m_place[i];
			if ((p == to) || (p == -to))
			{
				found = i;
				break;
			}
		}

		if (found != -1)
		{
			//swap
			int absFrom = m_place[set];
			int signFrom = m_place[set];
			if (absFrom < 0) absFrom *= -1;
			if (signFrom > 0)
			{
				signFrom = 1;
			}
			else if (signFrom < 0)
			{
				signFrom = -1;
			}

			int absTo = m_place[found];
			int signTo = m_place[found];
			if (absTo < 0) absTo *= -1;
			if (signTo > 0)
			{
				signTo = 1;
			}
			else if (signTo < 0)
			{
				signTo = -1;
			}

			m_place[set] = absTo * signFrom;
			m_place[found] = absFrom * signTo;


			/*
			int tmp = m_place[set];
			m_place[set] = to;
			m_place[found] = tmp;
			*/
		}
	}
}

void CCommonPrintParty::SetPlaceToVar(void)
{
	if (m_place == NULL) return;
	if (m_onOffVar == NULL) return;

	for (int i = 0; i < m_setNumber; i++)
	{
		int varNumber = m_onOffVar[i];
		if (varNumber != -1)
		{
			m_game->SetVarData(varNumber, m_place[i]);
		}
	}
}

void CCommonPrintParty::SetParamToVar(void)
{
	for (int i = 0; i < m_paramNumber; i++)
	{
		int varNumber = m_paramOnOffVar[i];
		if (varNumber != -1)
		{
			m_game->SetVarData(varNumber,m_param[i]);
		}
	}
}

void CCommonPrintParty::GetVarToParam(void)
{
	for (int i = 0; i < m_paramNumber; i++)
	{
		int data = 0;
		int varNumber = m_paramOnOffVar[i];
		if (varNumber != -1)
		{
			data = m_game->GetVarData(varNumber);
		}
		m_param[i] = data;
	}
}

void CCommonPrintParty::ChangeOnOff(int set)
{
	if (m_place == NULL) return;
	if (m_onOffVar == NULL) return;

	m_place[set] *= -1;
}

void CCommonPrintParty::ChangeParamOnOff(int n)
{
	m_param[n] = 1 - m_param[n];
}

void CCommonPrintParty::ChangeEtcOnOff(int etc)
{
	int varNumber = m_etcOnOffVar[etc];
	if (varNumber != -1)
	{
		int data = m_game->GetVarData(varNumber);
		data = 1 - data;
		m_game->SetVarData(varNumber, data);
	}
}

POINT CCommonPrintParty::GetBaseZahyo(int place)
{
	int selectSet = GetSetSelectSetNumber();
	return m_setPlaceSetData[selectSet * m_setNumber + place];
}

POINT CCommonPrintParty::GetEtcBaseZahyo(int n)
{
	int selectSet = GetSetSelectSetNumber();
	return m_etcPrintZahyo[selectSet*m_etcNumber+n];
}
