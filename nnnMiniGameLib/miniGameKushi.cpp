
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
#include "miniGameKushi.h"

//int CMiniGameSlide16::m_slideOkTable[]=
//{
	//1,0,0,1, 2,0,0,1, 1,3,0,-1, 2,3,0,-1, 0,1,1,0, 0,2,1,0, 3,1,-1,0, 3,2,-1,0,
//};



#define KUSHI_START_MODE 0
#define KUSHI_NORMAL_MODE 1
//#define KUSHI_GETTING_MODE 2
#define KUSHI_ERASE_MODE 3
#define KUSHI_DROP_MODE 4
#define KUSHI_HINT_MODE 5
#define KUSHI_LEFT_MODE 6
#define KUSHI_YATTANA_MODE 7



CMiniGameKushi::CMiniGameKushi(CAllMiniGame* lpAllMiniGame) : CMiniGameMahjongCommon(lpAllMiniGame)
{
	m_map = new int[20*10];
	m_downMax = new int[20*10];
	m_downed = new int[20*10];
	m_mapTmp = new int[20*10];

	m_yattana = new int[20];
	m_erasedPai = new int[20];

	m_printX = 0;
	m_printY = 0;

	m_eraseCountMax = 25;
//	m_gettingCountMax = 10;

	m_hintCountMax = 30-1;
}


CMiniGameKushi::~CMiniGameKushi()
{
	End();
}


void CMiniGameKushi::End(void)
{
	DELETEARRAY(m_erasedPai);
	DELETEARRAY(m_yattana);
	DELETEARRAY(m_mapTmp);
	DELETEARRAY(m_downed);
	DELETEARRAY(m_downMax);
	DELETEARRAY(m_map);
}

int CMiniGameKushi::Init(void)
{
	int work[18*8];
	for (int i=0;i<18*8;i++)
	{
		work[i] = i+1;
#if defined _DEBUG
//		work[i] = 1;
#endif
	}

	//shuffle
	for (int i=0;i<18*8;i++)
	{
		int k = rand() % (18*8);
		int tmp = work[i];
		work[i] = work[k];
		work[k] = tmp;
	}

/*
for (int i=0;i<18*8;i++)
{
	work[i] = 1;
}
for (int i=1;i<=2;i++)
{
	for (int j=1;j<=6;j++)
	{
		work[i+j*18] = (j-1)*4+5;
	}
}
*/

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
		int p = GetKushiPai(21);
		int type = (p-1) / 4;

		int found = -1;
		for (int j=1;j<=8;j++)
		{
			for (int i=1;i<=18;i++)
			{
				if ((i == 1) && (j==1)) continue;

				int p2 = GetKushiPai(j*20+i);
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
			int tmp = m_map[38];
			m_map[38] = m_map[found];
			m_map[found] = tmp;
		}
	}
/*
for (int j=1;j<=5;j++)
{
	for (int i=1;i<=18;i++)
	{
		m_map[j*20+i] = 0;
	}
}
for (int j=1;j<=8;j++)
{
	for (int i=7;i<=18;i++)
	{
		m_map[j*20+i] = 0;
	}
}
*/


	m_clearFlag = FALSE;

	m_kushiMode = KUSHI_START_MODE;
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

int CMiniGameKushi::Calcu(void)
{
	if (m_clearFlag)
	{
		return -1;
	}

	if (m_gameoverFlag)
	{
		return -1;
	}


	if (m_kushiMode == KUSHI_START_MODE)
	{
		return CalcuStart();
	}

	if (m_kushiMode == KUSHI_NORMAL_MODE)
	{
		return CalcuNormal();
	}

//	if (m_kushiMode == KUSHI_GETTING_MODE)
//	{
//		return CalcuGetting();
//	}

	if (m_kushiMode == KUSHI_ERASE_MODE)
	{
		return CalcuErase();
	}

	if (m_kushiMode == KUSHI_DROP_MODE)
	{
		return CalcuDrop();
	}

	if (m_kushiMode == KUSHI_HINT_MODE)
	{
		return CalcuHint();
	}

	if (m_kushiMode == KUSHI_LEFT_MODE)
	{
		return CalcuLeft();
	}

	if (m_kushiMode == KUSHI_YATTANA_MODE)
	{
		return CalcuYattana();
	}

	return -1;
}

int CMiniGameKushi::CalcuStart(void)
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
		m_kushiMode = KUSHI_NORMAL_MODE;
	}

	return -1;
}

int CMiniGameKushi::CalcuNormal(void)
{
	//1‚±‚¹‚ñ‚½‚­Žž‚à‚±‚±‚Å‚µ‚å‚è
	POINT pt = m_mouseStatus->GetZahyo();
	int n = GetOnBlockNumber(pt);
	m_maeSelect = m_nowSelect;
	m_nowSelect = -1;

	if (n > 0)
	{
		int p = GetKushiPai(n);
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
			m_kushiMode = KUSHI_HINT_MODE;
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

int CMiniGameKushi::CalcuHint(void)
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
		m_kushiMode = KUSHI_NORMAL_MODE;
		return -1;
	}

	return -1;
}


void CMiniGameKushi::GetRoutine(int first,int second)
{
	int dummy = first;
	dummy++;

	m_secondSelect = second;
	

	m_eraseCount = m_eraseCountMax;


	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			m_mapTmp[j*20+i] = 0;
		}
	}


	int x1 = m_firstSelect % 20;
	int y1 = m_firstSelect / 20;
	int x2 = m_secondSelect % 20;
	int y2 = m_secondSelect / 20;

	int loops = 0;
	int dx = 0;
	int dy = 0;

	if (y1 != y2)
	{
		loops = y2 - y1;
		dy =1;
		if (loops < 0)
		{
			loops *= -1;
			dy = -1;
		}
	}

	if (x1 != x2)
	{
		loops = x2 - x1;
		dx =1;
		if (loops < 0)
		{
			loops *= -1;
			dx = -1;
		}
	}

	for (int i=0;i<=loops;i++)
	{
		int x = x1 + dx * i;
		int y = y1 + dy * i;
		m_mapTmp[y*20+x] = 1;
	}

	m_erasedKosuu = 0;

	for (int i=0;i<loops;i++)
	{
		int x = x1 + dx * i;
		int y = y1 + dy * i;
		m_erasedPai[m_erasedKosuu] = m_map[y*20+x];
		m_erasedKosuu++;
	}



	m_allMiniGame->PlayGoodSound();
	m_kushiMode = KUSHI_ERASE_MODE;
}


BOOL CMiniGameKushi::CheckGetOk(int first,int second)
{
	//route ‚à‚³‚ª‚µ‚Ä‚¨‚­

	int p1 = GetKushiPai(first);
	int p2 = GetKushiPai(second);
	if (p1<1) return FALSE;
	if (p2<1) return FALSE;

	int type1 = (p1-1) / 4;
	int type2 = (p2-1) / 4;
	if (type1 != type2) return FALSE;

//’¼ü
	int x1 = first % 20;
	int y1 = first / 20;
	int x2 = second % 20;
	int y2 = second / 20;

	if ((x1 == x2) && (y1 == y2))
	{
		return FALSE;
	}

	if ((x1 != x2) && (y1 != y2))
	{
		if ( ((x1 - x2) < -1) || ((x1-x2) > 1) || ((y1-y2)<-1) || ((y1-y2)>1))
		{
			return FALSE;
		}
	}


	int loops = 0;
	int dx = 0;
	int dy = 0;

	if (y1 != y2)
	{
		loops = y2 - y1;
		dy =1;
		if (loops < 0)
		{
			loops *= -1;
			dy = -1;
		}
	}

	if (x1 != x2)
	{
		loops = x2 - x1;
		dx =1;
		if (loops < 0)
		{
			loops *= -1;
			dx = -1;
		}
	}

	for (int i=0;i<=loops;i++)
	{
		int x = x1 + dx * i;
		int y = y1 + dy * i;
		int p = m_map[y*20+x];
		if (p<1) return FALSE;
	}

	return TRUE;
}





BOOL CMiniGameKushi::CheckGetExist(void)
{
	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;

			int p = GetKushiPai(n);
			if (p>0)
			{
				for (int jj=1;jj<=8;jj++)
				{
					for (int ii=1;ii<=18;ii++)
					{
						int nn = jj*20 + ii;
						int pp = GetKushiPai(nn);
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

int CMiniGameKushi::GetKushiPai(int n)
{
	if ((n<0) || (n>=20*10)) return -1;

	return m_map[n];
}

BOOL CMiniGameKushi::CheckAllGet(void)
{
	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
			int p = GetKushiPai(n);
			if (p>0) return FALSE;
		}
	}

	return TRUE;
}


int CMiniGameKushi::CalcuDrop(void)
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
			int p = GetKushiPai(n);
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

	//‚·‚«‚Ü?
	if (CheckBottomSukima())
	{
		m_downSpeed = 0;
		m_kushiMode = KUSHI_LEFT_MODE;
		return -1;
	}

	if (CheckYattanaAru())
	{
		m_kushiMode = KUSHI_YATTANA_MODE;
		SetNewYattana();
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
	m_kushiMode = KUSHI_NORMAL_MODE;

	return -1;
}


int CMiniGameKushi::CalcuLeft(void)
{
	//count
	m_downSpeed++;
	int sizeX = m_paiSize.cx;

	BOOL flg = TRUE;
	CAreaControl::SetNextAllPrint();

	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j*20+i;
			int p = GetKushiPai(n);
			if (p>0)
			{
				int downMax = m_downMax[n];
				if (downMax > 0)
				{
					int x = m_downed[n];
					x += m_downSpeed;
					if (x >= downMax*sizeX)
					{
						x = downMax*sizeX;
					}
					else
					{
						flg = FALSE;
					}
					m_downed[n] = x;
				}
			}
		}
	}

	if (flg == FALSE)
	{
		return -1;
	}

	//all left
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
				m_mapTmp[n-down] = p;
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

	if (CheckYattanaAru())
	{
		m_kushiMode = KUSHI_YATTANA_MODE;
		SetNewYattana();
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
	m_kushiMode = KUSHI_NORMAL_MODE;

	return -1;
}

int CMiniGameKushi::CalcuYattana(void)
{
	//count
	m_yattanaSpeed++;
	int sizeY = m_paiSize.cy;

	BOOL flg = TRUE;
	CAreaControl::SetNextAllPrint();

	for (int j=0;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j*20+i;
			int p = GetKushiPai(n);
			if (p>0)
			{
				int downMax = m_downMax[n];
				if (downMax > 0)
				{
					int y = m_downed[n];
					y += m_yattanaSpeed;
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

	for (int j=0;j<=8;j++)
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

	for (int i=0;i<20;i++)
	{
		m_map[i] = 0;
	}

	if (m_yattanaKosuu > 0)
	{
		SetNewYattana();
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
	m_kushiMode = KUSHI_NORMAL_MODE;


	return -1;

//	return -1;
}

BOOL CMiniGameKushi::CheckYattanaAru(void)
{
	int typeKosuu[36];
	for (int i=0;i<36;i++)
	{
		typeKosuu[i] = 0;
	}

	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
			int p = m_map[n];
			if (p>0)
			{
				typeKosuu[(p-1) / 4]++;
			}
		}
	}

	m_yattanaKosuu = 0;

	for (int i=0;i<36;i++)
	{
		if (typeKosuu[i] == 1)
		{
			int found = -1;
			for (int k=0;k<m_erasedKosuu;k++)
			{
				int p = m_erasedPai[k];
				if (((p-1) / 4) == i)
				{
					found = k;
					break;
				}
			}

			if (found != -1)
			{
				m_yattana[m_yattanaKosuu] = m_erasedPai[found];
				m_yattanaKosuu++;
			}
		}
	}

	if (m_yattanaKosuu > 0) return TRUE;

	return FALSE;
}


void CMiniGameKushi::SetNewYattana(void)
{
	for (int j=0;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j*20+i;

			m_downed[n] = 0;
			m_downMax[n] = 0;
		}
	}

	int setKosuu = 0;
	for (int i=0;i<m_yattanaKosuu;i++)
	{
		int r = (rand() % 18) + 1;

		for (int k=0;k<18;k++)
		{
			if (m_map[r] == 0)
			{
				if (m_map[r+20] == 0)
				{
					m_map[r] = m_yattana[i];
					setKosuu++;
					break;
				}
			}

			r++;
			if (r>=19)
			{
				r = 1;
			}
		}
	}


	for (int i=setKosuu;i<m_yattanaKosuu;i++)
	{
		m_yattana[i-setKosuu] = m_yattana[i];
	}

	m_yattanaKosuu -= setKosuu;
	m_yattanaSpeed = 0;

	//set down

	for (int j=0;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
			int p = GetKushiPai(n);
			m_downed[n] = 0;
			m_downMax[n] = 0;

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
}


int CMiniGameKushi::CalcuErase(void)
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
				if (m_mapTmp[n])
				{
					m_map[n] = 0;
				}
			}
		}


		for (int j=1;j<=8;j++)
		{
			for (int i=1;i<=18;i++)
			{
				int n = j * 20 + i;
				int p = GetKushiPai(n);
				m_downed[n] = 0;
				m_downMax[n] = 0;

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

		if (CheckAllGet())
		{
			m_allMiniGame->PlayClearSound();
			m_clearFlag = TRUE;
			return -1;
		}

		m_downSpeed = 0;
		m_kushiMode = KUSHI_DROP_MODE;
		return -1;
	}

	return -1;
}

int CMiniGameKushi::Print(void)
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
				POINT pt = GetKushiZahyo(i,j);
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


	if (m_kushiMode == KUSHI_START_MODE)
	{
		return PrintStart();
	}

	if (m_kushiMode == KUSHI_NORMAL_MODE)
	{
		return PrintNormal();
	}

//	if (m_kushiMode == KUSHI_GETTING_MODE)
//	{
//		return PrintGetting();
//	}

	if (m_kushiMode == KUSHI_ERASE_MODE)
	{
		return PrintErase();
	}

	if (m_kushiMode == KUSHI_DROP_MODE)
	{
		return PrintDrop();
	}

	if (m_kushiMode == KUSHI_HINT_MODE)
	{
		return PrintHint();
	}

	if (m_kushiMode == KUSHI_LEFT_MODE)
	{
		return PrintLeft();
	}

	if (m_kushiMode == KUSHI_YATTANA_MODE)
	{
		return PrintYattana();
	}

	return -1;
}

int CMiniGameKushi::PrintStart(void)
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
			POINT pt = GetKushiZahyo(i,j);
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

int CMiniGameKushi::PrintNormal(void)
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
				POINT pt = GetKushiZahyo(i,j);
				int x = pt.x;
				int y = pt.y;

				int p = GetKushiPai(n);
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



int CMiniGameKushi::PrintHint(void)
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
				POINT pt = GetKushiZahyo(i,j);
				int x = pt.x;
				int y = pt.y;

				int p = GetKushiPai(n);
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




int CMiniGameKushi::PrintDrop(void)
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
				POINT pt = GetKushiZahyo(i,j);
				int putX = pt.x;
				int putY = pt.y;
				putY += m_downed[n];
				PutPai(putX,putY,p);
			}
		}
	}

	return -1;
}


int CMiniGameKushi::PrintLeft(void)
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
				POINT pt = GetKushiZahyo(i,j);
				int putX = pt.x;
				int putY = pt.y;
				putX -= m_downed[n];
				PutPai(putX,putY,p);
			}
		}
	}

	return -1;
}

int CMiniGameKushi::PrintYattana(void)
{
	CAreaControl::SetNextAllPrint();

	CPicture* pic = m_pic1;
	pic->Put(0,0,FALSE);
	PrintHaveHint();

	for (int j=0;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j*20+i;
			int p = m_map[n];
			if (p>0)
			{
				POINT pt = GetKushiZahyo(i,j);
				int putX = pt.x;
				int putY = pt.y;
				putY += m_downed[n];
				PutPai(putX,putY,p);
			}
		}
	}
	return -1;
}

int CMiniGameKushi::PrintErase(void)
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
			POINT pt = GetKushiZahyo(i,j);
			int x = pt.x;
			int y = pt.y;

			int p = GetKushiPai(n);
			if (p == -1)
			{
//				ErasePai(x,y);
				PutPai(x,y,-1);
			}
			else if (p == 0)
			{
				ErasePai(x,y);
			}
			else if (p>0)
			{
				if (m_mapTmp[n])
				{
					ErasePai(x,y);
					PutPai(x,y,p,ps);
				}
				else
				{
					PutPai(x,y,p);
				}
			}
		}
	}
	return -1;
}



POINT CMiniGameKushi::GetKushiZahyo(int x,int y)
{
	POINT pt;
	pt.x = m_printX + m_paiSize.cx * x;
	pt.y = m_printY + m_paiSize.cy * y;
	return pt;
}

/*
int CMiniGameKushi::SearchSlideOkPanel(int x,int y)
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

void CMiniGameKushi::SlidePanel(int n)
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



int CMiniGameKushi::GetOnBlockNumber(POINT pt)
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

void CMiniGameKushi::MakeHint(void)
{
	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
			m_mapTmp[n] = 0;
			int p = GetKushiPai(n);
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

BOOL CMiniGameKushi::CheckBottomSukima(void)
{
	BOOL flg = FALSE;

	for (int i=1;i<=17;i++)
	{
		int n = 8*20+i;
		int p = GetKushiPai(n);
		if (p == 0)
		{
			if (GetKushiPai(n+1) > 0)
			{
				flg = TRUE;
				break;
			}
		}
	}

	if (flg == FALSE) return FALSE;

	for (int j=1;j<=8;j++)
	{
		for (int i=1;i<=18;i++)
		{
			int n = j * 20 + i;
			int p = GetKushiPai(n);
			m_downed[n] = 0;
			m_downMax[n] = 0;

			if (p>0)
			{
				int down = 0;
				for (int ii=i-1;ii>=1;ii--)
				{
					int n2 = j*20+ii;
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

	return TRUE;
}


/*_*/

