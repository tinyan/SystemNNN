//
// effectsimplewipeWTogari.cpp
//

#include <windows.h>
#include <Math.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanlib\include\myGraphics.h"

#include "effectsimplewipecommon.h"
#include "effectsimplewipeShape.h"
#include "effectsimplewipeWTogari.h"
#include "allSimpleWipe.h"


CEffectSimpleWipeWTogari::CEffectSimpleWipeWTogari(CAllSimpleWipe* allWipe,int houkou) : CEffectSimpleWipeShape(allWipe)
{
	SetMaxDivide(4);
	SetEffectHoukou(houkou);
}

CEffectSimpleWipeWTogari::~CEffectSimpleWipeWTogari()
{
	End();
}

void CEffectSimpleWipeWTogari::End(void)
{
}

void CEffectSimpleWipeWTogari::CalcuShapeWork(int count, int countMax)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (countMax<1) countMax = 1;
	if (count>countMax) count = countMax;


	int naname = screenSizeY / 2;
	int width = screenSizeX / 2 + naname;

	int deltaX = (width * count) / countMax;

	int* rx = m_allSimpleWipe->GetShapeWork();


	for (int i=0;i<screenSizeY;i++)
	{
		int dx = i;
		if (i>=screenSizeY/2)
		{
			dx = screenSizeY-i;
		}

		int x1 = 0 - naname + dx;
		x1 += deltaX;

		int x2 = screenSizeX + naname - dx;
		x2 -= deltaX;

		if (x1 >= x2)
		{
			rx[i*4+0] = 0;
			rx[i*4+1] = screenSizeX;
			rx[i*4+2] = 0;
			rx[i*4+3] = 0;
		}
		else
		{
			if (x1<0) x1 = 0;
			if (x2>screenSizeX) x2 = screenSizeX;

			int centerSize = x2 - x1;

			rx[i*4+0] = 0;
			rx[i*4+1] = x1;
			rx[i*4+2] = centerSize;
			rx[i*4+3] = screenSizeX-x2;
		}
	}
}



