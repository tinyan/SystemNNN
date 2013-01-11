//
// effectCharaGrey.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectCharaGrey.h"


CEffectCharaGrey::CEffectCharaGrey(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectCharaGrey::~CEffectCharaGrey()
{
	End();
}

void CEffectCharaGrey::End(void)
{
}

BOOL CEffectCharaGrey::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>5) k = 5;
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


	lp->flag = TRUE;
	for (i=0;i<5;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_CHARAGREY;

	return TRUE;
}


BOOL CEffectCharaGrey::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectCharaGrey::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCharaGrey::Init(LPVOID para,int layer)
{
}

void CEffectCharaGrey::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectCharaGrey::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int subType = lp->para[1];
	int subFrame = lp->para[2];
	int endPs = lp->para[3];
	int startPs = lp->para[4];


	int count = lp->count;
	int countMax = lp->countMax;

	int ps256 = CCalcuSpeed::calcu(count,countMax,startPs * 256,endPs*256,subFrame,subType) / 100;
	if (ps256<0) ps256 = 0;
	if (ps256>256) ps256 = 256;


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

	lpPic->GreyBlt2(putX,putY,srcX,srcY,sizeX,sizeY,ps256,TRUE);
}


BOOL CEffectCharaGrey::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectCharaGrey::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


