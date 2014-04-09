//
// commonOverrap.cpp
//


#include <windows.h>

#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"


#include "commonOverrap.h"


CCommonOverrap::CCommonOverrap(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTOVERRAP_MODE);
//	m_classNumber = PRINTOVERRAP_MODE;

	m_shakin = 0;
	LoadSetupFile("Overrap",32);

	m_optionButtonPrintFlag = 1;
	m_sceneButtonPrintFlag = 1;

	GetInitGameParam(&m_optionButtonPrintFlag,"optionButtonPrintFlag");
	GetInitGameParam(&m_sceneButtonPrintFlag,"sceneButtonPrintFlag");
}


CCommonOverrap::~CCommonOverrap()
{
	End();
}

void CCommonOverrap::End(void)
{
}



int CCommonOverrap::Init(void)
{
	m_pic1 = m_game->GetOverrapPic(0);
	m_pic2= m_game->GetOverrapPic(1);

	m_count = 0;
	m_type = m_game->GetOverrapType();
	m_length = m_game->GetOverrapLength();

	return -1;
}

int CCommonOverrap::Calcu(void)
{
	m_shakin = 0;

	int dontPlay = m_game->GetDontPlayMode();

	if (dontPlay == 0)
	{
		BOOL f = FALSE;
		if (m_mouseStatus->CheckClick()) f = TRUE;
		if (m_game->CheckMessageSkipFlag()) f = TRUE;

		if (f)
		{
			m_game->ShakinHensai(-1);
			m_count = m_length;
			m_game->SetYoyaku();
			return -1;
		}
	}



	int kaeseru = m_length - m_count;
	if (kaeseru<=0) kaeseru = 1;

	int kaeshita = m_game->ShakinHensai(kaeseru);

	m_count += kaeshita;
	if (m_count >= m_length)
	{
		m_count = m_length;
		m_game->SetYoyaku();
		return -1;
	}


	//opening mode‚Ìê‡‚Ìˆ—
	if (m_game->CheckOpeningMode())
	{
		if ((m_mouseStatus->GetTrig(0)) || (m_mouseStatus->GetTrig(1)))
		{
			m_game->ShakinHensai(-1);
			m_game->SetOpeningMode(FALSE);
			return TITLE_MODE;	//‚Åok‚È‚Ì‚©??
		}
		return -1;
	}

	//ƒfƒ‚ƒ‚[ƒh‚Ìê‡

	return -1;

/*
	m_shakin = 0;

	int dontPlay = m_game->GetDontPlayMode();

	if (dontPlay == 0)
	{
		if (m_mouseStatus->CheckClick()) m_count = m_length;
		if (m_game->CheckMessageSkipFlag()) m_count = m_length;
	}

	m_count++;
	

	int paste = m_game->GetPastTime();
	int frameRate = m_game->GetFrameTime();
	if (frameRate<1) frameRate = 1;

	int deltaPaste = 0;
	if (paste>=frameRate)
	{
		deltaPaste = paste / frameRate;
	}

	if (m_game->CheckNoSkipFrame()) deltaPaste = 0;

	if (deltaPaste>0)
	{
		for (int i=0;i<deltaPaste;i++)
		{
			if (m_count+deltaPaste>m_length+1)
			{
				m_shakin++;
			}
			else
			{
				m_count++;
			}
		}
	}

	if (m_count > m_length)
	{
		m_count = m_length;
		m_game->SetYoyaku();
		return -1;
	}

	//opening mode‚Ìê‡‚Ìˆ—
	if (m_game->CheckOpeningMode())
	{
		if ((m_mouseStatus->GetTrig(0)) || (m_mouseStatus->GetTrig(1)))
		{
			m_game->SetOpeningMode(FALSE);
			return TITLE_MODE;	//‚Åok‚È‚Ì‚©??
		}
		return -1;
	}

*/
	return -1;
}


int CCommonOverrap::Print(void)
{
	CAreaControl::SetNextAllPrint();




	if (m_game->CheckDemoMode() == FALSE)
	{
		if (m_game->CheckOpeningMode() == FALSE)
		{
			if (m_game->CheckSceneMode() == FALSE)
			{
				if (m_optionButtonPrintFlag)
				{
					m_game->PrintOptionButtonYoyaku();
				}
			}
			else
			{
				if (m_sceneButtonPrintFlag)
				{
					m_game->PrintSceneButtonYoyaku();
				}
			}
		}
	}

	m_game->PrintOverrap(m_count);

	return -1;
}

void CCommonOverrap::ResetShakin(void)
{
	m_shakin = 0;
}


int CCommonOverrap::GetShakin(void)
{
	return m_shakin;
}
