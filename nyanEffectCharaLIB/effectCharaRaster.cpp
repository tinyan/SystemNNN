//
// effectCharaRaster.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectCharaRaster.h"



CEffectCharaRaster::CEffectCharaRaster(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	SetConstKosuu(2);
	Create("CharaRaster");
#endif
}


CEffectCharaRaster::~CEffectCharaRaster()
{
	End();
}

void CEffectCharaRaster::End(void)
{
}

BOOL CEffectCharaRaster::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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

	if (paraKosuu<2) para[1] = 32;	//•
	if (paraKosuu<3) para[2] = 10;	//omega
	if (paraKosuu<4) para[3] = 100;	//fay

	if (paraKosuu<5) para[4] = 0;	//type
	if (paraKosuu<6) para[5] = 0;	//subframe

	if (paraKosuu<7) para[6] = 100;	//”¼“§–¾I—¹
	if (paraKosuu<8) para[7] = para[6];	//”¼“§–¾ŠJŽn
	if (paraKosuu<9) para[8] = 0;	//type
	if (paraKosuu<10) para[9] = 0;	//subframe


	lp->flag = TRUE;
	lp->command = EFFECT_CHARARASTER;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectCharaRaster::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectCharaRaster::BeginPrint(LPVOID para,int layer)
{

}

void CEffectCharaRaster::Init(LPVOID para,int layer)
{
}

void CEffectCharaRaster::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
}


void CEffectCharaRaster::Print(LPVOID lpEffect,int layer)
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

	int rasterSize = lp->para[1];
	int omega = lp->para[2];
	int fay = lp->para[3];
	int rasterSpeedType = lp->para[4];
	int rasterSubFrame = lp->para[5];

	int transPercentEnd = lp->para[6];
	int transPercentStart = lp->para[7];
	int transSpeedType = lp->para[8];
	int transSubFrame = lp->para[9];


	int raster = CCalcuSpeed::calcu(c,dv,0,rasterSize*100,rasterSubFrame,rasterSpeedType);
	int transPercent = 256;
	if ((transPercentStart != 100) || (transPercentEnd != 100))
	{
		transPercent = CCalcuSpeed::calcu(c,dv,transPercentStart*256,transPercentEnd*256,transSubFrame,transSpeedType);
		transPercent /= 100;
		if (transPercent<0) transPercent = 0;
		if (transPercent>256) transPercent = 256;
	}

	double ml = (double)raster;
	ml *= 0.01;




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


	double k = (double)screenSizeY;
	k = 1/k;
	k *= 3.14159*2.0*3;
	k *= (double)fay;
	k *= 0.01;


	for (int j=0;j<sizeY;j++)
	{
		int y = srcY + j;

		double th = (double)(y + c * omega);
		th *= k;
		
		int d = (int)(cos(th)*ml+0.5);
		if (d <= -screenSizeX) d = -(screenSizeX-1);
		if (d >= (screenSizeX-1)) d = screenSizeX-2;
		rasterWork[putY+j] = d;
	}


#if defined _TINYAN3DLIB_
	if (CheckEffectError()) return;

	

	float limit1 = (float)(lpPic->m_charaClipXStart);
	float limit2 = (float)(lpPic->m_charaClipXEnd);
	float px = (float)picSizeX;
	if (px>0.0f)
	{
		limit1 /= px;
		limit2 /= px;
	}
	else
	{
		limit1 = 0.0f;
		limit2 = 1.0f;
	}

	SetConst(limit1);
	SetConst(limit2,1);


	int ww = raster;
	if (ww<0) ww *= -1;

	if (ww > screenSizeX) ww = screenSizeX;


	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture());


	int* workV = m_allEffect->GetTempWork();
	workV += screenSizeY;

	float div3 = 1.0f / 3.0f;
	float divSizeX = 1.0f / (float)(picSizeX);

	for (int j=0;j<screenSizeY;j++)
	{
		float x1 = 0.0f;

		if ((j>=putY) && (j<putY+sizeY))
		{
			x1 = (float)(rasterWork[j-putY]);
		}

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

	dstPoint.x = putX - ww;
	dstPoint.y = putY;
	dstSize.cx = sizeX + ww*2;
	dstSize.cy = sizeY;
	srcPoint.x = srcX - ww;
	srcPoint.y = srcY;

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

}

BOOL CEffectCharaRaster::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


/*_*/

