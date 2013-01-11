//
// EffectColorAddSub.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectColorAddSub.h"


CEffectColorAddSub::CEffectColorAddSub(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectColorAddSub::~CEffectColorAddSub()
{
	End();
}

void CEffectColorAddSub::End(void)
{
}

BOOL CEffectColorAddSub::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>10) k = 10;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = 0;	//end r
	if (paraKosuu<3) para[2] = para[1];	//end g
	if (paraKosuu<4) para[3] = para[2];	//end b

	if (paraKosuu<5) para[4] = para[1];	//start r
	if (paraKosuu<6) para[5] = para[2];	//start g
	if (paraKosuu<7) para[6] = para[3];	//start b


	if (paraKosuu<8) para[7] = 1;	//transflg
	if (paraKosuu<9) para[8] = 0;	//type
	if (paraKosuu<10) para[9] = 0;	//subframe



	lp->countMax = para[0];
	lp->flag = TRUE;
	lp->command = EFFECT_COLORADDSUB;
	lp->count = 0;

	for (i=0;i<10;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectColorAddSub::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int r = lp->para[1];
	int g = lp->para[2];
	int b = lp->para[3];

	int typ = lp->para[7];

	if ((r == 0) && (g == 0) && (b == 0))
	{
///		lp->command = EFFECT_NOP;
	}

	return TRUE;
}


void CEffectColorAddSub::BeginPrint(LPVOID para,int layer)
{

}

void CEffectColorAddSub::Init(LPVOID para,int layer)
{
}

void CEffectColorAddSub::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectColorAddSub::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;
	int pic = lp->pic;
	if (pic == -1) return;


	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;


	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[8];
	int subFrame = lp->para[9];

	int r1 = lp->para[4];
	int g1 = lp->para[5];
	int b1 = lp->para[6];

	int r2 = lp->para[1];
	int g2 = lp->para[2];
	int b2 = lp->para[3];

	int r = CCalcuSpeed::calcu(count,countMax,r1,r2,subFrame,type);
	int g = CCalcuSpeed::calcu(count,countMax,g1,g2,subFrame,type);
	int b = CCalcuSpeed::calcu(count,countMax,b1,b2,subFrame,type);


//	int dv = lp->countMax;
//	if (dv<1) dv = 1;
//	int c = lp->count;
//	int r = r1 + ((r2 - r1) * c) / dv;
//	int g = g1 + ((g2 - g1) * c) / dv;
//	int b = b1 + ((b2 - b1) * c) / dv;

	int putX = lp->dst.left;
	int putY = lp->dst.top;
	int srcX = lp->src.left;
	int srcY = lp->src.top;
	int sizeX = lp->dst.right;
	int sizeY = lp->dst.bottom;

	BOOL transFlag = TRUE;
	if (lp->para[7] == 0) transFlag = FALSE;

	lpPic->ColorAddBlt(putX,putY,srcX,srcY,sizeX,sizeY,transFlag,r,g,b);
}


BOOL CEffectColorAddSub::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}



