//
// transGradationBoxV
//

#include <windows.h>
//#include <stdio.h>
//#include <Math.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "transGradationBoxV.h"


CTransGradationBoxV::CTransGradationBoxV()
{
	m_work = CMyGraphics::GetCommonX8Buffer();
}


CTransGradationBoxV::~CTransGradationBoxV()
{
	End();
}

void CTransGradationBoxV::End(void)
{
}


void CTransGradationBoxV::Print(POINT leftTop,POINT rightBottom,int r1, int g1, int b1, int r4, int g4, int b4)
{
	int x1 = leftTop.x;
	int y1 = leftTop.y;
	int x4 = rightBottom.x;
	int y4 = rightBottom.y;

	if (x1>x4)
	{
		int tmp = x1;
		x1 = x4;
		x4 = tmp;
	}

	if (y1>y4)
	{
		int tmp = y1;
		y1 = y4;
		y4 = tmp;

		tmp = r1;
		r1 = r4;
		r4 = tmp;
		tmp = g1;
		g1 = g4;
		g4 = tmp;
		tmp = b1;
		b1 = b4;
		b4 = tmp;
	}

	POINT leftTop2;
	leftTop2.x = x1;
	leftTop2.y = y1;
	SIZE size;
	size.cx = x4 - x1;
	size.cy = y4 - y1;

	Print(leftTop2,size,r1,g1,b1,r4,g4,b4);
}


void CTransGradationBoxV::Print(POINT leftTop,SIZE size,int r1, int g1, int b1, int r4, int g4, int b4)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (size.cx <= 0) return;
	if (size.cy <= 0) return;

	//x clip
	int x1 = leftTop.x;
	int x2 = x1 + size.cx;

	if (x1>=screenSizeX) return;
	if (x2<0) return;

	if (x1<0) x1 = 0;
	if (x2>screenSizeX) x2 = screenSizeX;

	int loopX = x2 - x1;
	if (loopX <= 0) return;


	//y clip
	int y1 = leftTop.y;
	int y2 = y1 + size.cy;

	if (y1>=screenSizeY) return;
	if (y2<0) return;

	if (y1<0) y1 = 0;
	if (y2>screenSizeY) y2 = screenSizeY;

	int loopY = y2 - y1;
	if (loopY <= 0) return;



	int* delta = m_work;
	int* dst = CMyGraphics::GetScreenBuffer();
	int dstPitch = screenSizeX * sizeof(int);
#if defined _WIN64
	dst += (long long)screenSizeX * (long long)y1;
#else
	dst += screenSizeX * y1;
#endif

	dst += x1;


	int dy = y1 - leftTop.y;


	int dr = r4 - r1;
	int dg = g4 - g1;
	int db = b4 - b1;

	int dv = size.cy;

	for (int i=0;i<loopY;i++)
	{
		int k = dy + i;

		int rr = r1 + ((dr * k) / dv);
		int gg = g1 + ((dg * k) / dv);
		int bb = b1 + ((db * k) / dv);

		rr += 256;
		gg += 256;
		bb += 256;

		delta[i*2] = (bb & 0xffff) | ((gg<<16) & 0xffff0000);
		delta[i*2+1] = (rr & 0xffff);
	}

#if defined _WIN64
#pragma message("***ŽÀ‘•‚µ‚½‚É‚á ‚±‚±‚Éc++ŽÀ‘•‚ª•K—v‚É‚á " __FILE__)

	int* edi = dst;
	int* ebx = delta;
	for (int j = 0; j < loopY; j++)
	{
		int* pushedi = edi;

		int addB = *(ebx) & 0xffff;
		int addG = (*(ebx)>>16) & 0xffff;
		int addR = *(ebx+1) & 0xffff;

		addB -= 256;
		addG -= 256;
		addR -= 256;


		for (int i = 0; i < loopX; i++)
		{
			int d = *edi;
			int rr = (d >> 16) & 0xff;
			int gg = (d >>  8) & 0xff;
			int bb = (d      ) & 0xff;

			rr += addR;
			gg += addG;
			bb += addB;
			if (rr < 0) rr = 0;
			if (rr > 255) rr = 255;
			if (gg < 0) gg = 0;
			if (gg > 255) gg = 255;
			if (bb < 0) bb = 0;
			if (bb > 255) bb = 255;

			int c = (rr << 16) | (gg << 8) | bb;
			*edi = c;

			edi++;
		}

		edi = pushedi;
		edi += dstPitch / 4;
		ebx += 2;
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

		mov edi,dst
		mov ebx,delta
		mov ecx,loopY
		pxor mm0,mm0

		mov eax,256
		movd mm6,eax
		punpcklwd mm6,mm6
		punpckldq mm6,mm6
LOOP1:
		push ecx
		push edi

		movq mm7,[ebx]
		mov ecx,loopX
LOOP2:
		mov eax,[edi]
		movd mm1,eax
		punpcklbw mm1,mm0
		paddw mm1,mm7
		psubusw mm1,mm6
		packuswb mm1,mm1
		movd eax,mm1
		mov [edi],eax
		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		pop ecx
		add edi,dstPitch
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

#endif

}





/*_*/

