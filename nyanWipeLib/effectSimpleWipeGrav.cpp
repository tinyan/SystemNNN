//
// effectsimplewipeGrav.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeGrav.h"

#include "allSimpleWipe.h"


CEffectSimpleWipeGrav::CEffectSimpleWipeGrav(CAllSimpleWipe* allWipe,int omoteura) : CEffectSimpleWipeCommon(allWipe)
{
	m_256OkFlag = TRUE;
	m_omoteura = omoteura;
}

CEffectSimpleWipeGrav::~CEffectSimpleWipeGrav()
{
	End();
}

void CEffectSimpleWipeGrav::End(void)
{
}




void CEffectSimpleWipeGrav::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

//	int c = m_count;
	int dv = m_countMax;
	if (dv<0) dv = 1;


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

	int deltaY = screenSizeY;

	CPicture* src = m_startPic;
	CPicture* dst = m_endPic;


//‚±‚±‚Åd—ÍŒvŽZ


	int t1 = (countMax * 9 ) / 17;
	if (t1<1) t1 = 1;
	int t2 = (countMax * 6 ) / 17;
	if (t2<1) t2 = 1;
	int t3 = countMax - t1 - t2;
	if (t3<0) t3 = 0;


	double g = (double)(2.0*screenSizeY);
	g /= (double)(t1*t1);

	double v1 = (g * t1);
	double v2 = v1 / 3.0;
	double v3 = v2 / 3.0;


	if (count < t1)
	{
		double t = (double)count;
		t /= (double)(t1);

		double d = (double)screenSizeY;
		d *= (1.0 - t*t);
		deltaY = (int)(d+0.5);
	}
	else if (count<t1+t2)
	{
		double t = (double)(count - t1);
		double d = v2 * t - g * t * t / 2.0;
		deltaY = (int)(d+0.5);
	}
	else if (count<t1+t2+t3)
	{
		double t = (double)(count - t1 - t2);
		double d = v3 * t - g * t * t / 2.0;
		deltaY = (int)(d+0.5);
	}
	else
	{
		deltaY = 0;
	}

	if (deltaY<0) deltaY = 0;


	if (m_omoteura == 0)
	{
		putY2 -= deltaY;
		putY1 = screenSizeY - deltaY;
		srcY1 = putY1;
		sizeY1 = deltaY;
	}
	else
	{
		putY1 = screenSizeY - deltaY;
		sizeY2 = screenSizeY - deltaY;
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

