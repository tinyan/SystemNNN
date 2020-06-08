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

#include "..\nnnUtilLib\nnnButtonStatus.h"

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

char CCommonSelectMovie::m_defaultPrefixOff[] = "ta_sm_movie_off";
char CCommonSelectMovie::m_defaultPrefixOn[] = "ta_sm_movie_on";


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


	m_useOpeningMovie = 0;
	GetInitGameParam(&m_useOpeningMovie, "UseOpeningMovie");

	m_menuStartWaitTime = 0;
	m_menuStartEffectTime = 0;
	m_menuStartEffectType = 0;

	GetInitGameParam(&m_menuStartWaitTime, "menuStartWaitTime");
	GetInitGameParam(&m_menuStartEffectTime, "menuStartEffectTime");
	GetInitGameParam(&m_menuStartEffectType, "menuStartEffectType");


	m_movieCount = m_game->GetMovieCount();
	if (m_useOpeningMovie != 0)
	{
		m_movieCount++;
	}


	m_getMovieFlag = new int[m_movieCount];

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
	GetInitGameParam(&m_cursorSizeX, "cursorSizeX");
	GetInitGameParam(&m_cursorSizeY, "cursorSizeY");


	m_prefixOff = m_defaultPrefixOff;
	m_prefixOn = m_defaultPrefixOn;
	GetInitGameString(&m_prefixOff, "prefixOff");
	GetInitGameString(&m_prefixOn, "prefixOn");

//	m_cgFlag = new BOOL[maxCGKosuuPerChara];


	m_back = m_game->GetBackButton();


	LPSTR cursorName = m_defaultCursorFileName;
	GetInitGameString(&cursorName, "fileNameCursor");
	m_cursorPic = m_game->GetSystemPicture(cursorName);


	m_selectPrintMode = 1;
	GetInitGameParam(&m_selectPrintMode, "selectPrintMode");

	m_selectPercent = 50;
	GetInitGameParam(&m_selectPercent, "selectPercent");

	if (m_selectPrintMode == 1)
	{
		m_selectColorR = 230;
		m_selectColorG = 0;
		m_selectColorB = 50;

		GetInitGameParam(&m_selectColorR, "cursorColorR");
		GetInitGameParam(&m_selectColorG, "cursorColorG");
		GetInitGameParam(&m_selectColorB, "cursorColorB");
	}
	else if (m_selectPrintMode == 2)
	{
		LPSTR cursorName = m_defaultCursorFileName;
		GetInitGameString(&cursorName, "fileNameCursor");
		m_cursorPic = m_game->GetSystemPicture(cursorName);

		m_cursorPrintType = 0;
		GetInitGameParam(&m_cursorPrintType, "cursorPrintType");
	}


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

	m_page = 0;
	m_pageMax = (m_movieCount + m_blockKosuuX * m_blockKosuuY - 1)/(m_blockKosuuX * m_blockKosuuY);


//	GetModeNumberBySetup("nextMode",&m_nextMode);
}



CCommonSelectMovie::~CCommonSelectMovie()
{
	End();
}

void CCommonSelectMovie::End(void)
{
	ENDDELETECLASS(m_pagePrint);

	if (m_miniPic != NULL)
	{
		for (int i = 0; i < m_blockKosuuX*m_blockKosuuY; i++)
		{
			ENDDELETECLASS(m_miniPic[i]);
		}
		DELETEARRAY(m_miniPic);
	}
	DELETEARRAY(m_getMovieFlag);
}



int CCommonSelectMovie::Init(void)
{
	m_appearCount = 1;
	m_appearCountMax = 1;

//	if (!m_initStartWait)
	{
		m_menuStartCount = 0;
	}

	int total = 0;
	for (int i = 0; i < m_movieCount; i++)
	{
		if ((m_useOpeningMovie != 0) && (i == 0))
		{
			m_getMovieFlag[i] = 1;
			total++;
		}
		else
		{
			int mn = i;
			if (m_useOpeningMovie == 0)
			{
				mn++;
			}
			if (m_game->CheckGetMovie(0, mn))
			{

				m_getMovieFlag[i] = 1;
					total++;
			}
			else
			{
				m_getMovieFlag[i] = 0;
			}
		}
	}
	if (m_movieCount > 0)
	{
		m_percent = (total * 100) / m_movieCount;
	}
	else
	{
		m_percent = 0;
	}

	m_game->StopScriptSoundAndVoice();
	m_game->SetDefaultFrameRate();


	SetUpDownZahyo();
	m_updown->SetPageMax(m_pageMax);
	m_updown->SetPage(m_page);


	LoadBackMovie();


	LoadUpDownButtonPic();
	LoadBackButtonPic();



	m_nowSelectNumber = -1;
	m_maeSelectNumber = -1;


	//	m_back->Init();
	m_updownBack->Init();

	SetBackButtonZahyo();

	m_selectedNumber = -1;


	m_startupWait = 3;


	return -1;
}

int CCommonSelectMovie::Calcu(void)
{
	int startMode = GetStartWaitMode();
	if (startMode != 0)
	{
		m_menuStartCount++;
		if (m_menuStartCount >= m_menuStartWaitTime + m_menuStartEffectTime)
		{
			EndStartWaitMode();
		}
		else
		{
			if (m_mouseStatus->CheckClick()) EndStartWaitMode();
			if (m_mouseStatus->CheckClick(1)) EndStartWaitMode();
		}

		return -1;
	}


	POINT pt = m_mouseStatus->GetZahyo();
	int mouseX = pt.x;
	int mouseY = pt.y;

	//	if (m_selectedNumber >= 0)
	if ((m_selectedNumber != -1) && (m_selectedNumber != -2))
	{
		m_count--;
		if (m_count <= 0)
		{
			int fn = m_selectedNumber;
			if (m_useOpeningMovie == 0)
			{
				fn++;
			}
			m_game->SetDirectMovie(fn);
			return ReturnFadeOut(PRINTMOVIE_MODE);
		}
		return -1;
	}

	int rt = m_updownBack->Calcu(m_inputStatus);

	if (rt != NNNBUTTON_NOTHING)
	{
		//sound
		int nm = ProcessUpDownBack(rt);
		if (nm >= 0)
		{
			if (nm == 0)
			{
				return ReturnFadeOut(OMAKE_MODE);
//				return ReturnFadeOut(m_backMode);
			}

			m_selectedNumber = -1;
			if (nm > 0)
			{
				m_page = nm - 1;

				m_startupWait = 3;
				LoadBackMovie();
				CAreaControl::SetNextAllPrint();
				return -1;
			}
		}

		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_STARTCLICK)
		{
			int nm = CCommonButton::GetButtonData(rt);
			m_selectedNumber = -2;
		}
	}

	m_maeSelectNumber = m_nowSelectNumber;
	m_nowSelectNumber = GetOnMovie(mouseX, mouseY);

	if (m_mouseStatus->CheckClick())
	{
		if (m_nowSelectNumber != -1)
		{
			m_selectedNumber = m_nowSelectNumber + m_page * m_blockKosuuX * m_blockKosuuY;

			m_count = m_length;
			if (m_selectSound != -1)
			{
				m_game->PlaySystemSound(m_selectSound - 1);
			}
			//m_game->PlayCommonSystemSound(COMMON_SYSTEMSOUND_OK2);
			return -1;
		}
	}

	if (m_startupWait > 0)
	{
		m_startupWait--;
	}
	else
	{
//		if ((m_nowSelectNumber != m_maeSelectNumber) && (m_nowSelectNumber != -1))
//		{
//			if (m_cgPianoSoundFlag)
//			{
//				m_game->PlaySystemPiano(m_nowSelectNumber);
//			}
//		}
	}

	return -1;


}

int CCommonSelectMovie::Print(void)
{
	PrintBackScriptOrBG();

	BOOL b = CAreaControl::CheckAllPrintMode();


	int startMode = GetStartWaitMode();

	int dva = m_appearCountMax;
	if (dva < 1) dva = 1;

	int appearPercent = 100;
	if (m_menuStartEffectType & 1)
	{
		appearPercent = (100 * m_appearCount) / dva;
		if (appearPercent < 0) appearPercent = 0;
		if (appearPercent > 100) appearPercent = 100;
	}



	if (m_backScriptFlag)
	{
		PrintAllMiniPic();

//		if (m_addPicFlag) PrintAddPic();
//		m_pagePrint->Print(m_page + 1, m_pageMax);
		m_pagePrint->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType,m_page + 1, m_pageMax);

		//		if (m_pagePrintFlag) PrintPage();
		if (m_totalPercentPrintFlag) PrintTotalPercent();
	}


//	m_updownBack->Print(TRUE);
	m_updownBack->AppearPrint(m_appearCount,m_appearCountMax,m_menuStartEffectType);
	//	m_back->Print(TRUE);
	//	m_updown->Print(TRUE);

	for (int j = 0; j < m_blockKosuuY; j++)
	{
		for (int i = 0; i < m_blockKosuuX; i++)
		{
			int k = i + j * m_blockKosuuX;
			BOOL bb = b;
			if (m_nowSelectNumber != m_maeSelectNumber)
			{
				if ((k == m_nowSelectNumber) || (k == m_maeSelectNumber))
				{
					bb = TRUE;
				}
			}

			if (k == m_selectedNumber) bb = TRUE;

			if (bb)
			{
				int putX = m_printX + m_nextX * i;
				int putY = m_printY + m_nextY * j;
				int sizeX = m_sizeX;
				int sizeY = m_sizeY;

				int block = m_page * (m_blockKosuuX * m_blockKosuuY) + k;

				if (m_getMovieFlag[block] > 0)
				{
					if (m_backScriptFlag == 0)
					{
						m_commonBG->Blt(putX, putY, putX, putY, sizeX, sizeY, FALSE);
					}

					if ((k == m_nowSelectNumber) || (k == m_selectedNumber))
					{
						if ((m_selectedNumber == -1) || (m_count & 1))
						{
							int putX1 = putX + m_cursorPrintX;
							int putY1 = putY + m_cursorPrintY;
							int sizeX1 = m_cursorSizeX;
							int sizeY1 = m_cursorSizeY;

							if (m_selectPrintMode == 1)
							{
//								CAllGeo::TransBoxFill(putX1, putY1, sizeX1, sizeY1, m_selectColorR, m_selectColorG, m_selectColorB, m_selectPercent);
								CAllGeo::TransBoxFill(putX1, putY1, sizeX1, sizeY1, m_selectColorR, m_selectColorG, m_selectColorB, (m_selectPercent*appearPercent)/100);
							}
							else if (m_selectPrintMode == 2)
							{
								if (m_cursorPrintType == 0)
								{
//									m_cursorPic->Blt(putX1, putY1, 0, 0, sizeX1, sizeY1, TRUE);
									m_cursorPic->TransLucentBlt3(putX1, putY1, 0, 0, sizeX1, sizeY1, appearPercent);
								}
								else if (m_cursorPrintType == 1)
								{
									m_cursorPic->TransLucentBlt3(putX1, putY1, 0, 0, sizeX1, sizeY1, (m_selectPercent * appearPercent)/100);
								}
								else if (m_cursorPrintType == 2)
								{
									if (m_appearCount >= m_appearCountMax)
									{
										m_cursorPic->AddBlt(putX1, putY1, 0, 0, sizeX1, sizeY1);
									}
								}
								//								m_cursorPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
							}
							//							CPicture::TransBox(putX,putY,sizeX,sizeY,230,0,255,50);
							//							m_cursorPic->AddBlt(putX-1,putY-1,0,0,135,101);
						}
					}

					if (b == FALSE)
					{
						CAreaControl::AddArea(putX, putY, sizeX, sizeY);
					}
				}
			}
		}
	}

	return 0;



//	CAllGraphics::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
//	CPicture::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
	return -1;
}


void CCommonSelectMovie::LoadBackMovie(void)
{
	char filename[256];
	if (m_backScriptFlag == 0)
	{
		wsprintf(filename, "sys\\%s", m_filenameBG);
		m_commonBG->LoadDWQ(filename);
		m_commonBG->Put(0, 0, FALSE);
	}

	for (int j = 0; j < m_blockKosuuY; j++)
	{
		for (int i = 0; i < m_blockKosuuX; i++)
		{
			int n0 = j * m_blockKosuuX + i;
			int block = m_page * (m_blockKosuuX * m_blockKosuuY) + n0;

			if (block < m_movieCount)
			{
				int fn = block;
				if (m_useOpeningMovie == 0)
				{
					fn++;
				}

				if (m_getMovieFlag[block] == 0)
				{
					sprintf_s(filename, 256, "sys\\%s%d", m_prefixOff,fn);
				}
				else
				{
					sprintf_s(filename, 256, "sys\\%s%d", m_prefixOn,fn);

				}
				m_miniPic[n0]->LoadDWQ(filename);
			}
		}
	}

	if (m_backScriptFlag == 0)
	{
		PrintAllMiniPic();

		if (m_totalPercentPrintFlag)
		{
			PrintTotalPercent();
		}

		m_pagePrint->Print(m_page + 1, m_pageMax);


		m_commonBG->GetScreen();
	}

}

int CCommonSelectMovie::GetOnMovie(int mouseX, int mouseY)
{
	int x = mouseX - m_printX;
	int y = mouseY - m_printY;

	if ((x < 0) || (x >= m_nextX * m_blockKosuuX)) return -1;
	if ((y < 0) || (y >= m_nextY * m_blockKosuuY)) return -1;

	int ax = x % m_nextX;
	int ay = y % m_nextY;
	if (ax >= m_sizeX) return -1;
	if (ay >= m_sizeY) return -1;

	int d = x / m_nextX;
	d += ((y / m_nextY) * m_blockKosuuX);

	if ((d + m_page * m_blockKosuuX * m_blockKosuuY) >= m_movieCount) return -1;

	if (m_getMovieFlag[d] == 0) return -1;

	return d;
}


void CCommonSelectMovie::PrintTotalPercent(void)
{
//	m_suuji->Print(m_totalPercentPrintX, m_totalPercentPrintY, m_percent);
//	m_suuji->Put(m_totalPercentPrintX + m_fontNextX1 * 3, m_totalPercentPrintY, 12, 0);
	m_suuji->AppearPrint(m_appearCount, m_appearCountMax, m_menuStartEffectType,m_totalPercentPrintX, m_totalPercentPrintY, m_percent);
	m_suuji->AppearPut(m_appearCount, m_appearCountMax, m_menuStartEffectType,m_totalPercentPrintX + m_fontNextX1 * 3, m_totalPercentPrintY, 12, 0);
}

void CCommonSelectMovie::PrintAllMiniPic(void)
{
	int dva = m_appearCountMax;
	if (dva < 1) dva = 1;

	int appearPercent = 100;
	if (m_menuStartEffectType & 1)
	{
		appearPercent = (100 * m_appearCount) / dva;
		if (appearPercent < 0) appearPercent = 0;
		if (appearPercent > 100) appearPercent = 100;
	}


	for (int j = 0; j < m_blockKosuuY; j++)
	{
		for (int i = 0; i < m_blockKosuuX; i++)
		{
			int n0 = j * m_blockKosuuX + i;
			int block = m_page * (m_blockKosuuX * m_blockKosuuY) + n0;

			int putX = m_printX + i * m_nextX;
			int putY = m_printY + j * m_nextY;

			if (block < m_movieCount)
			{
//				m_miniPic[n0]->Put(putX, putY, TRUE);
				SIZE sz = m_miniPic[n0]->GetPicSize();
				if (m_miniPic[n0]->CheckMaskExist())
				{
					m_miniPic[n0]->TransLucentBlt3(putX, putY, 0, 0, sz.cx, sz.cy, appearPercent);
				}
				else
				{
					m_miniPic[n0]->TransLucentBlt0(putX, putY, 0, 0, sz.cx, sz.cy, appearPercent);
				}
			}
		}
	}
}


int CCommonSelectMovie::GetStartWaitMode(void)
{
	if (m_menuStartCount < m_menuStartWaitTime)
	{
		m_appearCount = 0;
		m_appearCountMax = 1;
		return 1;
	}

	if (m_menuStartCount < m_menuStartWaitTime + m_menuStartEffectTime)
	{
		m_appearCount = m_menuStartCount - m_menuStartWaitTime;
		m_appearCountMax = m_menuStartEffectTime;
		return 2;
	}

	m_appearCount = 1;
	m_appearCountMax = 1;

	return 0;
}

void CCommonSelectMovie::EndStartWaitMode(void)
{
	m_menuStartCount = m_menuStartWaitTime + m_menuStartEffectTime;
	//m_game->InitMiniGameButton(OMAKE_MODE);
}

/*_*/


