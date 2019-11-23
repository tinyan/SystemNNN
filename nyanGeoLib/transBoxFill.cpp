//
// transBoxFill
//

#include <windows.h>
//#include <stdio.h>
//#include <Math.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "transBoxFill.h"


CTransBoxFill::CTransBoxFill()
{
}


CTransBoxFill::~CTransBoxFill()
{
	End();
}

void CTransBoxFill::End(void)
{
}







void CTransBoxFill::Print(int x, int y, int sizeX, int sizeY, int r, int g, int b, int ps)
{
	//clip
	if (CMyGraphics::Clip(&x,&y,&sizeX,&sizeY) == FALSE) return;

	//print
//	int* dst = (int*)CPicture::m_lpScreenBuffer;
	int* dst = CMyGraphics::GetScreenBuffer();
//	int screenSizeX = CPicture::m_screenSizeX;
	int screenSizeX = CMyGraphics::GetScreenSizeX();

	dst += x;
#if defined _WIN64
	dst += (long long)y*(long long)screenSizeX;
#else
	dst += y * screenSizeX;
#endif

	int loopX = sizeX;
	int loopY = sizeY;

	if (ps<0) ps = 0;
	if (ps>100) ps = 100;

	int transPercent = ps * 256;
	transPercent /= 100;
     
	DWORD dwAlpha = (DWORD)transPercent;
	DWORD dwAlpha2 = (256 - dwAlpha);



	int col = (r<<16) | (g<<8) | b;
	int lPitch = screenSizeX * sizeof(int);

#if defined _WIN64
#pragma message("***ŽÀ‘•‚µ‚½‚É‚á ‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)

	int alpha = dwAlpha;
	int oneMinusAlpha = dwAlpha2;
	int* edi = dst;

	int addR = (r * alpha);
	int addG = (g * alpha);
	int addB = (b * alpha);

	for (int j = 0; j < loopY; j++)
	{
		int* pushedi = edi;
		for (int i = 0; i < loopX; i++)
		{
			int d = *edi;
			int srcR = (d << 16) & 0xff;
			int srcG = (d <<  8) & 0xff;
			int srcB = (d      ) & 0xff;

			int rr = (srcR * oneMinusAlpha);
			int gg = (srcG * oneMinusAlpha);
			int bb = (srcB * oneMinusAlpha);

			rr += addR;
			gg += addG;
			bb += addB;

			rr >>= 8;
			gg >>= 8;
			bb >>= 8;

			int c = (rr << 16) | (gg < 8) | bb;
			*edi = c;

			edi++;
		}

		edi = pushedi;
		edi += lPitch / 4;
	}


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

	    movd mm4,dwAlpha 
		punpcklwd mm4,mm4
		punpckldq mm4,mm4 // mm4 =  0ƒ¿0ƒ¿0ƒ¿0ƒ¿
		movd mm5,dwAlpha2 
		punpcklwd mm5,mm5
		punpckldq mm5,mm5 // mm5 = 0(1-ƒ¿)0(1-ƒ¿)0(1-ƒ¿)0(1-ƒ¿)

		mov eax,col
		movd mm3,eax
		punpcklbw mm3,mm0

		pmullw mm3,mm4



		pxor mm6,mm6
		pxor mm7,mm7

		mov edi,dst
		mov edx,loopY
		mov eax,col
LOOP1:
		push edi
		mov ecx,loopX
LOOP2:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0

		pmullw mm1,mm5

        paddw mm1,mm3
        psrlw mm1,8

        packuswb mm1,mm0
        movd dword ptr [edi],mm1
		
		add edi,4

		dec ecx
		jnz LOOP2

		pop edi
		add edi,lPitch
		dec edx
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
