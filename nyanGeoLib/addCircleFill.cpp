//
// addirclefill.cpp
//

#include <windows.h>
#include <stdio.h>
#include <Math.h>

#include "..\nyanlib\include\commonmacro.h"
#include "..\nyanlib\include\myGraphics.h"

#include "addcirclefill.h"


CAddCircleFill::CAddCircleFill()
{
//	int screenSizeY = CMyGraphics::GetScreenSizeY();
	m_table = CMyGraphics::GetCommonX8Buffer();
}

CAddCircleFill::~CAddCircleFill()
{
	End();
}

void CAddCircleFill::End(void)
{
}


void CAddCircleFill::Print(int x, int y, int rx, int ry, int dr, int dg, int db,int ps)
{
	if ((rx<1) || (ry<1)) return;

	int* table = m_table;	//size start

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* dst = CMyGraphics::GetScreenBuffer();
	int lPitch = screenSizeX * sizeof(int);


	int addR = (dr*ps)/100;
	int subR = (dr*ps)/100;
	int addG = (dg*ps)/100;
	int subG = (dg*ps)/100;
	int addB = (db*ps)/100;
	int subB = (db*ps)/100;

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

		movd mm7,addLight
		movd mm6,subLight

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
		movd mm0,eax

		paddusb mm0,mm7
		psubusb mm0,mm6
		movd eax,mm0

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


