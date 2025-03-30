#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "blt.h"



CBlt::CBlt()
{
}

CBlt::~CBlt()
{
	End();
}

void CBlt::End(void)
{
}

void CBlt::Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize)
{
	int* src = (int*)picData;
	int tr = *src;
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

	INT32* esi = src;
	INT32* edi = dst;
	INT32 ebx = (INT32)tr;

	for (int j = 0; j < loopY; j++)
	{
		INT32* esipush = esi;
		INT32* edipush = edi;
		for (int i = 0; i < loopX; i++)
		{
			INT32 eax = *esi;
			if (eax != ebx)
			{
				*edi = eax;
			}
			esi++;
			edi++;
		}
		esi = esipush;
		edi = edipush;
		esi += srcPitch / 4;
		edi += dstPitch / 4;

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


		mov ebx,tr
		mov edx,loopY
LOOP1:
		push esi
		push edi
		mov ecx,loopX
LOOP2:
		mov eax,[esi]
		cmp eax,ebx
		jz SKIP1
		mov [edi],eax
SKIP1:
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

