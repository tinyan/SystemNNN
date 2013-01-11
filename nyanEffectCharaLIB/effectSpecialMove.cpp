//
// effectSpecialMove.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectSpecialMove.h"


CEffectSpecialMove::CEffectSpecialMove(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectSpecialMove::~CEffectSpecialMove()
{
	End();
}

void CEffectSpecialMove::End(void)
{
}

BOOL CEffectSpecialMove::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[37];
	int k = paraKosuu;
	if (k>37) k = 37;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;	//movetype
	if (paraKosuu<3) para[2] = 1;	//transFlag 0,1

	if (paraKosuu<4) para[3] = 1;	//loop
	if (paraKosuu<5) para[4] = para[0];	//moveframe
	if (paraKosuu<6) para[5] = 0;	//movesubtype
	if (paraKosuu<7) para[6] = 0;	//movesubframe
	
	if (paraKosuu<8) para[7] = 0;	//dx1
	if (paraKosuu<9) para[8] = 0;	//dy1
	if (paraKosuu<10) para[9] = 0;	//dx2
	if (paraKosuu<11) para[10] = 0;	//dy2

	if (paraKosuu<13) para[11] = 100;	//trandEnd
	if (paraKosuu<14) para[12] = para[11];	//trandStart

	if (paraKosuu<15) para[13] = para[3];	//transloop
	if (paraKosuu<15) para[14] = para[4];	//transframe
	if (paraKosuu<16) para[15] = para[5];	//transsubtype
	if (paraKosuu<17) para[16] = para[6];	//transsubframe

	if (paraKosuu<18) para[17] = 0;	//work1
	if (paraKosuu<19) para[18] = 0;	//work2

	if (paraKosuu < 20) para[19] = para[3];//stretchloop
	if (paraKosuu < 21) para[20] = para[4];//frame
	if (paraKosuu < 22) para[21] = para[5];//subtype
	if (paraKosuu < 23) para[22] = para[6];//subframe

	if (paraKosuu < 24) para[23] = 100;//mulXEnd
	if (paraKosuu < 25) para[24] = 100;//mulYEnd
	if (paraKosuu < 26) para[25] = para[23];//mulXStart
	if (paraKosuu < 27) para[26] = para[24];//mulYStart

	if (paraKosuu < 28) para[27] = para[3];//addsubloop
	if (paraKosuu < 29) para[28] = para[4];//frame
	if (paraKosuu < 30) para[29] = para[5];//subtype
	if (paraKosuu < 31) para[30] = para[6];//subframe
	
	if (paraKosuu < 32) para[31] = 0;//rEnd
	if (paraKosuu < 33) para[32] = 0;//gEnd
	if (paraKosuu < 34) para[33] = 0;//bEnd
	if (paraKosuu < 35) para[34] = para[31];//rStart
	if (paraKosuu < 36) para[35] = para[32];//rStart
	if (paraKosuu < 37) para[36] = para[33];//rStart

	//addsubloop,frame,type,subframe
	//r,g,b,r,g,b

	//work3,work4

	lp->flag = TRUE;

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_SPECIALMOVE;

	for (i=0;i<37;i++)
	{
		lp->para[i] = para[i];
	}

	lp->para[17] = 0;
	lp->para[18] = 0;
	lp->para[62] = 0;
	lp->para[63] = 0;

	return TRUE;
}


BOOL CEffectSpecialMove::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectSpecialMove::BeginPrint(LPVOID para,int layer)
{

}

void CEffectSpecialMove::Init(LPVOID para,int layer)
{
}

void CEffectSpecialMove::Calcu(LPVOID lpEffect,int layer)
{
	return;

	EFFECT* lp = (EFFECT*)lpEffect;

	int count1 = lp->para[17];
	int loop1 = lp->para[3];
	int countMax1 = lp->para[4];

	int count2 = lp->para[18];
	int loop2 = lp->para[13];
	int countMax2 = lp->para[14];

	int count3 = lp->para[62];
	int loop3 = lp->para[19];
	int countMax3 = lp->para[20];

	int count4 = lp->para[63];
	int loop4 = lp->para[27];
	int countMax4 = lp->para[28];

	if (count1<0) count1 = 0;
	if (count2<0) count2 = 0;
	if (count3<0) count3 = 0;
	if (count4<0) count4 = 0;
	
	if (countMax1<1) countMax1 = 1;
	if (countMax2<1) countMax2 = 1;
	if (countMax3<1) countMax3 = 1;
	if (countMax4<1) countMax4 = 1;

	count1++;
	count2++;
	count3++;
	count4++;

	if (count1 >= countMax1)
	{
		if (loop1)
		{
			count1 %= countMax1; 
		}
		else
		{
			count1 = countMax1;
		}
	}

	if (count2 >= countMax2)
	{
		if (loop2)
		{
			count2 %= countMax2;
		}
		else
		{
			count2 = countMax2;
		}
	}

	if (count3 >= countMax3)
	{
		if (loop3)
		{
			count3 %= countMax3;
		}
		else
		{
			count3 = countMax3;
		}
	}

	if (count4 >= countMax4)
	{
		if (loop4)
		{
			count4 %= countMax4;
		}
		else
		{
			count4 = countMax4;
		}
	}

	lp->para[17] = count1;
	lp->para[18] = count2;
	lp->para[62] = count3;
	lp->para[63] = count4;
}


void CEffectSpecialMove::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	EFFECT* lp = (EFFECT*)lpEffect;


	int count1 = lp->para[17];
	int countMax1 = lp->para[4];
	int loop1 = lp->para[3];

	int count2 = lp->para[18];
	int countMax2 = lp->para[14];
	int loop2 = lp->para[13];

	int count3 = lp->para[62];
	int countMax3 = lp->para[20];
	int loop3 = lp->para[19];

	int count4 = lp->para[63];
	int countMax4 = lp->para[28];
	int loop4 = lp->para[27];

	if (countMax1 < 1) countMax1 = 1;
	if (countMax2 < 1) countMax2 = 1;
	if (countMax3 < 1) countMax3 = 1;
	if (countMax4 < 1) countMax4 = 1;

	int moveType = lp->para[1];
	int moveSubType = lp->para[5];
	int moveSubFrame = lp->para[6];

//	count1++;
//	count2++;
//	count3++;
//	count4++;

	count1 = lp->count;
	count2 = lp->count;
	count3 = lp->count;
	count4 = lp->count;


	if (count1 >= countMax1)
	{
		if (loop1)
		{
			count1 %= countMax1; 
		}
		else
		{
			count1 = countMax1;
		}
	}

	if (count2 >= countMax2)
	{
		if (loop2)
		{
			count2 %= countMax2;
		}
		else
		{
			count2 = countMax2;
		}
	}

	if (count3 >= countMax3)
	{
		if (loop3)
		{
			count3 %= countMax3;
		}
		else
		{
			count3 = countMax3;
		}
	}

	if (count4 >= countMax4)
	{
		if (loop4)
		{
			count4 %= countMax4;
		}
		else
		{
			count4 = countMax4;
		}
	}


	if (count1<0) count1 = 0;
	if (count2<0) count2 = 0;
	if (count3<0) count3 = 0;
	if (count4<0) count4 = 0;
	if (count1 > countMax1) count1 = countMax1;
	if (count2 > countMax2) count2 = countMax2;
	if (count3 > countMax3) count3 = countMax3;
	if (count4 > countMax4) count4 = countMax4;

	lp->para[17] = count1;
	lp->para[18] = count2;
	lp->para[62] = count3;
	lp->para[63] = count4;


	int transSubType = lp->para[15];
	int transSubFrame = lp->para[16];

	int transStart = lp->para[12];
	int transEnd = lp->para[11];

	int trans = transStart;
	if (transStart != transEnd)
	{
		trans = CCalcuSpeed::calcu(count2,countMax2,transStart,transEnd,transSubFrame,transSubType);
	}

	int stretchSubType = lp->para[21];
	int stretchSubFrame = lp->para[22];
	int multiStartX = lp->para[25];
	int multiStartY = lp->para[26];
	int multiEndX = lp->para[23];
	int multiEndY = lp->para[24];

	double multiX = 0.001 * (double)(CCalcuSpeed::calcu(count3,countMax3,multiStartX*10,multiEndX*10,stretchSubFrame,stretchSubType));
	double multiY = 0.001 * (double)(CCalcuSpeed::calcu(count3,countMax3,multiStartY*10,multiEndY*10,stretchSubFrame,stretchSubType));

	BOOL multiFlag = FALSE;
	if ((multiStartX != 100) || (multiEndX != 100) || (multiStartY != 100) || (multiEndY != 100))
	{
		multiFlag = TRUE;
	}


	int addSubSubType = lp->para[29];
	int addSubSubFrame = lp->para[30];
	int deltaStartR = lp->para[34];
	int deltaStartG = lp->para[35];
	int deltaStartB = lp->para[36];
	int deltaEndR = lp->para[31];
	int deltaEndG = lp->para[32];
	int deltaEndB = lp->para[33];

	int deltaR = CCalcuSpeed::calcu(count4,countMax4,deltaStartR,deltaEndR,addSubSubFrame,addSubSubType);
	int deltaG = CCalcuSpeed::calcu(count4,countMax4,deltaStartG,deltaEndG,addSubSubFrame,addSubSubType);
	int deltaB = CCalcuSpeed::calcu(count4,countMax4,deltaStartB,deltaEndB,addSubSubFrame,addSubSubType);

	BOOL addSubFlag = FALSE;
	if ((deltaStartR != 0) || (deltaStartG != 0) || (deltaStartB != 0) || (deltaEndR != 0) || (deltaEndG != 0) || (deltaEndB != 0))
	{
		addSubFlag = TRUE;
	}

	int dx1 = lp->para[7];
	int dy1 = lp->para[8];
	int dx2 = lp->para[9];
	int dy2 = lp->para[10];


	RECT dstRect = lp->dst;
	int dstX = dstRect.left;
	int dstY = dstRect.top;

	int moveCount1000 = CCalcuSpeed::calcu(count1,countMax1,0,1000,moveSubFrame,moveSubType);

	int dx = 0;
	int dy = 0;

	if (moveType == 0)
	{
		dx = dx1 + (dx2 - dx1) * (moveCount1000) / 1000;
		dy = dy1 + (dy2 - dy1) * (moveCount1000) / 1000;
	}
	else if (moveType == 1)
	{
		double th = (double)moveCount1000;
		th *= 3.14159;
		th /= 1000.0;
		double cc = (1.0-cos(th)) * 0.5;
		if (cc<0.0) cc = 0.0;
		if (cc>1.0) cc = 1.0;

		double ddx = (double)(dx2-dx1);
		ddx *= cc;
		dx = dx1 + (int)(ddx+0.5);

		double ddy = (double)(dy2-dy1);
		ddy *= cc;
		dy = dy1 + (int)(ddy+0.5);
	}
	else if (moveType == 2)
	{
		double t = (double)moveCount1000;
		t *= 0.001;
		double ddx = 2.0*t*(1.0-t)*((double)(dx1))+t*t*((double)(dx2));
		double ddy = 2.0*t*(1.0-t)*((double)(dy1))+t*t*((double)(dy2));

		dx = (int)(ddx+0.5);
		dy = (int)(ddy+0.5);
	}


	dstX += dx;
	dstY += dy;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	if (trans == 0) return;

	BOOL transFlag = TRUE;
	if (lp->para[2] == 0) transFlag = FALSE;

	SIZE sz = lpPic->GetPicSize();
	int sizeX = sz.cx;
	int sizeY = sz.cy;
	
	if (multiFlag == FALSE)
	{
		if (addSubFlag == FALSE)
		{
			if (trans == 100)
			{
				lpPic->Blt(dstX,dstY,0,0,sizeX,sizeY,transFlag);
			}
			else
			{
				lpPic->TransLucentBlt3(dstX,dstY,0,0,sizeX,sizeY,trans);
			}
		}
		else
		{
			lpPic->ColorAddBlt(dstX,dstY,0,0,sizeX,sizeY,transFlag,deltaR,deltaG,deltaB,trans);
		}
	}
	else
	{
		int dstSizeX = (int)(0.5+multiX * (double)sizeX);
		int dstSizeY = (int)(0.5+multiY * (double)sizeY);

		if ((dstSizeX <= 0) || (dstSizeY <= 0)) return;

		int dstDeltaX = (sizeX - dstSizeX) / 2;
		int dstDeltaY = (sizeY - dstSizeY) / 2;

		dstX += dstDeltaX;
		dstY += dstDeltaY;

		if (addSubFlag == FALSE)
		{
			lpPic->StretchBlt1(dstX,dstY,dstSizeX,dstSizeY,0,0,sizeX,sizeY,trans,transFlag);
		}
		else
		{
#if !defined _TINYAN3DLIB_
			lpPic->StretchAddSubBlt(dstX,dstY,dstSizeX,dstSizeY,0,0,sizeX,sizeY,trans,transFlag,deltaR,deltaG,deltaB);
#else
			lpPic->StretchBlt1(dstX,dstY,dstSizeX,dstSizeY,0,0,sizeX,sizeY,trans,transFlag);
#endif

		}

	}



}


BOOL CEffectSpecialMove::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectSpecialMove::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


