
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



CMiniGameMahjongCommon::CMiniGameMahjongCommon(CAllMiniGame* lpAllMiniGame) : CMiniGameBase(lpAllMiniGame)
{
	m_paiPic = m_allMiniGame->GetCommonPic(1);
	m_paiSize = m_allMiniGame->GetCommonPicSize(1);

	m_paiSrcZahyo = NULL;

	InitPaiSrcZahyo();
	m_hintPrintX = m_paiSize.cx;
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	m_hintPrintY = screenSizeY - m_paiSize.cy - 16;
}


CMiniGameMahjongCommon::~CMiniGameMahjongCommon()
{
	End();
}


void CMiniGameMahjongCommon::End(void)
{
	DELETEARRAY(m_paiSrcZahyo);
}

void CMiniGameMahjongCommon::ErasePai(int x,int y)
{
	int sizeX = m_paiSize.cx;
	int sizeY = m_paiSize.cy;
	m_pic1->Blt(x,y,x,y,sizeX,sizeY,FALSE);
	CAreaControl::AddArea(x,y,sizeX,sizeY);
}

void CMiniGameMahjongCommon::PutPai(int x,int y,int pai,int trans,BOOL sel,BOOL chk)
{
	if (m_paiPic == NULL) return;

	int sizeX = m_paiSize.cx;
	int sizeY = m_paiSize.cy;
	CAreaControl::AddArea(x,y,sizeX,sizeY);

	POINT src = GetPaiPic(pai);

	if (trans == 100)
	{
		m_paiPic->Blt(x,y,src.x,src.y,sizeX,sizeY,TRUE);
	}
	else
	{
		m_paiPic->TransLucentBlt3(x,y,src.x,src.y,sizeX,sizeY,trans);
	}

	if (sel)
	{
		CAllGeo::TransBoxFill(x,y,sizeX,sizeY,0,128,255,60);
//		src = GetCardPic(56);
//		m_trumpPic->Blt(x,y,src.x,src.y,sizeX,sizeY,TRUE);
	}

	if (chk)
	{
		CAllGeo::TransBoxFill(x,y,sizeX,sizeY,64,255,192,50);
//		src = GetCardPic(57);
//		m_trumpPic->Blt(x,y,src.x,src.y,sizeX,sizeY,TRUE);
	}
}

POINT CMiniGameMahjongCommon::GetPaiPic(int n)
{
	if (n == -1)
	{
		return m_paiSrcZahyo[0];//ura
	}

	if (n == -2)
	{
		return m_paiSrcZahyo[1];//hint pai
	}

	return m_paiSrcZahyo[n-1+4];
}



void CMiniGameMahjongCommon::InitPaiSrcZahyo(void)
{
	m_paiSrcZahyo = new POINT[256];

	int sizeX = m_paiSize.cx;
	int sizeY = m_paiSize.cy;

	for (int i=0;i<255;i++)
	{
		m_paiSrcZahyo[i].x = sizeX * 8;
		m_paiSrcZahyo[i].y = sizeY * 6;
	}

	for (int i=0;i<144;i++)
	{

		int n1 = i / 4;
		int n2 = i % 4;

		POINT pt;

		//1-9 1-9 1-9
		if (n1 < 27)
		{
			int n3 = n1 / 9;
			int n4 = n1 % 9;
			if (((n4 == 2) || (n4 == 4)) && (n2 == 3))
			{
				int n5 = n3 * 2;
				if (n4 == 4) n5 += 1;
				pt.x = n5 * sizeX;
				pt.y = 5 * sizeY;
			}
			else
			{
				pt.x = n4 * sizeX;
				pt.y = n3 * sizeY;
			}
		}
		else if (n1 < 34)//eswn_hc
		{
			pt.x = (n1 - 27) * sizeX;;
			pt.y = 3 * sizeY;
		}
		else if (n1 < 36)//season,flower
		{
			pt.x = (i - 34*4) * sizeX;;
			pt.y = 4 * sizeY;
		}
		else
		{
			pt.x = 0;
			pt.y = 0;
		}

		m_paiSrcZahyo[i+4] = pt;
	}

	//ura ? ? ?
	m_paiSrcZahyo[0].x = 0;
	m_paiSrcZahyo[0].y = 6*sizeY;

	//hint
	m_paiSrcZahyo[1].x = 8*sizeX;
	m_paiSrcZahyo[1].y = 6*sizeY;

}

void CMiniGameMahjongCommon::PrintHaveHint(void)
{
	if (m_haveHint > 0)
	{
		int sizeX = m_paiSize.cx;
		int sizeY = m_paiSize.cy;

		int x = m_hintPrintX;
		int y = m_hintPrintY;

		for (int i=0;i<m_haveHint;i++)
		{
			PutPai(x+i*sizeX,y,-2);
		}

		CAreaControl::AddArea(x,y,sizeX*m_haveHint,sizeY);
	}
}


BOOL CMiniGameMahjongCommon::CheckOnHint(POINT pt)
{
	int dx = pt.x - m_hintPrintX;
	int dy = pt.y - m_hintPrintY;
	int sizeX = m_paiSize.cx * m_haveHint;
	int sizeY = m_paiSize.cx;
	if ((dx>=0) && (dx<sizeX) && (dy>=0) && (dy<sizeY))
	{
		return TRUE;
	}

	return FALSE;
}

/*_*/

