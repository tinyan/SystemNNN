//
// effectRain.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectRain2.h"


CEffectRain2::CEffectRain2(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectRain2::~CEffectRain2()
{
	End();
}

void CEffectRain2::End(void)
{
}

void CEffectRain2::InitParameter(LPVOID lpEffect, int layer)
{
	int para[8];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<8;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,8,para,layer);
}

BOOL CEffectRain2::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[8];
	int k = paraKosuu;

	if (k>8) k = 8;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;

	if (paraKosuu<2) para[1] = 5;	//speedx
	if (paraKosuu<3) para[2] = 30;	//speedy
	if (paraKosuu<4) para[3] = 2;	//kosuu
	if (paraKosuu<5) para[4] = 3;	//randomx
	if (paraKosuu<6) para[5] = 0;	//randomy
	if (paraKosuu<7) para[6] = 50;	//next%
	if (paraKosuu<8) para[7] = 100;	//random 1/100	1-9999

	if (para[7]<1) para[7] = 1;

	if (para[3]<1) para[3] = 1;
	if (para[3]>4) para[3] = 4;



	lp->flag = TRUE;
	lp->command = EFFECT_RAIN2;
	lp->count = 0;
	lp->countMax = para[0];

	for (i=0;i<8;i++)
	{
		lp->para[i] = para[i];
	}

	m_speedX[layer][0] = para[1] * 100;
	m_speedY[layer][0] = para[2] * 100;
	m_randomX[layer][0] = para[4] * 100;
	m_randomY[layer][0] = para[5] * 100;
	m_x[layer][0] = 0;
	m_y[layer][0] = 0;

	for (i=1;i<para[3];i++)
	{
		m_speedX[layer][i] = (m_speedX[layer][i-1] * para[6]) / 100;
		m_speedY[layer][i] = (m_speedY[layer][i-1] * para[6]) / 100;
		m_randomX[layer][i] = (m_randomX[layer][i-1] * para[6]) / 100;
		m_randomY[layer][i] = (m_randomY[layer][i-1] * para[6]) / 100;
		m_x[layer][i] = 0;
		m_y[layer][i] = 0;
	}

	m_initRnd[layer] = 1;

	return TRUE;
}


BOOL CEffectRain2::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectRain2::BeginPrint(LPVOID para,int layer)
{

}

void CEffectRain2::Init(LPVOID para,int layer)
{
}

void CEffectRain2::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int kosuu = lp->para[3];
	SIZE sz = lpPic->GetPicSize();
	int sizeX = sz.cx;
	int sizeY = sz.cy;
	if ((sizeX <= 0) || (sizeY <=0)) return;	//‚æ‚¤‚¶‚ñ

	if (m_initRnd[layer])
	{
		for (int i=0;i<kosuu;i++)
		{
			m_x[layer][i] = rand() % sizeX;
			m_y[layer][i] = rand() % sizeY;
		}

		m_initRnd[layer] = 0;
	}


	//check random speed
	int i;
	for (i=0;i<kosuu;i++)
	{
		int rndx = m_randomX[layer][i];
		if (rndx > 0)
		{
			if ((rand() % (lp->para[7])) == 0)
			{
				int dx = rand() % rndx;
				if ((rand() % 100) < 50) dx *= -1;

				int speedX = m_speedX[layer][i];
				speedX += dx;
				if (speedX < (lp->para[1] - lp->para[4])*100) speedX = (lp->para[1] - lp->para[4])*100;
				if (speedX > (lp->para[1] + lp->para[4])*100) speedX = (lp->para[1] + lp->para[4])*100;

				m_speedX[layer][i] = speedX;
			}
		}
	}


	for (i=0;i<kosuu;i++)
	{
		int rndy = m_randomY[layer][i];
		if (rndy>0)
		{
			if ((rand() % (lp->para[7])) == 0)
			{
				int dy = rand() % rndy;
				if ((rand() % 100) < 50) dy *= -1;

				int speedY = m_speedY[layer][i];
				speedY += dy;
				if (speedY < (lp->para[2] - lp->para[5])*100) speedY = (lp->para[2] - lp->para[5])*100;
				if (speedY > (lp->para[2] + lp->para[5])*100) speedY = (lp->para[2] + lp->para[5])*100;

				if (speedY<100) speedY = 100;

				m_speedY[layer][i] = speedY;
			}
		}
	}

	//move

	for (i=0;i<kosuu;i++)
	{
		int x = m_x[layer][i];
		int y = m_y[layer][i];

		x += m_speedX[layer][i];
		y += m_speedY[layer][i];

		int screenSizeX = CMyGraphics::GetScreenSizeX();
		int screenSizeY = CMyGraphics::GetScreenSizeY();

		int minX = sz.cx;
		int minY = sz.cy;
		if (minX>screenSizeX) minX = screenSizeX;
		if (minY>screenSizeY) minY = screenSizeY;


		if (x<=-minX*100)
		{
			x += minX*1000;
		}
		if (x>=minX*100) x %= (minX*100);

		if (y<-minY*100)
		{
			y += minY*1000;
		}
		if (y>=minY*100) y %= (minY*100);

		m_x[layer][i] = x;
		m_y[layer][i] = y;
	}
}




void CEffectRain2::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int kosuu = lp->para[3];

	for (int n=kosuu-1;n>=0;n--)
	{
		int x = m_x[layer][n] / 100;
		int y = m_y[layer][n] / 100;

		int startX = 0;
		int startY = 0;
		if (x>0) startX = -1;
		if (y>0) startY = -1;

		SIZE sz = lpPic->GetPicSize();
		int sizeX = sz.cx;
		int sizeY = sz.cy;
		if ((sizeX <= 0) || (sizeY <=0)) return;	//‚æ‚¤‚¶‚ñ

		int blockX = 0;
		int blockY = 0;

		if ((x+sizeX) < screenSizeX)
		{
			blockX = (screenSizeX - (x+sizeX) + sizeX - 1) /sizeX;
		}

		if ((y+sizeY) < screenSizeY)
		{
			blockY = (screenSizeY - (y+sizeY) + sizeY - 1) /sizeY;
		}

		for (int j=startY;j<=blockY;j++)
		{
			int putY = y + sizeY * j;
			for (int i=startX;i<=blockX;i++)
			{
				int putX = x + sizeX * i;
				lpPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
			}
		}
	}
}


BOOL CEffectRain2::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectRain2::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}




/*_*/

