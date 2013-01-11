
#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nnnUtilLib\myMouseStatus.h"


#include "allMiniGame.h"
#include "miniGameBase.h"

#include "miniGameTrumpCommon.h"



CMiniGameTrumpCommon::CMiniGameTrumpCommon(CAllMiniGame* lpAllMiniGame) : CMiniGameBase(lpAllMiniGame)
{
	m_trumpPic = m_allMiniGame->GetCommonPic(0);
	m_trumpSize = m_allMiniGame->GetCommonPicSize(0);
	m_cardPicType = m_allMiniGame->GetPicType(0);
}


CMiniGameTrumpCommon::~CMiniGameTrumpCommon()
{
	End();
}


void CMiniGameTrumpCommon::End(void)
{
}

void CMiniGameTrumpCommon::EraseCard(int x,int y)
{
	int sizeX = m_trumpSize.cx;
	int sizeY = m_trumpSize.cy;
	m_pic1->Blt(x,y,x,y,sizeX,sizeY,FALSE);
	CAreaControl::AddArea(x,y,sizeX,sizeY);
}

void CMiniGameTrumpCommon::PutCard(int x,int y,int card,int trans,BOOL sel,BOOL chk)
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

POINT CMiniGameTrumpCommon::GetCardPic(int n)
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




/*_*/

