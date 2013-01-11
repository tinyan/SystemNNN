//
// effectSoyosoyo.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectSoyosoyo.h"


CEffectSoyosoyo::CEffectSoyosoyo(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetConstKosuu(2);
	SetTextureKosuu(2);
	Create("Soyosoyo");
#endif
}


CEffectSoyosoyo::~CEffectSoyosoyo()
{
	End();
}

void CEffectSoyosoyo::End(void)
{
}

BOOL CEffectSoyosoyo::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>13) k = 13;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 20;	//loop
	if (paraKosuu<3) para[2] = 10;	//right yure
	if (paraKosuu<4) para[3] = 10;	//left yure
	if (paraKosuu<5) para[4] = 50;	//往復比率
	if (paraKosuu<6) para[5] = 2;	//透過フラグ				//2
	if (paraKosuu<7) para[6] = 1;	//無限ループフラグ			//1
	if (paraKosuu<8) para[7] = -1;	//pic layer
	if (paraKosuu<9) para[8] = 0;	//上下速度反転

	if (paraKosuu<10) para[9] = 0;	//ちらし幅
	if (paraKosuu<11) para[10] = 1;	//ちらし周期
	if (paraKosuu<12) para[11] = 1;	//ちらしφ


	if (paraKosuu<13) para[12] = 0;	//ちらし初期値(ワーク)


//	m_r = para[0];
//	m_g = para[1];
//	m_b = para[2];


	lp->flag = TRUE;

	for (i=0;i<13;i++)
	{
		lp->para[i] = para[i];
	}

	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_SOYOSOYO;

	return TRUE;
}


BOOL CEffectSoyosoyo::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectSoyosoyo::BeginPrint(LPVOID para,int layer)
{

}

void CEffectSoyosoyo::Init(LPVOID para,int layer)
{
}

void CEffectSoyosoyo::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	if (lp->para[6])
	{
		int dv = lp->para[1];
		if (dv>0)
		{
			int count = lp->count;
			count %= dv;
			lp->count = count;
		}
	}

	lp->para[12] += lp->para[11];
	int dv2 = lp->para[10];
	if (dv2<1) dv2 = 1;
	lp->para[12] %= dv2;
}




void CEffectSoyosoyo::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;
	int loops = lp->para[1];
	double rightYure = (double)(lp->para[2]);
	double leftYure = (double)(lp->para[3]);
	int oufukuPercent = lp->para[4];
	int transMode = lp->para[5];
if (transMode != 2) return;
	int picLayer = lp->para[7];
	int hanten = lp->para[8];
	double chirashi = (double)(lp->para[9]);
	int omega = lp->para[10];
	int fay = lp->para[11];
	int chirashiWorkPara = lp->para[12];

	if (picLayer == -1) picLayer = layer;

	int* dst = CMyGraphics::GetScreenBuffer();

	CPicture* lpPic = m_allEffect->GetPicture(picLayer);
	if (lpPic == NULL) return;




	RECT rc;
	lpPic->GetPicSize(&rc);
	int picSizeX = rc.right;
	int picSizeY = rc.bottom;

	int putX = lp->dst.left;
	int putY = lp->dst.top;
	int srcX = 0;
	int srcY = 0;
	int sizeX = picSizeX;
	int sizeY = picSizeY;

	if (lpPic->Clip(putX,putY,srcX,srcY,sizeX,sizeY) == FALSE) return;


	//clip Y

	if (sizeX<0) return;

	if (putY>=screenSizeY) return;
	if (putY<0)
	{
		srcY += (-putY);
		sizeY -= (-putY);
		putY = 0;
		if (sizeY<=0) return;
	}

	if ((putY+sizeY) > screenSizeY)
	{
		sizeY = screenSizeY - putY;
		if (sizeY<=0) return;
	}



	int c = lp->count;
	if (loops>0)
	{
		c %= loops;
	}
	if (c>=countMax) c = countMax-1;
	if (c<0) c = 0;

//	int work[MAXSCREENSIZEY];
//	int* work = CEffectSimpleWipe::m_shapeWork;
	int* work = m_allEffect->GetTempWork();

	double mulTh = 3.14159 / ((double)sizeY) / 2.0;

	//往復チェック
	int md = 0;
	int check = (oufukuPercent * loops) / 100;
	int dv = check;
	if (c>=check)
	{
		md = 1;
		c -= check;
		dv = loops - check;
	}
	if (dv<1) dv = 1;

	double delta = 0.0;
	double th2 = (double)c;
	th2 /= (double)dv;
	th2 *= 3.14159;
	double ml2 = 1.0 - cos(th2);
	ml2 *= 0.5;

	double mulChirashi = 3.14159 * 2.0 / ((double)omega);



	if (md == 0)
	{
		delta = -leftYure + (rightYure + leftYure) * ml2;
	}
	else
	{
		delta = rightYure - (rightYure + leftYure) * ml2;
	}


	for (int i=0;i<sizeY;i++)
	{
		int k = i;
		if (hanten != 0)
		{
			k = sizeY - i;
		}

		double th = (double)k;


		th *= mulTh;


		double ml = 1.0 - sin(th);

		double tt = 0.0;
		if (chirashi > 0.0)
		{
			int cnt = (i + chirashiWorkPara) % omega;
			double th3 = (double)cnt;
			th3 *= mulChirashi;

			tt = chirashi * cos(th3);


		}

		work[i] = (int)((delta + tt)*ml + 0.5);
	}

#if defined _TINYAN3DLIB_
	if (CheckEffectError()) return;


	float w1 = (float)chirashi;
	if (w1 < 0.0f) w1 *= -1.0f;
	float w2 = (float)delta;
	if (w2 < 0.0f) w2 *= -1.0f;
	float w = (w1 + w2) * 2.0f;
	float limit1 = (float)(lpPic->m_charaClipXStart);
	float limit2 = (float)(lpPic->m_charaClipXEnd);
	float px = (float)picSizeX;
	if (px>0.0f)
	{
		limit1 /= px;
		limit2 /= px;
	}
	else
	{
		limit1 = 0.0f;
		limit2 = 1.0f;
	}

	SetConst(limit1);
	SetConst(limit2,1);

	int ww = (int)w;

	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture());


	int* workV = m_allEffect->GetTempWork();
	workV += screenSizeY;

	float div3 = 1.0f / 3.0f;
	float divSizeX = 1.0f / (float)(picSizeX);

	for (int j=0;j<screenSizeY;j++)
	{
		float x1 = 0.0f;

		if ((j>=putY) && (j<putY+sizeY))
		{
			x1 = (float)(work[j-putY]);
		}

		x1 *= divSizeX;
		x1 += 1.0f;
		x1 *= div3;

		if (x1<0.0f) x1 = 0.0f;
		if (x1>0.995f) x1 = 0.995f;

		int x1Int = (int)(x1*65536.0f);

		unsigned int x1High = x1Int >> 8;
		unsigned int x1Low  = x1Int & 0xff;


		//XRGB -> RGBA
		workV[j] = (int)((0 << 24) | (x1High << 16) | (x1Low<<8) | 0);
	}

	SetWorkV(workV,screenSizeY);
	SetTexture(GetVTexture(),1);

	POINT dstPoint;
	SIZE dstSize;
	POINT srcPoint;

	dstPoint.x = putX - ww;
	dstPoint.y = putY;
	dstSize.cx = sizeX + ww*2;
	dstSize.cy = sizeY;
	srcPoint.x = srcX - ww;
	srcPoint.y = srcY;

	Blt(dstPoint,dstSize,srcPoint);



#else
	lpPic->DeltaBlt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE,work);
#endif
}



BOOL CEffectSoyosoyo::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectSoyosoyo::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


