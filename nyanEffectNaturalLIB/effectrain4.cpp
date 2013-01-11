//
// effectRain.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectRain4.h"


CEffectRain4::CEffectRain4(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectRain4::~CEffectRain4()
{
	End();
}

void CEffectRain4::End(void)
{
}

void CEffectRain4::InitParameter(LPVOID lpEffect, int layer)
{
	int para[9];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<9;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,9,para,layer);
}

BOOL CEffectRain4::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[9];
	int k = paraKosuu;

	if (k>9) k = 9;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	if (paraKosuu<1) para[0] = 20;

	if (paraKosuu<2) para[1] = 2;	//kosuu

	if (paraKosuu<3) para[2] = 500;//high
	if (paraKosuu<4) para[3] = 20;	//	low
	
	if (paraKosuu<5) para[4] = -20;	//speed

	if (paraKosuu<6) para[5] = screenSizeX/2;	//centerX
	if (paraKosuu<7) para[6] = screenSizeY/2;	//centerY

	if (paraKosuu<8) para[7] = 0;	//—¼’[“§–¾“x“
	if (paraKosuu<9) para[8] = 60;	//“§–¾“x‚P‚O‚O“‹——£

	if (para[5]<0) para[5] = 0;
	if (para[6]<0) para[6] = 0;

	if (para[5]>=screenSizeX) para[5] = screenSizeX-1;
	if (para[6]>=screenSizeY) para[6] = screenSizeY-1;


	if (para[2]<10) para[2] = 10;
	if (para[3]<10) para[3] = 10;

	if (para[3] >= para[2]) para[3] = para[2]-1;


	lp->flag = TRUE;
	lp->command = EFFECT_RAIN4;
	lp->count = 0;
	lp->countMax = para[0];

	for (i=0;i<9;i++)
	{
		lp->para[i] = para[i];
	}

	m_dist[layer] = 0;

	return TRUE;
}


BOOL CEffectRain4::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectRain4::BeginPrint(LPVOID para,int layer)
{

}

void CEffectRain4::Init(LPVOID para,int layer)
{
	if (layer == -1)
	{
		for (int i=0;i<16;i++)
		{
			m_dist[i] = 0;
		}
	}
	else
	{
		m_dist[layer] = 0;
	}
}

void CEffectRain4::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int d = m_dist[layer];
	int speed = lp->para[4];
	d += speed;
	if (speed<0)
	{
		if (d < lp->para[3]) d = lp->para[2];
	}
	else
	{
		if (d>lp->para[2]) d = lp->para[3];
	}
	m_dist[layer] = d;
}




void CEffectRain4::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	SIZE sz = lpPic->GetPicSize();
	int srcPicSizeX = sz.cx;
	int srcPicSizeY = sz.cy;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int kosuu = lp->para[1];

	int high = lp->para[2];
	int low = lp->para[3];

	int dv = high - low;

	int dist[4];

	int startN = 0;
	int dh = 1;
	int speed = lp->para[4];
	int maxData = 0;
	int minData = 10000;
	if (speed<0)
	{
		dh = -1;
	}

	if (dv==0) dv = 1;

	int i;
	for (i=0;i<kosuu;i++)
	{
		int d = m_dist[layer];
		d += (dv * i) / kosuu;
		if (d>high)
		{
			d -= low;
			d %= dv;
			d += low;
		}
		dist[i] = d;

		if (speed<0)
		{
			if (d>maxData)
			{
				maxData = d;
				startN = i;
			}
		}
		else
		{
			if (d<minData)
			{
				minData = d;
				startN = i;
			}
		}
	}

	int centerX = lp->para[5];
	int centerY = lp->para[6];


	BOOL transFlag = TRUE;

	for (i=0;i<kosuu;i++)
	{
		int d = dist[startN];
		if (d == 0) d = 1;


		int ps1 = lp->para[7];
		int ps2 = 100;
		int dist100 = lp->para[8];

		int transPercent = 100;

		if (dist100>0)
		{
			if ((d-low)<dist100)
			{
				int c = d-low;
				transPercent = (c * (ps2-ps1))/dist100+ps1;
			}
			else if ((high-d)<dist100)
			{
				int c = high-d;
				transPercent = (c * (ps2-ps1))/dist100+ps1;
			}
		}


		if (transPercent < 1) transPercent = 1;
		if (transPercent > 100) transPercent = 100;


		int putSizeX = (srcPicSizeX * 100) / d;
		int putSizeY = (srcPicSizeY * 100) / d;

		if ((putSizeX>0) && (putSizeY>0))
		{
			int putX0 = centerX - putSizeX/2;
			int putY0 = centerY - putSizeY/2;

			int startX = 0;
			int endX = 0;
			int startY = 0;
			int endY = 0;

			if (putX0>0)
			{
				startX = (putX0 + putSizeX - 1) / putSizeX;
				startX *= -1;
			}

			if (putY0>0)
			{
				startY = (putY0 + putSizeY - 1) / putSizeY;
				startY *= -1;
			}

			if ((putX0+putSizeX)<screenSizeX)
			{
				endX = (screenSizeX - (putX0+putSizeX) + (putSizeX-1)) / putSizeX;
			}

			if ((putY0+putSizeY)<screenSizeY)
			{
				endY = (screenSizeY - (putY0+putSizeY) + (putSizeY-1)) / putSizeY;
			}


			for (int jj = startY;jj<=endY;jj++)
			{
				int putY = putY0 + jj*putSizeY;
				for (int ii=startX;ii<=endX;ii++)
				{
					int putX = putX0 + ii*putSizeX;
					lpPic->StretchBlt1(putX,putY,putSizeX,putSizeY,0,0,srcPicSizeX,srcPicSizeY,transPercent,transFlag);
				}
			}


			startN += dh;
			startN += kosuu;
			startN %= kosuu;
		}
	}
}


BOOL CEffectRain4::CheckAllPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}

BOOL CEffectRain4::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}




/*_*/

