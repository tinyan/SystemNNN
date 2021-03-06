//
// effectKe.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectKe.h"



CEffectKe::CEffectKe(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
}


CEffectKe::~CEffectKe()
{
	End();
}

void CEffectKe::End(void)
{
}

BOOL CEffectKe::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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

	if (paraKosuu<2) para[1] = 32;	//sizeX
	if (paraKosuu<3) para[2] = 32;	//sizeY

	if (paraKosuu<4) para[3] = 1;	//こすう	max16
	if (para[3]>16) para[3] = 16;

	if (paraKosuu<5) para[4] = 0;	//はりつき方向

	if (paraKosuu<6) para[5] = 1;	//パーツ種類

	if (paraKosuu<7) para[6] = 1;	//パーツアニメパターン
	if (paraKosuu<8) para[7] = 1;	//パーツアニメスピード


	if (paraKosuu<9) para[8] = 30;	//平均表示時間
	if (paraKosuu<10) para[9] = 0;	//平均非表示時間

	if (paraKosuu<11) para[10] = 10;	//ゆれ

	if (paraKosuu<12) para[11] = 100;	//張り付き方向変化確率１００

	lp->flag = TRUE;
	lp->command = EFFECT_KE;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	for (i=0;i<para[3];i++)
	{
		InitKe(lp,i,TRUE);
	}


	return TRUE;
}


BOOL CEffectKe::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectKe::BeginPrint(LPVOID para,int layer)
{

}

void CEffectKe::Init(LPVOID para,int layer)
{

}

void CEffectKe::InitKe(LPVOID lpEffect,int n,BOOL startFlag)
{
	// hyouji,kie,x,y,anime,animecount,houkou
	//

	EFFECT* lp = (EFFECT*)lpEffect;
	int hyoji = lp->para[8];
	int kie = lp->para[9];
	int dv = hyoji + kie;
	if (dv<1)dv = 1;
	int r = rand() % dv;
	
	int k= 16 + n * 8;

	lp->para[k+4] = 0;
	lp->para[k+5] = 0;


	if ((r < hyoji) || (startFlag == FALSE))
	{
		int dv2 = hyoji;
		if (dv2<1) dv2 = 1;
		int r2 = rand() % dv2;
		int c2 = hyoji / 2 + r2;
		if (c2<1) c2 = 1;

		lp->para[k+0] = c2;
	}
	else
	{
		lp->para[k+0] = 0;
	}

	int dv3 = kie;
	if (dv3<1) dv3 = 1;
	int r3 = rand() % dv3;
	int c3 = kie / 2 + r3;
	if (c3<1) c3 = 1;
	lp->para[k+1] = c3;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int sizeX = lp->para[1];
	int sizeY = lp->para[2];

	int x = rand() % screenSizeX;
	int y = rand() % screenSizeY;

	int haritsuki = lp->para[4];
	if (startFlag)
	{
		int houkou = GetHaritsukiHoukou(haritsuki);
		lp->para[k+6] = houkou;
		if (houkou == 1)
		{
			y = sizeY/2;
		}
		else if (houkou == 2)
		{
			x = screenSizeX - sizeX/2;
		}
		else if (houkou == 3)
		{
			y = screenSizeY - sizeY/2;
		}
		else if (houkou == 4)
		{
			x = sizeX/2;
		}
	}

	lp->para[k+2] = x;
	lp->para[k+3] = y;
}



void CEffectKe::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int c = lp->count;
	if (c > 10000)
	{
		lp->count = 0;
	}

	int kosuu = lp->para[3];
	int haritsuki = lp->para[4];
	int animePattern = lp->para[6];
	int animeSpeed = lp->para[7];

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int sizeX = lp->para[1];
	int sizeY = lp->para[2];

	int yure = lp->para[10];

	int haritukiMove100 = lp->para[11];


	for (int i=0;i<kosuu;i++)
	{
		int k = 16 + i * 8;
		int c1 = lp->para[k+0];
		if (c1 > 0)
		{
			c1--;
			lp->para[k+0] = c1;
		}
		else
		{
			int c2 = lp->para[k+1];
			c2--;
			lp->para[k+1] = c2;
			if (c2<=0)
			{
				InitKe(lp,i);
			}
		}

		//anime
		if (animePattern > 1)
		{
			int animeCount = lp->para[k+5];
			animeCount++;
			if (animeCount >= animeSpeed)
			{
				animeCount = 0;
				int pt = lp->para[k+4];
				pt++;
				if (pt >= animePattern)
				{
					pt = 0;
				}
				lp->para[k+4] = pt;
			}
			lp->para[k+5] = animeCount;
		}


		//move
		int x = lp->para[k+2];
		int y = lp->para[k+3];

		x += (rand() % (yure*2+1));
		x -= yure;
		y += (rand() % (yure*2+1));
		y -= yure;
		if (x<0) x = 0;
		if (x>=screenSizeX) x = screenSizeX-1;
		if (y<0) y = 0;
		if (y>=screenSizeY) y = screenSizeY-1;


		if (haritsuki != 0)
		{
			int houkou = lp->para[k+6];
			if (haritukiMove100>0)
			{
				if ((rand() % 10000) < haritukiMove100)
				{
					houkou = GetHaritsukiHoukou(haritsuki);
					lp->para[k+6] = houkou;
				}
			}

			if (houkou == 1)
			{
				y = sizeY/2;
			}
			else if (houkou == 2)
			{
				x = screenSizeX - sizeX/2;
			}
			else if (houkou == 3)
			{
				y = screenSizeY - sizeY/2;
			}
			else if (houkou == 4)
			{
				x = sizeX/2;
			}
		}

		lp->para[k+2] = x;
		lp->para[k+3] = y;
	}
}



void CEffectKe::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;


	int sizeX = lp->para[1];
	int sizeY = lp->para[2];
	int kosuu = lp->para[3];
	int partsShurui = lp->para[5];

	for (int i=0;i<kosuu;i++)
	{
		int k = 16 + i * 8;
		int c1 = lp->para[k+0];
		if (c1 > 0)
		{
			int putX = lp->para[k+2] - sizeX / 2;
			int putY = lp->para[k+3] - sizeY / 2;
			int srcX = (i % partsShurui) * sizeX;
			int srcY = lp->para[k+4] * sizeY;
			lpPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
		}
	}
}

BOOL CEffectKe::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}

int CEffectKe::GetHaritsukiHoukou(int hari)
{
	if (hari == 0) return 0;
	if (hari == 1) return 1;
	if (hari == 2) return 2;
	if (hari == 4) return 3;
	if (hari == 8) return 4;

	int houkou[4];
	int kosuu = 0;
	int bt = 1;
	for (int i=0;i<4;i++)
	{
		if (bt & hari)
		{
			houkou[kosuu] = i+1;
			kosuu++;
		}
		bt <<= 1;
	}

	if (kosuu<1) return 0;

	int r = rand() % kosuu;
	return houkou[r];
}



/*_*/

