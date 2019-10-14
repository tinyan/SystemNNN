//
// transBoxFill
//

#include <windows.h>
//#include <stdio.h>
//#include <Math.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "transBoxFill.h"


CTransBoxFill::CTransBoxFill()
{
}


CTransBoxFill::~CTransBoxFill()
{
	End();
}

void CTransBoxFill::End(void)
{
}







void CTransBoxFill::Print(int x, int y, int sizeX, int sizeY, int r, int g, int b, int ps)
{
	//clip
	if (CMyGraphics::Clip(&x,&y,&sizeX,&sizeY) == FALSE) return;

	//print
//	int* dst = (int*)CPicture::m_lpScreenBuffer;
	int* dst = CMyGraphics::GetScreenBuffer();
//	int screenSizeX = CPicture::m_screenSizeX;
	int screenSizeX = CMyGraphics::GetScreenSizeX();

	dst += x;
	dst += y*screenSizeX;

	int loopX = sizeX;
	int loopY = sizeY;

	if (ps<0) ps = 0;
	if (ps>100) ps = 100;

	int transPercent = ps * 256;
	transPercent /= 100;
     
	DWORD dwAlpha = (DWORD)transPercent;
	DWORD dwAlpha2 = (256 - dwAlpha);



	int col = (r<<16) | (g<<8) | b;
	int lPitch = screenSizeX * sizeof(int);

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

	    movd mm4,dwAlpha 
		punpcklwd mm4,mm4
		punpckldq mm4,mm4 // mm4 =  0ƒ¿0ƒ¿0ƒ¿0ƒ¿
		movd mm5,dwAlpha2 
		punpcklwd mm5,mm5
		punpckldq mm5,mm5 // mm5 = 0(1-ƒ¿)0(1-ƒ¿)0(1-ƒ¿)0(1-ƒ¿)

		mov eax,col
		movd mm3,eax
		punpcklbw mm3,mm0

		pmullw mm3,mm4



		pxor mm6,mm6
		pxor mm7,mm7

		mov edi,dst
		mov edx,loopY
		mov eax,col
LOOP1:
		push edi
		mov ecx,loopX
LOOP2:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0

		pmullw mm1,mm5

        paddw mm1,mm3
        psrlw mm1,8

        packuswb mm1,mm0
        movd dword ptr [edi],mm1
		
		add edi,4

		dec ecx
		jnz LOOP2

		pop edi
		add edi,lPitch
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
