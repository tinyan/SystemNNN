
#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nnnUtilLib\myMouseStatus.h"


#include "allMiniGame.h"
#include "miniGameBase.h"

#include "miniGameMahjongCommon.h"
#include "miniGameNikaku.h"

//int CMiniGameSlide16::m_slideOkTable[]=
//{
	//1,0,0,1, 2,0,0,1, 1,3,0,-1, 2,3,0,-1, 0,1,1,0, 0,2,1,0, 3,1,-1,0, 3,2,-1,0,
//};



#define NIKAKU_START_MODE 0
#define NIKAKU_NORMAL_MODE 1
#define NIKAKU_GETTING_MODE 2
#define NIKAKU_ERASE_MODE 3
#define NIKAKU_DROP_MODE 4
#define NIKAKU_HINT_MODE 5


CMiniGameNikaku::CMiniGameNikaku(CAllMiniGame* lpAllMiniGame,int layoutParamKosuu,int* layoutParam) : CMiniGameMahjongCommon(lpAllMiniGame,layoutParamKosuu,layoutParam)
{
	m_map = new int[20*10];
	m_downMax = new int[20*10];
	m_downed = new int[20*10];
	m_mapTmp = new int[20*10];

	m_printX = 0;
	m_printY = 0;

	m_eraseCountMax = 25;
	m_gettingCountMax = 10;

	m_hintCountMax = 30-1;
}


CMiniGameNikaku::~CMiniGameNikaku()
{
	End();
}


void CMiniGameNikaku::End(void)
{
	DELETEARRAY(m_mapTmp);
	DELETEARRAY(m_downed);
	DELETEARRAY(m_downMax);
	DELETEARRAY(m_map);
}

int CMiniGameNikaku::Init(void)
{
	int work[18*8];
	for (int i=0;i<18*8;i++)
	{
		work[i] = i+1;
	}

	//shuffle
	for (int i=0;i<18*8;i++)
	{
		int k = rand() % (18*8);
		int tmp = work[i];
		work[i] = work[k];
		work[k] = tmp;
	}

	for (int i=0;i<20*10;i++)
	{
		m_map[i] = 0;
	}

	for (int j=0;j<8;j++)
	{
		for (int i=0;i<18;i++)
		{
			int k = (j+1)*20 + i + 1;

			m_map[k] = work[j*18+i];
		}
	}

	if (CheckGetExist() == FALSE)
	{
		int p = GetNikakuPai(21);
		int type = (p-1) / 4;

		int found = -1;
		for (int j=1;j<=8;j++)
		{
			for (int i=1;i<=18;i++)
			{
				if ((i == 1) && (j==1)) continue;

				int p2 = GetNikakuPai(j*20+i);
				int type2 = (p2-1) / 4;
				if (type == type2)
				{
					found = j*20+i;
					break;
				}
			}

			if (found != -1) break;
		}

		if (found != -1)
		{
			int tmp = m_map[22];
			m_map[22] = m_map[found];
			m_map[found] = tmp;
		}
	}



	m_clearFlag = FALSE;

	m_nikakuMode = NIKAKU_START_MODE;
	m_startWaitCount = 0;

	CAreaControl::SetNextAllPrint();
//	m_lastClickN = -1;

	m_firstSelect = -1;
	m_secondSelect = -1;
	m_nowSelect = -1;
	m_maeSelect = -1;

	m_haveHint = 6;
#if defined _DEBUG
	m_haveHint = 30;
#endif

	//m_fromX = -1;
	//m_fromY = -1;
	//m_secondSelect = -1;
	//m_toX = -1;
	//m_toY = -1;
	//m_curveKosuu = 0;

	return -1;
}

int CMiniGameNikaku::Calcu(void)
{
	if (m_clearFlag)
	{
		return -1;
	}

	if (m_gameoverFlag)
	{
		return -1;
	}

	if (m_nikakuMode == NIKAKU_START_MODE)
	{
		return CalcuStart();
	}

	if (m_nikakuMode == NIKAKU_NORMAL_MODE)
	{
		return CalcuNormal();
	}

	if (m_nikakuMode == NIKAKU_GETTING_MODE)
	{
		return CalcuGetting();
	}

	if (m_nikakuMode == NIKAKU_ERASE_MODE)
	{
		return CalcuErase();
	}

	if (m_nikakuMode == NIKAKU_DROP_MODE)
	{
		return CalcuDrop();
	}

	if (m_nikakuMode == NIKAKU_HINT_MODE)
	{
		return CalcuHint();
	}

//	m_lastClickN = -1;

	/*
	if (m_mouseStatus->CheckClick())
	{
		POINT pt = m_mouseStatus->GetZahyo();
		int screenSizeX = CMyGraphics::GetScreenSizeX();
		int screenSizeY = CMyGraphics::GetScreenSizeY();
		int x = pt.x;
		int y = pt.y;
		if ((x>=0) && (y>=0))
		{
			x /= (screenSizeX / 4);
			y /= (screenSizeY / 4);

			if ((x<4) && (y<4))
			{
				int n = SearchSlideOkPanel(x,y);
				if (n != -1)
				{
					SlidePanel(n);
					m_lastClickN = n;

					m_clearFlag = TRUE;
					for (int j=0;j<4;j++)
					{
						for (int i=0;i<4;i++)
						{
							if ((i+j*4) != m_map[j][i])
							{
								m_clearFlag = FALSE;
								break;
							}
						}
					}
				}
			}

			if (m_clearFlag)
			{
				m_allMiniGame->PlayClearSound();
			}
			else
			{
				m_allMiniGame->PlayClickSound();
			}
		}
	}
*/


	return -1;
}

int CMiniGameNikaku::CalcuStart(void)
{
	m_startWaitCount++;
	
	if (m_mouseStatus->CheckClick(0))
	{
		m_startWaitCount = 8*18 + 1;
	}
	if (m_mouseStatus->CheckClick(1))
	{
		m_startWaitCount = 8*18 + 1;
	}

	if (m_startWaitCount > 8* 18)
	{
		CAreaControl::SetNextAllPrint();
		m_nikakuMode = NIKAKU_NORMAL_MODE;
	}


	//startup 演出
	return -1;
}

int CMiniGameNikaku::CalcuNormal(void)
{
	//1こせんたく時もここでしょり
	POINT pt = m_mouseStatus->GetZahyo();
	int n = GetOnBlockNumber(pt);
	m_maeSelect = m_nowSelect;
	m_nowSelect = -1;

	if (n > 0)
	{
		int p = GetNikakuPai(n);
		if (p>0)
		{
			m_nowSelect = n;
		}
	}

	BOOL hintFlag = FALSE;

	if (m_mouseStatus->CheckClick(2))
	{
		if (m_haveHint > 0)
		{
			hintFlag = TRUE;
		}
	}

	if (m_haveHint > 0)
	{
		if (m_mouseStatus->CheckClick(0))
		{
			if (CheckOnHint(pt))
			{
				hintFlag = TRUE;
			}
		}
	}

	if (hintFlag)
	{
		{
			MakeHint();
			m_haveHint--;
			m_nikakuMode = NIKAKU_HINT_MODE;
			m_hintCount = m_hintCountMax;
			m_firstSelect = -1;
			m_nowSelect = -1;
			m_maeSelect = -1;
			CAreaControl::SetNextAllPrint();
			return -1;
		}
	}


	if (m_firstSelect != -1)
	{
		BOOL cancelFlag = FALSE;
		if (m_mouseStatus->CheckClick(1))
		{
			cancelFlag = TRUE;
		}

		if (m_mouseStatus->CheckClick(0))
		{
			if (m_nowSelect == m_firstSelect)
			{
				cancelFlag = TRUE;
			}
			else if (m_nowSelect > 0)
			{
				if (CheckGetOk(m_firstSelect,m_nowSelect))
				{
					GetRoutine(m_firstSelect,m_nowSelect);
					return -1;
				}
				return -1;
			}
		}

		if (cancelFlag)
		{
			m_firstSelect = -1;
			CAreaControl::SetNextAllPrint();
			return -1;
		}
	}

	if (m_mouseStatus->CheckClick(0))
	{
		if (m_nowSelect > 0)
		{
			m_firstSelect = m_nowSelect;
			m_allMiniGame->PlayClickSound();
			return -1;
		}
	}


	return -1;
}

int CMiniGameNikaku::CalcuHint(void)
{
	if (m_hintCount > 0)
	{
		CAreaControl::SetNextAllPrint();
	}

	m_hintCount--;
	if (m_hintCount<0)
	{
		m_hintCount = 0;
	}

	BOOL flg = FALSE;
	if (m_mouseStatus->CheckClick(0)) flg = TRUE;
	if (m_mouseStatus->CheckClick(1)) flg = TRUE;
	if (m_mouseStatus->CheckClick(2)) flg = TRUE;

	if (flg)
	{
		m_nowSelect = -1;
		m_maeSelect = -1;
		m_firstSelect = -1;
		m_secondSelect = -1;
		CAreaControl::SetNextAllPrint();
		m_nikakuMode = NIKAKU_NORMAL_MODE;
		return -1;
	}

	return -1;
}


void CMiniGameNikaku::GetRoutine(int first,int second)
{
	int dummy = first;
	dummy++;

	m_secondSelect = second;
	
	//make lines
//	m_curveKosuu = 0;



	m_allMiniGame->PlayGoodSound();
	m_nikakuMode = NIKAKU_GETTING_MODE;
	m_gettingMode = 0;
	m_gettingCount = 0;
}

BOOL CMiniGameNikaku::CheckGetOk(int first,int second)
{
	//route もさがしておく

	int p1 = GetNikakuPai(first);
	int p2 = GetNikakuPai(second);
	if (p1<1) return FALSE;
	if (p2<1) return FALSE;

	int type1 = (p1-1) / 4;
	int type2 = (p2-1) / 4;
	if (type1 != type2) return FALSE;

//直線
	int x1 = first % 20;
	int y1 = first / 20;
	int x2 = second % 20;
	int y2 = second / 20;

	m_curveKosuu = 0;

	if ((x1 == x2) || (y1 == y2))
	{
		if (x1 == x2)
		{
			if (y1 == (y2+1)) return TRUE;
			if (y1 == (y2-1)) return TRUE;
		}

		if (y1 == y2)
		{
			if (x1 == (x2+1)) return TRUE;
			if (x1 == (x2-1)) return TRUE;
		}

		if (CheckLine(x1,y1,x2,y2,FALSE))
		{
			return TRUE;
		}
	}

	//1かい
	m_curveKosuu = 1;
	if (CheckLine(x1,y1,x1,y2,TRUE))
	{
		if (CheckLine(x2,y2,x1,y2))
		{
			m_curveX1 = x1;
			m_curveY1 = y2;
			return TRUE;
		}
	}
	if (CheckLine(x1,y1,x2,y1,TRUE))
	{
		if (CheckLine(x2,y2,x2,y1))
		{
			m_curveX1 = x2;
			m_curveY1 = y1;
			return TRUE;
		}
	}

	//2回
	m_curveKosuu = 2;
	for (int i=0;i<20;i++)
	{
		int x3 = i;
		int y3 = y1;
		int x4 = i;
		int y4 = y2;
		if ((x3 != x1) && (x3 != x2))
		{
			if (CheckLine(x1,y1,x3,y3,TRUE))
			{
				if (CheckLine(x2,y2,x4,y4,TRUE))
				{
					if (CheckLine(x3,y3,x4,y4,TRUE))
					{
						m_curveX1 = x3;
						m_curveY1 = y3;
						m_curveX2 = x4;
						m_curveY2 = y4;
						return TRUE;
					}
				}
			}
		}
	}

	for (int j=0;j<10;j++)
	{
		int x3 = x1;
		int y3 = j;
		int x4 = x2;
		int y4 = j;
		if ((y3 != y1) && (y3 != y2))
		{
			if (CheckLine(x1,y1,x3,y3,TRUE))
			{
				if (CheckLine(x2,y2,x4,y4,TRUE))
				{
					if (CheckLine(x3,y3,x4,y4,TRUE))
					{
						m_curveX1 = x3;
						m_curveY1 = y3;
						m_curveX2 = x4;
						m_curveY2 = y4;
						return TRUE;
					}
				}
			}
		}
	}



	return FALSE;
}

BOOL CMiniGameNikaku::CheckLine(int x1,int y1,int x2,int y2,BOOL lastCheckFlag)
{
	if (x1 == x2)
	{
		int loopY = y2 - y1;
		int startY = y1;
		int dy = 1;
		if (loopY < 0)
		{
			loopY *= -1;
//			startY = y2;
			dy = -1;
		}

		if (lastCheckFlag == FALSE)
		{
			loopY--;
		}

		if (loopY < 1) return TRUE;
		
		int count = 0;
		for (int i=1;i<=loopY;i++)
		{
			startY += dy;
			int p3 = GetNikakuPai(startY*20+x1);
			if (p3 > 0) break;
			count++;
		}
		if (count >= loopY)
		{
			return TRUE;
		}
	}

	if (y1 == y2)
	{
		int loopX = x2 - x1;
		int startX = x1;
		int dx = 1;
		if (loopX < 0)
		{
			loopX *= -1;
//			startX = x2;
			dx = -1;
		}

		if (lastCheckFlag == FALSE)
		{
			loopX--;
		}

		if (loopX < 1) return TRUE;
		
		int count = 0;
		for (int i=1;i<=loopX;i++)
		{
			startX += dx;;
			int p3 = GetNikakuPai(y1*20+startX);
			if (p3 > 0) break;
			count++;
		}
		if (count >= loopX)
		{
			return TRUE;
		}
	}

	return FALSE;
}




BOOL CMiniGameNikaku::CheckGetExist(void)
{
	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;

			int p = GetNikakuPai(n);
			if (p>0)
			{
				for (int jj=1;jj<=8;jj++)
				{
					for (int ii=1;ii<=18;ii++)
					{
						int nn = jj*20 + ii;
						int pp = GetNikakuPai(nn);
						if (pp > 0)
						{
							if (n != nn)
							{
								if (CheckGetOk(n,nn))
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

	return FALSE;
}

int CMiniGameNikaku::GetNikakuPai(int n)
{
	if ((n<0) || (n>=20*10)) return -1;

	return m_map[n];
}

BOOL CMiniGameNikaku::CheckAllGet(void)
{
	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
			int p = GetNikakuPai(n);
			if (p>0) return FALSE;
		}
	}

	return TRUE;
}

int CMiniGameNikaku::CalcuGetting(void)
{
	m_gettingCount++;
	BOOL flg = FALSE;

	if (m_gettingCount > m_gettingCountMax)
	{
		m_gettingMode++;
		if (m_gettingMode > m_curveKosuu)
		{
			flg = TRUE;
		}
		else
		{
			m_gettingCount = 0;
		}
	}

	if (m_mouseStatus->CheckClick(0))
	{
		flg = TRUE;
	}
	if (m_mouseStatus->CheckClick(1))
	{
		flg = TRUE;
	}

	if (flg)
	{
//		AddErasePai(m_firstSelect,m_secondSelect);

		int fromPai = m_map[m_firstSelect];

		m_map[m_firstSelect] = -1;
		m_map[m_secondSelect] = -1;

		if (CheckAllGet())
		{
			m_allMiniGame->PlayClearSound();
			m_clearFlag = TRUE;
			return -1;
		}
		
		int pp = (fromPai-1) / 4;
		if ((pp == 34) || (pp == 35))
//		if (pp>=18)
		{
			m_nikakuMode = NIKAKU_ERASE_MODE;
			m_eraseCount = m_eraseCountMax;
//			m_haveHint++;
			return -1;
		}

		if (CheckGetExist() == FALSE)
		{
			m_allMiniGame->PlayGameoverSound();
			m_gameoverFlag = TRUE;
			return -1;
		}

		m_firstSelect = -1;
		m_secondSelect = -1;
		m_nikakuMode = NIKAKU_NORMAL_MODE;
		CAreaControl::SetNextAllPrint();
		return -1;
	}




	//バーをのばして取るところまで7
	//とったら、クリアー、ゲームオーバーチェックをかける

	return -1;
}

int CMiniGameNikaku::CalcuDrop(void)
{
	//count
	m_downSpeed++;
	int sizeY = m_paiSize.cy;

	BOOL flg = TRUE;
	CAreaControl::SetNextAllPrint();

	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j*20+i;
			int p = GetNikakuPai(n);
			if (p>0)
			{
				int downMax = m_downMax[n];
				if (downMax > 0)
				{
					int y = m_downed[n];
					y += m_downSpeed;
					if (y >= downMax*sizeY)
					{
						y = downMax*sizeY;
					}
					else
					{
						flg = FALSE;
					}
					m_downed[n] = y;
				}
			}
		}
	}

	if (flg == FALSE)
	{
		return -1;
	}

	//all down
	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
			m_mapTmp[n] = 0;
		}
	}

	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
			int p = m_map[n];
			if (p>0)
			{
				int down = m_downMax[n];
				m_mapTmp[n+20*down] = p;
			}
		}
	}

	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
			m_map[n] = m_mapTmp[n];
		}
	}

	if (CheckGetExist() == FALSE)
	{
		m_allMiniGame->PlayGameoverSound();
		m_gameoverFlag = TRUE;
		return -1;
	}

	m_firstSelect = -1;
	m_secondSelect = -1;
	m_nikakuMode = NIKAKU_NORMAL_MODE;

	return -1;
}

int CMiniGameNikaku::CalcuErase(void)
{
	m_eraseCount--;
	if (m_mouseStatus->CheckClick(0)) m_eraseCount = 0;
	if (m_mouseStatus->CheckClick(1)) m_eraseCount = 0;

	if (m_eraseCount <= 0)
	{
		for (int j=1;j<=8;j++)
		{
			for (int i=1;i<=18;i++)
			{
				int n = j * 20 + i;
				int p = GetNikakuPai(n);
				m_downed[n] = 0;
				m_downMax[n] = 0;

				if (p == -1)
				{
					m_map[n] = 0;
				}

				if (p>0)
				{
					int down = 0;
					for (int jj=j+1;jj<=8;jj++)
					{
						int n2 = jj*20+i;
						int pp = m_map[n2];
						if (pp<1)
						{
							down++;
						}
					}
					m_downMax[n] = down;
				}
			}
		}

		m_downSpeed = 0;
		m_nikakuMode = NIKAKU_DROP_MODE;
		return -1;
	}

	return -1;
}

int CMiniGameNikaku::Print(void)
{
	if (m_clearFlag)
	{
		CAreaControl::SetNextAllPrint();
		CPicture* pic = m_pic1;
	//	if (m_map[0][0] == 1) pic = m_pic2;
		pic->Put(0,0,FALSE);
		return -1;
	}

	if (CheckGameover())
	{
		CAreaControl::SetNextAllPrint();
		CPicture* pic = m_pic1;
		pic->Put(0,0,FALSE);


		for (int j=1;j<=8;j++)
		{
			for (int i=1;i<=18;i++)
			{
				POINT pt = GetNikakuZahyo(i,j);
				int x = pt.x;
				int y = pt.y;

				int p = m_map[j*20+i];
				if ((p > 0) || (p == -1))
				{
					PutPai(x,y,p,40);
				}
			}
		}

		return -1;
	}


	if (m_nikakuMode == NIKAKU_START_MODE)
	{
		return PrintStart();
	}

	if (m_nikakuMode == NIKAKU_NORMAL_MODE)
	{
		return PrintNormal();
	}

	if (m_nikakuMode == NIKAKU_GETTING_MODE)
	{
		return PrintGetting();
	}

	if (m_nikakuMode == NIKAKU_ERASE_MODE)
	{
		return PrintErase();
	}

	if (m_nikakuMode == NIKAKU_DROP_MODE)
	{
		return PrintDrop();
	}

	if (m_nikakuMode == NIKAKU_HINT_MODE)
	{
		return PrintHint();
	}


	return -1;
}

int CMiniGameNikaku::PrintStart(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();

	if (b)
	{
		CPicture* pic = m_pic1;
		pic->Put(0,0,FALSE);
		PrintHaveHint();
	}

	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			POINT pt = GetNikakuZahyo(i,j);
			int x = pt.x;
			int y = pt.y;

			int p = m_map[j*20+i];
			if (b)
			{
				if (p<m_startWaitCount)
				{
					PutPai(x,y,p);
				}
				else
				{
					PutPai(x,y,-1);
				}
			}
			else
			{
				if (p == m_startWaitCount)
				{
					PutPai(x,y,p);
					CAreaControl::AddArea(x,y,m_paiSize.cx,m_paiSize.cy);
				}
				else if (m_startWaitCount == 1)
				{
					PutPai(x,y,-1);
				}
			}
		}
	}
	return -1;
}

int CMiniGameNikaku::PrintNormal(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();

	if (b)
	{
		CPicture* pic = m_pic1;
		pic->Put(0,0,FALSE);
		PrintHaveHint();
	}

	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
//@@			BOOL flg = FALSE;
			if (b || (n == m_nowSelect) || (n == m_maeSelect) || (n == m_firstSelect) || (n == m_secondSelect))
			{
				POINT pt = GetNikakuZahyo(i,j);
				int x = pt.x;
				int y = pt.y;

				int p = GetNikakuPai(n);
				if (p == -1)
				{
					PutPai(x,y,-1);
				}
				else if (p == 0)
				{
					ErasePai(x,y);
				}
				else if (p>0)
				{
					BOOL sel = FALSE;
					BOOL chk = FALSE;

					if (n == m_firstSelect) chk = TRUE;
					if (n == m_secondSelect) chk = TRUE;
					if (n == m_nowSelect) sel = TRUE;

					PutPai(x,y,p,100,sel,chk);
				}
			}
		}
	}

	return -1;
}



int CMiniGameNikaku::PrintHint(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();

	if (b)
	{
		CPicture* pic = m_pic1;
		pic->Put(0,0,FALSE);
		PrintHaveHint();
	}

	int ps = 50 + (m_hintCount * 50) / m_hintCountMax;
	int sizeX = m_paiSize.cx;
	int sizeY = m_paiSize.cy;

	if (b)
	{
		for (int j=1;j<=8;j++)
		{
			for (int i=1;i<=18;i++)
			{
				int n = j * 20 + i;
				POINT pt = GetNikakuZahyo(i,j);
				int x = pt.x;
				int y = pt.y;

				int p = GetNikakuPai(n);
				if (p == -1)
				{
					PutPai(x,y,-1);
				}
				else if (p > 0)
				{
					PutPai(x,y,p);
					if ((m_hintCount % 5) < 3)
					{
						if (m_mapTmp[n])
						{
							CAllGeo::TransBoxFill(x,y,sizeX,sizeY,255,64,128,ps);
						}
					}
				}
			}
		}
	}

	return -1;
}

int CMiniGameNikaku::PrintGetting(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();
	if (b)
	{
		PrintNormal();
//		PrintHaveHint();
	}

	//line
	int x[4];
	int y[4];
	x[0] = m_firstSelect % 20;
	y[0] = m_firstSelect / 20;
	if (m_curveKosuu == 0)
	{
		x[1] = m_secondSelect % 20;
		y[1] = m_secondSelect / 20;
	}
	else if (m_curveKosuu == 1)
	{
		x[1] = m_curveX1;
		y[1] = m_curveY1;
		x[2] = m_secondSelect % 20;
		y[2] = m_secondSelect / 20;
	}
	else if (m_curveKosuu == 2)
	{
		x[1] = m_curveX1;
		y[1] = m_curveY1;
		x[2] = m_curveX2;
		y[2] = m_curveY2;
		x[3] = m_secondSelect % 20;
		y[3] = m_secondSelect / 20;
	}

	for (int i=0;i<=m_gettingMode;i++)
	{
		int x1 = x[i];
		int y1 = y[i];
		int x2 = x[i+1];
		int y2 = y[i+1];
		

		POINT pt1 = GetNikakuZahyo(x1,y1);
		POINT pt2 = GetNikakuZahyo(x2,y2);

		int putX1 = pt1.x;
		int putY1 = pt1.y;
		int putX2 = pt2.x;
		int putY2 = pt2.y;

		putX1 += m_paiSize.cx /2;
		putY1 += m_paiSize.cy /2;
		putX2 += m_paiSize.cx /2;
		putY2 += m_paiSize.cy /2;

		int ps = 10000;

		if (i==m_gettingMode)
		{
			ps = (m_gettingCount * 10000) / m_gettingCountMax;
		}

		int putX3 = putX1 + ((putX2-putX1) * ps)/10000;
		int putY3 = putY1 + ((putY2-putY1) * ps)/10000;

		PrintBar(putX1,putY1,putX3,putY3,4,64,255,128);

	}
	return -1;
}

void CMiniGameNikaku::PrintBar(int x1,int y1,int x2,int y2,int sz,int r,int g,int b)
{
	if (x1>x2)
	{
		int tmp = x1;
		x1 = x2;
		x2 = tmp;
	}

	if (y1>y2)
	{
		int tmp = y1;
		y1 = y2;
		y2 = tmp;
	}


	x1 -= sz;
	y1 -= sz;
	x2 += sz;
	y2 += sz;

	int sizeX = x2 - x1 + 1;
	int sizeY = y2 - y1 + 1;

	CAllGeo::BoxFill(x1,y1,sizeX,sizeY,r,g,b);
	CAreaControl::AddArea(x1,y1,sizeX,sizeY);
}



int CMiniGameNikaku::PrintDrop(void)
{
	CAreaControl::SetNextAllPrint();

	CPicture* pic = m_pic1;
	pic->Put(0,0,FALSE);
	PrintHaveHint();

	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j*20+i;
			int p = m_map[n];
			if (p>0)
			{
				POINT pt = GetNikakuZahyo(i,j);
				int putX = pt.x;
				int putY = pt.y;
				putY += m_downed[n];
				PutPai(putX,putY,p);
			}
		}
	}

	return -1;
}

int CMiniGameNikaku::PrintErase(void)
{
	CAreaControl::SetNextAllPrint();

	CPicture* pic = m_pic1;
	pic->Put(0,0,FALSE);
	PrintHaveHint();

	int ps = (m_eraseCount * 100) / m_eraseCountMax;

	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
//@@			BOOL flg = FALSE;
			POINT pt = GetNikakuZahyo(i,j);
			int x = pt.x;
			int y = pt.y;

			int p = GetNikakuPai(n);
			if (p == -1)
			{
				ErasePai(x,y);
				PutPai(x,y,-1,ps);
			}
			else if (p == 0)
			{
				ErasePai(x,y);
			}
			else if (p>0)
			{
				PutPai(x,y,p);
			}
		}
	}
	return -1;
}

POINT CMiniGameNikaku::GetNikakuZahyo(int x,int y)
{
	POINT pt;
	pt.x = m_printX + m_paiSize.cx * x;
	pt.y = m_printY + m_paiSize.cy * y;
	return pt;
}

/*
int CMiniGameNikaku::SearchSlideOkPanel(int x,int y)
{
	for (int i=0;i<8;i++)
	{
		if (m_slideOkTable[i*4] == x)
		{
			if (m_slideOkTable[i*4+1] == y)
			{
				return i;
			}
		}
	}
	return -1;
}

void CMiniGameNikaku::SlidePanel(int n)
{
	int x = m_slideOkTable[n*4];
	int y = m_slideOkTable[n*4+1];
	int dx = m_slideOkTable[n*4+2];
	int dy = m_slideOkTable[n*4+3];

	x += dx*3;
	y += dy*3;
	int tmp = m_map[y][x];

	for (int i=0;i<3;i++)
	{
		int xx = x - dx;
		int yy = y - dy;
		m_map[y][x] = m_map[yy][xx];
		x = xx;
		y = yy;
	}

	m_map[y][x] = tmp;
}
*/



int CMiniGameNikaku::GetOnBlockNumber(POINT pt)
{
	int dx = pt.x - m_printX;
	int dy = pt.y - m_printY;
	
	int sizeX = m_paiSize.cx;
	int sizeY = m_paiSize.cy;

	if ((dx>=sizeX) && (dx<sizeX*19) && (dy>=sizeX) && (dy<sizeY*19))
	{
		int nx = dx / sizeX;
		int ny = dy / sizeY;

		return ny * 20 + nx;
	}

	return -1;
}

void CMiniGameNikaku::MakeHint(void)
{
	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
			m_mapTmp[n] = 0;
			int p = GetNikakuPai(n);
			if (p>0)
			{
				BOOL flg = FALSE;
				for (int jj=1;jj<=8;jj++)
				{
					for (int ii=1;ii<=18;ii++)
					{
						if ((i==ii) && (j==jj)) continue;

						int n2 = jj * 20 + ii;

						if (CheckGetOk(n,n2))
						{
							flg = TRUE;
							break;
						}
					}
					if (flg) break;
				}

				if (flg)
				{
					m_mapTmp[n] = 1;
				}
			}
		}
	}
}

/*_*/

