//
// genshoku16.cpp
//


#include <windows.h>

#include "..\nyanlib\include\picture.h"
#include "..\nyanlib\include\myGraphics.h"

#include "genshoku16.h"


CGenshoku16::CGenshoku16()
{
}

CGenshoku16::~CGenshoku16()
{
	End();
}

void CGenshoku16::End(void)
{
}


BOOL CGenshoku16::GenshokuMain(CPicture* lpPic)
{
	int* lpBuffer = (int*)lpPic->GetBuffer();
	if (lpBuffer == NULL) return FALSE;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (lpPic->Check256()) return FALSE;

	int deltaPat[4][8] = 
	{
		{0,5,6,3,7,2,1,4},
		{7,2,1,4,0,5,6,3},
		{1,4,7,2,6,3,0,5},
		{6,3,0,5,1,4,7,2},
//		{0,7,1,6,5,2,4,3},
//		{5,2,4,3,0,7,1,6},
//		{6,0,7,1,3,5,2,4},
//		{3,5,2,4,6,0,7,1},
	};

	int tr = *lpBuffer;


	//???
	for (int y=0;y<screenSizeY;y+=4)
	{
		for (int x=0;x<screenSizeX;x+=8)
		{
			for (int j=0;j<4;j++)
			{
				for (int i=0;i<8;i++)
				{
					int* ptr = lpBuffer;
					ptr += (i+x) + (j+y) * screenSizeX;

					int c = *ptr;

					if (c != tr)
					{
						int r = (c >> 16) & 0xff;
						int g = (c >> 8) & 0xff;
						int b = c & 0xff;


						r += deltaPat[j][i];
						g -= deltaPat[j][i];
						b += deltaPat[j][i];

						if (r>255) r = 255;
						if (g<0) g = 0;
						if (b>255) b = 255;

						r &= 0xf8;
						g &= 0xf8;
						b &= 0xf8;

						int c2 = (r<<16) | (g<<8) | b;
						if (c2 != tr)
						{
							*ptr = c2;
						}
					}
				}
			}
		}
	}


	return TRUE;
}