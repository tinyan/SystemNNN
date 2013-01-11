//
// effectsimplewipeCenter.cpp					///移動タイプの共通クラスひながた。現時点ではshapeのコピーにすぎない
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeCenter.h"

#include "allSimpleWipe.h"

CEffectSimpleWipeCenter::CEffectSimpleWipeCenter(CAllSimpleWipe* allWipe,int houkou,int transFlag) : CEffectSimpleWipeCommon(allWipe)
{
	m_transFlag = transFlag;
	SetEffectHoukou(houkou);
}


CEffectSimpleWipeCenter::~CEffectSimpleWipeCenter()
{
	End();
}

void CEffectSimpleWipeCenter::End(void)
{
}

/*
void CEffectSimpleWipeCenter::SetMoveType(int inOut,int houkou)
{
	m_houkou = houkou;
	m_inOut = inOut;
}
*/


void CEffectSimpleWipeCenter::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int c = m_count;

	if (m_effectHoukou == 1)
	{
		SwapPic();
		c = m_countMax - c;
		if (c<0) c = 0;
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int dv = m_countMax;
	if (dv<1) dv = 1;

	if (c<=0)
	{
		m_startPic->Blt(0,0,m_startPoint.x,m_startPoint.y,screenSizeX,screenSizeY,FALSE);
		return;
	}

	if (c>=dv)
	{
		m_endPic->Blt(0,0,m_endPoint.x,m_endPoint.y,screenSizeX,screenSizeY,FALSE);
		return;
	}

	int areaSizeX = (screenSizeX * c) / dv;
	int areaSizeY = (screenSizeY * c) / dv;

	int x1 = screenSizeX/2 - areaSizeX/2;
	int y1 = screenSizeY/2 - areaSizeY/2;
	int x2 = screenSizeX/2 + areaSizeX/2;
	int y2 = screenSizeY/2 + areaSizeY/2;


	if (x1<0) x1 = 0;
	if (y1<0) y1 = 0;
	if (x2>screenSizeX) x2 = screenSizeX;
	if (y2>screenSizeY) y2 = screenSizeY;

	int sizeX = x2 - x1;
	int sizeY = y2 - y1;

	int startX = m_startPoint.x;
	int startY = m_startPoint.y;

	if (m_transFlag == 0)
	{
		m_startPic->Blt(0,0,startX,startY,screenSizeX,y1,FALSE);
		m_startPic->Blt(0,y2,startX,startY+y2,screenSizeX,screenSizeY-y2,FALSE);
		m_startPic->Blt(0,y1,startX,startY+y1,x1,y2-y1,FALSE);
		m_startPic->Blt(x2,y1,startX+x2,startY+y1,screenSizeX-x2,y2-y1,FALSE);
	}
	else
	{
		m_startPic->Blt(0,0,startX,startY,screenSizeX,screenSizeY,FALSE);
	}

	if (sizeX<=0) return;
	if (sizeY<=0) return;

	if (m_transFlag == 0)
	{
		m_endPic->StretchBlt1(x1,y1,sizeX,sizeY,m_startPoint.x,m_startPoint.y,screenSizeX,screenSizeY,100,FALSE);
	}
	else
	{
		int ps = (c * 100) / dv;
		m_endPic->StretchBlt1(x1,y1,sizeX,sizeY,m_startPoint.x,m_startPoint.y,screenSizeX,screenSizeY,ps,TRUE);
	}
}




/*_*/

