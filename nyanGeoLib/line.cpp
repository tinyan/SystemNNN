//
//
//

#include <windows.h>
//#include <stdio.h>
//#include <Math.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "line.h"


CLine::CLine()
{
}


CLine::~CLine()
{
	End();
}

void CLine::End(void)
{
}

void CLine::Print(POINT startPoint,POINT endPoint,int r,int g,int b)
{
	Print(startPoint.x,startPoint.y,endPoint.x,endPoint.y,r,g,b);
}

void CLine::Print(int startX,int startY,int endX,int endY,int r,int g,int b)
{
	//clip

	//dmyRoutine;

	int sizeX = startX - endX;
	if (sizeX<0) sizeX *= -1;
	int sizeY = startY - endY;
	if (sizeY<0) sizeY *= -1;
	sizeX++;
	sizeY++;

	int size = sizeX;
	if (size<sizeY) size = sizeY;


	int dx = endX - startX;
	int dy = endY - startY;

	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int dv = size - 1;
	if (dv<1) dv = 1;
	int dv2 = dv / 2;

	int col = (r<<16) | (g<<8) | b;

	for (int i=0;i<size;i++)
	{
		int x = startX + (dx*i+dv2)/dv;
		int y = startY + (dy*i+dv2)/dv;

		if ((x>=0) && (x<screenSizeX) && (y>=0) && (y<screenSizeY))
		{
			*(dst + x + y*screenSizeX) = col;
		}
	}
}



void CLine::TransPrint(POINT startPoint,POINT endPoint,int r,int g,int b,int ps)
{
	TransPrint(startPoint.x,startPoint.y,endPoint.x,endPoint.y,r,g,b,ps);
}

void CLine::TransPrint(int startX,int startY,int endX,int endY,int r,int g,int b,int ps)
{
	//clip

	//dmyRoutine;

	int sizeX = startX - endX;
	if (sizeX<0) sizeX *= -1;
	int sizeY = startY - endY;
	if (sizeY<0) sizeY *= -1;
	sizeX++;
	sizeY++;

	int size = sizeX;
	if (size<sizeY) size = sizeY;


	int dx = endX - startX;
	int dy = endY - startY;

	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int dv = size - 1;
	if (dv<1) dv = 1;
	int dv2 = dv / 2;

//@@	int col = (r<<16) | (g<<8) | b;

	int ps1 = (ps * 255) / 100;
	int ps0 = 255 - ps1;

	int r1 = ps1 * r;
	int g1 = ps1 * g;
	int b1 = ps1 * b;

	for (int i=0;i<size;i++)
	{
		int x = startX + (dx*i+dv2)/dv;
		int y = startY + (dy*i+dv2)/dv;

		if ((x>=0) && (x<screenSizeX) && (y>=0) && (y<screenSizeY))
		{
			int col0 = *(dst + x + y*screenSizeX);

			int r0 = (col0 >> 16) & 0xff;
			int g0 = (col0 >> 8 ) & 0xff;
			int b0 =  col0        & 0xff;

			int rr = (r0 * ps0 + r1) >> 8;
			int gg = (g0 * ps0 + g1) >> 8;
			int bb = (b0 * ps0 + b1) >> 8;


			int col1 = (rr << 16) | (gg << 8) | bb;


			*(dst + x + y*screenSizeX) = col1;
		}
	}
}

void CLine::PrintF(float startX,float startY,float endX,float endY,int r,int g,int b,int ps)
{
	//clip

	//dmyRoutine;

	float sizeX = startX - endX;
	if (sizeX<0) sizeX *= -1.0f;
	float sizeY = startY - endY;
	if (sizeY<0) sizeY *= -1.0f;


	float dvml = sizeX;
	if (dvml < sizeY) dvml = sizeY;
	if (dvml < 1.0f) dvml = 1.0f;

	sizeX += 1.0f;
	sizeY += 1.0f;

	int size = (int)sizeX;
	int size2 = (int)sizeY;

	if (size<size2) size = size2;


	float dx = endX - startX;
	float dy = endY - startY;

	int* dst = CMyGraphics::GetScreenBuffer();
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	int dv0 = size - 1;
	if (dv0<1) dv0 = 1;


//	float dvml = sizeX;
//	if (dvml < sizeY) dvml = sizeY;

	//float dvml = (float)dv0;
	dvml = 1.0f / dvml;

//	float dv2 = dv / 2;

//@@	int col = (r<<16) | (g<<8) | b;

	int ps1 = (ps * 255) / 100;
	int ps0 = 255 - ps1;

	int r1 = ps1 * r;
	int g1 = ps1 * g;
	int b1 = ps1 * b;

	for (int i=0;i<size;i++)
	{
		float ml = (float)i;
		ml *= dvml;

		int x = (int)(startX + dx*ml + 0.5f);
		int y = (int)(startY + dy*ml + 0.5f);

		if ((x>=0) && (x<screenSizeX) && (y>=0) && (y<screenSizeY))
		{
			int col0 = *(dst + x + y*screenSizeX);

			int r0 = (col0 >> 16) & 0xff;
			int g0 = (col0 >> 8 ) & 0xff;
			int b0 =  col0        & 0xff;

			int rr = (r0 * ps0 + r1) >> 8;
			int gg = (g0 * ps0 + g1) >> 8;
			int bb = (b0 * ps0 + b1) >> 8;


			int col1 = (rr << 16) | (gg << 8) | bb;


			*(dst + x + y*screenSizeX) = col1;
		}
	}
}

/*_*/


