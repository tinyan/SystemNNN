//
//
//

#include <windows.h>
#include <stdio.h>
//#include <Math.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "boxFill.h"


CBoxFill::CBoxFill()
{
}


CBoxFill::~CBoxFill()
{
	End();
}

void CBoxFill::End(void)
{
}


void CBoxFill::Print(int x,int y,int sizeX,int sizeY,int r,int g,int b)
{
//static int aaa = 0;
//aaa++;
//if (aaa == 5)
//{
//	MessageBox(NULL,"boxfill start","a",MB_OK);
//}

//clip
	if (CMyGraphics::Clip(&x,&y,&sizeX,&sizeY) == FALSE) return;

	//print
	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();


//if (aaa == 5)
//{
//	char mes[256];
//	sprintf_s(mes,256,"x=%d y=%d buf=%d",sizeX,sizeY,(int)dst);
//	MessageBox(NULL,mes,"b",MB_OK);
//
//}

	dst += x;
	dst += y*screenSizeX;

	int loopX = sizeX;
	int loopY = sizeY;

	int col = (r<<16) | (g<<8) | b;
	int lPitch = screenSizeX * sizeof(int);


	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld
		mov edi,dst
		mov edx,loopY
		mov eax,col
LOOP1:
		push edi
		mov ecx,loopX
		rep stosd
		pop edi
		add edi,lPitch
		dec edx
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


