//
// effectsimplewipeMove.cpp					///移動タイプの共通クラスひながた。現時点ではshapeのコピーにすぎない
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeMove.h"

#include "allSimpleWipe.h"

CEffectSimpleWipeMove::CEffectSimpleWipeMove(CAllSimpleWipe* allWipe,int houkou,int direction) : CEffectSimpleWipeCommon(allWipe)
{
	m_256OkFlag = TRUE;
	SetEffectHoukou(houkou);
	m_direction = direction;
}


CEffectSimpleWipeMove::~CEffectSimpleWipeMove()
{
	End();
}

void CEffectSimpleWipeMove::End(void)
{
}



void CEffectSimpleWipeMove::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
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

	int deltaX = screenSizeX;
	int deltaY = screenSizeY;

	CPicture* src = m_startPic;
	CPicture* dst = m_endPic;

	int dv = m_countMax;
	if (dv<1) dv = 1;

	int c = dv - m_count;
	if (c<0) c = 0;
	if (c>dv) c = dv;

	deltaX *= c;
	deltaX /= dv;
	deltaY *= c;
	deltaY /= dv;


	if (m_direction == 0)
	{
		putY2 -= deltaY;
		putY1 = screenSizeY - deltaY;
		srcY1 = putY1;
		sizeY1 = deltaY;
	}
	else if (m_direction == 1)
	{
		putX2 += deltaX;
		sizeX1 = deltaX;
	}
	else if (m_direction == 2)
	{
		putY2 += deltaY;
		sizeY1 = deltaY;
	}
	else if (m_direction == 3)
	{
		putX2 -= deltaX;
		putX1 = screenSizeX - deltaX;
		srcX1 = putX1;
		sizeX1 = deltaX;
	}

	srcX1 += m_startPoint.x;
	srcY1 += m_startPoint.y;
	srcX2 += m_endPoint.x;
	srcY2 += m_endPoint.y;


	if ((sizeX1>0) && (sizeY1>0))
	{
		src->Blt(putX1,putY1,srcX1,srcY1,sizeX1,sizeY1,FALSE);
	}

	if ((sizeX2>0) && (sizeY2>0))
	{
		dst->Blt(putX2,putY2,srcX2,srcY2,sizeX2,sizeY2,FALSE);
	}
}




/*_*/

