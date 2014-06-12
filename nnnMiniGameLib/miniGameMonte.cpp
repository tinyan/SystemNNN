
#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nnnUtilLib\myMouseStatus.h"

#include "minigameLayoutParamName.h"

#include "allMiniGame.h"
#include "miniGameBase.h"

#include "miniGameMonte.h"



CMiniGameMonte::CMiniGameMonte(CAllMiniGame* lpAllMiniGame,int layoutParamKosuu,int* layoutParam) : CMiniGameBase(lpAllMiniGame,layoutParamKosuu,layoutParam)
{
	m_trumpPic = m_allMiniGame->GetCommonPic(0);
	m_trumpSize = m_allMiniGame->GetCommonPicSize(0);

	m_startNaraberuCountMax = 4*6 + 15;
	m_kieruCountMax = 20;
	m_tsumeruCountMax = 15;
	m_naraberuCountMax = 4*6 + 10;

	int nextX = 100;
	GetLayoutData(&nextX,MINIGAME_LAYOUTPARAM_NEXTX);
	m_cardPrintNext.x = nextX;

	int startX = 4;
	GetLayoutData(&startX,MINIGAME_LAYOUTPARAM_STARTX);
	m_cardPrintStart.x = startX;

	int nextY = 150;
	GetLayoutData(&nextY,MINIGAME_LAYOUTPARAM_NEXTY);
	m_cardPrintNext.y = nextY;

	int startY = 2;
	GetLayoutData(&startY,MINIGAME_LAYOUTPARAM_STARTY);
	m_cardPrintStart.y = startY;



	m_yamaPrint.x = m_cardPrintStart.x + m_cardPrintNext.x * 7;
	m_yamaPrint.y = m_cardPrintStart.y;

	m_cardPicType = m_allMiniGame->GetPicType(0);
}


CMiniGameMonte::~CMiniGameMonte()
{
	End();
}


void CMiniGameMonte::End(void)
{
}

int CMiniGameMonte::Init(void)
{
	m_clearFlag = FALSE;

	CAreaControl::SetNextAllPrint();

	m_firstClick = -1;
	m_subMode = 1;

	Shuffle();
	m_yamaMaisuu = 52;
	for (int j=0;j<4;j++)
	{
		for (int i=0;i<6;i++)
		{
			m_ba[j][i] = m_yama[m_yamaMaisuu-1];
			m_yamaMaisuu--;
		}
	}

	m_startNaraberuCount = 0;
	m_nowSelect = -1;
	m_maeSelect = -1;

	return -1;
}

int CMiniGameMonte::Calcu(void)
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
			CalcuTsumeru();
		}

		if (m_subMode == 4)
		{
			CalcuNaraberu();
		}

		return -1;
	}

	m_maeSelect = m_nowSelect;
	m_nowSelect = -1;

	POINT pt = m_mouseStatus->GetZahyo();
	int on = GetOnCard(pt);
	if (on != -1)
	{
		if (on == 52)
		{
			if (CheckTsumerareru())
			{
				m_nowSelect = on;
			}
			else
			{
				if (m_yamaMaisuu>0)
				{
					if (CheckSukimaaru())
					{
						m_nowSelect = on;
					}
				}
			}
		}
		else
		{
			int nx = on % 6;
			int ny = on / 6;
			if (m_ba[ny][nx] != -1)
			{
				m_nowSelect = on;
			}
		}
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
			if (m_nowSelect == 52)
			{
				m_allMiniGame->PlayClickSound();
				m_firstClick = -1;
				ClickYama();
				return -1;
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
					m_allMiniGame->PlayClickSound();
					m_firstClick = m_nowSelect;
					CAreaControl::SetNextAllPrint();
					return -1;
				}
				else
				{
					//‚¿‚©‚¢?
					int x1 = m_firstClick % 6;
					int y1 = m_firstClick / 6;
					int x2 = m_nowSelect % 6;
					int y2 = m_nowSelect / 6;
					BOOL nearFlag = TRUE;
					int dx = x1 - x2;
					int dy = y1 - y2;
					if ((dx<-1) || (dx>1) || (dy<-1) || (dy>1))
					{
						nearFlag = FALSE;
					}

					int card1 = m_ba[y1][x1];
					int card2 = m_ba[y2][x2];
					int n1 = card1 % 13;
					int n2 = card2 % 13;
					if ((n1 != n2) || (nearFlag == FALSE))
					{
						m_allMiniGame->PlayBadSound();
						return -1;
					}
					else
					{
						m_nextClick = m_nowSelect;
						m_allMiniGame->PlayGoodSound();
						StartKieru();
						return -1;
					}
				}
			}
		}
	}

	return -1;
}

void CMiniGameMonte::ClickYama(void)
{
	if (CheckTsumerareru())
	{
		StartTsumeru();
		return;
	}

	if (CheckSukimaaru())
	{
		if (m_yamaMaisuu>0)
		{
			StartNaraberu();
			return;
		}
	}
}


void CMiniGameMonte::CalcuStartNaraberu(void)
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

void CMiniGameMonte::StartNormal(void)
{
	CAreaControl::SetNextAllPrint();
	m_subMode = 0;
	m_firstClick = -1;
	m_maeSelect = -1;
	m_nowSelect = -1;
}

void CMiniGameMonte::StartKieru(void)
{
	m_kieruCount = 0;
	m_subMode = 2;
	CAreaControl::SetNextAllPrint();
}

void CMiniGameMonte::StartTsumeru(void)
{
	int i,j;
	int n = 0;

	for (j=0;j<4;j++)
	{
		for (i=0;i<6;i++)
		{
			int card = m_ba[j][i];
			if (card != -1)
			{
				m_mokutekichi[j][i] = n;
				n++;
			}
		}
	}

	m_tsumeruCount = 0;
	m_subMode = 3;
	CAreaControl::SetNextAllPrint();
}

void CMiniGameMonte::StartNaraberu(void)
{
	int i,j;
	m_normalMaisuu = 0;
	int n = 0;

	for (j=0;j<4;j++)
	{
		for (i=0;i<6;i++)
		{
			if (m_ba[j][i] != -1)
			{
				m_normalMaisuu++;
			}
			else
			{
				if (m_yamaMaisuu>0)
				{
					m_ba[j][i] = m_yama[m_yamaMaisuu-1];
					m_yamaMaisuu--;
					n++;
				}
			}
		}
	}

	m_naraberuMaisuu = n;
	m_naraberuCountMax = n + 15;

	m_naraberuCount = 0;
	m_subMode = 4;
	CAreaControl::SetNextAllPrint();
}

void CMiniGameMonte::CalcuKieru(void)
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

		int x1 = m_firstClick % 6;
		int y1 = m_firstClick / 6;
		int x2 = m_nextClick % 6;
		int y2 = m_nextClick / 6;
		m_ba[y1][x1] = -1;
		m_ba[y2][x2] = -1;

		CalcuClearCheck();
		if (CheckClear())
		{
			m_allMiniGame->PlayClearSound();
			return;
		}
		else
		{
			CalcuGameOverCheck();
			if (CheckGameover())
			{
				m_allMiniGame->PlayGameoverSound();
				return;
			}
		}

		StartNormal();
	}
}

void CMiniGameMonte::CalcuTsumeru(void)
{
	if (m_tsumeruCount >= 1)
	{
		if (CheckSkip())
		{
			m_tsumeruCount = m_tsumeruCountMax;
		}
	}

	m_tsumeruCount++;

	int i,j;

	if (m_tsumeruCount >= m_tsumeruCountMax)
	{
		int tmp[4][6];
		for (j=0;j<4;j++)
		{
			for (i=0;i<6;i++)
			{
				tmp[j][i] = -1;
			}
		}

		for (j=0;j<4;j++)
		{
			for (i=0;i<6;i++)
			{
				int card = m_ba[j][i];
				if (card != -1)
				{
					int mokuteki = m_mokutekichi[j][i];
					int x = mokuteki % 6;
					int y = mokuteki / 6;
					tmp[y][x] = card;
				}
			}
		}

		for (j=0;j<4;j++)
		{
			for (i=0;i<6;i++)
			{
				m_ba[j][i] = tmp[j][i];
			}
		}

		if (CheckSukimaaru())
		{
			if (m_yamaMaisuu>0)
			{
				StartNaraberu();
				return;
			}
		}

		CalcuGameOverCheck();
		if (CheckGameover())
		{
			m_allMiniGame->PlayGameoverSound();
			return;
		}

		StartNormal();
		return;
	}
}


void CMiniGameMonte::CalcuNaraberu(void)
{
	if (m_naraberuCount >= 1)
	{
		if (CheckSkip())
		{
			m_naraberuCount = m_naraberuCountMax;
		}
	}
	m_naraberuCount++;

	if (m_naraberuCount >= m_naraberuCountMax)
	{
		CalcuGameOverCheck();
		if (CheckGameover())
		{
			m_allMiniGame->PlayGameoverSound();
			return;
		}

		StartNormal();
		return;
	}
}

BOOL CMiniGameMonte::CheckSkip(void)
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

int CMiniGameMonte::Print(void)
{
	if (m_clearFlag)
	{
		CAreaControl::SetNextAllPrint();
		m_pic1->Put(0,0,FALSE);
		return -1;
	}

	if (CheckGameover())
	{
		CAreaControl::SetNextAllPrint();
		m_pic1->Put(0,0,FALSE);

		PrintYama();
		for (int j=0;j<4;j++)
		{
			for (int i=0;i<6;i++)
			{
				int card = m_ba[j][i];
				if (card != -1)
				{
					int x = m_cardPrintStart.x + m_cardPrintNext.x * i;
					int y = m_cardPrintStart.y + m_cardPrintNext.y * j;

					PutCard(x,y,card,60);
				}
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
		PrintTsumeru();
	}
	else if (m_subMode == 4)
	{
		PrintNaraberu();
	}

	return -1;
}

void CMiniGameMonte::PrintNormal(void)
{
//	CAreaControl::SetNextAllPrint();
	BOOL b = CAreaControl::CheckAllPrintMode();
//	int sizeX = m_trumpSize.cx;
//	int sizeY = m_trumpSize.cy;

//	if (1)
	{
		BOOL eraseFlag = FALSE;
		if (b == FALSE) eraseFlag = TRUE;

		BOOL selFlag = FALSE;
		if (m_nowSelect == 52)
		{
			selFlag = TRUE;
		}
		PrintYama(selFlag,eraseFlag);
	}


	for (int j=0;j<4;j++)
	{
		for (int i=0;i<6;i++)
		{
			int card = m_ba[j][i];
			if (card != -1)
			{
				int x = m_cardPrintStart.x + m_cardPrintNext.x * i;
				int y = m_cardPrintStart.y + m_cardPrintNext.y * j;

				int n = i + j * 6;

				BOOL printFlag = b;
				if (m_nowSelect != m_maeSelect)
				{
					if (n == m_nowSelect) printFlag = TRUE;
					if (n == m_maeSelect) printFlag = TRUE;
				}

				if (printFlag)
				{
					if (b == FALSE)
					{
						EraseCard(x,y);
					}

					BOOL selFlag = FALSE;
					BOOL chkFlag = FALSE;

					if (n == m_nowSelect)
					{
						selFlag = TRUE;
					}

					if (n == m_firstClick)
					{
						chkFlag = TRUE;
					}

					PutCard(x,y,card,100,selFlag,chkFlag);
				}
			}
		}
	}

}


void CMiniGameMonte::PrintStartNaraberu(void)
{
	CAreaControl::SetNextAllPrint();

	PrintYama();

	int dv = m_startNaraberuCountMax - 4 * 6;
	if (dv<1) dv = 1;

	int x1 = m_yamaPrint.x;
	int y1 = m_yamaPrint.y;

	for (int j=0;j<4;j++)
	{
		for (int i=0;i<6;i++)
		{
			int c = m_startNaraberuCount - i - j * 6;
			if (c<0) c = 0;
			if (c>dv) c = dv;

			int x2 = m_cardPrintStart.x + m_cardPrintNext.x * i;
			int y2 = m_cardPrintStart.y + m_cardPrintNext.y * j;

			int x = x1 + ((x2 - x1) * c) / dv;
			int y = y1 + ((y2 - y1) * c) / dv;

			PutCard(x,y,m_ba[j][i]);
		}
	}
}

void CMiniGameMonte::PrintKieru(void)
{
	CAreaControl::SetNextAllPrint();

	PrintYama();

	int ps = ((m_kieruCountMax - m_kieruCount) * 100) / m_kieruCountMax;
	if (ps<1) ps = 1;
	if (ps>99) ps = 99;

	for (int j=0;j<4;j++)
	{
		for (int i=0;i<6;i++)
		{
			int n = i + j * 6;
			int card = m_ba[j][i];
			int x = m_cardPrintStart.x + m_cardPrintNext.x * i;
			int y = m_cardPrintStart.y + m_cardPrintNext.y * j;
			if (card != -1)
			{
				if ((n == m_firstClick) || (n == m_nextClick))
				{
					PutCard(x,y,card,ps);
				}
				else
				{
					PutCard(x,y,card);
				}
			}
		}
	}
}

void CMiniGameMonte::PrintTsumeru(void)
{
	CAreaControl::SetNextAllPrint();

	PrintYama();

	for (int j=0;j<4;j++)
	{
		for (int i=0;i<6;i++)
		{
			int card = m_ba[j][i];
			if (card != -1)
			{
				int x1 = m_cardPrintStart.x + m_cardPrintNext.x * i;
				int y1 = m_cardPrintStart.y + m_cardPrintNext.y * j;

				int mokuteki = m_mokutekichi[j][i];
				int mx = mokuteki % 6;
				int my = mokuteki / 6;

				int x2 = m_cardPrintStart.x + m_cardPrintNext.x * mx;
				int y2 = m_cardPrintStart.y + m_cardPrintNext.y * my;

				int x = x1 + ((x2 - x1) * m_tsumeruCount) / m_tsumeruCountMax;
				int y = y1 + ((y2 - y1) * m_tsumeruCount) / m_tsumeruCountMax;

				PutCard(x,y,card);
			}
		}
	}
}

void CMiniGameMonte::PrintNaraberu(void)
{
	CAreaControl::SetNextAllPrint();

	PrintYama();

	int dv = m_naraberuCountMax - m_naraberuMaisuu;
	if (dv<1) dv = 1;

	int narabechu = 0;

	for (int j=0;j<4;j++)
	{
		for (int i=0;i<6;i++)
		{
			int card = m_ba[j][i];
			if (card != -1)
			{
				int x2 = m_cardPrintStart.x + m_cardPrintNext.x * i;
				int y2 = m_cardPrintStart.y + m_cardPrintNext.y * j;

				int x = x2;
				int y = y2;

				int n = i + j * 6;
				if (n>=m_normalMaisuu)
				{
					int c = m_naraberuCount - narabechu;
					narabechu++;

					if (c<0) c = 0;
					if (c>dv) c = dv;

					int x1 = m_yamaPrint.x;
					int y1 = m_yamaPrint.y;

					x = x1 + ((x2 - x1) * c) / dv;
					y = y1 + ((y2 - y1) * c) / dv;
				}

				PutCard(x,y,card);
			}
		}
	}
}

void CMiniGameMonte::Shuffle(void)
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

void CMiniGameMonte::EraseCard(int x,int y)
{
	int sizeX = m_trumpSize.cx;
	int sizeY = m_trumpSize.cy;
	m_pic1->Blt(x,y,x,y,sizeX,sizeY,FALSE);
	CAreaControl::AddArea(x,y,sizeX,sizeY);
}

void CMiniGameMonte::PutCard(int x,int y,int card,int trans,BOOL sel,BOOL chk)
{
	if (m_trumpPic == NULL) return;

	int sizeX = m_trumpSize.cx;
	int sizeY = m_trumpSize.cy;

//	int srcX = (card % 13) * sizeX;
//	int srcY = (card / 13) * sizeY;
	POINT src = GetCardPic(card);

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
		src = GetCardPic(57);
//		srcX = 5 * sizeX;
//		srcY = 4 * sizeY;
		m_trumpPic->Blt(x,y,src.x,src.y,sizeX,sizeY,TRUE);
	}
}

POINT CMiniGameMonte::GetCardPic(int n)
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

void CMiniGameMonte::PrintYama(BOOL selFlag,BOOL eraseFlag)
{

	int card = 54;
	int x = m_yamaPrint.x;
	int y = m_yamaPrint.y;
	if (eraseFlag)
	{
		EraseCard(x,y);
	}
	if (m_yamaMaisuu == 0)
	{
		card = 55;
	}
	PutCard(x,y,card,100,selFlag);
}

void CMiniGameMonte::CalcuGameOverCheck(void)
{
	if (CheckClear()) return;

	if (CheckExistOkCard()) return;
	if (CheckTsumerareru()) return;
	if (CheckSukimaaru() && (m_yamaMaisuu>0))
	{
		return;
	}

	m_gameoverFlag = TRUE;
}


BOOL CMiniGameMonte::CheckTsumerareru(void)
{
	BOOL sukima = FALSE;
	for (int j=0;j<4;j++)
	{
		for (int i=0;i<6;i++)
		{
			int card = m_ba[j][i];
			if (card  == -1)
			{
				sukima = TRUE;
			}
			else
			{
				if (sukima) return TRUE;
			}
		}
	}
	return FALSE;
}


BOOL CMiniGameMonte::CheckSukimaaru(void)
{
	if (m_ba[3][5] == -1) return TRUE;
	return FALSE;
}


void CMiniGameMonte::CalcuClearCheck(void)
{
	if (m_yamaMaisuu > 0) return;

	for (int j=0;j<4;j++)
	{
		for (int i=0;i<6;i++)
		{
			if (m_ba[j][i] != -1) return;
		}
	}
	m_clearFlag = TRUE;
}



BOOL CMiniGameMonte::CheckExistOkCard(void)
{
	for (int j=0;j<4;j++)
	{
		for (int i=0;i<6;i++)
		{
			int card = m_ba[j][i];
			if (card != -1)
			{
				for (int dy=-1;dy<=1;dy++)
				{
					for (int dx=-1;dx<=1;dx++)
					{
						int x = i + dx;
						int y = j + dy;
						if ((x>=0) && (x<6) && (y>=0) && (y<4))
						{
							if ((x != i) || (y != j))
							{
								int card2 = m_ba[y][x];
								if (card2 != -1)
								{
									int n1 = card % 13;
									int n2 = card2 % 13;
									if (n1 == n2)
									{
										return TRUE;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return FALSE;
}

int CMiniGameMonte::GetOnCard(POINT pt)
{
	int sizeX = m_trumpSize.cx;
	int sizeY = m_trumpSize.cy;

	int dx = pt.x - m_yamaPrint.x;
	int dy = pt.y - m_yamaPrint.y;

	if ((dx>=0) && (dx<sizeX) && (dy>=0) && (dy<sizeY))
	{
//		if (1)
		{
			return 52;
		}
//		return -1;
	}

	dx = pt.x - m_cardPrintStart.x;
	dy = pt.y - m_cardPrintStart.y;
	if ((dx<0) || (dy<0)) return -1;

	int nextX = m_cardPrintNext.x;
	int nextY = m_cardPrintNext.y;

	int nx = dx / nextX;
	int ny = dy / nextY;
	if ((nx>=6) || (ny>=4)) return -1;

	int amariX = dx % nextX;
	if (amariX >= sizeX) return -1;
	
	int amariY = dy % nextY;
	if (amariY >= sizeY) return -1;

	return nx + ny* 6;
}



/*_*/

