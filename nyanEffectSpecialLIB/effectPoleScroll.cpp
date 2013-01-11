//
// effectPoleScroll.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectPoleScroll.h"


CEffectPoleScroll::CEffectPoleScroll(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectPoleScroll::~CEffectPoleScroll()
{
	End();
}

void CEffectPoleScroll::End(void)
{
}

BOOL CEffectPoleScroll::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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
	if (paraKosuu<1) para[1] = 20;
	if (paraKosuu<2) para[1] = 32;
	if (paraKosuu<3) para[2] = 0;
	if (paraKosuu<4) para[3] = 1;

	lp->flag = TRUE;
	lp->para[0] = para[0];
	lp->para[1] = para[1];
	lp->para[2] = para[2];
	lp->para[3] = para[3];

	lp->para[12] = 0;//count old
	lp->para[13] = 1;//deltacount
	lp->para[14] = 0;//dx
	lp->para[15] = 0;//dy

	lp->count = 0;
	lp->countMax = 9999;
	lp->command = EFFECT_POLESCROLL;

	return TRUE;
}


BOOL CEffectPoleScroll::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectPoleScroll::BeginPrint(LPVOID para,int layer)
{

}

void CEffectPoleScroll::Init(LPVOID para,int layer)
{
}

void CEffectPoleScroll::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int oldCount = lp->para[12];
	int newCount = lp->count;
	int deltaCount = newCount - oldCount;

	if (lp->count >= lp->countMax)
	{
		if (lp->para[3] == 0)
		{
			lp->count = lp->countMax;
			deltaCount = 0;
		}
		else
		{
			int dv = lp->countMax;
			if (dv<1) dv = 1;
			int count = lp->count;
			count %= dv;
			lp->count = count;
		}
	}
	lp->para[12] = lp->count;
	lp->para[13] = deltaCount;

	int deltaX = lp->para[14];
	int deltaY = lp->para[15];
	int dx = lp->para[1];
	int dy = lp->para[2];

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	deltaX += dx * deltaCount;
	deltaY += dy * deltaCount;
	if (deltaX >= 0)
	{
		deltaX %= screenSizeX;
	}
	else
	{
		deltaX *= -1;
		deltaX %= screenSizeX;
		deltaX *= -1;
	}

	if (deltaY >= 0)
	{
		deltaY %= screenSizeY;
	}
	else
	{
		deltaY *= -1;
		deltaY %= screenSizeY;
		deltaY *= -1;
	}

	lp->para[14] = deltaX;
	lp->para[15] = deltaY;
}


void CEffectPoleScroll::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int deltaX = lp->para[14];
	int deltaY = lp->para[15];

	if (deltaX < 0) deltaX += screenSizeX;
	if (deltaY < 0) deltaY += screenSizeY;

	int sx = deltaX;
	int sy = deltaY;
	int sx2 = screenSizeX-deltaX;
	int sy2 = screenSizeY-deltaY;

	CPicture* lpPic = m_allEffect->GetPicture(layer);


	for (int j=-1;j<=0;j++)
	{
		for (int i=-1;i<=0;i++)
		{
			lpPic->Blt(deltaX+i*screenSizeX,deltaY+j*screenSizeY,0,0,screenSizeX,screenSizeY,FALSE);
		}
	}

}


BOOL CEffectPoleScroll::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectPoleScroll::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


