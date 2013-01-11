//
// effectCharaDualMask.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectDualMask.h"



CEffectDualMask::CEffectDualMask(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	SetConstKosuu(1);
	SetColorKosuu(1);
	Create("DualMask");
#endif
}


CEffectDualMask::~CEffectDualMask()
{
	End();
}

void CEffectDualMask::End(void)
{
}

BOOL CEffectDualMask::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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


	if (paraKosuu<1) para[0] = 20;	//frame

	if (paraKosuu<2) para[1] = 13;	//buffer layer

	if (paraKosuu<3) para[2] = 100;	//”¼“§–¾I—¹
	if (paraKosuu<4) para[3] = para[2];	//”¼“§–¾ŠJŽn
	if (paraKosuu<5) para[4] = 0;	//type
	if (paraKosuu<6) para[5] = 0;	//subframe

	if (paraKosuu < 7) para[6] = 0;	//fadeinFlag
	if (paraKosuu<8) para[7] = 0;	//type
	if (paraKosuu<9) para[8] = 0;	//subframe
	if (paraKosuu<10) para[9] = 255;	//R
	if (paraKosuu<11) para[10] = 255;	//G
	if (paraKosuu<12) para[11] = 255;	//B







	lp->flag = TRUE;
	lp->command = EFFECT_DUALMASK;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<12;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectDualMask::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectDualMask::BeginPrint(LPVOID para,int layer)
{

}

void CEffectDualMask::Init(LPVOID para,int layer)
{
}

void CEffectDualMask::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;
}


void CEffectDualMask::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;	//not use
	int c = lp->count;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int maskLayer = lp->para[1];
	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;
	if (lpPic->Check256()) return;

	CPicture* lpMaskPic = m_allEffect->GetPicture(maskLayer);
	if (lpMaskPic == NULL) return;
	if (lpMaskPic->Check256()) return;


	char* mask1 = lpPic->GetMaskPic();
	if (mask1 == NULL) return;
	char* mask2 = lpMaskPic->GetMaskPic();
	if (mask2 == NULL) return;

	POINT pt1 = m_allEffect->GetDstPoint(layer);
	POINT pt2 = m_allEffect->GetDstPoint(maskLayer);
	SIZE sz1 = lpPic->GetPicSize();
	SIZE sz2 = lpMaskPic->GetPicSize();
	int putX1 = pt1.x;
	int putY1 = pt1.y;
	int srcX1 = 0;
	int srcY1 = 0;
	int sizeX1 = sz1.cx;
	int sizeY1 = sz1.cy;

	if (!(lpPic->Clip(putX1,putY1,srcX1,srcY1,sizeX1,sizeY1))) return;

	int putX2 = pt2.x;
	int putY2 = pt2.y;
	int srcX2 = 0;
	int srcY2 = 0;
	int sizeX2 = sz2.cx;
	int sizeY2 = sz2.cy;

	if (!(lpMaskPic->Clip(putX2,putY2,srcX2,srcY2,sizeX2,sizeY2))) return;

	//‹¤’Ê•”•ªŽæ“¾

	RECT rc1;
	RECT rc2;

	SetRect(&rc1,putX1,putY1,putX1+sizeX1,putY1+sizeY1);
	SetRect(&rc2,putX2,putY2,putX2+sizeX2,putY2+sizeY2);

	RECT rc;
	if (!IntersectRect(&rc,&rc1,&rc2)) return;


	int deltaX1 = rc.left - rc1.left;
	int deltaY1 = rc.top - rc1.top;
	srcX1 += deltaX1;
	srcY1 += deltaY1;
	putX1 = rc.left;
	putY1 = rc.top;
	sizeX1 = rc.right - rc.left;
	sizeY1 = rc.bottom - rc.top;

	int deltaX2 = rc.left - rc2.left;
	int deltaY2 = rc.top - rc2.top;
	srcX2 += deltaX2;
	srcY2 += deltaY2;
	putX2 = rc.left;
	putY2 = rc.top;
	sizeX2 = rc.right - rc.left;
	sizeY2 = rc.bottom - rc.top;

	if (sizeX1 <= 0) return;
	if (sizeY1 <= 0) return;
	if (sizeX2 <= 0) return;
	if (sizeY2 <= 0) return;


	int psEnd = lp->para[2];
	int psStart = lp->para[3];
	int psType = lp->para[4];
	int psSubFrame = lp->para[5];
	
	int ps = CCalcuSpeed::calcu(c,dv,psStart*100,psEnd*100,psSubFrame,psType);
	int ps256 = (ps * 256) / 10000;

	int loopSizeX = sizeX1;
	int loopSizeY = sizeY1;

	int fadeinFlag = lp->para[6];
	int fadeinMulti = 0;
	LONGLONG fadeinAdd = 0;

	float f3dps = 0.0f;

	if (fadeinFlag)
	{
		int fpsSubFrame = lp->para[8];
		int fpsSubType = lp->para[7];
		int fps = CCalcuSpeed::calcu(c,dv,0,255,fpsSubFrame,fpsSubType);

		f3dps = ((float)(255-fps)) / 255.0f;

		int flashR = ((255-fps) * (lp->para[9])) /255;
		int flashG = ((255-fps) * (lp->para[10])) /255;
		int flashB = ((255-fps) * (lp->para[11])) /255;

		fadeinMulti = (fps<<16) | (fps<<8) | fps;

		LONGLONG fr = (LONGLONG)flashR;
		LONGLONG fg = (LONGLONG)flashG;
		LONGLONG fb = (LONGLONG)flashB;

		fr <<= 32;
		fg <<= 16;
		fadeinAdd = fr | fg | fb;
	}




#if defined _TINYAN3DLIB_
	if (CheckEffectError()) return;

	float const1 = (float)ps256;
	const1 /= 256.0f;
	SetConst(const1);

	float fadeColor[4];
	fadeColor[0] = ((float)(lp->para[9])) / 255.0f;
	fadeColor[1] = ((float)(lp->para[10])) / 255.0f;
	fadeColor[2] = ((float)(lp->para[11])) / 255.0f;
	fadeColor[3] = f3dps;
	SetColor(fadeColor);

	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture(),0);
	CMyTexture* lpTexture2 = (CMyTexture*)(lpMaskPic->GetTexture());
	SetTexture(lpTexture2->GetTexture(),1);

	POINT dstPoint;
	dstPoint.x = putX1;
	dstPoint.y = putY1;
	SIZE dstSize;
	dstSize.cx = sizeX1;
	dstSize.cy = sizeY1;
	POINT srcPoint;
	srcPoint.x = srcX1;
	srcPoint.y = srcY1;
	POINT srcPoint2;
	srcPoint2.x = srcX2;
	srcPoint2.y = srcY2;

	Blt2(dstPoint,dstSize,srcPoint,srcPoint2);


#else
	int* src = (int*)(lpPic->GetBuffer());
	int srcPitch = sz1.cx * sizeof(int);
	int srcMaskPitch = sz1.cx;
	int maskMaskPitch = sz2.cx;
	int dstPitch = screenSizeX * sizeof(int);

	src += sz1.cx * srcY1;
	src += srcX1;

	mask1 += sz1.cx * srcY1;
	mask1 += srcX1;

	mask2 += sz2.cx * srcY2;
	mask2 += srcX2;

	int* dst = CMyGraphics::GetScreenBuffer();
	dst += screenSizeX * putY1;
	dst += putX1;



	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi


		pxor mm0,mm0

		mov eax,ps256
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

		mov eax,01000100h
		movd mm7,eax
		punpckldq mm7,mm7


		mov ebx,mask1
		mov edx,mask2
		mov esi,src
		mov edi,dst

		mov ecx,loopSizeY
LOOP1:
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov ecx,loopSizeX
LOOP2:
		push ecx
		
		xor eax,eax
		mov al,[ebx]
		or eax,eax
		jz SKIP1

		movd mm4,eax
		mov al,[edx]
		or eax,eax
		jz SKIP1

		inc eax
		movd mm5,eax
		punpcklwd mm4,mm4
		punpcklwd mm5,mm5
		punpckldq mm4,mm4
		punpckldq mm5,mm5
		pmullw mm4,mm5
		psrlw mm4,8
		pmullw mm4,mm6
		psrlw mm4,8
		movq mm5,mm7
		psubw mm5,mm4

		mov eax,[esi]
		movd mm1,eax
		punpcklbw mm1,mm0

		mov eax,fadeinFlag
		or eax,eax
		jz SKIP00

		mov eax,fadeinMulti
		movd mm2,eax
		punpcklbw mm2,mm0
		pmullw mm1,mm2
		psrlw mm1,8
		paddw mm1,fadeinAdd

SKIP00:


		mov eax,[edi]
		movd mm2,eax
		punpcklbw mm2,mm0

		pmullw mm4,mm1
		pmullw mm5,mm2
		paddw mm4,mm5
		psrlw mm4,8
		packuswb mm4,mm0
		movd eax,mm4

		mov [edi],eax

SKIP1:
		pop ecx
		add esi,4
		add edi,4
		inc ebx
		inc edx
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx

		add edi,dstPitch
		add esi,srcPitch
		add ebx,srcMaskPitch
		add edx,maskMaskPitch
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

BOOL CEffectDualMask::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}


/*_*/

