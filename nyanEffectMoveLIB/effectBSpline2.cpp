//
// effectBSpline2.cpp
//

#include "..\nyanEffectLib\includer.h"
#include "effectBSpline2.h"

//
//–¢ŽÀ‘•
//

CEffectBSpline2::CEffectBSpline2(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectBSpline2::~CEffectBSpline2()
{
	End();
}

void CEffectBSpline2::End(void)
{
}

BOOL CEffectBSpline2::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[9];
	int k = paraKosuu;
	if (k>9) k = 9;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 1;	//frame

	if (paraKosuu<2) para[1] = 0;
	if (paraKosuu<3) para[2] = 0;
	if (paraKosuu<4) para[3] = 200;
	if (paraKosuu<5) para[4] = -200;
	if (paraKosuu<6) para[5] = 400;
	if (paraKosuu<7) para[6] = 100;

	if (paraKosuu<8) para[7] = 0;
	if (paraKosuu<9) para[8] = 0;//subframe



	lp->flag = TRUE;
	for (i=0;i<9;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_BSPLINE2;

	return TRUE;
}


BOOL CEffectBSpline2::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectBSpline2::BeginPrint(LPVOID para,int layer)
{

}

void CEffectBSpline2::Init(LPVOID para,int layer)
{
}

void CEffectBSpline2::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectBSpline2::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	float x1 = (float)(lp->para[1]);
	float y1 = (float)(lp->para[2]);
	float x2 = (float)(lp->para[3]);
	float y2 = (float)(lp->para[4]);
	float x3 = (float)(lp->para[5]);
	float y3 = (float)(lp->para[6]);

	int c = lp->count;
	int countMax = lp->countMax;

	int type = lp->para[7];
	int subFrame = lp->para[8];
	int s = CCalcuSpeed::calcu(c,countMax,0,10000,subFrame,type);

	float t = (float)s;
	t *= 0.0001f;

	float t2 = t*t;
	float t1 = t*(1.0f-t);
	float t0 = (1.0f-t)*(1.0f-t);

	float x = t0*x1 + 2.0f*t1*x2 + t2*x3;
	float y = t0*y1 + 2.0f*t1*y2 + t2*y3;

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


BOOL CEffectBSpline2::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectBSpline2::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


