
#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nnnUtilLib\myMouseStatus.h"

#include "allMiniGame.h"
#include "miniGameBase.h"

#include "minigameLayoutParamName.h"

#include "miniGamePyramid.h"


int CMiniGamePyramid::m_checkTable[]=
{
	1, 3,4, 6,7,8, 10,11,12,13, 15,16,17,18,19, 21,22,23,24,25,26,
};

CMiniGamePyramid::CMiniGamePyramid(CAllMiniGame* lpAllMiniGame,int layoutParamKosuu,int* layoutParam) : CMiniGameBase(lpAllMiniGame,layoutParamKosuu,layoutParam)
{
	m_trumpPic = m_allMiniGame->GetCommonPic(0);
	m_trumpSize = m_allMiniGame->GetCommonPicSize(0);

	m_startNaraberuCountMax = 28 + 15;
	m_kieruCountMax = 20;
	m_mekuruCountMax = 10;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int sizeX = m_trumpSize.cx;
	int sizeY = m_trumpSize.cy;

	int amariX = screenSizeX - sizeX * 7;
	int sukimaX = amariX / 7;
	if (sukimaX > (sizeX*3)/4) sukimaX = (sizeX*3)/4;
	if (sukimaX < 0) sukimaX = 0;
	int nextX = sizeX - (sizeX - sukimaX) / 2;
	GetLayoutData(&nextX,MINIGAME_LAYOUTPARAM_NEXTX);

	int startX = screenSizeX / 2 - sizeX / 2;
	startX -= 6 * nextX;
	GetLayoutData(&startX,MINIGAME_LAYOUTPARAM_STARTX);

	int sukimaY = 8;
	int startY = sukimaY;
	int lastY = screenSizeY - sukimaY - sizeY;
	int nextY = (lastY - startY) / (7-1);
	GetLayoutData(&nextY,MINIGAME_LAYOUTPARAM_NEXTY);
	GetLayoutData(&startY,MINIGAME_LAYOUTPARAM_STARTY);

	m_cardZahyo[0].x = startX;
	m_cardZahyo[0].y = startY;
	m_cardZahyo[1].x = startX + nextX*2;
	m_cardZahyo[1].y = startY;

	int n = 2;
	for (int j=0;j<7;j++)
	{
		int y = startY + nextY*j;

		for (int i=0;i<=j;i++)
		{
			int x = startX + nextX*i*2 + nextX*(6-j); 

			m_cardZahyo[n].x = x; 
			m_cardZahyo[n].y = y; 
			n++;
		}
	}

	m_cardPicType = m_allMiniGame->GetPicType(0);
}


CMiniGamePyramid::~CMiniGamePyramid()
{
	End();
}


void CMiniGamePyramid::End(void)
{
}

int CMiniGamePyramid::Init(void)
{
	m_clearFlag = FALSE;

	CAreaControl::SetNextAllPrint();

	m_firstClick = -1;
	m_subMode = 1;

	Shuffle();
	m_yamaMaisuu = 52;
	m_daiMaisuu = 0;

	m_nowSelect = -1;
	m_maeSelect = -1;

	m_reShuffleCount = 1;
	StartNaraberu();

	return -1;
}

int CMiniGamePyramid::Calcu(void)
{
	if (m_clearFlag)
	{
		return -1;
	}

	if (CheckGameover())
	{
		return -1;
	}

	if (m_subMode != 0)
	{
		if (m_subMode == 1)
		{
			CalcuStartNaraberu();
		}
		else if (m_subMode == 2)
		{
			CalcuKieru();
		}
		else if (m_subMode == 3)
		{
			CalcuMekuru();
		}
		else if (m_subMode == 4)
		{
			CalcuModosu();
		}
		return -1;
	}

	m_maeSelect = m_nowSelect;
	m_nowSelect = -1;

	POINT pt = m_mouseStatus->GetZahyo();
	int on = GetOnCard(pt);
	if (on != -1)
	{
		if (on == 0)
		{
			if (m_yamaMaisuu > 0)
			{
				if (m_firstClick == -1)
				{
					m_nowSelect = on;
				}
			}
			else
			{
				if (m_reShuffleCount > 0)
				{
					if (m_firstClick == -1)
					{
						m_nowSelect = on;
					}
				}
			}
		}
		else if (on == 1)
		{
			if (m_daiMaisuu > 0)
			{
				m_nowSelect = on;
			}
		}
		else if ((on >= 2) && (on < 28+2))
		{
			if (m_ba[on-2] != -1)
			{
				if (CheckClickOk(on-2))
				{
					m_nowSelect = on;
				}
			}
		}
	}

	if (m_nowSelect != m_maeSelect)
	{
		CAreaControl::SetNextAllPrint();
	}

	if (m_mouseStatus->CheckClick(1))
	{
		if (m_firstClick != -1)
		{
			StartNormal();
			return -1;
		}
	}

	if (m_mouseStatus->CheckClick())
	{
		if (m_nowSelect != -1)
		{
			if (m_nowSelect == 0)
			{
				if (m_yamaMaisuu > 0)
				{
					m_allMiniGame->PlayClickSound();
					StartMekuru();
					return -1;
				}
				else
				{
					m_allMiniGame->PlayClickSound();
					StartModosu();
					return -1;
				}
			}
			else
			{
				if (m_nowSelect == m_firstClick)
				{
					m_allMiniGame->PlayClickSound();
					StartNormal();
					return -1;
				}

				if (m_firstClick == -1)
				{
					//K?
					int card1 = GetCard(m_nowSelect);
					int n1 = card1 % 13;
					if (n1 == 12)
					{
						m_allMiniGame->PlayGoodSound();
						StartKieru(m_nowSelect,-1);
						return -1;
					}
					else
					{
						m_allMiniGame->PlayClickSound();
						m_firstClick = m_nowSelect;
						CAreaControl::SetNextAllPrint();
						return -1;
					}
				}
				else
				{
					int card1 = GetCard(m_firstClick);
					int card2 = GetCard(m_nowSelect);
					int n1 = card1 % 13;
					int n2 = card2 % 13;
					if ((n1+n2+2) == 13)
					{
						m_allMiniGame->PlayGoodSound();
						StartKieru(m_firstClick,m_nowSelect);
						return -1;
					}
					m_allMiniGame->PlayBadSound();
					return -1;
				}
			}
		}
	}

	return -1;
}





void CMiniGamePyramid::StartNormal(void)
{
	CAreaControl::SetNextAllPrint();
	m_subMode = 0;
	m_firstClick = -1;
	m_maeSelect = -1;
	m_nowSelect = -1;
}

void CMiniGamePyramid::StartNaraberu(void)
{
	for (int i=0;i<28;i++)
	{
		m_ba[i] = m_yama[m_yamaMaisuu-1];
		m_yamaMaisuu--;
	}

	m_startNaraberuCount = 0;
	m_subMode = 1;
	CAreaControl::SetNextAllPrint();
}

void CMiniGamePyramid::StartKieru(int place1,int place2)
{
	m_kieru1 = place1;
	m_kieru2 = place2;

	m_kieruCount = 0;
	m_subMode = 2;
	CAreaControl::SetNextAllPrint();
}

void CMiniGamePyramid::StartMekuru(void)
{
	CAreaControl::SetNextAllPrint();

	if (m_yamaMaisuu <= 0) return;	//error!
	m_mekuruCard = m_yama[m_yamaMaisuu-1];
	m_yamaMaisuu--;

	m_mekuruCount = 0;
	m_subMode = 3;
}

void CMiniGamePyramid::StartModosu(void)
{
	CAreaControl::SetNextAllPrint();
	if (m_daiMaisuu <= 0) return;//error!

	m_modosuCountMax = m_daiMaisuu + 10;
	m_modosuCount = 0;
	m_subMode = 4;
}


void CMiniGamePyramid::CalcuStartNaraberu(void)
{
	if (m_startNaraberuCount >= 1)
	{
		if (CheckSkip())
		{
			m_startNaraberuCount = m_startNaraberuCountMax;
		}
	}

	m_startNaraberuCount++;

	if (m_startNaraberuCount>=m_startNaraberuCountMax)
	{
		StartNormal();
	}
}



void CMiniGamePyramid::CalcuKieru(void)
{
	if (m_kieruCount >= 1)
	{
		if (CheckSkip())
		{
			m_kieruCount = m_kieruCountMax;
		}
	}

	m_kieruCount++;
	
	if (m_kieruCount >= m_kieruCountMax)
	{
		//‚¯‚·

		if (m_kieru1 == 1)
		{
			m_daiMaisuu--;
		}
		else if (m_kieru1 > 1)
		{
			m_ba[m_kieru1-2] = -1;
		}

		if (m_kieru2 == 1)
		{
			m_daiMaisuu--;
		}
		else if (m_kieru2 > 1)
		{
			m_ba[m_kieru2-2] = -1;
		}

		CheckAllGet();
		if (CheckClear())
		{
			m_allMiniGame->PlayClearSound();
			return;
		}
		else
		{
			CheckCannot();
			if (CheckGameover())
			{
				m_allMiniGame->PlayGameoverSound();
				return;
			}
		}

		StartNormal();
	}
}


void CMiniGamePyramid::CalcuMekuru(void)
{
	if (m_mekuruCount >= 1)
	{
		if (CheckSkip())
		{
			m_mekuruCount = m_mekuruCountMax;
		}
	}
	m_mekuruCount++;

	if (m_mekuruCount >= m_mekuruCountMax)
	{
		m_dai[m_daiMaisuu] = m_mekuruCard;
		m_daiMaisuu++;

		CheckCannot();
		if (CheckGameover())
		{
			m_allMiniGame->PlayGameoverSound();
			return;
		}

		StartNormal();
		return;
	}
}

void CMiniGamePyramid::CalcuModosu(void)
{
	if (m_modosuCount >= 1)
	{
		if (CheckSkip())
		{
			m_modosuCount = m_modosuCountMax;
		}
	}
	m_modosuCount++;

	if (m_modosuCount >= m_modosuCountMax)
	{
		for (int i=0;i<m_daiMaisuu;i++)
		{
			m_yama[i] = m_dai[m_daiMaisuu-1-i];
		}
		m_yamaMaisuu = m_daiMaisuu;
		m_daiMaisuu = 0;
		m_reShuffleCount--;
		StartNormal();
		return;
	}
}


BOOL CMiniGamePyramid::CheckSkip(void)
{
	if (m_mouseStatus->CheckClick())
	{
		return TRUE;
	}
	if (m_mouseStatus->CheckClick(1))
	{
		return TRUE;
	}

	return FALSE;
}




int CMiniGamePyramid::Print(void)
{
	if (m_clearFlag)
	{
		CAreaControl::SetNextAllPrint();
		m_pic1->Put(0,0,FALSE);
		return -1;
	}

	if (CheckGameover())
	{
		int ps = 60;

		CAreaControl::SetNextAllPrint();
		m_pic1->Put(0,0,FALSE);

		PrintYama(FALSE,ps);
		PrintDai(FALSE,FALSE,ps);
		for (int i=0;i<28;i++)
		{
			int card = m_ba[i];
			if (card != -1)
			{
				POINT pt = GetCardZahyo(i+2);
				PutCard(pt,card,ps);
			}
		}
		return -1;
	}


	BOOL b = CAreaControl::CheckAllPrintMode();
	if (b)
	{
		m_pic1->Put(0,0,FALSE);
	}

	if (m_subMode == 0)
	{
		PrintNormal();
	}
	else if (m_subMode == 1)
	{
		PrintStartNaraberu();
	}
	else if (m_subMode == 2)
	{
		PrintKieru();
	}
	else if (m_subMode == 3)
	{
		PrintMekuru();
	}
	else if (m_subMode == 4)
	{
		PrintModosu();
	}

	return -1;
}


POINT CMiniGamePyramid::GetCardZahyo(int n)
{
	POINT pt = m_cardZahyo[n];

	return pt;
}


void CMiniGamePyramid::PrintNormal(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();
//	int sizeX = m_trumpSize.cx;
//	int sizeY = m_trumpSize.cy;

	if (b)
	{
		BOOL selFlag = FALSE;
		if (m_nowSelect == 0)
		{
			selFlag = TRUE;
		}
		PrintYama(selFlag);

		selFlag = FALSE;
		
		if (m_nowSelect == 1)
		{
			selFlag = TRUE;
		}
		BOOL chkFlag = FALSE;
		if (m_firstClick == 1)
		{
			chkFlag = TRUE;
		}
		PrintDai(selFlag,chkFlag);

		for (int i=0;i<28;i++)
		{
			int card = m_ba[i];
			if (card != -1)
			{
				POINT pt = GetCardZahyo(i+2);

				BOOL selFlag = FALSE;
				BOOL chkFlag = FALSE;

				int n = i + 2;
				if (n == m_nowSelect)
				{
					selFlag = TRUE;
				}

				if (n == m_firstClick)
				{
					chkFlag = 1;
				}

				PutCard(pt,card,100,selFlag,chkFlag);
			}
		}
	}
}


void CMiniGamePyramid::PrintStartNaraberu(void)
{
	CAreaControl::SetNextAllPrint();

	PrintYama();
	PrintDai();

	int dv = m_startNaraberuCountMax - 28;
	if (dv<1) dv = 1;

	POINT pt0 = GetCardZahyo(0);

	int x1 = pt0.x;
	int y1 = pt0.y;

	for (int i=0;i<28;i++)
	{
		int c = m_startNaraberuCount - i; 
		//if (c<0) c = 0;
		if (c>=0)
		{
			if (c>dv) c = dv;

			POINT pt = GetCardZahyo(i+2);

			int x2 = pt.x;
			int y2 = pt.y;

			int x = x1 + ((x2 - x1) * c) / dv;
			int y = y1 + ((y2 - y1) * c) / dv;

			PutCard(x,y,m_ba[i]);
		}
	}
}

void CMiniGamePyramid::PrintKieru(void)
{
	CAreaControl::SetNextAllPrint();

	PrintYama();
	if ((m_kieru1 == 1) || (m_kieru2 == 1))
	{
		PrintDai(FALSE,FALSE,100,TRUE);
	}
	else
	{
		PrintDai();
	}

	int ps = ((m_kieruCountMax - m_kieruCount) * 100) / m_kieruCountMax;
	if (ps<1) ps = 1;
	if (ps>99) ps = 99;

	if ((m_kieru1 == 1) || (m_kieru2 == 1))
	{
		if (m_daiMaisuu > 0)
		{
			POINT pt = GetCardZahyo(1);
			PutCard(pt,m_dai[m_daiMaisuu-1],ps);
		}
	}

	for (int i=0;i<28;i++)
	{
		int card = m_ba[i];
		POINT pt = GetCardZahyo(i+2);

		if (card != -1)
		{
			int n = i + 2;
			if ((n == m_kieru1) || (n == m_kieru2))
			{
				PutCard(pt,card,ps);
			}
			else
			{
				PutCard(pt,card);
			}
		}
	}
}


void CMiniGamePyramid::PrintMekuru(void)
{
	CAreaControl::SetNextAllPrint();

	PrintYama();
	PrintDai();

	//move card
	int dv = m_mekuruCountMax;
	int c = m_mekuruCount;
	if (dv<1) dv = 1;
	if (c<0) c = 0;
	if (c>dv) c = dv;

	POINT pt1 = GetCardZahyo(0);
	POINT pt2 = GetCardZahyo(1);

	int ps = 30 + (70*c) / dv;
	if (ps>100) ps = 100;

	int x1 = pt1.x;
	int y1 = pt1.y;
	int x2 = pt2.x;
	int y2 = pt2.y;
	int x = x1 + ((x2 - x1) * c) / dv;
	int y = y1 + ((y2 - y1) * c) / dv;
//	int card0 = m_dai[m_daiMaisuu-1];
	PutCard(x,y,m_mekuruCard,ps);
	
	for (int i=0;i<28;i++)
	{
		int card = m_ba[i];
		if (card != -1)
		{
			POINT pt = GetCardZahyo(i+2);
			PutCard(pt,card);
		}
	}
}


void CMiniGamePyramid::PrintModosu(void)
{
	int i = 0;

	CAreaControl::SetNextAllPrint();

	POINT pt1 = GetCardZahyo(0);
	PutCard(pt1,54);	//yama base

	POINT pt2 = GetCardZahyo(1);
	PutCard(pt2,55);	//dai base


	//move card
	int dv = m_modosuCountMax-10;
	if (dv<1) dv = 1;
	for (i=0;i<m_daiMaisuu;i++)
	{
		int c = m_modosuCount + i - 10;
		if ((c>=0) && (c<=10))
		{
			int x = pt2.x + ((pt1.x - pt2.x) * c) / 10;
			int y = pt2.y + ((pt1.y - pt2.y) * c) / 10;

			int card = m_dai[i];
			int ps = 7*c + 30;
			PutCard(x,y,card,ps);
		}
	}

	for (i=0;i<28;i++)
	{
		int card = m_ba[i];
		if (card != -1)
		{
			POINT pt = GetCardZahyo(i+2);
			PutCard(pt,card);
		}
	}
}

void CMiniGamePyramid::Shuffle(void)
{
	int i = 0;
	for (i=0;i<52;i++)
	{
		m_yama[i] = i;
	}

	for (i=0;i<52;i++)
	{
		int r = (i+(rand() % 51)) % 52;
		int tmp = m_yama[r];
		m_yama[r] = m_yama[i];
		m_yama[i] = tmp;
	}
}

void CMiniGamePyramid::PutCard(POINT pt,int card,int trans,BOOL sel,int chk)
{
	int x = pt.x;
	int y = pt.y;
	PutCard(x,y,card,trans,sel,chk);
}


void CMiniGamePyramid::PutCard(int x,int y,int card,int trans,BOOL sel,int chk)
{
	if (m_trumpPic == NULL) return;

	int sizeX = m_trumpSize.cx;
	int sizeY = m_trumpSize.cy;

	POINT src = GetCardPic(card);

	//int srcX = (card % 13) * sizeX;
	//int srcY = (card / 13) * sizeY;

	if (trans == 100)
	{
		m_trumpPic->Blt(x,y,src.x,src.y,sizeX,sizeY,TRUE);
	}
	else
	{
		m_trumpPic->TransLucentBlt3(x,y,src.x,src.y,sizeX,sizeY,trans);
	}

	if (sel)
	{
		src = GetCardPic(56);
//		srcX = 4 * sizeX;
//		srcY = 4 * sizeY;
		m_trumpPic->Blt(x,y,src.x,src.y,sizeX,sizeY,TRUE);
	}

	if (chk)
	{
		src = GetCardPic(56+chk);
//		srcX = (4 + (chk-1)) * sizeX;
//		srcY = 4 * sizeY;
		m_trumpPic->Blt(x,y,src.x,src.y,sizeX,sizeY,TRUE);
	}
}

POINT CMiniGamePyramid::GetCardPic(int n)
{
	POINT pt;
	
	if (m_cardPicType == 0)
	{
		int dv = 13;
		pt.x = (n % dv) * m_trumpSize.cx;
		pt.y = (n / dv) * m_trumpSize.cy;
	}
	else
	{
		int dv = 10;

		int s = n / 13;
		int k = n % 13;
		if ((s<4) && (k<dv))
		{
			pt.x = k * m_trumpSize.cx;
			pt.y = s * m_trumpSize.cy;
		}
		else if (s<3)
		{
			pt.x = (s*3+(k-dv)) * m_trumpSize.cx;
			pt.y = 4 * m_trumpSize.cy;
		}
		else
		{
			int p = n-49;
			pt.x = (p % dv) * m_trumpSize.cx;
			pt.y = ((p / dv) + 5) * m_trumpSize.cy;
		}
	}

	return pt;
}

void CMiniGamePyramid::PrintYama(BOOL selFlag,int ps)
{
	int card = 54;
	POINT pt = GetCardZahyo(0);

	if (m_yamaMaisuu == 0)
	{
		card = 55;
	}
	int bad = 0;

	if (card == 55)
	{
		if (m_reShuffleCount <= 0)
		{
			bad = 2;
		}
	}

	PutCard(pt,card,ps,selFlag,bad);
}

void CMiniGamePyramid::PrintDai(BOOL selFlag,BOOL chkFlag,int ps,int kieruFlag)
{
	int card = 55;
	POINT pt = GetCardZahyo(1);
	int n = m_daiMaisuu;
	if (kieruFlag)
	{
		n--;
	}
	if (n > 0)
	{
		card = m_dai[n-1];
	}
	int chkFlagNum = 0;
	if (chkFlag) chkFlagNum = 1;
	PutCard(pt,card,ps,selFlag,chkFlagNum);
}


void CMiniGamePyramid::CheckCannot(void)
{
	if (CheckClear()) return;
	if (m_yamaMaisuu > 0) return;

	if (m_reShuffleCount > 0)
	{
		if (m_daiMaisuu>0)
		{
			return;
		}
	}

	int cardMaisuu = 0;
	int cardWork[28+1];

	if (m_daiMaisuu > 0)
	{
		cardWork[cardMaisuu] = (m_dai[m_daiMaisuu-1] % 13) + 1;
		cardMaisuu++;
	}

	int i = 0;
	for (i=0;i<28;i++)
	{
		int card = m_ba[i];
		if (card != -1)
		{
			if (CheckClickOk(i))
			{
				cardWork[cardMaisuu] = (card % 13) + 1;
				cardMaisuu++;
			}
		}
	}


	for (i=0;i<cardMaisuu;i++)
	{
		if (cardWork[i] == 13) return;
	}

	if (cardMaisuu >= 2)
	{
		for (int j=0;j<cardMaisuu-1;j++)
		{
			int card1 = cardWork[j];
			for (i=j+1;i<=cardMaisuu;i++)
			{
				int card2 = cardWork[i];
				if ((card1+card2) == 13) return;
			}
		}
	}

	m_gameoverFlag = TRUE;
}




void CMiniGamePyramid::CheckAllGet(void)
{
//	if (m_yamaMaisuu > 0) return;
//	if (m_daiMaisuu > 0) return;

	for (int i=0;i<28;i++)
	{
		if (m_ba[i] != -1) return;
	}
	m_clearFlag = TRUE;
}



int CMiniGamePyramid::GetOnCard(POINT pt)
{
//	int sizeX = m_trumpSize.cx;
//	int sizeY = m_trumpSize.cy;

	POINT pt2 = GetCardZahyo(0);
	if (CheckOnCard(pt,pt2))
	{
		if (m_yamaMaisuu > 0)
		{
			return 0;
		}
		else
		{
			if ((m_daiMaisuu > 0) && (m_reShuffleCount > 0))
			{
				return 0;
			}
		}
	}


	if (m_daiMaisuu > 0)
	{
		POINT pt2 = GetCardZahyo(1);
		if (CheckOnCard(pt,pt2))
		{
			return 1;
		}
	}

	for (int i=27;i>=0;i--)
	{
		if (m_ba[i] != -1)
		{
			POINT pt2 = GetCardZahyo(i+2);
			if (CheckOnCard(pt,pt2))
			{
				if (CheckClickOk(i))
				{
					return i+2;
				}
			}
		}
	}

	return -1;
}


BOOL CMiniGamePyramid::CheckClickOk(int n)
{
	if (n>=21) return TRUE;
	int k = m_checkTable[n];
	if (m_ba[k] != -1) return FALSE;
	if (m_ba[k+1] != -1) return FALSE;
	return TRUE;
}

BOOL CMiniGamePyramid::CheckOnCard(POINT pt,POINT pt2)
{
	int dx = pt.x - pt2.x;
	int dy = pt.y - pt2.y;

	if ((dx<0) || (dy<0)) return FALSE;
	if (dx>=m_trumpSize.cx) return FALSE;
	if (dy>=m_trumpSize.cy) return FALSE;

	//pic check??

	return TRUE;
}


int CMiniGamePyramid::GetCard(int n)
{
	if (n == 0)
	{
		if (m_yamaMaisuu > 0)
		{
			return m_yama[m_yamaMaisuu-1];
		}
	}

	if (n == 1)
	{
		if (m_daiMaisuu > 0)
		{
			return m_dai[m_daiMaisuu-1];
		}
	}
	
	if (n>=2)
	{
		return m_ba[n-2];
	}

	return -1;	//error!!
}


/*_*/

