#pragma once


//
// MyDirectDraw.h
//

#if !defined __NYANDIRECTX_2D__
#define __NYANDIRECTX_2D__

#include <ddraw.h>

#include "mydirectDraw.h"

class CMyDirect2D : public CMyDirectDraw
{
public:
	CMyDirect2D(HWND hwnd, HINSTANCE hinstance, int sizeX, int sizeY, int col, BOOL bFullScreen = TRUE, int deviceNumber = 0);
	virtual ~CMyDirect2D();
	virtual void End(void) override;

	
	BOOL CheckInitOk(void) override;
	bool Lock(void) override;
	HRESULT Unlock(void) override;
	HRESULT Flip(void) override;
	HRESULT NiseFlip(int x, int y, int sizeX, int sizeY, BOOL waitVSync = FALSE) override;
	HRESULT NiseFlip2(int dstX, int dstY, int dstSizeX, int dstSizeY, int srcX, int srcY, int srcSizeX, int srcSizeY, BOOL waitVSync = FALSE) override;
	//HRESULT NiseFlip2(RECT dstRect, RECT srcRect, BOOL waitVSync = FALSE);

	LPVOID GetSurfaceAddr(void) override;
	int GetLPitch(void) override;
	BOOL OnActivate(BOOL bActive) override;
	BOOL WindowIsMoved(int x, int y) override;

	HDC GetMyDC() override;
	void ReleaseMyDC(HDC hdc) override;
	bool Activate(BOOL bActive = TRUE) override;

//	void SetWindowSize(int x, int y) override;

//	void SetWindowStart(POINT pt) override;
//	void SetWindowEnd(POINT pt) override;

//	BOOL Check565Mode(void) override;
//	BOOL CheckRGB24Mode(void) override;
//	BOOL CheckRGB32Mode(void) override;

	//void SetGDIFullScreen(BOOL flg = TRUE) { m_gdiFullScreenFlag = flg; }


/*
	static BOOL WINAPI DDEnumCallbackEx(
		GUID FAR* lpGUID,
		LPWSTR lpDriverDescription,
		LPWSTR lpDriverName,
		LPVOID lpContext,
		HMONITOR hm
	);
	*/



	BOOL Restore(BOOL flg = TRUE) override;

//	static void SetOutColor(int r, int g, int b);

//	static bool m_direct2DFlag;
	
	void ClearBackSurface(void) override;

protected:

	LPVOID m_factory;
	LPVOID m_renderTargetHWND;

//	int GetTopBit(int dt);

	/*
	int m_sizeX;
	int m_sizeY;
	int m_col;

	int m_printX;
	int m_printY;
	int m_edgeX;
	int m_edgeY;
	int m_menuBarY;

	BOOL m_fullScreenFlag;
	BOOL m_displayModeChangedFlag;
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	BOOL m_initFlag;

	LPVOID m_addr;
	int m_lPitch;

	BOOL m_lockedFlag;
	LPDIRECTDRAW7 m_lpDirectDraw;
	LPDIRECTDRAWSURFACE7 m_lpFront;
	LPDIRECTDRAWSURFACE7 m_lpBack;
	LPDIRECTDRAWCLIPPER m_lpClip;


	//	LPVOID m_directDraw7;

	int m_maskRed;
	int m_maskGreen;
	int m_maskBlue;

	int m_shiftRed;
	int m_shiftGreen;
	int m_shiftBlue;

	int m_windowSizeX;
	int m_windowSizeY;

	int m_windowStartX;
	int m_windowStartY;
	int m_windowEndX;
	int m_windowEndY;

	BOOL m_555Flag;
	BOOL m_565Flag;

	BOOL m_RGB24Flag;
	BOOL m_RGB32Flag;

	BOOL m_gdiFullScreenFlag;

	int m_bitCount;
	static int m_fillColorR;
	static int m_fillColorG;
	static int m_fillColorB;

	//void ErrorLog(LPSTR mes);

	*/



	
};

#endif
/*_*/

