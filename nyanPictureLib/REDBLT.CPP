//
// redBlt.cpp
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
//#include "..\nyanLib\include\picture.h"

#include "redblt.h"


CRedBlt::CRedBlt()
{
}

CRedBlt::~CRedBlt()
{
	End();
}

void CRedBlt::End()
{
}

void CRedBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, BOOL transFlag, LPVOID lpPalette)
{
	//clip
	if (CMyGraphics::Clip(&putPoint,&srcPoint,&putSize,&picSize) == FALSE) return;


	if (lpPalette != NULL)	//256 mode
	{
		if (transFlag)
		{
			RedBltTrans256(putPoint,srcPoint,putSize,srcPic,picSize,lpPalette);
		}
		else
		{
			RedBltBeta256(putPoint,srcPoint,putSize,srcPic,picSize,lpPalette);
		}
		return;
	}


	if (maskPic == NULL)	//oldType(noMask)
	{
		if (transFlag)
		{
			RedBltTrans(putPoint,srcPoint,putSize,srcPic,picSize);
		}
		else
		{
			RedBltBeta(putPoint,srcPoint,putSize,srcPic,picSize);
		}
	}

	MaskRedBlt(putPoint,srcPoint,putSize,srcPic,picSize,maskPic);
}



void CRedBlt::RedBltTrans256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize, LPVOID lpPalette)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int picSizeX = picSize.cx;
//	int picSizeY = picSize.cy;
	int dstPitch = screenSizeX * sizeof(int);
	int* dst = CMyGraphics::GetScreenBuffer();

	char* src = (char*)srcPic;
	char tr = *src;

	src += srcPoint.y * picSizeX + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;

	int* pPal = (int*)lpPalette;

	int srcPitch = picSize.cx;

	int loopY = putSize.cy;
	int loopX = putSize.cx;

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
		mov ebx,pPal

		mov ecx,loopY
LOOP_T256_1:
		push ecx

		push esi
		push edi

		mov ecx,loopX
LOOP_T256_2:
		xor eax,eax
		mov al,[esi]
		cmp al,tr

		jz SKIP_T256
		shl eax,2
		mov edx,[ebx+eax]
				
		and edx,0ff0000h

		mov [edi],edx
SKIP_T256:
		inc esi
		add edi,4

		dec ecx
		jnz LOOP_T256_2

		pop edi
		pop esi

		add edi,dstPitch
		add esi,srcPitch

		pop ecx
		dec ecx
		jnz LOOP_T256_1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}


void CRedBlt::RedBltBeta256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize, LPVOID lpPalette)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int picSizeX = picSize.cx;
//	int picSizeY = picSize.cy;
	int dstPitch = screenSizeX * sizeof(int);
	int* dst = CMyGraphics::GetScreenBuffer();

	char* src = (char*)srcPic;
//	char tr = *src;

	src += srcPoint.y * picSizeX + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;

	int* pPal = (int*)lpPalette;

	int srcPitch = picSizeX;

	int loopY = putSize.cy;
	int loopX = putSize.cy;

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
		mov ebx,pPal

		mov ecx,loopY
LOOP_256_1:
		push ecx

		push esi
		push edi

		mov ecx,loopX
LOOP_256_2:
		xor eax,eax
		mov al,[esi]
//		cmp al,tr
//		jz SKIP256T
		shl eax,2
		mov edx,[ebx+eax]
				
		and edx,0ff0000h

		mov [edi],edx
//SSKIP256T:
		inc esi
		add edi,4

		dec ecx
		jnz LOOP_256_2

		pop edi
		pop esi
		add edi,dstPitch
		add esi,srcPitch

		pop ecx
		dec ecx
		jnz LOOP_256_1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}


void CRedBlt::RedBltTrans(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int picSizeX = picSize.cx;
//	int picSizeY = picSize.cy;
	int dstPitch = screenSizeX * sizeof(int);
	int* dst = CMyGraphics::GetScreenBuffer();

	int* src = (int*)srcPic;
	int tr = *src;

	src += srcPoint.y * picSizeX + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;

	int srcPitch = picSize.cx * sizeof(int);

	int loopY = putSize.cy;
	int loopX = putSize.cy;

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


		mov ebx,tr
		mov edx,loopY
LOOP_T_1:
		push esi
		push edi
		mov ecx,loopX
LOOP_T_2:
		mov eax,[esi]
		cmp eax,ebx
		jz SKIP_T
		and eax,0ff0000h
		mov [edi],eax
SKIP_T:
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP_T_2

		pop edi
		pop esi
		add edi,dstPitch
		add esi,srcPitch
		dec edx
		jnz LOOP_T_1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}

void CRedBlt::RedBltBeta(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int picSizeX = picSize.cx;
//	int picSizeY = picSize.cy;
	int dstPitch = screenSizeX * sizeof(int);
	int* dst = CMyGraphics::GetScreenBuffer();

	int* src = (int*)srcPic;
	int tr = *src;

	src += srcPoint.y * picSizeX + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;

	int srcPitch = picSize.cx * sizeof(int);
	int loopY = putSize.cy;
	int loopX = putSize.cx;

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


		mov ebx,tr
		mov edx,loopY
LOOP_1:
		push esi
		push edi
		mov ecx,loopX
LOOP_2:
		mov eax,[esi]
//				cmp eax,ebx
//				jz SKIPB1
		and eax,0ff0000h
		mov [edi],eax
//	SSKIPB1:
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP_2

		pop edi
		pop esi
		add edi,dstPitch
		add esi,srcPitch
		dec edx
		jnz LOOP_1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}


void CRedBlt::MaskRedBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int picSizeX = picSize.cx;
//	int picSizeY = picSize.cy;
	int dstPitch = screenSizeX * sizeof(int);
	int* dst = CMyGraphics::GetScreenBuffer();




	int* src = (int*)srcPic;

	src += srcPoint.y * picSizeX + srcPoint.x;
	dst += putPoint.y * screenSizeX + putPoint.x;

	maskPic += srcPoint.x;
	maskPic += srcPoint.y * picSizeX;

	int srcPitch = picSizeX * 4;
	int maskPitch = picSizeX;
	int loopY = putSize.cy;
	int loopX = putSize.cx;


	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0


		mov esi,src
		mov edi,dst
		mov ebx,maskPic

		mov ecx,loopY
LOOP_M_1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,loopX
LOOP_M_2:
		mov al,[ebx]
		or al,al
		jz SKIP_M
		cmp al,255
		jz NORMAL_M

		mov edx,[esi]
		and edx,0ff0000h
		movd mm1,edx

		mov edx,[edi]
		movd mm2,edx

		punpcklbw mm1,mm0
		punpcklbw mm2,mm0

		movd mm3,eax
		not al
		movd mm4,eax
		punpcklbw mm3,mm0
		punpcklbw mm4,mm0
		punpcklwd mm3,mm3
		punpcklwd mm4,mm4
		punpckldq mm3,mm3
		punpckldq mm4,mm4

		pmullw mm1,mm3
		pmullw mm2,mm4

		paddw mm1,mm2
		psrlw mm1,8
		packuswb mm1,mm0

		movd edx,mm1
		mov [edi],edx

		jmp SKIP_M
NORMAL_M:
		mov edx,[esi]
		and edx,0ff0000h
		mov [edi],edx
SKIP_M:

		add esi,4
		add edi,4
		inc ebx
		dec ecx
		jnz LOOP_M_2

		pop edi
		pop esi
		pop ebx
		pop ecx
			
		add edi,dstPitch
		add esi,srcPitch
		add ebx,maskPitch

		dec ecx
		jnz LOOP_M_1

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


