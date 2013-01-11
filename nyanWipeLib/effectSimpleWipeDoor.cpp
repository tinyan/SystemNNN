//
// effectsimplewipeDoor.cpp					///移動タイプの共通クラスひながた。現時点ではshapeのコピーにすぎない
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeDoor.h"

#include "allSimpleWipe.h"

CEffectSimpleWipeDoor::CEffectSimpleWipeDoor(CAllSimpleWipe* allWipe,int inOut,int tateyoko) : CEffectSimpleWipeCommon(allWipe)
{
	m_256OkFlag = TRUE;
	m_tateyoko = tateyoko;
	SetEffectHoukou(inOut);
}


CEffectSimpleWipeDoor::~CEffectSimpleWipeDoor()
{
	End();
}

void CEffectSimpleWipeDoor::End(void)
{
}

/*
void CEffectSimpleWipeDoor::SetMoveType(int inOut,int houkou)
{
	m_houkou = houkou;
	m_inOut = inOut;
}
*/


void CEffectSimpleWipeDoor::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	if (m_effectHoukou == 1)
	{
		SwapPic();
		m_count = m_countMax - m_count;
		if (m_count<0) m_count = 0;
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();



	int dv = m_countMax;
	if (dv<1) dv = 1;


	int srcX0 = 0;
	int srcY0 = 0;
	int putX0 = 0;
	int putY0 = 0;
	int sizeX0 = screenSizeX;
	int sizeY0 = screenSizeY;

	int srcX1 = 0;
	int srcY1 = 0;
	int putX1 = 0;
	int putY1 = 0;
	int sizeX1 = screenSizeX;
	int sizeY1 = screenSizeY;
	
	int srcX2 = 0;
	int srcY2 = 0;
	int putX2 = 0;
	int putY2 = 0;
	int sizeX2 = screenSizeX;
	int sizeY2 = screenSizeY;


	if (m_tateyoko == 0)
	{
		sizeY1 = screenSizeY / 2;

		srcY2 = sizeY1;
		sizeY2 = screenSizeY - sizeY1;
		putY2 = srcY2;
	}
	else
	{
		sizeX1 = screenSizeX / 2;

		srcX2 = sizeX1;
		sizeX2 = screenSizeX - sizeX1;
		putX2 = srcX2;
	}

	int deltaX = screenSizeX / 2;
	int deltaY = screenSizeY / 2;

	int c = m_countMax - m_count;
//	if (m_effectHoukou == 1)
//	{
//		SwapPic();
//		c = m_countMax - m_count;
//		if (c<0) c = 0;
//	}

	deltaX *= c;
	deltaX /= dv;
	deltaY *= c;
	deltaY /= dv;

	if (m_tateyoko == 0)
	{
		putY1 -= deltaY;
		putY2 += deltaY;

		putY0 = screenSizeY / 2 - deltaY;
		sizeY0 = deltaY * 2;
		srcY0 = putY0;
	}
	else
	{
		putX1 -= deltaX;
		putX2 += deltaX;

		putX0 = screenSizeX / 2 - deltaX;
		sizeX0 = deltaX * 2;
		srcX0 = putX0;
	}

	srcX0 += m_startPoint.x;
	srcY0 += m_startPoint.y;
	
	srcX1 += m_endPoint.x;
	srcY1 += m_endPoint.y;
	
	srcX2 += m_endPoint.x;
	srcY2 += m_endPoint.y;


	if ((sizeX0>0) && (sizeY0>0))
	{
		m_startPic->Blt(putX0,putY0,srcX0,srcY0,sizeX0,sizeY0,FALSE);
	}

	if ((sizeX1>0) && (sizeY1>0))
	{
		m_endPic->Blt(putX1,putY1,srcX1,srcY1,sizeX1,sizeY1,FALSE);
	}

	if ((sizeX2>0) && (sizeY2>0))
	{
		m_endPic->Blt(putX2,putY2,srcX2,srcY2,sizeX2,sizeY2,FALSE);
	}
}




/*_*/

