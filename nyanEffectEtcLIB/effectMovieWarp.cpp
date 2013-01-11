//
// effectMovieWarp.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectMovieWarp.h"



CEffectMovieWarp::CEffectMovieWarp(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
}


CEffectMovieWarp::~CEffectMovieWarp()
{
	End();
}

void CEffectMovieWarp::End(void)
{
}

BOOL CEffectMovieWarp::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = screenSizeX / 2;
	if (paraKosuu<3) para[2] = screenSizeY / 2;

	if (paraKosuu<4) para[3] = 180;	//kaitenTh
	if (paraKosuu<5) para[4] = 0;	//type(not used)

	if (paraKosuu<6) para[5] = 0;	//へんかタイプ
	if (paraKosuu<7) para[6] = 0;	//サブフレーム

	if (paraKosuu<8) para[7] = 100;	//半透明終了
	if (paraKosuu<9) para[8] = para[7];	//半透明開始
	if (paraKosuu<10) para[9] = 0;	//へんかタイプ
	if (paraKosuu<11) para[10] = 0;	//サブフレーム

	if (paraKosuu<12) para[11] = 100;	//倍率終了
	if (paraKosuu<13) para[12] = para[11];	//倍率開始
	if (paraKosuu<14) para[13] = 0;	//へんかタイプ
	if (paraKosuu<15) para[14] = 0;	//サブフレーム


	lp->flag = TRUE;
	lp->command = EFFECT_MOVIE_WARP;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectMovieWarp::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectMovieWarp::BeginPrint(LPVOID para,int layer)
{

}

void CEffectMovieWarp::Init(LPVOID para,int layer)
{
}

void CEffectMovieWarp::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int c = lp->count;
}


void CEffectMovieWarp::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	if (lpPic->Check256()) return;
	if (lpPic->CheckMaskExist() == FALSE) return;

	SIZE sz = lpPic->GetPicSize();

	char* maskPic = lpPic->GetMaskPic();
	int* srcPic = lpPic->GetPictureBuffer();

	int centerX = lp->para[1];
	int centerY = lp->para[2];
	int kaitenTH = lp->para[3];
	int speedType = lp->para[5];
	int subFrame = lp->para[6];

	int transPercentStart = lp->para[8];
	int transPercentEnd = lp->para[7];
	int transSpeedType = lp->para[9];
	int transSubFrame = lp->para[10];

	int multiStart = lp->para[12];
	int multiEnd = lp->para[11];
	int multiSpeedType = lp->para[13];
	int multiSubFrame = lp->para[14];

	int ps = CCalcuSpeed::calcu(c,dv,0,10000,subFrame,speedType);
	ps = 10000-ps;

	int transPercent = CCalcuSpeed::calcu(c,dv,transPercentStart,transPercentEnd,transSubFrame,transSpeedType);
	int multi1000 = CCalcuSpeed::calcu(c,dv,multiStart*10,multiEnd*10,multiSubFrame,multiSpeedType);
	if (multi1000<1) multi1000 = 1;

	if (transPercent<0) transPercent = 0;
	if (transPercent>100) transPercent = 100;

	kaitenTH *= ps;
	kaitenTH /= 10000;

	POINT dstPoint = m_allEffect->GetDstPoint(layer);

	int sizeX = sz.cx;
	int sizeY = sz.cy;

	int dstX = dstPoint.x;
	int dstY = dstPoint.y;

	int maxR = sizeX;
	if (maxR>sizeY) maxR = sizeY;
	maxR /= 2;
	if (maxR < 1) maxR = 1;

	int* screenBuffer = CMyGraphics::GetScreenBuffer();

	int pictureCenterX = dstX + centerX;
	int pictureCenterY = dstY + centerY;


	double multiR= (double)multi1000;
	multiR *= 0.001;
	multiR = 1/multiR;

	int maxR10 = maxR * 10;

	for (int j=0;j<screenSizeY;j++)
	{
//		int dy = j - pictureCenterY;
		int dy = j - centerY;
		double ddy = (double)dy;

		for (int i=0;i<screenSizeX;i++)
		{
		//	int dx = i - pictureCenterX;
			int dx = i - centerX;
			double ddx = (double)dx;

			int* dstBuffer = screenBuffer + i + j * screenSizeX;

			double rr = (double)(dx*dx + dy*dy);
			rr = sqrt(rr);

			int r = int(rr*multiR);
			int r10 = int(rr*multiR*10);
			if (r<1) r = 1;

			double th = atan2(ddy,ddx);

			int dth = kaitenTH * r10;
			dth /= (maxR10);
			
			if (dth>0)
			{
				dth %= 360;
			}
			else
			{
				dth *= -1;
				dth %= 360;
				dth *= -1;
			}

			double dth2 = (double)dth;
			dth2 /= 360.0;
			dth2 *= 3.14159*2;

			double cosTH = cos(th+dth2) * r;
			double sinTH = sin(th+dth2) * r;

			int dx2 = int(cosTH + 0.5);
			int dy2 = int(sinTH + 0.5);

			int srcX = pictureCenterX + dx2;
			int srcY = pictureCenterY + dy2;

			if ((srcX>=0) && (srcY>=0) && (srcX<sizeX) && (srcY<sizeY))
			{
				int d = *(srcPic + srcX + srcY * sizeX);
				char mask = *(maskPic + srcX + srcY * sizeX);
				if (mask == 0) continue;

				if (transPercent != 100)
				{
					int mask1 = (int)mask;
					mask1 &= 0xff;
					mask1 *= transPercent;
					mask1 /= 100;
					mask = (char)mask1;
					mask &= 0xff;
				}

				if (mask == (char)0xff)
				{
					*dstBuffer = d;
				}
				else
				{
					int srcMulti = (int)mask;
					srcMulti &= 0xff;
					int dstMulti = 256 - srcMulti;

					int dstCol = *dstBuffer;
					int srcColorR = (d>>16) & 0xff;
					int srcColorG = (d>>8) & 0xff;
					int srcColorB = d & 0xff;

					int dstColorR = (dstCol>>16) & 0xff;
					int dstColorG = (dstCol>>8) & 0xff;
					int dstColorB = dstCol & 0xff;

					int colR = (srcColorR * srcMulti + dstColorR * dstMulti) >> 8;
					int colG = (srcColorG * srcMulti + dstColorG * dstMulti) >> 8;
					int colB = (srcColorB * srcMulti + dstColorB * dstMulti) >> 8;

					int col = (colR<<16) | (colG<<8) | colB;
					*dstBuffer = col;
				}
			}
		}
	}


/*
	for (int j=0;j<sizeY;j++)
	{
		int dy = j - centerY;
		double ddy = (double)dy;

		for (int i=0;i<sizeX;i++)
		{
			char mask = *(maskPic + i + j * sizeX);
			if (mask == 0) continue;

			int dx = i - centerX;
			double ddx = (double)dx;

			double rr = (double)(dx*dx + dy*dy);
			rr = sqrt(rr);
//			if (rr < 0.5) rr = 0.5;
			int r = int(rr);
			if (r<1) r = 1;

			double th = atan2(ddy,ddx);

			int dth = kaitenTH * r;
			dth /= maxR;
			
			if (dth>0)
			{
				dth %= 360;
			}
			else
			{
				dth *= -1;
				dth %= 360;
				dth *= -1;
			}

			double dth2 = (double)dth;
			dth2 /= 360.0;
			dth2 *= 3.14159*2;


			double cosTH = cos(th+dth2) * r;
			double sinTH = sin(th+dth2) * r;

			int dx2 = int(cosTH + 0.5);
			int dy2 = int(sinTH + 0.5);

			int putX = centerX + dx2 + dstX;
			int putY = centerY + dy2 + dstY;

			if ((putX>=0) && (putY>=0) && (putX<screenSizeX) && (putY<screenSizeY))
			{
				int d = *(srcPic + i + j * sizeX);
				int* dstBuffer = screenBuffer + putX + putY * screenSizeX;

				if (mask == (char)0xff)
				{
					*dstBuffer = d;
				}
				else
				{
					int dstMulti = (int)mask;
					dstMulti &= 0xff;
					int srcMulti = 256 - dstMulti;

					int dstCol = *dstBuffer;
					int srcColorR = (d>>16) & 0xff;
					int srcColorG = (d>>8) & 0xff;
					int srcColorB = d & 0xff;

					int dstColorR = (dstCol>>16) & 0xff;
					int dstColorG = (dstCol>>8) & 0xff;
					int dstColorB = dstCol & 0xff;

					int colR = (srcColorR * srcMulti + dstColorR * dstMulti) >> 8;
					int colG = (srcColorG * srcMulti + dstColorG * dstMulti) >> 8;
					int colB = (srcColorB * srcMulti + dstColorB * dstMulti) >> 8;

					int col = (colR<<16) | (colG<<8) | colB;
					*dstBuffer = col;
				}
			}
		}
	}
*/


}

BOOL CEffectMovieWarp::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


/*_*/

