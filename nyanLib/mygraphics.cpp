//
// mygraphics.cpp
//



#include <windows.h>
#include <stdio.h>
#include <Math.h>

#include "include\commonmacro.h"
#include "include\mygraphics.h"

#include "include\picture.h"
#include "include\allGraphics.h"
#include "include\allGeo.h"
#include "include\allPicture.h"


int* CMyGraphics::m_lpScreenBuffer = NULL;
int* CMyGraphics::m_commonX8Buffer = NULL;
SIZE CMyGraphics::m_screenSize = {800,600};


POINT CMyGraphics::m_screenClipStart = {0,0};
POINT CMyGraphics::m_screenClipEnd = {800,600};

HBITMAP CMyGraphics::m_dib = NULL;

CMyGraphics::CMyGraphics(int sizeX,int sizeY,int notUseDirectDraw)
{

	m_screenSize.cx = sizeX;
	m_screenSize.cy = sizeY;

	m_notUseDirectDraw = notUseDirectDraw;

	m_screenClipStart.x = 0;
	m_screenClipStart.y = 0;
	m_screenClipEnd.x = sizeX;
	m_screenClipEnd.y = sizeY;

	if (m_notUseDirectDraw == 0)
	{
		m_lpScreenBuffer = new int[sizeX*(sizeY+2)];
		m_dib = NULL;
	}
	else
	{
		BITMAPINFO bmi;
		ZeroMemory(&bmi,sizeof(bmi));
		bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth = sizeX;
		bmi.bmiHeader.biHeight = -(sizeY + 2);
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biBitCount = 32;
		bmi.bmiHeader.biCompression = BI_RGB;
		bmi.bmiHeader.biSizeImage = 0;
		bmi.bmiHeader.biXPelsPerMeter = 0;
		bmi.bmiHeader.biYPelsPerMeter = 0;
		bmi.bmiHeader.biClrUsed = 0;
		bmi.bmiHeader.biClrImportant = 0;

		m_dib = CreateDIBSection(NULL,&bmi,DIB_RGB_COLORS,(void**)&m_lpScreenBuffer,NULL,0);
	}



	ZeroMemory(m_lpScreenBuffer,sizeX*(sizeY+2));

	m_commonX8Buffer = new int[sizeY * 8];
	
	//‚»‚Ì‘¼‚à‰Šú‰»‚·‚é
	//
	// graphicsLib,geoLib,pictureLib,picture,effect,etc..

	CPicture::InitStaticData();

	m_allGraphics = new CAllGraphics();
	m_allGeo = new CAllGeo();

	m_allPicture = new CAllPicture();
}


CMyGraphics::~CMyGraphics()
{
	End();
}


void CMyGraphics::End(void)
{
	ENDDELETECLASS(m_allPicture);
	ENDDELETECLASS(m_allGeo);
	ENDDELETECLASS(m_allGraphics);

	CPicture::ReleaseStaticData();

	DELETEARRAY(m_commonX8Buffer);
	if (m_notUseDirectDraw == 0)
	{
		DELETEARRAY(m_lpScreenBuffer);
	}
	else
	{
		if (m_dib != NULL)
		{
			DeleteObject(m_dib);
			m_dib = NULL;
		}
	}
}

int* CMyGraphics::GetScreenBuffer(void)
{
	return m_lpScreenBuffer;
}

int* CMyGraphics::GetCommonX8Buffer(void)
{
	return m_commonX8Buffer;
}

SIZE CMyGraphics::GetScreenSize(void)
{
	return m_screenSize;
}

int CMyGraphics::GetScreenSizeX(void)
{
	return m_screenSize.cx;
}

int CMyGraphics::GetScreenSizeY(void)
{
	return m_screenSize.cy;
}

int CMyGraphics::GetScreenClipStartX(void)
{
	return m_screenClipStart.x;
}

int CMyGraphics::GetScreenClipStartY(void)
{
	return m_screenClipStart.y;
}

int CMyGraphics::GetScreenClipEndX(void)
{
	return m_screenClipEnd.x;
}

int CMyGraphics::GetScreenClipEndY(void)
{
	return m_screenClipEnd.y;
}

void CMyGraphics::SetScreenClip(POINT startPoint,POINT endPoint)
{
	int x1 = startPoint.x;
	int y1 = startPoint.y;
	int x2 = endPoint.x;
	int y2 = endPoint.y;

	if ((x1>m_screenSize.cx) || (x2<0) || (y1>m_screenSize.cy) || (y2<0)) return;

	if (x1<0) x1 = 0;
	if (y1<0) y1 = 0;
	if (x2>m_screenSize.cx) x2 = m_screenSize.cx;
	if (y2>m_screenSize.cy) y2 = m_screenSize.cy;

	if (x1>=x2) return;
	if (y1>=y2) return;

	m_screenClipStart.x = x1;
	m_screenClipStart.y = y1;
	m_screenClipEnd.x = x2;
	m_screenClipEnd.y = y2;
}


/*
BOOL CMyGraphics::InitStaticData(int sizeX,int sizeY)
{
	m_screenSize.cx = sizeX;
	m_screenSize.cy = sizeY;

	int screenSizeX = GetScreenSizeX();
	int screenSizeY = GetScreenSizeY();

	if (m_lpScreenBuffer == NULL) m_lpScreenBuffer = new int[screenSizeX*(screenSizeY+2)];
	if (m_commonX8Buffer == NULL) m_commonX8Buffer = new int[screenSizeY * 8];

	return TRUE;
}

BOOL CMyGraphics::ReleaseStaticData(void)
{
	DELETEARRAY(m_commonX8Buffer);
	DELETEARRAY(m_lpScreenBuffer);

	return TRUE;
}
*/

BOOL CMyGraphics::Clip(int* pX, int* pY, int* pSizeX, int* pSizeY)
{

	int x = *pX;
	int y = *pY;
	int sizeX = *pSizeX;
	int sizeY = *pSizeY;

	int screenSizeX = GetScreenSizeX();
	int screenSizeY = GetScreenSizeY();


	if ((sizeX<=0) || (sizeY<=0)) return FALSE;
	if ((x>=screenSizeX) || (y>=screenSizeY)) return FALSE;
	if (((x+sizeX)<0) || ((y+sizeY) <0)) return FALSE;

	if (x<0)
	{
		sizeX -= (-x);
		x = 0;
	}

	if (y<0)
	{
		sizeY -= (-y);
		y = 0;
	}

	if ((sizeX<=0) || (sizeY<=0)) return FALSE;
//	if ((x>=screenSizeX) || (y>=screenSizeY)) return FALSE;
//	if (((x+sizeX)<0) || ((y+sizeY) <0)) return FALSE;

	if ((x+sizeX)>screenSizeX)
	{
		sizeX = screenSizeX - x;
	}

	if ((y+sizeY)>screenSizeY)
	{
		sizeY = screenSizeY - y;
	}

	if ((sizeX<=0) || (sizeY<=0)) return FALSE;

	*pX = x;
	*pY = y;
	*pSizeX = sizeX;
	*pSizeY = sizeY;

	return TRUE;
}


BOOL CMyGraphics::Clip(POINT* lpDstPoint,POINT* lpSrcPoint,SIZE* lpSize,SIZE* lpSrcSize)
{
	if (lpDstPoint == NULL) return FALSE;
	if (lpSrcPoint == NULL) return FALSE;
	if (lpSize == NULL) return FALSE;
	if (lpSrcSize == NULL) return FALSE;

	return TRUE;
}


BOOL CMyGraphics::Clip(POINT* lpDstPoint,POINT* lpSrcPoint,SIZE* lpSize)
{
	int dstX = lpDstPoint->x;
	int dstY = lpDstPoint->y;
	int srcX = lpSrcPoint->x;
	int srcY = lpSrcPoint->y;
	int sizeX = lpSize->cx;
	int sizeY = lpSize->cy;

	SIZE screenSize = GetScreenSize();
	int screenSizeX = screenSize.cx;
	int screenSizeY = screenSize.cy;

	if ((sizeX <= 0) || (sizeY <= 0)) return FALSE;
	if ((dstX >= screenSizeX) || ((dstX + sizeX) < 0) || (dstY >= screenSizeY) || ((dstY + sizeY) < 0)) return FALSE;

	if (dstX < 0)
	{
		int delta = -dstX;

		sizeX -= delta;

		srcX += delta;
		dstX = 0;
		if (sizeX <= 0) return FALSE;
	}

	if ((dstX+sizeX) > screenSizeX)
	{
		int delta = dstX + sizeX - screenSizeX;

		sizeX -= delta;

		if (sizeX <= 0) return FALSE;
	}

	if (dstY < 0)
	{
		int delta = -dstY;

		sizeY -= delta;

		srcY += delta;
		dstY = 0;
		if (sizeY <= 0) return FALSE;
	}

	if ((dstY+sizeY) > screenSizeY)
	{
		int delta = dstY + sizeY - screenSizeY;

		sizeY -= delta;

		if (sizeY <= 0) return FALSE;
	}

	lpDstPoint->x = dstX;
	lpDstPoint->y = dstY;
	lpSrcPoint->x = srcX;
	lpSrcPoint->y = srcY;

	lpSize->cx = sizeX;
	lpSize->cy = sizeY;

	return TRUE;
}

void CMyGraphics::NiseFlip(HWND hwnd,int x,int y,int sizeX,int sizeY,int waitFlag)
{
	if (waitFlag)
	{
	}

	HDC hdc = GetDC(hwnd);

	HDC src = CreateCompatibleDC(hdc);

	HGDIOBJ old = SelectObject(src,m_dib);
	BitBlt(hdc,x,y,sizeX,sizeY,src,x,y,SRCCOPY);
	SelectObject(src,old);
	DeleteDC(src);

	ReleaseDC(hwnd,hdc);
}


void CMyGraphics::ReCreateAllShader(void)
{
#if defined _TINYAN3DLIB_
	m_allGraphics->ReCreateAllShader();
	m_allPicture->ReCreateAllShader();
	m_allGeo->ReCreateAllShader();
#endif
}


/*_*/

