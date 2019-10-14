#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "addBlt.h"


CAddBlt::CAddBlt()
{
}

CAddBlt::~CAddBlt()
{
	End();
}

void CAddBlt::End(void)
{
}


void CAddBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize)
{
	int* src = (int*)picData;
	int* dst = CMyGraphics::GetScreenBuffer();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	src += srcPoint.y * srcSize.cx + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;

	int srcPitch = srcSize.cx * sizeof(int);
	int dstPitch = screenSizeX * 4;

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	if ((loopY<=0) || (loopX<=0)) return;


	int loopX2 = loopX / 2;
	int loopX2Amari = loopX2 & 1;

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
		mov edx,loopY

		pxor mm6,mm6
		pxor mm7,mm7
LOOP1:
		push esi
		push edi

		mov ecx,loopX2
		or ecx,ecx
		jz SKIP1
LOOP2:
		movq mm0,dword ptr [esi]
		movq mm1,dword ptr [edi]
		paddusb mm0,mm1

        movq dword ptr [edi],mm0

		add esi,8
		add edi,8
		dec ecx
		jnz LOOP2
SKIP1:
		mov ecx,loopX2Amari
		or ecx,ecx
		jz SKIP2

		mov eax,[esi]
		movd mm0,eax
		mov eax,[edi]
		movd mm1,eax
		paddusb mm0,mm1
		movd eax,mm0
		mov [edi],eax
		//add edi,4
SKIP2:
		pop edi
		pop esi
		add edi,dstPitch
		add esi,srcPitch
		dec edx
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
