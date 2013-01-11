//
// effectsimplewipecircle.cpp
//

#include <windows.h>
#include <Math.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanlib\include\myGraphics.h"

#include "effectsimplewipecommon.h"
#include "effectsimplewipeShape.h"
#include "effectsimplewipeCircle.h"
#include "allSimpleWipe.h"


CEffectSimpleWipeCircle::CEffectSimpleWipeCircle(CAllSimpleWipe* allWipe,int houkou) : CEffectSimpleWipeShape(allWipe)
{
	SetMaxDivide(4);
	SetEffectHoukou(houkou);
}

CEffectSimpleWipeCircle::~CEffectSimpleWipeCircle()
{
	End();
}

void CEffectSimpleWipeCircle::End(void)
{
}

void CEffectSimpleWipeCircle::CalcuShapeWork(int count, int countMax)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (countMax<1) countMax = 1;
	if (count>countMax) count = countMax;

	int rr = int(sqrt((double)((screenSizeX/2)*(screenSizeX/2) + (screenSizeY/2)*(screenSizeY/2))) + 1);
	int r;
	
//	if (m_effectHoukou == 0)
//	{
		r = (count * rr) / countMax;
//	}
//	else	// houkou == 1
//	{
//		r = ((countMax - count) * rr) / countMax;
//	}

	int* rx = m_allSimpleWipe->GetShapeWork();

//	int centerX = screenSizeX / 2;
	int centerY = screenSizeY / 2;


	for (int i=0;i<screenSizeY;i++)
	{
		int y = i - centerY;
		int x2 = r*r - y*y;
		if (x2<=0)
		{
			rx[i*4] = screenSizeX;
			rx[i*4+1] = 0;
			rx[i*4+2] = 0;
			rx[i*4+3] = 0;
		}
		else
		{
			int xx = (int)(sqrt((double)x2) + 0.5);
			if (xx >= screenSizeX / 2)
			{
				rx[i*4] = 0;
				rx[i*4+1] = screenSizeX;
				rx[i*4+2] = 0;
				rx[i*4+3] = 0;
			}
			else
			{
				rx[i*4] = screenSizeX/2 - xx;
				rx[i*4+1] = xx*2;
				rx[i*4+2] = screenSizeX/2 - xx;
				rx[i*4+3] = 0;
			}
		}
	}
}



