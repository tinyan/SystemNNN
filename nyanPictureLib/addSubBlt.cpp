#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "addSubBlt.h"


CAddSubBlt::CAddSubBlt()
{
}

CAddSubBlt::~CAddSubBlt()
{
	End();
}

void CAddSubBlt::End(void)
{
}

void CAddSubBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,char* maskData,SIZE srcSize,int percent)
//void CAddSubBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize)
{
	if (percent == 0) return;

	int* src = (int*)picData;
	int* dst = CMyGraphics::GetScreenBuffer();
	char* mask = maskData;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	src += (SSIZE_T)srcPoint.y * srcSize.cx + srcPoint.x;
	mask += (SSIZE_T)srcPoint.y * srcSize.cx + srcPoint.x;
	dst += (SSIZE_T)putPoint.y * screenSizeX + putPoint.x;

	int srcPitch = srcSize.cx * sizeof(int);
	int maskPitch = srcSize.cx;
	int dstPitch = screenSizeX * 4;

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	if ((loopY<=0) || (loopX<=0)) return;


	percent *= 256;
	percent /= 100;

	int flg = 0;
	if (percent < 0)
	{
		flg = 1;
		percent *= -1;
	}

#if defined _WIN64
	INT32* src64Org = src;
	INT32* dst64Org = dst;
	char* mask64Org = mask;

	for (int j = 0; j < loopY; j++)
	{
		INT32* src64 = src64Org;
		INT32* dst64 = dst64Org;
		char* mask64 = mask64Org;
		for (int i = 0; i < loopX; i++)
		{
			INT32 maskData = (INT32)(*mask64);
			maskData &= 0xff;

			if (maskData != 0)
			{
				INT32 srcData = *src64;
				INT32 srcR = (srcData >> 16) & 0xff;
				INT32 srcG = (srcData >> 8) & 0xff;
				INT32 srcB = (srcData) & 0xff;


				INT32 dstData = *dst64;
				INT32 dstR = (dstData >> 16) & 0xff;
				INT32 dstG = (dstData >> 8) & 0xff;
				INT32 dstB = (dstData) & 0xff;

				INT32 r = dstR + (srcR * percent) / 256;
				INT32 g = dstG + (srcG * percent) / 256;
				INT32 b = dstB + (srcB * percent) / 256;

				if (r < 0) r = 0;
				if (r > 255) r = 255;
				if (g < 0) g = 0;
				if (g > 255) g = 255;
				if (b < 0) b = 0;
				if (b > 255) b = 255;


				INT32 colorR = r * maskData + dstR * (255 - maskData);
				INT32 colorG = g * maskData + dstG * (255 - maskData);
				INT32 colorB = b * maskData + dstB * (255 - maskData);
				colorR /= 255;
				colorG /= 255;
				colorB /= 255;

				INT32 color = (colorR << 16) | (colorG << 8) | colorB;
				*dst64 = color;
			}

			src64++;
			dst64++;
			mask64++;
		}

		src64Org += srcPitch / 4;
		dst64Org += dstPitch / 4;
		mask64Org += maskPitch;
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
		mov ebx,mask
		mov ecx,loopY

		pxor mm0,mm0
		mov eax,percent

		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7

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
		jz SKIP3
		movd mm4,eax

		neg eax
		add eax,256
		movd mm5,eax

		punpcklwd mm4,mm4
		punpcklwd mm5,mm5
		punpckldq mm4,mm4
		punpckldq mm5,mm5




		mov eax,[esi]
		movd mm1,eax
		punpcklbw mm1,mm0
		movq mm2,mm1
		pmullw mm1,mm7
		pmulhw mm2,mm7
		psrlw mm1,8
		psllw mm2,8
		por mm1,mm2
		packuswb mm1,mm0

		mov eax,[edi]
		movd mm2,eax
		movq mm3,mm2
		mov eax,flg
		or eax,eax
		jnz SKIP1

		paddusb mm2,mm1		//add
		jmp skip2
SKIP1:
		psubusb mm2,mm1		//sub

SKIP2:
		punpcklbw mm2,mm0
		punpcklbw mm3,mm0


		pmullw mm2,mm4
		pmullw mm3,mm5
		psrlw mm2,8
		psrlw mm3,8

		paddw mm2,mm3
		packuswb mm2,mm0


		movd eax,mm2
		mov [edi],eax
SKIP3:
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
