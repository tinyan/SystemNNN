//
// MyDirectDraw.h
//

#if !defined __NYANDIRECTX_DRAW__
#define __NYANDIRECTX_DRAW__

#include <ddraw.h>

class CMyDirect2D;



class CMyDirectDraw
{
public:
	CMyDirectDraw(HWND hwnd,HINSTANCE hinstance,int sizeX,int sizeY,int col,BOOL bFullScreen = TRUE,int deviceNumber = 0);
	virtual ~CMyDirectDraw();
	virtual void End(void);
	virtual BOOL CheckInitOk(void);
	virtual bool Lock(void);
	virtual HRESULT Unlock(void);
	virtual HRESULT Flip(void);
	virtual HRESULT NiseFlip(int x, int y, int sizeX,int sizeY,BOOL waitVSync = FALSE);
	virtual HRESULT NiseFlip2(int dstX, int dstY, int dstSizeX,int dstSizeY,int srcX,int srcY,int srcSizeX,int srcSizeY,BOOL waitVSync = FALSE);
	virtual HRESULT NiseFlip2(RECT dstRect,RECT srcRect,BOOL waitVSync = FALSE);
	virtual HRESULT NiseFlip3(int dstX, int dstY, int dstSizeX, int dstSizeY, int srcX, int srcY, int srcSizeX, int srcSizeY, BOOL waitVSync = FALSE);
	virtual HRESULT NiseFlip3(RECT dstRect, RECT srcRect, BOOL waitVSync = FALSE);

	virtual LPVOID GetSurfaceAddr(void);
	virtual int GetLPitch(void);
	virtual BOOL OnActivate(BOOL bActive);
	virtual BOOL WindowIsMoved(int x, int y);

	virtual HDC GetMyDC();
	virtual void ReleaseMyDC(HDC hdc);
	virtual bool Activate(BOOL bActive = TRUE);

	virtual void SetWindowSize(int x, int y);

	virtual void SetWindowStart(POINT pt);
	virtual void SetWindowEnd(POINT pt);

	virtual BOOL Check565Mode(void);
	virtual BOOL CheckRGB24Mode(void);
	virtual BOOL CheckRGB32Mode(void);

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

	virtual BOOL Restore(BOOL flg = TRUE);

	static int m_notUseDirectDraw;
	static void SetOutColor(int r,int g,int b);

	static bool m_direct2DFlag;
	virtual void ClearBackSurface(void);

protected:

	virtual int GetTopBit(int dt);

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

	virtual void ErrorLog(LPSTR mes);

	CMyDirect2D* m_direct2D;


//	CMyDirect2D* m_direct2D;


};

#endif
/*_*/

