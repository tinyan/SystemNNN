//
// effectfadein.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectfadein.h"


CEffectFadein::CEffectFadein(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectFadein::~CEffectFadein()
{
	End();
}

void CEffectFadein::End(void)
{
}

BOOL CEffectFadein::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[6];
	int k = paraKosuu;
	if (k>6) k = 6;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}



	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 0;
	if (paraKosuu<3) para[2] = para[1];
	if (paraKosuu<4) para[3] = para[2];
	if (paraKosuu<5) para[4] = 0;
	if (paraKosuu<6) para[5] = 0;

	for (i=0;i<6;i++)
	{
		lp->para[i] = para[i];
	}

	lp->countMax = para[0];
	lp->flag = TRUE;
	lp->command = EFFECT_FADEIN;
	lp->count = 0;


	return TRUE;
}


BOOL CEffectFadein::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	lp->command = EFFECT_NOP;


	if (lp->pic == -1)
	{
		lp->flag = FALSE;
		lp->notTransFlag = m_allEffect->CheckBGLayer(layer);
	}
	return TRUE;
}



void CEffectFadein::BeginPrint(LPVOID para,int layer)
{

}

void CEffectFadein::Init(LPVOID para,int layer)
{
}

void CEffectFadein::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectFadein::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();
	EFFECT* lp = (EFFECT*)lpEffect;

	int count = lp->count;
	int countMax = lp->countMax;
	int subType = lp->para[4];
	int subFrame = lp->para[5];

	int ps1 = CCalcuSpeed::calcu(count,countMax,0,100,subFrame,subType);
	int ps2 = 100-ps1;

	int r = lp->para[1];
	int g = lp->para[2];
	int b = lp->para[3];

	CAllGraphics::Fade(ps1,r,g,b,ps2);
}



/*_*/

