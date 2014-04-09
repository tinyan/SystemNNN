//
// effectbossdeath.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectbossdeath.h"


CEffectBossDeath::CEffectBossDeath(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectBossDeath::~CEffectBossDeath()
{
	End();
}

void CEffectBossDeath::End(void)
{
}

BOOL CEffectBossDeath::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>11) k = 11;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;	//初期おちないフレーム
	if (paraKosuu<3) para[2] = 8;	//ゆれはば
	if (paraKosuu<4) para[3] = para[2];	//最小ゆれはば
	if (paraKosuu<5) para[4] = 0;	//speedType
	if (paraKosuu<6) para[5] = 0;	//subFrame

	if (paraKosuu<7) para[6] = 0;	//半透明フラグ
	if (paraKosuu<8) para[7] = 50;	//終了半透明
	if (paraKosuu<9) para[8] = para[7];	//開始半透明
	if (paraKosuu<10) para[9] = 0;	//半透明スピードタイプ
	if (paraKosuu<11) para[10] = 0;	//半透明サブフレーム


	if (para[1] >= para[0]) para[1] = para[0]-1;


	for (i=0;i<11;i++)
	{
		lp->para[i] = para[i];
	}

	lp->flag = TRUE;
	lp->command = EFFECT_BOSSDEATH;
	lp->count = 0;
	lp->countMax = para[0];

	return TRUE;
}


BOOL CEffectBossDeath::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	lp->flag = FALSE;
	lp->command = EFFECT_NOP;
//	lp->notTransFlag = m_effect->CheckBGLayer(layer);
	lp->notTransFlag = m_allEffect->CheckBGLayer(layer);




	return TRUE;
}


void CEffectBossDeath::BeginPrint(LPVOID para,int layer)
{

}

void CEffectBossDeath::Init(LPVOID para,int layer)
{
}

void CEffectBossDeath::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectBossDeath::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;



//	if (paraKosuu<1) para[0] = 20;	//frame
//	if (paraKosuu<2) para[1] = 0;	//初期おちないフレーム
//	if (paraKosuu<3) para[2] = 8;	//ゆれはば
//	if (paraKosuu<4) para[3] = para[2];	//最小ゆれはば
//	if (paraKosuu<5) para[4] = 0;	//speedType
//	if (paraKosuu<6) para[5] = 0;	//subFrame

//	if (paraKosuu<7) para[6] = 0;	//半透明フラグ
//	if (paraKosuu<8) para[7] = 50;	//終了半透明
//	if (paraKosuu<9) para[8] = para[7];	//開始半透明
//	if (paraKosuu<10) para[9] = 0;	//半透明スピードタイプ
//	if (paraKosuu<11) para[10] = 0;	//半透明サブフレーム

	int count = lp->count;
	int countMax = lp->countMax;
	int startKeepFrame = lp->para[1];
	int minYure = lp->para[3];
	int maxYure = lp->para[2];
	int yureSpeedType = lp->para[4];
	int yureSubFrame = lp->para[5];
	
	int yure = CCalcuSpeed::calcu(count,countMax,minYure,maxYure,yureSubFrame,yureSpeedType);

	int transFlag = lp->para[6];
	int startTransPercent = lp->para[8];
	int endTransPercent = lp->para[7];
	int transSpeedType = lp->para[9];
	int transSubFrame = lp->para[10];
	
	int transPercent = CCalcuSpeed::calcu(count,countMax,startTransPercent,endTransPercent,transSubFrame,transSpeedType);

	int pic = lp->pic;
	if (pic == -1) return;



	CPicture* lpPic = m_allEffect->GetPicture(layer);	//debug 2005-05-08
	if (lpPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);
	int sizeX = rc.right;
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int yStart = 0;
	if (count >= startKeepFrame)
	{
		int dv = countMax - startKeepFrame;
		if (dv<1) dv = 1;
		int c = count - startKeepFrame;
		if (c<0) c = 0;
		if (c>dv) c = dv;
		yStart = (c * screenSizeY) / dv;
	}

	if (yStart>=screenSizeY) return;

	int yLen = screenSizeY - yStart;

	int x0 = lp->dst.left;
	int y0 = lp->dst.top;



	for (int j=0;j<yLen;j++)
	{
		int x = x0;
		if (yure > 0)
		{
			x += ( (rand() % (yure*2)) - yure);
		}

		int y = yStart + j;

		if (transFlag == 0)
		{
			lpPic->Blt(x,y,0,j,sizeX,1,TRUE);
		}
		else
		{
			lpPic->TransLucentBlt3(x,y,0,j,sizeX,1,transPercent);
		}
	}
}


BOOL CEffectBossDeath::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

/*_*/

