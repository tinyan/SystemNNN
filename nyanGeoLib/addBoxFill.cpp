//
// addBoxFill
//

#include <windows.h>
//#include <stdio.h>
//#include <Math.h>


#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "addBoxFill.h"


CAddBoxFill::CAddBoxFill()
{
}


CAddBoxFill::~CAddBoxFill()
{
	End();
}

void CAddBoxFill::End(void)
{
}






void CAddBoxFill::Print(int x, int y, int sizeX, int sizeY, int r, int g, int b,int ps)
{
	//clip
	if (CMyGraphics::Clip(&x,&y,&sizeX,&sizeY) == FALSE) return;

	//print
//	int* dst = (int*)CPicture::m_lpScreenBuffer;
	int* dst = CMyGraphics::GetScreenBuffer();
//	int screenSizeX = CPicture::m_screenSizeX;
	int screenSizeX = CMyGraphics::GetScreenSizeX();

	dst += x;
#if defined _WIN64
	dst += (long long)y*(long long)screenSizeX;
#else
	dst += y * screenSizeX;
#endif
	int loopX = sizeX;
	int loopY = sizeY;

	int addR = (r*ps)/100;
	int subR = (r*ps)/100;
	int addG = (g*ps)/100;
	int subG = (g*ps)/100;
	int addB = (b*ps)/100;
	int subB = (b*ps)/100;


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



	int lPitch = screenSizeX * sizeof(int);

#if defined _WIN64
#pragma message("***ŽÀ‘•‚µ‚½‚É‚á ‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)
	int* edi = dst;
	for (int j = 0; j < loopY;j++)
	{
		int* pushedi = edi;
		for (int i = 0; i < loopX;i++)
		{
			int d = *edi;
			int srcR = (d << 16) & 0xff;
			int srcG = (d << 8) & 0xff;
			int srcB = (d) & 0xff;

			int rr = srcR + addR - subR;
			int gg = srcG + addG - subG;
			int bb = srcB + addB - subB;

			if (rr < 0) rr = 0;
			if (rr >255) rr = 255;
			if (gg < 0) gg = 0;
			if (gg > 255) gg = 255;
			if (bb < 0) bb = 0;
			if (bb > 255) bb = 255;

			int c = (rr << 16) | (gg << 8) | bb;
			*dst = c;
			dst++;
		}


		edi = pushedi;
		edi += lPitch / 4;
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

		pxor mm0,mm0

		movd mm7,addLight
		movd mm6,subLight

		mov edi,dst
		mov edx,loopY
LOOP1:
		push edi
		mov ecx,loopX
LOOP2:
		mov eax,[edi]
		movd mm1,eax

		paddusb mm1,mm7
		psubusb mm1,mm6
		movd eax,mm1

		mov [edi],eax

		add edi,4

		dec ecx
		jnz LOOP2

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

		emms
	}
#endif

}
