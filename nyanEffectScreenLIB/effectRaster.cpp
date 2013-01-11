//
// effectRaster.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectRaster.h"


CEffectRaster::CEffectRaster(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	Create("Raster");
#endif
}


CEffectRaster::~CEffectRaster()
{
	End();
}

void CEffectRaster::End(void)
{
}

BOOL CEffectRaster::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[5];
	int k = paraKosuu;
	if (k>5) k = 5;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();

	if (paraKosuu<1) para[0] = 60;
	if (paraKosuu<2) para[1] = 0;
	if (paraKosuu<3) para[2] = 64;
	if (paraKosuu<4) para[3] = 0;//type
	if (paraKosuu<5) para[4] = 0;//subFrame

	if (para[1] >= screenSizeX/2) para[1] = screenSizeX / 2 - 1;
	if (para[2] >= screenSizeX/2) para[2] = screenSizeX / 2 - 1;

	lp->flag = TRUE;
	lp->command = EFFECT_RASTER;
	lp->count = 0;
	lp->countMax = para[0];

	for (i=0;i<5;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectRaster::CountIsMax(LPVOID lpEffect,int layer)
{
	return TRUE;
}


void CEffectRaster::BeginPrint(LPVOID para,int layer)
{

}

void CEffectRaster::Init(LPVOID para,int layer)
{
}

void CEffectRaster::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectRaster::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

//	int raster[MAXSCREENSIZEY];
//	int* raster = CEffectSimpleWipe::m_shapeWork;
	int* raster = m_allEffect->GetTempWork();

	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[3];
	int subFrame = lp->para[4];

	int ml100 = CCalcuSpeed::calcu(count,countMax,100 * lp->para[1],100 * lp->para[2],subFrame,type);

	if (ml100 < 100) return;

	double ml = (double)ml100;
	ml /= 100.0;


	int c = lp->count;

	int h = 1;
	if (lp->para[2] > lp->para[1])
	{
		c = lp->countMax - c;
		h = -1;
	}


	double dScreenSizeY = (double)screenSizeY;

	for (int i=0;i<screenSizeY;i++)
	{
		double th = (double)(i*h + c * 10 );
		th *= (3.14159 * 2.0 / dScreenSizeY * 3);
		int d = (int)(cos(th)*ml+0.5);
		if (d <= -screenSizeX) d = -(screenSizeX-1);
		if (d >= (screenSizeX-1)) d = screenSizeX-2;
		raster[i] = d;
	}

#if defined _TINYAN3DLIB_

	if (CheckEffectError()) return;


	float div3 = 1.0f / 3.0f;
	float divSizeX = 1.0f / ((float)screenSizeX);

	for (int j=0;j<screenSizeY;j++)
	{
		float x1 = (float)(raster[j]);

		x1 *= divSizeX;
		x1 += 1.0f;
		x1 *= div3;

		if (x1<0.0f) x1 = 0.0f;
		if (x1>0.995f) x1 = 0.995f;

		int x1Int = (int)(x1*65536.0f);

		unsigned int x1High = x1Int >> 8;
		unsigned int x1Low  = x1Int & 0xff;


		//XRGB -> RGBA
		raster[j] = (int)((0 << 24) | (x1High << 16) | (x1Low<<8) | 0);
	}

	SetWorkV(raster,screenSizeY);

	ExchangeScreenAndBuffer();
	SetTexture(GetBufferTexture(),0);


	LPDIRECT3DTEXTURE9 vTexture = CMyDirect3D::GetVTexture();
	SetTexture(vTexture,1);


	POINT srcPoint;
	srcPoint.x = 0;
	srcPoint.y = 0;

	POINT dstPoint;
	dstPoint.x = 0;
	dstPoint.y = 0;

	SIZE dstSize;
	dstSize.cx = screenSizeX;
	dstSize.cy = screenSizeY;


	Blt(dstPoint,dstSize,srcPoint);
#else

	int* ras = raster;
	int* screen = CMyGraphics::GetScreenBuffer();

	int loopX = screenSizeX;
	int loopY = screenSizeY;

	int srcPitch = screenSizeX * sizeof(int);

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov ebx,ras
		mov edx,loopY
		mov esi,screen

LOOP1:
		push esi

		mov eax,[ebx]
		or eax,eax
		jz SKIP
		test eax,80000000h
		jnz MINUS

		push eax
		mov edi,esi
		mov ecx,eax
		mov eax,0
		cld
		rep stosd
		pop eax

		mov ecx,eax
		neg ecx
		add ecx,screenSizeX

		mov eax,ecx
		dec eax
		shl eax,2
		add esi,eax
		add edi,eax

		std
		rep movsd

		jmp NEXT
MINUS:
		mov edi,esi
		push eax
		mov ecx,eax
		add ecx,screenSizeX
		neg eax
		shl eax,2
		add esi,eax
		cld
		rep movsd
		pop eax
		mov ecx,eax
		neg ecx
		mov eax,0
		cld
		rep stosd
NEXT:

SKIP:
		pop esi
		add esi,srcPitch
		add ebx,4
		dec edx
		jnz LOOP1

		cld


		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#endif
}
