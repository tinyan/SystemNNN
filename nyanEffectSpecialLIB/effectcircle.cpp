//
// effectcircle.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectcircle.h"


CEffectCircle::CEffectCircle(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(1);
	SetColorKosuu(1);
	Create("Circle");
#endif
}

CEffectCircle::~CEffectCircle()
{
	End();
}

void CEffectCircle::End(void)
{
}

BOOL CEffectCircle::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();

	double rr = sqrt((double)(sizeX*sizeX + sizeY*sizeY / 4));

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = sizeX/2;
	if (paraKosuu<3) para[2] = sizeY/2;
	if (paraKosuu<4) para[3] = 60;
	if (paraKosuu<5) para[4] = (int)rr;
	if (paraKosuu<6) para[5] = 0;
	if (paraKosuu<7) para[6] = para[5];
	if (paraKosuu<8) para[7] = para[6];

	lp->flag = TRUE;
	lp->command = EFFECT_CIRCLE;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<8;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectCircle::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();
	int r = (int)(sqrt((double)(sizeX*sizeX + sizeY*sizeY / 4)) + 0.5);

	if (lp->para[3] <= 1)
	{
		lp->command = EFFECT_FILL;
		lp->para[0] = lp->para[5];
		lp->para[1] = lp->para[6];
		lp->para[2] = lp->para[7];
	}
	else if (lp->para[3] >= r)
	{
		lp->command = EFFECT_NOP;
		if (lp->pic == -1)
		{
			lp->flag = FALSE;
		}
	}

	return TRUE;
}


void CEffectCircle::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCircle::Init(LPVOID para,int layer)
{
}

void CEffectCircle::Calcu(LPVOID lpEffect,int layer)
{
}

#if defined _TINYAN3DLIB_
void CEffectCircle::Print(LPVOID lpEffect,int layer)
{
	int shader = 0;
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;


	int dv = lp->countMax;
	int c = lp->count;
	if (dv<1)
	{
		dv = 1;
		c = 1;
	}
	
	int centerX = lp->para[1];
	int centerY = lp->para[2];
	int rSrc = lp->para[4];
	int rDst = lp->para[3];

	int colR = lp->para[5];
	int colG = lp->para[6];
	int colB = lp->para[7];

	int col = (lp->para[5] << 16) | (lp->para[6] << 8) | (lp->para[7]);
	int r = rSrc + ((rDst - rSrc) * c + dv / 2) / dv;
	if (r<1) r = 1;


	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	//upper
	int y1 = centerY - r;
	if (y1>=0)
	{
		y1++;
		if (y1>=sizeY) y1 = sizeY;
		CAllGeo::BoxFill(0,0,sizeX,y1,colR,colG,colB);
	}


	//lower
	int y2 = centerY + r;
	if (y2<sizeY)
	{
		if (y2<0) y2 = 0;
		CAllGeo::BoxFill(0,y2,sizeX,sizeY-y2,colR,colG,colB);
	}




	if (CheckEffectError()) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();









	SetTexture(GetBufferTexture());	//dummy
	float cols[4];
	cols[0] = ((float)colR) / 255.0f;
	cols[1] = ((float)colG) / 255.0f;
	cols[2] = ((float)colB) / 255.0f;
	cols[3] = 1.0f;
	SetColor(cols);


//OutputDebugString("[start2]");
	LPD3DXEFFECT effect = m_d3dxEffect;
	if (effect == NULL) return;
	SetAllColor();
	SetAllPercent();
	SetAllConst();
	SetAllTexture();


//OutputDebugString("[start3]");

	if (m_hTechnique == NULL)
	{
		OutputDebugString("[no tec]");
	}

	HRESULT hr = effect->SetTechnique(m_hTechnique[shader]);
	if (FAILED(hr))
	{
///		DXTRACE_ERR("settech",hr);
	}

	UINT passKosuu0 = 0;
	hr = effect->Begin(&passKosuu0,0);
	int passKosuu = passKosuu0;


	for (int i=0;i<passKosuu;i++)
	{
		effect->BeginPass(i);


		//center
		for (int j=-r;j<=r;j++)
		{
			int y = centerY + j;
			if ((y>=0) && (y<sizeY))
			{
				double xx = (double)(r*r - j*j);
				if (xx<0) xx = 0.0;
				xx = sqrt(xx);
				int x = (int)(xx+0.5);



				//left
				int x1 = centerX - x;
				if (x1>=0)
				{
					x1++;
					if (x1>sizeX) x1 = sizeX;

					POINT dstPoint[2];
					dstPoint[0].x = 0;
					dstPoint[0].y = y;
					dstPoint[1].x = x1;
					dstPoint[1].y = y;
//					POINT srcPoint[2];
					DrawLine(dstPoint,dstPoint);
				}

				//right
				int x2 = centerX + x;
				if (x2<sizeX)
				{
					if (x2<0) x2 = 0;

					int ln = sizeX-x2;
					if (ln>0)
					{
						POINT dstPoint[2];
						dstPoint[0].x = x2;
						dstPoint[0].y = y;
						dstPoint[1].x = screenSizeX;
						dstPoint[1].y = y;
					//	POINT srcPoint[2];
						DrawLine(dstPoint,dstPoint);
					}
				}

			}
		}

		effect->EndPass();
	}

	effect->End();
}

#else
void CEffectCircle::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;


	int dv = lp->countMax;
	int c = lp->count;
	if (dv<1)
	{
		dv = 1;
		c = 1;
	}
	
	int centerX = lp->para[1];
	int centerY = lp->para[2];
	int rSrc = lp->para[4];
	int rDst = lp->para[3];

	int col = (lp->para[5] << 16) | (lp->para[6] << 8) | (lp->para[7]);
	int r = rSrc + ((rDst - rSrc) * c + dv / 2) / dv;
	if (r<1) r = 1;


	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	//upper
	int y1 = centerY - r;
	if (y1>=0)
	{
		y1++;
		if (y1>=sizeY) y1 = sizeY;
		int* ptr = CMyGraphics::GetScreenBuffer();
		int ln = y1 * sizeX;
		for (int i=0;i<ln;i++)
		{
			*ptr++ = col;
		}
	}

	//lower
	int y2 = centerY + r;
	if (y2<sizeY)
	{
		if (y2<0) y2 = 0;

		int ln = (sizeY - y2)*sizeX;
		int* ptr = CMyGraphics::GetScreenBuffer();
		ptr += (y2*sizeX);
		for (int i=0;i<ln;i++)
		{
			*ptr++ = col;
		}
	}

	//center
	for (int j=-r;j<=r;j++)
	{
		int y = centerY + j;
		if ((y>=0) && (y<sizeY))
		{
			double xx = (double)(r*r - j*j);
			if (xx<0) xx = 0;
			xx = sqrt(xx);
			int x = (int)(xx+0.5);

			//left
			int x1 = centerX - x;
			if (x1>=0)
			{
				x1++;
				if (x1>sizeX) x1 = sizeX;
				int* ptr = CMyGraphics::GetScreenBuffer();
				ptr += (y * sizeX);
				for (int i=0;i<x1;i++)
				{
					*ptr++ = col;
				}
			}

			//right
			int x2 = centerX + x;
			if (x2<sizeX)
			{
				if (x2<0) x2 = 0;

				int ln = sizeX-x2;

				int* ptr = CMyGraphics::GetScreenBuffer();
				ptr += (y * sizeX);
				ptr += x2;
				for (int i=0;i<ln;i++)
				{
					*ptr++ = col;
				}
			}


		}
	}

}
#endif



/*_*/

