//
// effectCharaGrey.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectLayerSepia.h"


CEffectLayerSepia::CEffectLayerSepia(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectLayerSepia::~CEffectLayerSepia()
{
	End();
}

void CEffectLayerSepia::End(void)
{
}

BOOL CEffectLayerSepia::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>8) k = 8;
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

	if (paraKosuu<6) para[5] = 107;	//start r
	if (paraKosuu<7) para[6] = 74;	//start g
	if (paraKosuu<8) para[7] = 43;	//start b


	lp->flag = TRUE;
	for (i=0;i<8;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_LAYERSEPIA;

	return TRUE;
}


BOOL CEffectLayerSepia::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectLayerSepia::BeginPrint(LPVOID para,int layer)
{

}

void CEffectLayerSepia::Init(LPVOID para,int layer)
{
}

void CEffectLayerSepia::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectLayerSepia::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int subType = lp->para[1];
	int subFrame = lp->para[2];
	int endPs = lp->para[3];
	int startPs = lp->para[4];


	int r = lp->para[5];
	int g = lp->para[6];
	int b = lp->para[7];

	int count = lp->count;
	int countMax = lp->countMax;

	int ps256 = CCalcuSpeed::calcu(count,countMax,startPs * 256,endPs*256,subFrame,subType) / 100;
	if (ps256<0) ps256 = 0;
	if (ps256>256) ps256 = 256;

	CAllGraphics::LayerSepia(ps256,r,g,b);
}


BOOL CEffectLayerSepia::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectLayerSepia::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}



