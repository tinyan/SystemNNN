//
//
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "systemPicture.h"
#include "namelist.h"
#include "FpsPrint.h"

char CFpsPrint::m_defaultFontName[]="nekofont";

CFpsPrint::CFpsPrint(CNameList* lpNameList)
{
	m_fps = 0;
	m_fpsCount = 0;

	m_setup = lpNameList;

	m_sizeX = 16;
	m_sizeY = 16;

	GetInitGameParam(&m_sizeX,"fpsFontSizeX");
	GetInitGameParam(&m_sizeY,"fpsFuntSizeY");

	m_printX = 0;
	m_printY = CMyGraphics::GetScreenSizeY() - m_sizeY*2;
	GetInitGameParam(&m_printX,"FpsPrintX");
	GetInitGameParam(&m_printY,"FpsPrintY");

	m_fontName = m_defaultFontName;
	GetInitGameString(&m_fontName,"fpsFileName");
	m_pic = CSystemPicture::GetSystemPicture(m_fontName);

	m_oldTime = GetLocalTimeCount();
}


CFpsPrint::~CFpsPrint()
{
	End();
}


void CFpsPrint::End(void)
{
//	ENDDELETECLASS(m_setup);
}






void CFpsPrint::Print(void)
{
	m_fpsCount++;

	LONGLONG newTime = GetLocalTimeCount();
	if ((newTime - m_oldTime) >= 1000)
	{
		m_fps = (int)((m_fpsCount * 1000) / (newTime - m_oldTime));
		if (m_fps>999) m_fps = 999;
		m_fpsCount = 0;
		m_oldTime = newTime;
	}


	int dh = m_fps / 100;
	int dm = m_fps - dh*100;
	int dl = dm % 10;
	dm /= 10;


	int putX = m_printX;
	int putY = m_printY;

	int sizeX = m_sizeX;
	int sizeY = m_sizeY;

	if (dh>0) m_pic->Blt(putX,putY,dh*sizeX,sizeY,sizeX,sizeY,FALSE);
	m_pic->Blt(putX+16,putY,dm*sizeX,sizeY,sizeX,sizeY,FALSE);
	m_pic->Blt(putX+32,putY,dl*sizeX,sizeY,sizeX,sizeY,FALSE);

	CAreaControl::AddArea(putX,putY,sizeX*3,sizeY);
}


BOOL CFpsPrint::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CFpsPrint::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}

LONGLONG CFpsPrint::GetLocalTimeCount(void)
{

	SYSTEMTIME tm;
	GetLocalTime(&tm);

	int hour = tm.wHour;
	int minute = tm.wMinute;
	int second = tm.wSecond;
	int millSecond = tm.wMilliseconds;

	LONGLONG d = hour;
	d *= 60;
	d += minute;
	d *= 60;
	d += second;
	d *= 1000;
	d += millSecond;

	return d;

}

/*_*/

