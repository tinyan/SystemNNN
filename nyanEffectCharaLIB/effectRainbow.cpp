//
// effectRainbow.cpp
//

#include "..\nyanEffectLib\includer.h"

#include "effectRainbow.h"

CEffectRainbow::CEffectRainbow(CAllEffect* lpAll) : CCommonEffect(lpAll)
{
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_color = new int[screenSizeY + 7];

	m_rainbowTable[0] = 0x0ff0000;
	m_rainbowTable[1] = 0x0ffff00;
	m_rainbowTable[2] = 0x000ff00;
	m_rainbowTable[3] = 0x000ffff;
	m_rainbowTable[4] = 0x00000ff;
	m_rainbowTable[5] = 0x0ff00ff;
	m_rainbowTable[6] = m_rainbowTable[0];

#if defined _TINYAN3DLIB_
	SetTextureKosuu(2);
	SetConstKosuu(1);
	Create("Rainbow");
#endif

}

CEffectRainbow::~CEffectRainbow()
{
	End();
}

void CEffectRainbow::End(void)
{
	DELETEARRAY(m_color);
}

void CEffectRainbow::InitParameter(LPVOID lpEffect, int layer)
{
	int para[16];
	EFFECT* lp = (EFFECT*)lpEffect;
	for (int i=0;i<16;i++)
	{
		para[i] = lp->para[i];
	}
	SetParam(lp,16,para,layer);
}

BOOL CEffectRainbow::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>9) k = 9;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}

	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 100;	//trans% end
	if (paraKosuu<3) para[2] = para[1];	//trans% start
	if (paraKosuu<4) para[3] = 0;	//trans% change type
	if (paraKosuu<5) para[4] = 0;	//subframe

	if (paraKosuu<6) para[5] = 0;	//color type(now 0 only)
	if (paraKosuu<7) para[6] = 1;	//color change speed
	if (paraKosuu<8) para[7] = 1;	//color pic change speed


	lp->flag = TRUE;
	lp->command = EFFECT_RAINBOW;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<9;i++)
	{
		lp->para[i] = para[i];
	}

	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;

	m_colorOffset = 0;

	return TRUE;
}


BOOL CEffectRainbow::CountIsMax(LPVOID lpEffect,int layer)
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


void CEffectRainbow::BeginPrint(LPVOID para,int layer)
{

}

void CEffectRainbow::Init(LPVOID para,int layer)
{
	m_colorOffset = 0;
}


void CEffectRainbow::Calcu(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	m_colorOffset += lp->para[6];
	if (m_colorOffset < 0)
	{
		m_colorOffset *= -1;
		m_colorOffset %= screenSizeY;
		m_colorOffset *= -1;
	}
	else
	{
		m_colorOffset %= screenSizeY;
	}

	int dv = (screenSizeY+5) / 6;

	for (int j=0;j<6;j++)
	{
		int d0 = m_rainbowTable[j];
		int d1 = m_rainbowTable[j+1];

		int r0 = (d0 >> 16) & 0xff;
		int g0 = (d0 >>  8) & 0xff;
		int b0 = (d0      ) & 0xff;

		int r1 = (d1 >> 16) & 0xff;
		int g1 = (d1 >>  8) & 0xff;
		int b1 = (d1      ) & 0xff;

		for (int i=0;i<dv;i++)
		{
			int k = j * dv + i;
			if (k<screenSizeY)
			{
				k += m_colorOffset;
				k += screenSizeY;
				k %= screenSizeY;

				int r = r0 + ((r1 - r0) * i) / dv;
				int g = g0 + ((g1 - g0) * i) / dv;
				int b = b0 + ((b1 - b0) * i) / dv;


				m_color[k] = (r<<16) | (g<<8) | b;
			}
		}
	}
}


void CEffectRainbow::Print(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int dv = lp->countMax;
	int c = lp->count;

	if (dv<1)
	{
		dv = 1;
	}

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

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
	POINT dstPoint = m_allEffect->GetDstPoint(layer);

	//int putX = rcPic.left;
	//int putY = rcPic.top;
	int putX = dstPoint.x;
	int putY = dstPoint.y;

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


	int loopY = sizeY;
	int loopX = sizeX ;

	if ((loopX<1) || (loopY<1)) return;

	int* colorTable = m_color;
	colorTable += putY;

	int transPercent = CCalcuSpeed::calcu(c,dv,lp->para[2]*256,lp->para[1]*256,lp->para[4],lp->para[3]);
	transPercent /= 100;
	if (transPercent <= 0) transPercent = 0;
	if (transPercent > 256) transPercent = 256;


#if defined _TINYAN3DLIB_
	float alfa = (float)transPercent;
	alfa /= 256.0f;
	SetConst(alfa);

	float div3 = 1.0f / 3.0f;

	if (CheckEffectError()) return;

	CMyTexture* lpTexture = (CMyTexture*)(lpPic->GetTexture());
	SetTexture(lpTexture->GetTexture());

	SetWorkV(colorTable,screenSizeY);
	SetTexture(GetVTexture(),1);

	POINT dstPoint2;
	SIZE dstSize;
	POINT srcPoint;
	dstPoint2.x = putX;
	dstPoint2.y = putY;
	dstSize.cx = sizeX;
	dstSize.cy = sizeY;
	srcPoint.x = srcX;
	srcPoint.y = srcY;

	Blt(dstPoint2,dstSize,srcPoint);




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

		pxor mm0,mm0

		mov eax,transPercent
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5
		neg eax
		add eax,256
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov edi,dst
		mov esi,src
		mov ebx,mask
		mov edx,colorTable

		mov ecx,loopY
LOOP1:
		push ecx

		push edx
		push ebx
		push esi
		push edi

		mov eax,[edx]
		movd mm3,eax
		punpcklbw mm3,mm0
		pmullw mm3,mm5
		psrlw mm3,8
		packuswb mm3,mm3



		mov ecx,loopX

LOOP2:
		xor eax,eax
		mov al,[ebx]
		or al,al
		jz SKIP1

		movd mm7,eax

		movq mm1,mm3
		mov eax,[edx]
		cmp eax,256
		jz FULLRAINBOW

		mov eax,[esi]
		movd mm2,eax
		punpcklbw mm2,mm0
		pmullw mm2,mm6
		psrlw mm2,8
		packuswb mm2,mm0
		paddb mm1,mm2

FULLRAINBOW:
		movd eax,mm7
		cmp eax,255
		jz OK1
		neg eax
		add eax,256
		movd mm4,eax
		punpcklbw mm4,mm0
		punpcklwd mm4,mm4
		punpckldq mm4,mm4
		punpcklbw mm7,mm0
		punpcklwd mm7,mm7
		punpckldq mm7,mm7

		punpcklbw mm1,mm0
		pmullw mm1,mm7

		mov eax,[edi]
		movd mm2,eax
		punpcklbw mm2,mm0
		pmullw mm2,mm4
		psrlw mm1,8
		psrlw mm2,8
		paddw mm1,mm2
		packuswb mm1,mm0
OK1:
		movd eax,mm1
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

		pop ecx
		add edx,4
		add ebx,maskPitch
		add edi,lPitch
		add esi,srcPitch
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

#endif


}

BOOL CEffectRainbow::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}




