
#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nnnUtilLib\myMouseStatus.h"



#include "allMiniGame.h"
#include "miniGameBase.h"

#include "miniGameCross.h"

CMiniGameCross::CMiniGameCross(CAllMiniGame* lpAllMiniGame) : CMiniGameBase(lpAllMiniGame)
{
}


CMiniGameCross::~CMiniGameCross()
{
	End();
}


void CMiniGameCross::End(void)
{
}

int CMiniGameCross::Init(void)
{
	for (int j=0;j<8;j++)
	{
		for (int i=0;i<8;i++)
		{
			m_map[j][i] = 0;
		}
	}

	for (int i=0;i<12;i++)
	{
		int x = rand() % 8;
		int y = rand() % 8;
		Reverse(x,y);
	}
	m_clearFlag = FALSE;

	CAreaControl::SetNextAllPrint();
	m_lastClickX = -1;
	m_lastClickY = -1;

	return -1;
}

int CMiniGameCross::Calcu(void)
{
	if (m_clearFlag)
	{
		return -1;
	}

	m_lastClickX = -2;
	m_lastClickY = -2;

	if (m_mouseStatus->CheckClick())
	{
		POINT pt = m_mouseStatus->GetZahyo();
		int screenSizeX = CMyGraphics::GetScreenSizeX();
		int screenSizeY = CMyGraphics::GetScreenSizeY();
		int x = pt.x;
		int y = pt.y;
		if ((x>=0) && (y>=0))
		{
			x /= (screenSizeX / 8);
			y /= (screenSizeY / 8);

			if ((x<8) && (y<8))
			{
				Reverse(x,y);
				int d = m_map[y][x];
				m_lastClickX = x;
				m_lastClickY = y;

				m_clearFlag = TRUE;
				for (int j=0;j<8;j++)
				{
					for (int i=0;i<8;i++)
					{
						if (d != m_map[j][i])
						{
							m_clearFlag = FALSE;
							break;
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

int CMiniGameCross::Print(void)
{
	if (m_clearFlag)
	{
		CAreaControl::SetNextAllPrint();
		CPicture* pic = m_pic1;
		if (m_map[0][0] == 1) pic = m_pic2;
		pic->Put(0,0,FALSE);
		return -1;
	}

	BOOL b = CAreaControl::CheckAllPrintMode();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int divX = screenSizeX / 8;
	int divY = screenSizeY / 8;

	for (int j=0;j<8;j++)
	{
		int putY = divY * j;

		int absY = m_lastClickY - j;
		if (absY<0) absY *= -1;

		for (int i=0;i<8;i++)
		{
			int putX = divX * i;

			int absX = m_lastClickX - i;
			if (absX<0) absX *= -1;


			if (b || ((absX<=1) && (absY<=1)))
			{
				CPicture* pic = m_pic1;
				if (m_map[j][i] == 1) pic = m_pic2;

				pic->Blt(putX,putY,putX,putY,divX,divY,FALSE);
				CAreaControl::AddArea(putX,putY,divX,divY);
			}
		}
	}

	return -1;
}

void CMiniGameCross::Reverse(int x,int y)
{
	ReverseSub(x,y);
	ReverseSub(x,y-1);
	ReverseSub(x,y+1);
	ReverseSub(x-1,y);
	ReverseSub(x+1,y);
}

void CMiniGameCross::ReverseSub(int x,int y)
{
	if ((x>=0) && (x<8) && (y>=0) && (y<8))
	{
		int d = m_map[y][x];
		d++;
		d %= 2;
		m_map[y][x] = d;
	}
}



/*_*/

