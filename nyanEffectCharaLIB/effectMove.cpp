//
// EffectMove.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectMove.h"


CEffectMove::CEffectMove(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectMove::~CEffectMove()
{
	End();
}

void CEffectMove::End(void)
{
}

BOOL CEffectMove::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[3];
	int k = paraKosuu;
	if (k>1) k = 1;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;

	lp->flag = TRUE;
	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_MOVE;

	return TRUE;
}


BOOL CEffectMove::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	lp->dst = lp->dstTo;
	lp->src = lp->srcTo;
	lp->command = EFFECT_NOP;

	return TRUE;
}


void CEffectMove::BeginPrint(LPVOID para,int layer)
{

}

void CEffectMove::Init(LPVOID para,int layer)
{
}

void CEffectMove::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectMove::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;
	return;


}


BOOL CEffectMove::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}


BOOL CEffectMove::CheckAllPrint(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	if (lp->count >= lp->countMax) return FALSE;

	return TRUE;
}



