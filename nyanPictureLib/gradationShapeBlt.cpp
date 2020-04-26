#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "gradationShapeBlt.h"



CGradationShapeBlt::CGradationShapeBlt()
{
}

CGradationShapeBlt::~CGradationShapeBlt()
{
	End();
}

void CGradationShapeBlt::End(void)
{
}

void CGradationShapeBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID maskData,SIZE srcSize,int r1,int g1,int b1,int r2,int g2,int b2)
{
//	int yStart = srcPoint.y;

	char* src = (char*)maskData;
	int* dst = CMyGraphics::GetScreenBuffer();

	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	src += (SSIZE_T)srcPoint.y * srcSize.cx + srcPoint.x;
	dst += (SSIZE_T)putPoint.y * screenSizeX + putPoint.x;

	int srcPitch = srcSize.cx * sizeof(char);
	int dstPitch = screenSizeX * 4;

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	if ((loopY<=0) || (loopX<=0)) return;


	int* colorTable = CMyGraphics::GetCommonX8Buffer();

	int deltaY = srcPoint.y;
	int dv = srcSize.cy;
	if (dv<1) dv = 1;

	int dr = r2 - r1;
	int dg = g2 - g1;
	int db = b2 - b1;

	for (int j=0;j<loopY;j++)
	{
		int yy = j + deltaY;
		
		int rr = r1 + (dr * yy ) / dv;
		int gg = g1 + (dg * yy ) / dv;
		int bb = b1 + (db * yy ) / dv;

		if (rr<0) rr = 0;
		if (rr>255) rr = 255;
		if (gg<0) gg = 0;
		if (gg>255) gg = 255;
		if (bb<0) bb = 0;
		if (bb>255) bb = 255;

		colorTable[j] = (rr << 16) | (gg<<8) | bb;
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

		mov ebx,src
		mov dl,[ebx]

		mov esi,src
		mov edi,dst

		mov ebx,colorTable

		mov ecx,loopY
LOOP1:
		push ecx
		push esi
		push edi

		mov eax,[ebx]
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
		add ebx,4

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

