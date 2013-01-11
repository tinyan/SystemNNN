//
// effectTarget1.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectTarget1.h"


#define Target1_KOSUU_MAX 600
#define Target1_SCALE 256

CEffectTarget1::CEffectTarget1(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
}


CEffectTarget1::~CEffectTarget1()
{
	End();
}

void CEffectTarget1::End(void)
{
}

BOOL CEffectTarget1::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	
	if (paraKosuu<2) para[1] = screenSizeX / 4;
	if (paraKosuu<3) para[2] = screenSizeY / 4;
	if (paraKosuu<4) para[3] = screenSizeX / 2;
	if (paraKosuu<5) para[4] = screenSizeY / 2;

	if (paraKosuu<6) para[5] = 1;	//line

	if (paraKosuu<7) para[6] = 255;	//r
	if (paraKosuu<8) para[7] = 255;	//g
	if (paraKosuu<9) para[8] = 255;	//b

	if (paraKosuu<10) para[9] = 0;	//printtype


	if (paraKosuu<11) para[10] = 0;//type
	if (paraKosuu<12) para[11] = 0;//subframe

	if (paraKosuu<13) para[12] = 0;//開始割合
	if (paraKosuu<14) para[13] = 50;//半透明使用時%

	if (para[1]<0) para[1] = 0;
	if (para[1] >= screenSizeX) para[1] = screenSizeX-1;
	if (para[2]<0) para[2] = 0;
	if (para[2] >= screenSizeY) para[2] = screenSizeY-1;

	if (para[1] + para[3] > screenSizeX) para[3] = screenSizeX - para[1];
	if (para[2] + para[4] > screenSizeY) para[4] = screenSizeY - para[2];

	if (para[3]<1) para[3] = 1;
	if (para[4]<1) para[4] = 1;

	if (para[5]<1) para[5] = 1;
	if (para[5] > screenSizeX) para[5] = screenSizeX;
	if (para[6] > screenSizeY) para[5] = screenSizeY;


	lp->flag = TRUE;
	lp->command = EFFECT_TARGET1;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectTarget1::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectTarget1::BeginPrint(LPVOID para,int layer)
{

}

void CEffectTarget1::Init(LPVOID para,int layer)
{
}

void CEffectTarget1::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectTarget1::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int start = lp->para[12];
	int subFrame = lp->para[11];
	int speedType = lp->para[10];

	int ps100 = CCalcuSpeed::calcu(c,dv,start*100,10000,subFrame,speedType);

	int colR = lp->para[6];
	int colG = lp->para[7];
	int colB = lp->para[8];
	int printType = lp->para[9];

	int lineSize = lp->para[5];

	int startX1 = 0;
	int startX2 = screenSizeX - lineSize;
	int startY1 = 0;
	int startY2 = screenSizeY - lineSize;

	int endX1 = lp->para[1];
	int endX2 = lp->para[1] + lp->para[3] - lineSize;
	int endY1 = lp->para[2];
	int endY2 = lp->para[2] + lp->para[4] - lineSize;


	int x1 = startX1 + ((endX1-startX1) * ps100) / 10000;
	int x2 = startX2 + ((endX2-startX2) * ps100) / 10000;
	int y1 = startY1 + ((endY1-startY1) * ps100) / 10000;
	int y2 = startY2 + ((endY2-startY2) * ps100) / 10000;

	RECT rc[4];
	SetRect(&rc[0],x1,0,lineSize,screenSizeY);
	SetRect(&rc[1],x2,0,lineSize,screenSizeY);
	SetRect(&rc[2],0,y1,screenSizeX,lineSize);
	SetRect(&rc[3],0,y2,screenSizeX,lineSize);


	int transPercent = lp->para[13];

	for (int i=0;i<4;i++)
	{
		int x = rc[i].left;
		int y = rc[i].top;
		int sizeX = rc[i].right;
		int sizeY = rc[i].bottom;


		if (printType == 0)
		{
			CAllGeo::BoxFill(x,y,sizeX,sizeY,colR,colG,colB);
		}
		else if (printType == 1)
		{
			CAllGeo::TransBoxFill(x,y,sizeX,sizeY,colR,colG,colB,transPercent);
		}
		else
		{
			CAllGeo::AddBoxFill(x,y,sizeX,sizeY,colR,colG,colB);
		}
	}
}



/*_*/

