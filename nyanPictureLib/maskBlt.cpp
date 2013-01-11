
#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "maskBlt.h"

CMaskBlt::CMaskBlt()
{
}

CMaskBlt::~CMaskBlt()
{
	End();
}

void CMaskBlt::End(void)
{
}


void CMaskBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE picSize)
{
//	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

//	if (sizeX<=0) return;
//	if (sizeY<=0) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* src = (int*)picData;
	int* dst = CMyGraphics::GetScreenBuffer();
	char* mask = (char*)maskData;

	src += srcPoint.x;
	src += srcPoint.y * picSize.cx;

	dst += putPoint.x;
	dst += putPoint.y * screenSizeX;

	mask += srcPoint.x;
	mask += srcPoint.y * picSize.cx;


	int dstPitch = screenSizeX * sizeof(int);
	int srcPitch = picSize.cx * sizeof(int);
	int maskPitch = picSize.cx;

	int loopX = putSize.cx;
	int loopY = putSize.cy;

	if ((loopX <= 0) || (loopY <= 0)) return;


	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov ebx,mask
		mov esi,src
		mov edi,dst

		pxor mm0,mm0

		mov ecx,loopY
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
		jz SKIP1
		cmp eax,0ffh
		jnz TRANS
		mov eax,[esi]
		mov [edi],eax
		jmp SKIP1
TRANS:
		movd mm1,[esi]
		movd mm4,eax
		neg eax
		movd mm2,[edi]
		add eax,256
		punpcklbw mm1,mm0
		movd mm5,eax
		punpcklbw mm2,mm0

		punpcklwd mm4,mm4
		punpcklwd mm5,mm5
		punpckldq mm4,mm4
		punpckldq mm5,mm5
	
		pmullw mm1,mm4
		pmullw mm2,mm5

		psrlw mm1,8
		psrlw mm2,8

		paddw mm1,mm2
		packuswb mm1,mm0

		movd eax,mm1

		mov [edi],eax
SKIP1:
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

