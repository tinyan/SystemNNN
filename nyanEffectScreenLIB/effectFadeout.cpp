//
// effectfadeout.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectfadeout.h"


CEffectFadeout::CEffectFadeout(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectFadeout::~CEffectFadeout()
{
	End();
}

void CEffectFadeout::End(void)
{
}

BOOL CEffectFadeout::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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
	lp->command = EFFECT_FADEOUT;
	lp->count = 0;


	return TRUE;
}


BOOL CEffectFadeout::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	lp->command = EFFECT_FILL;

	int r = lp->para[1];
	int g = lp->para[2];
	int b = lp->para[3];

	lp->para[1] = r;
	lp->para[2] = g;
	lp->para[3] = b;

	return TRUE;
}



void CEffectFadeout::BeginPrint(LPVOID para,int layer)
{

}

void CEffectFadeout::Init(LPVOID para,int layer)
{
}

void CEffectFadeout::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectFadeout::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int count = lp->count;
	int countMax = lp->countMax;
	int subType = lp->para[4];
	int subFrame = lp->para[5];

	int r = lp->para[1];
	int g = lp->para[2];
	int b = lp->para[3];


	int ps2 = CCalcuSpeed::calcu(count,countMax,0,100,subFrame,subType);
	int ps1 = 100-ps2;

	CAllGraphics::Fade(ps1,r,g,b,ps2);
}



/*_*/

