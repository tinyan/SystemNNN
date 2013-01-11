//
// effectRain.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectRain.h"


CEffectRain::CEffectRain(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectRain::~CEffectRain()
{
	End();
}

void CEffectRain::End(void)
{
}

void CEffectRain::InitParameter(LPVOID lpEffect, int layer)
{
	int para[8];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<8;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,8,para,layer);
}

BOOL CEffectRain::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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
	if (paraKosuu<2) para[1] = 30;	//houkou
	if (paraKosuu<3) para[2] = 100;	//kosuu
	if (paraKosuu<4) para[3] = 60;	//speed
	if (paraKosuu<5) para[4] = 80;	//length


	if (paraKosuu<6) para[5] = 255;
	if (paraKosuu<7) para[6] = para[5];
	if (paraKosuu<8) para[7] = para[6];

	lp->flag = TRUE;
	lp->command = EFFECT_RAIN;
	lp->count = 0;
	lp->countMax = para[0];

	if (para[2] > RAIN_KOSUU) para[2] = RAIN_KOSUU;
	if (para[3] < 1) para[3] = 1;
	if (para[4] < 1) para[4] = 1;

	for (i=0;i<8;i++)
	{
		lp->para[i] = para[i];
	}
	
	m_rainHoukou = para[1];
	m_rainKosuu = para[2];
	m_rainSpeed = para[3];
	m_rainLength = para[4];
	m_rainR = para[5];
	m_rainG = para[6];
	m_rainB = para[7];

	InitRain();

	return TRUE;
}


BOOL CEffectRain::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectRain::BeginPrint(LPVOID para,int layer)
{

}

void CEffectRain::Init(LPVOID para,int layer)
{
}

void CEffectRain::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	CalcuRain(lp);
}


void CEffectRain::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
//	CalcuRain(lp);
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int col = (m_rainR << 16) | (m_rainG << 8) | m_rainB;

	int r = m_rainR;
	int g = m_rainG;
	int b = m_rainB;

	for (int i=0;i<m_rainKosuu;i++)
	{
		int x = m_rain[i].x;
		int y = m_rain[i].y;
		int ln = m_rain[i].lenY;

		int putY = y / 256;
		if (putY>=screenSizeY) continue;
		if ((putY+ln) < 0) continue;
		
		int putX = (x+128)>>8;

		int houkouX = m_rain[i].houkouX;

		int putY2 = putY + ln;
		int putX2 = putX + ((houkouX*ln)>>16);

//		CAllGeo::Line(putX,putY,putX+10,putY+20,r,g,b);

		CAllGeo::Line(putX,putY,putX2,putY2,r,g,b);
	}
}




void CEffectRain::InitRain(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	for (int i=0;i<m_rainKosuu;i++)
	{
		SetNewRain(i);
		int y = rand() % (screenSizeY + m_rainLength);
		y -= m_rainLength;
		y *= 256;
		m_rain[i].y = y;
	}
}



void CEffectRain::CalcuRain(LPVOID lpEffect)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

//	m_rainHoukou = m_effect[n].para[0];
//	m_rainKosuu = m_effect[n].para[1];
//	m_rainSpeed = m_effect[n].para[2];
//	m_rainLength = m_effect[n].para[3];
//	m_rainR = m_effect[n].para[4];
//	m_rainG = m_effect[n].para[5];
//	m_rainB = m_effect[n].para[6];

	for (int i=0;i<m_rainKosuu;i++)
	{
		int x = m_rain[i].x;
		int y = m_rain[i].y;
		x += (m_rain[i].houkouX * m_rain[i].speedY) / 256;
		y += m_rain[i].speedY*256;
		m_rain[i].x = x;
		m_rain[i].y = y;

		if (y>=screenSizeY*256)
		{
			SetNewRain(i);
//			x = m_rain[i].x;
//			y = m_rain[i].y;
		}
	}
}


void CEffectRain::SetNewRain(int n)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int spd = m_rainSpeed;
	if (spd<1) spd = 1;

	int spd2 = spd / 2;
	if (spd2<1) spd2 = 1;

	int ln = m_rainLength;
	int ln2 = m_rainLength / 2;
	if (ln<1) ln = 1;
	if (ln2<1) ln2 = 1;

	int houkouX = m_rainHoukou + (rand() % 16) - 8;

	int hdx = houkouX * screenSizeY / 256;
	if (hdx<0) hdx = -hdx;

	int x = rand() % (screenSizeX+hdx*2);
	x -= hdx;
	
	int y = rand() % spd;
	y = -y;

	x *= 256;
	y *= 256;

	int speedY = rand() % spd2;
	speedY += spd;

	int lenY = ln2 + (rand() % ln);

	houkouX *= 256;

	m_rain[n].x = x;
	m_rain[n].y = y;
	m_rain[n].speedY = speedY;
	m_rain[n].lenY = lenY;
	m_rain[n].houkouX = houkouX;
}




/*_*/

