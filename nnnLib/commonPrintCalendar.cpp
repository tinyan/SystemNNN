//
// commonPrintCalendar.cpp
//


#include <windows.h>

#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"

#include "commonPrintCalendar.h"


int CCommonPrintCalendar::m_modeLength[] = {10,20,30,10};


CCommonPrintCalendar::CCommonPrintCalendar(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTCALENDAR_MODE);
//	m_classNumber = PRINTCALENDAR_MODE;
//	m_fillColorR = 255;
//	m_fillColorG = 255;
//	m_fillColorB = 255;
//	m_nextMode = LOGO_MODE;

	LoadSetupFile("PrintCalendar",32);

//	GetInitGameParam(&m_fillColorR,"fillColorR");
//	GetInitGameParam(&m_fillColorG,"fillColorG");
//	GetInitGameParam(&m_fillColorB,"fillColorB");

//	GetInitGameParam(&m_nextMode,"nextMode");

	GetFadeInOutSetup();

}


CCommonPrintCalendar::~CCommonPrintCalendar()
{
	End();
}

void CCommonPrintCalendar::End(void)
{
}



int CCommonPrintCalendar::Init(void)
{
	int month = m_dayMonth / 100;
	int day = m_dayMonth % 100;

	month--;
	day--;

	m_commonBG->LoadDWQ("sys\\days_bg");
	m_commonBG->Put(0,0,FALSE);
	m_commonParts->LoadDWQ("sys\\ta_days_month");
	int sizeX = 215;
	int sizeY = 123;
	m_commonParts->Blt(172,193,sizeX*month,0,sizeX,sizeY,TRUE);

	m_commonParts->LoadDWQ("sys\\ta_days_day");
	sizeX = 170;
	sizeY = 124;
	int srcX = (day % 7) * sizeX;
	int srcY = (day / 7) * sizeY;
	m_commonParts->Blt(172+229,193,srcX,srcY,sizeX,sizeY,TRUE);

	if (m_nokori >= 0)
	{
		m_commonParts->LoadDWQ("sys\\ta_days_nokori1");
		m_commonParts->Blt(312,342,0,0,54,40,TRUE);

		m_commonParts->LoadDWQ("sys\\ta_days_nokori2");
		m_commonParts->Blt(312+170,342,0,0,30,40,TRUE);
	}

	m_commonBG->GetScreen();

	m_commonParts->LoadDWQ("sys\\ta_days_day2");

	m_mode = 0;
	m_count = 0;
	m_countMax = m_modeLength[m_mode];
	return -1;
}

int CCommonPrintCalendar::Calcu(void)
{
	m_count++;
	if ((m_count >= m_countMax) || (m_mouseStatus->CheckClick(0)))
	{
		m_mode++;
		m_count = 0;
		if (m_nokori < 0)
		{
			if (m_mode == 1)
			{
				m_mode++;
			}
		}
		else
		{
			if (m_mode == 2)
			{
				m_commonBG->Put(0,0,FALSE);
				PutNokori(TRUE);
				PutNokori(FALSE);
				m_commonBG->GetScreen();
			}
		}
		if (m_mode >= 4)
		{
			m_game->SetYoyaku();
		}
		m_countMax = m_modeLength[m_mode];
		return -1;
	}

	return -1;
}

int CCommonPrintCalendar::Print(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (m_mode == 0)
	{
		CAreaControl::SetNextAllPrint();

		int ps = (m_count * 100) / m_countMax;
		if (ps<1) ps = 1;
		if (ps > 99) ps = 99;

		CAllGraphics::FillScreen();
		m_commonBG->TransLucentBlt(0,0,0,0,screenSizeX,screenSizeY,ps);

	}

	if (m_mode == 1)
	{
		CAreaControl::SetNextAllPrint();
		m_commonBG->Put(0,0,FALSE);
		PrintNokori();
	}

	if (m_mode == 2)
	{
		m_commonBG->Put(0,0,FALSE);
	}

	if (m_mode == 3)
	{
		CAreaControl::SetNextAllPrint();

		int ps = ((m_countMax - m_count) * 100) / m_countMax;
		if (ps<1) ps = 1;
		if (ps > 99) ps = 99;

		CAllGraphics::FillScreen();
		m_commonBG->TransLucentBlt(0,0,0,0,screenSizeX,screenSizeY,ps);
	}

	if (m_mode == 4)
	{
		CAllGraphics::FillScreen();
		CAreaControl::SetNextAllPrint();
	}

	return 0;
}


void CCommonPrintCalendar::PutNokori(BOOL high, int ps)
{
	if (m_nokori < 0) return;

	int sizeX = 46;
	int sizeY = 52;

	if (high)
	{
		if (m_nokori >= 10)
		{
			int srcX = m_nokori / 10;
			srcX *= sizeX;
			m_commonParts->TransLucentBlt3(372,332,srcX,0,sizeX,sizeY,ps);
		}
	}
	else
	{
		int putX = 372 + 48;
		if (m_nokori < 10)
		{
			putX -= 24;
		}

		int srcX = (m_nokori % 10);
		srcX *= sizeX;
		m_commonParts->TransLucentBlt3(putX,332,srcX,0,sizeX,sizeY,ps);
	}
}

void CCommonPrintCalendar::PrintNokori(void)
{
	if (m_nokori < 0) return;

	int ps1 = (m_count * 200) / m_countMax;
	int ps2 = (m_count * 200) / m_countMax - 100;


	if (ps1<0) ps1 = 0;
	if (ps1>99) ps1 = 99;

	if (ps2<0) ps2 = 0;
	if (ps2>99) ps2 = 99;

	if (ps1 > 0) PutNokori(TRUE,ps1);
	if (ps2 > 0) PutNokori(FALSE,ps2);

}
