
#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nnnUtilLib\myMouseStatus.h"

#include "allMiniGame.h"
#include "miniGameBase.h"

#include "miniGamePuzzle9.h"

CMiniGamePuzzle9::CMiniGamePuzzle9(CAllMiniGame* lpAllMiniGame) : CMiniGameBase(lpAllMiniGame)
{
}


CMiniGamePuzzle9::~CMiniGamePuzzle9()
{
	End();
}


void CMiniGamePuzzle9::End(void)
{
}

int CMiniGamePuzzle9::Init(void)
{
	int i,j;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int divX = screenSizeX / 8;
	int divY = screenSizeY / 8;

	for (j=0;j<3;j++)
	{
		for (i=0;i<3;i++)
		{
			m_answer[j][i] = 0;
		}
	}

	for (j=0;j<3;j++)
	{
		for (i=0;i<3;i++)
		{
			int k = i+j*3;

			m_panel[k].flag = TRUE;
			m_panel[k].answer = k;
			m_panel[k].pic = 0;
			m_panel[k].srcX = divX/2 + divX*(i*2+1);
			m_panel[k].srcY = divY/2 + divY*(j*2+1);
			SetStartPanelZahyo(k);
		}
	}

	for (i=0;i<9;i++)
	{
		int k = 9 + i;
		m_panel[k].flag = TRUE;
		m_panel[k].answer = -1;
		m_panel[k].pic = 1;
		SetPanelStartBad(k);
		SetStartPanelZahyo(k);
	}

	m_clearFlag = FALSE;

	CAreaControl::SetNextAllPrint();

	m_catch = -1;

	return -1;
}

int CMiniGamePuzzle9::Calcu(void)
{

//	if (m_mouseStatus->CheckClick(1)) return 0;

	if (m_clearFlag)
	{
//@@@		CalcuCongra();
		return -1;
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int divX = screenSizeX / 8;
	int divY = screenSizeY / 8;

	int leftLimit = -divX*2;
	int rightLimit = screenSizeX+divX;
	int upLimit = -divY*2;
	int downLimit = screenSizeY+divY;


	for (int i=0;i<18;i++)
	{
		if (m_panel[i].flag)
		{
			int x = m_panel[i].x + m_panel[i].speedX;
			int y = m_panel[i].y + m_panel[i].speedY;

			if ((x<leftLimit) || (x>rightLimit) || (y<upLimit) || (y>downLimit))
			{
				SetStartPanelZahyo(i);
				if (i>9)
				{
					SetPanelStartBad(i);
				}
				else if (m_panel[i].answer == -1)
				{
					SetPanelStartBad(i);
				}
			}
			else
			{
				m_panel[i].x = x;
				m_panel[i].y = y;
			}
		}
	}

	POINT pt = m_mouseStatus->GetZahyo();

	if (m_catch == -1)
	{
		if (m_mouseStatus->CheckClick())
		{
			int panel = SearchMovingPanel(pt);
			if (panel != -1)
			{
				m_panel[panel].flag = FALSE;
				m_catch = panel;
				m_allMiniGame->PlayClickSound();
				return -1;
			}
		}
		return -1;
	}


	if (m_mouseStatus->CheckClick())
	{
		int area = GetAreaNumber(pt);
		if (area == -1)
		{
			ReleasePanel();
			return -1;
		}

		int xx = area % 3;
		int yy = area / 3;
		if (m_answer[yy][xx])
		{
			ReleasePanel();
			return -1;
		}

		if (m_panel[m_catch].answer == area)
		{
			m_panel[m_catch].flag = TRUE;
			m_answer[yy][xx] = 1;
			m_panel[m_catch].answer = -1;
			SetPanelStartBad(m_catch);
			SetStartPanelZahyo(m_catch);

			if (CheckAllSet())
			{
				m_allMiniGame->PlayClearSound();
				m_clearFlag = TRUE;
			}
			else
			{
				m_allMiniGame->PlayGoodSound();
			}

			m_catch = -1;

			return -1;
		}
		else
		{
			m_allMiniGame->PlayBadSound();
			ReleasePanel();
			return -1;
		}

	}

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
				int d = m_map[y][x];
				m_map[y][x] = m_catch;
				m_catch = d;

				if (m_catch == -1)
				{
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
				PlayClearSound();
			}
			else if (m_map[y][x] == y*4+x)
			{
				PlayGoodSound();
			}
			else
			{
				PlayClickSound();
			}
		}
	}
*/

	return -1;
}

int CMiniGamePuzzle9::Print(void)
{
	CAreaControl::SetNextAllPrint();
	if (m_clearFlag)
	{
		m_pic1->Put(0,0,FALSE);
		return -1;
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int divX = screenSizeX / 8;
	int divY = screenSizeY / 8;

	m_pic1->Put(0,0,FALSE);
	int i,j;
	for (j=0;j<3;j++)
	{
		int putY = divY / 2 + divY * (j*2+1);
		for (i=0;i<3;i++)
		{
			int putX = divX / 2 + divX * (i*2+1);

			if (m_answer[j][i] == 0)
			{
				CAllGeo::TransBoxFill(putX,putY,divX,divY,32,64,128,80);
			}
		}
	}


	for (i=0;i<18;i++)
	{
		if (m_panel[i].flag)
		{
			int x = m_panel[i].x;
			int y = m_panel[i].y;
			int srcX = m_panel[i].srcX;
			int srcY = m_panel[i].srcY;
			CPicture* pic = m_pic1;
			if (m_panel[i].pic != 0)
			{
				pic = m_pic2;
			}
			pic->TransLucentBlt0(x,y,srcX,srcY,divX,divY,50);
		}
	}

	if (m_catch != -1)
	{
		POINT pt = m_mouseStatus->GetZahyo();

		int x = pt.x - divX / 2;
		int y = pt.y - divY / 2;

		int srcX = m_panel[m_catch].srcX;
		int srcY = m_panel[m_catch].srcY;
		CPicture* pic = m_pic1;
		if (m_panel[m_catch].pic != 0)
		{
			pic = m_pic2;
		}

		pic->Blt(x,y,srcX,srcY,divX,divY,FALSE);
	}

	return -1;
}



void CMiniGamePuzzle9::SetPanelStartBad(int n)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int divX = screenSizeX / 8;
	int divY = screenSizeY / 8;

	int srcX = (rand() % 4)*2*divX + (divX/2);
	int srcY = (rand() % 4)*2*divY + (divY/2);

	m_panel[n].srcX = srcX;
	m_panel[n].srcY = srcY;
}


void CMiniGamePuzzle9::SetStartPanelZahyo(int n)
{
	int r = rand() % 4;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int divX = screenSizeX / 8;
	int divY = screenSizeY / 8;
	
	int x = (rand() % (screenSizeX+divX*2)) + divX;
	int y = (rand() % (screenSizeY+divY*2)) + divY;

	int speedX = ((rand() % 2)*2-1) * ((rand() % 7) + 3);
	int speedY = ((rand() % 2)*2-1) * ((rand() % 7) + 3);

	if (r == 0)
	{
		y = - divY;
		if (speedY<0) speedY *= -1;
	}
	else if (r == 1)
	{
		y = screenSizeY + divY;
		if (speedY>0) speedY *= -1;
	}
	else if (r == 2)
	{
		x = - divX;
		if (speedX<0) speedX *= -1;
	}
	else if (r == 3)
	{
		x = screenSizeX + divX;
		if (speedX>0) speedX *= -1;
	}

	m_panel[n].x = x;
	m_panel[n].y = y;
	m_panel[n].speedX = speedX;
	m_panel[n].speedY = speedY;

}


int CMiniGamePuzzle9::SearchMovingPanel(POINT pt)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int divX = screenSizeX / 8;
	int divY = screenSizeY / 8;

	for (int i=17;i>=0;i--)
	{
		if (m_panel[i].flag)
		{
			int x = pt.x - m_panel[i].x;
			int y = pt.y - m_panel[i].y;

			if ((x>=0) && (x<divX) && (y>=0) && (y<divY))
			{
				return i;
			}

		}
	}

	return -1;
}

int CMiniGamePuzzle9::GetAreaNumber(POINT pt)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int divX = screenSizeX / 8;
	int divY = screenSizeY / 8;

	int x = pt.x;
	int y = pt.y;
	
	x -= divX / 2;
	y -= divY / 2;
	if ((x<0) || (y<0)) return -1;

	int amariX = x % (divX*2);
	if (amariX < divX) return -1;
	int nx = x / (divX*2);
	if (nx>=3) return -1;

	int amariY = y % (divY*2);
	if (amariY < divY) return -1;
	int ny = y / (divY*2);
	if (ny>=3) return -1;

	return nx + ny*3;

}

BOOL CMiniGamePuzzle9::CheckAllSet(void)
{
	for (int j=0;j<3;j++)
	{
		for (int i=0;i<3;i++)
		{
			if (m_answer[j][i] == 0) return FALSE;
		}
	}
	return TRUE;
}

void CMiniGamePuzzle9::ReleasePanel(void)
{
	m_panel[m_catch].flag = TRUE;
	m_catch = -1;
}

/*_*/

