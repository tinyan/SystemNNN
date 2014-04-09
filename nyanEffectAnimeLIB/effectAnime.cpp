//
// effectAnime.cpp
//

#include "..\nyanEffectLib\includer.h"


#include "effectAnime.h"


CEffectAnime::CEffectAnime(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectAnime::~CEffectAnime()
{
	End();
}

void CEffectAnime::End(void)
{
}

BOOL CEffectAnime::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[17];
	int k = paraKosuu;
	if (k>17) k = 17;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 4;	//pattern数
	if (paraKosuu<3) para[2] = 1;	//length
	if (paraKosuu<4) para[3] = 0;	//loop flag
	if (paraKosuu<5) para[4] = 12;	//start buffer
	if (paraKosuu<6) para[5] = 0;	//trans flag
	if (paraKosuu<7) para[6] = 100;	//半透明終了
	if (paraKosuu<8) para[7] = para[6];	//半透明開始
	if (paraKosuu<9) para[8] = 0;	//speedtype
	if (paraKosuu<10) para[9] = 10;	//subframe
	if (paraKosuu<11) para[10] = 0;//永続エフェクトフラグ




//	if (paraKosuu<17) para[16] = 0;	//無限ループ用
	//max 9 pattern?



	if (para[1]<1) para[1] = 1;
	if (para[2]<1) para[2] = 1;


	lp->flag = TRUE;
	lp->command = EFFECT_ANIME;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<17;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}







BOOL CEffectAnime::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

//	lp->command = EFFECT_NOP;
//	if (lp->pic == -1)
//	{
//		lp->flag = FALSE;
//	}
//
//	return TRUE;
	return FALSE;
}


void CEffectAnime::BeginPrint(LPVOID para,int layer)
{

}

void CEffectAnime::Init(LPVOID para,int layer)
{
}

void CEffectAnime::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	if (lp->para[10])
	{
		int dv = lp->para[1] * lp->para[2];
		if (dv<1) dv = 1;

		int c = lp->count;
		c %= dv;
		lp->count = c;
	}
}


void CEffectAnime::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int* dst = CMyGraphics::GetScreenBuffer();


	int count = lp->count;
	int countMax = lp->countMax;
	int patternKosuu = lp->para[1];
	int frameLength = lp->para[2];
	int loopFlag = lp->para[3];

	int dv = frameLength;
	if (dv<1) dv = 1;

	int koma = count / dv;
	if (loopFlag)
	{
		if (patternKosuu>0)
		{
			koma %= patternKosuu;
		}
	}
	else
	{
		if (koma >= patternKosuu) koma = patternKosuu-1;
	}


	int bufferNumber = lp->para[4] + koma;
	if (bufferNumber < 0) bufferNumber = 0;
	if (bufferNumber > 15) bufferNumber = 15;

	CPicture* lpPic = m_allEffect->GetPicture(bufferNumber);
	if (lpPic == NULL) return;

	POINT dstPoint = m_allEffect->GetDstPoint(bufferNumber);
	POINT srcPoint = m_allEffect->GetSrcPoint(bufferNumber);
	SIZE sz = m_allEffect->GetDstSize(bufferNumber);

	int putX = dstPoint.x;
	int putY = dstPoint.y;
	int srcX = srcPoint.x;
	int srcY = srcPoint.y;
	int sizeX = sz.cx;
	int sizeY = sz.cy;


	int transFlag = lp->para[5];



	if (lp->para[4] == 0)
	{
		lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,FALSE);
	}
	else
	{
		int ps1 = lp->para[7];
		int ps2 = lp->para[6];
		int speedType = lp->para[8];
		int subFrame = lp->para[9];

		int ps = CCalcuSpeed::calcu(count,countMax,ps1,ps2,subFrame,speedType);

		if (lp->para[4] == 1)
		{
			lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
		}
		else
		{
			lpPic->TransLucentBlt3(putX,putY,srcX ,srcY ,sizeX,sizeY,ps);
		}
	}
}



BOOL CEffectAnime::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}
