//
// effectsimplewipeMove.cpp					///移動タイプの共通クラスひながた。現時点ではshapeのコピーにすぎない
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectSimpleWipeCommon.h"
#include "effectSimpleWipeTokoroten.h"

#include "allSimpleWipe.h"


int CEffectSimpleWipeTokoroten::m_tokorotenHoukou[]=
{
	0,1, -1,0, 0,-1, 1,0
};

CEffectSimpleWipeTokoroten::CEffectSimpleWipeTokoroten(CAllSimpleWipe* allWipe,int direction) : CEffectSimpleWipeCommon(allWipe)
{
	m_256OkFlag = TRUE;
//	SetEffectHoukou(houkou);
	m_direction = direction;
}


CEffectSimpleWipeTokoroten::~CEffectSimpleWipeTokoroten()
{
	End();
}

void CEffectSimpleWipeTokoroten::End(void)
{
}



void CEffectSimpleWipeTokoroten::Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax, POINT* lpStartPoint, POINT* lpEndPoint)
{
	if (ClipAndCheck(lpPicStart,lpPicEnd,count,countMax,lpStartPoint,lpEndPoint) == FALSE) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int houkouX = m_tokorotenHoukou[m_direction*2];
	int houkouY = m_tokorotenHoukou[m_direction*2+1];

	int putX1 = 0;
	int putY1 = 0;
	int putX2 = -screenSizeX * houkouX;
	int putY2 = -screenSizeY * houkouY;

	CPicture* src = m_startPic;
	CPicture* dst = m_endPic;

	int dv = m_countMax;
	if (dv<1) dv = 1;

	int c = m_count;
	if (c<0) c = 0;
	if (c>dv) c = dv;

	int deltaX = screenSizeX * houkouX;
	int deltaY = screenSizeY * houkouY;

	deltaX *= c;
	deltaX /= dv;
	deltaY *= c;
	deltaY /= dv;

	putX1 += deltaX;
	putY1 += deltaY;
	putX2 += deltaX;
	putY2 += deltaY;

	int srcX1 = 0;
	int srcY1 = 0;
	int srcX2 = 0;
	int srcY2 = 0;

	srcX1 += m_startPoint.x;
	srcY1 += m_startPoint.y;
	srcX2 += m_endPoint.x;
	srcY2 += m_endPoint.y;


	src->Blt(putX1,putY1,srcX1,srcY1,screenSizeX,screenSizeY,FALSE);
	dst->Blt(putX2,putY2,srcX2,srcY2,screenSizeX,screenSizeY,FALSE);
}




/*_*/

