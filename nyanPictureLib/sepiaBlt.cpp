//
// Sepiablt.cpp
//

#include <windows.h>
//#include <stdio.h>

#include "..\nyanlib\include\commonmacro.h"
#include "..\nyanlib\include\myGraphics.h"
#include "sepiablt.h"



CSepiaBlt::CSepiaBlt()
{
}

CSepiaBlt::~CSepiaBlt()
{
	End();
}

void CSepiaBlt::End(void)
{
}


void CSepiaBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, int ps256,int r,int g,int b,BOOL transFlag, LPVOID lpPalette)
{
	//clip
	if (CMyGraphics::Clip(&putPoint,&srcPoint,&putSize,&picSize) == FALSE) return;

/*
	if (lpPalette != NULL)	//256 mode
	{
		if (transFlag)
		{
			SepiaBltTrans256(putPoint,srcPoint,putSize,srcPic,picSize,lpPalette);
		}
		else
		{
			SepiaBltBeta256(putPoint,srcPoint,putSize,srcPic,picSize,lpPalette);
		}
		return;
	}
*/


	if (maskPic == NULL)	//oldType(noMask)
	{

		SepiaBltBeta(putPoint,srcPoint,putSize,srcPic,picSize,ps256,r,g,b);
/*
		if (transFlag)
		{
			SepiaBltTrans(putPoint,srcPoint,putSize,srcPic,picSize);
		}
		else
		{
			SepiaBltBeta(putPoint,srcPoint,putSize,srcPic,picSize);
		}
*/
		return;

	}

	MaskSepiaBlt(putPoint,srcPoint,putSize,srcPic,picSize,maskPic,ps256,r,g,b);
	if ((lpPalette == NULL) || (transFlag))
	{
		return;//dummy for warning lv4
	}
}



/*
void CSepiaBlt::SepiaBltTrans256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize, LPVOID lpPalette)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int picSizeX = picSize.cx;
	int picSizeY = picSize.cy;
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
		
		and edx,000ff00h
		movd mm0,edx
		movq mm1,mm0
		movq mm2,mm0
		psllq mm1,8
		psrlq mm2,8
		por mm0,mm1
		por mm0,mm2
		movd edx,mm0

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

		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}


void CGreyBlt::GreyBltBeta256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize, LPVOID lpPalette)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int picSizeX = picSize.cx;
	int picSizeY = picSize.cy;
	int dstPitch = screenSizeX * sizeof(int);
	int* dst = CMyGraphics::GetScreenBuffer();

	char* src = (char*)srcPic;
	char tr = *src;

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

		shl eax,2
		mov edx,[ebx+eax]
		
		and edx,000ff00h
		movd mm0,edx
		movq mm1,mm0
		movq mm2,mm0
		psllq mm1,8
		psrlq mm2,8
		por mm0,mm1
		por mm0,mm2
		movd edx,mm0

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

		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}


void CGreyBlt::GreyBltTrans(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	int picSizeX = picSize.cx;
	int picSizeY = picSize.cy;
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

		and eax,000ff00h
		movd mm0,eax
		movq mm1,mm0
		movq mm2,mm0
		psllq mm1,8
		psrlq mm2,8
		por mm0,mm1
		por mm0,mm2
		movd eax,mm0

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

		emms
		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}
*/

void CSepiaBlt::SepiaBltBeta(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,int ps256,int r,int g,int b)
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

//	maskPic += srcPoint.x;
//	maskPic += srcPoint.y * picSizeX;

	int srcPitch = picSizeX * 4;
//	int maskPitch = picSizeX;
	int loopY = putSize.cy;
	int loopX = putSize.cx;

	int ps256work = ps256;
	int nega256work = 256-ps256;

	int col = (r << 16) | (g<<8) | b;

#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

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

		mov eax,76*65536 + 150*256 + 29
		movd mm7,eax
		punpcklbw mm7,mm0

		mov eax,ps256work
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5

		mov eax,nega256work
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6


		mov eax,col
		movd mm4,eax
		punpcklbw mm4,mm0

		mov esi,src
		mov edi,dst
//		mov ebx,maskPic

		mov ecx,loopY
LOOP_B_1:
		push ecx
		push ebx
		push esi
		push edi

		mov ecx,loopX
LOOP_B_2:
//		xor eax,eax
//		mov al,[ebx]
//		or al,al
//		jz SKIP_M


		mov edx,[esi]
		movd mm1,edx
		punpcklbw mm1,mm0
		movq mm2,mm1

		pmaddwd mm1,mm7

		psrld mm1,8
		packssdw mm1,mm1

		movq mm3,mm1
		psrld mm3,16
		paddw mm1,mm3
		punpcklwd mm1,mm1
		punpckldq mm1,mm1

		pmullw mm1,mm4
		psrlw mm1,8

		//ps
		pmullw mm1,mm5
		pmullw mm2,mm6
		paddw mm1,mm2


//NORMAL_M:
		psrlw mm1,8
		packuswb mm1,mm0
		movd edx,mm1
		mov [edi],edx

//SKIP_M:
		add esi,4
		add edi,4
		inc ebx
		dec ecx
		jnz LOOP_B_2

		pop edi
		pop esi
		pop ebx
		pop ecx
			
		add edi,dstPitch
		add esi,srcPitch
//		add ebx,maskPitch

		dec ecx
		jnz LOOP_B_1

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


void CSepiaBlt::MaskSepiaBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic,int ps256,int r,int g,int b)
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

	int ps256work = ps256;
	int nega256work = 256-ps256;

	int col = (r << 16) | (g<<8) | b;

#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

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

		mov eax,76*65536 + 150*256 + 29
		movd mm7,eax
		punpcklbw mm7,mm0

		mov eax,ps256work
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5

		mov eax,nega256work
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6

		mov eax,col
		movd mm4,eax
		punpcklbw mm4,mm0

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
		xor eax,eax
		mov al,[ebx]
		or al,al
		jz SKIP_M


		mov edx,[esi]
		movd mm1,edx
		punpcklbw mm1,mm0
		movq mm2,mm1

		pmaddwd mm1,mm7

		psrld mm1,8
		packssdw mm1,mm1

		movq mm3,mm1
		psrld mm3,16
		paddw mm1,mm3
		punpcklwd mm1,mm1
		punpckldq mm1,mm1

		pmullw mm1,mm4
		psrlw mm1,8

		//ps
		pmullw mm1,mm5
		pmullw mm2,mm6
		paddw mm1,mm2

		cmp al,255
		jz NORMAL_M

		mov edx,[edi]
		movd mm2,edx
		punpcklbw mm2,mm0

		mov edx,eax
		inc eax
		not dl
		movd mm3,eax



		psrlw mm1,8

		punpcklwd mm3,mm3
		punpckldq mm3,mm3
		pmullw mm1,mm3


		movd mm3,edx
		punpcklwd mm3,mm3
		punpckldq mm3,mm3

		pmullw mm2,mm3

		paddw mm1,mm2

NORMAL_M:
		psrlw mm1,8
		packuswb mm1,mm0
		movd edx,mm1
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
#endif

}



/*_*/




