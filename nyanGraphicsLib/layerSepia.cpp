//
// LayerSepia.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "layerSepia.h"


CLayerSepia::CLayerSepia()
{
}


CLayerSepia::~CLayerSepia()
{
	End();
}

void CLayerSepia::End(void)
{
}



void CLayerSepia::Print(int ps256,int r,int g,int b)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* dst = CMyGraphics::GetScreenBuffer();

	int loopSize = screenSizeX * screenSizeY;

	int ps256work = ps256;
	int nega256work = 256-ps256;


	int col = (r << 16) | (g<<8) | b;

#if defined _WIN64

	int* edi = dst;
	for (int i = 0; i < loopSize; i++)
	{
		int d = *edi;
		int srcR = (d >> 16) & 0xff;
		int srcG = (d >> 8) & 0xff;
		int srcB = (d) & 0xff;
		int y = srcR * 76 + srcG * 150 + srcB * 29;
		y >>= 8;
		int sepiaR = y * r;
		int sepiaG = y * g;
		int sepiaB = y * b;
		sepiaR >>= 8;
		sepiaG >>= 8;
		sepiaB >>= 8;

		int colR = srcR * nega256work + sepiaR * ps256work;
		int colG = srcG * nega256work + sepiaG * ps256work;
		int colB = srcB * nega256work + sepiaB * ps256work;

		colR >>= 8;
		colG >>= 8;
		colB >>= 8;

		int color = (colR << 16) | (colG << 8) | colB;
		*edi = color;

		edi++;
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

		mov eax,76*65536 + 150*256 + 29
		movd mm7,eax
		punpcklbw mm7,mm0

		mov eax,ps256work
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5

		mov eax,nega256work
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov eax,col
		movd mm4,eax
		punpcklbw mm4,mm0

		mov edi,dst

		mov ecx,loopSize
LOOP1:
		mov edx,[edi]
		movd mm1,edx
		punpcklbw mm1,mm0
		movq mm2,mm1

		pmaddwd mm1,mm7

		psrld mm1,8
		packssdw mm1,mm1

		movq mm3,mm1
		psrld mm3,16
		paddw mm1,mm3
		punpcklwd mm1,mm1
		punpckldq mm1,mm1

		pmullw mm1,mm4
		psrlw mm1,8

		//ps
		pmullw mm1,mm5
		pmullw mm2,mm6
		paddw mm1,mm2

		psrlw mm1,8
		packuswb mm1,mm0
		movd edx,mm1
		mov [edi],edx

		add edi,4
		inc ebx
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

