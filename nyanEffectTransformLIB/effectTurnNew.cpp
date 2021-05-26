//
// effectTurnNew.cpp
//

#include "..\nyanEffectLib\includer.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "effectTurnNew.h"


#define TURNNEW_FRAME 0
#define TURNNEW_DRAWMODE 1
#define TURNNEW_COMPLEMENT 2
#define TURNNEW_END_ANGLE 3
#define TURNNEW_START_ANGLE 4
#define TURNNEW_CENTER_DX 5
#define TURNNEW_CENTER_DY 6
#define TURNNEW_END_STRETCH_X 7
#define TURNNEW_END_STRETCH_Y 8
#define TURNNEW_START_STRETCH_X 9
#define TURNNEW_START_STRETCH_Y 10
#define TURNNEW_END_TRANS 11
#define TURNNEW_START_TRANS 12

#define TURNNEW_ANGLE_TYPE 13
#define TURNNEW_ANGLE_SUBFRAME 14
#define TURNNEW_STRETCH_TYPE 15
#define TURNNEW_STRETCH_SUBFRAME 16
#define TURNNEW_TRANS_TYPE 17
#define TURNNEW_TRANS_SUBFRAME 18
#define TURNNEW_ADDSUB_TYPE 19
#define TURNNEW_ADDSUB_SUBFRAME 20

#define TURNNEW_END_ADDSUB_R 21
#define TURNNEW_END_ADDSUB_G 22
#define TURNNEW_END_ADDSUB_B 23
#define TURNNEW_START_ADDSUB_R 24
#define TURNNEW_START_ADDSUB_G 25
#define TURNNEW_START_ADDSUB_B 26


CEffectTurnNew::CEffectTurnNew(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	SetPercentKosuu(1);
	Create("Turn");
#endif
}

CEffectTurnNew::~CEffectTurnNew()
{
	End();
}

void CEffectTurnNew::End(void)
{
}

BOOL CEffectTurnNew::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr, int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[36];
	int k = paraKosuu;
	if (k > 36) k = 36;
	int i;
	for (i = 0; i < k; i++)
	{
		para[i] = paraPtr[i];
	}




	if (paraKosuu <= TURNNEW_FRAME) para[TURNNEW_FRAME] = 20;	//frame
	if (paraKosuu <= TURNNEW_DRAWMODE) para[TURNNEW_DRAWMODE] = 0;	//•`‰æƒ‚[ƒh
	if (paraKosuu <= TURNNEW_COMPLEMENT) para[TURNNEW_COMPLEMENT] = 0;	//•âŠ®

	if (paraKosuu <= TURNNEW_END_ANGLE) para[TURNNEW_END_ANGLE] = 0;	//th1	‰ñ“]end
	if (paraKosuu <= TURNNEW_START_ANGLE) para[TURNNEW_START_ANGLE] = para[TURNNEW_END_ANGLE];	//th2	‰ñ“]start
	if (paraKosuu <= TURNNEW_CENTER_DX) para[TURNNEW_CENTER_DX] = 0;	//‰ñ“]’†SdeltaX
	if (paraKosuu <= TURNNEW_CENTER_DY) para[TURNNEW_CENTER_DY] = 0;	//‰ñ“]’†SdeltaY
	if (paraKosuu <= TURNNEW_END_STRETCH_X) para[TURNNEW_END_STRETCH_X] = 100;	//Šg‘åk¬EndX		
	if (paraKosuu <= TURNNEW_END_STRETCH_Y) para[TURNNEW_END_STRETCH_Y] = 100;	//Šg‘åk¬EndY		
	if (paraKosuu <= TURNNEW_START_STRETCH_X) para[TURNNEW_START_STRETCH_X] = para[TURNNEW_END_STRETCH_X];	//Šg‘åk¬StartX		
	if (paraKosuu <= TURNNEW_START_STRETCH_Y) para[TURNNEW_START_STRETCH_Y] = para[TURNNEW_END_STRETCH_Y];	//Šg‘åk¬StartY		


	if (paraKosuu <= TURNNEW_END_TRANS) para[TURNNEW_END_TRANS] = 100;	//transEnd
	if (paraKosuu <= TURNNEW_START_TRANS) para[TURNNEW_START_TRANS] = para[TURNNEW_END_TRANS];//transStart


	if (paraKosuu <= TURNNEW_ANGLE_TYPE) para[TURNNEW_ANGLE_TYPE] = 0;	//‰ñ“]speedType
	if (paraKosuu <= TURNNEW_ANGLE_SUBFRAME) para[TURNNEW_ANGLE_SUBFRAME] = 0;	//‰ñ“]subframe

	if (paraKosuu <= TURNNEW_STRETCH_TYPE) para[TURNNEW_STRETCH_TYPE] = 0;	//Šg‘åspeedType
	if (paraKosuu <= TURNNEW_STRETCH_SUBFRAME) para[TURNNEW_STRETCH_SUBFRAME] = 0;	//Šg‘åsubframe

	if (paraKosuu <= TURNNEW_TRANS_TYPE) para[TURNNEW_TRANS_TYPE] = 0;	//“§‰ßspeedType
	if (paraKosuu <= TURNNEW_TRANS_SUBFRAME) para[TURNNEW_TRANS_SUBFRAME] = 0;	//“§‰ßsubframe

	if (paraKosuu <= TURNNEW_ADDSUB_TYPE) para[TURNNEW_ADDSUB_TYPE] = 0;	//addsubspeedType
	if (paraKosuu <= TURNNEW_ADDSUB_SUBFRAME) para[TURNNEW_ADDSUB_SUBFRAME] = 0;	//addsubsubframe

	if (paraKosuu <= TURNNEW_END_ADDSUB_R) para[TURNNEW_END_ADDSUB_R] = 0;	//end r
	if (paraKosuu <= TURNNEW_END_ADDSUB_G) para[TURNNEW_END_ADDSUB_G] = para[TURNNEW_END_ADDSUB_R];	//end g
	if (paraKosuu <= TURNNEW_END_ADDSUB_B) para[TURNNEW_END_ADDSUB_B] = para[TURNNEW_END_ADDSUB_G];	//end b

	if (paraKosuu <= TURNNEW_START_ADDSUB_R) para[TURNNEW_START_ADDSUB_R] = para[TURNNEW_END_ADDSUB_B];	//start r
	if (paraKosuu <= TURNNEW_START_ADDSUB_G) para[TURNNEW_START_ADDSUB_G] = para[TURNNEW_START_ADDSUB_R];	//start g
	if (paraKosuu <= TURNNEW_START_ADDSUB_G) para[TURNNEW_START_ADDSUB_G] = para[TURNNEW_START_ADDSUB_G];	//start b



	lp->flag = TRUE;
	lp->command = EFFECT_TURNNEW;
	lp->countMax = para[TURNNEW_FRAME];
	lp->count = 0;

	for (i = 0; i < 36; i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectTurnNew::CountIsMax(LPVOID lpEffect, int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	//	lp->command = EFFECT_NOP;
	//	if (lp->pic == -1)
	//	{
	//		lp->flag = FALSE;
	//	}
	//
	//	return TRUE;
	return FALSE;
}


void CEffectTurnNew::BeginPrint(LPVOID para, int layer)
{

}

void CEffectTurnNew::Init(LPVOID para, int layer)
{
}

void CEffectTurnNew::Calcu(LPVOID lpEffect, int layer)
{
}


void CEffectTurnNew::Print(LPVOID lpEffect, int layer)
{


	int* screenBuffer = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;



	int angleType = lp->para[TURNNEW_ANGLE_TYPE];
	int angleSubFrame = lp->para[TURNNEW_ANGLE_SUBFRAME];

	int stretchType = lp->para[TURNNEW_STRETCH_TYPE];
	int stretchSubFrame = lp->para[TURNNEW_STRETCH_SUBFRAME];

	int transType = lp->para[TURNNEW_TRANS_TYPE];
	int transSubFrame = lp->para[TURNNEW_TRANS_SUBFRAME];

	int addsubType = lp->para[TURNNEW_ADDSUB_TYPE];
	int addsubSubFrame = lp->para[TURNNEW_ADDSUB_SUBFRAME];




	int startAngle = lp->para[TURNNEW_START_ANGLE];
	int endAngle = lp->para[TURNNEW_END_ANGLE];

	int centerDx = lp->para[TURNNEW_CENTER_DX];
	int centerDy = lp->para[TURNNEW_CENTER_DY];

	int stretchStartX = lp->para[TURNNEW_START_STRETCH_X];
	int stretchStartY = lp->para[TURNNEW_START_STRETCH_Y];
	int stretchEndX = lp->para[TURNNEW_END_STRETCH_X];
	int stretchEndY = lp->para[TURNNEW_END_STRETCH_Y];

	int transStart = lp->para[TURNNEW_START_TRANS];
	int transEnd = lp->para[TURNNEW_END_TRANS];

	int transPercent = CCalcuSpeed::calcu(count, countMax, transStart, transEnd, transSubFrame, transType);
	if (transPercent <= 0) return;


	int stretchX = CCalcuSpeed::calcu(count, countMax, stretchStartX * 100, stretchEndX * 100, stretchSubFrame, stretchType) / 100;
	int stretchY = CCalcuSpeed::calcu(count, countMax, stretchStartY * 100, stretchEndY * 100, stretchSubFrame, stretchType) / 100;
	if (stretchX < 1) stretchX = 1;
	if (stretchY < 1) stretchY = 1;


	int drawMode = lp->para[TURNNEW_DRAWMODE];
	int complement = lp->para[TURNNEW_COMPLEMENT];
	int addsubtype = lp->para[TURNNEW_ADDSUB_TYPE];
	int addsubsubFrame = lp->para[TURNNEW_ADDSUB_SUBFRAME];

	int r1 = lp->para[TURNNEW_START_ADDSUB_R];
	int g1 = lp->para[TURNNEW_START_ADDSUB_G];
	int b1 = lp->para[TURNNEW_START_ADDSUB_B];

	int r2 = lp->para[TURNNEW_END_ADDSUB_R];
	int g2 = lp->para[TURNNEW_END_ADDSUB_G];
	int b2 = lp->para[TURNNEW_END_ADDSUB_B];

	int addSubR = CCalcuSpeed::calcu(count, countMax, r1, r2, addsubsubFrame, addsubtype);
	int addSubG = CCalcuSpeed::calcu(count, countMax, g1, g2, addsubsubFrame, addsubtype);
	int addSubB = CCalcuSpeed::calcu(count, countMax, b1, b2, addsubsubFrame, addsubtype);


	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);

	int srcPicSizeX = rc.right;
	int srcPicSizeY = rc.bottom;

	if ((srcPicSizeX < 1) || (srcPicSizeY < 1)) return;


	int* picSrc = (int*)(lpPic->GetBuffer());
	if (picSrc == NULL) return;

	char* picMask = lpPic->GetMaskPic();
	if (picMask == nullptr) return;


	int srcCenterX = srcPicSizeX / 2;
	int srcCenterY = srcPicSizeY / 2;

	int turnCenterX = srcCenterX + centerDx;
	int turnCenterY = srcCenterX + centerDy;


	int angleMulti = 10;
	int th = CCalcuSpeed::calcu(count, countMax, startAngle * angleMulti, endAngle * angleMulti, angleSubFrame, angleType);

	if (th < 0)
	{
		th *= -1;
		if (th >= 360*angleMulti)
		{
			th %= (360*angleMulti);
		}
		th *= -1;
		th += 360*angleMulti;
	}

	if (th >= 360 * angleMulti)
	{
		th %= (360 * angleMulti);
	}

	double kaitenTh = (double)th;
	kaitenTh *= (M_PI * 2 / (360.0*angleMulti));


	double cosTH = cos(kaitenTh);
	double sinTH = sin(kaitenTh);


	double mCosTH = (float)cos(-kaitenTh);
	double mSinTH = (float)sin(-kaitenTh);


	int putX = lp->dst.left;
	int putY = lp->dst.top;

	int srcTurnCenterX = srcPicSizeX / 2 + centerDx;
	int srcTurnCenterY = srcPicSizeY / 2 + centerDy;

	int screenTurnCenterX = putX + srcPicSizeX / 2 + centerDx;
	int screenTurnCenterY = putY + srcPicSizeY / 2 + centerDy;


	double multiX = ((double)stretchX) / 100.0;
	double multiY = ((double)stretchY) / 100.0;

	double revMultiX = 100.0 / ((double)stretchX);
	double revMultiY = 100.0 / ((double)stretchY);


	int dstStartX = 0;
	int dstEndX = screenSizeX;
	int dstStartY = 0;
	int dstEndY = screenSizeY;


	double x0 = -srcTurnCenterX;
	double y0 = -srcTurnCenterY;

	double x1 = x0 * multiX;
	double y1 = y0 * multiY;

	double x2 = cosTH * x1 - sinTH * y1;
	double y2 = sinTH * x1 + cosTH * y1;

	x2 += screenTurnCenterX;
	y2 += screenTurnCenterY;

	double clipXMin = x2;
	double clipXMax = x2;
	double clipYMin = y2;
	double clipYMax = y2;

	x0 = srcPicSizeX - srcTurnCenterX;
	y0 = -srcTurnCenterY;
	x1 = x0 * multiX;
	y1 = y0 * multiY;
	x2 = cosTH * x1 - sinTH * y1;
	y2 = sinTH * x1 + cosTH * y1;
	x2 += screenTurnCenterX;
	y2 += screenTurnCenterY;
	if (x2 < clipXMin) clipXMin = x2;
	if (x2 > clipXMax) clipXMax = x2;
	if (y2 < clipYMin) clipYMin = y2;
	if (y2 > clipYMax) clipYMax = y2;

	x0 = -srcTurnCenterX;
	y0 = srcPicSizeY-srcTurnCenterY;
	x1 = x0 * multiX;
	y1 = y0 * multiY;
	x2 = cosTH * x1 - sinTH * y1;
	y2 = sinTH * x1 + cosTH * y1;
	x2 += screenTurnCenterX;
	y2 += screenTurnCenterY;
	if (x2 < clipXMin) clipXMin = x2;
	if (x2 > clipXMax) clipXMax = x2;
	if (y2 < clipYMin) clipYMin = y2;
	if (y2 > clipYMax) clipYMax = y2;

	x0 = srcPicSizeX-srcTurnCenterX;
	y0 = srcPicSizeY - srcTurnCenterY;
	x1 = x0 * multiX;
	y1 = y0 * multiY;
	x2 = cosTH * x1 - sinTH * y1;
	y2 = sinTH * x1 + cosTH * y1;
	x2 += screenTurnCenterX;
	y2 += screenTurnCenterY;
	if (x2 < clipXMin) clipXMin = x2;
	if (x2 > clipXMax) clipXMax = x2;
	if (y2 < clipYMin) clipYMin = y2;
	if (y2 > clipYMax) clipYMax = y2;



	int areaStartX = (int)clipXMin - 2;
	int areaEndX = (int)clipXMax + 2;
	int areaStartY = (int)clipYMin - 2;
	int areaEndY = (int)clipYMax + 2;

	if (areaStartX < 0) areaStartX = 0;
	if (areaStartY < 0) areaStartY = 0;
	if (areaEndX > screenSizeX) areaEndX = screenSizeX;
	if (areaEndY > screenSizeY) areaEndY = screenSizeY;

	if ((areaEndX - areaStartX) <= 0) return;
	if ((areaEndY - areaStartY) <= 0) return;



	dstStartX = areaStartX;
	dstEndX = areaEndX;

	dstStartY = areaStartY;
	dstEndY = areaEndY;




	int* dst0 = screenBuffer + dstStartX + dstStartY * screenSizeX;

	for (int dstY = dstStartY; dstY < dstEndY; dstY++)
	{
		int* dst = dst0;

		for (int dstX = dstStartX; dstX < dstEndX; dstX++)
		{
			double dx = (double)(dstX - screenTurnCenterX);
			double dy = (double)(dstY - screenTurnCenterY);

			double revTurnedX = mCosTH * dx - mSinTH * dy;
			double revTurnedY = mSinTH * dx + mCosTH * dy;

			double revStretchedX = revTurnedX * revMultiX;
			double revStretchedY = revTurnedY * revMultiY;

			double calcuedSrcX = srcTurnCenterX + revStretchedX;
			double calcuedSrcY = srcTurnCenterY + revStretchedY;

			calcuedSrcX += 0.5;
			calcuedSrcY += 0.5;

			if ((calcuedSrcX >= 0.0) && (calcuedSrcY >= 0.0))
			{
				int srcX = (int)(calcuedSrcX);
				int srcY = (int)(calcuedSrcY);
				if ((srcX >= 0) && (srcY >= 0) && (srcX < srcPicSizeX) && (srcY < srcPicSizeY))
				{
					int* src = picSrc + srcX + srcY * srcPicSizeX;
					int srcColor = *src;
					int dstColor = *dst;

					int srcR = (srcColor >> 16) & 0xff;
					int srcG = (srcColor >> 8) & 0xff;
					int srcB = (srcColor) & 0xff;
					int dstR = (dstColor >> 16) & 0xff;
					int dstG = (dstColor >> 8) & 0xff;
					int dstB = (dstColor) & 0xff;

					int srcTrans = (int)(*(picMask + srcX + srcY * srcPicSizeX)) & 0xff;


					if (complement == 1)
					{
						double amariX = calcuedSrcX - srcX;
						double amariY = calcuedSrcY - srcY;

						double directionX = 1.0f;
						double directionY = 1.0f;
						double alphaX = amariX;
						double alphaY = amariY;

						if (amariX >= 0.5)
						{
							alphaX = 1.5 - amariX;
						}
						else
						{
							alphaX = 0.5 + amariX;
							directionX = -1.0;
						}

						if (amariY >= 0.5)
						{
							alphaY = 1.5 - amariY;
						}
						else
						{
							alphaY = 0.5 + amariY;
							directionY = -1.0;
						}

						double peekXDouble = calcuedSrcX + directionX * revMultiX;
						double peekYDouble = calcuedSrcY + directionY * revMultiY;

						int peekX = (int)(peekXDouble);
						int peekY = (int)(peekYDouble);


						//”ÍˆÍŠO‚¾‚Á‚½‚ç‚µ‚å‚¤‚ª‚È‚¢
						if ((peekXDouble < 0.0) || (peekX < 0) || (peekX >= srcPicSizeX))
						{
							peekX = srcX;
						}
						if ((peekYDouble < 0.0) || (peekY < 0) || (peekY >= srcPicSizeY))
						{
							peekY = srcY;
						}


						int alphaX0Y0 = (int)(alphaX * alphaY * 256);
						int alphaX1Y0 = (int)((1.0 - alphaX) * alphaY * 256);
						int alphaX0Y1 = (int)(alphaX * (1.0 - alphaY) * 256);
						int alphaX1Y1 = (int)((1.0 - alphaX) * (1.0 - alphaY) * 256);

						int colX0Y0 = *(picSrc + srcX + srcY * srcPicSizeX);
						int colX1Y0 = *(picSrc + peekX + srcY * srcPicSizeX);
						int colX0Y1 = *(picSrc + srcX + peekY * srcPicSizeX);
						int colX1Y1 = *(picSrc + peekX + peekY * srcPicSizeX);


						int maskX0Y0 = (*(picMask + srcX + srcY * srcPicSizeX)) & 0xff;
						int maskX1Y0 = (*(picMask + peekX + srcY * srcPicSizeX)) & 0xff;
						int maskX0Y1 = (*(picMask + srcX + peekY * srcPicSizeX)) & 0xff;
						int maskX1Y1 = (*(picMask + peekX + peekY * srcPicSizeX)) & 0xff;

						int X0Y0_R = (colX0Y0 >> 16) & 0xff;
						int X0Y0_G = (colX0Y0 >> 8) & 0xff;
						int X0Y0_B = (colX0Y0) & 0xff;
						int X1Y0_R = (colX1Y0 >> 16) & 0xff;
						int X1Y0_G = (colX1Y0 >> 8) & 0xff;
						int X1Y0_B = (colX1Y0) & 0xff;
						int X0Y1_R = (colX0Y1 >> 16) & 0xff;
						int X0Y1_G = (colX0Y1 >> 8) & 0xff;
						int X0Y1_B = (colX0Y1) & 0xff;
						int X1Y1_R = (colX1Y1 >> 16) & 0xff;
						int X1Y1_G = (colX1Y1 >> 8) & 0xff;
						int X1Y1_B = (colX1Y1) & 0xff;

						srcR = ((X0Y0_R * alphaX0Y0) + (X1Y0_R * alphaX1Y0) + (X0Y1_R * alphaX0Y1) + (X1Y1_R * alphaX1Y1)) >> 8;
						srcG = ((X0Y0_G * alphaX0Y0) + (X1Y0_G * alphaX1Y0) + (X0Y1_G * alphaX0Y1) + (X1Y1_G * alphaX1Y1)) >> 8;
						srcB = ((X0Y0_B * alphaX0Y0) + (X1Y0_B * alphaX1Y0) + (X0Y1_B * alphaX0Y1) + (X1Y1_B * alphaX1Y1)) >> 8;

						srcTrans = ((maskX0Y0 * alphaX0Y0) + (maskX1Y0 * alphaX1Y0) + (maskX0Y1 * alphaX0Y1) + (maskX1Y1 * alphaX1Y1)) >> 8;

					}


					if (srcTrans > 0)
					{
						srcR += addSubR;
						srcG += addSubG;
						srcB += addSubB;
						if (srcR < 0) srcR = 0;
						if (srcG < 0) srcG = 0;
						if (srcB < 0) srcB = 0;
						if (srcR > 255) srcR = 255;
						if (srcG > 255) srcG = 255;
						if (srcB > 255) srcB = 255;

						int r = srcR;
						int g = srcG;
						int b = srcB;

						if (drawMode == 0)
						{
							//normal
							if ((srcTrans == 255) && (transPercent == 100))
							{

							}
							else
							{
								int tr = (256 * (srcTrans * transPercent)) / (100 * 255);

								r = (srcR * tr + dstR * (256 - tr)) >> 8;
								g = (srcG * tr + dstG * (256 - tr)) >> 8;
								b = (srcB * tr + dstB * (256 - tr)) >> 8;
							}
						}
						else if (drawMode == 1)
						{
							//add
							int tr = (256 * (srcTrans * transPercent)) / (100 * 255);
							r = dstR + ((srcR * tr) >> 8);
							g = dstG + ((srcG * tr) >> 8);
							b = dstB + ((srcB * tr) >> 8);

							if (r > 255) r = 255;
							if (g > 255) g = 255;
							if (b > 255) b = 255;
						}
						else if (drawMode == 2)
						{
							//sub
							int tr = (256 * (srcTrans * transPercent)) / (100 * 255);
							r = dstR - ((srcR * tr) >> 8);
							g = dstG - ((srcG * tr) >> 8);
							b = dstB - ((srcB * tr) >> 8);

							if (r < 0) r = 0;
							if (g < 0) g = 0;
							if (b < 0) b = 0;
						}


						int col = (r << 16) | (g << 8) | b;
						*dst = col;
					}



				}
			}


			dst++;

		}

		dst0 += screenSizeX;
	}

/*





	int zX = lp->dst.left;
	int zY = lp->dst.top;

	int sprineFlag = lp->para[25];

	if ((sprineFlag == 2) || (sprineFlag == 3))
	{
		int spSubType = lp->para[34];
		int spSubFrame = lp->para[35];

		float x1 = (float)(lp->para[26]);
		float y1 = (float)(lp->para[27]);
		float x2 = (float)(lp->para[28]);
		float y2 = (float)(lp->para[29]);
		float x3 = (float)(lp->para[30]);
		float y3 = (float)(lp->para[31]);
		float x4 = (float)(lp->para[32]);
		float y4 = (float)(lp->para[33]);

		int s = CCalcuSpeed::calcu(count, countMax, 0, 10000, spSubFrame, spSubType);

		float t = (float)s;
		t *= 0.0001f;

		if (sprineFlag == 3)
		{
			float t3 = t * t*t;
			float t2 = t * t*(1.0f - t);
			float t1 = t * (1.0f - t)*(1.0f - t);
			float t0 = (1.0f - t)*(1.0f - t)*(1.0f - t);

			float sprx = t0 * x1 + 3.0f*t1*x2 + 3.0f*t2*x3 + t3 * x4;
			float spry = t0 * y1 + 3.0f*t1*y2 + 3.0f*t2*y3 + t3 * y4;

			zX += (int)(sprx + 0.5f);
			zY += (int)(spry + 0.5f);
		}
		else
		{
			float t2 = t * t;
			float t1 = t * (1.0f - t);
			float t0 = (1.0f - t)*(1.0f - t);

			float sprx = t0 * x1 + 2.0f*t1*x2 + t2 * x3;
			float spry = t0 * y1 + 2.0f*t1*y2 + t2 * y3;

			zX += (int)(sprx + 0.5f);
			zY += (int)(spry + 0.5f);
		}
	}


	double cosTH = cos(kaitenTh);
	double sinTH = sin(kaitenTh);


	cosTH /= (double)multi;
	cosTH *= 100.0;

	sinTH /= (double)multi;
	sinTH *= 100.0;





	double pX = (double)(sx / 2 + dx);
	double pY = (double)(sy / 2 + dy);



	double x = 0;
	double y = 0.0;

	double mx = (double)(screenSizeX / 2);
	double my = (double)(screenSizeY / 2);


	x = 0.0 - (mx + zX);
	y = 0.0 - (my + zY);
	double x0 = cosTH * x - sinTH * y + pX;
	double y0 = sinTH * x + cosTH * y + pY;

	x = (double)screenSizeX - (mx + zX);
	y = 0.0 - (my + zY);
	double x1 = cosTH * x - sinTH * y + pX;
	double y1 = sinTH * x + cosTH * y + pY;

	x = 0.0 - (mx + zX);
	y = (double)screenSizeY - (my + zY);
	double x2 = cosTH * x - sinTH * y + pX;
	double y2 = sinTH * x + cosTH * y + pY;

	x = (double)screenSizeX - (mx + zX);
	y = (double)screenSizeY - (my + zY);
	double x3 = cosTH * x - sinTH * y + pX;
	double y3 = sinTH * x + cosTH * y + pY;

	x0 += 0.5;
	y0 += 0.5;
	x1 += 0.5;
	y1 += 0.5;
	x2 += 0.5;
	y2 += 0.5;
	x3 += 0.5;
	y3 += 0.5;


	double ddx = (x1 - x0) / ((double)screenSizeX);
	double ddy = (y1 - y0) / ((double)screenSizeX);

	double ddx2 = (x2 - x0) / ((double)screenSizeY);
	double ddy2 = (y2 - y0) / ((double)screenSizeY);


	double ml = 65536.0;

	int ddxInt = (int)ddx;
	int ddxAmari = 0;
	if (ddx >= 0)
	{
		ddxAmari = (int)((ddx - ddxInt) * ml);
	}
	else
	{
		ddxInt--;
		ddxAmari = (int)((ddx - ddxInt) * ml);
	}

	int ddyInt = (int)ddy;
	int ddyAmari = 0;
	if (ddy >= 0)
	{
		ddyAmari = (int)((ddy - ddyInt) * ml);
	}
	else
	{
		ddyInt--;
		ddyAmari = (int)((ddy - ddyInt) * ml);
	}


	int ddx2Int = (int)ddx2;
	int ddx2Amari = 0;
	if (ddx2 >= 0)
	{
		ddx2Amari = (int)((ddx2 - ddx2Int) * ml);
	}
	else
	{
		ddx2Int--;
		ddx2Amari = (int)((ddx2 - ddx2Int) * ml);
	}

	int ddy2Int = (int)ddy2;
	int ddy2Amari = 0;
	if (ddy2 >= 0)
	{
		ddy2Amari = (int)((ddy2 - ddy2Int) * ml);
	}
	else
	{
		ddy2Int--;
		ddy2Amari = (int)((ddy2 - ddy2Int) * ml);
	}



	int lPitch = screenSizeX * 4;
	int maskPitch = sx;


	int tmpX = (int)(x0);
	int tmpAmariX;
	if (x0 >= 0)
	{
		tmpAmariX = (int)((x0 - tmpX) * ml);
	}
	else
	{
		tmpX--;
		tmpAmariX = (int)((x0 - tmpX) * ml);
	}

	int tmpY = (int)(y0);
	int tmpAmariY;
	if (y0 >= 0)
	{
		tmpAmariY = (int)((y0 - tmpY) * ml);
	}
	else
	{
		tmpY--;
		tmpAmariY = (int)((y0 - tmpY) * ml);
	}

	int tmpX2 = tmpX;
	int tmpAmariX2 = tmpAmariX;
	int tmpY2 = tmpY;
	int tmpAmariY2 = tmpAmariY;

	int trans = *src;


	if (transFlag == 2)
	{
		if (mask == NULL) transFlag = 1;
		if (lpPic->CheckMaskExist() == FALSE) transFlag = 1;
	}


	int addColor = (addColorR << 16) | (addColorG << 8) | addColorB;
	int subColor = (subColorR << 16) | (subColorG << 8) | subColorB;
	LONGLONG addColor64 = (LONGLONG)addColor;
	LONGLONG subColor64 = (LONGLONG)subColor;


	*/




}



BOOL CEffectTurnNew::CheckNeedPicPrint(LPVOID lpEffect, int layer)
{
	return FALSE;
}


/*_*/