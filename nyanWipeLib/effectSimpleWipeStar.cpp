//
// effectsimplewipeStar.cpp
//

#include <windows.h>
#include <Math.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\myGraphics.h"

#include "effectsimplewipecommon.h"
#include "effectsimplewipeShape.h"
#include "effectsimplewipeStar.h"
#include "allSimpleWipe.h"



CEffectSimpleWipeStar::CEffectSimpleWipeStar(CAllSimpleWipe* allWipe,int houkou) : CEffectSimpleWipeShape(allWipe)
{
	SetMaxDivide(6);
	SetEffectHoukou(houkou);
}

CEffectSimpleWipeStar::~CEffectSimpleWipeStar()
{
	End();
}

void CEffectSimpleWipeStar::End(void)
{
}


void CEffectSimpleWipeStar::CalcuShapeWork(int count, int countMax)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

//	if (m_effectHoukou == 1)
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

	int centerX = screenSizeX / 2;
	int centerY = screenSizeY / 2;


	double th18 = (18.0 / 180.0) * 3.14159;
	double th36 = (36.0 / 180.0) * 3.14159;

	double sin18 = sin(th18);
	double cos18 = cos(th18);

	double sin36 = sin(th36);
	double cos36 = cos(th36);

	int x0 = 0;
	int y0 = ((int)(-r + 0.5));

	int x1 = (int)(-r2 * sin36 + 0.5);
	int y1 = (int)(-r *  sin18 + 0.5);

	int x2 = (int)(-r * cos18);
	int y2 = y1;

	int x3 = (int)(-r2*cos18+0.5);
	int y3 = (int)(r2*sin18+0.5);

	int x4 = 0;		//dummy
	int y4 = (int)(r2+0.5);

	int x5 = (int)(-r * sin36 + 0.5);;
	int y5 = (int)(r * cos36 + 0.5);


//	int* shapeWork = CEffectSimpleWipe::m_shapeWork;
	int* shapeWork = m_allSimpleWipe->GetShapeWork();

	if (shapeWork == NULL) return;
	if (m_shapeDivide == 0) return;

	int* sPtr = shapeWork;

	for (int j=0;j<screenSizeY;j++)
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


	//‚Æ‚ñ‚ª‚è
	int st0 = centerY + y0;
	int ed0 = centerY + y1 - 1;
	int st = st0;
	int ed = ed0;

	if (st<0) st = 0;
	if (ed>=screenSizeY) ed = screenSizeY-1;
	if (ed>=st)
	{
		int dv = ed0 - st0;
		if (dv<1) dv = 1;

		int sx1 = centerX + x0;
		int ex1 = centerX + x1;

		int sx2 = centerX - x0;
		int ex2 = centerX - x1;

		int* ptr = shapeWork + st * m_shapeDivide;

		for (int j=st;j<=ed;j++)
		{
			int k = (j - st0);
			int leftX = sx1 + ((ex1 - sx1) * k) / dv;
			int rightX = sx2 + ((ex2 - sx2) * k) / dv;

			if (leftX<0) leftX = 0;
			if (rightX>screenSizeX-1) rightX = screenSizeX-1;

			int len1 = leftX;
			if (len1<0) len1 = 0;
			if (len1>screenSizeX) len1 = screenSizeX;

			int len2 = rightX+1-leftX;
			if (len2<0) len2 = 0;
			if (len2>screenSizeX) len2 = screenSizeX;
			if (leftX>=screenSizeX) len2 = 0;

			int len3 = screenSizeX - (rightX+1);
			if (len3<0) len3 = 0;
			if (len3>screenSizeX) len3 = screenSizeX;

			*ptr = len1;
			ptr++;
			*ptr = len2;
			ptr++;
			*ptr = len3;
			ptr+=(m_shapeDivide - 2);
		}
	}





	st0 = centerY + y2;
	ed0 = centerY + y3 - 1;
	st = st0;
	ed = ed0;

	if (st<0) st = 0;
	if (ed>=screenSizeY) ed = screenSizeY-1;
	if (ed>=st)
	{
		int dv = ed0 - st0;
		if (dv<1) dv = 1;

		int sx1 = centerX + x2;
		int ex1 = centerX + x3;

		int sx2 = centerX - x2;
		int ex2 = centerX - x3;

		int* ptr = shapeWork + st * m_shapeDivide;

		for (int j=st;j<=ed;j++)
		{
			int k = (j - st0);
			int leftX = sx1 + ((ex1 - sx1) * k) / dv;
			int rightX = sx2 + ((ex2 - sx2) * k) / dv;

			if (leftX<0) leftX = 0;
			if (rightX>screenSizeX-1) rightX = screenSizeX-1;

			int len1 = leftX;
			if (len1<0) len1 = 0;
			if (len1>screenSizeX) len1 = screenSizeX;

			int len2 = rightX+1-leftX;
			if (len2<0) len2 = 0;
			if (len2>screenSizeX) len2 = screenSizeX;
			if (leftX>=screenSizeX) len2 = 0;

			int len3 = screenSizeX - (rightX+1);
			if (len3<0) len3 = 0;
			if (len3>screenSizeX) len3 = screenSizeX;

			*ptr = len1;
			ptr++;
			*ptr = len2;
			ptr++;
			*ptr = len3;
			ptr+=(m_shapeDivide - 2);
		}
	}


	st0 = centerY + y3;
	ed0 = centerY + y4 - 1;
	int ed1 = centerY + y5;
	st = st0;
	ed = ed0;

	if (st<0) st = 0;
	if (ed>=screenSizeY) ed = screenSizeY-1;
	if (ed>=st)
	{
		int dv = ed1 - st0;
		if (dv<1) dv = 1;

		int sx1 = centerX + x3;
		int ex1 = centerX + x5;

		int sx2 = centerX - x3;
		int ex2 = centerX - x5;

		int* ptr = shapeWork + st * m_shapeDivide;

		for (int j=st;j<=ed;j++)
		{
			int k = (j - st0);
			int leftX = sx1 + ((ex1 - sx1) * k) / dv;
			int rightX = sx2 + ((ex2 - sx2) * k) / dv;

			if (leftX<0) leftX = 0;
			if (rightX>screenSizeX-1) rightX = screenSizeX-1;

			int len1 = leftX;
			if (len1<0) len1 = 0;
			if (len1>screenSizeX) len1 = screenSizeX;

			int len2 = rightX+1-leftX;
			if (len2<0) len2 = 0;
			if (len2>screenSizeX) len2 = screenSizeX;
			if (leftX>=screenSizeX) len2 = 0;

			int len3 = screenSizeX - (rightX+1);
			if (len3<0) len3 = 0;
			if (len3>screenSizeX) len3 = screenSizeX;

			*ptr = len1;
			ptr++;
			*ptr = len2;
			ptr++;
			*ptr = len3;
			ptr+=(m_shapeDivide - 2);
		}
	}

	st0 = centerY + y3;
	int st1 = centerY + y4;
	ed0 = centerY + y5 - 1;
	st = st1;
	ed = ed0;

	if (st<0) st = 0;
	if (ed>=screenSizeY) ed = screenSizeY-1;
	if (ed>=st)
	{
		int dv0 = ed0 - st0;
		if (dv0<1) dv0 = 1;
		int dv1 = ed0 - st1;
		if (dv1<1) dv1 = 1;

		int sx1 = centerX + x3;
		int ex1 = centerX + x5;

		int sx2 = centerX + x4;
		int ex2 = centerX + x5;


		int sx2b = centerX - x3;
		int ex2b = centerX - x5;

		int sx1b = centerX - x4;
		int ex1b = centerX - x5;


		int* ptr = shapeWork + st * m_shapeDivide;

		for (int j=st;j<=ed;j++)
		{
			int k = (j - st0);
			int k2 = (j - st1);

			int leftX = sx1 + ((ex1 - sx1) * k) / dv0;
			int rightX = sx2 + ((ex2 - sx2) * k2) / dv1;

			int leftX2 = sx1b + ((ex1b - sx1b) * k2) / dv1;
			int rightX2 = sx2b + ((ex2b - sx2b) * k) / dv0;

			if (leftX<0) leftX = 0;
			if (rightX>screenSizeX-1) rightX = screenSizeX-1;

			int len1 = leftX;
			if (len1<0) len1 = 0;
			if (len1>screenSizeX) len1 = screenSizeX;

			int len2 = rightX+1-leftX;
			if (len2<0) len2 = 0;
			if (len2>screenSizeX) len2 = screenSizeX;
			if (leftX>=screenSizeX) len2 = 0;

			int r1 = rightX;
			if (r1<0) r1 = 0;
			int l1 = leftX2;
			if (l1>screenSizeX) l1 = screenSizeX;

			int len3 = l1 +1 - r1;
			if (len3<0) len3= 0;
			if (len3>screenSizeX) len3 = screenSizeX;
			if (rightX>=screenSizeX) len3 = 0;

			int len4 = rightX2 - leftX2;
			if (len4<0) len4 = 0;
			if (leftX2>=screenSizeX) len4 = 0;

			int len5 = screenSizeX - (rightX2+1);
			if (len5<0) len5 = 0;
			if (len5>screenSizeX) len5 = screenSizeX;



			*ptr = len1;
			ptr++;
			*ptr = len2;
			ptr++;
			*ptr = len3;
			ptr++;
			*ptr = len4;
			ptr++;
			*ptr = len5;
			ptr+=(m_shapeDivide - 4);
		}
	}

}



