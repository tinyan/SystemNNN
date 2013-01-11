//
// effectGrassPlane.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectGrassPlane.h"


CEffectGrassPlane::CEffectGrassPlane(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	m_myDoubleWork = NULL;
#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	Create("GrassPlane");
#endif
}


CEffectGrassPlane::~CEffectGrassPlane()
{
	End();
}

void CEffectGrassPlane::End(void)
{
	DELETEARRAY(m_myDoubleWork);
}

BOOL CEffectGrassPlane::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[16];
	int k = paraKosuu;
	if (k>12) k = 12;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = screenSizeY/2;
	if (paraKosuu<3) para[2] = screenSizeY/2;

	if (para[1]<0) para[1] = 0;
	if (para[1]>=screenSizeY-1) para[1] = screenSizeY-1;
	if (para[2]<1) para[2] = 1;
	if (para[2]>screenSizeY) para[2] = screenSizeY;

	if ((para[1]+para[2]) > screenSizeY) para[2] = screenSizeY - para[1];

	if (paraKosuu<4) para[3] = 500;
	if (paraKosuu<5) para[4] = 100;
	if (paraKosuu<6) para[5] = 0;
	if (paraKosuu<7) para[6] = 100;
	if (paraKosuu<8) para[7] = 5;
	if (paraKosuu<9) para[8] = 100;
	if (paraKosuu<10) para[9] = 50;
	if (paraKosuu<11) para[10] = 20;
	if (paraKosuu<12) para[11] = -1;

	if (para[3]<=para[4]) para[3] = para[4]+1;



	lp->flag = TRUE;
	for (i=0;i<12;i++)
	{
		lp->para[i] = para[i];
	}
	lp->count = 0;
	lp->countMax = para[0];
	lp->command = EFFECT_GRASSPLANE;

	InitParameter(lpEffect, layer);

	return TRUE;
}


BOOL CEffectGrassPlane::CountIsMax(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectGrassPlane::BeginPrint(LPVOID para,int layer)
{

}

void CEffectGrassPlane::Init(LPVOID para,int layer)
{
}

void CEffectGrassPlane::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int printSizeY = lp->para[2];
	int farDist = lp->para[3];
	int nearDist = lp->para[4];

	int windHoukou = lp->para[5];
	int windPower = lp->para[6];
	int solitonKosuu = lp->para[7];
	
	int solitonPower = lp->para[8];
	int solitonSpeed = lp->para[9];

	for (int i=0;i<solitonKosuu;i++)
	{
		if (m_solitonWait[i]==0)
		{
			if (windHoukou == 0)
			{
				m_solitonY[i] += m_solitonSpeed[i];
				if (m_solitonY[i] > farDist)
				{
					SetNewSoliton(lpEffect,i);
				}
			}
			else
			{
				m_solitonY[i] -= m_solitonSpeed[i];
				if (m_solitonY[i] < nearDist)
				{
					SetNewSoliton(lpEffect,i);
				}
			}
		}
		else
		{
			m_solitonWait[i]--;
		}
	}
}


void CEffectGrassPlane::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	if (m_myDoubleWork == NULL) CreateMyDoubleWork();

	if (m_myDoubleWork == NULL) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int count = lp->count;
	int countMax = lp->countMax;

	int startY = lp->para[1];
	int printSizeY = lp->para[2];
	int farDist = lp->para[3];
	int nearDist = lp->para[4];
	int windHoukou = lp->para[5];
	int windPower = lp->para[6];
	int solitonKosuu = lp->para[7];
	int solitonPower = lp->para[8];
	int solitonSpeed = lp->para[9];
	int solitonHaba = lp->para[10];
	int picLayer = lp->para[11];

	if (picLayer == -1) picLayer = layer;

	CPicture* lpPic = m_allEffect->GetPicture(picLayer);
	if (lpPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);

//	double delta[MAXSCREENSIZEY];
	double* delta = m_myDoubleWork;

//	int work[MAXSCREENSIZEY];
//	int* work = CEffectSimpleWipe::m_shapeWork;
	int* work = m_allEffect->GetTempWork();
	int* workPtr = work;


	int putX = lp->dst.left;
	int putY = lp->dst.top;
	int srcX = 0;
	int srcY = 0;
	int sizeX = rc.right;
	int sizeY = rc.bottom;

	if ((sizeX<=0) || (sizeY<=0)) return;



	double th2 = (double)count;
	if (windHoukou == 1)
	{
		th2 = -th2;
	}
	th2 /= (double)(screenSizeY);
	th2 *= 3.14159*2.0 * 5.0;

	int i;
	for (i=0;i<screenSizeY;i++)
	{
		double dist = DotToDist(i);
		double th = dist;
		th *= 0.08;
		th += th2;

		double ml0 = m_constNear / dist;
		delta[i] = (int)(windPower* ml0 *cos(th)+0.5);
//		delta[i] = 0.0;
	}

	for (int n=0;n<solitonKosuu;n++)
	{
		if (m_solitonWait[n] == 0)
		{
			int y = m_solitonY[n];
			double pw = (double)m_solitonPower[n];
			int haba = m_solitonHaba[n];

			double yNear = (double)(y - haba);
			if (yNear<1.0) yNear = 1.0;
			double yFar = (double)(y + haba);
			if (yFar<=yNear) yFar = yNear + 0.1;

			int solitonDotNear = (int)(DistToDot(yNear));
			int solitonDotFar = (int)(DistToDot(yFar));


			for (int dot=solitonDotFar;dot<=solitonDotNear;dot++)
			{
				if ((dot>=0) && (dot<printSizeY))
				{
					double dist = DotToDist(dot);
					double ml0 = m_constNear / dist;

					double th = (dist - yNear) / (yFar - yNear) * 3.14159*2.0;
					double ml = 1.0 - cos(th);

					delta[dot] += ml * pw * ml0;
				}

			}
		}
	}




	for (i=0;i<screenSizeY;i++)
	{
		work[i] = (int)(delta[i] + 0.5);
	}


#if defined _TINYAN3DLIB_
	if (CheckEffectError()) return;
	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture());

	int* workV = m_allEffect->GetTempWork();
	workV += screenSizeY;

	float div3 = 1.0f / 3.0f;
	float divSizeX = 1.0f / (float)(sizeX);

	for (int j=0;j<screenSizeY;j++)
	{
		float x1 = (float)(work[j]);

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

	dstPoint.x = putX;
	dstPoint.y = putY;
	dstSize.cx = sizeX;
	dstSize.cy = sizeY;
	srcPoint.x = srcX;
	srcPoint.y = srcY;

	Blt(dstPoint,dstSize,srcPoint);
	


#else
	lpPic->DeltaBlt(putX,putY,srcX,srcY,sizeX,sizeY,FALSE,workPtr);
#endif
}


BOOL CEffectGrassPlane::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectGrassPlane::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


void CEffectGrassPlane::InitParameter(LPVOID lpEffect, int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	m_constNear = (double)(lp->para[4]);
	m_constFar = (double)(lp->para[3]);
	m_constDot = (double)(lp->para[2]);

	m_constL = m_constFar / (m_constFar - m_constNear) * m_constDot;

	for (int i=0;i<SOLITON_KOSUU_MAX;i++)
	{
		SetNewSoliton(lpEffect,i,TRUE);
	}
}


void CEffectGrassPlane::SetNewSoliton(LPVOID lpEffect, int n, BOOL inScreenFlag)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int printSizeY = lp->para[2];
	int farDist = lp->para[3];
	int nearDist = lp->para[4];
	int windHoukou = lp->para[5];
	int windPower = lp->para[6];
	int solitonPower = lp->para[8];
	int solitonSpeed = lp->para[9];
	int solitonHaba = lp->para[10];

	m_solitonWait[n] = rand() % 50;
	int r = 100 + (rand() % 100) - 50;
	m_solitonPower[n] = (windPower * solitonPower) / 100;
	m_solitonPower[n] *= r;
	m_solitonPower[n] /= 100;


	int r2 = 100 + (rand() % 60) - 30;
	m_solitonSpeed[n] = (solitonSpeed * r2) / 100;
	if (m_solitonSpeed[n]<1) m_solitonSpeed[n] = 1;

	if (windHoukou == 0)
	{
		m_solitonY[n] = nearDist;
	}
	else
	{
		m_solitonY[n] = farDist;
	}

	int r3 = 100 + (rand() % 40) - 20;
	m_solitonHaba[n] = (solitonHaba * r3) / 100;
	if (m_solitonHaba[n]<1) m_solitonHaba[n] = 1;

	if (inScreenFlag)
	{
		m_solitonWait[n] = 0;
		if (windHoukou == 0)
		{
			m_solitonY[n] = nearDist + (rand() % (farDist - nearDist));
		}
		else
		{
			m_solitonY[n] = farDist - (rand() % (farDist - nearDist));
		}
	}
}



double CEffectGrassPlane::DotToDist(double dot)
{
	double dv = m_constL - m_constDot + dot;
	if (dv<0.1) dv = 0.1;
	return (m_constL * m_constNear) / dv;
}

double CEffectGrassPlane::DistToDot(double dist)
{
	if (dist<0.1) dist = 0.1;
	return m_constDot - ((dist - m_constNear) * m_constL) / dist;
}


void CEffectGrassPlane::CreateMyDoubleWork(void)
{
	if (m_myDoubleWork != NULL) return;

	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_myDoubleWork = new double[screenSizeY];
}
