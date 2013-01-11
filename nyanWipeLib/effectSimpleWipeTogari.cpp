//
// effectsimplewipeTogari.cpp
//

#include <windows.h>
#include <Math.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanlib\include\myGraphics.h"

#include "effectsimplewipecommon.h"
#include "effectsimplewipeShape.h"
#include "effectsimplewipeTogari.h"
#include "allSimpleWipe.h"


CEffectSimpleWipeTogari::CEffectSimpleWipeTogari(CAllSimpleWipe* allWipe,int houkou,BOOL gradFlag,int gradSize) : CEffectSimpleWipeShape(allWipe)
{
	SetEffectHoukou(houkou);
	SetGrad(gradFlag,gradSize);
}

CEffectSimpleWipeTogari::~CEffectSimpleWipeTogari()
{
	End();
}

void CEffectSimpleWipeTogari::End(void)
{
}


void CEffectSimpleWipeTogari::CalcuShapeWork(int count, int countMax)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	if (countMax<1) countMax = 1;
	if (count<0) count = 0;
	if (count>countMax) count = countMax;

	int naname = screenSizeY/2*2;
	int width = naname + screenSizeX;
	BOOL gradFlag = m_gradFlag;

	int startDelta = 0;

	if (gradFlag)
	{
		width += m_gradSize;
		startDelta = m_gradSize;
	}

	int* shapeWork = m_allSimpleWipe->GetShapeWork();

	if (shapeWork == NULL) return;
	if (m_shapeDivide == 0) return;

	int* sPtr = shapeWork;


	int gradDelta = 4;
	if (gradFlag)
	{
		if (m_gradSize > 0) gradDelta = 256 / m_gradSize;
	}

	int houkou = m_effectHoukou;

	int deltaX = (width * count) / countMax;

	for (int j=0;j<screenSizeY;j++)
	{
		int dx = j*2;
		if (j>=screenSizeY/2)
		{
			dx = (screenSizeY-j)*2;
		}

		int x;
		if (houkou == 0)
		{
			x = - naname + dx;
			x += deltaX;
		}
		else
		{
			x = 0 - dx;
			x += deltaX;
		}

		x -= startDelta;

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



