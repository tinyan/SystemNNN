
#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nnnUtilLib\myMouseStatus.h"

#include "allMiniGame.h"
#include "miniGameBase.h"

#include "miniGameGolf.h"


int CMiniGameGolf::m_checkTable[]=
{
	1, 3,4, 6,7,8, 10,11,12,13, 15,16,17,18,19, 21,22,23,24,25,26,
};

CMiniGameGolf::CMiniGameGolf(CAllMiniGame* lpAllMiniGame,int layoutParamKosuu,int* layoutParam) : CMiniGameBase(lpAllMiniGame,layoutParamKosuu,layoutParam)
{
	m_trumpPic = m_allMiniGame->GetCommonPic(0);
	m_trumpSize = m_allMiniGame->GetCommonPicSize(0);

	m_startNaraberuCountMax = 35 + 15;
	m_kieruCountMax = 20;
	m_mekuruCountMax = 10;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int sizeX = m_trumpSize.cx;
	int sizeY = m_trumpSize.cy;

	int amariX = screenSizeX - sizeX * 7;
	int sukimaX = amariX / 7;
	int nextX = sukimaX + sizeX;
	int startX = sukimaX / 2;
	int sukimaY = 8;
	int startY = sukimaY;
	int lastY = screenSizeY - sukimaY - sizeY;
	int nextY = (lastY - startY) / (7-1);

	int startX2 = startX + nextX*3;
	int startY2 = startY + nextY*4 + sizeY + sukimaY;

	m_cardZahyo[1].x = startX2;
	m_cardZahyo[1].y = startY2;
	m_cardZahyo[0].x = startX2 + nextX;
	m_cardZahyo[0].y = startY2;

	int n = 2;
	for (int j=0;j<7;j++)
	{
		int x = startX + nextX*j;

		for (int i=0;i<5;i++)
		{
			int y = startY + nextY * i;

			m_cardZahyo[n].x = x; 
			m_cardZahyo[n].y = y; 
			n++;
		}
	}

	m_cardPicType = m_allMiniGame->GetPicType(0);
}


CMiniGameGolf::~CMiniGameGolf()
{
	End();
}


void CMiniGameGolf::End(void)
{
}

int CMiniGameGolf::Init(void)
{
	m_clearFlag = FALSE;

	CAreaControl::SetNextAllPrint();

//	m_firstClick = -1;
	m_subMode = 1;

	Shuffle();
	m_yamaMaisuu = 54;
//	m_daiMaisuu = 0;

	m_daifuda = m_yama[53];
	m_yamaMaisuu--;

	m_nowSelect = -1;
	m_maeSelect = -1;

	m_reShuffleCount = 1;
	StartNaraberu();

	return -1;
}

int CMiniGameGolf::Calcu(void)
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
//		else if (m_subMode == 4)
//		{
//			CalcuModosu();
//		}
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
//				if (m_firstClick == -1)
//				{
					m_nowSelect = on;
//				}
			}
		}
		else if (on == 1)
		{
//			if (m_daiMaisuu > 0)
//			{
//				m_nowSelect = on;
//			}
		}
		else if ((on >= 2) && (on < 35+2))
		{
			int ny = (on-2) / 5;
			int nx = (on-2) % 5;

			if (m_baMaisuu[ny] > nx)
			{
				if (m_ba[ny][nx] != -1)
				{
					if (CheckClickOk(on))
					{
						m_nowSelect = on;
					}
				}
			}
		}
	}

	if (m_nowSelect != m_maeSelect)
	{
		CAreaControl::SetNextAllPrint();
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
			}
			else
			{
///@@				int card = GetCard(m_nowSelect);
				StartKieru(m_nowSelect);
				return -1;
			}
		}
	}

	return -1;
}





void CMiniGameGolf::StartNormal(void)
{
	CAreaControl::SetNextAllPrint();
	m_subMode = 0;
//	m_firstClick = -1;
	m_maeSelect = -1;
	m_nowSelect = -1;
}

void CMiniGameGolf::StartNaraberu(void)
{
	for (int i=0;i<35;i++)
	{
		int nx = i % 5;
		int ny = i / 5;
		m_ba[ny][nx] = m_yama[m_yamaMaisuu-1];
		m_yamaMaisuu--;
	}

	for (int j=0;j<7;j++)
	{
		m_baMaisuu[j] = 5;
	}

	m_startNaraberuCount = 0;
	m_subMode = 1;
	CAreaControl::SetNextAllPrint();
}

void CMiniGameGolf::StartKieru(int place)
{
	m_kieru = place;

	m_kieruCount = 0;
	m_subMode = 2;
	CAreaControl::SetNextAllPrint();
}

void CMiniGameGolf::StartMekuru(void)
{
	CAreaControl::SetNextAllPrint();

	if (m_yamaMaisuu <= 0) return;	//error!
	m_mekuruCard = m_yama[m_yamaMaisuu-1];
	m_yamaMaisuu--;

	m_mekuruCount = 0;
	m_subMode = 3;
}

/*
void CMiniGameGolf::StartModosu(void)
{
	CAreaControl::SetNextAllPrint();
	if (m_daiMaisuu <= 0) return;//error!

	m_modosuCountMax = m_daiMaisuu + 10;
	m_modosuCount = 0;
	m_subMode = 4;
}
*/

void CMiniGameGolf::CalcuStartNaraberu(void)
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



void CMiniGameGolf::CalcuKieru(void)
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

		if (m_kieru > 1)
		{
			int nx = (m_kieru-2) % 5;
			int ny = (m_kieru-2) / 5;
			m_daifuda = m_ba[ny][nx];

			m_ba[ny][nx] = -1;
			m_baMaisuu[ny]--;
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


void CMiniGameGolf::CalcuMekuru(void)
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
		m_daifuda = m_mekuruCard;
//		m_daiMaisuu++;

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

/*
void CMiniGameGolf::CalcuModosu(void)
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
*/

BOOL CMiniGameGolf::CheckSkip(void)
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




int CMiniGameGolf::Print(void)
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
		for (int i=0;i<35;i++)
		{
			int card = m_ba[i / 5][i % 5];
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
//	else if (m_subMode == 4)
//	{
//		PrintModosu();
//	}

	return -1;
}


POINT CMiniGameGolf::GetCardZahyo(int n)
{
	POINT pt = m_cardZahyo[n];

	return pt;
}


void CMiniGameGolf::PrintNormal(void)
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
		
		BOOL chkFlag = FALSE;
		PrintDai(selFlag,chkFlag);

		for (int j=0;j<7;j++)
		{
			int maisuu = m_baMaisuu[j];
			for (int i=0;i<maisuu;i++)
			{
				int card = m_ba[j][i];
				if (card != -1)
				{
					int n = i + j * 5 + 2;
					POINT pt = GetCardZahyo(n);

					BOOL selFlag = FALSE;
///@@@					BOOL chkFlag = FALSE;

					if (n == m_nowSelect)
					{
						selFlag = TRUE;
					}


					PutCard(pt,card,100,selFlag);
				}
			}
		}
	}
}


void CMiniGameGolf::PrintStartNaraberu(void)
{
	CAreaControl::SetNextAllPrint();

	PrintYama();
	PrintDai();

	int dv = m_startNaraberuCountMax - 35;
	if (dv<1) dv = 1;

	POINT pt0 = GetCardZahyo(0);

	int x1 = pt0.x;
	int y1 = pt0.y;

	for (int i=0;i<35;i++)
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

			PutCard(x,y,m_ba[i/5][i % 5]);
		}
	}
}

void CMiniGameGolf::PrintKieru(void)
{
	CAreaControl::SetNextAllPrint();

	PrintYama();
//	if ((m_kieru1 == 1) || (m_kieru2 == 1))
//	{
//		PrintDai(FALSE,FALSE,100,TRUE);
//	}
//	else
//	{
	PrintDai();
//	}

	int ps = 50+((m_kieruCountMax - m_kieruCount) * 50) / m_kieruCountMax;
	if (ps<1) ps = 1;
	if (ps>99) ps = 99;

//	if ((m_kieru1 == 1) || (m_kieru2 == 1))
//	{
//		if (m_daiMaisuu > 0)
//		{
//			POINT pt = GetCardZahyo(1);
//			PutCard(pt,m_dai[m_daiMaisuu-1],ps);
//		}
//	}



	int i,j;

	for (j=0;j<7;j++)
	{
		int maisuu = m_baMaisuu[j];
		for (i=0;i<maisuu;i++)
		{
			int n = i+j*5+2;

			int card = m_ba[j][i];
			POINT pt = GetCardZahyo(n);

			if (card != -1)
			{
				if (n == m_kieru)
				{
					POINT pt2 = GetCardZahyo(1);
					POINT pt3;
					pt3.x = pt.x + ((pt2.x - pt.x) * m_kieruCount) / m_kieruCountMax;
					pt3.y = pt.y + ((pt2.y - pt.y) * m_kieruCount) / m_kieruCountMax;

				//	PutCard(pt3,card,ps);
				}
				else
				{
					PutCard(pt,card);
				}
			}
		}
	}

	for (j=0;j<7;j++)
	{
		int maisuu = m_baMaisuu[j];
		for (i=0;i<maisuu;i++)
		{
			int n = i+j*5+2;

			int card = m_ba[j][i];
			POINT pt = GetCardZahyo(n);

			if (card != -1)
			{
				if (n == m_kieru)
				{
					POINT pt2 = GetCardZahyo(1);
					POINT pt3;
					pt3.x = pt.x + ((pt2.x - pt.x) * m_kieruCount) / m_kieruCountMax;
					pt3.y = pt.y + ((pt2.y - pt.y) * m_kieruCount) / m_kieruCountMax;

					PutCard(pt3,card,ps);
				}
				else
				{
				//	PutCard(pt,card);
				}
			}
		}
	}

}


void CMiniGameGolf::PrintMekuru(void)
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
	
	for (int j=0;j<7;j++)
	{
		int maisuu = m_baMaisuu[j];
		for (int i=0;i<maisuu;i++)
		{
			int card = m_ba[j][i];
			if (card != -1)
			{
				POINT pt = GetCardZahyo(i+j*5+2);
				PutCard(pt,card);
			}
		}
	}
}

/*
void CMiniGameGolf::PrintModosu(void)
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
*/

void CMiniGameGolf::Shuffle(void)
{
	int i = 0;
	for (i=0;i<54;i++)
	{
		m_yama[i] = i;
	}

	for (i=0;i<54;i++)
	{
		int r = (i+(rand() % 53)) % 54;
		int tmp = m_yama[r];
		m_yama[r] = m_yama[i];
		m_yama[i] = tmp;
	}
}

void CMiniGameGolf::PutCard(POINT pt,int card,int trans,BOOL sel)
{
	int x = pt.x;
	int y = pt.y;
	PutCard(x,y,card,trans,sel);
}


void CMiniGameGolf::PutCard(int x,int y,int card,int trans,BOOL sel)
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

//	if (chk)
//	{
//		src = GetCardPic(56+chk);
//		srcX = (4 + (chk-1)) * sizeX;
//		srcY = 4 * sizeY;
//		m_trumpPic->Blt(x,y,src.x,src.y,sizeX,sizeY,TRUE);
//	}
}

POINT CMiniGameGolf::GetCardPic(int n)
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

void CMiniGameGolf::PrintYama(BOOL selFlag,int ps)
{
	int card = 54;
	POINT pt = GetCardZahyo(0);

	if (m_yamaMaisuu == 0)
	{
		card = 55;
	}
//@@	int bad = 0;

//	if (card == 55)
//	{
//		if (m_reShuffleCount <= 0)
//		{
//			bad = 2;
//		}
//	}

	PutCard(pt,card,ps,selFlag);
}

void CMiniGameGolf::PrintDai(BOOL selFlag,BOOL chkFlag,int ps)
{
	int card = 55;
	POINT pt = GetCardZahyo(1);
//	int n = m_daiMaisuu;
//	if (kieruFlag)
//	{
//		n--;
//	}
//	if (n > 0)
//	{
	if (m_daifuda != -1)
	{
		card = m_daifuda;
	}

//	}
	int chkFlagNum = 0;
	if (chkFlag) chkFlagNum = 1;
	PutCard(pt,card,ps,selFlag);
}


void CMiniGameGolf::CheckCannot(void)
{
	if (CheckClear()) return;
	if (m_yamaMaisuu > 0) return;


	for (int j=0;j<7;j++)
	{
		int maisuu = m_baMaisuu[j];
		if (maisuu>0)
		{
			if (CheckClickOk(2+maisuu-1+j*5))
			{
				return;
			}
		}
	}

	m_gameoverFlag = TRUE;
}




void CMiniGameGolf::CheckAllGet(void)
{
//	if (m_yamaMaisuu > 0) return;
//	if (m_daiMaisuu > 0) return;

	for (int j=0;j<7;j++)
	{
		if (m_baMaisuu[j] > 0) return;
	}
	m_clearFlag = TRUE;
}



int CMiniGameGolf::GetOnCard(POINT pt)
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
	}


	for (int j=0;j<7;j++)
	{
		int maisuu = m_baMaisuu[j];
		if (maisuu>0)
		{
			int n = j*5+maisuu-1+2;

			POINT pt2 = GetCardZahyo(n);
			if (CheckOnCard(pt,pt2))
			{
				if (CheckClickOk(n))
				{
					return n;
				}
			}
		}
	}

	return -1;
}


BOOL CMiniGameGolf::CheckClickOk(int n)
{
	if (n<2) return FALSE;
	if (n>=2+35) return FALSE;

	n -= 2;
	int nx = n % 5;
	int ny = n / 5;

	int maisuu = m_baMaisuu[ny];
	if (maisuu <= 0) return FALSE;
	if (nx != maisuu-1) return FALSE;

	int card = m_ba[ny][nx];
	if ((card == 52) || (card == 53)) return TRUE;
	if ((m_daifuda == 52) || (m_daifuda == 53)) return TRUE;

	int d1 = card % 13;
	int d2 = m_daifuda % 13;

	int delta = d1 - d2;
	delta += 13*2;
	delta %= 13;

	if ((delta == 1) || (delta == 12)) return TRUE;


	return FALSE;
}

BOOL CMiniGameGolf::CheckOnCard(POINT pt,POINT pt2)
{
	int dx = pt.x - pt2.x;
	int dy = pt.y - pt2.y;

	if ((dx<0) || (dy<0)) return FALSE;
	if (dx>=m_trumpSize.cx) return FALSE;
	if (dy>=m_trumpSize.cy) return FALSE;

	//pic check??

	return TRUE;
}


int CMiniGameGolf::GetCard(int n)
{
	if (n == 0)
	{
		if (m_yamaMaisuu > 0)
		{
			return m_yama[m_yamaMaisuu-1];
		}
	}

//	if (n == 1)
//	{
//		if (m_daiMaisuu > 0)
//		{
//			return m_dai[m_daiMaisuu-1];
//		}
//	}
	
	if (n>=2)
	{
		int nx = (n-2) % 5;
		int ny = (n-5) / 5;

		return m_ba[ny][nx];
	}

	return -1;	//error!!
}


/*_*/

