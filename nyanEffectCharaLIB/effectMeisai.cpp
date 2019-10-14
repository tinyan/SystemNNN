//
// effectMeisai.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectMeisai.h"



CEffectMeisai::CEffectMeisai(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
#if defined _TINYAN3DLIB_
	SetConstKosuu(1);
	SetTextureKosuu(2);
	Create("Meisai");
#endif
}

CEffectMeisai::~CEffectMeisai()
{
	End();
}

void CEffectMeisai::End(void)
{
}

BOOL CEffectMeisai::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
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
	if (paraKosuu<2) para[1] = 10;	//dxEnd
	if (paraKosuu<3) para[2] = 5;	//dyEnd
	if (paraKosuu<4) para[3] = para[1];	//dxStart
	if (paraKosuu<5) para[4] = para[2];	//picNumber

	if (paraKosuu < 6) para[5] = 0;	//type
	if (paraKosuu < 7) para[6] = 0;	//subframe


	lp->flag = TRUE;
	lp->command = EFFECT_MEISAI;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	return TRUE;
}


BOOL CEffectMeisai::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectMeisai::BeginPrint(LPVOID para,int layer)
{

}

void CEffectMeisai::Init(LPVOID para,int layer)
{


}

void CEffectMeisai::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectMeisai::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

//	int dv = lp->countMax;
//	int c = lp->count;
//
//	if (dv<1)
//	{
//		dv = 1;
//	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int count = lp->count;
	int countMax = lp->countMax;
	int type = lp->para[5];
	int subFrame = lp->para[6];


	int* dst = CMyGraphics::GetScreenBuffer();

	int pic = lp->pic;
	if (pic == -1) return;

	CPicture* lpPic = m_allEffect->GetPicture(layer);
	if (lpPic == NULL) return;

	RECT rc;
	lpPic->GetPicSize(&rc);
	int picSizeX = rc.right;
	int picSizeY = rc.bottom;
	if ((picSizeX<1) || (picSizeY<1)) return;

	int md = 0;
	if (lpPic->CheckMaskExist())
	{
		md = 2;
	}

	if (md != 2) return;


	//clip
	//RECT rcPic = m_effect->m_effect[pic].dst;
	//int putX = rcPic.left;
	//int putY = rcPic.top;

//	POINT dstPoint = m_allEffect->GetDstPoint(layer);
//	int putX = dstPoint.x;
//	int putY = dstPoint.y;
	
	int putX = lp->dst.left;
	int putY = lp->dst.top;



	int srcX = 0;
	int srcY = 0;
	int sizeX = picSizeX;
	int sizeY = picSizeY;

	int upClip = lpPic->m_charaClipYStart;
	int downClip = lpPic->m_charaClipYEnd;
	int leftClip = lpPic->m_charaClipXStart;
	int rightClip = lpPic->m_charaClipXEnd;

	putX += leftClip;
	putY += upClip;
	srcX += leftClip;
	srcY += upClip;
	sizeX = rightClip - leftClip;
	sizeY = downClip - upClip;

	if ((sizeX<1) || (sizeY<1)) return;

	if ((putX>=screenSizeX) || (putY>=screenSizeY)) return;

	if (putX<0)
	{
		sizeX -= (-putX);
		srcX += (-putX);
		putX = 0;
	}

	if (putY<0)
	{
		sizeY -= (-putY);
		srcY += (-putY);
		putY = 0;
	}

	if ((sizeX<1) || (sizeY<1)) return;

	if ((putX + sizeX) > screenSizeX)
	{
		sizeX = screenSizeX - putX;
	}

	if ((putY + sizeY) > screenSizeY)
	{
		sizeY = screenSizeY - putY;
	}

	if ((sizeX<1) || (sizeY<1)) return;

	int lPitch = screenSizeX * sizeof(int);

	dst += screenSizeX * putY;
	dst += putX;

	char* mask = lpPic->GetMaskPic();
	if (mask == NULL) return;
	int* src = (int*)(lpPic->GetBuffer());

	int srcPitch = picSizeX * sizeof(int);
	src += picSizeX * srcY;
	src += srcX;

	int maskPitch = picSizeX;
	mask += picSizeX * srcY;
	mask += srcX;

	int dx1 = lp->para[3];
	int dx2 = lp->para[1];
//	int deltaX = dx1 + ((dx2 - dx1) * c ) / dv;
	int deltaX = CCalcuSpeed::calcu(count,countMax,dx1,dx2,subFrame,type);

	int dy1 = lp->para[4];
	int dy2 = lp->para[2];
//	int deltaY = dy1 + ((dy2 - dy1) * c ) / dv;
	int deltaY = CCalcuSpeed::calcu(count,countMax,dy1,dy2,subFrame,type);

	if (deltaX<0) deltaX = 0;

	deltaY = 0;


	int loopY = sizeY;
	int loopX = sizeX - deltaX;

	if ((loopX<1) || (loopY<1)) return;

#if defined _TINYAN3DLIB_
	CopyScreenToBuffer();
	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture(),0);
	SetTexture(GetBufferTexture(),1);

	POINT dstPoint;
	dstPoint.x = putX;
	dstPoint.y = putY;
	SIZE dstSize;
	dstSize.cx = sizeX;
	dstSize.cy = sizeY;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;

	float deltaF = (float)deltaX;
	deltaF /= ((float)screenSizeX);
	SetConst(deltaF);

	Blt(dstPoint,dstSize,srcPoint);

#else

#if defined _WIN64
#pragma message("‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)

#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov edi,dst
		mov esi,edi
		mov eax,deltaX
		shl eax,2
		add esi,eax

		mov ebx,mask
		mov edx,loopY
LOOP1:
		push edx
		push ebx
		push esi
		push edi

		mov ecx,loopX

LOOP2:
		xor eax,eax
		mov al,[ebx]
		or al,al
		jz SKIP1

		mov eax,[esi]
		mov [edi],eax
SKIP1:
		inc ebx
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ebx
		pop edx
		add ebx,maskPitch
		add edi,lPitch
		add esi,lPitch
		dec edx
		jnz LOOP1


		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#endif

#endif

}

BOOL CEffectMeisai::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}




