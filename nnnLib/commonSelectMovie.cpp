//
// commonSelectMovie.cpp
//


#include <windows.h>



#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"
#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\namelist.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonSelectMovie.h"



#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonBackButton.h"
#include "..\nnnUtilLib\commonupDownButtonGroup.h"
#include "..\nnnUtilLib\commonUpDownBack.h"
#include "..\nnnUtilLib\suuji.h"

#include "..\nnnUtilLib\pagePrint.h"



char CCommonSelectMovie::m_defaultBGFileName[] = "movie_bg";

char CCommonSelectMovie::m_defaultFont1FileName[] = "ta_font_movie1";
char CCommonSelectMovie::m_defaultFont2FileName[] = "ta_sl_font3";
char CCommonSelectMovie::m_defaultFont3FileName[] = "ta_sl_font3";
char CCommonSelectMovie::m_defaultCursorFileName[] = "ta_movie_cur";


CCommonSelectMovie::CCommonSelectMovie(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTMOVIE_MODE);
	m_classNumber = SELECTMOVIE_MODE;

	LoadSetupFile("SelectMovie",256);



	GetBackExecSetup();

	m_superMode = 0;
	GetInitGameParam(&m_superMode, "superButtonFlag");

	m_filenameBG = m_defaultBGFileName;
	GetInitGameString(&m_filenameBG, "filenameBG");

	m_blockKosuuX = 4;
	m_blockKosuuY = 3;

	GetInitGameParam(&m_blockKosuuX, "blockNumberX");
	GetInitGameParam(&m_blockKosuuY, "blockNumberY");

	m_picMustPrintPercent = 0;
	GetInitGameParam(&m_picMustPrintPercent, "picMustPrintPercent");



	m_miniPic = new CPicture*[m_blockKosuuX*m_blockKosuuY];
	int i = 0;
	for (i = 0; i < m_blockKosuuX*m_blockKosuuY; i++)
	{
		m_miniPic[i] = new CPicture();
	}


	m_printX = 85;
	m_printY = 113;
	m_nextX = 166;
	m_nextY = 124;
	m_sizeX = 133;
	m_sizeY = 100;

	m_picPrintX = 0;
	m_picPrintY = 0;


	GetInitGameParam(&m_printX, "printX");
	GetInitGameParam(&m_printY, "printY");
	GetInitGameParam(&m_nextX, "nextX");
	GetInitGameParam(&m_nextY, "nextY");
	GetInitGameParam(&m_sizeX, "sizeX");
	GetInitGameParam(&m_sizeY, "sizeY");

	m_picSizeX = m_sizeX;
	m_picSizeY = m_sizeY;

	GetInitGameParam(&m_picPrintX, "picPrintX");
	GetInitGameParam(&m_picPrintY, "picPrintY");

	GetInitGameParam(&m_picSizeX, "picSizeX");
	GetInitGameParam(&m_picSizeY, "picSizeY");


	m_cursorSizeX = m_picSizeX;
	m_cursorSizeY = m_picSizeY;
	m_cursorPrintX = m_picPrintX;
	m_cursorPrintY = m_picPrintY;

	GetInitGameParam(&m_cursorPrintX, "cursorPrintX");
	GetInitGameParam(&m_cursorPrintY, "cursorPrintY");
	GetInitGameParam(&m_cursorSizeX, "cursprSizeX");
	GetInitGameParam(&m_cursorSizeY, "cursprSizeY");




//	m_cgFlag = new BOOL[maxCGKosuuPerChara];


	m_back = m_game->GetBackButton();


	LPSTR cursorName = m_defaultCursorFileName;
	GetInitGameString(&cursorName, "fileNameCursor");
	m_cursorPic = m_game->GetSystemPicture(cursorName);


	m_totalPercentPrintFlag = 1;
	GetInitGameParam(&m_totalPercentPrintFlag, "totalPercentPrintFlag");
	m_suuji = NULL;
	if (m_totalPercentPrintFlag)
	{
		LPSTR font1Name = m_defaultFont1FileName;
		GetInitGameString(&font1Name, "fileNameTotalPercent");
		CPicture* suujiPic = m_game->GetSystemPicture(font1Name);

		m_fontSizeX1 = 16;
		m_fontSizeY1 = 22;
		GetInitGameParam(&m_fontSizeX1, "totalPercentFontSizeX");
		GetInitGameParam(&m_fontSizeY1, "totalPercentFontSizeY");
		m_fontNextX1 = m_fontSizeX1;
		GetInitGameParam(&m_fontNextX1, "totalPercentFontNextX");

		m_totalPercentPrintX = 688;
		m_totalPercentPrintY = 25;
		GetInitGameParam(&m_totalPercentPrintX, "totalPercentPrintX");
		GetInitGameParam(&m_totalPercentPrintY, "totalPercentPrintY");

		m_suuji = new CSuuji(suujiPic, m_fontSizeX1, m_fontSizeY1, 3, m_fontNextX1);
	}


	CPicture* lpBG = m_commonBG;
	if (m_backScriptFlag) lpBG = NULL;

	m_pagePrint = new CPagePrint(m_setup, lpBG);



	m_length = 8;
	m_selectedNumber = -1;

	m_selectSound = 1;
	GetInitGameParam(&m_selectSound, "selectSound");
	CreateBackButton();
	CreateUpDownButton();
	CreateUpDownBack();

	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();

//	GetModeNumberBySetup("nextMode",&m_nextMode);
}



CCommonSelectMovie::~CCommonSelectMovie()
{
	End();
}

void CCommonSelectMovie::End(void)
{
}



int CCommonSelectMovie::Init(void)
{
	return -1;
}

int CCommonSelectMovie::Calcu(void)
{
	return -1;
	return m_nextMode;
}

int CCommonSelectMovie::Print(void)
{
//	CAreaControl::SetNextAllPrint();
//	CAllGraphics::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
//	CPicture::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
	return -1;
}




/*_*/


