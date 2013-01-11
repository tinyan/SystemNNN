//
// nyanGeoLib.cpp
//



#include <windows.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "daikei.h"

CDaikei::CDaikei()
{
//	int screenSizeY = CMyGraphics::GetScreenSizeY();
	m_work = CMyGraphics::GetCommonX8Buffer();
}

CDaikei::~CDaikei()
{
	End();
}

void CDaikei::End(void)
{
}

void CDaikei::Print(POINT leftUpperPoint, int sizeUpperX, POINT leftBottomPoint, int sizeBottomX, int r, int g, int b)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int* dxtable = m_work;

	int x1 = leftUpperPoint.x;
	int y1 = leftUpperPoint.y;

	int x2 = leftBottomPoint.x;
	int y2 = leftBottomPoint.y;

	int x3 = x1 + sizeUpperX;
	int x4 = x2 + sizeBottomX;

	if (sizeUpperX<0) return;
	if (sizeBottomX<0) return;

	if (y2<y1) return;

	int startY = y1;
	int endY = y2;

	if (startY>=screenSizeY) return;
	if (endY<0) return;


	if (startY<0) startY = 0;
	if (endY>=screenSizeY)endY = screenSizeY-1;

	int loopY = endY - startY + 1;
	if (loopY<=0) return;

	int* dst = CMyGraphics::GetScreenBuffer();
	dst += screenSizeX * startY;

	int col = (r<<16) | (g<<8) | b;

	int dstPitch = screenSizeY * sizeof(int);

	int dy = startY - y1;

	int dx1 = x2 - x1;
	int dx3 = x4 - x3;

	for (int j=0;j<loopY;j++)
	{
		int k= dy + j;
		dxtable[j*2] = 0;

		int xLeft = x1 + (dx1*k) / loopY;
		int xRight = x3 + (dx3*k) / loopY;

		if ((xLeft < screenSizeX) && (xRight>=0))
		{
			if (xLeft<0) xLeft = 0;
			if (xRight>=screenSizeX) xRight = screenSizeX-1;
			int sx = xRight - xLeft + 1;
			if (sx>0)
			{
				dxtable[j*2] = sx;
				dxtable[j*2+1] = xLeft;
			}
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

		cld
		mov eax,col
		mov edi,dst

		mov ebx,dxtable
		mov ecx,loopY
LOOP1:
		push ebx
		push ecx
		push edi

		mov ecx,[ebx]
		or ecx,ecx
		jz SKIP1
		mov edx,[ebx+4]
		add edx,edx
		add edx,edx
		add edi,edx
		rep stosd
SKIP1:
		pop edi
		pop ecx
		pop ebx
		add ebx,4*2
		add edi,dstPitch
		dec ecx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
}


/*_*/

