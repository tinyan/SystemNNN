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
#include "..\nnnUtilLib\commonMultiStateButton.h"
#include "..\nnnUtilLib\commonRadioButtonGroup.h"
#include "..\nnnUtilLib\commonCheckButton.h"


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
	m_onOffVar = new int[m_setNumber];
	m_onOffButton = new CCommonCheckButton*[m_setNumber];
	for (int i = 0; i < m_setNumber; i++)
	{
		m_onOffVar[i] = -1;
		m_onOffButton[i] = NULL;
	}
	m_printZahyo = new POINT[m_setNumber];
	m_placeUpDown = new CCommonUpDownButtonGroup*[m_setNumber];
	for (int i = 0; i < m_setNumber; i++)
	{
		m_printZahyo[i].x = 100*i;
		m_printZahyo[i].y = 0;
		m_placeUpDown[i] = NULL;
	}
	m_place = new int[m_setNumber];

	CPicture* lpBG = m_commonBG;
	if (m_backScriptFlag) lpBG = NULL;



	m_checkPrintDeltaX = 100;
	m_checkPrintDeltaY = 0;
	m_upPrintDeltaX = 150;
	m_upPrintDeltaY = 0;
	m_downPrintDeltaX = 150;
	m_downPrintDeltaY = 50;
	GetInitGameParam(&m_checkPrintDeltaX, "checkPrintDeltaX");
	GetInitGameParam(&m_checkPrintDeltaY, "checkPrintDeltaY");
	GetInitGameParam(&m_upPrintDeltaX, "upPrintDeltaX");
	GetInitGameParam(&m_upPrintDeltaY, "upPrintDeltaY");
	GetInitGameParam(&m_downPrintDeltaX, "downPrintDeltaX");
	GetInitGameParam(&m_downPrintDeltaY, "downPrintDeltaY");

	for (int i=0;i<m_setNumber;i++)
	{
		char name[256];
		sprintf_s(name,256,"set%d",i+1);
		m_playStatusData[i] = new CCommonPlayStatusData(m_setup,name);
		m_onOffButton[i] = NULL;
		m_placeUpDown[i] = NULL;

		int graphNumber = m_playStatusData[i]->GetGraphNumber();
		for (int k=0;k<graphNumber;k++)
		{
			LPSTR varName = m_playStatusData[i]->GetVarName(k);
			int varNumber = m_game->GetVarNumber(varName);
			m_playStatusData[i]->SetVarNumber(k,varNumber);
		}

		sprintf_s(name, 256, "setPlaceX%d", i + 1);
		int x = m_printZahyo[i].x;
		if (GetInitGameParam(&x, name))
		{
			m_printZahyo[i].x = x;
		}
		sprintf_s(name, 256, "setPlaceY%d", i + 1);
		int y = m_printZahyo[i].y;
		if (GetInitGameParam(&y, name))
		{
			m_printZahyo[i].y = y;
		}

		m_setPlaceSetNumber = 1;
		GetInitGameParam(&m_setPlaceSetNumber,"setPlaceSetNumber");
		m_setPlaceSetData = new POINT[m_setPlaceSetNumber * m_setNumber];
		for (int i = 0; i < m_setPlaceSetNumber; i++)
		{
			for (int k = 0; k < m_setNumber; k++)
			{
				int x = m_printZahyo[k].x;
				int y = m_printZahyo[k].y;
				char name[256];
				sprintf_s(name, 256, "setPlaceSetX%d_%d", i + 1, k + 1);
				GetInitGameParam(&x, name);
				sprintf_s(name, 256, "setPlaceSetY%d_%d", i + 1, k + 1);
				GetInitGameParam(&y, name);
				m_setPlaceSetData[i*m_setNumber + k].x = x;
				m_setPlaceSetData[i*m_setNumber + k].y = y;
			}
		}
		
	
		LPSTR varName = NULL;
		sprintf_s(name, 256, "controlVarName%d", i + 1);
		GetInitGameString(&varName, name);
		if (varName != NULL)
		{
			m_onOffVar[i] = m_game->GetVarNumber(varName);
			if (m_onOffVar[i] != -1)
			{
				char buttonName[256];
				sprintf_s(buttonName, 256, "onOff%dButton", i + 1);

				m_onOffButton[i] = new CCommonCheckButton(m_setup, lpBG, buttonName);
				m_onOffButton[i]->SetPicture(CSuperButtonPicture::GetPicture(3 + i * 4), 0);
				m_onOffButton[i]->SetPicture(CSuperButtonPicture::GetPicture(3 + i * 4 + 1), 1);

				char buttonName2[256];
				sprintf_s(buttonName, 256, "up%d", i + 1);
				sprintf_s(buttonName2, 256, "down%d", i + 1);
				m_placeUpDown[i] = new CCommonUpDownButtonGroup(buttonName, buttonName2, m_setup, lpBG);
				m_placeUpDown[i]->SetPicture(0,CSuperButtonPicture::GetPicture(3 + i * 4 + 2));
				m_placeUpDown[i]->SetPicture(1,CSuperButtonPicture::GetPicture(3 + i * 4 + 3));

				m_placeUpDown[i]->ClearAccelKey();
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
			CPicture* lpPic = CSuperButtonPicture::GetPicture(3 + 4 * m_setNumber + n * 2 + 0);
			m_radio->SetPicture(lpPic, n, 0);
			lpPic = CSuperButtonPicture::GetPicture(3 + 4 * m_setNumber + n * 2 + 1);
			m_radio->SetPicture(lpPic, n, 1);
		}
	}


	m_setPlaceSetSelectVar = -1;
	{
		LPSTR varName = NULL;
		if (GetInitGameString(&varName, "setPlaceSelectvarName"))
		{
			if (varName != NULL)
			{
				m_setPlaceSetSelectVar = m_game->GetVarNumber(varName);
			}
		}
	}

	m_effectTime = 0;
	GetInitGameParam(&m_effectTime,"effectTime");

	//add button
	GetDokuritsuPrintMode();



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
	DELETEARRAY(m_place);
	DELETEARRAY(m_printZahyo);
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
	if (m_playStatusData != NULL)
	{
		for (int i=0;i<m_setNumber;i++)
		{
			ENDDELETECLASS(m_playStatusData[i]);
		}
		DELETEARRAY(m_playStatusData);
	}

	DELETEARRAY(m_setPlaceSetData);
	ENDDELETECLASS(m_radio);
}


int CCommonPrintStatus::Init(void)
{
	LoadBackBG();
	m_effectCount = 0;

	GetPlaceList();

	
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

	LoadCheckButtonPic();
	LoadUpdownButtonPic();
	LoadRadioButtonPic();


	InitCheckButton();
	InitUpdownButton();
	InitRadioButton();


	return -1;
}

void CCommonPrintStatus::LoadCheckButtonPic(void)
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

void CCommonPrintStatus::LoadUpdownButtonPic(void)
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

int CCommonPrintStatus::GetSetSelectSetNumber(void)
{
	int varData = 0;
	if (m_setPlaceSetSelectVar != -1)
	{
		varData = m_game->GetVarData(m_setPlaceSetSelectVar);
	}
	if (varData < 0) varData = 0;
	return varData;
}
void CCommonPrintStatus::SetSetSelectSetNumber(int n)
{
	if (m_setPlaceSetSelectVar != -1)
	{
		m_game->SetVarData(m_setPlaceSetSelectVar,n);
	}
}

void CCommonPrintStatus::LoadRadioButtonPic(void)
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
				return -1;
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

	PrintStatusSub(ps,TRUE);
//	for (int i=0;i<m_setNumber;i++)
//	{
//		m_playStatusData[i]->Print(ps);
//	}

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



int CCommonPrintStatus::PrintDokuristu(int nowMode)
{
	GetPlaceList();

	for (int i = 0; i < m_setNumber; i++)
	{
		int graphNumber = m_playStatusData[i]->GetGraphNumber();
		for (int k = 0; k < graphNumber; k++)
		{
			int varNumber = m_playStatusData[i]->GetVarNumber(k);
			int varData = m_game->GetVarData(varNumber);
			m_playStatusData[i]->SetData(k, varData);
		}
	}

	PrintStatusSub(100);


	return -1;
}

void CCommonPrintStatus::PrintStatusSub(int ps,BOOL mustPrint)
{
	for (int i = 0; i < m_setNumber; i++)
	{
		int onOff = 0;
		if (m_place[i] > 0)
		{
			onOff = 1;
		}
		/*
		if (m_onOffVar[i] != -1)
		{
			int varData = m_game->GetVarData(m_onOffVar[i]);
			if (varData > 0)
			{
				onOff = 1;
			}
		}
		*/

		if (onOff || mustPrint)
		{
			int pl = m_place[i];
			if (pl < 0) pl *= -1;
			if (pl > 0) pl--;

			POINT p = GetBaseZahyo(pl);

			m_playStatusData[i]->Print(p,ps);
//			m_playStatusData[i]->Print(m_printZahyo[pl], ps);
		}
	}

}


void CCommonPrintStatus::InitCheckButton(void)
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

void CCommonPrintStatus::InitUpdownButton(void)
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


void CCommonPrintStatus::InitRadioButton(void)
{
	if (m_radio == NULL) return;

	int select = GetSetSelectSetNumber();
	m_radio->SetRadio(select);
	m_radio->Init(select);
}


void CCommonPrintStatus::GetPlaceList(void)
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


void CCommonPrintStatus::ChangePlace(int set, int delta)
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

void CCommonPrintStatus::SetPlaceToVar(void)
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

void CCommonPrintStatus::ChangeOnOff(int set)
{
	if (m_place == NULL) return;
	if (m_onOffVar == NULL) return;

	m_place[set] *= -1;
}


POINT CCommonPrintStatus::GetBaseZahyo(int place)
{
	int selectSet = GetSetSelectSetNumber();
	return m_setPlaceSetData[selectSet * m_setNumber + place];
}

