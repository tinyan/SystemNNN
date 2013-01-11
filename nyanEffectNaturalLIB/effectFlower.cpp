//
// effectflower.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectflower.h"


CEffectFlower::CEffectFlower(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_picFlag = FALSE;
	m_flowerKosuu = FLOWER_KOSUU;

	m_flowerPic = new CPicture();

	BOOL old = CPicture::m_errorPrintFlag;
	CPicture::m_errorPrintFlag = FALSE;

	if (m_flowerPic->LoadDWQ("sys\\ta_eff_saku"))
	{
		m_picFlag = TRUE;
	}
	else
	{
		if (m_flowerPic->LoadDWQ("sys\\eff_saku",TRUE))
		{
			m_picFlag = TRUE;
		}
	}

	CPicture::m_errorPrintFlag = old;
	if (m_picFlag == FALSE)
	{
		if (old)
		{
			MessageBox(NULL,"ta_eff_saku.dwq –”‚Í eff_saku.dwq‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ","Error",MB_OK);
		}
	}

}

CEffectFlower::~CEffectFlower()
{
	End();
}

void CEffectFlower::End(void)
{
	ENDDELETECLASS(m_flowerPic);
}

BOOL CEffectFlower::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[4];
	int k = paraKosuu;
	if (k>4) k = 4;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 0;
	if (paraKosuu<3) para[2] = 2;
	if (paraKosuu<4) para[3] = m_flowerKosuu / 2;
	if (para[3] > m_flowerKosuu) para[3] = m_flowerKosuu;

	lp->flag = TRUE;
	lp->command = EFFECT_FLOWER;
	lp->count = 0;
	lp->countMax = 99999;

	lp->para[0] = para[0];
	lp->para[1] = para[1];
	lp->para[2] = para[2];
	lp->para[3] = para[3];


	return TRUE;
}


BOOL CEffectFlower::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectFlower::BeginPrint(LPVOID para,int layer)
{
	m_flowerCalcuedFlag = FALSE;
}


void CEffectFlower::Init(LPVOID para,int layer)
{
	int i,j;

	m_flowerMulti[0] = 32;
	m_flowerMulti[1] = 16;
	m_flowerMulti[2] = 8;

	m_flowerSize[0] = 32;
	m_flowerSize[1] = 16;
	m_flowerSize[2] = 8;

	m_flowerStartY[0] = 0;
	m_flowerStartY[1] = 32;
	m_flowerStartY[2] = 32+16;

	for (j=0;j<10;j++)
	{
		int mx = j + 30;

		for (i=0;i<mx;i++)
		{
			double th1 = (double)(i + mx / 4);
			double th2 = (double)(i + mx / 4 + 1);
			th1 *= 3.14159 * 2;
			th2 *= 3.14159 * 2;
			th1 /= mx;
			th2 /= mx;

			double dlt = cos(th2) - cos(th1);
			dlt *= 2000;
			dlt += 0.5;

			m_flowerDeltaX[j][i] = (int)dlt;


			double th3 = (double)(i % (mx/2));
			th3 *= 3.14159 * 2;
			th3 /= mx;


			m_flowerDeltaY[j][i] = (int)((sin(th3) - 0.8) * 300);

		}
	}

	for (i=0;i<50;i++)
	{
		m_flower[i].typ = 2;
	}
	for (i=50;i<85;i++)
	{
		m_flower[i].typ = 1;
	}
	for (i=85;i<100;i++)
	{
		m_flower[i].typ = 0;
	}
	for (i=100;i<200;i++)
	{
		m_flower[i].typ = 0;
	}

	for (i=0;i<m_flowerKosuu;i++)
	{
		SetNewFlower(i);
	}

}

void CEffectFlower::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectFlower::Print(LPVOID lpEffect,int layer)
{
	if (m_picFlag == FALSE) return;

	EFFECT* lp = (EFFECT*)lpEffect;

	if (m_flowerCalcuedFlag == FALSE)
	{
		CalcuFlower();
		m_flowerCalcuedFlag = TRUE;
	}

	int st = lp->para[1];
	int ed = lp->para[2];

	int kosuu = lp->para[3];


//MessageBox(NULL,"PrintSnow","1",MB_OK);
	for (int i=0;i<kosuu;i++)
	{
		int x = m_flower[i].putX;
		int y = m_flower[i].putY;
		int typ = m_flower[i].typ;
		int pat = m_flower[i].pat;

		if ((typ>=st) && (typ<=ed))
		{
			int sizeX = m_flowerSize[typ];
			int sizeY = sizeX;
			int srcX = sizeX * pat;
			int srcY = m_flowerStartY[typ];
//char mes[256];
//sprintf(mes,"%d %d %d %d %d %d",x,y,srcX,srcY,sizeX,sizeY);
//MessageBox(NULL,mes,"PrintSnow",MB_OK);
			m_flowerPic->Blt(x,y,srcX,srcY,sizeX,sizeY,TRUE);
		}
	}

}


void CEffectFlower::SetNewFlower(int n)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_flower[n].pat = 0;
	m_flower[n].x = rand() % (screenSizeX*40);
	m_flower[n].y = rand() % (screenSizeY*40);
	m_flower[n].speedX = (rand() % 600) - 300;
	m_flower[n].speedY = (rand() % 150) + 200;
	m_flower[n].count = 0;
	m_flower[n].countMax = (rand() % 10) + 30;

	m_flower[n].x *= 64;
	m_flower[n].y *= 64;
	m_flower[n].x /= m_flowerMulti[m_flower[n].typ];
	m_flower[n].y /= m_flowerMulti[m_flower[n].typ];

	CalcuFlowerXY(n);

}


void CEffectFlower::CalcuFlower(void)
{
	if (m_flowerCalcuedFlag) return;
	m_flowerCalcuedFlag = TRUE;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	for (int i=0;i<m_flowerKosuu;i++)
	{
		int c = m_flower[i].count;
		int mx = m_flower[i].countMax;
		c++;
		if (c>=mx) c = 0;
		m_flower[i].count = c;

		m_flower[i].x += m_flower[i].speedX;
		m_flower[i].x += m_flowerDeltaX[mx-30][c];
		m_flower[i].y += m_flower[i].speedY;
		m_flower[i].y += m_flowerDeltaY[mx-30][c];

		CalcuFlowerXY(i);
		if (m_flower[i].putY >= screenSizeY)
		{
			SetNewFlower(i);
			m_flower[i].y = -1000;
			CalcuFlowerXY(i);
		}
	}
}


void CEffectFlower::CalcuFlowerXY(int n)
{
	int x = m_flower[n].x;
	int y = m_flower[n].y;

	int ml = m_flowerMulti[m_flower[n].typ];
	
	x *= ml;
	y *= ml;

	x /= (40*64);
	y /= (40*64);

	m_flower[n].putX = x;
	m_flower[n].putY = y;

	int pt = m_flower[n].count;
	pt *= 8;
	pt /= m_flower[n].countMax;
	if (pt>=5)
	{
		pt = 8-pt;
	}

	m_flower[n].pat = pt;
}
