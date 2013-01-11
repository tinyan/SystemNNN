#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "blt256Beta.h"


CBlt256Beta::CBlt256Beta()
{
}

CBlt256Beta::~CBlt256Beta()
{
	End();
}

void CBlt256Beta::End(void)
{
}

void CBlt256Beta::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID lpPalette,SIZE srcSize)
{
	char* src = (char*)picData;
	int* dst = CMyGraphics::GetScreenBuffer();
//	char tr = *src;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	src += srcPoint.y * srcSize.cx + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;

	int srcPitch = srcSize.cx * sizeof(char);
	int dstPitch = screenSizeX * 4;

	int* pPal = (int*)lpPalette;

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	if ((loopY<=0) || (loopX<=0)) return;

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
		mov ebx,pPal

		mov ecx,loopY
LOOP1:
		push ecx

		push esi
		push edi

		mov ecx,loopX
LOOP2:
		xor eax,eax
		mov al,[esi]
//		cmp al,tr
//		jz SKIP1
		shl eax,2
		mov edx,[ebx+eax]
		mov [edi],edx
//SKIP1:
		inc esi
		add edi,4

		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		add edi,dstPitch
		add esi,srcPitch

		pop ecx
		dec ecx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}

}
