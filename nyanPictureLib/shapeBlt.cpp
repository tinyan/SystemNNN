#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "shapeBlt.h"



CShapeBlt::CShapeBlt()
{
}

CShapeBlt::~CShapeBlt()
{
	End();
}

void CShapeBlt::End(void)
{
}

void CShapeBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID maskData,SIZE srcSize,int r,int g,int b)
{
	char* src = (char*)maskData;
	int* dst = CMyGraphics::GetScreenBuffer();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	src += srcPoint.y * srcSize.cx + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;

	int srcPitch = srcSize.cx * sizeof(char);
	int dstPitch = screenSizeX * 4;

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	int col = (r<<16) | (g<<8) | b;

	if ((loopY<=0) || (loopX<=0)) return;

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

		mov ebx,src
		mov dl,[ebx]

		mov esi,src
		mov edi,dst
		mov eax,col

		mov ecx,loopY
LOOP1:
		push ecx
		push esi
		push edi

		mov ecx,loopX
LOOP2:
		cmp dl,[esi]
		jz SKIP1
		mov [edi],eax
SKIP1:
		inc esi
		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ecx
		add edi,dstPitch
		add esi,srcPitch
		dec ecx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#endif

}