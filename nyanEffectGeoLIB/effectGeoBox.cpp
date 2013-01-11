//
// effectGeoBox.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectGeoBox.h"


CEffectGeoBox::CEffectGeoBox(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectGeoBox::~CEffectGeoBox()
{
	End();
}

void CEffectGeoBox::End(void)
{
}

BOOL CEffectGeoBox::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int para[24];
	int k = paraKosuu;
	if (k>24) k = 24;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 20;	//frame


	if (paraKosuu<2) para[1] = 0;	//first wait
	if (paraKosuu<3) para[2] = 0;	//last wait

	if (paraKosuu<4) para[3] = 100;	//rxStart
	if (paraKosuu<5) para[4] = 100;	//ryStart

	if (paraKosuu<6) para[5] = para[3];	//rxEnd
	if (paraKosuu<7) para[6] = para[4];	//ryEnd

	if (paraKosuu<8) para[7] = 128;	//drStart
	if (paraKosuu<9) para[8] = 128;	//dgStart
	if (paraKosuu<10) para[9] = 128;//dbStart

	if (paraKosuu<11) para[10] = para[7];	//drEnd
	if (paraKosuu<12) para[11] = para[8];	//dgEnd
	if (paraKosuu<13) para[12] = para[9];	//dbEnd

	if (paraKosuu<14) para[13] = screenSizeX / 2;	//centerXStart
	if (paraKosuu<15) para[14] = screenSizeY / 2;	//centerYStart

	if (paraKosuu<16) para[15] = para[13];	//centerXEnd
	if (paraKosuu<17) para[16] = para[14];	//centerYEnd

//	if (paraKosuu<18) para[17] = 50;	//rx2Start	(ana)
//	if (paraKosuu<19) para[18] = 50;	//rx2Start	(ana)
//	if (paraKosuu<20) para[19] = para[17];	//rx2Start	(ana)
//	if (paraKosuu<21) para[20] = para[18];	//rx2Start	(ana)



	lp->flag = TRUE;
	for (i=0;i<24;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_GEOBOX;

	return TRUE;
}


BOOL CEffectGeoBox::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectGeoBox::BeginPrint(LPVOID para,int layer)
{

}

void CEffectGeoBox::Init(LPVOID para,int layer)
{
}

void CEffectGeoBox::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectGeoBox::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int count = lp->count;
	int countMax = lp->countMax;

	int firstWait = lp->para[1];
	int lastWait = lp->para[2];

	if (count<firstWait) return;
	if (count>=countMax-lastWait) return;

	int dv = lp->countMax - firstWait - lastWait;
	if (dv<1) return;

	int c = count - firstWait;

	int colRStart = lp->para[7];
	int colGStart = lp->para[8];
	int colBStart = lp->para[9];

	int colREnd = lp->para[10];
	int colGEnd = lp->para[11];
	int colBEnd = lp->para[12];

	int colR = colRStart + ((colREnd - colRStart) * c) / dv;
	int colG = colGStart + ((colGEnd - colGStart) * c) / dv;
	int colB = colBStart + ((colBEnd - colBStart) * c) / dv;

	int rxStart = lp->para[3];
	int ryStart = lp->para[4];
	int rxEnd = lp->para[5];
	int ryEnd = lp->para[6];

	int rx1 = rxStart + ((rxEnd - rxStart) * c) / dv;
	int ry1 = ryStart + ((ryEnd - ryStart) * c) / dv;

	int cxStart = lp->para[13];
	int cyStart = lp->para[14];
	int cxEnd = lp->para[15];
	int cyEnd = lp->para[16];

	int cx1 = cxStart + ((cxEnd - cxStart) * c) / dv;
	int cy1 = cyStart + ((cyEnd - cyStart) * c) / dv;

	CAllGeo::TransBoxFill(cx1,cy1,rx1,ry1,colR,colG,colB,100);
//	CMyGraphics::TransTorusFill(centerX,centerY,rx1,ry1,centerX2,centerY2,rx2,ry2,colR,colG,colB);
}


BOOL CEffectGeoBox::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectGeoBox::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}


