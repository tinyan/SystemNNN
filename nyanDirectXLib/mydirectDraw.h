//
// MyDirectDraw.h
//

#if !defined __NYANDIRECTX_DRAW__
#define __NYANDIRECTX_DRAW__

#include <ddraw.h>


class CMyDirectDraw
{
public:
	CMyDirectDraw(HWND hwnd,HINSTANCE hinstance,int sizeX,int sizeY,int col,BOOL bFullScreen = TRUE,int deviceNumber = 0);
	~CMyDirectDraw();
	void End(void);
	BOOL CheckInitOk(void);
	HRESULT Lock(void);
	HRESULT Unlock(void);
	HRESULT Flip(void);
	HRESULT NiseFlip(int x, int y, int sizeX,int sizeY,BOOL waitVSync = FALSE);
	HRESULT NiseFlip2(int dstX, int dstY, int dstSizeX,int dstSizeY,int srcX,int srcY,int srcSizeX,int srcSizeY,BOOL waitVSync = FALSE);
	HRESULT NiseFlip2(RECT dstRect,RECT srcRect,BOOL waitVSync = FALSE);

	LPVOID GetSurfaceAddr(void);
	int GetLPitch(void);
	BOOL OnActivate(BOOL bActive);
	BOOL WindowIsMoved(int x, int y);

	HDC GetMyDC();
	void ReleaseMyDC(HDC hdc);
	HRESULT Activate(BOOL bActive = TRUE);

	void SetWindowSize(int x, int y);

	void SetWindowStart(POINT pt);
	void SetWindowEnd(POINT pt);

	BOOL Check565Mode(void);
	BOOL CheckRGB24Mode(void);
	BOOL CheckRGB32Mode(void);

	void SetGDIFullScreen(BOOL flg = TRUE){m_gdiFullScreenFlag = flg;}



	static BOOL WINAPI DDEnumCallbackEx(
											GUID FAR* lpGUID, 
											LPWSTR lpDriverDescription, 
											LPWSTR lpDriverName, 
											LPVOID lpContext, 
											HMONITOR hm
				); 

	static int m_deviceFound;
	static int m_deviceNumber;
	static int m_deviceCount;
	static GUID m_deviceGUID;

	BOOL Restore(BOOL flg = TRUE);

	static int m_notUseDirectDraw;

private:

	int GetTopBit(int dt);

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

	void ErrorLog(LPSTR mes);
};

#endif
/*_*/

