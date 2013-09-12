
#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nnnUtilLib\myMouseStatus.h"

#include "allMiniGame.h"
#include "miniGameBase.h"

#include "miniGameDevil.h"

int CMiniGameDevil::m_slideOkTable[]=
{
	1,0,0,1, 2,0,0,1, 1,3,0,-1, 2,3,0,-1, 0,1,1,0, 0,2,1,0, 3,1,-1,0, 3,2,-1,0,
};


CMiniGameDevil::CMiniGameDevil(CAllMiniGame* lpAllMiniGame,int layoutParamKosuu,int* layoutParam) : CMiniGameBase(lpAllMiniGame,layoutParamKosuu,layoutParam)
{
	m_trumpPic = m_allMiniGame->GetCommonPic(0);
	m_trumpSize = m_allMiniGame->GetCommonPicSize(0);
}


CMiniGameDevil::~CMiniGameDevil()
{
	End();
}


void CMiniGameDevil::End(void)
{
}

int CMiniGameDevil::Init(void)
{
	for (int j=0;j<4;j++)
	{
		for (int i=0;i<4;i++)
		{
			m_map[j][i] = i+j*4;
		}
	}


	for (int i=0;i<13;i++)
	{
		int n = rand() % 8;
		SlidePanel(n);
	}
	m_clearFlag = FALSE;

	CAreaControl::SetNextAllPrint();
	m_lastClickN = -1;

	return -1;
}

int CMiniGameDevil::Calcu(void)
{
	if (m_clearFlag)
	{
		return -1;
	}

	m_lastClickN = -1;

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

	return -1;
}

int CMiniGameDevil::Print(void)
{
	if (m_clearFlag)
	{
		CAreaControl::SetNextAllPrint();
		CPicture* pic = m_pic1;
	//	if (m_map[0][0] == 1) pic = m_pic2;
		pic->Put(0,0,FALSE);
		return -1;
	}

	BOOL b = CAreaControl::CheckAllPrintMode();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int divX = screenSizeX / 4;
	int divY = screenSizeY / 4;

	int panel[4][4];
	int i,j;
	if (b)
	{
		for (j=0;j<4;j++)
		{
			for (i=0;i<4;i++)
			{
				panel[j][i] = 1;
			}
		}
	}
	else
	{
		if (m_lastClickN != -1)
		{
			int x = m_slideOkTable[m_lastClickN*4];
			int y = m_slideOkTable[m_lastClickN*4+1];
			int dx = m_slideOkTable[m_lastClickN*4+2];
			int dy = m_slideOkTable[m_lastClickN*4+3];

			for (i=0;i<4;i++)
			{
				panel[y][x] = 1;
				x += dx;
				y += dy;
			}
		}
	}



	for (j=0;j<4;j++)
	{
		int putY = divY * j;
		for (i=0;i<8;i++)
		{
			int putX = divX * i;

			if (panel[j][i])
			{
				CPicture* pic = m_pic1;
				int srcX = (m_map[j][i] % 4) * divX;
				int srcY = (m_map[j][i] / 4) * divY;

				pic->Blt(putX,putY,srcX,srcY,divX,divY,FALSE);
				CAreaControl::AddArea(putX,putY,divX,divY);
			}
		}
	}

	if (m_trumpPic != NULL)
	{
		int sizeX = m_trumpSize.cx;
		int sizeY = m_trumpSize.cy;
		int srcX = (rand() % 13)* sizeX;
		int srcY = (rand() % 4) * sizeY;
		POINT pt = m_mouseStatus->GetZahyo();
		int putX = pt.x;
		int putY = pt.y;
		m_trumpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}

	return -1;
}

int CMiniGameDevil::SearchSlideOkPanel(int x,int y)
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

void CMiniGameDevil::SlidePanel(int n)
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




/*_*/

