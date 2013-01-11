//
// effectflash.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectflash.h"


CEffectFlash::CEffectFlash(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectFlash::~CEffectFlash()
{
	End();
}

void CEffectFlash::End(void)
{
}

BOOL CEffectFlash::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>6) k = 6;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 1;
	if (paraKosuu<3) para[2] = para[1];
	if (paraKosuu<4) para[3] = 255;
	if (paraKosuu<5) para[4] = para[3];
	if (paraKosuu<6) para[5] = para[4];

	lp->countMax = para[0];
	for (i=0;i<6;i++) lp->para[i] = para[i];

	lp->flag = TRUE;
	lp->command = EFFECT_FLASH;
	lp->count = 0;

	return TRUE;
}


BOOL CEffectFlash::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	lp->command = EFFECT_FILL;

	lp->para[1] = lp->para[3];
	lp->para[2] = lp->para[4];
	lp->para[3] = lp->para[5];

	return TRUE;
}


void CEffectFlash::BeginPrint(LPVOID para,int layer)
{

}

void CEffectFlash::Init(LPVOID para,int layer)
{
}

void CEffectFlash::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectFlash::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int onTime = lp->para[1];
	int offTime = lp->para[2];
	int r = lp->para[3];
	int g = lp->para[4];
	int b = lp->para[5];

	int dv = onTime + offTime;
	if (dv<1)
	{
		dv = 1;
//		c = 1;
	}

	int count = lp->count;
	if ((count % dv)>=onTime) return;

	CAllGraphics::FillScreen(r,g,b);
}
