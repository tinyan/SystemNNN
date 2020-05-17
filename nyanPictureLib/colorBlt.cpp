//
//
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
//#include "..\nyanLib\include\picture.h"

#include "colorblt.h"


CColorBlt::CColorBlt()
{
}

CColorBlt::~CColorBlt()
{
	End();
}

void CColorBlt::End(void)
{
}

void CColorBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,char* maskPic,SIZE srcSize,int r,int g,int b)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* dst = CMyGraphics::GetScreenBuffer();
	dst += putPoint.x;
	dst += (SSIZE_T)putPoint.y * screenSizeX;

	char* mask = maskPic;
	mask += srcPoint.x;
	mask += (SSIZE_T)srcPoint.y * srcSize.cx;


	int maskPitch = srcSize.cx;
	int dstPitch = screenSizeX * sizeof(int);

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	if ((loopX<=0) || (loopY<=0)) return;

	int col = (r << 16) | (g<<8) | b;

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

		pxor mm0,mm0

		mov ebx,mask
		mov edi,dst

		mov edx,loopY
LOOP1:
		push ebx
		push edx
		push esi
		push edi

		mov edx,col

		mov ecx,loopX
LOOP2:
		xor eax,eax
		mov al,[ebx]
		or eax,eax
		jz SKIP1

		cmp al,255
		jz NORMAL1
	
		movd mm1,eax
		punpcklwd mm1,mm1
		not al
		movd mm2,eax
		punpckldq mm1,mm1
		mov eax,edx			//not SRC
		punpcklwd mm2,mm2
		movd mm3,eax
		punpckldq mm2,mm2
		mov eax,[edi]
		punpcklbw mm3,mm0
		movd mm4,eax
		pmullw mm1,mm3
		punpcklbw mm4,mm0
		pmullw mm2,mm4
		//stall
		//stall
		paddw mm1,mm2
		psrlw mm1,8
		packuswb mm1,mm0
		movd eax,mm1

		mov [edi],eax
		jmp SKIP1

NORMAL1:
		mov [edi],edx
SKIP1:
		inc ebx
//		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop edx
		pop ebx

		add ebx,maskPitch
//		add esi,srcDelta
		add edi,dstPitch

		dec edx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax

		emms
	}
#endif

}
