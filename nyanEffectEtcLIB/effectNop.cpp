//
// EffectNop.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectNop.h"


CEffectNop::CEffectNop(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectNop::~CEffectNop()
{
	End();
}

void CEffectNop::End(void)
{
}

BOOL CEffectNop::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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

	lp->flag = TRUE;

	lp->count = 0;
	lp->countMax = 99999;
	lp->command = EFFECT_NOP;

	return TRUE;
}


BOOL CEffectNop::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectNop::BeginPrint(LPVOID para,int layer)
{

}

void CEffectNop::Init(LPVOID para,int layer)
{
}

void CEffectNop::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectNop::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;
	return;


}

BOOL CEffectNop::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

