//
// effectoldfilm.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectoldfilm.h"

CEffectOldFilm::CEffectOldFilm(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_renzokuEffectFlag = TRUE;
}


CEffectOldFilm::~CEffectOldFilm()
{
	End();
}

void CEffectOldFilm::End(void)
{
}


BOOL CEffectOldFilm::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	
	int k = paraKosuu;
	if (k>15) k = 15;

	int para[16];
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (paraKosuu < 2) para[1] = 0;
	if (paraKosuu < 3) para[2] = 0;
	if (paraKosuu < 4) para[3] = screenSizeX;
	if (paraKosuu < 5) para[4] = screenSizeY;


	if (paraKosuu<6) para[5] = 3;	//kosuu
	if (para[5] > 10) para[5] = 10;

	if (paraKosuu<7) para[6] = 1;	//line size	max4?
	if (para[6] < 1) para[6] = 1;
	if (para[6] > 4) para[6] = 4;

	if (para[1] < 0) para[1] = 0;
	if (para[2] < 0) para[2] = 0;
	if (para[1] >= screenSizeX-para[6]+1) para[1] = screenSizeX-1-para[6]+1;
	if (para[2] >= screenSizeY-para[6]+1) para[2] = screenSizeY-1-para[6]+1;

	if (para[1]+para[3] > screenSizeX) para[3] = screenSizeX - para[1];
	if (para[2]+para[4] > screenSizeY) para[4] = screenSizeY - para[2];




	if (paraKosuu<8) para[7] = 128;	//col
	if (paraKosuu<9) para[8] = 128;
	if (paraKosuu<10) para[9] = 128;
	
	if (paraKosuu<11) para[10] = 200;	//iji time
	if (paraKosuu<12) para[11] = 80;	//iji rnd
	if (paraKosuu<13) para[12] = 30;	//print rnd

	if (paraKosuu < 14) para[13] = 100; //min trans percent
	if (paraKosuu < 15) para[14] = 100; //min trans percent

	for (i=0;i<15;i++)
	{
		lp->para[i] = para[i];
	}

	lp->flag = TRUE;
	lp->count = 0;
	lp->countMax = 9999;
	lp->command = EFFECT_OLDFILM;


//	m_point.x = para[1];
//	m_point.y = para[2];
//	m_size.cx = para[3];
//	m_size.cy = para[4];
//	m_lineSize = para[6];

	for (i=0;i<para[5];i++)
	{
		InitLine(lp,i);
	}



	return TRUE;
}

BOOL CEffectOldFilm::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}

void CEffectOldFilm::BeginPrint(LPVOID para,int layer)
{
}

void CEffectOldFilm::Init(LPVOID para,int layer)
{
}

void CEffectOldFilm::Calcu(LPVOID para,int layer)
{
}

void CEffectOldFilm::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int pointX = lp->para[1];
	int pointY = lp->para[2];
	int sizeX = lp->para[3];
	int sizeY = lp->para[4];
	int lineSize = lp->para[6];
	
//	int k = 16 + n*4;

//	m_point.x = lp->para[1];
//	m_point.y = lp->para[2];
//	m_size.cx = lp->para[3];
//	m_size.cy = lp->para[4];
//	m_lineSize = lp->para[6];

//	int xMin = m_point.x * 256;
//	int xMax = (m_point.x+m_size.cx-(m_lineSize-1)) * 256;
	int xMin = pointX * 256;
	int xMax = (pointX+sizeX-(lineSize-1)) * 256;

	int putY = pointY;
	int putSizeX = lineSize;
	int putSizeY = sizeY;

	int colR = lp->para[7];
	int colG = lp->para[8];
	int colB = lp->para[9];

	int printRnd = lp->para[12];

	for (int i=0;i<lp->para[5];i++)
	{
		int k = 16 + i * 4;

		//m_lines[i].count --;
		lp->para[k+3]--;

//		if (m_lines[i].count <= 0)
		if (lp->para[k+3] <= 0)
		{
			InitLine(lp,i);
		}

		//m_lines[i].countX--;
		lp->para[k+2]--;

		//if (m_lines[i].countX <=0)
		if (lp->para[k+2] <=0)
		{
			//m_lines[i].countX = (rand() % 20) + 10;
			lp->para[k+2] = (rand() % 20) + 10;
			//m_lines[i].speedX256 = (rand() % 1024) + 128;
			lp->para[k+1] = (rand() % 1024) + 128;
			//if ((rand() % 100) < 50) m_lines[i].speedX256 *= -1;
			if ((rand() % 100) < 50) lp->para[k+1] *= -1;
		}

//		int x = m_lines[i].x256 + m_lines[i].speedX256;
		int x = lp->para[k+0] + lp->para[k+1];

		if (x >= xMax)
		{
			x = xMax-1;
			//m_lines[i].speedX256 *= -1;
			lp->para[k+1] *= -1;
		}

		if (x < xMin)
		{
			x = xMin;
			//m_lines[i].speedX256 *= -1;
			lp->para[k+1] *= -1;
		}

		//m_lines[i].x256 = x;
		lp->para[k+0] = x;

		int putX = x / 256;

		if ((rand() % 100) < printRnd)
		{
			int psMin = lp->para[13];
			int psMax = lp->para[14];
			if (psMin > psMax)
			{
				int tmp = psMin;
				psMin = psMax;
				psMax = tmp;
			}
			int dv = psMax - psMin + 1;
			int ps = psMin + (rand() % dv);
			if (ps >= 100)
			{
				CAllGeo::BoxFill(putX, putY, putSizeX, putSizeY, colR, colG, colB);
			}
			else
			{
				CAllGeo::TransBoxFill(putX, putY, putSizeX, putSizeY, colR, colG, colB,ps);

			}
		}
	}
}


void CEffectOldFilm::InitLine(LPVOID lpEffect,int n)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int pointX = lp->para[1];
	int pointY = lp->para[2];
	int sizeX = lp->para[3];
	int sizeY = lp->para[4];
	int lineSize = lp->para[6];
	
	int k = 16 + n*4;


	//m_lines[n].countX = (rand() % 20) + 10;
	lp->para[k+2] = (rand() % 20) + 10;

//	m_lines[n].count = (rand() % 300) + 40;
	int h = lp->para[10];
	int r = lp->para[11];
	if (r<1) r = 1;
	r *= h;
	r /= 100;
	if (r<1) r = 1;
	int d = rand() % r;
	if ((rand() % 100) < 50) d *= -1;
	int c = h + d;
	if (c<1) c = 1;
	lp->para[k+3] = c;
	
	//int dv = m_size.cx;
	int dv = sizeX;
	//dv -= (m_lineSize-1);
	dv -= (lineSize-1);
	if (dv<1) dv = 1;

	int x = rand() % dv;

	//m_lines[n].x256 = (x + pointX) * 256;
	lp->para[k+0] = (x + pointX) * 256;

	//m_lines[n].speedX256 = (rand() % 1024) + 128;
	lp->para[k+1] = (rand() % 1024) + 128;

	if ((rand() % 100) < 50)
	{
	//	m_lines[n].speedX256 *= -1;
		lp->para[k+1] *= -1;
	}
}

/*_*/


