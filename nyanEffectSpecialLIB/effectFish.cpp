//
// EffectFish.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "EffectFish.h"



CEffectFish::CEffectFish(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
}


CEffectFish::~CEffectFish()
{
	End();
}

void CEffectFish::End(void)
{
}

BOOL CEffectFish::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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

	if (paraKosuu<1) para[0] = 20;	//frame dumy
	para[0] = 999999;

	if (paraKosuu<2) para[1] = 1;	//‚±‚·‚¤	max48
	if (para[1]>40) para[1] = 40;

	if (paraKosuu<3) para[2] = 32;	//sizeX
	if (paraKosuu<4) para[3] = 32;	//sizeY


	if (paraKosuu<5) para[4] = 0;	//…‘…‚˜
	if (paraKosuu<6) para[5] = 0;	//…‘…‚™

	if (paraKosuu<7) para[6] = screenSizeX;	//…‘…‚³‚¢‚¸‚˜
	if (paraKosuu<8) para[7] = screenSizeY;	//…‘…‚³‚¢‚¸‚™


	if (paraKosuu<9) para[8] = 1;	//‚³‚©‚È‚µ‚ã‚é‚¢
	if (paraKosuu<10) para[9] = 1;	//‚³‚©‚È‚ ‚É‚ß‚Ï‚½[‚ñ
	if (paraKosuu<11) para[10] = 1;	//‚ ‚É‚ß‚Ó‚ê[‚Þ

	if (paraKosuu<12) para[11] = 1;	//‚³‚¢‚Ä‚¢‚»‚­‚Ç
	if (paraKosuu<13) para[12] = 3;	//‚³‚¢‚±‚¤‚»‚­‚Ç
	if (para[12]<para[11]) para[12] = para[11];

	if (paraKosuu<14) para[13] = 100;	//•Ï‰»Šm—¦x100



	lp->flag = TRUE;
	lp->command = EFFECT_FISH;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	for (i=0;i<para[1];i++)
	{
		InitFish(lp,i,TRUE);
	}


	return TRUE;
}


BOOL CEffectFish::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectFish::BeginPrint(LPVOID para,int layer)
{

}

void CEffectFish::Init(LPVOID para,int layer)
{

}

void CEffectFish::InitFish(LPVOID lpEffect,int n,BOOL startFlag)
{
	// x,y,speedx,count


	EFFECT* lp = (EFFECT*)lpEffect;

	int sizeX = lp->para[2];
	int sizeY = lp->para[3];
	int suisouX = lp->para[4];
	int suisouY = lp->para[5];
	int suisouSizeX = lp->para[6];
	int suisouSizeY = lp->para[7];

	int minSpeed = lp->para[11];
	int maxSpeed = lp->para[12];

	int k = 16 + 4 * n;

	int dx = suisouSizeX - sizeX;
	if (dx<1) dx = 1;
	lp->para[k+0] = suisouX + (rand() % dx);

	int dy = suisouSizeY - sizeY;
	if (dy<1) dy = 1;
	lp->para[k+1] = suisouY + (rand() % dy);


	int sdv = maxSpeed - minSpeed + 1;
	if (sdv<1) sdv = 1;
	int sp = minSpeed + (rand() % sdv);

	if ((rand() % 100) < 50) sp *= -1;
	lp->para[k+2] = sp;

	lp->para[k+3] = 0;
}



void CEffectFish::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int c = lp->count;
	if (c > 10000)
	{
		lp->count = 0;
	}

	int kosuu = lp->para[1];

	int sizeX = lp->para[2];
	int sizeY = lp->para[3];
	int suisouX = lp->para[4];
	int suisouY = lp->para[5];
	int suisouSizeX = lp->para[6];
	int suisouSizeY = lp->para[7];

	int minSpeed = lp->para[11];
	int maxSpeed = lp->para[12];

	int sdv = maxSpeed - minSpeed + 1;
	if (sdv<1) sdv = 1;

	int rndSpeed = lp->para[13];

	int animePattern = lp->para[9];
	int animeFrame = lp->para[10];

	int anime = animePattern * animeFrame;
	if (anime<1) anime = 1;

	for (int i=0;i<kosuu;i++)
	{
		int k = 16 + 4 * i;

		int sp = lp->para[k+2];

		if (rndSpeed>0)
		{
			if ((rand() % 10000) < rndSpeed)
			{
				sp = minSpeed + (rand() % sdv);
				if ((rand() % 100) < 50) sp *= -1;
				lp->para[k+2] = sp;
				lp->para[k+3] = 0;

				int y = lp->para[k+1];
				y += (rand() % 5);
				y -= 2;
				if (y<suisouY)
				{
					y = suisouY;
				}

				if (y+sizeY>suisouY+suisouSizeY)
				{
					y = suisouY + suisouSizeY - sizeY;
				}

				lp->para[k+1] = y;
			}
		}

		int x = lp->para[k+0];
		x += lp->para[k+2];

		if (x<suisouX)
		{
			x = suisouX;
			if (sp<0)
			{
				sp *= -1;
			}
		}

		if (x+sizeX>suisouX+suisouSizeX)
		{
			x = suisouX + suisouSizeX - sizeX;
			if (sp>0)
			{
				sp *= -1;
			}
		}

		lp->para[k+2] = sp;
		lp->para[k] = x;

		lp->para[k+3]++;
		lp->para[k+3] %= anime;
	}
}



void CEffectFish::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int kosuu = lp->para[1];

	int sizeX = lp->para[2];
	int sizeY = lp->para[3];

	int fishType = lp->para[8];
	int animePattern = lp->para[9];
	int animeFrame = lp->para[10];

	if (animeFrame<1) animeFrame = 1;

	int adiv = animePattern * animeFrame;
	if (adiv<1) adiv = 1;

	for (int i=0;i<kosuu;i++)
	{
		int k = 16 + i * 4;
		int x = lp->para[k+0];
		int y = lp->para[k+1];
		int sp = lp->para[k+2];

		int srcX = 0;
		if (sp>0) srcX = sizeX;
		int srcY = 0;

		if (fishType > 1)
		{
			srcX += sizeX*2*(i % fishType);
		}

		if (animePattern>1)
		{
			srcY += sizeY * ((lp->para[k+3] % adiv) / animeFrame);
		}

		lpPic->Blt(x,y,srcX,srcY,sizeX,sizeY,TRUE);
	}

}

BOOL CEffectFish::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


/*_*/

