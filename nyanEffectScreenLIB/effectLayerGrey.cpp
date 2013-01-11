//
// effectCharaGrey.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectLayerGrey.h"


CEffectLayerGrey::CEffectLayerGrey(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectLayerGrey::~CEffectLayerGrey()
{
	End();
}

void CEffectLayerGrey::End(void)
{
}

BOOL CEffectLayerGrey::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>5) k = 5;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;	//type
	if (paraKosuu<3) para[2] = 0;	//subframe
	if (paraKosuu<4) para[3] = 100;	//end ps
	if (paraKosuu<5) para[4] = 0;	//start ps



	lp->flag = TRUE;
	for (i=0;i<5;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_LAYERGREY;

	return TRUE;
}


BOOL CEffectLayerGrey::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectLayerGrey::BeginPrint(LPVOID para,int layer)
{

}

void CEffectLayerGrey::Init(LPVOID para,int layer)
{
}

void CEffectLayerGrey::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectLayerGrey::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int subType = lp->para[1];
	int subFrame = lp->para[2];
	int endPs = lp->para[3];
	int startPs = lp->para[4];


	int count = lp->count;
	int countMax = lp->countMax;

	int ps256 = CCalcuSpeed::calcu(count,countMax,startPs * 256,endPs*256,subFrame,subType) / 100;
	if (ps256<0) ps256 = 0;
	if (ps256>256) ps256 = 256;

	CAllGraphics::LayerGrey(ps256);
}


BOOL CEffectLayerGrey::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectLayerGrey::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}



