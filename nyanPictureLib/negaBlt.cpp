#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "negaBlt.h"



CNegaBlt::CNegaBlt()
{
}

CNegaBlt::~CNegaBlt()
{
	End();
}

void CNegaBlt::End(void)
{
}

void CNegaBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int negaPercent)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int c = -254*2 * negaPercent;
	c /= 100;
	c += 254;

	int* dst = CMyGraphics::GetScreenBuffer();
	int* src = (int*)picData;

	int dstPitch = screenSizeX * sizeof(int);
	int srcPitch = srcSize.cx * sizeof(int);

	src += srcPoint.y * srcSize.cx + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	if ((loopX <= 0) || (loopY <= 0)) return;

	if ( ((putPoint.x & 3) == 0) && ((putSize.cx & 3) == 0))
	{
		loopX /= 4;

		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov eax,c

			shl eax,6

			movd mm7,eax
			punpcklwd mm7,mm7
			punpckldq mm7,mm7


			mov eax,00800080h
			movd mm6,eax
			punpckldq mm6,mm6

			pxor mm4,mm4

			mov edi,dst
			mov esi,src

			mov ecx,loopY
LOOP1:
			push ecx
			push esi
			push edi
			mov ecx,loopX
LOOP2:

			movq mm0,[esi]
			movq mm2,[esi+8]
			movq mm1,mm0
			movq mm3,mm2
			
			punpcklbw mm0,mm4
			punpckhbw mm1,mm4
			psubw mm0,mm6
			punpcklbw mm2,mm4
			psubw mm1,mm6
			punpckhbw mm3,mm4

			psubw mm2,mm6
			psllw mm0,2
			psubw mm3,mm6


			psllw mm1,2
			pmulhw mm0,mm7
			psllw mm2,2
			pmulhw mm1,mm7
			psllw mm3,2
			paddw mm0,mm6

			pmulhw mm2,mm7
			paddw mm1,mm6
			pmulhw mm3,mm7

			packuswb mm0,mm1
			paddw mm2,mm6
			
			movq [edi],mm0
			paddw mm3,mm6
			packuswb mm2,mm3

			movq [edi+8],mm2

			add esi,16
			add edi,16
			dec ecx
			jnz LOOP2

			pop edi
			pop esi
			add edi,dstPitch
			add esi,srcPitch
			pop ecx
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
	}
	else
	{
		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov eax,c

			shl eax,6

			movd mm7,eax
			punpcklwd mm7,mm7
			punpckldq mm7,mm7


			mov eax,00800080h
			movd mm6,eax
			punpckldq mm6,mm6

			pxor mm4,mm4

			mov edi,dst
			mov esi,src

			mov ecx,loopY
LOOP_B1:
			push ecx
			push esi
			push edi
			mov ecx,loopX
LOOP_B2:
			mov eax,[esi]
			movd mm0,eax
			punpcklbw mm0,mm4
			psubw mm0,mm6
			psllw mm0,2
			pmulhw mm0,mm7
			paddw mm0,mm6
			packuswb mm0,mm0
			movd eax,mm0
			mov [edi],eax

			add esi,4
			add edi,4
			dec ecx
			jnz LOOP_B2

			pop edi
			pop esi
			add edi,dstPitch
			add esi,srcPitch
			pop ecx
			dec ecx
			jnz LOOP_B1

			emms
			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}

	}
}


/*_*/

