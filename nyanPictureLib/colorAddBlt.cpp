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

	src += srcPoint.y  * srcSize.cx + srcPoint.x;
	dst += putPoint.y  * screenSizeX + putPoint.x;

	int srcPitch = srcSize.cx * sizeof(int);
	int loopY = putSize.cy;
	int loopX = putSize.cx;

	int dstPitch = screenSizeX * sizeof(int);

	char* mask = (char*)maskData;

	int transPercent256 = (ps * 256) / 100;

	if (transFlag && (mask != NULL))
	{
		int maskPicSizeX = srcSize.cx;

		mask += srcPoint.x;
		mask += srcPoint.y * maskPicSizeX;
		int maskPitch = srcSize.cx;

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
	}
	else
	{
		if (transFlag)
		{
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
		}
		else
		{
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

		}
	}
}



/*_*/

