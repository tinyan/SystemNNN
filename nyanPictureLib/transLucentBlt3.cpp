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

	src += (SSIZE_T)srcPoint.y * srcSize.cx + srcPoint.x;
	dst += (SSIZE_T)putPoint.y * screenSizeX + putPoint.x;
	maskTable += (SSIZE_T)srcPoint.y * srcSize.cx + srcPoint.x;

	int srcPitch = srcSize.cx * sizeof(int);
	int dstPitch = screenSizeX * 4;
	int maskPitch = srcSize.cx * sizeof(char);

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	if ((loopY<=0) || (loopX<=0)) return;

	int alpha = transPercent;
	int one_minus_alpha = 256 - transPercent;


#if defined _WIN64


	int* esi = src;
	int* edi = dst;
	char* ebx = maskTable;

	for (int j = 0; j < loopY; j++)
	{
		int* pushesi = esi;
		int* pushedi = edi;
		char* pushebx = ebx;

		for (int i = 0; i < loopX; i++)
		{
			int maskData = 0xff & (int)(*ebx);
			if (maskData != 0)
			{
				int srcData = *src;
				int dstData = *dst;

				int alpha2 = maskData * alpha;
				int one_minus_alpha2 = 256 - alpha2;

				if (alpha2 == 255*255)
				{
					*edi = srcData;
				}
				else
				{
					int srcR = (srcData >> 16) & 0xff;
					int srcG = (srcData >> 8) & 0xff;
					int srcB = (srcData) & 0xff;

					int dstData = *edi;
					int dstR = (dstData >> 16) & 0xff;
					int dstG = (dstData >> 8) & 0xff;
					int dstB = (dstData) & 0xff;

					int colR = srcR * alpha + dstR * one_minus_alpha;
					int colG = srcG * alpha + dstG * one_minus_alpha;
					int colB = srcB * alpha + dstB * one_minus_alpha;

					colR >>= 8;
					colG >>= 8;
					colB >>= 8;

					int color = (colR << 16) | (colG << 8) | colB;

					*edi = color;


				}
			}
			esi++;
			edi++;
			ebx++;
		}
		esi = pushesi;
		edi = pushedi;
		ebx = pushebx;
		esi += srcPitch / 4;
		edi += dstPitch / 4;
		ebx += maskPitch;
	}
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
#endif

}


/*_*/

