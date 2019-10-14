//
// addsub.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanlib\include\allGraphics.h"
#include "..\nyanLib\include\myGraphics.h"

#include "addsub.h"


CAddSub::CAddSub()
{
}


CAddSub::~CAddSub()
{
	End();
}

void CAddSub::End(void)
{
}


void CAddSub::Print(int deltaR,int deltaG,int deltaB)
{
	if (deltaG == -9999) deltaG = deltaR;
	if (deltaB == -9999) deltaB = deltaG;

	int addR = deltaR;
	int addG = deltaG;
	int addB = deltaB;
	int subR = -deltaR;
	int subG = -deltaG;
	int subB = -deltaB;

	if (addR<0) addR = 0;
	if (addR>255) addR = 255;
	if (addG<0) addG = 0;
	if (addG>255) addG = 255;
	if (addB<0) addB = 0;
	if (addB>255) addB = 255;

	if (subR<0) subR = 0;
	if (subR>255) subR = 255;
	if (subG<0) subG = 0;
	if (subG>255) subG = 255;
	if (subB<0) subB = 0;
	if (subB>255) subB = 255;


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* dst = CMyGraphics::GetScreenBuffer();


	int addColor = (addR << 16) | (addG << 8) | addB;
	int subColor = (subR << 16) | (subG << 8) | subB;

#if defined _WIN64
#pragma message("***実装したにゃ　ここにc++実装が必要にゃ " __FILE__)
	int loop = screenSizeX * screenSizeY;

	for (int i = 0; i < loop; i++)
	{
		int d = *dst;
		int r = (d >> 16) & 0xff;
		int g = (d >>  8) & 0xff;
		int b = (d     ) & 0xff;

		r += addR;
		g += addG;
		b += addB;
		r -= subR;
		g -= subG;
		b -= subB;

		if (r < 0) r = 0;
		if (r > 255) r = 255;
		if (g < 0) g = 0;
		if (g > 255) g = 255;
		if (b < 0) b = 0;
		if (b > 255) b = 255;

		int color = (r << 16) | (g << 8) | b;

		*dst = color;
		dst++;

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

		mov eax,addColor
		movd mm6,eax
		punpckldq mm6,mm6

		mov eax,subColor
		movd mm7,eax
		punpckldq mm7,mm7



		mov eax,screenSizeX
		mov edx,screenSizeY
		mul edx
		shr eax,3
		mov ecx,eax

		mov edi,dst
LOOP2:
		movq mm1,[edi]
		movq mm2,[edi+8]
		movq mm3,[edi+16]
		movq mm4,[edi+24]

		paddusb mm1,mm6
		paddusb mm2,mm6
		paddusb mm3,mm6
		paddusb mm4,mm6

		psubusb mm1,mm7
		psubusb mm2,mm7
		psubusb mm3,mm7
		psubusb mm4,mm7

		movq [edi],mm1
		movq [edi+8],mm2
		movq [edi+16],mm3
		movq [edi+24],mm4

		add edi,32
		dec ecx
		jnz LOOP2

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


void CAddSub::PrintClip(int startX,int startY,int sizeX,int sizeY,int deltaR,int deltaG ,int deltaB)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (CAllGraphics::Clip(startX,startY,sizeX,sizeY) == FALSE) return;

	if ((startX == 0) && (startY == 0) && (sizeX == screenSizeX) && (sizeY == screenSizeY))
	{
		Print(deltaR,deltaG,deltaB);
		return;
	}





	if (deltaG == -9999) deltaG = deltaR;
	if (deltaB == -9999) deltaB = deltaG;

	int addR = deltaR;
	int addG = deltaG;
	int addB = deltaB;
	int subR = -deltaR;
	int subG = -deltaG;
	int subB = -deltaB;

	if (addR<0) addR = 0;
	if (addR>255) addR = 255;
	if (addG<0) addG = 0;
	if (addG>255) addG = 255;
	if (addB<0) addB = 0;
	if (addB>255) addB = 255;

	if (subR<0) subR = 0;
	if (subR>255) subR = 255;
	if (subG<0) subG = 0;
	if (subG>255) subG = 255;
	if (subB<0) subB = 0;
	if (subB>255) subB = 255;



	int* dst = CMyGraphics::GetScreenBuffer();
	int lPitch = screenSizeX * sizeof(int);
	dst += startX;
	int delta = startY * screenSizeX;
	dst += delta;

	int loopX = sizeX;
	int loopY = sizeY;

	int addColor = (addR << 16) | (addG << 8) | addB;
	int subColor = (subR << 16) | (subG << 8) | subB;

#if defined _WIN64
#pragma message("***実装したにゃ ここにc++実装が必要にゃ " __FILE__)

	int* edi = dst;
	for (int j=0;j<loopY;j++)
	{
		int* pushedi = edi;

		for (int i = 0; i < loopX; i++)
		{
			int d = *edi;
			int r = (d >> 16) & 0xff;
			int g = (d >> 8) & 0xff;
			int b = (d) & 0xff;

			r += addR;
			g += addG;
			b += addB;
			r -= subR;
			g -= subG;
			b -= subB;

			if (r < 0) r = 0;
			if (r > 255) r = 255;
			if (g < 0) g = 0;
			if (g > 255) g = 255;
			if (b < 0) b = 0;
			if (b > 255) b = 255;

			int color = (r << 16) | (g << 8) | b;

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

		mov eax,addColor
		movd mm6,eax
		punpckldq mm6,mm6

		mov eax,subColor
		movd mm7,eax
		punpckldq mm7,mm7


		mov edi,dst
		mov ecx,loopY
LOOP1A:
		push ecx
		push edi

		mov ecx,loopX
LOOP1B:
		mov eax,[edi]
		movd mm1,eax
		paddusb mm1,mm6
		psubusb mm1,mm7
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

