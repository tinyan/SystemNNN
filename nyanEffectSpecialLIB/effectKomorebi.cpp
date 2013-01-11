//
// effectkomorebi.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectKomorebi.h"


CEffectKomorebi::CEffectKomorebi(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	SetColorKosuu(1);
	Create("Komorebi");
#endif
}

CEffectKomorebi::~CEffectKomorebi()
{
	End();
}

void CEffectKomorebi::End(void)
{
}


BOOL CEffectKomorebi::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;	//pic2
	if (para[1]<0) para[1] = 0;
	if (para[1]>15) para[1] = 15;

	if (paraKosuu<3) para[2] = 128;
	if (paraKosuu<4) para[3] = para[2];
	if (paraKosuu<5) para[4] = para[3];
	if (paraKosuu<6) para[5] = para[2];
	if (paraKosuu<7) para[6] = para[3];
	if (paraKosuu<8) para[7] = para[4];

	if (paraKosuu<9) para[8] = -1;	//pic1
	if (para[8]<-1) para[8] = -1;
	if (para[8]>15) para[8] = 15;

	if (paraKosuu<10) para[9] = 0;
	if (paraKosuu<11) para[10] = 0;

	lp->flag = TRUE;
	lp->command = EFFECT_KOMOREBI;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectKomorebi::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectKomorebi::BeginPrint(LPVOID para,int layer)
{

}

void CEffectKomorebi::Init(LPVOID para,int layer)
{
}

void CEffectKomorebi::Calcu(LPVOID lpEffect,int layer)
{

}


void CEffectKomorebi::Print(LPVOID lpEffect,int layer)
{
	if (layer == -1) layer = 0;

	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();



	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
		c = 0;
	}

	if (c<0) c = 0;
	if (c>dv) c = dv;

	int type = lp->para[9];
	int subFrame = lp->para[10];


	int dr = CCalcuSpeed::calcu(c,dv,lp->para[5],lp->para[2],subFrame,type);
	int dg = CCalcuSpeed::calcu(c,dv,lp->para[6],lp->para[3],subFrame,type);
	int db = CCalcuSpeed::calcu(c,dv,lp->para[7],lp->para[4],subFrame,type);


//	int dr = ((lp->para[2] - lp->para[5]) * c) / dv + lp->para[5];
//	int dg = ((lp->para[3] - lp->para[6]) * c) / dv + lp->para[6];
//	int db = ((lp->para[4] - lp->para[7]) * c) / dv + lp->para[7];


	int addColor = 0;
	int subColor = 0;

	if (dr>=0)
	{
		addColor |= (dr<<16);
	}
	else
	{
		subColor |= ((-dr)<<16);
	}

	if (dg>=0)
	{
		addColor |= (dg<<8);
	}
	else
	{
		subColor |= ((-dg)<<8);
	}

	if (db>=0)
	{
		addColor |= (db<<0);
	}
	else
	{
		subColor |= ((-db)<<0);
	}

	int layer1 = lp->para[8];
	if (layer1 == -1) layer1 = layer;
//	int pic = m_effect->m_effect[layer1].pic;
	int pic = m_allEffect->GetOtherLayerPic(layer1);
	CPicture* lpPic = m_allEffect->GetPicture(layer);	//debug 2005-05-09
	if (lpPic == NULL) return;
	if (lpPic->Check256()) return;
	if (lpPic->CheckMaskExist() == FALSE) return;

	int layer2 = lp->para[1];
	if (layer2 == -1) return;
//	int pic2 = m_effect->m_effect[layer2].pic;
	int pic2 = m_allEffect->GetOtherLayerPic(layer2);
	CPicture* lpPic2 = m_allEffect->GetPicture(layer2);	//debug 2005-05-09
	if (lpPic2 == NULL) return;
	if (lpPic2->Check256()) return;
	if (lpPic2->CheckMaskExist() == FALSE) return;

//	RECT rc = m_effect->m_effect[layer1].dst;
	POINT rcPoint = m_allEffect->GetDstPoint(layer1);
	SIZE rcSize = m_allEffect->GetDstSize(layer1);


//	int putX1 = rc.left;
//	int putY1 = rc.top;
//	int sizeX1 = rc.right;
//	int sizeY1 = rc.bottom;
	int putX1 = rcPoint.x;
	int putY1 = rcPoint.y;
	int sizeX1 = rcSize.cx;
	int sizeY1 = rcSize.cy;
	int srcX1 = 0;
	int srcY1 = 0;

	int picSizeX1 = sizeX1;
	int picSizeY1 = sizeY1;

	int top1 = lpPic->m_charaClipYStart;
	int bottom1 = lpPic->m_charaClipYEnd;
	int left1 = lpPic->m_charaClipXStart;
	int right1 = lpPic->m_charaClipXEnd;

	putX1 += left1;
	putY1 += top1;
	sizeX1 = right1 - left1;
	sizeY1 = bottom1 - top1;
	srcX1 += left1;
	srcY1 += top1;

	if ((sizeX1<1) || (sizeY1<1)) return;

	if (lpPic->Clip(putX1,putY1,srcX1,srcY1,sizeX1,sizeY1) == FALSE) return;


//	RECT rc2 = m_effect->m_effect[layer2].dst;
	POINT rc2Point = m_allEffect->GetDstPoint(layer2);
	SIZE rc2Size = m_allEffect->GetDstSize(layer2);

//	int putX2 = rc2.left;
//	int putY2 = rc2.top;
//	int sizeX2 = rc2.right;
//	int sizeY2 = rc2.bottom;
	int putX2 = rc2Point.x;
	int putY2 = rc2Point.y;
	int sizeX2 = rc2Size.cx;
	int sizeY2 = rc2Size.cy;
	int srcX2 = 0;
	int srcY2 = 0;

	int picSizeX2 = sizeX2;
	int picSizeY2 = sizeY2;

	int top2 = lpPic2->m_charaClipYStart;
	int bottom2 = lpPic2->m_charaClipYEnd;
	int left2 = lpPic2->m_charaClipXStart;
	int right2 = lpPic2->m_charaClipXEnd;

	putX2 += left2;
	putY2 += top2;
	sizeX2 = right2 - left2;
	sizeY2 = bottom2 - top2;
	srcX2 += left2;
	srcY2 += top2;

	if ((sizeX2<1) || (sizeY2<1)) return;

	if (lpPic2->Clip(putX2,putY2,srcX2,srcY2,sizeX2,sizeY2) == FALSE) return;

	//
	//
	//

	int putX = putX1;
	if (putX2>putX) putX = putX2;

	if (putX1<putX)
	{
		int deltaX = putX - putX1;

		putX1 += deltaX;
		srcX1 += deltaX;
		sizeX1 -= deltaX;
		if (sizeX1<1) return;
	}

	if (putX2<putX)
	{
		int deltaX = putX - putX2;

		putX2 += deltaX;
		srcX2 += deltaX;
		sizeX2 -= deltaX;
		if (sizeX2<1) return;
	}


	int putY = putY1;
	if (putY2>putY) putY = putY2;

	if (putY1<putY)
	{
		int deltaY = putY - putY1;

		putY1 += deltaY;
		srcY1 += deltaY;
		sizeY1 -= deltaY;
		if (sizeY1<1) return;
	}

	if (putY2<putY)
	{
		int deltaY = putY - putY2;

		putY2 += deltaY;
		srcY2 += deltaY;
		sizeY2 -= deltaY;
		if (sizeY2<1) return;
	}

	int sizeX = sizeX1;
	if (sizeX2<sizeX) sizeX = sizeX2;

	if (sizeX1<sizeX)
	{
		int deltaX = sizeX - sizeX1;
		sizeX1 -= deltaX;
		if (sizeX1<1) return;
	}

	if (sizeX2<sizeX)
	{
		int deltaX = sizeX - sizeX2;
		sizeX2 -= deltaX;
		if (sizeX2<1) return;
	}

	int sizeY = sizeY1;
	if (sizeY2<sizeY) sizeY = sizeY2;

	if (sizeY1<sizeY)
	{
		int deltaY = sizeY - sizeY1;
		sizeY1 -= deltaY;
		if (sizeY1<1) return;
	}

	if (sizeY2<sizeY)
	{
		int deltaY = sizeY - sizeY2;
		sizeY2 -= deltaY;
		if (sizeY2<1) return;
	}

#if defined _TINYAN3DLIB_
	if (CheckEffectError()) return;

	float color[4];
	color[0] = ((float)dr) / 255.0f;
	color[1] = ((float)dg) / 255.0f;
	color[2] = ((float)db) / 255.0f;
	color[3] = 0.0f;
	SetColor(color);

	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture(),0);
	CMyTexture* lpTexture2 = (CMyTexture*)(lpPic2->GetTexture());
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

	int srclPitch1 = picSizeX1 * sizeof(int);
	int srclPitch2 = picSizeX2 * sizeof(int);
	int maskPitch1 = picSizeX1;
	int maskPitch2 = picSizeX2;

	int* src1 = lpPic->GetPictureBuffer();
	if (src1 == NULL) return;
	src1 += srcX1;
	src1 += srcY1 * picSizeX1;
	char* mask1 = lpPic->GetMaskPic();
	if (mask1 == NULL) return;
	mask1 += srcX1;
	mask1 += srcY1 * picSizeX1;

	int* src2 = lpPic2->GetPictureBuffer();
	if (src2 == NULL) return;
	src2 += srcX2;
	src2 += srcY2 * picSizeX2;
	char* mask2 = lpPic2->GetMaskPic();
	if (mask2 == NULL) return;
	mask2 += srcX2;
	mask2 += srcY2 * picSizeX2;

	dst += putX;
	dst += putY * screenSizeX;

	int lPitch = screenSizeX * sizeof(int);

	int loopX = sizeX;
	int loopY = sizeY;


	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,addColor
		movd mm5,eax
		punpcklbw mm5,mm0
//		punpcklwd mm5,mm5
//		punpckldq mm5,mm5

		mov eax,subColor
		movd mm6,eax
		punpcklbw mm6,mm0
//		punpcklwd mm6,mm6
//		punpckldq mm6,mm6

		mov edi,dst
		mov ebx,mask1
		mov esi,mask2
		mov ecx,loopY
LOOP1:
		push ebx
		push ecx
		push esi
		push edi

		mov ecx,loopX
LOOP2:
		xor eax,eax
		mov al,[esi]
		or al,al
		jz SKIP99
		mov dl,[ebx]
		or dl,dl
		jz SKIP99


		movq mm3,mm5
		movq mm4,mm6
		cmp al,255
		jz NORMAL1

		movd mm1,eax
		punpcklbw mm1,mm0
		punpcklwd mm1,mm1
		punpckldq mm1,mm1
		cmp dl,255
		jz NORMAL0
		movd mm2,edx
		punpcklbw mm2,mm0
		punpcklwd mm2,mm2
		punpckldq mm2,mm2
		pmullw mm1,mm2
		psrlw mm1,8
NORMAL0:
		pmullw mm3,mm1
		psrlw mm3,8
		pmullw mm4,mm1
		psrlw mm4,8
		jmp CALCU1


NORMAL1:
		cmp dl,255
		jz CALCU1

		movd mm1,edx
		punpcklbw mm1,mm0
		punpcklwd mm1,mm1
		punpckldq mm1,mm1
		pmullw mm3,mm1
		psrlw mm3,8
		pmullw mm4,mm1
		psrlw mm4,8

CALCU1:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0
		paddusw mm1,mm3
		psubusw mm1,mm4
		packuswb mm1,mm1
		movd eax,mm1
		mov [edi],eax
SKIP99:
		inc ebx
		inc esi
		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ecx
		pop ebx
		add ebx,maskPitch1
		add esi,maskPitch2
		add edi,lPitch
		dec ecx
		jnz LOOP1

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



BOOL CEffectKomorebi::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return TRUE;
}
