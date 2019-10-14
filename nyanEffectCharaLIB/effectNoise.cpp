//
// effectNoise.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectNoise.h"



CEffectNoise::CEffectNoise(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	Create("Noise");
#endif
}


CEffectNoise::~CEffectNoise()
{
	End();
}

void CEffectNoise::End(void)
{
}

BOOL CEffectNoise::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = 2;	//こすう
	if (para[1]>16) para[1] = 16;

	if (paraKosuu<3) para[2] = 32;	//はば
	if (paraKosuu<4) para[3] = 2;	//なみ

	if (paraKosuu<5) para[4] = 40;	//へいきんながさ
	if (paraKosuu<6) para[5] = 50;	//ながさらんだむ％

	if (paraKosuu<7) para[6] = 50;	//へいきん表示じかん
	if (paraKosuu<8) para[7] = 0;	//いどうそくど

	if (paraKosuu<9) para[8] = 0;	//全体ランダム

	if (paraKosuu<10) para[9] = 100;	//半透明終了
	if (paraKosuu<11) para[10] = para[9];	//半透明開始
	if (paraKosuu<12) para[11] = 0;	//type
	if (paraKosuu<13) para[12] = 0;	//subframe


	lp->flag = TRUE;
	lp->command = EFFECT_NOISE;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	for (i=0;i<para[1];i++)
	{
		InitNoise(lp,i,layer);
	}

	return TRUE;

}


BOOL CEffectNoise::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

//	lp->command = EFFECT_NOP;
//	if (lp->pic == -1)
//	{
//		lp->flag = FALSE;
//	}
//
//	return TRUE;
	return FALSE;
}


void CEffectNoise::BeginPrint(LPVOID para,int layer)
{

}

void CEffectNoise::Init(LPVOID para,int layer)
{
}

void CEffectNoise::InitNoise(LPVOID lpEffect,int n,int layer)
{
	//count,y,len,pow

	EFFECT* lp = (EFFECT*)lpEffect;

	int k= 16 + n * 8;

	CPicture* lpPic = m_allEffect->GetPicture(layer);

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int sizeY = screenSizeY;
	
	if (lpPic != NULL)
	{
		SIZE sz = lpPic->GetPicSize();
		sizeY = sz.cy;
	}

	int wy = lp->para[6];
	int dw = (wy * 2) / 10;
	if (dw > 0)
	{
		wy += (rand() % (dw*2));
		wy -= dw;
		if (wy<1) wy = 1;
	}
	lp->para[k+0] = wy;



	int c0 = lp->para[4];
	int cdiv = (lp->para[5] * c0) / 100;
	if (cdiv > 0)
	{
		c0 += (rand() % (cdiv*2));
		c0 -= cdiv;
	}

	if (c0<1) c0= 1;
	lp->para[k+2] = c0;

	int sy = sizeY - c0;
	if (sy<1) sy = 1;
	lp->para[k+1] = rand() % sy;

	lp->para[k+3] = 20 + (rand() % 60);
}

void CEffectNoise::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
	int kosuu = lp->para[1];

	int speed = lp->para[7];

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	SIZE sz = lpPic->GetPicSize();
	int sizeY = sz.cy;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	for (int i=0;i<kosuu;i++)
	{
		int k = 16 + i * 8;
		lp->para[k]--;
		if (lp->para[k]<=0)
		{
			InitNoise(lp,i,layer);
		}

		int y = lp->para[k+1];
		int ln = lp->para[k+2];

		y += speed;
		lp->para[k+1] = y;
		if ((y<-ln) || (y>=sizeY))
		{
			InitNoise(lp,i,layer);
		}

		int pw = lp->para[k+3];

		pw += ((rand() % 10) - 6);

		if ((rand() % 100) < 2)
		{
			pw += (rand() % 160) - 40;
		}

		if (pw<30) pw = 30;
		if (pw>100) pw = 100;
		lp->para[k+3] = pw;
	}
}




void CEffectNoise::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;
	if (lpPic->Check256()) return;

	int* rasterWork = m_allEffect->GetTempWork();

	int transPercentEnd = lp->para[9];
	int transPercentStart = lp->para[10];
	int transSpeedType = lp->para[11];
	int transSubFrame = lp->para[12];

	int transPercent = 256;
	if ((transPercentStart != 100) || (transPercentEnd != 100))
	{
		transPercent = CCalcuSpeed::calcu(c,dv,transPercentStart*256,transPercentEnd*256,transSubFrame,transSpeedType);
		transPercent /= 100;
		if (transPercent<0) transPercent = 0;
		if (transPercent>256) transPercent = 256;
	}

	int kosuu = lp->para[1];



	int zentaiRnd = lp->para[8];

	for (int j=0;j<screenSizeY;j++)
	{
		rasterWork[j] = 0;
		if (zentaiRnd > 0)
		{
			int r = rand() % zentaiRnd;
			r += 50;
			r /= 100;

			if (r>0)
			{
				rasterWork[j] = r * ((rand() % 2)*2-1);
			}

		}
	}

	int pow = lp->para[2];
	int nami = lp->para[3];
	if (nami<1) nami = 1;


	POINT pt = m_allEffect->GetDstPoint(layer);
	int putX = pt.x;
	int putY = pt.y;
	int srcX = 0;
	int srcY = 0;


	SIZE sz = lpPic->GetPicSize();
	int sizeX = sz.cx;
	int sizeY = sz.cy;

	int picSizeX = sizeX;
	int picSizeY = sizeY;

	if (putY>=screenSizeY) return;
	if ((putY+sizeY)<0) return;

	if (putY<0)
	{
		sizeY += putY;
		srcY -= putY;
		putY = 0;
	}
	if (sizeY<=0) return;

	if ((putY+sizeY) > screenSizeY)
	{
		sizeY = screenSizeY - putY;
	}
	if (sizeY<=0) return;



	for (int n=0;n<kosuu;n++)
	{
		int k = 16 + n * 8;
		//count,y,len,pow
		int yStart = lp->para[k+1];
		int ln = lp->para[k+2];
		int pw = lp->para[k+3];

yStart += putY;

		int p = (pow * pw) / 100;
		if (p<1) p = 1;

		int r = 100;

		int lnDiv = ln / 2;
		if (lnDiv < 1) lnDiv = 1;

		for (int y=0;y<ln;y++)
		{
			int yy = yStart + y;

			if ((y % nami) == 0)
			{
				r = (rand() % 70) + 30;
			}

			int namiMul = nami - (y % nami)*2;
			int signFlag = 1;
			if ((y % (nami*2)) >= nami) signFlag = -1;


			int lnMul = y % lnDiv;
			if ((y % ln) >= lnDiv)
			{
				if ((y % ln)<lnDiv*2)
				{
					lnMul = lnDiv - lnMul;
				}
				else
				{
					lnMul = 0;
				}
			}


			int delta = r * lnMul * namiMul * p;
			delta /= (lnDiv*nami*100);
			delta *= signFlag;

			if ((yy>=0) && (yy<screenSizeY))
			{
				rasterWork[yy] += delta;
			}
		}
	}


#if defined _TINYAN3DLIB_

	if (CheckEffectError()) return;


	float div3 = 1.0f / 3.0f;
	float divSizeX = 1.0f / ((float)screenSizeX);

	for (int j=0;j<screenSizeY;j++)
	{
		float x1 = (float)(rasterWork[j]);

		x1 *= divSizeX;
		x1 += 1.0f;
		x1 *= div3;

		if (x1<0.0f) x1 = 0.0f;
		if (x1>0.995f) x1 = 0.995f;

		int x1Int = (int)(x1*65536.0f);

		unsigned int x1High = x1Int >> 8;
		unsigned int x1Low  = x1Int & 0xff;


		//XRGB -> RGBA
		rasterWork[j] = (int)((0 << 24) | (x1High << 16) | (x1Low<<8) | 0);
	}

	SetWorkV(rasterWork,screenSizeY);

	CMyTexture* lpTexture1 = (CMyTexture*)(lpPic->GetTexture());
	if (lpTexture1 == NULL) return;
	SetTexture(lpTexture1->GetTexture(),0);


	LPDIRECT3DTEXTURE9 vTexture = CMyDirect3D::GetVTexture();
	SetTexture(vTexture,1);


	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;

	POINT dstPoint;
	dstPoint.x = putX;
	dstPoint.y = putY;

	SIZE dstSize;
	dstSize.cx = sizeX;
	dstSize.cy = sizeY;


	Blt(dstPoint,dstSize,srcPoint);






#else
	int* ras = rasterWork;
	int* screen = CMyGraphics::GetScreenBuffer();
	int srcPitch = picSizeX * sizeof(int);
	int lPitch = screenSizeX * sizeof(int);
	int maskPitch = picSizeX;

	ras += putY;
	int* dst = CMyGraphics::GetScreenBuffer();
	dst += putY * screenSizeX;

	int* src = lpPic->GetPictureBuffer();
	src += srcY * picSizeX;

	char* mask = lpPic->GetMaskPic();
	if (mask == NULL) return;
	mask += srcY * picSizeX;

#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld
		pxor mm0,mm0

		mov eax,transPercent
		movd mm3,eax


		mov edx,ras
		mov ecx,sizeY
		mov esi,src
		mov ebx,mask
		mov edi,dst
LOOP1:
		push ebx
		push ecx
		push edx
		push esi
		push edi


		mov eax,[edx]
		add eax,putX
		cmp eax,screenSizeX
		jns SKIP99

		mov ecx,sizeX
		add eax,ecx
		cmp eax,1
		js SKIP99
		sub eax,ecx

		cmp eax,0
		jns SKIP1
		
		add ecx,eax
		cmp ecx,1
		js SKIP99
		sub ebx,eax
		add eax,eax
		add eax,eax
		sub esi,eax
		mov eax,0
SKIP1:
		add edi,eax
		add edi,eax
		add edi,eax
		add edi,eax
		add eax,ecx
		cmp eax,screenSizeX
		js OK1
		sub eax,ecx
		mov ecx,screenSizeX
		sub ecx,eax
OK1:
LOOP2:
		xor eax,eax
		mov al,[ebx]
		movd mm4,eax
		pmullw mm4,mm3
		mov edx,[esi]
		psrlw mm4,8
		movd eax,mm4

		cmp al,255
		jz NORMAL
		or eax,eax
		jz LAST

		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5
		neg eax
		add eax,256
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

		mov eax,[esi]
		movd mm1,eax
		mov eax,[edi]
		movd mm2,eax
		punpcklbw mm1,mm0
		punpcklbw mm2,mm0
		pmullw mm1,mm5
		pmullw mm2,mm6
		//stall
		paddw mm1,mm2
		psrlw mm1,8
		packuswb mm1,mm1
		movd edx,mm1
NORMAL:
		mov [edi],edx
LAST:
		inc ebx
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2

SKIP99:
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx

		add edi,lPitch
		add esi,srcPitch
		add ebx,maskPitch
		add edx,4
		dec ecx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax

		emms
	}

#endif

#endif
}

BOOL CEffectNoise::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


/*_*/

