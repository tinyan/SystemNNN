//
// effectsnow.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectsnow.h"


CEffectSnow::CEffectSnow(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_kosuuMax = SNOW_KOSUU_MAX;
	m_kosuu = 1;

	m_picFlag = FALSE;

	BOOL old = CPicture::m_errorPrintFlag;
	CPicture::m_errorPrintFlag = FALSE;

	m_snowPic = new CPicture();
	if (m_snowPic->LoadDWQ("sys\\ta_eff_snow"))
	{
		m_picFlag = TRUE;
	}
	else if (m_snowPic->LoadDWQ("sys\\eff_snow",TRUE))
	{
		m_picFlag = TRUE;
	}
	else
	{
			CPicture::m_errorPrintFlag = old;
			if (m_picFlag == FALSE)
			{
				if (old)
				{
					MessageBox(NULL,"ta_eff_snow.dwq –”‚Í eff_snow.dwq‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ","Error",MB_OK);
				}
			}
		return;
	}

	CPicture::m_errorPrintFlag = old;


	Init((LPVOID)m_kosuuMax);
	InitSnow();
}


CEffectSnow::~CEffectSnow()
{
	End();
}


void CEffectSnow::End(void)
{
	ENDDELETECLASS(m_snowPic);
}

void CEffectSnow::InitParameter(LPVOID lpEffect, int layer)
{
	int para[3];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<3;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,3,para,layer);
}


BOOL CEffectSnow::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[3];

	int k = paraKosuu;

	if (k>3) k = 3;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}
	

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = 0;
	if (paraKosuu<3) para[2] = 5;

	lp->flag = TRUE;

	for (i=0;i<3;i++)
	{
		lp->para[i] = para[i];
	}


	lp->count = 0;
	lp->countMax = lp->para[0];
	lp->command = EFFECT_SNOW;

	InitSnow();

	return TRUE;
}

BOOL CEffectSnow::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
	//nothing to do
}

void CEffectSnow::BeginPrint(LPVOID para,int layer)
{
	m_snowCalcuedFlag = FALSE;
}


void CEffectSnow::Init(LPVOID para,int layer)
{
	int kosuu = m_kosuuMax;
	if (para != NULL) kosuu = (int)para;

	if (kosuu<1) kosuu = 1;
	if (kosuu > m_kosuuMax) kosuu = m_kosuuMax;

	m_kosuu = kosuu;
}


void CEffectSnow::Calcu(LPVOID lpEffect,int layer)
{
}

void CEffectSnow::Print(LPVOID lpEffect,int layer)
{
	if (m_picFlag == FALSE) return;


	EFFECT* lp = (EFFECT*)lpEffect;

	if (m_snowCalcuedFlag == FALSE)
	{
		CalcuSnow();
		m_snowCalcuedFlag = TRUE;
	}


	int startPic = lp->para[1];
	int endPic = lp->para[2];

	if (startPic == -1) startPic = 0;
	if (endPic == -1) endPic = 5;

	for (int i=0;i<m_kosuu;i++)
	{
		int x = m_snow[i].putX;
		int y = m_snow[i].putY;
		int typ = m_snow[i].typ;
		int pat = m_snow[i].pat;

		if ((typ >= startPic) && (typ<=endPic))
		{
			int sizeX = m_snowSize[typ];
			int sizeY = sizeX;
			int srcX = sizeX * pat;
			int srcY = m_snowStartY[typ];
			m_snowPic->Blt(x,y,srcX,srcY,sizeX,sizeY,TRUE);
		}
	}
}



//void CEffectSnow::PrintSnow(int n)
//{
//}




void CEffectSnow::InitSnow(void)
{
	int i,j;

	m_snowMulti[0] = 64;
	m_snowMulti[1] = 48;
	m_snowMulti[2] = 32;
	m_snowMulti[3] = 24;
	m_snowMulti[4] = 16;
	m_snowMulti[5] = 8;

	m_snowSize[0] = 64;
	m_snowSize[1] = 48;
	m_snowSize[2] = 32;
	m_snowSize[3] = 24;
	m_snowSize[4] = 16;
	m_snowSize[5] = 8;

	m_snowStartY[0] = 0;
	m_snowStartY[1] = 64;
	m_snowStartY[2] = 64+48;
	m_snowStartY[3] = 64+48+32;
	m_snowStartY[4] = 64+48+32+24;
	m_snowStartY[5] = 64+48+32+24+16;

	for (j=0;j<10;j++)
	{
		int mx = j + 20;

		for (i=0;i<mx;i++)
		{
			double th1 = (double)i;
			double th2 = (double)(i+1);
			th1 *= 3.14159 * 2;
			th2 *= 3.14159 * 2;
			th1 /= mx;
			th2 /= mx;

			double dlt = cos(th2) - cos(th1);
			dlt *= 1000;
			dlt += 0.5;

			m_snowDelta[j][i] = (int)dlt;
		}
	}


	for (i=0;i<m_kosuu;i++)
	{
		SetNewSnow(i);
	}
}

void CEffectSnow::SetNewSnow(int n)
{
	int r = rand() % 25600;

	if (r<1) m_snow[n].typ = 0;
	else if (r<10) m_snow[n].typ = 1;
	else if (r<2000) m_snow[n].typ = 2;
	else if (r<6000) m_snow[n].typ = 3;
	else if (r<14000) m_snow[n].typ = 4;
	else m_snow[n].typ = 5;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();



	m_snow[n].pat = rand() % 4;
	m_snow[n].x = rand() % (screenSizeX*40);
	m_snow[n].y = rand() % (screenSizeY*40);
	m_snow[n].speedX = (rand() % 300) - 150;
	m_snow[n].speedY = (rand() % 200) + 500;
	m_snow[n].count = 0;
	m_snow[n].countMax = (rand() % 10) + 20;

	m_snow[n].x *= 64;
	m_snow[n].y *= 64;
	m_snow[n].x /= m_snowMulti[m_snow[n].typ];
	m_snow[n].y /= m_snowMulti[m_snow[n].typ];

	CalcuSnowXY(n);
}


void CEffectSnow::CalcuSnow(void)
{
	if (m_snowCalcuedFlag) return;
	m_snowCalcuedFlag = TRUE;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();



	for (int i=0;i<m_kosuu;i++)
	{
		int c = m_snow[i].count;
		int mx = m_snow[i].countMax;
		c++;
		if (c>=mx) c = 0;
		m_snow[i].count = c;

		m_snow[i].x += m_snow[i].speedX;
		m_snow[i].x += m_snowDelta[mx-20][c];
		m_snow[i].y += m_snow[i].speedY;

		CalcuSnowXY(i);
		if (m_snow[i].putY >= screenSizeY)
		{
			SetNewSnow(i);
			m_snow[i].y = -1000;
			CalcuSnowXY(i);
		}
	}
}


void CEffectSnow::CalcuSnowXY(int n)
{
	int x = m_snow[n].x;
	int y = m_snow[n].y;

	int ml = m_snowMulti[m_snow[n].typ];
	
	x *= ml;
	y *= ml;

	x /= (40*64);
	y /= (40*64);

	m_snow[n].putX = x;
	m_snow[n].putY = y;
}


/*_*/

