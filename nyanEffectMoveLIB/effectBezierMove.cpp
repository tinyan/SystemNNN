//
// effectBezierMove.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectBezierMove.h"

//
//–¢ŽÀ‘•
//

CEffectBezierMove::CEffectBezierMove(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectBezierMove::~CEffectBezierMove()
{
	End();
}

void CEffectBezierMove::End(void)
{
}

BOOL CEffectBezierMove::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[11];
	int k = paraKosuu;
	if (k>11) k = 11;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 1;	//frame

	if (paraKosuu<2) para[1] = 0;
	if (paraKosuu<3) para[2] = 0;
	if (paraKosuu<4) para[3] = 200;
	if (paraKosuu<5) para[4] = -100;
	if (paraKosuu<6) para[5] = 300;
	if (paraKosuu<7) para[6] = -200;
	if (paraKosuu<8) para[7] = 400;
	if (paraKosuu<9) para[8] = 100;

	if (paraKosuu<10) para[9] = 0;
	if (paraKosuu<11) para[10] = 0;//subframe



	lp->flag = TRUE;
	for (i=0;i<11;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_BEZIERMOVE;

	return TRUE;
}


BOOL CEffectBezierMove::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectBezierMove::BeginPrint(LPVOID para,int layer)
{

}

void CEffectBezierMove::Init(LPVOID para,int layer)
{
}

void CEffectBezierMove::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectBezierMove::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	float x1 = (float)(lp->para[1]);
	float y1 = (float)(lp->para[2]);
	float x2 = (float)(lp->para[3]);
	float y2 = (float)(lp->para[4]);
	float x3 = (float)(lp->para[5]);
	float y3 = (float)(lp->para[6]);
	float x4 = (float)(lp->para[7]);
	float y4 = (float)(lp->para[8]);

	int c = lp->count;
	int countMax = lp->countMax;

	int type = lp->para[9];
	int subFrame = lp->para[10];
	int s = CCalcuSpeed::calcu(c,countMax,0,10000,subFrame,type);

	float t = (float)s;
	t *= 0.0001f;

	float t3 = t*t*t;
	float t2 = t*t*(1.0f-t);
	float t1 = t*(1.0f-t)*(1.0f-t);
	float t0 = (1.0f-t)*(1.0f-t)*(1.0f-t);

	float x = t0*x1 + 3.0f*t1*x2 + 3.0f*t2*x3 + t3*x4;
	float y = t0*y1 + 3.0f*t1*y2 + 3.0f*t2*y3 + t3*y4;

	int deltaX = (int)(x+0.5f);
	int deltaY = (int)(y+0.5f);

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	POINT pt = m_allEffect->GetDstPoint(layer);
	int putX = pt.x;
	int putY = pt.y;
	int srcX = 0;
	int srcY = 0;
	SIZE sz = lpPic->GetPicSize();
	int sizeX = sz.cx;
	int sizeY = sz.cy;


	BOOL flg = TRUE;
	if (m_allEffect->CheckBGLayer(layer)) flg = FALSE;

	lpPic->Blt(putX+deltaX,putY+deltaY,srcX,srcY,sizeX,sizeY,flg);
}


BOOL CEffectBezierMove::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectBezierMove::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


