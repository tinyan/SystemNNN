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
#include "effectsimplewipeBeach.h"
#include "allSimpleWipe.h"


CEffectSimpleWipeBeach::CEffectSimpleWipeBeach(CAllSimpleWipe* allWipe,int houkou,BOOL gradFlag,int gradSize) : CEffectSimpleWipeShape(allWipe)
{
	SetEffectHoukou(houkou);
	SetGrad(gradFlag,gradSize);
}

CEffectSimpleWipeBeach::~CEffectSimpleWipeBeach()
{
	End();
}

void CEffectSimpleWipeBeach::End(void)
{
}


void CEffectSimpleWipeBeach::CalcuShapeWork(int count, int countMax)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	if (countMax<1) countMax = 1;
	if (count<0) count = 0;
	if (count>countMax) count = countMax;

	double r[3];
	int fay[3];
	int omega[3];
	int omega2[3];

	//çáåv15%
	r[0] = 8.0;
	r[1] = 5.0;
	r[2] = 2.0;

	fay[0] = 0;
	fay[1] = 70;
	fay[2] = 250;

	omega[0] = 2;
	omega[1] = 3;
	omega[2] = 7;

	omega2[0] = 35;
	omega2[1] = 53;
	omega2[2] = 21;

	for (int i=0;i<3;i++)
	{
		r[i] *= (double)screenSizeX;
		r[i] /= 100.0;

		int t2 = count * omega2[i];
		t2 %= 360;
		double th2 = (double)t2;
		th2 *= (3.14159 / 180.0);

		r[i] *= (sin(th2)+1.5) / 2.5;
	}

	double x0 = (count * screenSizeX * 13) / (10*countMax);
	x0 -= (screenSizeX * 3) / 20;


//	int* shapeWork = CEffectSimpleWipe::m_shapeWork;
//	int* shapeWork = NULL;
	int* shapeWork = m_allSimpleWipe->GetShapeWork();

	///




	if (shapeWork == NULL) return;
	if (m_shapeDivide == 0) return;

	int* sPtr = shapeWork;

	BOOL gradFlag = m_gradFlag;

	int gradDelta = 4;
	if (gradFlag)
	{
		if (m_gradSize > 0) gradDelta = 256 / m_gradSize;
	}

	for (int j=0;j<screenSizeY;j++)
	{
		double xx = 0.0;
		for (int i=0;i<3;i++)
		{
			int t = fay[i] + count * 17 + omega[i] * j;
			t %= 360;
			double th = (double)t;
			th *= (3.14159/180.0);

			xx += (r[i] * sin(th) * 0.5);
		}

		xx += x0;
		int x = (int)(xx + 0.5);


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



