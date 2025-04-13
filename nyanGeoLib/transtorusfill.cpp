//
// transtorusfill.cpp
//

#include <windows.h>
#include <stdio.h>
#include <Math.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "transtorusfill.h"


CTransTorusFill::CTransTorusFill()
{
//	int screenSizeY = CMyGraphics::GetScreenSizeY();
	m_table = CMyGraphics::GetCommonX8Buffer();
}

CTransTorusFill::~CTransTorusFill()
{
	End();
}

void CTransTorusFill::End(void)
{
}


void CTransTorusFill::Print(int x, int y, int rx, int ry, int x2, int y2, int rx2, int ry2, int r, int g, int b,int ps)
{
	if ((rx<1) || (ry<1)) return;
	if ((rx2<1) || (ry2<1)) return;

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
#if defined _WIN64
		*(table+(long long)j*4) = 0;
		*(table+(long long)j*4+2) = 0;
#else
		* (table + j * 4) = 0;
		*(table + j * 4 + 2) = 0;
#endif
	}

	int yStart = y - ry;
	int yEnd = y + ry;

	if (yStart<0) yStart = 0;
	if (yEnd>=screenSizeY) yEnd = screenSizeY - 1;


	int yStart2 = y2 - ry2;
	int yEnd2 = y2 + ry2;

	if (yStart2<0) yStart2 = 0;
	if (yEnd2 >= screenSizeY) yEnd = screenSizeY - 1;


	for (int j=yStart;j<=yEnd;j++)
	{
		double yy = (double)((double)j - (double)y);
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
			if ((j<yStart2) || (j>yEnd2))
			{
#if defined _WIN64
				*(table+(long long)j*4) = sizeX;
				*(table+(long long)j*4+1) = xStart;
				*(table+(long long)j*4+2) = 0;
#else
				* (table + j * 4) = sizeX;
				*(table + j * 4 + 1) = xStart;
				*(table + j * 4 + 2) = 0;
#endif

			}
			else
			{
				double yy2 = (double)((double)j-(double)y2);
				yy2 /= ry2;
				yy2 = yy2*yy2;
				yy2 *= -1.0;
				yy2 += 1.0;
				if (yy2<0.0) yy2 = 0.0;
				int xx2 = (int)(sqrt(yy2) * rx2 + 0.5);

				int xStart2 = x2 - xx2 - 1;
				int xEnd2 = x2 + xx2 + 1;

				if (xStart2 >= screenSizeX) xStart2 = screenSizeX - 1;
				if (xEnd2<0) xEnd2 = 0;

				int sizeX2 = xStart2 - xStart + 1;
				
				int ptr = 0;

				if (sizeX2>0)
				{
#if defined _WIN64
					*(table+(long long)j*4) = sizeX2;
					*(table+(long long)j*4+1) = xStart;
#else
					* (table + j * 4) = sizeX2;
					*(table + j * 4 + 1) = xStart;
#endif

					ptr += 2;
				}

				int sizeX3 = xEnd - xEnd2 + 1;
				if (sizeX3>0)
				{
#if defined _WIN64
					*(table+(long long)j*4+ptr) = sizeX3;
					*(table+(long long)j*4+ptr+1) = xEnd2;
#else
					* (table + j * 4 + ptr) = sizeX3;
					*(table + j * 4 + ptr + 1) = xEnd2;
#endif
				}
			}
		}
	}


#if defined _WIN64

	int* edi = dst;
	int* ebx = table;

	int alpha = percent256;
	int oneMinusAlpha = percent256Neg;

	int addR = (r * alpha);
	int addG = (g * alpha);
	int addB = (b * alpha);

	for (int j = 0; j < screenSizeY; j++)
	{
		int* pushedi = edi;
		for (int k = 0; k < 2; k++)
		{
			edi = pushedi;

			int ecx = *ebx;
			if (ecx > 0)
			{
				edi += *(ebx + 1);
				for (int i = 0; i < ecx; i++)
				{

					int d = *edi;
					int srcR = (d << 16) & 0xff;
					int srcG = (d << 8) & 0xff;
					int srcB = (d) & 0xff;

					int rr = (srcR * oneMinusAlpha);
					int gg = (srcG * oneMinusAlpha);
					int bb = (srcB * oneMinusAlpha);

					rr += addR;
					gg += addG;
					bb += addB;

					rr >>= 8;
					gg >>= 8;
					bb >>= 8;

					int c = (rr << 16) | (gg < 8) | bb;
					*edi = c;

					edi++;
				}
			}


			ebx += 2;
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



		push edi

		mov ecx,[ebx+8]
		or ecx,ecx
		jz SKIP2
		mov eax,[ebx+12]
		add eax,eax
		add eax,eax
		add edi,eax
LOOP2B:
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
		jnz LOOP2B
SKIP2:
		pop edi

		pop ecx
		add edi,lPitch
		add ebx,4*4
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


