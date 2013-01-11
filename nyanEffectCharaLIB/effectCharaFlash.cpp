//
// effectCharaFlash.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectCharaFlash.h"


CEffectCharaFlash::CEffectCharaFlash(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectCharaFlash::~CEffectCharaFlash()
{
	End();
}

void CEffectCharaFlash::End(void)
{
}

BOOL CEffectCharaFlash::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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
	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 255;
	if (paraKosuu<3) para[2] = para[1];
	if (paraKosuu<4) para[3] = para[2];

	if (paraKosuu < 5) para[4] = 1;
	if (paraKosuu < 6) para[5] = 1;


	if (para[4]<1) para[4] = 1;
	if (para[5]<1) para[5] = 1;


	lp->flag = TRUE;
	for (i=0;i<6;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_CHARAFLASH;

	return TRUE;
}


BOOL CEffectCharaFlash::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectCharaFlash::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCharaFlash::Init(LPVOID para,int layer)
{
}

void CEffectCharaFlash::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectCharaFlash::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int r = lp->para[1] & 0xff;
	int g = lp->para[2] & 0xff;
	int b = lp->para[3] & 0xff;

	int count = lp->count;
	int countMax = lp->countMax;

//char mes[256];
//sprintf(mes,"[%d %d]",count,countMax);
//OutputDebugString(mes);

	int putX = lp->dst.left;
	int putY = lp->dst.top;
	int srcX = lp->src.left;
	int srcY = lp->src.top;
	int sizeX = lp->dst.right;
	int sizeY = lp->dst.bottom;


	int pic = lp->pic;
	if (pic == -1) return;


	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int dv = lp->para[4] + lp->para[5];
	if (dv<1) dv = 1;
	int amari = count % dv;


	if ((count>=countMax) || (amari < lp->para[4]))
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);	//’Êí
	}
	else
	{
		lpPic->ShapeBlt(putX,putY,srcX,srcY,sizeX,sizeY,r,g,b);
	}
}


BOOL CEffectCharaFlash::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectCharaFlash::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


