//
// EffectScroll.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectScroll.h"


CEffectScroll::CEffectScroll(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectScroll::~CEffectScroll()
{
	End();
}

void CEffectScroll::End(void)
{
}

BOOL CEffectScroll::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[4];
	int k = paraKosuu;
	if (k>4) k = 4;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 32;
	if (paraKosuu<3) para[2] = 0;
	if (paraKosuu<4) para[3] = 0;	//loopflag

	lp->flag = TRUE;
	lp->command = EFFECT_SCROLL;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<4;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectScroll::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	if (lp->para[3] == 0)
	{
		lp->command = EFFECT_NOP;
	}
	else
	{
		lp->count = 0;
	}

	return TRUE;
}


void CEffectScroll::BeginPrint(LPVOID para,int layer)
{

}

void CEffectScroll::Init(LPVOID para,int layer)
{
}

void CEffectScroll::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	if (lp->para[3] != 0)
	{
		if (lp->count >= lp->countMax)
		{
			lp->count -= lp->countMax;
		}
	}
}


void CEffectScroll::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();

	int c = lp->count;
	int dv = lp->countMax;
	if (dv<1)
	{
		dv = 1;
		c = 1;
	}
//	c = dv - c;

	int dx = lp->para[1] * c;
	int dy = lp->para[2] * c;

//	dx *= -1;
//	dy *= -1;

	if (dx>0)
	{
		dx %= sizeX;
	}
	else
	{
		dx = -dx;
		dx %= sizeX;
		dx = -dx;
		dx += sizeX;
		dx %= sizeX;
	}

	if (dy>0)
	{
		dy %= sizeY;
	}
	else
	{
		dy = -dy;
		dy %= sizeY;
		dy = -dy;
		dy += sizeY;
		dy %= sizeY;
	}


	CPicture* lpPic = m_allEffect->GetPicture(layer);


	for (int j=-1;j<=0;j++)
	{
		for (int i=-1;i<=0;i++)
		{
			lpPic->Blt(dx+i*sizeX,dy+j*sizeY,0,0,sizeX,sizeY,FALSE);
		}
	}

}


