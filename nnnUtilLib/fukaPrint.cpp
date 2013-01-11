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
#include "fukaPrint.h"

char CFukaPrint::m_defaultFontName[]="nekofont";

CFukaPrint::CFukaPrint(CNameList* lpNameList)
{
	m_fuka = 0;
	m_fukaStart = 0;
	m_fukaCount = 0;

//	m_setup = new CSetupList();
//	m_setup->LoadSetupFile("fukaPrint");
	m_setup = lpNameList;


	m_sizeX = 16;
	m_sizeY = 16;

	GetInitGameParam(&m_sizeX,"fukaFontSizeX");
	GetInitGameParam(&m_sizeY,"fukaFuntSizeY");

	m_printX = 0;
	m_printY = CMyGraphics::GetScreenSizeY() - m_sizeY;
	GetInitGameParam(&m_printX,"fukaPrintX");
	GetInitGameParam(&m_printY,"fukaPrintY");

	m_fontName = m_defaultFontName;
	GetInitGameString(&m_fontName,"fukaFileName");
	m_pic = CSystemPicture::GetSystemPicture(m_fontName);
}


CFukaPrint::~CFukaPrint()
{
	End();
}


void CFukaPrint::End(void)
{
//	ENDDELETECLASS(m_setup);
}





void CFukaPrint::SetStartTime(int startTime)
{
	m_fukaStart = startTime;
}

void CFukaPrint::CalcuFuka(int nowTime)
{
	m_fuka = nowTime - m_fukaStart;
}

void CFukaPrint::PrintFuka(int fuka)
{
	int d = m_fuka;
	if (fuka != -1) d = fuka;

	if (d>99) d = 99;
	if (d<1) d = 1;

	int dh = d / 10;
	int dl = d % 10;


	int putX = m_printX;
	int putY = m_printY;

	int sizeX = m_sizeX;
	int sizeY = m_sizeY;

	m_fukaCount++;
	m_fukaCount %= 20;

	int cd = ' ' - 32;
	if (m_fukaCount < 10) cd = '-' - 32;
	if (CAreaControl::CheckAllPrintMode()) cd = '+' - 32;

	m_pic->Blt(putX,putY,(cd % 16) * m_sizeX,(cd / 16)*m_sizeY,m_sizeX,m_sizeY,FALSE);

	m_pic->Blt(putX+16,putY,dh*sizeX,sizeY,sizeX,sizeY,FALSE);
	m_pic->Blt(putX+32,putY,dl*sizeX,sizeY,sizeX,sizeY,FALSE);

	CAreaControl::AddArea(putX,putY,sizeX*3,sizeY);
}


BOOL CFukaPrint::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CFukaPrint::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}

/*_*/

