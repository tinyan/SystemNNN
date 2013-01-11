//
// EffectTrans.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectTrans.h"


CEffectTrans::CEffectTrans(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectTrans::~CEffectTrans()
{
	End();
}

void CEffectTrans::End(void)
{
}

BOOL CEffectTrans::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[3];
	int k = paraKosuu;
	if (k>2) k = 2;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//dummy
	if (paraKosuu<2) para[1] = 50;

	lp->countMax = 1;
	lp->command = EFFECT_TRANS;
	lp->count = 0;
	lp->para[0] = para[0];
	lp->para[1] = para[1];

	return TRUE;
}


BOOL CEffectTrans::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	return TRUE;


	if (lp->para[1] == 100)
	{
		lp->command = EFFECT_NOP;
	}
	else if (lp->para[1] == 0)
	{
		lp->flag = FALSE;
		lp->command = EFFECT_NOP;
		lp->notTransFlag = m_allEffect->CheckBGLayer(layer);
	}
	else
	{
		lp->para[0] = lp->para[1];
	}


	return TRUE;
}


void CEffectTrans::BeginPrint(LPVOID para,int layer)
{

}

void CEffectTrans::Init(LPVOID para,int layer)
{
}

void CEffectTrans::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectTrans::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;
	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int dv = lp->countMax;
	if (dv<1) dv = 1;
	int c = lp->count;

	//int ps = lp->para[0] + ((lp->para[1] - lp->para[0]) * c + dv / 2) / dv;
	int ps = lp->para[1];// + ((lp->para[1] - lp->para[0]) * c + dv / 2) / dv;
	if (ps<0) ps = 0;
	if (ps>100) ps = 100;

	int x = lp->dst.left;
	int y = lp->dst.top;
	int srcX = lp->src.left;
	int srcY = lp->src.top;
	int sizeX = lp->dst.right;
	int sizeY = lp->dst.bottom;

	if (lp->notTransFlag)
	{
		lpPic->TransLucentBlt(x ,y ,srcX ,srcY ,sizeX,sizeY,ps);
	}
	else
	{
		lpPic->TransLucentBlt3(x ,y ,srcX ,srcY ,sizeX,sizeY,ps);
	}
}


BOOL CEffectTrans::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

BOOL CEffectTrans::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

