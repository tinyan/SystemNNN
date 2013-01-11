//
// effectGeoCircle.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectGeoCircle.h"


CEffectGeoCircle::CEffectGeoCircle(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectGeoCircle::~CEffectGeoCircle()
{
	End();
}

void CEffectGeoCircle::End(void)
{
}

BOOL CEffectGeoCircle::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int para[25];
	int k = paraKosuu;
	if (k>25) k = 25;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = screenSizeX/2;	//centerXEnd
	if (paraKosuu<3) para[2] = screenSizeY/2;	//centerYEnd

	if (paraKosuu<4) para[3] = 100;	//rxEnd
	if (paraKosuu<5) para[4] = 100;	//ryEnd

	if (paraKosuu<6) para[5] = 128;	//drEnd
	if (paraKosuu<7) para[6] = 128;	//dgEnd
	if (paraKosuu<8) para[7] = 128;	//dbEnd

	if (paraKosuu<9) para[8] = 100;	//‰ÁŽZ—¦End


	if (paraKosuu<10) para[9] = para[1];	//centerXStart
	if (paraKosuu<11) para[10] = para[2];	//centerYStart
	if (paraKosuu<12) para[11] = 0;	//type
	if (paraKosuu<13) para[12] = 0;	//subFrame

	if (paraKosuu<14) para[13] = para[3];	//rxStart
	if (paraKosuu<15) para[14] = para[4];	//ryStart
	if (paraKosuu<16) para[15] = 0;	//type
	if (paraKosuu<17) para[16] = 0;	//subFrame

	if (paraKosuu<18) para[17] = para[5];	//drStart
	if (paraKosuu<19) para[18] = para[6];	//dgStart
	if (paraKosuu<20) para[19] = para[7];	//dbStart
	if (paraKosuu<21) para[20] = 0;	//type
	if (paraKosuu<22) para[21] = 0;	//subFrame

	if (paraKosuu<23) para[22] = para[8];	//‰ÁŽZ—¦Start
	if (paraKosuu<24) para[23] = 0;	//type
	if (paraKosuu<25) para[24] = 0;	//subFrame


	lp->flag = TRUE;
	for (i=0;i<25;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_GEOCIRCLE;

	return TRUE;
}


BOOL CEffectGeoCircle::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectGeoCircle::BeginPrint(LPVOID para,int layer)
{

}

void CEffectGeoCircle::Init(LPVOID para,int layer)
{
}

void CEffectGeoCircle::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectGeoCircle::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int count = lp->count;
	int countMax = lp->countMax;


	int centerXEnd = lp->para[1];
	int centerYEnd = lp->para[2];
	int rxEnd = lp->para[3];
	int ryEnd = lp->para[4];
	int drEnd = lp->para[5];
	int dgEnd = lp->para[6];
	int dbEnd = lp->para[7];
	int daEnd = lp->para[8];


	int centerXStart = lp->para[9];
	int centerYStart = lp->para[10];
	int centerType = lp->para[11];
	int centerSubFrame = lp->para[12];

	int rxStart = lp->para[13];
	int ryStart = lp->para[14];
	int rType = lp->para[15];
	int rSubFrame = lp->para[16];

	int drStart = lp->para[17];
	int dgStart = lp->para[18];
	int dbStart = lp->para[19];
	int rgbType = lp->para[20];
	int rgbSubFrame = lp->para[21];

	int daStart = lp->para[22];
	int daType = lp->para[23];
	int daSubFrame = lp->para[24];


	int centerX = CCalcuSpeed::calcu(count,countMax,centerXStart,centerXEnd,centerSubFrame,centerType);
	int centerY = CCalcuSpeed::calcu(count,countMax,centerYStart,centerYEnd,centerSubFrame,centerType);

	int rx = CCalcuSpeed::calcu(count,countMax,rxStart,rxEnd,rSubFrame,rType);
	int ry = CCalcuSpeed::calcu(count,countMax,ryStart,ryEnd,rSubFrame,rType);

	int dr = CCalcuSpeed::calcu(count,countMax,drStart,drEnd,rgbSubFrame,rgbType);
	int dg = CCalcuSpeed::calcu(count,countMax,dgStart,dgEnd,rgbSubFrame,rgbType);
	int db = CCalcuSpeed::calcu(count,countMax,dbStart,dbEnd,rgbSubFrame,rgbType);


	int colA = CCalcuSpeed::calcu(count,countMax,daStart,daEnd,daSubFrame,daType);


	CAllGeo::TransCircleFill(centerX,centerY,rx,ry,dr,dg,db,colA);
//	CAllGeo::TransCircleFill(cx1,cy1,rx1,ry1,colR,colG,colB,100);
}


BOOL CEffectGeoCircle::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectGeoCircle::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}


