#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "transLucentBlt3.h"


CTransLucentBlt3::CTransLucentBlt3()
{

}


CTransLucentBlt3::~CTransLucentBlt3()
{
	End();
}


void CTransLucentBlt3::End(void)
{
}


void CTransLucentBlt3::Print(POINT putPoint,POINT srcPoint, SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize, int transPercent)
{
	if (transPercent <= 0) return;

	transPercent *= 256;
	transPercent /= 100;
     
	DWORD dwAlpha = (DWORD)transPercent;
	DWORD dwAlpha2 = (256 - dwAlpha);

	int* src = (int*)picData;
	int* dst = CMyGraphics::GetScreenBuffer();
	char* maskTable = (char*)maskData;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	src += srcPoint.y * srcSize.cx + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;
	maskTable += srcPoint.y * srcSize.cx + srcPoint.x;

	int srcPitch = srcSize.cx * sizeof(int);
	int dstPitch = screenSizeX * 4;
	int maskPitch = srcSize.cx * sizeof(char);

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
		mov edx,loopY

	    movd mm4,dwAlpha 
		punpcklwd mm4,mm4
		punpckldq mm4,mm4 // mm4 =  0α0α0α0α
		movd mm5,dwAlpha2 
		punpcklwd mm5,mm5
		punpckldq mm5,mm5 // mm5 = 0(1-α)0(1-α)0(1-α)0(1-α)

		pxor mm6,mm6
		pxor mm7,mm7

		mov ebx,maskTable
LOOP1:
		push ebx
		push esi
		push edi

		mov ecx,loopX
LOOP2:
///		mov eax,[esi]
//		cmp eax,mask
//		jz SKIP1
///		movd mm0,eax

		movd mm0,dword ptr [esi]

		xor eax,eax
		mov al,[ebx]
		or eax,eax
		jz SKIP1
				
		movd mm1,dword ptr [edi]

        punpcklbw mm0,mm6
        punpcklbw mm1,mm7


		cmp al,0ffh
		jnz TYPE2

        // パック掛け算
        pmullw mm0,mm4
        pmullw mm1,mm5

        //  word 単位で足して256で割る
        paddw mm0,mm1
        psrlw mm0,8

        // word->byte にパックして転送
		jmp OK
TYPE2:
	//	and eax,0ffh
		movd mm2,eax
		punpcklbw mm2,mm6
		punpcklwd mm2,mm2
		punpckldq mm2,mm2
		pmullw mm2,mm4
		psrlw mm2,8

		mov eax,00ff00ffh
		movd mm3,eax
		punpckldq mm3,mm3
		psubw mm3,mm2

        pmullw mm0,mm2
        pmullw mm1,mm3

        paddw mm0,mm1
        psrlw mm0,8


OK:
        packuswb mm0,mm6
        movd dword ptr [edi],mm0

SKIP1:
		add esi,4
		add edi,4
		inc ebx
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		pop ebx
		add edi,dstPitch
		add esi,srcPitch
		add ebx,maskPitch
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
}


/*_*/

