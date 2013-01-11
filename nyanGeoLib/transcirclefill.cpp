//
// transcirclefill.cpp
//

#include <windows.h>
#include <stdio.h>
#include <Math.h>

#include "..\nyanlib\include\commonmacro.h"
#include "..\nyanlib\include\myGraphics.h"

#include "transcirclefill.h"


CTransCircleFill::CTransCircleFill()
{
//	int screenSizeY = CMyGraphics::GetScreenSizeY();
	m_table = CMyGraphics::GetCommonX8Buffer();
}

CTransCircleFill::~CTransCircleFill()
{
	End();
}

void CTransCircleFill::End(void)
{
}


void CTransCircleFill::Print(int x, int y, int rx, int ry, int r, int g, int b,int ps)
{
	if ((rx<1) || (ry<1)) return;

	int* table = m_table;	//size start

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* dst = CMyGraphics::GetScreenBuffer();
	int lPitch = screenSizeX * sizeof(int);

	int col = (r<<16) | (g<<8) | b;
	int percent256 = (ps*256)/100;
	int percent256Neg = ((100-ps)*256)/100;



	for (int j=0;j<screenSizeY;j++)
	{
		*(table+j*2) = 0;
	}

	int yStart = y - ry;
	int yEnd = y + ry;

	if (yStart<0) yStart = 0;
	if (yEnd>=screenSizeY) yEnd = screenSizeY - 1;

	for (int j=yStart;j<=yEnd;j++)
	{
		double yy = (double)(j - y);
		yy /= ry;
		yy = yy*yy;
		yy *= -1.0;
		yy += 1.0;
		if (yy<0.0) yy = 0.0;
		int xx =  (int)(sqrt(yy) * rx + 0.5);

		int xStart = x - xx;
		int xEnd = x + xx;

		if (xStart<0) xStart = 0;
		if (xEnd>=screenSizeX) xEnd = screenSizeX - 1;

		int sizeX = xEnd - xStart + 1;
		
		if (sizeX>0)
		{
			*(table+j*2) = sizeX;
			*(table+j*2+1) = xStart;
		}
	}



__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		pxor mm0,mm0

		mov eax,col
		movd mm6,eax
		punpcklbw mm6,mm0
		mov eax,percent256
		movd mm1,eax
		punpcklwd mm1,mm1
		punpckldq mm1,mm1
		pmullw mm6,mm1

		mov eax,percent256Neg
		movd mm5,eax
		punpcklwd mm5,mm5
		punpckldq mm5,mm5

		mov ebx,table
		mov ecx,screenSizeY
		mov edi,dst
LOOP1:
		push ecx
		push edi

		mov ecx,[ebx]
		or ecx,ecx
		jz SKIP1
		mov eax,[ebx+4]
		add eax,eax
		add eax,eax
		add edi,eax
LOOP2:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0
		pmullw mm1,mm5
		paddw mm1,mm6
		psrlw mm1,8
		packuswb mm1,mm1
		movd eax,mm1

		mov [edi],eax

		add edi,4
		dec ecx
		jnz LOOP2
SKIP1:
		pop edi
		pop ecx
		add edi,lPitch
		add ebx,4*2
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
}


