#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "bltBeta.h"



CBltBeta::CBltBeta()
{
}

CBltBeta::~CBltBeta()
{
	End();
}

void CBltBeta::End(void)
{
}

void CBltBeta::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize)
{
	int* src = (int*)picData;
	int* dst = CMyGraphics::GetScreenBuffer();


	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();

	src += (SSIZE_T)srcPoint.y * srcSize.cx + srcPoint.x;
	dst += (SSIZE_T)putPoint.y * screenSizeX + putPoint.x;

	int srcPitch = srcSize.cx * sizeof(int);
	int dstPitch = screenSizeX * 4;

	int loopY = putSize.cy;
	int loopX = putSize.cx;

	if ((loopY<=0) || (loopX<=0)) return;

#if defined _WIN64
#pragma message("*** ŽÀ‘•‚µ‚½‚É‚á ‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)
	int* esi = src;
	int* edi = dst;
	for (int j = 0; j < loopY; j++)
	{
		int* pushesi = esi;
		int* pushedi = edi;

		memcpy(edi, esi, loopX * sizeof(int));

		esi = pushesi;
		edi = pushedi;
		esi += srcPitch / 4;
		edi += dstPitch / 4;
	}
#else


	if ((srcPoint.x == 0) && (putSize.cx == screenSizeX) && (putPoint.x==0))
	{
		int loopX2 = loopX / 8;


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

			cld
LOOP1:
			push esi
			push edi
			// pre fetch read wnd write buffer to L1 L2 Cache
				

			mov ecx,loopX2
LOOPPRF1:
			mov eax,[esi]
			mov ebx,[edi]
			add esi,32
			add edi,32
			dec ecx
			jnz LOOPPRF1

			pop edi
			pop esi
			push esi
			push edi



			mov ecx,loopX2
LOOP2:
			movq mm0,[esi]
			movq mm1,[esi+8]
			movq mm2,[esi+16]
			movq mm3,[esi+24]
			movq [edi],mm0
			movq [edi+8],mm1
			movq [edi+16],mm2
			movq [edi+24],mm3
			add esi,32
			add edi,32
			dec ecx
			jnz LOOP2

			pop edi
			pop esi
			add esi,srcPitch
			add edi,dstPitch
			dec edx
			jnz LOOP1

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
			emms
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

			mov esi,src
			mov edi,dst
			mov edx,loopY

			cld
LOOP_N1:
			push esi
			push edi

			mov ecx,loopX
			rep movsd

			pop edi
			pop esi
			add esi,srcPitch
			add edi,dstPitch
			dec edx
			jnz LOOP_N1

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}

	}
#endif
}
