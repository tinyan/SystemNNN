//
// SelectHeroin.cpp
//


#include <windows.h>
#include <Math.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\areaControl.h"



#include "..\nnnUtilLib\nameList.h"
#include "..\nnnUtilLib\myMessage.h"


#include "..\nnnUtilLib\superButtonPicture.h"



#include "..\nnnUtilLib\CommonButton.h"
#include "..\nnnUtilLib\superButtonSetup.h"


#include "..\nnnUtilLib\commonKeyList.h"

#include "..\nnnUtilLib\suuji.h"


#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\nnnButtonStatus.h"

#include "..\nnnUtilLib\commonUpDownButtonGroup.h"

#include "commonSystemSoundName.h"
#include "commonSystemParamName.h"


#include "commonMode.h"


#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonSelectHeroin.h"


char CCommonSelectHeroin::m_defaultBGFileName[] = "bg_selectheroin";
//char CCommonSelectHeroin::m_defaultOkFileName[] = "ta_story_next01";
//char CCommonSelectHeroin::m_defaultNextFileName[] = "ta_story_ok01";



CCommonSelectHeroin::CCommonSelectHeroin(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTHEROIN_MODE);
//	m_classNumber = SELECTHEROIN_MODE;
//	m_game2 = lpGame;

	m_message = m_game->GetMyMessage();

	m_heroinList = new CNameList();
	m_heroinList->LoadFile("nya\\heroin.xtx");

	LoadSetupFile("SelectHeroin",128);

	GetBackExecSetup();
	GetAllPrintSetup();



	m_nextButtonFlag = 0;
	m_okButtonFlag = 1;
	GetInitGameParam(&m_nextButtonFlag,"nextButtonFlag");
	GetInitGameParam(&m_okButtonFlag,"okButtonFlag");

	m_nextButtonSetup = NULL;
	m_okButtonSetup = NULL;
	m_nextButton = NULL;
	m_okButton = NULL;

	if (m_nextButtonFlag)
	{
		m_nextButtonSetup = new CSuperButtonSetup(m_setup,"next");
		m_nextButton = new CCommonButton();
		m_nextButtonSetup->SetupButtonStatus(m_nextButton);

		m_nextButton->SetPicture(CSuperButtonPicture::GetPicture(3));
	}

	if (m_okButtonFlag)
	{
		m_okButtonSetup = new CSuperButtonSetup(m_setup,"ok");
		m_okButton = new CCommonButton();
		m_okButtonSetup->SetupButtonStatus(m_okButton);

		m_okButton->SetPicture(CSuperButtonPicture::GetPicture(4));
	}



	m_createBufferFlag = 0;
	GetInitGameParam(&m_createBufferFlag,"createBufferFlag");	//“––Ê”ñŒöŠJ

	m_heroinPrintMax = 4;
	GetInitGameParam(&m_heroinPrintMax,"heroinPrintMax");

	if (m_heroinPrintMax > 12)
	{
		m_heroinPrintMax = 12;
	}


	int i = 0;
	for (i=0;i<12;i++)
	{
		if (i<m_heroinPrintMax)
		{
			if (m_createBufferFlag)
			{
				m_heroinPic[i] = new CPicture();
			}
			else
			{
				//6-15,2-3
				if (i<10)
				{
					m_heroinPic[i] = m_game->GetEffectPicture((6+i) % 16);
				}
				else
				{
					m_heroinPic[i] = m_game->GetEffectPicture((6+i+2) % 16);
				}
			}
		}
		else
		{
			m_heroinPic[i] = NULL;
		}
	}


	LPSTR varName = NULL;

	for (i=0;i<m_heroinPrintMax;i++)
	{
		char name[256];
		wsprintf(name,"heroinVarName%d",i+1);
		GetInitGameString(&varName,name);
		m_heroinCheckVarNumber[i] = m_game->GetVarNumber(varName);
	}

	GetInitGameString(&varName,"nextButtonVarName");
	m_nextCheckVarNumber = m_game->GetVarNumber(varName);


	GetInitGameString(&varName,"returnVarName");
	m_returnVarNumber = m_game->GetVarNumber(varName);



	m_minTurnNumber = 1;
	GetInitGameParam(&m_minTurnNumber,"minTurnNumber");

	m_turnFrame = 10;
	GetInitGameParam(&m_turnFrame,"turnFrame");

	m_percent1 = 20;
	m_percent2 = 110;

	GetInitGameParam(&m_percent1,"percent1");
	GetInitGameParam(&m_percent2,"percent2");

	m_circleX = 250;
	m_circleY = 120;

	GetInitGameParam(&m_circleX,"circleX");
	GetInitGameParam(&m_circleY,"circleY");

	m_deltaAngle = 15;
	GetInitGameParam(&m_deltaAngle,"deltaAngle");


	m_nowSelectHeroin = 0;

	m_superMode = 0;
	GetInitGameParam(&m_superMode,"superButtonFlag");

	m_filenameBG = m_defaultBGFileName;
	GetInitGameString(&m_filenameBG,"filenameBG");

	m_filenamePlate = NULL;
	GetInitGameString(&m_filenamePlate,"filenamePlate");

	m_platePrintX = 0;
	m_platePrintY = 0;

	GetInitGameParam(&m_platePrintX,"plateX");
	GetInitGameParam(&m_platePrintY,"plateY");

	CreateUpDownButton();

	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
}


CCommonSelectHeroin::~CCommonSelectHeroin()
{
	End();
}


void CCommonSelectHeroin::End(void)
{
	ENDDELETECLASS(m_okButton);
	ENDDELETECLASS(m_nextButton);
	ENDDELETECLASS(m_okButtonSetup);
	ENDDELETECLASS(m_nextButtonSetup);

	if (m_createBufferFlag)
	{
		for (int i=0;i<12;i++)
		{
			ENDDELETECLASS(m_heroinPic[i]);
		}
	}

	ENDDELETECLASS(m_heroinList);
}



int CCommonSelectHeroin::Init(void)
{
	char filename[256];
	int i = 0;

//	m_game->StopMusic();

	m_game->SetDefaultFrameRate();

	m_page = 0;
	m_heroinNinzu = 0;
	m_buttonMode = 0;

	m_pageMax = 5;


	m_startupWait = 3;






	m_nextButtonExistFlag = 0;
	m_heroinNinzu = 0;

	m_errorFlag = 0;

	if (m_game->GetVarData(m_nextCheckVarNumber) != 0) m_nextButtonExistFlag = 1;

	for (i=0;i<m_heroinPrintMax;i++)
	{
		int var = m_heroinCheckVarNumber[i];
		if (var != -1)
		{
			int dd = m_game->GetVarData(var);
			if (dd > 0)
			{
				m_heroinNumber[m_heroinNinzu] = i;
				m_heroinFace[m_heroinNinzu] = dd-1;
				m_heroinNinzu++;
			}
		}
	}

//	m_pageMax = m_heroinNinzu;
//	if (m_pageMax<1) m_pageMax = 1;

	m_page = 2;
	//



	LoadUpDownButtonPic();
	SetUpDownZahyo();
	m_updown->SetPage(m_page);
	m_updown->SetPageMax(m_pageMax);


	if ((m_heroinNinzu <= 0) && (m_nextButtonExistFlag == 0))
	{
		m_errorFlag = TRUE;
	}


	m_devideTh = 360;
	if (m_heroinNinzu>0)
	{
		m_devideTh = 360 / m_heroinNinzu;
	}

	//load heroinpic
	for (i=0;i<m_heroinNinzu;i++)
	{
		LPSTR heroinName = m_heroinList->GetName(m_heroinNumber[i] + m_heroinFace[i] * m_heroinPrintMax);
		wsprintf(filename,"ta\\%s",heroinName);
		m_heroinPic[i]->LoadDWQ(filename);
	}

	if (m_filenamePlate != NULL)
	{
		wsprintf(filename,"sys\\%s",m_filenamePlate);
		m_platePic->LoadDWQ(filename);
	}


	//load back
	if (m_backScriptFlag == 0)
	{
		wsprintf(filename,"sys\\%s",m_filenameBG);
		m_commonBG->LoadDWQ(filename);
	}

	m_nowSelectHeroin = GetLastSelect();

	m_turnHoukou = 0;
	m_turnCount = 0;

	InitAllButton();

//	m_nowSelectNumber = -1;
//	m_maeSelectNumber = -1;
//	m_selectedNumber = -1;

	return -1;
}



int CCommonSelectHeroin::Calcu(void)
{
	if (m_turnHoukou != 0)
	{
		m_turnCount++;
		if (m_turnCount >= m_turnFrame)
		{
			m_nowSelectHeroin += m_turnHoukou;
			m_nowSelectHeroin += m_heroinNinzu;

			if (m_heroinNinzu > 0)
			{
				m_nowSelectHeroin %= m_heroinNinzu;
			}
			else
			{
				m_nowSelectHeroin = 0;
			}

			SetLastSelect(m_nowSelectHeroin);

			m_turnCount = 0;
			m_turnHoukou = 0;
			InitAllButton();
		}
		return -1;
	}



	int rt = m_game->CalcuOptionButton();

	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessCommonButton(rt);
		if (nm == 0)
		{
			m_game->TaihiAllEffect();

			m_game->SetSaveMode(SELECTHEROIN_MODE);
			m_game->MakeMiniCG();
			m_game->SetCommonBackMode(SYSTEMMENU_MODE,SELECTHEROIN_MODE);
			return SYSTEMMENU_MODE;
		}

		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_STARTCLICK) return -1;
		if (st == NNNBUTTON_CLICKING) return -1;
	}


	if ((m_heroinNinzu >= m_minTurnNumber) && (m_heroinNinzu > 0))
	{
		rt = m_updown->Calcu(m_inputStatus);
		if (rt != NNNBUTTON_NOTHING)
		{
			int nm = ProcessCommonButton(rt);
			if (nm >= 0)
			{
				if (nm == 1)
				{
					m_turnHoukou = 1;
				}
				else if (nm == 3)
				{
					m_turnHoukou = -1;
				}

				m_turnCount = 0;

				m_updown->SetPage(2);
				m_updown->Init();
			}

			int st = CCommonButton::GetButtonStatus(rt);
			if (st == NNNBUTTON_STARTCLICK) return -1;
			if (st == NNNBUTTON_CLICKING) return -1;
		}
	}

	if (m_heroinNinzu > 0)
	{
		rt = m_okButton->Calcu(m_inputStatus);
		if (rt != NNNBUTTON_NOTHING)
		{
			int nm = ProcessCommonButton(rt);

			if (nm >= 0)
			{

				SetReturnHeroinData(m_nowSelectHeroin+1);
				//m_game->SetYoyaku();
				m_exitModeFlag = TRUE;
				return ReturnFadeOut(-1);
			}
			int st = CCommonButton::GetButtonStatus(rt);
			if (st == NNNBUTTON_STARTCLICK) return -1;
			if (st == NNNBUTTON_CLICKING) return -1;
		}
	}

	if (m_nextButtonExistFlag)
	{
		rt = m_nextButton->Calcu(m_inputStatus);

		if (rt != NNNBUTTON_NOTHING)
		{
			int nm = ProcessCommonButton(rt);
			if (nm >= 0)
			{
				SetReturnHeroinData(0);
				m_exitModeFlag = TRUE;
				return ReturnFadeOut(-1);
			}
			int st = CCommonButton::GetButtonStatus(rt);
			if (st == NNNBUTTON_STARTCLICK) return -1;
			if (st == NNNBUTTON_CLICKING) return -1;
		}
	}

	int nextMode = m_game->ProcessGameKey(SELECTHEROIN_MODE);
	if (nextMode != -1)
	{
		m_exitModeFlag = FALSE;
		return ReturnFadeOut(nextMode);
	}

	return -1;
}



int CCommonSelectHeroin::Print(void)
{
	CAreaControl::SetNextAllPrint();
	PrintBackScriptOrBG();

	BOOL b = CAreaControl::CheckAllPrintMode();

	if (m_backScriptFlag)
	{
	}



	int heroinTh[12];
	int heroinDist[12];
	int heroinJunban[12];

	int i = 0;
	for (i=0;i<m_heroinNinzu;i++)
	{
		int k = (-i + m_nowSelectHeroin + 10*m_heroinNinzu) % m_heroinNinzu;
		
		int th = 90+m_deltaAngle+k*m_devideTh;

		th += (m_turnHoukou * ((m_turnCount * m_devideTh) / m_turnFrame));
		th += 360*2;
		th %= 360;

		heroinTh[i] = th;

		double t = (double)th;
		t *= 3.14159*2;
		t /= 360.0;

		heroinDist[i] = (int)(sin(t)*100+0.5);
		heroinJunban[i] = i;
	}


	//sort
	
	if (m_heroinNinzu>1)
	{
		int j = 0;
		for (j=0;j<m_heroinNinzu-1;j++)
		{
			for (i=j+1;i<m_heroinNinzu;i++)
			{
				if (heroinDist[j] > heroinDist[i])
				{
					int tmp = heroinDist[j];
					heroinDist[j] = heroinDist[i];
					heroinDist[i] = tmp;

					tmp = heroinJunban[j];
					heroinJunban[j] = heroinJunban[i];
					heroinJunban[i] = tmp;
				}
			}
		}
	}



	for (i=0;i<m_heroinNinzu;i++)
	{
		int heroin = heroinJunban[i];

		double t = (double)heroinTh[heroin];
		t *= 3.14159*2.0;
		t /= 360.0;

		int dx = (int)(cos(t) * (double)m_circleX + 0.5);
		int ps = (int)((sin(t)+1.0)/2 * (m_percent2-m_percent1));
		ps += m_percent1;
		if (ps<1) ps = 1;
		if (ps>100) ps = 100;

		int dy = (int)((1.0-sin(t))/2 * (double)m_circleY + 0.5);
		int putX = dx;
		int putY = dy;

		if (ps == 100)
		{
			m_heroinPic[heroin]->Put(putX,putY,TRUE);
		}
		else
		{
			m_heroinPic[heroin]->TransLucentBlt3(putX,putY,0,0,800,600,ps);
		}


	}


	if (m_filenamePlate != NULL)
	{
		m_platePic->Put(m_platePrintX,m_platePrintY,TRUE);
	}


	if (1)
	{
		if ((m_heroinNinzu>0) && (m_heroinNinzu >= m_minTurnNumber))
		{
			m_updown->Print(TRUE);
		}
	}

	if ((m_heroinNinzu>0) && (m_turnHoukou == 0))
	{
		m_okButton->Print(TRUE);
	}

	if (m_turnHoukou == 0)
	{
		if (m_nextButtonExistFlag)
		{
			m_nextButton->Print(TRUE);
		}
	}


	m_game->PrintOptionButtonYoyaku();

	return 0;
}




void CCommonSelectHeroin::CreateStartScreen(void)
{
	//menu setup?

	//script exec?

	Print();
}



/*
void CCommonSelectHeroin::CreateNextButton(void)
{
	m_nextPrintX = 600;
	m_nextPrintY = 500;

	GetInitGameParam(&m_nextPrintX,"nextPrintX");
	GetInitGameParam(&m_nextPrintY,"nextPrintY");


	m_nextSizeX = 170;
	m_nextSizeY = 52;

	GetInitGameParam(&m_nextSizeX,"nextSizeX");
	GetInitGameParam(&m_nextSizeY,"nextSizeY");


	LPSTR name1 = "ta_story_next01";
	GetInitGameString(&name1,"fileNameNext");

//	m_updownButtonAnime = 1;
	m_updownButtonType = 0;	//0:‚±‚ÌÝ’è‚Å‚Â‚­‚é 1:CGame‚©‚ç‚à‚ç‚¤

//	GetInitGameParam(&m_updownButtonAnime,"updownButtonAnime");
//	GetInitGameParam(&m_updownButtonType,"updownButtonType");

//	m_superUpDownButtonFlag = 0;
//	GetInitGameParam(&m_superUpDownButtonFlag,"superUpDownButtonFlag");

	CPicture* nextPic = m_game->GetSystemPicture(name1);

	CPicture* lpBGPic = NULL;
	BOOL transFlag = TRUE;
	BOOL tateCutFlag = FALSE;

//@@@	m_nextButton = new CMyCommonButton(nextPic,m_nextPrintX, m_nextPrintY,m_nextSizeX,m_nextSizeY,0,0,transFlag,lpBGPic,tateCutFlag);
//@@@	m_nextButton->SetSuperMode();
	m_superButtonSetup->SetupButtonStatus(m_nextButton);
}


void CCommonSelectHeroin::CreateOkButton(void)
{
	m_okPrintX = 600;
	m_okPrintY = 500;

	GetInitGameParam(&m_nextPrintX,"okPrintX");
	GetInitGameParam(&m_nextPrintY,"okPrintY");


	m_okSizeX = 170;
	m_okSizeY = 52;

	GetInitGameParam(&m_okSizeX,"okSizeX");
	GetInitGameParam(&m_okSizeY,"okSizeY");


	LPSTR name1 = "ta_story_ok01";
	GetInitGameString(&name1,"fileNameOk");

	CPicture* okPic = m_game->GetSystemPicture(name1);

	CPicture* lpBGPic = NULL;
	BOOL transFlag = TRUE;
	BOOL tateCutFlag = FALSE;

//@@@	m_okButton = new CMyCommonButton(okPic,m_okPrintX, m_okPrintY,m_okSizeX,m_okSizeY,0,0,transFlag,lpBGPic,tateCutFlag);
//@@@	m_okButton->SetSuperMode();
	m_superButtonSetupOk->SetupButtonStatus(m_okButton);
}
*/


void CCommonSelectHeroin::StartUserCommand(int paraKosuu,int* paraPtr)
{
	//
}


void CCommonSelectHeroin::StartSelectHeroin(void)
{
	SetLastSelect(0);
}


void CCommonSelectHeroin::SetReturnHeroinData(int n)
{
	if (n == 0)
	{
		m_game->SetVarData(m_returnVarNumber,1);
	}
	else
	{
		int heroinNumber = m_heroinNumber[n-1];
		m_game->SetVarData(m_returnVarNumber,heroinNumber+1);
	}
}


int CCommonSelectHeroin::GetLastSelect(void)
{
	int heroin = m_game->GetLastSelectHeroinNumber();
	
	for (int i=0;i<m_heroinNinzu;i++)
	{
		if (m_heroinNumber[i] == heroin)
		{
			return i;
		}
	}

	return 0;
}


void CCommonSelectHeroin::SetLastSelect(int n)
{
	int heroin = m_heroinNumber[n];
	m_game->SetLastSelectHeroinNumber(heroin);
}

void CCommonSelectHeroin::InitAllButton(void)
{
	m_buttonMode = 0;
	m_page = 2;
//@@@	m_updown->SetUpDownParam(m_pageMax,m_page);
	m_updown->Init();

	m_nextButton->Init();
	m_okButton->Init();
}


void CCommonSelectHeroin::FinalExitRoutine(void)
{
//	return;

	if (m_exitModeFlag)
	{
//		m_game->SetVarData(m_selectPlaceResultVarNumber,m_selectedNumber + 1);
		m_game->SetYoyaku();
	}
}

int CCommonSelectHeroin::EndMode(void)
{
	return -1;

	if (m_exitModeFlag)
	{
//		m_game->SetVarData(m_selectPlaceResultVarNumber,m_selectedNumber + 1);
		m_game->SetYoyaku();
	}
	return -1;
}
