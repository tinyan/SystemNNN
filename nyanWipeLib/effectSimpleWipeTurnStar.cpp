//
// effectsimplewipeTurnStar.cpp
//

#include <windows.h>
#include <Math.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectsimplewipecommon.h"
#include "effectsimplewipeShape.h"
#include "effectsimplewipeTurnStar.h"
#include "allSimpleWipe.h"


CEffectSimpleWipeTurnStar::CEffectSimpleWipeTurnStar(CAllSimpleWipe* allWipe,int houkou,int speed) : CEffectSimpleWipeShape(allWipe)
{
	SetMaxDivide(6);
	SetEffectHoukou(houkou);
	m_turnSpeed = speed;
}

CEffectSimpleWipeTurnStar::~CEffectSimpleWipeTurnStar()
{
	End();
}

void CEffectSimpleWipeTurnStar::End(void)
{
}


void CEffectSimpleWipeTurnStar::CalcuShapeWork(int count, int countMax)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

///	if (m_effectHoukou == 1)
//	{
//		count = countMax - count;
//	}

	if (countMax<1) countMax = 1;
	if (count<0) count = 0;
	if (count>countMax) count = countMax;

	double r = (double)screenSizeX;
	r *= 1.8;
	r *= count;
	r /= countMax;
	double r2 = r * (3.0 - sqrt(5.0)) / 2.0;


//	int* shapeWork = CEffectSimpleWipe::m_shapeWork;
	int* shapeWork = m_allSimpleWipe->GetShapeWork();

	if (shapeWork == NULL) return;
	if (m_shapeDivide == 0) return;

	int* sPtr = shapeWork;

	for (int j=0;j<screenSizeY;j++)
	{
		*sPtr = 0;	//no shape
		sPtr+=6;
	}


	int th0 = count * 360*2;
	if (m_turnSpeed == 1)
	{
		th0 = count * 72*3;
	}

	th0 /= m_countMax;

	th0 %= (360 / 5);


	int centerX = screenSizeX / 2;
	int centerY = screenSizeY / 2;


	int outerX[5];
	int outerY[5];
	int innerX[5];
	int innerY[5];

	for (int i=0;i<5;i++)
	{
		int t = (th0 + 180 + 18 + i * 72) % 360;
		double th = (double)t;
		int t2 = (th0 + 180 + 18 + 36 + i * 72) % 360;
		double th2 = (double)t2;

		th *= (3.14159 / 180.0);
		th2 *= (3.14159 / 180.0);

		outerX[i] = (int)(centerX + r * cos(th) + 0.5);
		outerY[i] = (int)(centerY + r * sin(th) + 0.5);

		innerX[i] = (int)(centerX + r2 * cos(th2) + 0.5);
		innerY[i] = (int)(centerY + r2 * sin(th2) + 0.5);
	}

	AddLeftRightDot(0,outerX[0],outerY[0],innerX[4],innerY[4]);
	AddLeftRightDot(1,outerX[0],outerY[0],innerX[0],innerY[0]);

	AddLeftRightDot(0,innerX[4],innerY[4],outerX[4],outerY[4]);
	AddLeftRightDot(1,innerX[3],innerY[3],outerX[4],outerY[4]);

	AddLeftRightDot(0,outerX[1],outerY[1],innerX[0],innerY[0]);
	AddLeftRightDot(1,outerX[1],outerY[1],innerX[1],innerY[1]);

	AddLeftRightDot(0,innerX[3],innerY[3],outerX[3],outerY[3]);
	AddLeftRightDot(1,innerX[2],innerY[2],outerX[3],outerY[3]);

	AddLeftRightDot(1,outerX[2],outerY[2],innerX[2],innerY[2]);
	AddLeftRightDot(1,innerX[1],innerY[1],outerX[2],outerY[2]);


	sPtr = shapeWork;
	for (int j=0;j<screenSizeY;j++)
	{
		int ln = *sPtr;
		if (ln == 0)	//no shape
		{
			*sPtr = screenSizeX;
			sPtr++;
			*sPtr = 0;
			sPtr++;
			*sPtr = 0;
			sPtr++;
			*sPtr = 0;
			sPtr++;
			*sPtr = 0;
			sPtr++;
			*sPtr = 0;
			sPtr++;
		}
		else
		{
			int left1 = *(sPtr+1);
			int right1 = *(sPtr+2);
			int left2 = *(sPtr+3);
			int right2 = *(sPtr+4);

			if (ln == 1)
			{
				right1 = screenSizeX+1;
				left2 = right1;
				right2 = left2 - 1;
			}
			else if (ln == 2)
			{
				left2 = screenSizeX;
				right2 = screenSizeX;
			}
			else if (ln == 3)
			{
				right2 = screenSizeX + 1;
			}

			int ln1 = 0;
			int ln2 = 0;
			int ln3 = 0;
			int ln4 = 0;
			int ln5 = 0;

			if (left1 > 0)
			{
				int left = left1;
				if (left > screenSizeX) left = screenSizeX;
				ln1 = left;
			}

			if (right1>left1)
			{
				if ((left1 < screenSizeX) && (right1 >= 0))
				{
					int left = left1;
					int right = right1;
					if (left<0) left = 0;
					if (right<0) right = 0;
					if (left >= screenSizeX) left = screenSizeX; 
					if (right >= screenSizeX) right = screenSizeX;
					ln2 = right - left;
					if (ln2<0) ln2 = 0;
				}
			}

			if (left2>right1)
			{
				int left = right1;
				int right = left2;
				if ((left < screenSizeX) && (right >= 0))
				{
					if (left<0) left = 0;
					if (right<0) right = 0;
					if (left >= screenSizeX) left = screenSizeX;
					if (right >= screenSizeX) right = screenSizeX;
					ln3 = right - left;
					if (ln3<0) ln3 = 0;
				}
			}

			if (right2>left2)
			{
				if ((left2 < screenSizeX) && (right2 >= 0))
				{
					int left = left2;
					int right = right2;
					if (left<0) left = 0;
					if (right<0) right = 0;
					if (left >= screenSizeX) left = screenSizeX;
					if (right >= screenSizeX) right = screenSizeX;
					ln4 = right - left;
					if (ln4<0) ln4 = 0;
				}
			}
			if (right2 < screenSizeX)
			{
				int left = right2;
				int right = screenSizeX;
				if ((left < screenSizeX) && (right >= 0))
				{
					if (left<0) left = 0;
					if (right<0) right = 0;
					if (left >= screenSizeX) left = screenSizeX;
					if (right >= screenSizeX) right = screenSizeX;
					ln5 = right - left;
					if (ln5<0) ln5 = 0;
				}
			}

			*sPtr = ln1;
			sPtr++;
			*sPtr = ln2;
			sPtr++;
			*sPtr = ln3;
			sPtr++;
			*sPtr = ln4;
			sPtr++;
			*sPtr = ln5;
			sPtr++;
			*sPtr = 0;
			sPtr++;
		}
	}



}


void CEffectSimpleWipeTurnStar::AddLeftRightDot(int leftRight, int startX, int startY, int endX,int endY)
{
	if (endY < startY)
	{
		leftRight = 1 - leftRight;
		
		int tmp = startX;
		startX= endX;
		endX = tmp;

		tmp = startY;
		startY = endY;
		endY = tmp;
	}

	if (leftRight == 0)
	{
		AddLeftDot(startX,startY,endX,endY);
	}
	else
	{
		AddRightDot(startX,startY,endX,endY);
	}
}

void CEffectSimpleWipeTurnStar::AddLeftDot(int startX,int startY,int endX,int endY)
{
//	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int dv = endY - startY;
	if (dv<1) dv = 1;

	int st = startY;
	int ed = endY;
	if (st<0) st = 0;
	if (ed>=screenSizeY) ed = screenSizeY;

//	int* shapeWork = CEffectSimpleWipe::m_shapeWork;
	int* shapeWork = m_allSimpleWipe->GetShapeWork();

	int* sPtr = shapeWork;
	sPtr += m_shapeDivide * st;



	if (st<=ed)
	{
		for (int j=st;j<=ed;j++)
		{
			int k = j - startY;
			int x = startX + ((endX - startX) * k) / dv;

			int ln = *sPtr;
			if (ln == 0)
			{
				*sPtr = 1;
				*(sPtr + 1) = x;
			}
			else if (ln == 2)
			{
				*sPtr = 3;
				*(sPtr + 3) = x;
			}

			sPtr += m_shapeDivide;
		}
	}
}

void CEffectSimpleWipeTurnStar::AddRightDot(int startX,int startY,int endX,int endY)
{
//	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int dv = endY - startY;
	if (dv<1) dv = 1;

	int st = startY;
	int ed = endY;
	if (st<0) st = 0;
	if (ed>=screenSizeY) ed = screenSizeY;

//	int* shapeWork = CEffectSimpleWipe::m_shapeWork;
	int* shapeWork = m_allSimpleWipe->GetShapeWork();

	int* sPtr = shapeWork;
	sPtr += m_shapeDivide * st;

	if (st<=ed)
	{
		for (int j=st;j<=ed;j++)
		{
			int k = j - startY;
			int x = startX + ((endX - startX) * k) / dv;

			int ln = *sPtr;

			if (ln == 1)
			{
				*sPtr = 2;
				*(sPtr + 2) = x;
			}
			else if (ln == 2)	//‰„’·
			{
//				*sPtr = 2;
				if (x>(*(sPtr+2)))
				{
					*(sPtr + 2) = x;
				}
			}
			else if (ln == 3)
			{
				*sPtr = 4;
				*(sPtr + 4) = x;
			}

			sPtr += m_shapeDivide;
		}
	}
}













