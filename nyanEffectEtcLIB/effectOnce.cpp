//
// effectOnce.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectOnce.h"



CEffectOnce::CEffectOnce(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_onceFlag = new BOOL[16];
}


CEffectOnce::~CEffectOnce()
{
	End();
}

void CEffectOnce::End(void)
{
	DELETEARRAY(m_onceFlag);
}


void CEffectOnce::InitParameter(LPVOID lpEffect, int layer)
{
	int para[16];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<16;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,16,para,layer);
}

BOOL CEffectOnce::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	if (layer == -1) layer = 0;

	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;
	if (paraKosuu<3) para[2] = 1;

	lp->flag = TRUE;
	lp->command = EFFECT_ONCE;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	m_onceFlag[layer] = FALSE;

	return TRUE;
}


BOOL CEffectOnce::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectOnce::BeginPrint(LPVOID para,int layer)
{

}

void CEffectOnce::Init(LPVOID para,int layer)
{
}

void CEffectOnce::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectOnce::Print(LPVOID lpEffect,int layer)
{
	if (layer == -1) layer = 0;
	m_onceFlag[layer] = TRUE;
}


BOOL CEffectOnce::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	if (layer == -1) layer = 0;

	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
	}

	int st = lp->para[1];
	int sz = lp->para[2];

	if ((c>=st) && (c<(st+sz))) return TRUE;
	if (m_onceFlag[layer] == FALSE) return TRUE;

	return FALSE;
}


/*_*/

