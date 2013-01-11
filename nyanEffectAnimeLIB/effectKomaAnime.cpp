//
// effectKomaAnime.cpp
#include "..\nyanEffectLib\includer.h"

#include "..\nyanlib\include\areaControl.h"
#include "effectKomaAnime.h"


CEffectKomaAnime::CEffectKomaAnime(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectKomaAnime::~CEffectKomaAnime()
{
	End();
}

void CEffectKomaAnime::End(void)
{
}

BOOL CEffectKomaAnime::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}



	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 64;	//sizex
	if (paraKosuu<3) para[2] = 64;	//sizey

	if (paraKosuu<4) para[3] = 1;

	if (paraKosuu<5) para[4] = 0;
	if (paraKosuu<6) para[5] = 0;
	if (paraKosuu<7) para[6] = para[4];
	if (paraKosuu<8) para[7] = para[5];
	if (paraKosuu<9) para[8] = 0;
	if (paraKosuu<10) para[9] = 0;
//	if (paraKosuu<11) para[10] = 0;

	if (paraKosuu<11) para[10] = 100;	//透明度終了
	if (paraKosuu<12) para[11] = 100;	//透明度開始

	if (paraKosuu<13) para[12] = 0;	//拡張移動パターン
	if (paraKosuu<14) para[13] = 0;	//拡張移動パターンパラメーター

	if (paraKosuu<15) para[14] = 0;	//無限ループカウンター


	lp->flag = TRUE;
	lp->command = EFFECT_KOMAANIME;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectKomaAnime::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectKomaAnime::BeginPrint(LPVOID para,int layer)
{

}

void CEffectKomaAnime::Init(LPVOID para,int layer)
{
}

void CEffectKomaAnime::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int dv = lp->para[14];
	if (dv>0)
	{
		int c = lp->count;
		c %= dv;
		lp->count = c;
	}
}


void CEffectKomaAnime::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;


	int dv = lp->countMax;
	int c = lp->count;

	if (c>=dv) return;

	dv--;
	if (dv<1)
	{
		dv = 1;
		c = 0;
	}

	if (c>=dv)
	{
		c = dv - 1;
	}
	


	int x1 = lp->para[6];
	int y1 = lp->para[7];
	int x2 = lp->para[4];
	int y2 = lp->para[5];

	int putX = x1 + ((x2 - x1) * c ) / dv;
	int putY = y1 + ((y2 - y1) * c ) / dv;

	int sx = lp->para[1];
	int sy = lp->para[2];

	if ((sx<1) || (sy<1)) return;

	RECT rc;
	lpPic->GetPicSize(&rc);
	int picSizeX = rc.right;
	int picSizeY = rc.bottom;
	if ((picSizeX<=0) || (picSizeY<=0)) return;


	int picKosuuX = picSizeX / sx;
	int picKosuuY = picSizeY / sy;

	if ((picKosuuX<1) || (picKosuuY<1)) return;

	int komaCount = lp->para[3];
	if (komaCount<1) komaCount = 1;

	int koma = c / komaCount;

//	koma += lp->para[10];

	int komaLoop = lp->para[9];
	if (komaLoop>0)
	{
		koma %= komaLoop;
	}

	int partsX = koma % picKosuuX;
	int partsY = koma / picKosuuX;

	int srcX = partsX * sx;
	int srcY = partsY * sy;

	int transFlag = lp->para[8];

	if (transFlag == 0)
	{
		lpPic->Blt(putX,putY,srcX,srcY,sx,sy,FALSE);
	}
	else if (transFlag == 1)
	{
		lpPic->Blt(putX,putY,srcX,srcY,sx,sy,TRUE);
	}
	else if (transFlag == 2)
	{
		int ps1 = lp->para[11];
		int ps2 = lp->para[10];
		int ps = ps1 + ((ps2 - ps1) * c) / dv;
		
		if (ps == 100)
		{
			lpPic->AntiAliasBlt2(putX,putY,srcX,srcY,sx,sy);
		}
		else
		{
			lpPic->TransLucentBlt3(putX,putY,srcX,srcY,sx,sy,ps);
		}
	}
	else
	{
		lpPic->Blt(putX,putY,srcX,srcY,sx,sy,TRUE);	//dummy
	}



	if (CheckAllPrint(lpEffect) == FALSE)
	{
		CAreaControl::AddArea(putX,putY,sx,sy);
	}
}



BOOL CEffectKomaAnime::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

BOOL CEffectKomaAnime::CheckAllPrint(LPVOID lpEffect,int layer)
{
	//移動なし、(移動パターン==0) 透過なし、半透明度100%のときのみFALSE

	EFFECT* lp = (EFFECT*)lpEffect;

	int x1 = lp->para[4];
	int y1 = lp->para[5];
	int x2 = lp->para[6];
	int y2 = lp->para[7];

	if (x1 != x2) return TRUE;
	if (y1 != y2) return TRUE;

	int transFlag = lp->para[8];
	if (transFlag != 0) return TRUE;

	int ps1 = lp->para[11];
	int ps2 = lp->para[12];

	if (ps1 != 100) return TRUE;
	if (ps2 != 100) return TRUE;

	int type = lp->para[13];
	if (type != 0) return TRUE;

	return FALSE;
}