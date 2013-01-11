//
// effectwater.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectwater.h"


CEffectWater::CEffectWater(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int sizeY = CMyGraphics::GetScreenSizeY();

	m_effectWaterY = new int[sizeY];
	m_effectWaterCount = 0;

#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	Create("Water");
#endif

}

CEffectWater::~CEffectWater()
{
	End();
}

void CEffectWater::End(void)
{
	DELETEARRAY(m_effectWaterY);
}

void CEffectWater::InitParameter(LPVOID lpEffect, int layer)
{
	int para[4];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<4;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,4,para,layer);
}

BOOL CEffectWater::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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

	int sizeY = CMyGraphics::GetScreenSizeY();

	if (paraKosuu<1) para[0] = 20;
	if (paraKosuu<2) para[1] = sizeY/2;
	if (paraKosuu<3) para[2] = 100;	//Šg‘å“
	if (paraKosuu<4) para[3] = 0;	//‚¸‚ç‚µ‚x


	if (para[1] < 0) para[1] = 0;
	if (para[1] >= sizeY) para[1] = sizeY-1;
	lp->flag = TRUE;
	lp->command = EFFECT_WATER;
	lp->count = 0;
	lp->countMax = 99999;

	for (i=0;i<4;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectWater::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectWater::BeginPrint(LPVOID para,int layer)
{

}

void CEffectWater::Init(LPVOID para,int layer)
{
}

void CEffectWater::Calcu(LPVOID lpEffect,int layer)
{
}

#if defined _TINYAN3DLIB_
void CEffectWater::Print(LPVOID lpEffect,int layer)
{
	m_effectWaterCount++;
	if (m_effectWaterCount > 1000000) m_effectWaterCount = 0;

	CalcuEffectWater(lpEffect);

	if (CheckEffectError()) return;

	EFFECT* lp = (EFFECT*)lpEffect;



	CMyDirect3D::CopyScreenToBuffer();

	int* waterWork = m_allEffect->GetTempWork();
	
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	float divSizeY = 1.0f / (float)(screenSizeY);
	float div3 = 1.0f / 3.0f;


	int yStart = lp->para[1];


	for (int j=0;j<screenSizeY;j++)
	{
		int d = j;
		if (j>=yStart)
		{
			d = m_effectWaterY[j];
		}

		float y1 = (float)d;
		y1 *= divSizeY;
		y1 += 1.0f;
		y1 *= div3;

		if (y1<0.0f) y1 = 0.0f;
		if (y1>0.995f) y1 = 0.995f;

		int y1Int = (int)(y1*65536.0f);

		unsigned int y1High = y1Int >> 8;
		unsigned int y1Low  = y1Int & 0xff;


		//XRGB -> RGBA
		*(waterWork +j)   = (int)((0 << 24) | (y1High << 16) | (y1Low<<8) | 0);
//		*(workV2+j)   = (int)((x4Low << 24) | (x3High << 16) | (x3Low<<8) | x4High);
	}

	SetTexture(CMyDirect3D::GetBufferTexture(),0);
	SetWorkV(waterWork,screenSizeY);
	LPDIRECT3DTEXTURE9 vTexture = CMyDirect3D::GetVTexture();
	SetTexture(vTexture,1);



	POINT pt;
	pt.x = 0;
	pt.y = yStart;
	SIZE sz;
	sz.cx = screenSizeX;
	sz.cy = screenSizeY - yStart;
	POINT srcPoint;
	srcPoint.x = 0;
	srcPoint.y = yStart;
	Blt(pt,sz,srcPoint);
//	BoxFill(pt,sz);
}
#else

void CEffectWater::Print(LPVOID lpEffect,int layer)
{
	m_effectWaterCount++;
	if (m_effectWaterCount > 1000000) m_effectWaterCount = 0;

	CalcuEffectWater(lpEffect);

//	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;


	int yStart = lp->para[1];

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	for (int j=yStart;j<sizeY;j++)
	{
		int* src = CMyGraphics::GetScreenBuffer();

		int* dst = src + j * sizeX;

		src += (m_effectWaterY[j] * sizeX);

		for (int i=0;i<sizeX;i++)
		{
			*dst = *src;
			dst++;
			src++;
		}
	}
}
#endif


void CEffectWater::CalcuEffectWater(LPVOID lpEffect)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int yStart = lp->para[1];

	int sizeY = CMyGraphics::GetScreenSizeY();

	int i;
	for (i=0;i<sizeY;i++) m_effectWaterY[i] = 0;

	int k = 0;
	for (i=yStart;i<sizeY;i++)
	{
		int dv = sizeY-yStart;
		if (dv<1) dv = 1;

		int ml = k;

		double th = (-m_effectWaterCount*3 + ((dv-k)*(dv-k)) / dv *4);
		th *= 3.14159 * 2;
		th /= 100.0;

		int d = (int)(cos(th) * 8 * (ml+dv) / (dv*2)+ 0.5);
		d += (yStart - k - 10);

		if (d>=yStart) d = yStart -1;
		if (d<0) d = 0;

		m_effectWaterY[i] = d;
		k++;
	}
}
