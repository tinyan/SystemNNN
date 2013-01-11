//
//
//

#include <windows.h>
//#include <stdio.h>
//#include <Math.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "fillScreen.h"


CFillScreen::CFillScreen()
{
}


CFillScreen::~CFillScreen()
{
	End();
}

void CFillScreen::End(void)
{
}

void CFillScreen::Print(int r, int g, int b)
{
	if (g == -1) g = r;
	if (b == -1) b = g;

	//print
	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int rgb = (r<<16) | (g<<8) | b;


	int sz = screenSizeX * screenSizeY;

	__asm
	{
		push eax
		push ecx
		push edi

		mov edi,dst
		mov ecx,sz
		mov eax,rgb
		cld
		rep stosd

		pop edi
		pop ecx
		pop eax
	}

}


/*_*/

