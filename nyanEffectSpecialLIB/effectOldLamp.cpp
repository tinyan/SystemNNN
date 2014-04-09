//
// EffectOldLamp.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectOldLamp.h"



CEffectOldLamp::CEffectOldLamp(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
}


CEffectOldLamp::~CEffectOldLamp()
{
	End();
}

void CEffectOldLamp::End(void)
{
}

BOOL CEffectOldLamp::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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

	if (paraKosuu<2) para[1] = 20;	//平均ジジジ時間
	if (paraKosuu<3) para[2] = 0;	//平均つき時間
	if (paraKosuu<4) para[3] = 40;	//平均きえ時間

	if (paraKosuu<5) para[4] = 1;	//点灯フレーム
	if (paraKosuu<6) para[5] = 1;	//消灯フレーム

	if (paraKosuu<7) para[6] = 0;	//点灯消灯ランダム


	lp->flag = TRUE;
	lp->command = EFFECT_OLDLAMP;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	lp->para[16] = 0;	//じじじ
	lp->para[17] = 0;


	return TRUE;
}


BOOL CEffectOldLamp::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectOldLamp::BeginPrint(LPVOID para,int layer)
{

}

void CEffectOldLamp::Init(LPVOID para,int layer)
{

}




void CEffectOldLamp::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int c = lp->count;
	if (c > 10000)
	{
		lp->count = 0;
	}

	int jijijiCount = lp->para[17];
	jijijiCount--;
	lp->para[17] = jijijiCount;

	if (jijijiCount < 0)
	{
		int jijijiType = lp->para[16];

		int jijijiTime = lp->para[1];
		int tenTime = lp->para[2];
		int metsuTime = lp->para[3];

		int nextMode = 0;
		int tm = jijijiTime;
		if (jijijiType == 0)
		{
			int dv = tenTime + metsuTime;
			if (dv<1) dv = 1;
			int r = (rand() % dv);
			if (r<tenTime)
			{
				nextMode = 1;
				tm = tenTime;
			}
			else
			{
				nextMode = 2;
				tm = metsuTime;
			}
		}

		lp->para[16] = nextMode;
		int t = tm;
		if (tm>0)
		{
			t += (rand() % tm);
			t -= tm / 2;
		}
		if (t<1) t = 1;

		lp->para[17] = t;
	}
}



void CEffectOldLamp::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int jijijiType = lp->para[16];
	if (jijijiType == 2) return;	//滅

	if (jijijiType == 0)
	{
		int tenTime = lp->para[4];
		int metsuTime = lp->para[5];
		int tenDiv = tenTime + metsuTime;
		if (tenDiv<1) tenDiv = 1;
		
		int jijijiTime = lp->para[17];

		int md = 0;

		if ((jijijiTime % tenDiv) < tenTime) md = 1;
		
		int tenRnd = lp->para[6];
		if (tenRnd > 0)
		{
			if ((rand() % 100) < tenRnd) md = 1-md;
		}

		if (md == 0) return;
	}

	SIZE sz = lpPic->GetPicSize();
	int sizeX = sz.cx;
	int sizeY = sz.cy;
	POINT pt = m_allEffect->GetDstPoint(layer);
	int putX = pt.x;
	int putY = pt.y;

	lpPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
}

BOOL CEffectOldLamp::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


/*_*/

