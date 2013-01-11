//
// effectsimplewipeBeach.cpp
//

#include <windows.h>
#include <Math.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanlib\include\myGraphics.h"

#include "effectsimplewipecommon.h"
#include "effectsimplewipeShape.h"
#include "effectsimplewipeNaname.h"
#include "allSimpleWipe.h"


CEffectSimpleWipeNaname::CEffectSimpleWipeNaname(CAllSimpleWipe* allWipe,int houkou,BOOL gradFlag,int gradSize) : CEffectSimpleWipeShape(allWipe)
{
	SetEffectHoukou(houkou / 2);
	m_nanameHoukou = houkou;
	SetGrad(gradFlag,gradSize);
}

CEffectSimpleWipeNaname::~CEffectSimpleWipeNaname()
{
	End();
}

void CEffectSimpleWipeNaname::End(void)
{
}


void CEffectSimpleWipeNaname::CalcuShapeWork(int count, int countMax)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	if (countMax<1) countMax = 1;
	if (count<0) count = 0;
	if (count>countMax) count = countMax;


	int* shapeWork = m_allSimpleWipe->GetShapeWork();


	if (shapeWork == NULL) return;
	if (m_shapeDivide == 0) return;

	int* sPtr = shapeWork;

	BOOL gradFlag = m_gradFlag;

	int gradDelta = 4;
	if (gradFlag)
	{
		if (m_gradSize > 0) gradDelta = 256 / m_gradSize;
	}

	int gradSize = m_gradSize;

	int ml = gradSize + screenSizeX + screenSizeY;

	int naname = m_nanameHoukou;

	for (int j=0;j<screenSizeY;j++)
	{
		int x = 0;

		if (naname == 0)
		{
			x = -gradSize - j + (count * ml) / countMax;
		}
		else if (naname == 1)
		{
			x = -gradSize + j - screenSizeY + (count * ml) / countMax;
		}
		else if (naname == 2)
		{
//			x = screenSizeX + j - (count*ml) / countMax;
			x = -gradSize + j -screenSizeY + (count * ml) / countMax;
		}
		else if (naname == 3)
		{
//			x = screenSizeX - j +screenSizeY - (count*ml) / countMax;
			x = -gradSize - j + (count * ml) / countMax;
		}





		if (gradFlag == FALSE)
		{
			if (x<0) x = 0;
			if (x>screenSizeX) x = screenSizeX;

			*sPtr = x;
			sPtr++;
		}
		else
		{
			int gradStart = 256;
			if (x<0)
			{
				gradStart += x*gradDelta;
			}

			int leftSize = x;
			if (leftSize<0) leftSize = 0;
			if (leftSize > screenSizeX) leftSize = screenSizeX;

			int leftPoint = x;
			int rightPoint = x + m_gradSize;
			if (leftPoint < 0) leftPoint = 0;
			if (rightPoint < 0) rightPoint = 0;
			if (leftPoint > screenSizeX) leftPoint = screenSizeX;
			if (rightPoint > screenSizeX) rightPoint = screenSizeX;

			int gradSize = rightPoint - leftPoint;
			if (gradSize<0) gradSize = 0;

			int rightSize = screenSizeX - rightPoint;
			if (rightSize<0) rightSize = 0;

			*sPtr = leftSize;
			sPtr++;
			*sPtr = gradSize;
			sPtr++;
			*sPtr = gradStart;
			sPtr++;
			*sPtr = rightSize;
			sPtr++;
		}
	}
}



