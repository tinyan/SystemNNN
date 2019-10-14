//
// nega.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanlib\include\allGraphics.h"
#include "..\nyanLib\include\myGraphics.h"

#include "nega.h"


CNega::CNega()
{
}


CNega::~CNega()
{
	End();
}

void CNega::End(void)
{
}


void CNega::Print(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

#if defined _WIN64
	PrintClip(0, 0, screenSizeX, screenSizeY);
	return;
#endif
	int* dst = CMyGraphics::GetScreenBuffer();

	int loopSize = screenSizeX * screenSizeY / 8;

#if defined _WIN64
//#pragma message("ここにc++実装が必要にゃ " __FILE__)

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

		mov eax,0ffffffh
		movd mm6,eax
		punpckldq mm6,mm6

		mov edi,dst
		mov ecx,loopSize
LOOP1:
		movq mm1,[edi]
		movq mm2,[edi+8]
		movq mm3,[edi+16]
		movq mm4,[edi+24]
		pxor mm1,mm6
		pxor mm2,mm6
		pxor mm3,mm6
		pxor mm4,mm6
		movq [edi],mm1
		movq [edi+8],mm2
		movq [edi+16],mm3
		movq [edi+24],mm4
		add edi,32
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

void CNega::PrintClip(int startX,int startY,int sizeX,int sizeY)
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

	int lPitch = screenSizeX * sizeof(int);
	dst += startX;
	int delta = startY * screenSizeX;
	dst += delta;
	int loopX = sizeX;
	int loopY = sizeY;

#if defined _WIN64
#pragma message("***実装したにゃ ここにc++実装が必要にゃ " __FILE__)

	int* edi = dst;
	for (int j = 0; j < loopY; j++)
	{
		int* pushedi = edi;
		for (int i = 0; i < loopX; i++)
		{
			int d = *edi;
			d ^= 0xffffff;
			*edi = d;

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

		mov eax,0ffffffh
	//	movd mm6,eax
	//	punpckldq mm6,mm6

		mov edi,dst
		mov ecx,loopY
LOOP1A:
		push ecx
		push edi

		mov ecx,loopX
LOOP1B:
		xor [edi],eax
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

