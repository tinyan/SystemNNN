#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "changeTransLucentBlt.h"


CChangeTransLucentBlt::CChangeTransLucentBlt()
{
}

CChangeTransLucentBlt::~CChangeTransLucentBlt()
{
	End();
}

void CChangeTransLucentBlt::End(void)
{
}



//void CChangeTransLucentBlt::Print(POINT dstPoint,POINT srcPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID maskData1,LPVOID maskData2,SIZE picSize,int ps1,int ps2)
void CChangeTransLucentBlt::Print(POINT dstPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID maskData1,LPVOID maskData2,SIZE picSize,SIZE picSize2,int ps1,int ps2)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();


	ps1 *= 256;
	ps1 += 50;
	ps1 /= 100;

	if (ps1>256) ps1 = 256;

//	ps2 = 256 - ps1;

	ps2 *= 256;
	ps2 += 50;
	ps2 /= 100;

	if (ps2>256) ps2 = 256;

	int loopX = putSize.cx;
	int loopY = putSize.cy;

//	int* screen=(int*)m_lpScreenBuffer;
	int* screen = CMyGraphics::GetScreenBuffer();
	int* src1 = (int*)picData1;
	int* src2 = (int*)picData2;


	char* maskPtr1 = (char*)maskData1;
	char* maskPtr2 = (char*)maskData2;

//	int srcX = srcPoint.x;
//	int srcY = srcPoint.y;

//	maskPtr1 += srcX;
//	maskPtr1 += srcY * picSize.cx;

//	maskPtr2 += srcX;
//	maskPtr2 += srcY * picSize.cx;

	screen += dstPoint.x;
	screen += dstPoint.y * screenSizeX;

//	src1 += srcX;
//	src1 += srcY * picSize.cx;

//	src2 += srcX;
//	src2 += srcY * picSize.cx;

	int maskPitch = picSize.cx;
	int srcPitch = picSize.cx * sizeof(int);

	int maskPitch2 = picSize2.cx;
	int srcPitch2 = picSize2.cx * sizeof(int);

	int percent1 = ps1;
	int percent2 = ps2;

	int dstPitch = screenSizeX * 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi


		mov eax,percent1
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6
		psllw mm6,6

		mov eax,percent2
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7
		psllw mm7,6

		mov edi,screen
		mov ebx,src1
		mov esi,src2
		
		mov eax,maskPtr1
		mov edx,maskPtr2

		pxor mm0,mm0
		
		mov ecx,loopY
LOOP1:
		push ecx

		push eax
		push edx

		push ebx
		push esi

		push edi



		mov ecx,loopX
LOOP2:
		push ecx

		pxor mm1,mm1	//total trans
		pxor mm3,mm3	//maked pic

		//src
		mov cl,[eax]
		or cl,cl
		jz SKIP1

		movq mm4,mm6

		cmp cl,255
		jz NORMAL1

		//keisan

		movd mm2,ecx
		punpcklbw mm2,mm0
		punpcklwd mm2,mm2
		punpckldq mm2,mm2
		psrlw mm4,6
		pmullw mm4,mm2
		psrlw mm4,2
NORMAL1:
		paddw mm1,mm4

		mov ecx,[ebx]
		movd mm2,ecx
		punpcklbw mm2,mm0
		psllw mm2,2
		pmulhw mm2,mm4
		paddw mm3,mm2
		mov cl,[edx]
		jmp PART2
SKIP1:
		mov cl,[edx]
		or cl,cl
		jz NEXT
PART2:
		movq mm5,mm7

		cmp cl,255
		jz NORMAL2


		//keisan

		movd mm2,ecx
		punpcklbw mm2,mm0
		punpcklwd mm2,mm2
		punpckldq mm2,mm2
		psrlw mm5,6
		pmullw mm5,mm2
		psrlw mm5,2
NORMAL2:
		paddw mm1,mm5

		mov ecx,[esi]
		movd mm2,ecx
		punpcklbw mm2,mm0
		psllw mm2,2
		pmulhw mm2,mm5
		paddw mm3,mm2

		movd ecx,mm1
		cmp ecx,40004000h
		jz NOTTRANS

		mov ecx,40004000h
		movd mm2,ecx
		punpckldq mm2,mm2
		psubw mm2,mm1

		mov ecx,[edi]
		movd mm1,ecx
		punpcklbw mm1,mm0
		psllw mm1,2
		pmulhw mm1,mm2
		paddw mm3,mm1

NOTTRANS:
		packuswb mm3,mm3
		movd ecx,mm3
		mov [edi],ecx

NEXT:
		pop ecx
		
		inc eax
		inc edx
		add ebx,4
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		
		pop esi
		pop ebx
		
		pop edx
		pop eax

		pop ecx

		add edi,dstPitch
		add esi,srcPitch2
		add ebx,srcPitch
		add edx,maskPitch2
		add eax,maskPitch
		
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
}


void CChangeTransLucentBlt::PrintBeta(POINT dstPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,SIZE picSize,SIZE picSize2,int ps1,int ps2)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();


//	char mes[256];
//	sprintf_s(mes,256,"[%d %d] ",ps1,ps2);
//	OutputDebugString(mes);

	ps1 *= 256;
	ps1 += 50;
	ps1 /= 100;

	if (ps1>256) ps1 = 256;

//	ps2 = 256 - ps1;

	ps2 *= 256;
	ps2 += 50;
	ps2 /= 100;

	if (ps2>256) ps2 = 256;

	int loopX = putSize.cx;
	int loopY = putSize.cy;

//	int* screen=(int*)m_lpScreenBuffer;
	int* screen = CMyGraphics::GetScreenBuffer();
	int* src1 = (int*)picData1;
	int* src2 = (int*)picData2;


//	char* maskPtr1 = (char*)maskData1;
//	char* maskPtr2 = (char*)maskData2;

//	int srcX = srcPoint.x;
//	int srcY = srcPoint.y;

//	maskPtr1 += srcX;
//	maskPtr1 += srcY * picSize.cx;

//	maskPtr2 += srcX;
//	maskPtr2 += srcY * picSize.cx;

	screen += dstPoint.x;
	screen += dstPoint.y * screenSizeX;

//	src1 += srcX;
//	src1 += srcY * picSize.cx;

//	src2 += srcX;
//	src2 += srcY * picSize.cx;

	//int maskPitch = picSize.cx;
	int srcPitch = picSize.cx * sizeof(int);

//	int maskPitch2 = picSize2.cx;
	int srcPitch2 = picSize2.cx * sizeof(int);

	int percent1 = ps1;
	int percent2 = ps2;

	int dstPitch = screenSizeX * 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi


		mov eax,percent1
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6
		psllw mm6,6

		mov eax,percent2
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7
		psllw mm7,6

		mov edi,screen
		mov ebx,src1
		mov esi,src2
		
//		mov eax,maskPtr1
//		mov edx,maskPtr2

		pxor mm0,mm0
		
		mov ecx,loopY
LOOP1:
		push ecx

		push eax
		push edx

		push ebx
		push esi

		push edi

		mov ecx,loopX
LOOP2:
		push ecx

		mov ecx,[ebx]
		movd mm3,ecx
		punpcklbw mm3,mm0
		psllw mm3,2
		pmulhw mm3,mm6

		mov ecx,[esi]
		movd mm2,ecx
		punpcklbw mm2,mm0
		psllw mm2,2
		pmulhw mm2,mm7

		paddw mm3,mm2

		packuswb mm3,mm3
		movd ecx,mm3
		mov [edi],ecx

//NEXT:
		pop ecx
		
//		inc eax
//		inc edx
		add ebx,4
		add esi,4
		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		
		pop esi
		pop ebx
		
		pop edx
		pop eax

		pop ecx

		add edi,dstPitch
		add esi,srcPitch2
		add ebx,srcPitch
//		add edx,maskPitch2
//		add eax,maskPitch
		
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
}

void CChangeTransLucentBlt::PrintBeta256(POINT dstPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID paletteData1,LPVOID paletteData2,SIZE picSize,SIZE picSize2,int ps1,int ps2)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();


//	char mes[256];
//	sprintf_s(mes,256,"[%d %d] ",ps1,ps2);
//	OutputDebugString(mes);

	ps1 *= 256;
	ps1 += 50;
	ps1 /= 100;

	if (ps1>256) ps1 = 256;

//	ps2 = 256 - ps1;

	ps2 *= 256;
	ps2 += 50;
	ps2 /= 100;

	if (ps2>256) ps2 = 256;

	int loopX = putSize.cx;
	int loopY = putSize.cy;

//	int* screen=(int*)m_lpScreenBuffer;
	int* screen = CMyGraphics::GetScreenBuffer();
	char* src1 = (char*)picData1;
	char* src2 = (char*)picData2;
	int* palette1 = (int*)paletteData1;
	int* palette2 = (int*)paletteData2;


//	char* maskPtr1 = (char*)maskData1;
//	char* maskPtr2 = (char*)maskData2;

//	int srcX = srcPoint.x;
//	int srcY = srcPoint.y;

//	maskPtr1 += srcX;
//	maskPtr1 += srcY * picSize.cx;

//	maskPtr2 += srcX;
//	maskPtr2 += srcY * picSize.cx;

	screen += dstPoint.x;
	screen += dstPoint.y * screenSizeX;

//	src1 += srcX;
//	src1 += srcY * picSize.cx;

//	src2 += srcX;
//	src2 += srcY * picSize.cx;

	//int maskPitch = picSize.cx;
	int srcPitch = picSize.cx * sizeof(char);

//	int maskPitch2 = picSize2.cx;
	int srcPitch2 = picSize2.cx * sizeof(char);

	int percent1 = ps1;
	int percent2 = ps2;

	int dstPitch = screenSizeX * 4;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi


		mov eax,percent1
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6
		psllw mm6,6

		mov eax,percent2
		movd mm7,eax
		punpcklwd mm7,mm7
		punpckldq mm7,mm7
		psllw mm7,6

		mov edi,screen
		mov ebx,src1
		mov esi,src2
		
//		mov eax,maskPtr1
//		mov edx,maskPtr2

		pxor mm0,mm0
		

		mov eax,palette1
		mov edx,palette2



		mov ecx,loopY
LOOP1:
		push ecx

		push eax
		push edx

		push ebx
		push esi

		push edi

		mov ecx,loopX
LOOP2:
		push ecx

		push edx
		xor ecx,ecx
		mov cl,[ebx]
		add ecx,ecx
		add ecx,ecx
		mov edx,[eax+ecx]
		movd mm3,edx
		pop edx

		push eax
		xor ecx,ecx
		mov cl,[esi]
		add ecx,ecx
		add ecx,ecx
		mov eax,[edx+ecx]
		movd mm2,eax
		pop eax

		punpcklbw mm3,mm0
		punpcklbw mm2,mm0

		psllw mm3,2
		psllw mm2,2

		pmulhw mm3,mm6
		pmulhw mm2,mm7

		paddw mm3,mm2

		packuswb mm3,mm3
		movd ecx,mm3
		mov [edi],ecx

//NEXT:
		pop ecx
		
//		inc eax//palette‚ä‚¦
//		inc edx

		//add ebx,4
		//add esi,4
		inc ebx
		inc esi

		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		
		pop esi
		pop ebx
		
		pop edx
		pop eax

		pop ecx

		add edi,dstPitch
		add esi,srcPitch2
		add ebx,srcPitch
//		add edx,maskPitch2
//		add eax,maskPitch
		
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
}
