//
// multi.cpp
//

#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanlib\include\allGraphics.h"
#include "..\nyanLib\include\myGraphics.h"

#include "multi.h"


CMulti::CMulti()
{
}


CMulti::~CMulti()
{
	End();
}

void CMulti::End(void)
{
}


void CMulti::Print(int percentR,int percentG,int percentB)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

#if defined _WIN64
	PrintClip(0, 0, screenSizeX, screenSizeY, percentR, percentG, percentB);
	return;
#endif

	if (percentG == -1) percentG = percentR;
	if (percentB == -1) percentB = percentG;

	if (percentR<0) percentR = 0;
	if (percentR>100) percentR = 100;
	if (percentG<0) percentG = 0;
	if (percentG>100) percentG = 100;
	if (percentB<0) percentB = 0;
	if (percentB>100) percentB = 100;

//	if (percent < 0) percent = 0;
//	if (percent > 100) percent = 100;


	int* dst = CMyGraphics::GetScreenBuffer();


//	int r = 100 - ((100-percentR)*percent) / 100;
//	int g = 100 - ((100-percentG)*percent) / 100;
//	int b = 100 - ((100-percentB)*percent) / 100;

//	if (r<0) r = 0;
//	if (r>100) r = 100;
//	if (g<0) g = 0;
//	if (g>100) g = 100;
//	if (b<0) b = 0;
//	if (b>100) b = 100;
	

//	int mulR= (r * 256)/100;
//	int mulG= (g * 256)/100;
//	int mulB= (b * 256)/100;

	int mulR= (percentR * 256)/100;
	int mulG= (percentG * 256)/100;
	int mulB= (percentB * 256)/100;

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

		mov eax,mulR
		movd mm7,eax
		psll mm7,32
		mov eax,mulG
		movd mm1,eax
		psll mm1,16
		por mm7,mm1
		mov eax,mulB
		movd mm1,eax
		por mm7,mm1

//		mov eax,col
//		movd mm7,eax
//		punpcklbw mm7,mm0

		mov eax,screenSizeX
		mov edx,screenSizeY
		mul edx
		shr eax,2
		mov ecx,eax

		mov edi,dst
LOOP2:
		movq mm1,[edi]
		movq mm2,mm1

		punpcklbw mm1,mm0
		punpckhbw mm2,mm0
		
		pmullw mm1,mm7
		pmullw mm2,mm7

		movq mm3,[edi+8]
		movq mm4,mm3

		psrlw mm1,8
		psrlw mm2,8

		punpcklbw mm3,mm0
		punpckhbw mm4,mm0

		packuswb mm1,mm0
		packuswb mm2,mm0

		pmullw mm3,mm7
		pmullw mm4,mm7

		punpckldq mm1,mm2

		psrlw mm3,8
		psrlw mm4,8

		movq [edi],mm1

		packuswb mm3,mm0
		packuswb mm4,mm0

		punpckldq mm3,mm4

		movq [edi+8],mm3

		add edi,16
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

void CMulti::PrintClip(int startX,int startY,int sizeX,int sizeY,int percentR,int percentG ,int percentB)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (CAllGraphics::Clip(startX,startY,sizeX,sizeY) == FALSE) return;

	if ((startX == 0) && (startY == 0) && (sizeX == screenSizeX) && (sizeY == screenSizeY))
	{
		Print(percentR,percentG,percentB);
		return;
	}


	if (percentG == -1) percentG = percentR;
	if (percentB == -1) percentB = percentG;

	if (percentR<0) percentR = 0;
	if (percentR>100) percentR = 100;
	if (percentG<0) percentG = 0;
	if (percentG>100) percentG = 100;
	if (percentB<0) percentB = 0;
	if (percentB>100) percentB = 100;

	int* dst = CMyGraphics::GetScreenBuffer();

	dst += startX;
	int delta = startY * screenSizeX;
	dst += delta;
	int lPitch = screenSizeX * sizeof(int);

	int loopX = sizeX;
	int loopY = sizeY;


	int mulR= (percentR * 256)/100;
	int mulG= (percentG * 256)/100;
	int mulB= (percentB * 256)/100;

#if defined _WIN64
#pragma message("***実装したにゃ ここにc++実装が必要にゃ " __FILE__)
	int* edi = dst;
	for (int j = 0; j < loopY; j++)
	{
		int* pushedi = edi;
		for (int i = 0; i < loopX; i++)
		{
			int d = *edi;
			int r = (d >> 16) & 0xff;
			int g = (d >>  8) & 0xff;
			int b = (d     ) & 0xff;

			r *= mulR;
			g *= mulG;
			b *= mulB;

			r >>= 8;
			g >>= 8;
			b >>= 8;

			int col = (r << 16) | (g << 8) | b;
			*edi = col;

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

		mov eax,mulR
		movd mm7,eax
		psll mm7,32
		mov eax,mulG
		movd mm1,eax
		psll mm1,16
		por mm7,mm1
		mov eax,mulB
		movd mm1,eax
		por mm7,mm1


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
		pmullw mm1,mm7
		psrlw mm1,8
		packuswb mm1,mm0
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

