#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "..\nnnUtilLib\nameList.h"
#include "..\nnnUtilLib\suuji.h"

#include "..\nnnUtilLib\calcuWeek.h"

#include "printGameDate.h"

char CPrintGameDate::m_defaultPicFileName[]= "ta_font";


CPrintGameDate::CPrintGameDate(CNameList* setup,LPSTR tagName,CPicture* lpBG)
{
	m_setup = setup;
	m_commonBG = NULL;
	if (m_commonBG == NULL)
	{
		m_bgPrintFlag = FALSE;
	}
	else
	{
		m_bgPrintFlag = TRUE;
	}

	m_timePic = NULL;
	m_weekPic = NULL;
	m_yearSuuji = NULL;
	m_monthSuuji = NULL;
	m_daySuuji = NULL;
	m_weekSuuji = NULL;

	char name[256];

	m_yearPrintFlag = 0;
	wsprintf(name,"%sYearPrintFlag",tagName);
	GetInitGameParam(&m_yearPrintFlag,name);

	m_monthPrintFlag = 1;
	wsprintf(name,"%sMonthPrintFlag",tagName);
	GetInitGameParam(&m_monthPrintFlag,name);

	m_dayPrintFlag = 1;
	wsprintf(name,"%sDayPrintFlag",tagName);
	GetInitGameParam(&m_dayPrintFlag,name);

	m_weekPrintFlag = 1;
	wsprintf(name,"%sWeekPrintFlag",tagName);
	GetInitGameParam(&m_weekPrintFlag,name);

	m_gameDateSlashPrintFlag = 1;
	wsprintf(name,"%sDateSlashPrintFlag",tagName);
	GetInitGameParam(&m_gameDateSlashPrintFlag,name);

	m_yearSlashPrintFlag = m_yearPrintFlag * 2 * m_gameDateSlashPrintFlag;
	wsprintf(name,"%sYearSlashPrintFlag",tagName);
	GetInitGameParam(&m_yearSlashPrintFlag,name);

	m_monthSlashPrintFlag = m_monthPrintFlag * 2 * m_gameDateSlashPrintFlag;
	wsprintf(name,"%sMonthSlashPrintFlag",tagName);
	GetInitGameParam(&m_monthSlashPrintFlag,name);

	m_daySlashPrintFlag = 0;
	wsprintf(name,"%sDaySlashPrintFlag",tagName);
	GetInitGameParam(&m_daySlashPrintFlag,name);

	m_weekYouPrintFlag = 1;
	wsprintf(name,"%sWeekYouPrintFlag",tagName);
	GetInitGameParam(&m_weekYouPrintFlag,name);
	m_weekBiPrintFlag = 2;
	wsprintf(name,"%sWeekBiPrintFlag",tagName);
	GetInitGameParam(&m_weekBiPrintFlag,name);

	int x = 0;
	int y = 0;

	int picSizeX = 16;
	int picSizeY = 16;

	int nextX = 16;

	if (m_yearPrintFlag || m_monthPrintFlag || m_dayPrintFlag)
	{
		wsprintf(name,"filename%sTimeFont",tagName);
		m_timePic = new CPicture();

		LPSTR timeFontFileName = m_defaultPicFileName;
		GetInitGameString(&timeFontFileName,name);

		char filename[256];
		wsprintf(filename,"sys\\%s",timeFontFileName);
		m_timePic->LoadDWQ(filename);

		wsprintf(name,"%sTimeFontSizeX",tagName);
		GetInitGameParam(&picSizeX,name);
		wsprintf(name,"%sTimeFontSizeY",tagName);
		GetInitGameParam(&picSizeY,name);
		m_timeFontSize.cx = picSizeX;
		m_timeFontSize.cy = picSizeY;
		nextX = picSizeX;

		wsprintf(name,"%sTimeFontNextX",tagName);
		GetInitGameParam(&nextX,name);
		m_timeFontNextX = nextX;
	}



	int baseX = 0;
	int baseY = 0;

	wsprintf(name,"%sTimePrintX",tagName);
	GetInitGameParam(&baseX,name);
	wsprintf(name,"%sTimePrintY",tagName);
	GetInitGameParam(&baseY,name);

	if (m_yearPrintFlag)
	{
		m_yearUpZeroFlag = 1;
		wsprintf(name,"%sYearUpZeroPrintFlag",tagName);
		GetInitGameParam(&m_yearUpZeroFlag,name);

		int keta = 4;

		x = baseX;
		y = baseY;
		wsprintf(name,"%sYearPrintX",tagName);
		GetInitGameParam(&x,name);
		wsprintf(name,"%sYearPrintY",tagName);
		GetInitGameParam(&y,name);

		m_yearZahyo.x = x;
		m_yearZahyo.y = y;

		m_yearSuuji = new CSuuji(m_timePic,picSizeX,picSizeY,keta,nextX,m_yearUpZeroFlag);

		baseX = x + nextX * 5;
		baseY = y;
	}

	if (m_monthPrintFlag)
	{
		m_monthUpZeroFlag = 1;
		wsprintf(name,"%sMonthUpZeroPrintFlag",tagName);
		GetInitGameParam(&m_monthUpZeroFlag,name);

		int keta = 2;

		x = baseX;
		y = baseY;
		wsprintf(name,"%sMonthPrintX",tagName);
		GetInitGameParam(&x,name);
		wsprintf(name,"%sMonthPrintY",tagName);
		GetInitGameParam(&y,name);

		m_monthZahyo.x = x;
		m_monthZahyo.y = y;

		m_monthSuuji = new CSuuji(m_timePic,picSizeX,picSizeY,keta,nextX,m_monthUpZeroFlag);

		baseX = x + nextX * 3;
		baseY = y;
	}

	if (m_dayPrintFlag)
	{
		m_dayUpZeroFlag = 1;
		wsprintf(name,"%sDayUpZeroPrintFlag",tagName);
		GetInitGameParam(&m_dayUpZeroFlag,name);

		int keta = 2;

		x = baseX;
		y = baseY;
		wsprintf(name,"%sDayPrintX",tagName);
		GetInitGameParam(&x,name);
		wsprintf(name,"%sDayPrintY",tagName);
		GetInitGameParam(&y,name);

		m_dayZahyo.x = x;
		m_dayZahyo.y = y;

		m_daySuuji = new CSuuji(m_timePic,picSizeX,picSizeY,keta,nextX,m_dayUpZeroFlag);

		baseX = x + nextX * 2;
		baseY = y;
		if (m_daySlashPrintFlag)
		{
			baseX += nextX;
		}
	}


	if (m_weekPrintFlag)
	{
		wsprintf(name,"filename%sWeekFont",tagName);
		m_weekPic = new CPicture();

		LPSTR weekFontFileName = m_defaultPicFileName;
		GetInitGameString(&weekFontFileName,name);

		char filename[256];
		wsprintf(filename,"sys\\%s",weekFontFileName);
		m_weekPic->LoadDWQ(filename);

		wsprintf(name,"%sWeekFontSizeX",tagName);
		GetInitGameParam(&picSizeX,name);
		wsprintf(name,"%sWeekFontSizeY",tagName);
		GetInitGameParam(&picSizeY,name);
		m_weekFontSize.cx = picSizeX;
		m_weekFontSize.cy = picSizeY;
		nextX = picSizeX;

		wsprintf(name,"%sWeekFontNextX",tagName);
		GetInitGameParam(&nextX,name);
		m_weekFontNextX = nextX;

		int keta = 1;

		x = baseX;
		y = baseY;
		wsprintf(name,"%sWeekPrintX",tagName);
		GetInitGameParam(&x,name);
		wsprintf(name,"%sWeekPrintY",tagName);
		GetInitGameParam(&y,name);

		m_weekZahyo.x = x;
		m_weekZahyo.y = y;

		m_weekSuuji = new CSuuji(m_weekPic,picSizeX,picSizeY,keta,nextX);
	}

	m_printX = 0;
	m_printY = 0;
	wsprintf(name,"%sDatePrintX",tagName);
	GetInitGameParam(&m_printX,name);
	wsprintf(name,"%sDatePrintY",tagName);
	GetInitGameParam(&m_printY,name);

	if (m_bgPrintFlag)
	{
		int allPrint = 0;
		GetInitGameParam(&allPrint,"mustAllPrint");
		if (allPrint)
		{
			m_bgPrintFlag = FALSE;
		}
	}
}


CPrintGameDate::~CPrintGameDate()
{
	End();
}

void CPrintGameDate::End(void)
{
	ENDDELETECLASS(m_weekSuuji);
	ENDDELETECLASS(m_daySuuji);
	ENDDELETECLASS(m_monthSuuji);
	ENDDELETECLASS(m_yearSuuji);
	ENDDELETECLASS(m_weekPic);
	ENDDELETECLASS(m_timePic);

}

void CPrintGameDate::Print(int date)
{
	POINT pt;
	pt.x = m_printX;
	pt.y = m_printY;
	Print(pt,date);
}

void CPrintGameDate::Print(int month,int day)
{
	POINT pt;
	pt.x = m_printX;
	pt.y = m_printY;
	Print(pt,2000,month,day);
}

void CPrintGameDate::Print(int year,int month,int day)
{
	POINT pt;
	pt.x = m_printX;
	pt.y = m_printY;
	Print(pt,year,month,day);
}


void CPrintGameDate::Print(POINT pt,int date)
{
	int year = 2000;
	int month = date / 100;
	int day = date % 100;
	Print(pt,year,month,day);
}

void CPrintGameDate::Print(POINT pt,int month,int day)
{
	Print(pt,2000,month,day);
}

void CPrintGameDate::Print(POINT pt,int year,int month,int day)
{
	int printX = pt.x;
	int printY = pt.y;

	if (m_bgPrintFlag)
	{
		if (m_yearPrintFlag)
		{
			int putX = printX + m_yearZahyo.x;
			int putY = printY + m_yearZahyo.y;
			int sizeY = m_timeFontSize.cy;
			int nextX = m_timeFontNextX;

			int sizeX = nextX * 3 + m_timeFontSize.cx;

			if (m_yearSlashPrintFlag)
			{
				sizeX += nextX;
			}
			Erase(putX,putY,sizeX,sizeY);
		}

		if (m_monthPrintFlag)
		{
			int putX = printX + m_monthZahyo.x;
			int putY = printY + m_monthZahyo.y;
			int sizeY = m_timeFontSize.cy;
			int nextX = m_timeFontNextX;

			int sizeX = nextX * 1 + m_timeFontSize.cx;
			if (m_monthSlashPrintFlag)
			{
				sizeX += nextX;
			}

			Erase(putX,putY,sizeX,sizeY);
		}

		if (m_dayPrintFlag)
		{
			int putX = printX + m_dayZahyo.x;
			int putY = printY + m_dayZahyo.y;
			int sizeY = m_timeFontSize.cy;
			int nextX = m_timeFontNextX;

			int sizeX = nextX * 1 + m_timeFontSize.cx;
			if (m_daySlashPrintFlag)
			{
				sizeX += nextX;
			}

			Erase(putX,putY,sizeX,sizeY);
		}

		if (m_weekPrintFlag)
		{
			int putX = printX + m_weekZahyo.x;
			int putY = printY + m_weekZahyo.y;
			int sizeY = m_weekFontSize.cy;
			int nextX = m_weekFontNextX;

			int sizeX = nextX * 2 + m_weekFontSize.cx;
			Erase(putX,putY,sizeX,sizeY);
		}
	}



	if (m_yearPrintFlag)
	{
		int putX = printX + m_yearZahyo.x;
		int putY = printY + m_yearZahyo.y;
		int sizeX = m_timeFontSize.cx;
		int sizeY = m_timeFontSize.cy;
		int nextX = m_timeFontNextX;

		m_yearSuuji->Print(putX,putY,year);

		putX += nextX * 4;
		if (m_yearSlashPrintFlag)
		{
			m_yearSuuji->Put(putX,putY,m_yearSlashPrintFlag-1+10);
		}
	}

	if (m_monthPrintFlag)
	{
		int putX = printX + m_monthZahyo.x;
		int putY = printY + m_monthZahyo.y;
		int sizeX = m_timeFontSize.cx;
		int sizeY = m_timeFontSize.cy;
		int nextX = m_timeFontNextX;
		
		m_monthSuuji->Print(putX,putY,month);

		putX += nextX * 2;
		if (m_monthSlashPrintFlag)
		{
			m_monthSuuji->Put(putX,putY,m_monthSlashPrintFlag-1+10);
		}
	}

	if (m_dayPrintFlag)
	{
		int putX = printX + m_dayZahyo.x;
		int putY = printY + m_dayZahyo.y;
		int sizeX = m_timeFontSize.cx;
		int sizeY = m_timeFontSize.cy;
		int nextX = m_timeFontNextX;
		
		m_daySuuji->Print(putX,putY,day);

		putX += nextX * 2;
		if (m_daySlashPrintFlag)
		{
			m_daySuuji->Put(putX,putY,m_daySlashPrintFlag-1+10);
		}
	}

	if (m_weekPrintFlag)
	{
		int putX = printX + m_weekZahyo.x;
		int putY = printY + m_weekZahyo.y;
		int sizeX = m_weekFontSize.cx;
		int sizeY = m_weekFontSize.cy;
		int nextX = m_weekFontNextX;

		int week = CCalcuWeek::CalcuWeek(year,month,day);
		m_weekSuuji->Print(putX,putY,week);

		putX += nextX;
		if (m_weekYouPrintFlag)
		{
			m_weekSuuji->Put(putX,putY,m_weekYouPrintFlag-1+10);
		}

		putX += nextX;
		if (m_weekBiPrintFlag)
		{
			m_weekSuuji->Put(putX,putY,m_weekBiPrintFlag-1+10);
		}

	}
}

void CPrintGameDate::Erase(int putX,int putY,int sizeX,int sizeY)
{
	if (m_commonBG == NULL) return;

	m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
	CAreaControl::AddArea(putX,putY,sizeX,sizeY);
}


BOOL CPrintGameDate::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CPrintGameDate::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CPrintGameDate::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CPrintGameDate::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}
