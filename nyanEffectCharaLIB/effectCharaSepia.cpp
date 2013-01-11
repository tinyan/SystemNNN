//
// effectCharaSepia.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectCharaSepia.h"


CEffectCharaSepia::CEffectCharaSepia(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectCharaSepia::~CEffectCharaSepia()
{
	End();
}

void CEffectCharaSepia::End(void)
{
}

BOOL CEffectCharaSepia::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>8) k = 8;
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

	if (paraKosuu<6) para[5] = 107;	//start r
	if (paraKosuu<7) para[6] = 74;	//start g
	if (paraKosuu<8) para[7] = 43;	//start b


	lp->flag = TRUE;
	for (i=0;i<8;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_SEPIA;

	return TRUE;
}


BOOL CEffectCharaSepia::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectCharaSepia::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCharaSepia::Init(LPVOID para,int layer)
{
}

void CEffectCharaSepia::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectCharaSepia::Print(LPVOID lpEffect,int layer)
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


	int r = lp->para[5];
	int g = lp->para[6];
	int b = lp->para[7];

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

	lpPic->SepiaBlt(putX,putY,srcX,srcY,sizeX,sizeY,ps256,r,g,b,TRUE);
}


BOOL CEffectCharaSepia::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectCharaSepia::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


