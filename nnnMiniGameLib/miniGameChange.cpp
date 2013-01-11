
#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nnnUtilLib\myMouseStatus.h"




#include "allMiniGame.h"
#include "miniGameBase.h"

#include "miniGameChange.h"

CMiniGameChange::CMiniGameChange(CAllMiniGame* lpAllMiniGame) : CMiniGameBase(lpAllMiniGame)
{
}


CMiniGameChange::~CMiniGameChange()
{
	End();
}


void CMiniGameChange::End(void)
{
}

int CMiniGameChange::Init(void)
{
	for (int j=0;j<4;j++)
	{
		for (int i=0;i<4;i++)
		{
			m_map[j][i] = j*4+i;
		}
	}

	for (int i=0;i<16;i++)
	{
		int x1 = i % 4;
		int y1 = i / 4;
		int x2 = rand() % 4;
		int y2 = rand() % 4;
		int d = m_map[y1][x1];
		m_map[y1][x1] = m_map[y2][x2];
		m_map[y2][x2] = d;
	}
	m_clearFlag = FALSE;

	CAreaControl::SetNextAllPrint();

	m_catch = -1;

	return -1;
}

int CMiniGameChange::Calcu(void)
{
	if (m_clearFlag)
	{
		return -1;
	}

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
				m_allMiniGame->PlayClearSound();
			}
			else if (m_map[y][x] == y*4+x)
			{
				m_allMiniGame->PlayGoodSound();
			}
			else
			{
				m_allMiniGame->PlayClickSound();
			}
		}
	}

	return -1;
}

int CMiniGameChange::Print(void)
{
	CAreaControl::SetNextAllPrint();
	if (m_clearFlag)
	{
		m_pic1->Put(0,0,FALSE);
		return -1;
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int divX = screenSizeX / 4;
	int divY = screenSizeY / 4;

	for (int j=0;j<4;j++)
	{
		int putY = divY * j;
		for (int i=0;i<4;i++)
		{
			int putX = divX * i;

			int d = m_map[j][i];
			if (d != -1)
			{
				int srcX = (d % 4) * divX;
				int srcY = (d / 4) * divY;

				CPicture* pic = m_pic1;
				pic->Blt(putX,putY,srcX,srcY,divX,divY,FALSE);
			}
			else
			{
				CAllGeo::BoxFill(putX,putY,divX,divY,0,64,128);
			}
		}
	}

	if (m_catch != -1)
	{
		int srcX = (m_catch % 4) * divX;
		int srcY = (m_catch / 4) * divY;
		POINT pt = m_mouseStatus->GetZahyo();
		int putX = pt.x - divX / 2;
		int putY = pt.y - divY / 2;

		CPicture* pic = m_pic1;
		pic->TransLucentBlt0(putX,putY,srcX,srcY,divX,divY,50);
	}

	return -1;
}




/*_*/

