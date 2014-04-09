//
// effectkonoha.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectKonoha.h"



CEffectKonoha::CEffectKonoha(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	for (int i=0;i<360;i++)
	{
		double th = (double)i;
		th /= 360.0;
		th *= 3.14159*2;

		double cosTH = cos(th) * 256;
		double sinTH = sin(th) * 256;

		m_cossinTable[i*2] = (int)(cosTH + 0.5);
		m_cossinTable[i*2+1] = (int)(sinTH + 0.5);
	}
}


CEffectKonoha::~CEffectKonoha()
{
	End();
}

void CEffectKonoha::End(void)
{
}

BOOL CEffectKonoha::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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

	if (paraKosuu<1) para[0] = 20;	//frame dumy
	para[0] = 999999;

	if (paraKosuu<2) para[1] = 32;	//sizeX
	if (paraKosuu<3) para[2] = 32;	//sizeY

	if (paraKosuu<4) para[3] = 1;	//パーツ種類
	if (paraKosuu<5) para[4] = 1;	//パーツ角度種類

	if (paraKosuu<6) para[5] = 100;	//こすう
	if (paraKosuu<7) para[6] = 3;	//ぶんかつ
	if (paraKosuu<8) para[7] = 7;	//dr
	if (paraKosuu<9) para[8] = 15;	//dth
	
	if (paraKosuu<10) para[9] = 0;	//かいしr
	if (paraKosuu<11) para[10] = 1000;//終了r
	
	if (paraKosuu<12) para[11] = 0;//初期非表示マイナス値

	if (paraKosuu<13) para[12] = screenSizeX / 2;
	if (paraKosuu<14) para[13] = screenSizeY / 2;


	lp->flag = TRUE;
	lp->command = EFFECT_KONOHA;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectKonoha::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectKonoha::BeginPrint(LPVOID para,int layer)
{

}

void CEffectKonoha::Init(LPVOID para,int layer)
{
}

void CEffectKonoha::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int c = lp->count;
	if (c > 10000)
	{
		c = lp->para[11];
		lp->count = c;
	}
}


void CEffectKonoha::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;


	int sizeX = lp->para[1];
	int sizeY = lp->para[2];
	int partsShurui = lp->para[3];
	int partsAngleShurui = lp->para[4];
	int kosuu = lp->para[5];
	int bunkatsu = lp->para[6];
	int deltaR = lp->para[7];
	int deltaTH = lp->para[8];
	int startR = lp->para[9];
	int endR = lp->para[10];
	int divR = endR - startR;
	if (divR<0) divR *= -1;
	if (divR == 0) divR = 1;
	int startMinus = lp->para[11];
	int centerX = lp->para[12];
	int centerY = lp->para[13];

	int sizeX2 = sizeX / 2;
	int sizeY2 = sizeY / 2;

	int bunkatsuDeltaTH = 360 / bunkatsu;
	int dbth = 0;
	int partsAngleDiv = 360 / partsAngleShurui;
	int partsAngleDiv2 = partsAngleDiv / 2;

	for (int i=0;i<kosuu;i++)
	{
		int k = c+i - startMinus;

		dbth += bunkatsuDeltaTH;
		dbth %= 360;

		if (k<0) continue;

		int r = k * deltaR;
		r %= divR;

		if (endR >= startR)
		{
			r += startR;
		}
		else
		{
			r *= -1;
			r += startR;
			if (r<0) r = 0;
		}

		int th = k * deltaTH;
		th %= 360;

		th += (i * 360) / kosuu;
		th += dbth;
		th %= 360;

		int dx = (m_cossinTable[th*2] * r) / 256;
		int dy = (m_cossinTable[th*2+1] * r) / 256;

		int x = centerX + dx - sizeX2;
		int y = centerY + dy - sizeY2;

		int srcX = 0;
		int srcY = 0;


		if ((x>=-sizeX) && (y>=-sizeY) && (x < (screenSizeX+sizeX)) && (y < (screenSizeY+sizeY)))
		{
			if (partsShurui > 1)
			{
				srcY = sizeY * (i % partsShurui);
			}

			if (partsAngleShurui > 1)
			{
				int th2 = th + partsAngleDiv2;
				th2 %= 360;
				th2 /= partsAngleDiv;
				th2 %= partsAngleShurui;

				srcX = sizeX * th2;
			}

			lpPic->Blt(x,y,srcX,srcY,sizeX,sizeY,TRUE);
		}
	}

}

BOOL CEffectKonoha::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


/*_*/

