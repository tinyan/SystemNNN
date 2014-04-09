#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "transLucentBlt0.h"


CTransLucentBlt0::CTransLucentBlt0()
{

}


CTransLucentBlt0::~CTransLucentBlt0()
{
	End();
}


void CTransLucentBlt0::End(void)
{
}


//no mask buki,256fuka
void CTransLucentBlt0::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int transPercent)
{
	transPercent *= 256;
	transPercent /= 100;
     
	DWORD dwAlpha = (DWORD)transPercent;
	DWORD dwAlpha2 = (256 - dwAlpha);

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
LOOP1:
		push esi
		push edi

		mov ecx,loopX
LOOP2:
		movq mm0,dword ptr [esi]
		movd mm1,dword ptr [edi]
//		pxor mm1,mm1


        // byte -> word にアンパック
        punpcklbw mm0,mm6
        punpcklbw mm1,mm7

        // パック掛け算
		pmullw mm0,mm4
		pmullw mm1,mm5

        //  word 単位で足して256で割る
       
		paddw mm0,mm1
		psrlw mm0,8

        // word->byte にパックして転送
        packuswb mm0,mm6
        movd dword ptr [edi],mm0

		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2

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
}

/*_*/

