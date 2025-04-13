#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "colorAddBlt.h"


CColorAddBlt::CColorAddBlt()
{
}


CColorAddBlt::~CColorAddBlt()
{
	End();
}

void CColorAddBlt::End(void)
{
}

void CColorAddBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize,BOOL transFlag,int r,int g,int b,int ps)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int addR = r;
	int subR = r;
	int addG = g;
	int subG = g;
	int addB = b;
	int subB = b;

	if (addR<0) addR = 0;
	if (subR>0) subR = 0;
	if (addG<0) addG = 0;
	if (subG>0) subG = 0;
	if (addB<0) addB = 0;
	if (subB>0) subB = 0;

	subR *= -1;
	subG *= -1;
	subB *= -1;


	int addLight = (addR<<16) | (addG<<8) | addB;
	int subLight = (subR<<16) | (subG<<8) | subB;

//	int light = (r<<16) | (g<<8) | b;

	int* src = (int*)picData;
	int tr = *src;

	int* dst = CMyGraphics::GetScreenBuffer();

	src += (SSIZE_T)srcPoint.y  * srcSize.cx + srcPoint.x;
	dst += (SSIZE_T)putPoint.y  * screenSizeX + putPoint.x;

	int srcPitch = srcSize.cx * sizeof(int);
	int loopY = putSize.cy;
	int loopX = putSize.cx;

	int dstPitch = screenSizeX * sizeof(int);

	char* mask = (char*)maskData;

	int transPercent256 = (ps * 256) / 100;

#if defined _WIN64
	INT32 maskPicSizeX = 0;
	INT32 maskPitch = 0;

	if (mask != NULL)
	{
		maskPicSizeX = srcSize.cx;

		mask += srcPoint.x;
		mask += (SSIZE_T)srcPoint.y * maskPicSizeX;
		maskPitch = srcSize.cx;
	}

	INT32* src64Org = (INT32*)src;
	INT32* dst64Org = (INT32*)dst;
	char* mask64Org = (char*)mask;

	for (int j = 0; j < loopY; j++)
	{
		INT32* src64 = src64Org;
		INT32* dst64 = dst64Org;
		char* mask64 = mask64Org;

		for (int i = 0; i < loopX; i++)
		{
			INT32 transPercent = 255;
			if (transFlag && (mask != NULL))
			{
				transPercent = ((INT32)(*mask64)) & 0xff;
			}

			if (transPercent != 0)
			{
				INT32 srcData = *src64;
				INT32 dstData = *dst64;
				INT32 srcR = (srcData >> 16) & 0xff;
				INT32 srcG = (srcData >> 8) & 0xff;
				INT32 srcB = (srcData ) & 0xff;
				INT32 dstR = (dstData >> 16) & 0xff;
				INT32 dstG = (dstData >> 8) & 0xff;
				INT32 dstB = (dstData) & 0xff;
				srcR += addR;
				srcR -= subR;
				if (srcR < 0) srcR = 0;
				if (srcR > 255) srcR = 255;
				srcG += addG;
				srcG -= subG;
				if (srcG < 0) srcG = 0;
				if (srcG > 255) srcG = 255;
				srcB += addB;
				srcB -= subB;
				if (srcB < 0) srcB = 0;
				if (srcB > 255) srcB = 255;

				if (transPercent == 255)
				{
					*dst64 = (srcR << 16) | (srcG << 8) | srcB;
				}
				else
				{
					INT32 r = srcR * transPercent + dstR * (255 - transPercent);
					r /= 255;
					INT32 g = srcG * transPercent + dstG * (255 - transPercent);
					g /= 255;
					INT32 b = srcB * transPercent + dstB * (255 - transPercent);
					b /= 255;
					*dst64 = (r << 16) | (g << 8) | b;
				}
			}

			src64++;
			dst64++;
			if (mask != NULL)
			{
				mask64++;
			}
		}

		dst64Org += dstPitch / 4;
		src64Org += srcPitch / 4;
		if (mask != NULL)
		{
			mask64Org += maskPitch;
		}
	}

	return;
#else


	if (transFlag && (mask != NULL))
	{
		int maskPicSizeX = srcSize.cx;

		mask += srcPoint.x;
		mask += (SSIZE_T)srcPoint.y * maskPicSizeX;
		int maskPitch = srcSize.cx;

#if defined _WIN64

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
			movd mm7,addLight
			movd mm6,subLight

			mov esi,src
			mov edi,dst
			mov ebx,mask
			mov ecx,loopY
LOOPD1:
			push ecx
			push ebx
			push esi
			push edi

			mov ecx,loopX
LOOPD2:
			xor eax,eax
			mov al,[ebx]
			or al,al
			jz SKIPD1

			mov edx,transPercent256
			cmp edx,256
			jz NOTMUL

			mul edx
			shr eax,8

NOTMUL:



			cmp al,255
			jz NORMALD1

			mov edx,[esi]
			movd mm1,edx
			paddusb mm1,mm7
			psubusb mm1,mm6

			punpcklbw mm1,mm0

			movd mm3,eax
			not al
			movd mm4,eax
			punpcklbw mm3,mm0
			punpcklbw mm4,mm0
			punpcklwd mm3,mm3
			punpcklwd mm4,mm4
			punpckldq mm3,mm3
			punpckldq mm4,mm4

			mov edx,[edi]
			movd mm2,edx
			punpcklbw mm2,mm0

			pmullw mm1,mm3
			pmullw mm2,mm4

			paddw mm1,mm2
			psrlw mm1,8
			packuswb mm1,mm0

			movd edx,mm1
			mov [edi],edx


			jmp SKIPD1
NORMALD1:
			mov edx,[esi]
			movd mm1,edx
			paddusb mm1,mm7
			psubusb mm1,mm6
			movd edx,mm1
			mov [edi],edx
SKIPD1:
			add esi,4
			add edi,4
			inc ebx
			dec ecx
			jnz LOOPD2

			pop edi
			pop esi
			pop ebx
			pop ecx
			add esi,srcPitch
			add edi,dstPitch
			add ebx,maskPitch
			dec ecx
			jnz LOOPD1

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
	else
	{
		if (transFlag)
		{
#if defined _WIN64

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
				mov eax,transPercent256
				movd mm3,eax
				punpcklwd mm3,mm3
				punpckldq mm3,mm3
				neg eax
				add eax,256
				movd mm4,eax
				punpcklwd mm4,mm4
				punpckldq mm4,mm4



				mov esi,src
				mov edi,dst

				movd mm7,addLight
				movd mm6,subLight

				mov ebx,tr
				mov edx,loopY
LOOPB1:
				push edx
				push esi
				push edi
				mov ecx,loopX
LOOPB2:
				mov eax,[esi]
				cmp eax,ebx
				jz SKIPB1

//				mov eax,[edi]
				movd mm1,eax
				paddusb mm1,mm7
				psubusb mm1,mm6
				movd eax,mm1

				mov edx,transPercent256
				cmp edx,256
				jz NOTMUL2

				mov eax,[edi]
				movd mm2,eax
				punpcklbw mm1,mm0
				punpcklbw mm2,mm0
				pmullw mm1,mm3
				pmullw mm2,mm4
				paddw mm1,mm2
				psrlw mm1,8
				packuswb mm1,mm1
				movd eax,mm1

NOTMUL2:
				mov [edi],eax
SKIPB1:
				add esi,4
				add edi,4
				dec ecx
				jnz LOOPB2

				pop edi
				pop esi
				pop edx
				add edi,dstPitch
				add esi,srcPitch
				dec edx
				jnz LOOPB1

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
		else
		{
#if defined _WIN64

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
				mov eax,transPercent256
				movd mm3,eax
				punpcklwd mm3,mm3
				punpckldq mm3,mm3
				neg eax
				add eax,256
				movd mm4,eax
				punpcklwd mm4,mm4
				punpckldq mm4,mm4

				mov esi,src
				mov edi,dst

				movd mm7,addLight
				movd mm6,subLight

				mov ebx,tr
				mov edx,loopY
LLOOPB1:
				push edx
				push esi
				push edi
				mov ecx,loopX
LLOOPB2:
				mov eax,[esi]
//				cmp eax,ebx
//				jz SSKIPB1
//				mov eax,[edi]
				movd mm1,eax
				paddusb mm1,mm7
				psubusb mm1,mm6
				movd eax,mm1

				mov edx,transPercent256
				cmp edx,256
				jz NOTMUL3

				mov eax,[edi]
				movd mm2,eax
				punpcklbw mm1,mm0
				punpcklbw mm2,mm0
				pmullw mm1,mm3
				pmullw mm2,mm4
				paddw mm1,mm2
				psrlw mm1,8
				packuswb mm1,mm1
				movd eax,mm1


NOTMUL3:
				mov [edi],eax
//SSKIPB1:
				add esi,4
				add edi,4
				dec ecx
				jnz LLOOPB2

				pop edi
				pop esi
				pop edx
				add edi,dstPitch
				add esi,srcPitch
				dec edx
				jnz LLOOPB1


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
	}
#endif

}



/*_*/

