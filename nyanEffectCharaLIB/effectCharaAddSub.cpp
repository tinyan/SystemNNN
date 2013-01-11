//
// effectCharaAddSub.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectCharaAddSub.h"


CEffectCharaAddSub::CEffectCharaAddSub(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectCharaAddSub::~CEffectCharaAddSub()
{
	End();
}

void CEffectCharaAddSub::End(void)
{
}

BOOL CEffectCharaAddSub::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[20];
	int k = paraKosuu;
	if (k>5) k = 5;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 100;	//percent
	if (para[1] < -9999) para[1] = -9999;
	if (para[1] > 9999) para[1] = 9999;
	if (paraKosuu<3) para[2] = para[1];	//start percent
	if (para[2] < -9999) para[2] = -9999;
	if (para[2] > 9999) para[2] = 9999;
	if (paraKosuu<4) para[3] = 0;	//subtype
	if (paraKosuu<5) para[4] = 0;	//esubframe
	


	lp->flag = TRUE;

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_ADDSUB;

	for (i=0;i<5;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectCharaAddSub::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectCharaAddSub::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCharaAddSub::Init(LPVOID para,int layer)
{
}

void CEffectCharaAddSub::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectCharaAddSub::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	EFFECT* lp = (EFFECT*)lpEffect;

	int count = lp->count;
	int countMax = lp->countMax;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;


	int endPercent = lp->para[1];
	int startPercent = lp->para[2];
	int subType = lp->para[3];
	int subFrame = lp->para[4];
	int ps = CCalcuSpeed::calcu(count,countMax,startPercent,endPercent,subFrame,subType);

	int x = lp->dst.left;
	int y = lp->dst.top;
	int srcX = lp->src.left;
	int srcY = lp->src.top;
	int sizeX = lp->dst.right;
	int sizeY = lp->dst.bottom;

	lpPic->AddSubBlt(x,y,srcX,srcY,sizeX,sizeY,ps);
}



BOOL CEffectCharaAddSub::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectCharaAddSub::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


