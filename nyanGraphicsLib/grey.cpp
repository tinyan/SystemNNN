//
// grey.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanlib\include\allGraphics.h"
#include "..\nyanLib\include\myGraphics.h"

#include "grey.h"


CGrey::CGrey()
{
}


CGrey::~CGrey()
{
	End();
}

void CGrey::End(void)
{
}



void CGrey::Print(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* dst = CMyGraphics::GetScreenBuffer();

	int loopSize = screenSizeX * screenSizeY / 4;

#if defined _WIN64
	PrintClip(0, 0, screenSizeX, screenSizeY);
	return;
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
		movd mm6,eax
		punpcklbw mm6,mm0

		mov edi,dst
		mov ecx,loopSize
LOOP1:
		movq mm1,[edi]
		movq mm2,mm1
		movq mm3,[edi+8]
		movq mm4,mm3
		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		punpcklbw mm3,mm0
		punpckhbw mm4,mm0
		pmaddwd mm1,mm6
		pmaddwd mm2,mm6
		pmaddwd mm3,mm6
		pmaddwd mm4,mm6


		psrld mm1,8
		psrld mm2,8
		psrld mm3,8
		psrld mm4,8

		packssdw mm1,mm2
		packssdw mm3,mm4


		movq mm2,mm1
		psrld mm2,16
		paddw mm1,mm2

		movq mm2,mm1

		punpcklbw mm1,mm1
		punpcklwd mm1,mm1

		punpckhbw mm2,mm2
		punpcklwd mm2,mm2

		punpckldq mm1,mm2

		movq mm4,mm3
		psrld mm4,16
		paddw mm3,mm4

		movq mm4,mm3

		punpcklbw mm3,mm3
		punpcklwd mm3,mm3

		punpckhbw mm4,mm4
		punpcklwd mm4,mm4

		punpckldq mm3,mm4



		pslld mm1,8
		psrld mm1,8

		pslld mm3,8
		psrld mm3,8


		movq [edi],mm1
		movq [edi+8],mm3

		add edi,16
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

void CGrey::PrintClip(int startX,int startY,int sizeX,int sizeY)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (CAllGraphics::Clip(startX,startY,sizeX,sizeY) == FALSE) return;

	if ((startX == 0) && (startY == 0) && (sizeX == screenSizeX) && (sizeY == screenSizeY))
	{
		Print();
		return;
	}


	int* dst = CMyGraphics::GetScreenBuffer();

	int loopX = sizeX;
	int loopY = sizeY;
	dst += startX;
	dst += startY * screenSizeX;

	int lPitch = screenSizeX * sizeof(int);

//	int loopSize = screenSizeX * screenSizeY / 4;

#if defined _WIN64
#pragma message("***ŽÀ‘•‚µ‚½‚É‚á ‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)
	int* edi = dst;
	for (int j = 0; j < loopY; j++)
	{
		int* pushedi = edi;
		
		for (int i = 0; i < loopX; i++)
		{
			int d = *edi;
			int r = (d >> 16) & 0xff;
			int g = (d >>  8) & 0xff;
			int b = (d      ) & 0xff;
			int y = r * 76 + g * 150 + b * 29;
			y >>= 8;
			int color = (y << 16) | (y << 8) | y;
			*edi = color;

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

		mov eax,76*65536 + 150*256 + 29
		movd mm6,eax
		punpcklbw mm6,mm0

		mov edi,dst
		mov ecx,loopY
LOOP1A:
		push ecx
		push edi

		mov ecx,loopX
LOOP1B:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0
		pmaddwd mm1,mm6
		psrld mm1,8
		packssdw mm1,mm1
		movq mm2,mm1
		psrld mm2,16
		paddw mm1,mm2
		punpcklwd mm1,mm0
		movq mm2,mm1
		movq mm3,mm1
		pslld mm2,8
		pslld mm3,16
		paddw mm1,mm2
		paddw mm1,mm3

		movd eax,mm1
		mov [edi],eax

		add edi,4
		dec ecx
		jnz LOOP1B

		pop edi
		pop ecx
		add edi,lPitch
		dec ecx
		jnz LOOP1A

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

/*_*/

