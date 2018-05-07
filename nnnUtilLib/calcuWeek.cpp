#include <windows.h>

#include "calcuWeek.h"

CCalcuWeek::CCalcuWeek()
{
}

CCalcuWeek::~CCalcuWeek()
{
	End();
}

void CCalcuWeek::End(void)
{
	//
}

int CCalcuWeek::CalcuWeek(int date)
{
	int month = date / 100;
	int day = date % 100;
	int year = 2000;
	return CalcuWeek(year,month,day);
}

int CCalcuWeek::CalcuWeek(int month,int day)
{
	int year = 2000;
	return CalcuWeek(year,month,day);
}

int CCalcuWeek::CalcuWeek(int year,int month,int day,BOOL year0is2000)
{

	int month2 = month;
	int year2 = year;

	if (month2 <= 2)
	{
		year2 -= 1;
		month2 += 12;
	}

	int week = (year2 + year2/4 - year2/100 + year2/400 + (13*month2+8)/5 + day);
	week %= 7;

	return week;
}

/*_*/


