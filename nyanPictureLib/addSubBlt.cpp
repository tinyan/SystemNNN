#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "addSubBlt.h"


CAddSubBlt::CAddSubBlt()
{
}

CAddSubBlt::~CAddSubBlt()
{
	End();
}

void CAddSubBlt::End(void)
{
}

void CAddSubBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,char* maskData,SIZE srcSize,int percent)
//void CAddSubBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize)
{
	if (percent == 0) return;

	int* src = (int*)picData;
	int* dst = CMyGraphics::GetScreenBuffer();
	char* mask = maskData;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	src += srcPoint.y * srcSize.cx + srcPoint.x;
	mask += srcPoint.y * srcSize.cx + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;

	int srcPitch = srcSize.cx * sizeof(int);
	int maskPitch = srcSize.cx;
	int dstPitch = screenSizeX * 4;

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	if ((loopY<=0) || (loopX<=0)) return;


	percent *= 256;
	percent /= 100;

	int flg = 0;
	if (percent < 0)
	{
		flg = 1;
		percent *= -1;
	}

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

		mov esi,src
		mov edi,dst
		mov ebx,mask
		mov ecx,loopY

		pxor mm0,mm0
		mov eax,percent

		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7

LOOP1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,loopX
LOOP2:
		xor eax,eax
		mov al,[ebx]
		or eax,eax
		jz SKIP3
		movd mm4,eax

		neg eax
		add eax,256
		movd mm5,eax

		punpcklwd mm4,mm4
		punpcklwd mm5,mm5
		punpckldq mm4,mm4
		punpckldq mm5,mm5




		mov eax,[esi]
		movd mm1,eax
		punpcklbw mm1,mm0
		movq mm2,mm1
		pmullw mm1,mm7
		pmulhw mm2,mm7
		psrlw mm1,8
		psllw mm2,8
		por mm1,mm2
		packuswb mm1,mm0

		mov eax,[edi]
		movd mm2,eax
		movq mm3,mm2
		mov eax,flg
		or eax,eax
		jnz SKIP1

		paddusb mm2,mm1		//add
		jmp skip2
SKIP1:
		psubusb mm2,mm1		//sub

SKIP2:
		punpcklbw mm2,mm0
		punpcklbw mm3,mm0


		pmullw mm2,mm4
		pmullw mm3,mm5
		psrlw mm2,8
		psrlw mm3,8

		paddw mm2,mm3
		packuswb mm2,mm0


		movd eax,mm2
		mov [edi],eax
SKIP3:
		add esi,4
		add edi,4
		inc ebx
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ebx
		pop ecx
		add edi,dstPitch
		add esi,srcPitch
		add ebx,maskPitch
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
