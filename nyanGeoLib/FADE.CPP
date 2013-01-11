//
//
//

#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "fade.h"

CFade::CFade()
{
}

CFade::~CFade()
{
	End();
}

void CFade::End(void)
{
}

void CFade::Print(int ps1,int r,int g,int b,int ps2)
{
	if (g == -1) g = r;
	if (b == -1) b = g;
	if (ps2 == -1) ps2 = 100 - ps1;

	int* dst = CMyGraphics::GetScreenBuffer();

	if (ps1<0) ps1 = 0;
	if (ps1>100) ps1 = 100;
	if (ps2<0) ps2 = 0;
	if (ps2>100) ps2 = 100;

	int d = ps1 * 0x7fff;
	int d2 = ps2 * 0x7fff;

	d /= 100;
	d2 /= 100;

	d &= 0x7fff;
	d2 &= 0x7fff;

	int srcColor = (r<<16) | (g<<8) | b;

	int mulColor1 = d;
	int mulColor2 = d2;

	int sizeX = CMyGraphics::GetScreenSizeX();
	int sizeY = CMyGraphics::GetScreenSizeY();


	int loops = sizeX * sizeY / 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov edi,dst

		pxor mm7,mm7

		mov eax,mulColor1
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5

		mov eax,mulColor2
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

		mov eax,srcColor
		movd mm4,eax
		punpcklbw mm4,mm7
		psllw mm4,1
		pmulhw mm6,mm4

		mov ecx,loops

LOOP1:
		movq mm0,[edi]
		movq mm1,mm0
		movq mm2,[edi+8]
		movq mm3,mm2

		punpcklbw mm0,mm7
		punpckhbw mm1,mm7
		punpcklbw mm2,mm7
		punpckhbw mm3,mm7

		psllw mm0,1
		psllw mm1,1

		pmulhw mm0,mm5
		pmulhw mm1,mm5

		psllw mm2,1
		psllw mm3,1

		pmulhw mm2,mm6
		pmulhw mm3,mm6

		paddw mm0,mm6
		paddw mm1,mm6

		paddw mm2,mm6
		paddw mm3,mm6

		packuswb mm0,mm1
		packuswb mm2,mm3

		movq [edi],mm0
		movq [edi+8],mm2

		add edi,16
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

}



/*_*/

