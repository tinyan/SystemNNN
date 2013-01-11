//
// effectCharaBure.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectCharaBure.h"


CEffectCharaBure::CEffectCharaBure(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectCharaBure::~CEffectCharaBure()
{
	End();
}

void CEffectCharaBure::End(void)
{
}

BOOL CEffectCharaBure::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[20];
	int k = paraKosuu;
	if (k>8) k = 8;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 4;	//burex
	if (para[1] < 0) para[1] = 0;
	if (paraKosuu<3) para[2] = 4;	//burey
	if (para[2] < 0) para[2] = 0;

	if (paraKosuu<4) para[3] = 8;	//buretime
	if (paraKosuu<5) para[4] = 50;	//buresizerandom
	if (paraKosuu<6) para[5] = 50;	//buretimerandom
	
	if (paraKosuu<7) para[6] = 0;//subType
	if (paraKosuu<8) para[7] = 0;//subFrame

	lp->flag = TRUE;

	lp->count = 0;
	lp->countMax = lp->para[0];
	lp->command = EFFECT_CHARABURE;

	for (i=0;i<8;i++)
	{
		lp->para[i] = para[i];
	}

	lp->para[20] = 0;//dummy
	lp->para[21] = 1;//dummy
	lp->para[22] = 0;
	lp->para[23] = 0;
	lp->para[24] = 0;
	lp->para[25] = 0;
	CalcuNewBure(lp);

	return TRUE;
}


BOOL CEffectCharaBure::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectCharaBure::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCharaBure::Init(LPVOID para,int layer)
{
}

void CEffectCharaBure::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	lp->para[20]++;
	if (lp->para[20] > lp->para[21])
	{
		CalcuNewBure(lp);
	}
}


void CEffectCharaBure::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	EFFECT* lp = (EFFECT*)lpEffect;

	int count = lp->para[20];
	int countMax = lp->para[21];
	int dxStart = lp->para[22];
	int dyStart = lp->para[23];
	int dxEnd = lp->para[24];
	int dyEnd = lp->para[25];

	int subType = lp->para[6];
	int subFrame = lp->para[7];

	int dx = CCalcuSpeed::calcu(count,countMax,dxStart,dxEnd,subFrame,subType);
	int dy = CCalcuSpeed::calcu(count,countMax,dyStart,dyEnd,subFrame,subType);


	int x = lp->dst.left;
	int y = lp->dst.top;
	int srcX = lp->src.left;
	int srcY = lp->src.top;
	int sizeX = lp->dst.right;
	int sizeY = lp->dst.bottom;


	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int putX = x + dx;
	int putY = y + dy;

	BOOL flg = TRUE;
	if ((layer < 4) || (layer == 14))
	{
		flg = FALSE;
	}
	lpPic->Put(putX,putY,flg);
}


BOOL CEffectCharaBure::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectCharaBure::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectCharaBure::CalcuNewBure(LPVOID lpEffect)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	lp->para[22] = lp->para[24];
	lp->para[23] = lp->para[25];

	int bureX = lp->para[1];
	int bureY = lp->para[2];
	int bureTime = lp->para[3];

	int bureXYRandom = lp->para[4];
	int bureTimeRandom = lp->para[5];

	int divX = bureX * bureXYRandom;
	if (divX < 1) divX = 1;
	int divY = bureY * bureXYRandom;
	if (divY < 1) divY = 1;
	int divT = bureTime * bureTimeRandom;
	if (divT < 1) divT = 1;

	int dx = bureX * 100 - (rand() % divX);
	int dy = bureY * 100 - (rand() % divY);
	int dt = bureTime * 100 - (rand() % divT);

	dx /= 100;
	dy /= 100;
	dt /= 100;

	if ((rand() % 100) < 50)
	{
		dx *= -1;
	}
	if ((rand() % 100) < 50)
	{
		dy *= -1;
	}

	lp->para[24] = dx;
	lp->para[25] = dy;
	lp->para[21] = dt;

	lp->para[20] = 0;
}


