//
// effectsimplewipeGaza.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectsimplewipecommon.h"
#include "effectsimplewipeShape.h"
#include "effectsimplewipeGaza.h"
#include "allSimpleWipe.h"


CEffectSimpleWipeGaza::CEffectSimpleWipeGaza(CAllSimpleWipe* allWipe,int gazaType,BOOL gradFlag,int gradSize) : CEffectSimpleWipeShape(allWipe)
{
	SetEffectHoukou(gazaType);
	SetGrad(gradFlag,gradSize);
//	m_houkou = 0;
}

CEffectSimpleWipeGaza::~CEffectSimpleWipeGaza()
{
	End();
}

void CEffectSimpleWipeGaza::End(void)
{
}



void CEffectSimpleWipeGaza::CalcuShapeWork(int count, int countMax)
{
//	int c = count;
	int dv = countMax;
	if (dv<1) dv = 1;

//	if (m_effectHoukou == 1)
//	{
//		c = countMax - count;
//		if (c<0) c = 0;
//	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int* gazaTable = m_allSimpleWipe->GetShapeWork();
	int* rndTable = m_allSimpleWipe->GetRandomTableY();

	BOOL gradFlag = m_gradFlag;

	int gradDelta = 4;
	if (gradFlag)
	{
		if (m_gradSize > 0) gradDelta = 256 / m_gradSize;
	}

	//make data
	for (int i=0;i<screenSizeY;i++)
	{
		int startZahyo = -(((*rndTable) * screenSizeX) / (1*32768));
		rndTable++;
		int endZahyo = screenSizeX + ((*rndTable) * screenSizeX) / (2*32768);
		rndTable++;

		if (gradFlag)
		{
			startZahyo -= m_gradSize;
		}

		int d = startZahyo + ((endZahyo - startZahyo) * count) / countMax;


		if (gradFlag == FALSE)
		{
			if (d<0) d = 0;
			if (d>screenSizeX) d = screenSizeX;

//			if (m_houkou == 1) d = screenSizeX - d;

			gazaTable[i] = d;
		}
		else
		{
			int gradStart = 256;
			if (d<0)
			{
				gradStart += d*gradDelta;
			}

			int leftSize = d;
			if (leftSize<0) leftSize = 0;
			if (leftSize > screenSizeX) leftSize = screenSizeX;

			int leftPoint = d;
			int rightPoint = d + m_gradSize;
			if (leftPoint < 0) leftPoint = 0;
			if (rightPoint < 0) rightPoint = 0;
			if (leftPoint > screenSizeX) leftPoint = screenSizeX;
			if (rightPoint > screenSizeX) rightPoint = screenSizeX;

			int gradSize = rightPoint - leftPoint;
			if (gradSize<0) gradSize = 0;

			int rightSize = screenSizeX - rightPoint;
			if (rightSize<0) rightSize = 0;

			gazaTable[i*4] = leftSize;
			gazaTable[i*4+1] = gradSize;
			gazaTable[i*4+2] = gradStart;
			gazaTable[i*4+3] = rightSize;
		}
	}
}






/*_*/

