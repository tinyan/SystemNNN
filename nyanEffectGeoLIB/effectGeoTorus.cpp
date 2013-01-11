//
// effectGeoTorus.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectGeoTorus.h"


CEffectGeoTorus::CEffectGeoTorus(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectGeoTorus::~CEffectGeoTorus()
{
	End();
}

void CEffectGeoTorus::End(void)
{
}

BOOL CEffectGeoTorus::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int para[33];
	int k = paraKosuu;
	if (k>33) k = 33;
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

	if (paraKosuu<6) para[5] = screenSizeX/2;	//centerXEnd2
	if (paraKosuu<7) para[6] = screenSizeY/2;	//centerYEnd2

	if (paraKosuu<8) para[7] = 50;	//rxEnd2
	if (paraKosuu<9) para[8] = 50;	//ryEnd2

	if (paraKosuu<10) para[9] = 128;	//drEnd
	if (paraKosuu<11) para[10] = 128;	//dgEnd
	if (paraKosuu<12) para[11] = 128;	//dbEnd

	if (paraKosuu<13) para[12] = 100;	//‰ÁŽZ—¦End




	if (paraKosuu<14) para[13] = para[1];	//centerXStart
	if (paraKosuu<15) para[14] = para[2];	//centerYStart
	if (paraKosuu<16) para[15] = para[5];	//centerXStart2
	if (paraKosuu<17) para[16] = para[6];	//centerYStart2
	if (paraKosuu<18) para[17] = 0;	//type
	if (paraKosuu<19) para[18] = 0;	//subFrame

	if (paraKosuu<20) para[19] = para[3];	//rxStart
	if (paraKosuu<21) para[20] = para[4];	//ryStart
	if (paraKosuu<22) para[21] = para[7];	//rxStart
	if (paraKosuu<23) para[22] = para[8];	//ryStart
	if (paraKosuu<24) para[23] = 0;	//type
	if (paraKosuu<25) para[24] = 0;	//subFrame

	if (paraKosuu<26) para[25] = para[9];	//drStart
	if (paraKosuu<27) para[26] = para[10];	//dgStart
	if (paraKosuu<28) para[27] = para[11];	//dbStart
	if (paraKosuu<29) para[28] = 0;	//type
	if (paraKosuu<30) para[29] = 0;	//subFrame

	if (paraKosuu<31) para[30] = para[12];	//‰ÁŽZ—¦Start
	if (paraKosuu<32) para[31] = 0;	//type
	if (paraKosuu<33) para[32] = 0;	//subFrame


	lp->flag = TRUE;
	for (i=0;i<33;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_GEOTORUS;

	return TRUE;
}


BOOL CEffectGeoTorus::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectGeoTorus::BeginPrint(LPVOID para,int layer)
{

}

void CEffectGeoTorus::Init(LPVOID para,int layer)
{
}

void CEffectGeoTorus::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectGeoTorus::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int count = lp->count;
	int countMax = lp->countMax;


	int centerXEnd = lp->para[1];
	int centerYEnd = lp->para[2];
	int rxEnd = lp->para[3];
	int ryEnd = lp->para[4];
	int centerXEnd2 = lp->para[5];
	int centerYEnd2 = lp->para[6];
	int rxEnd2 = lp->para[7];
	int ryEnd2 = lp->para[8];

	int drEnd = lp->para[9];
	int dgEnd = lp->para[10];
	int dbEnd = lp->para[11];
	int daEnd = lp->para[12];


	int centerXStart = lp->para[13];
	int centerYStart = lp->para[14];
	int centerXStart2 = lp->para[15];
	int centerYStart2 = lp->para[16];
	int centerType = lp->para[17];
	int centerSubFrame = lp->para[18];

	int rxStart = lp->para[19];
	int ryStart = lp->para[20];
	int rxStart2 = lp->para[21];
	int ryStart2 = lp->para[22];
	int rType = lp->para[23];
	int rSubFrame = lp->para[24];

	int drStart = lp->para[25];
	int dgStart = lp->para[26];
	int dbStart = lp->para[27];
	int rgbType = lp->para[28];
	int rgbSubFrame = lp->para[29];

	int daStart = lp->para[30];
	int daType = lp->para[31];
	int daSubFrame = lp->para[32];


	int centerX = CCalcuSpeed::calcu(count,countMax,centerXStart,centerXEnd,centerSubFrame,centerType);
	int centerY = CCalcuSpeed::calcu(count,countMax,centerYStart,centerYEnd,centerSubFrame,centerType);
	int centerX2 = CCalcuSpeed::calcu(count,countMax,centerXStart2,centerXEnd2,centerSubFrame,centerType);
	int centerY2 = CCalcuSpeed::calcu(count,countMax,centerYStart2,centerYEnd2,centerSubFrame,centerType);

	int rx = CCalcuSpeed::calcu(count,countMax,rxStart,rxEnd,rSubFrame,rType);
	int ry = CCalcuSpeed::calcu(count,countMax,ryStart,ryEnd,rSubFrame,rType);
	int rx2 = CCalcuSpeed::calcu(count,countMax,rxStart2,rxEnd2,rSubFrame,rType);
	int ry2 = CCalcuSpeed::calcu(count,countMax,ryStart2,ryEnd2,rSubFrame,rType);

	int dr = CCalcuSpeed::calcu(count,countMax,drStart,drEnd,rgbSubFrame,rgbType);
	int dg = CCalcuSpeed::calcu(count,countMax,dgStart,dgEnd,rgbSubFrame,rgbType);
	int db = CCalcuSpeed::calcu(count,countMax,dbStart,dbEnd,rgbSubFrame,rgbType);


	int colA = CCalcuSpeed::calcu(count,countMax,daStart,daEnd,daSubFrame,daType);

	CAllGeo::TransTorusFill(centerX,centerY,rx,ry,centerX2,centerY2,rx2,ry2,dr,dg,db,colA);
}


BOOL CEffectGeoTorus::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectGeoTorus::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}


