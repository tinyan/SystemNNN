
#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "yuvChangeBlt.h"

CYUVChangeBlt::CYUVChangeBlt()
{
	for (int i=0;i<256;i++)
	{
		if (i == 0)
		{
			m_table256[i] = 32767;
		}
		else
		{
			m_table256[i] = 32767 / i;
		}
	}
}

CYUVChangeBlt::~CYUVChangeBlt()
{
	End();
}

void CYUVChangeBlt::End(void)
{
}


void CYUVChangeBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE picSize,BOOL yuvReverseFlag,int betaTransPercent255)
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


	//mask Ç†ÇËÇ»ÇµÅAreverseflag


//RGB<-->YCC(YCbCr)Y = 0.29900*R + 0.58700*G + 0.11400*B
//Cb = -0.16874*R - 0.33126*G + 0.50000*B + CENTER
//Cr = 0.50000*R - 0.41869*G - 0.08131*B + CENTER

//R = Y + 1.402*(Cr-CENTER)
//G = Y - 0.34414*(Cb-CENTER) - 0.71414*(Cr-CENTER)
//B = Y + 1.772*(Cb-CENTER)

//9798,19234,3736			2646 4B22 0E98
//-5529,-10855,16384		EA67 D599 4000
//16384,-13720,-2664		4000 CA68 F598

// 8192,0,11485				2000 0000 2CDD
// 8192,-2819,-5850			2000 F4FD E926
// 8192,14516,0				2000 38B4 0000


	
	__int64 param_toY = 0x26464b220e98;
//	__int64 param_toU = 0xea67d5994000;
//	__int64 param_toV = 0x4000ca68f598;

//	__int64 param_toR = 0x200000002c00;
//	__int64 param_toG = 0x2000f4fde926;
//	__int64 param_toB = 0x200038b40000;


	int maskFlag = 0;
	if (maskData == NULL) maskFlag = betaTransPercent255;

	int reverseFlag = yuvReverseFlag;

	int* tablePtr = m_table256;

#if defined _WIN64
#pragma message("Ç±Ç±Ç…c++é¿ëïÇ™ïKóvÇ…Ç· " __FILE__)

#else

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

		movq mm6,param_toY

		mov eax,0ffffh
		movd mm4,eax

		mov ecx,loopY
LOOP1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,loopX
LOOP2:
		mov edx,maskFlag
		or edx,edx
		jnz NONMASK

//		xor edx,edx
		mov dl,[ebx]
		or edx,edx
		jz SKIP1
NONMASK:
		mov eax,[esi]
		movd mm1,eax
		punpcklbw mm1,mm0

		mov eax,[edi]
		movd mm2,eax
		punpcklbw mm2,mm0
		movq mm3,mm2

		mov eax,reverseFlag
		or eax,eax
		jz NONREV
		movq mm3,mm1
		movq mm1,mm2
		movq mm2,mm3
NONREV:
		pmaddwd mm1,mm6
		pmaddwd mm2,mm6

		movq mm5,mm1
		psrlq mm5,32
		paddd mm1,mm5
		pslld mm1,1
		psrld mm1,16
		pand mm1,mm4
		packuswb mm1,mm0
		//Y1

		movq mm5,mm2
		psrlq mm5,32
		paddd mm2,mm5
		pslld mm2,1
		psrld mm2,16
		pand mm2,mm4
		packuswb mm2,mm0
		//Y2

		//
		// RGB = rgb*Y1/Y2
		//

		movd eax,mm2
		shl eax,2
		add eax,tablePtr
		mov eax,[eax]

		movd mm2,eax

		pmaddwd mm1,mm2
		//stall
		//stall
		psrld mm1,8

		movq mm7,mm1

		punpckldq mm1,mm1
		pmaddwd mm1,mm3

		pslld mm7,16

		pmaddwd mm7,mm3

		psrld mm1,7
		psrld mm7,7

		pslld mm7,16
		por mm1,mm7


		movq mm7,mm1
		packuswb mm1,mm0

		//mask?
		cmp edx,255
		jz NORMAL

		mov eax,[edi]

		//Ç≥ÇÁÇ…îºìßñæ
		jb NORMALTRANS

		//256à»è„ÇÕå≥âÊëúÇ∆îºìßñæèàóù
		neg edx
		add edx,511
		mov eax,[esi]

NORMALTRANS:
		movd mm2,edx
		punpcklwd mm2,mm2
		punpckldq mm2,mm2
		pmullw mm7,mm2

//		mov eax,[edi]
		movd mm3,eax
		punpcklbw mm3,mm0

		not dl
		movd mm2,edx
		punpcklwd mm2,mm2
		punpckldq mm2,mm2
		pmullw mm3,mm2


		psrlw mm7,7
		psrlw mm3,7

		paddw mm7,mm3
		psrlw mm7,1

		packuswb mm7,mm0
		movq mm1,mm7

NORMAL:
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

#endif

}


/*_*/

