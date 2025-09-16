//
// MyDierectX.cpp
//

//#define INITGUID
#include <windows.h>
#include <stdio.h>

#include "..\nyanlib\include\myfile.h"

#include "..\nnnLib\mainControl.h"
#include "..\nyanLib\INCLUDE\commonmacro.h"
#include "myDirect2D.h"
#include "MyDirectDraw.h"




int CMyDirectDraw::m_deviceFound = 0;
int CMyDirectDraw::m_deviceNumber = 0;
int CMyDirectDraw::m_deviceCount = 0;
GUID CMyDirectDraw::m_deviceGUID;

int CMyDirectDraw::m_fillColorR = 0;
int CMyDirectDraw::m_fillColorG = 0;
int CMyDirectDraw::m_fillColorB = 0;

int CMyDirectDraw::m_notUseDirectDraw = 0;

bool CMyDirectDraw::m_direct2DFlag = false;

BOOL WINAPI CMyDirectDraw::DDEnumCallbackEx(
  GUID FAR* lpGUID, 
  LPWSTR lpDriverDescription, 
  LPWSTR lpDriverName, 
  LPVOID lpContext, 
  HMONITOR hm
)
{
	OutputDebugString("\n\nDriver=");
	OutputDebugString((LPCSTR)lpDriverDescription);
	OutputDebugString("\nDesc=");
	OutputDebugString((LPCSTR)lpDriverName);

	if (lpGUID == NULL)
	{
		return TRUE;
	}

	unsigned long id1 = lpGUID->Data1;
	unsigned short id2 = lpGUID->Data2;
	unsigned short id3 = lpGUID->Data3;
	unsigned char* id4 = lpGUID->Data4;

	char mes[1024];
	wsprintf(mes,"\n %d - %d - %d - %s",(int)id1,(int)id2,(int)id3,id4);
	OutputDebugString(mes);

	if (hm == NULL) return TRUE;

	m_deviceCount++;

	if (m_deviceCount == m_deviceNumber)
	{
		OutputDebugString("\n\nFound 指定ディスプレイ");
		m_deviceFound = m_deviceNumber;
		m_deviceGUID = *lpGUID;
		return FALSE;
	}

	if (m_deviceCount > m_deviceNumber)
	{
		OutputDebugString("\n\nFound ディスプレイが見つかりませんでした");
		return FALSE;	//noit found
	}

	return TRUE;
}




//void ClearBackSurface(void);



CMyDirectDraw::CMyDirectDraw(HWND hwnd,HINSTANCE hinstance, int sizeX,int sizeY,int col,BOOL bFullScreen,int deviceNumber)
{
#if defined _TINYAN3DLIB_
	return;
#endif

//deviceNumber = 0;

//	m_displayModeChangedFlag = bFullScreen;

	m_direct2D = NULL;



	m_hWnd = hwnd;
	m_hInstance = hinstance;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_col = col;
	m_fullScreenFlag = bFullScreen;
	m_gdiFullScreenFlag = bFullScreen;
	m_windowSizeX = sizeX;
	m_windowSizeY = sizeY;

	m_555Flag = FALSE;
	m_565Flag = FALSE;
	m_RGB24Flag = TRUE;
	m_RGB32Flag = TRUE;

	m_lpFront = NULL;
	m_lpBack = NULL;
	m_lpDirectDraw = NULL;

	m_lpClip = NULL;

	m_displayModeChangedFlag = FALSE;

	m_lockedFlag = FALSE;

	m_initFlag = FALSE;

	m_addr = nullptr;
	m_bitCount = 8;
	m_edgeX = 0;
	m_edgeY = 0;

	m_lPitch = 0;
	m_maskBlue = 0xff;
	m_maskGreen = 0xff00;
	m_maskRed = 0xff0000;

	m_menuBarY = 0;
	m_printX = 0;
	m_printY = 0;

	m_shiftBlue = 0;
	m_shiftGreen = 8;
	m_shiftRed = 16;

	m_windowStartX = 0;
	m_windowStartY = 0;
	m_windowEndX = 800;
	m_windowEndY = 600;



	if (m_direct2DFlag)
	{
		return;
	}


	if (m_notUseDirectDraw) return;

//	m_directDraw = NULL;


	HRESULT hr;
//LPDDENUMCALLBACK(
//DirectDrawEnumerateExA(

//	LPDIRECTDRAW lpDD;
//	if (DirectDrawCreate(NULL,&lpDD,NULL)  != DD_OK) return;
//	HRESULT hr = lpDD->QueryInterface(IID_IDirectDraw7,(LPVOID*)&m_lpDirectDraw);
//	lpDD->Release();
//	if (hr != DD_OK) return;



	m_deviceNumber = deviceNumber;
	m_deviceCount = 0;
	m_deviceFound = 0;

	if (deviceNumber > 0)
	{
		DirectDrawEnumerateEx((LPDDENUMCALLBACKEX)DDEnumCallbackEx,NULL,DDENUM_ATTACHEDSECONDARYDEVICES);
	}


	if (m_deviceFound > 0)
	{
		if (DirectDrawCreateEx(&m_deviceGUID,(void**)&m_lpDirectDraw,IID_IDirectDraw7,NULL) != DD_OK)
		{
//MessageBox(NULL,"1","directDraw error",MB_OK);

			return;
		}
	}
	else
	{
		if (DirectDrawCreateEx(NULL,(void**)&m_lpDirectDraw,IID_IDirectDraw7,NULL) != DD_OK)
		{
//MessageBox(NULL,"1","directDraw error",MB_OK);

			return;
		}
	}



//	if (bFullScreen)
	if (0)
	{
		if (m_lpDirectDraw->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN) != DD_OK)
		{
			return;
		}
		if (m_lpDirectDraw->SetDisplayMode(sizeX, sizeY, col,0,0) != DD_OK)
		{
			return;
		}
	}
	else
	{
		if (m_lpDirectDraw->SetCooperativeLevel(hwnd, DDSCL_NORMAL) != DD_OK)
		{
//MessageBox(NULL,"2","directDraw error",MB_OK);
			return;
		}
	}


	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize=sizeof(ddsd);
	if (0)
	{
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT ;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		ddsd.dwBackBufferCount=1;
		m_displayModeChangedFlag = TRUE;
	}
	else
	{
		ddsd.dwFlags = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	}


//887600e1

//	LPDIRECTDRAWSURFACE7 lpSurface;
//	HRESULT hr99 = m_lpDirectDraw->CreateSurface(&ddsd,&lpSurface,NULL);
//	if (hr99  != DD_OK) return;
//	HRESULT hr2 = lpSurface->QueryInterface(IID_IDirectDrawSurface3,(LPVOID*)&m_lpFront);
//	lpSurface->Release();
//	if (hr2 != DD_OK) return;
	HRESULT hr99 = m_lpDirectDraw->CreateSurface(&ddsd,&m_lpFront,NULL);
	if (hr99  != DD_OK)
	{
//MessageBox(NULL,"3","directDraw error",MB_OK);
		return;
	}



//	if (bFullScreen)
	if (0)
	{
		ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER | DDSCAPS_VIDEOMEMORY ;
		if (m_lpFront->GetAttachedSurface(&(ddsd.ddsCaps),&m_lpBack) != DD_OK)
		{
			ddsd.ddsCaps.dwCaps = DDSCAPS_BACKBUFFER;
			if (m_lpFront->GetAttachedSurface(&(ddsd.ddsCaps),&m_lpBack) != DD_OK)
			{
				return;
			}
		}
	}
	else
	{
		ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		ddsd.dwWidth = sizeX;
		ddsd.dwHeight = sizeY;
//		LPDIRECTDRAWSURFACE7 lpBack1;
//		if (m_lpDirectDraw->CreateSurface(&ddsd,&lpBack1,NULL) != DD_OK) return;
//		HRESULT hr3 = lpBack1->QueryInterface(IID_IDirectDrawSurface7,(LPVOID*)&m_lpBack);
//		lpBack1->Release();
		HRESULT hr3 = m_lpDirectDraw->CreateSurface(&ddsd,&m_lpBack,NULL);
		if (hr3 != DD_OK)
		{
//MessageBox(NULL,"4","directDraw error",MB_OK);
			return;
		}
	}









//	MessageBox(NULL,"1","2",MB_OK);

	DDPIXELFORMAT ddpf;
	ddpf.dwSize = sizeof(ddpf);

	m_lpFront->GetPixelFormat(&ddpf);

	m_maskRed = ddpf.dwRBitMask;
	m_maskGreen = ddpf.dwGBitMask;
	m_maskBlue = ddpf.dwBBitMask;

//	char mes[256];
//	sprintf_s(mes,256,"[%d %d %d]",m_maskRed,m_maskGreen,m_maskBlue);

	m_bitCount = ddpf.dwRGBBitCount;
	//OutputDebugString(mes);
	//m_shiftRed = 24-GetTopBit(m_maskRed);
	//m_shiftGreen = 24-GetTopBit(m_maskGreen);
	//m_shiftBlue = 24-GetTopBit(m_maskBlue);

	if (ddpf.dwRGBBitCount == 16)
	{
		if (m_maskGreen == 0x7e0) m_565Flag = TRUE;
		if (m_maskGreen == 0x3e0) m_555Flag = TRUE;
	}

	m_RGB24Flag = TRUE;
	if (ddpf.dwRGBBitCount == 24)
	{
		if (m_maskRed == 0xff) m_RGB24Flag = FALSE;
	}

	m_RGB32Flag = TRUE;
	if (ddpf.dwRGBBitCount == 32)
	{
		if (m_maskRed == 0xff) m_RGB32Flag = FALSE;
	}


//if (m_565Flag) MessageBox(NULL,"565","16bit",MB_OK);
//if (m_555Flag) MessageBox(NULL,"555","16bit",MB_OK);

	m_initFlag = TRUE;

	if (1)
	{
		hr = m_lpDirectDraw->CreateClipper(0,&m_lpClip,NULL);
		if (hr != 0)
		{
//			char mes[256];
//			sprintf(mes,"[create clipper error:%X]",hr);
//			ErrorLog(mes);
		}

//		m_lpClip->Initialize();

		if (m_lpClip != NULL)
		{
			//m_lpClip->Initialize();
			hr = m_lpClip->SetHWnd(0,m_hWnd);
			if (hr != 0)
			{
//				char mes[256];
//				sprintf(mes,"[clipper::sethwnd error:%X]",hr);
//				ErrorLog(mes);
			}

			hr = m_lpFront->SetClipper(m_lpClip);
			if (hr != 0)
			{
//				char mes[256];
//				sprintf(mes,"[clipper::setclipper error:%X]",hr);
//				ErrorLog(mes);
			}
		}
	}


	ClearBackSurface();




	WindowIsMoved(0,0);
}



CMyDirectDraw::~CMyDirectDraw()
{


	if (m_notUseDirectDraw) return;

#if defined _TINYAN3DLIB_
	return;
#endif

	End();
}


void CMyDirectDraw::End(void)
{
	if (m_direct2DFlag)
	{
		ENDDELETECLASS(m_direct2D);
		return;
	}

	if (m_notUseDirectDraw) return;

#if defined _TINYAN3DLIB_
	return;
#endif


	Sleep(100);

	if (m_lpClip != NULL)
	{
//ErrorLog("1");
//		m_lpClip->SetHWnd(0,NULL);
		m_lpClip->Release();
		m_lpClip = NULL;
	}

	if (!m_fullScreenFlag)
	{
//ErrorLog("2");
		if (m_lpBack != NULL)
		{
			m_lpBack->Release();
			m_lpBack = NULL;
		}
	}


	if (m_lpFront != NULL)
	{
//ErrorLog("3");

		m_lpFront->Release();
		m_lpFront = NULL;
	}

	if (m_lpDirectDraw != NULL)
	{
//ErrorLog("4");

		if (m_displayModeChangedFlag)
		{
//ErrorLog("5");

			m_lpDirectDraw->RestoreDisplayMode();
		}
//ErrorLog("6");

		m_lpDirectDraw->SetCooperativeLevel(NULL, DDSCL_NORMAL);
	//もとのモードにもどす
//ErrorLog("7");

		Sleep(100);
		m_lpDirectDraw->Release();
		m_lpDirectDraw = NULL;
//ErrorLog("8");

	}
}


BOOL CMyDirectDraw::CheckInitOk(void)
{
	if (m_direct2DFlag)
	{
		return TRUE;//@@@;
	}


	if (m_notUseDirectDraw) return TRUE;

#if defined _TINYAN3DLIB_
	return TRUE;
#endif

	return m_initFlag;
}

BOOL CMyDirectDraw::Restore(BOOL flg)
{
	if (m_direct2DFlag)
	{
		return TRUE;//@@@
	}




	if (m_notUseDirectDraw) return TRUE;

#if defined _TINYAN3DLIB_
	return TRUE;
#endif

	BOOL b = FALSE;

	if (flg)
	{
		HRESULT hr;

		if (m_lpFront != NULL)
		{
			hr =m_lpFront->IsLost();
			if (hr == DDERR_SURFACELOST)
			{
				m_lpFront->Restore();
				b = TRUE;
			}
		}

		if (m_lpBack != NULL)
		{
			hr =m_lpBack->IsLost();
			if (hr == DDERR_SURFACELOST)
			{
				m_lpBack->Restore();
				ClearBackSurface();

				b = TRUE;
			}
		}
	}
	return b;
}


bool CMyDirectDraw::Activate(BOOL bActive)
{
	if (m_direct2DFlag)
	{
		return true;//@@@
	}



	if (m_notUseDirectDraw) return false;

#if defined _TINYAN3DLIB_
	return false;
#endif

	bool b = false;

	if (bActive)
	{
		HRESULT hr;


		if (m_lpFront != NULL)
		{
			hr =m_lpFront->IsLost();
			if (hr == DDERR_SURFACELOST)
			{
//				MessageBox(NULL,"1","2",MB_OK);
				m_lpFront->Restore();
				b = true;
			}
		}

		if (m_lpBack != NULL)
		{
			hr =m_lpBack->IsLost();
			if (hr == DDERR_SURFACELOST)
			{
				m_lpBack->Restore();
				ClearBackSurface();

				b = true;
			}
		}
	}

	return b;

}



bool CMyDirectDraw::Lock(void)
{
	if (m_direct2DFlag)
	{
		return true;//@@@
	}


	if (m_notUseDirectDraw) return false;

#if defined _TINYAN3DLIB_
	return DD_OK;
#endif

	if (m_fullScreenFlag)
	{
		if (m_lpBack == NULL) return false;
	}
	else
	{
		if (m_lpBack == NULL) return false;
	}

//	if (m_lpFront->IsLost() == DDERR_SURFACELOST) return FALSE;
//	if (m_lpBack->IsLost() == DDERR_SURFACELOST) return FALSE;

	DDSURFACEDESC2 ddsd;
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize=sizeof(ddsd);

	HRESULT ddrval;
	
	if (m_fullScreenFlag)
	{
//		ddrval = m_lpBack->Lock(NULL,&ddsd,DDLOCK_NOSYSLOCK | DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT | DDLOCK_WRITEONLY,NULL);
		ddrval = m_lpBack->Lock(NULL,&ddsd,DDLOCK_NOSYSLOCK | DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT ,NULL);
	}
	else
	{
//		ddrval = m_lpBack->Lock(NULL,&ddsd,DDLOCK_NOSYSLOCK | DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT | DDLOCK_WRITEONLY,NULL);
		ddrval = m_lpBack->Lock(NULL,&ddsd,DDLOCK_NOSYSLOCK | DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT ,NULL);
	}

	if (ddrval == DD_OK)
	{
		m_lPitch = (int)ddsd.lPitch;
		m_addr = ddsd.lpSurface;
		m_lockedFlag=TRUE;
		return true;
	}

	m_lockedFlag=FALSE;
	return false;
}

HRESULT CMyDirectDraw::Unlock(void)
{
	if (m_direct2DFlag)
	{
		return TRUE;//@@@
	}


	if (m_notUseDirectDraw) return DD_OK;

#if defined _TINYAN3DLIB_
	return DD_OK;
#endif

	if (m_fullScreenFlag)
	{
		if (m_lpBack == NULL) return FALSE;
	}
	else
	{
		if (m_lpBack == NULL) return FALSE;
	}

//	if (m_lpFront->IsLost() == DDERR_SURFACELOST) return FALSE;
//	if (m_lpBack->IsLost() == DDERR_SURFACELOST) return FALSE;

	HRESULT ddrval;
	if (m_fullScreenFlag)
	{
		ddrval = m_lpBack->Unlock(NULL);
	}
	else
	{
		ddrval = m_lpBack->Unlock(NULL);
	}

	if (ddrval != DD_OK) return FALSE;
	m_lockedFlag=FALSE;
	return TRUE;
}

HRESULT CMyDirectDraw::NiseFlip(int x,int y, int sizeX, int sizeY,BOOL waitVSync)
{
	if (m_direct2DFlag)
	{
		if (m_direct2D)
		{
			return m_direct2D->NiseFlip(x, y, sizeX, sizeY, 0);
		}
			
		return TRUE;//@@@
	}




	if (m_notUseDirectDraw) return DD_OK;

#if defined _TINYAN3DLIB_
	return DD_OK;
#endif

	if (m_lpFront == NULL) return FALSE;
//	if (m_fullScreenFlag) return FALSE;
	if (m_lpBack == NULL) return FALSE;


	if (m_lpFront->IsLost() == DDERR_SURFACELOST)
	{
		m_lpFront->Restore();
	}

	if (m_lpBack != NULL)
	{
		if (m_lpBack->IsLost() == DDERR_SURFACELOST)
		{
			m_lpBack->Restore();
			ClearBackSurface();
		}
	}

	if (m_lpFront->IsLost() == DDERR_SURFACELOST) return FALSE;
	if (m_lpBack->IsLost() == DDERR_SURFACELOST) return FALSE;


	DWORD flg = DDBLT_ASYNC | DDBLT_WAIT;

	RECT srcRect;
	RECT dstRect;


	int srcStartX = 0 + x;
	int srcStartY = 0 + y;
	int srcEndX = x + sizeX;
	int srcEndY = y + sizeY;

	int dstStartX = x;
	int dstStartY = y;

	if (m_fullScreenFlag == FALSE)
	{
		if (m_gdiFullScreenFlag == FALSE)
		{
			dstStartX += m_printX + m_edgeX;
			dstStartY += m_printY + m_edgeY + m_menuBarY;
		}
	}

	int dstEndX = dstStartX + sizeX ;
	int dstEndY = dstStartY + sizeY ;


	if (m_fullScreenFlag)
	{
		if (dstStartX<0)
		{
			srcStartX += (-dstStartX);
			dstStartX = 0;
		}

		if (dstStartY<0)
		{
			srcStartY += (-dstStartY);
			dstStartY = 0;
		}


		if (dstEndX >m_windowSizeX)
		{
			srcEndX -= (dstEndX - m_windowSizeX);
			dstEndX = m_windowSizeX;
		}

		if (dstEndY >m_windowSizeY)
		{
			srcEndY -= (dstEndY - m_windowSizeY);
			dstEndY = m_windowSizeY;
		}
	}
	else
	{
		if (dstStartX<m_windowStartX)
		{
			srcStartX += (m_windowStartX-dstStartX);
			dstStartX = m_windowStartX;
		}

		if (dstStartY<m_windowStartY)
		{
			srcStartY += (m_windowStartY-dstStartY);
			dstStartY = m_windowStartY;
		}


		if (dstEndX >m_windowEndX)
		{
			srcEndX -= (dstEndX - m_windowEndX);
			dstEndX = m_windowEndX;
		}

		if (dstEndY >m_windowEndY)
		{
			srcEndY -= (dstEndY - m_windowEndY);
			dstEndY = m_windowEndY;
		}
	}

	if (srcStartX >= srcEndX)
	{
		return FALSE;
	}
	if (srcStartY >= srcEndY)
	{
		return FALSE;
	}

	SetRect(&srcRect,srcStartX,srcStartY,srcEndX,srcEndY);
	SetRect(&dstRect,dstStartX,dstStartY,dstEndX,dstEndY);




	if (waitVSync)
	{
		m_lpDirectDraw->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN ,NULL);
	}

	HRESULT hr = m_lpFront->Blt(&dstRect,m_lpBack,&srcRect,flg,NULL);


	return TRUE;
}

HRESULT CMyDirectDraw::NiseFlip2(RECT dstRect,RECT srcRect,BOOL waitVSync)
{
	return NiseFlip2(dstRect.left,dstRect.top,dstRect.right,dstRect.bottom,srcRect.left,srcRect.top,srcRect.right,srcRect.bottom,waitVSync);
}

HRESULT CMyDirectDraw::NiseFlip3(RECT dstRect, RECT srcRect, BOOL waitVSync)
{
	return NiseFlip3(dstRect.left, dstRect.top, dstRect.right, dstRect.bottom, srcRect.left, srcRect.top, srcRect.right, srcRect.bottom, waitVSync);
}

HRESULT CMyDirectDraw::NiseFlip2(int dstX, int dstY, int dstSizeX,int dstSizeY,int srcX,int srcY,int srcSizeX,int srcSizeY,BOOL waitVSync)
{
	if (m_direct2DFlag)
	{
		if (m_direct2D)
		{
			return m_direct2D->NiseFlip2(dstX, dstY, dstSizeX, dstSizeY, srcX, srcY, srcSizeX, srcSizeY, 0);
		}
		return TRUE;//@@@
	}

	if (m_notUseDirectDraw) return DD_OK;

#if defined _TINYAN3DLIB_
	return DD_OK;
#endif

	if (m_lpFront == NULL) return FALSE;
	if (m_lpBack == NULL) return FALSE;


	if (m_lpFront->IsLost() == DDERR_SURFACELOST)
	{
		m_lpFront->Restore();
	}

	if (m_lpBack != NULL)
	{
		if (m_lpBack->IsLost() == DDERR_SURFACELOST)
		{
			m_lpBack->Restore();
			ClearBackSurface();
		}
	}

	if (m_lpFront->IsLost() == DDERR_SURFACELOST) return FALSE;
	if (m_lpBack->IsLost() == DDERR_SURFACELOST) return FALSE;


	DWORD flg = DDBLT_ASYNC | DDBLT_WAIT;

	RECT srcRect;
	RECT dstRect;


	int srcStartX = srcX;
	int srcStartY = srcY;
	int srcEndX = srcX + srcSizeX;
	int srcEndY = srcY + srcSizeY;

	int dstStartX = dstX;
	int dstStartY = dstY;


	if (m_fullScreenFlag == FALSE)
	{
		if (m_gdiFullScreenFlag == FALSE)
		{
			dstStartX += m_printX + m_edgeX;
			dstStartY += m_printY + m_edgeY + m_menuBarY;
		}
	}

	int dstEndX = dstStartX + dstSizeX ;
	int dstEndY = dstStartY + dstSizeY ;

	int srcMultiX = srcSizeX;
	int dstMultiX = dstSizeX;
	int srcMultiY = srcSizeY;
	int dstMultiY = dstSizeY;

	if (m_fullScreenFlag)
	{
		if (dstStartX<0)
		{
			srcStartX += ((-dstStartX) * srcMultiX) / dstMultiX;
			dstStartX = 0;
		}

		if (dstStartY<0)
		{
			srcStartY += ((-dstStartY) + srcMultiY) / dstMultiY;
			dstStartY = 0;
		}


		if (dstEndX >m_windowSizeX)
		{
			srcEndX -= ((dstEndX - m_windowSizeX) * srcMultiX) / dstMultiX;
			dstEndX = m_windowSizeX;
		}

		if (dstEndY >m_windowSizeY)
		{
			srcEndY -= ((dstEndY - m_windowSizeY) * srcMultiY) / dstMultiY;
			dstEndY = m_windowSizeY;
		}
	}
	else
	{
		if (dstStartX<m_windowStartX)
		{
			srcStartX += ((m_windowStartX-dstStartX) * srcMultiX) / dstMultiX;
			dstStartX = m_windowStartX;
		}

		if (dstStartY<m_windowStartY)
		{
			srcStartY += ((m_windowStartY-dstStartY) * srcMultiY) / dstMultiY;
			dstStartY = m_windowStartY;
		}


		if (dstEndX >m_windowEndX)
		{
			srcEndX -= ((dstEndX - m_windowEndX) * srcMultiX) / dstMultiX;
			dstEndX = m_windowEndX;
		}

		if (dstEndY >m_windowEndY)
		{
			srcEndY -= ((dstEndY - m_windowEndY) * srcMultiY) / dstMultiY;
			dstEndY = m_windowEndY;
		}
	}

	if (srcStartX >= srcEndX)
	{
		return FALSE;
	}
	if (srcStartY >= srcEndY)
	{
		return FALSE;
	}

	SetRect(&srcRect,srcStartX,srcStartY,srcEndX,srcEndY);
	SetRect(&dstRect,dstStartX,dstStartY,dstEndX,dstEndY);




	if (waitVSync)
	{
		m_lpDirectDraw->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN ,NULL);
	}

	HRESULT hr = m_lpFront->Blt(&dstRect,m_lpBack,&srcRect,flg,NULL);


	return TRUE;
}

HRESULT CMyDirectDraw::NiseFlip3(int dstX, int dstY, int dstSizeX, int dstSizeY, int srcX, int srcY, int srcSizeX, int srcSizeY, BOOL waitVSync)
{
	srcX = 0;
	srcY = 0;
	srcSizeX = dstSizeX;
	srcSizeY = dstSizeY;

	if (m_lpFront == NULL) return FALSE;
	if (m_lpBack == NULL) return FALSE;

	if (m_lpFront->IsLost() == DDERR_SURFACELOST)
	{
		m_lpFront->Restore();
	}

	if (m_lpBack != NULL)
	{
		if (m_lpBack->IsLost() == DDERR_SURFACELOST)
		{
			m_lpBack->Restore();
			ClearBackSurface();
		}
	}

	if (m_lpFront->IsLost() == DDERR_SURFACELOST) return FALSE;
	if (m_lpBack->IsLost() == DDERR_SURFACELOST) return FALSE;


	DWORD flg = DDBLT_ASYNC | DDBLT_WAIT;

	RECT srcRect;
	RECT dstRect;


	int srcStartX = srcX;
	int srcStartY = srcY;
	int srcEndX = srcX + srcSizeX;
	int srcEndY = srcY + srcSizeY;

	int dstStartX = dstX;
	int dstStartY = dstY;


	if (m_fullScreenFlag == FALSE)
	{
		if (m_gdiFullScreenFlag == FALSE)
		{
			dstStartX += m_printX + m_edgeX;
			dstStartY += m_printY + m_edgeY + m_menuBarY;
		}
	}

	int dstEndX = dstStartX + dstSizeX;
	int dstEndY = dstStartY + dstSizeY;

	int srcMultiX = srcSizeX;
	int dstMultiX = dstSizeX;
	int srcMultiY = srcSizeY;
	int dstMultiY = dstSizeY;

	if (m_fullScreenFlag)
	{
		if (dstStartX < 0)
		{
			srcStartX += ((-dstStartX) * srcMultiX) / dstMultiX;
			dstStartX = 0;
		}

		if (dstStartY < 0)
		{
			srcStartY += ((-dstStartY) + srcMultiY) / dstMultiY;
			dstStartY = 0;
		}


		if (dstEndX > m_windowSizeX)
		{
			srcEndX -= ((dstEndX - m_windowSizeX) * srcMultiX) / dstMultiX;
			dstEndX = m_windowSizeX;
		}

		if (dstEndY > m_windowSizeY)
		{
			srcEndY -= ((dstEndY - m_windowSizeY) * srcMultiY) / dstMultiY;
			dstEndY = m_windowSizeY;
		}
	}
	else
	{
		if (dstStartX < m_windowStartX)
		{
			srcStartX += ((m_windowStartX - dstStartX) * srcMultiX) / dstMultiX;
			dstStartX = m_windowStartX;
		}

		if (dstStartY < m_windowStartY)
		{
			srcStartY += ((m_windowStartY - dstStartY) * srcMultiY) / dstMultiY;
			dstStartY = m_windowStartY;
		}


		if (dstEndX > m_windowEndX)
		{
			srcEndX -= ((dstEndX - m_windowEndX) * srcMultiX) / dstMultiX;
			dstEndX = m_windowEndX;
		}

		if (dstEndY > m_windowEndY)
		{
			srcEndY -= ((dstEndY - m_windowEndY) * srcMultiY) / dstMultiY;
			dstEndY = m_windowEndY;
		}
	}

	if (srcStartX >= srcEndX)
	{
		return FALSE;
	}
	if (srcStartY >= srcEndY)
	{
		return FALSE;
	}

	SetRect(&srcRect, srcStartX, srcStartY, srcEndX, srcEndY);
	SetRect(&dstRect, dstStartX, dstStartY, dstEndX, dstEndY);




	if (waitVSync)
	{
		m_lpDirectDraw->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, NULL);
	}

	HRESULT hr = m_lpFront->Blt(&dstRect, m_lpBack, &srcRect, flg, NULL);


	return TRUE;
}

HRESULT CMyDirectDraw::Flip(void)
{
	if (m_direct2DFlag)
	{
		//@@@
		return TRUE;
	}

	if (m_notUseDirectDraw) return DD_OK;

#if defined _TINYAN3DLIB_
	return DD_OK;
#endif

	if (m_lpFront == NULL) return FALSE;

	if (m_lpFront->IsLost() == DDERR_SURFACELOST) return FALSE;
	if (m_lpBack->IsLost() == DDERR_SURFACELOST) return FALSE;

	DWORD flg = DDBLT_ASYNC | DDBLT_WAIT;


	if (m_fullScreenFlag)
	{
//		HRESULT ddrval = m_lpFront->Flip(NULL,DDFLIP_WAIT);
		RECT srcRect;
		RECT dstRect;
		SetRect(&srcRect,0,0,m_sizeX,m_sizeY);
		SetRect(&dstRect,0,0,m_sizeX,m_sizeY);
		HRESULT ddrval = m_lpFront->Blt(&dstRect,m_lpBack,&srcRect,flg,NULL);

		if (ddrval == DD_OK)
		{
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		if (m_lpBack == NULL)
		{
			return FALSE;
		}


		RECT srcRect;
		RECT dstRect;


		int srcStartX = 0;
		int srcStartY = 0;
		int srcEndX = m_sizeX;
		int srcEndY = m_sizeY;

		int dstStartX = m_printX + m_edgeX;
		int dstStartY = m_printY + m_edgeY + m_menuBarY;
		int dstEndX = dstStartX + m_sizeX;
		int dstEndY = dstStartY + m_sizeY;

		int x0,x1,x2,x3;
		x0=dstStartX;
		x1=m_printX;
		x2=m_edgeX;
		x3=dstEndX;

		if (dstStartX<0)
		{
			srcStartX += (-dstStartX);
			dstStartX = 0;
		}

		if (dstStartY<0)
		{
			srcStartY += (-dstStartY);
			dstStartY = 0;
		}

		if (dstEndX >m_windowSizeX)
		{
			srcEndX -= (dstEndX - m_windowSizeX);
			dstEndX = m_windowSizeX;
		}

		if (dstEndY >m_windowSizeY)
		{
			srcEndY -= (dstEndY - m_windowSizeY);
			dstEndY = m_windowSizeY;
		}

		if (srcStartX >= srcEndX)
		{
			return FALSE;
		}
		if (srcStartY >= srcEndY)
		{
			return FALSE;
		}
	
		SetRect(&srcRect,srcStartX,srcStartY,srcEndX,srcEndY);
		SetRect(&dstRect,dstStartX,dstStartY,dstEndX,dstEndY);



//		SetRect(&srcRect,0,0,m_sizeX,m_sizeY);
//		int sx = m_printX+m_edgeX;
//		int sy = m_printY+m_edgeY+m_menuBarY;
//		SetRect(&dstRect,sx,sy,sx+m_dispX,sy+m_dispY);

//		SetRect(&dstRect,sx,sy,sx+m_sizeX,sy+m_sizeY);

		//clip in screen







		HRESULT hr = m_lpFront->Blt(&dstRect,m_lpBack,&srcRect,flg,NULL);
//		HRESULT hr = m_lpFront->BltFast(sx,sy,m_lpBack,&srcRect,0);

//		HDC src,dst;
//		m_lpBack->GetDC(&src);
//		m_lpFront->GetDC(&dst);

//		BitBlt(dst,0,0,m_sizeX,m_sizeY,src,0,0,SRCCOPY);

//		m_lpBack->ReleaseDC(src);
//		m_lpFront->ReleaseDC(dst);







		return TRUE;
	}

	return FALSE;	//dmy
}


LPVOID CMyDirectDraw::GetSurfaceAddr(void)
{
	if (m_direct2DFlag)
	{
		return NULL;//@@@
	}

	if (m_notUseDirectDraw) return NULL;

#if defined _TINYAN3DLIB_
	return NULL;
#endif

	if (!m_lockedFlag)
	{
		return NULL;
	}

	return m_addr;
}


int CMyDirectDraw::GetLPitch(void)
{
	if (m_direct2DFlag)
	{
		return 0;//@@@
	}


#if defined _TINYAN3DLIB_
	return 0;
#endif

	if (!m_lockedFlag)
	{
		return 0;
	}
	return m_lPitch;
}

int CMyDirectDraw::GetTopBit(int d)
{



#if defined _TINYAN3DLIB_
	return 0;
#endif

	
	int n=0;
	unsigned int dd = (unsigned int)d;
	for (int i=0;i<32;i++)
	{
		if ((dd & 0x80000000)==0)
		{
			dd <<= 1;
			n++;
		}
	}
	return(n);
}

BOOL CMyDirectDraw::OnActivate(BOOL bActive)
{
	if (m_direct2DFlag)
	{
		if (m_direct2DFlag)
		{
			return m_direct2D->OnActivate(bActive);
		}

		return TRUE;//@@@
	}


	if (m_notUseDirectDraw) return TRUE;

#if defined _TINYAN3DLIB_
	return TRUE;
#endif

	if (m_lpDirectDraw == NULL) return FALSE;
	if (m_fullScreenFlag)
	{
		if (m_lpDirectDraw->SetCooperativeLevel(m_hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN) != DD_OK) return FALSE;
		if (m_lpDirectDraw->SetDisplayMode(m_sizeX, m_sizeY, m_col,0,0) != DD_OK) return FALSE;
	}
	else
	{
		if (m_lpDirectDraw->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL) != DD_OK) return FALSE;
	}


	if (m_lpFront == NULL) return FALSE;
	if (m_lpFront->IsLost() == DDERR_SURFACELOST)
	{
		m_lpFront->Restore();
	}

	if (m_lpBack != NULL)
	{
		if (m_lpBack->IsLost() == DDERR_SURFACELOST)
		{
			m_lpBack->Restore();
			ClearBackSurface();

		}
	}

	return TRUE;
}


BOOL CMyDirectDraw::WindowIsMoved(int x, int y)
{
	if (m_direct2DFlag)
	{
		if (m_direct2DFlag)
		{
			return m_direct2D->WindowIsMoved(x, y);
		}
		return TRUE;//@@@
	}

	if (m_notUseDirectDraw) return TRUE;

#if defined _TINYAN3DLIB_
	return TRUE;
#endif

	if (m_fullScreenFlag) return FALSE;


	m_edgeX = GetSystemMetrics(SM_CXFIXEDFRAME );
	m_edgeY = GetSystemMetrics(SM_CYFIXEDFRAME );

	m_edgeX = CMainControl::GetClientOffsetX();
	m_edgeY = CMainControl::GetClientOffsetY();


	long style = GetWindowLong(m_hWnd,GWL_STYLE);
//	if (style & WS_OVERLAPPED)
	if (style & WS_CAPTION)
	{
		m_menuBarY = GetSystemMetrics(SM_CYCAPTION);
	}
	else
	{
		m_menuBarY = 0;
	}

	if ((style & (WS_BORDER)) == 0)
	{
		m_edgeX = 0;
		m_edgeY = 0;
	}


	RECT rc;
	GetWindowRect(m_hWnd,&rc);

	m_printX = x;
	m_printY = y;

	m_printX = rc.left;// +m_edgeX;
	m_printY = rc.top;// +m_edgeY;// +m_menuBarY;



	return TRUE;
}

HDC CMyDirectDraw::GetMyDC(void)
{
	if (m_direct2DFlag)
	{
		if (m_direct2DFlag)
		{
			return m_direct2D->GetMyDC();
		}

		return NULL;//@@@
	}

	if (m_notUseDirectDraw) return NULL;

#if defined _TINYAN3DLIB_
	return NULL;
#endif

	HDC hdc = NULL;
	if (m_fullScreenFlag)
	{
		m_lpBack->GetDC(&hdc);
	}
	else
	{
		m_lpBack->GetDC(&hdc);
	}
	return hdc;

}

void CMyDirectDraw::ReleaseMyDC(HDC hdc)
{
	if (m_direct2DFlag)
	{
		if (m_direct2DFlag)
		{
			m_direct2D->ReleaseMyDC(hdc);
		}

		return;//@@@
	}


	if (m_notUseDirectDraw) return;

#if defined _TINYAN3DLIB_
	return;
#endif

	if (hdc == NULL) return;
	if (m_fullScreenFlag)
	{
		m_lpBack->ReleaseDC(hdc);
	}
	else
	{
		m_lpBack->ReleaseDC(hdc);
	}
}


void CMyDirectDraw::SetWindowSize(int x, int y)
{


//	if (m_notUseDirectDraw) return;

#if defined _TINYAN3DLIB_
	return;
#endif

	m_windowSizeX = x;
	m_windowSizeY = y;
}

void CMyDirectDraw::SetWindowStart(POINT pt)
{


//	if (m_notUseDirectDraw) return TRUE;

#if defined _TINYAN3DLIB_
	return;
#endif
	m_windowStartX = pt.x;
	m_windowStartY = pt.y;
}

void CMyDirectDraw::SetWindowEnd(POINT pt)
{


#if defined _TINYAN3DLIB_
	return;
#endif
	m_windowEndX = pt.x;
	m_windowEndY = pt.y;
}

BOOL CMyDirectDraw::Check565Mode(void)
{

#if defined _TINYAN3DLIB_
	return FALSE;
#endif

	if (m_565Flag) return TRUE;
	if (m_555Flag) return FALSE;

	return TRUE;	//???
}


BOOL CMyDirectDraw::CheckRGB24Mode(void)
{
#if defined _TINYAN3DLIB_
	return FALSE;
#endif

	return m_RGB24Flag;
}

BOOL CMyDirectDraw::CheckRGB32Mode(void)
{

#if defined _TINYAN3DLIB_
	return TRUE;
#endif

	return m_RGB32Flag;
}


void CMyDirectDraw::ErrorLog(LPSTR mes)
{
#if defined _TINYAN3DLIB_
	return;
#endif

	FILE* file = CMyFile::Open("dxerrorlog.txt","ab");
	if (file != NULL)
	{
		fwrite(mes,sizeof(char),strlen(mes),file);
		fwrite("\x00d\x00a",sizeof(char),2,file);
		fclose(file);
	}
}

void CMyDirectDraw::ClearBackSurface(void)
{
	if (m_direct2DFlag)
	{
		if (m_direct2DFlag)
		{
			m_direct2D->ClearBackSurface();
		}

		return;//@@@
	}

	if (m_lpBack == NULL) return;

	if (Lock())
	{


		int sz = m_bitCount / 8;
		int sizeX = sz * m_sizeX;

		unsigned char* ptr = (unsigned char*)m_addr;

		unsigned char col0 = 0;
		unsigned char col1 = 0;
		unsigned char col2 = 0;
		unsigned char col3 = 0;

		int type = 0;
		if ((m_fillColorR == 0) && (m_fillColorG == 0) && (m_fillColorB == 0))
		{
		}
		else
		{
			type = sz;
			col0 = m_fillColorB;
			col1 = m_fillColorG;
			col2 = m_fillColorR;
			col3 = 0;

			if (m_bitCount == 2)
			{
				int col = 0;

				if (m_565Flag)
				{
					col = (m_fillColorB >> 3) | ((m_fillColorG >> 2) << 5) | ((m_fillColorR >> 3) << 11);
				}
				else if (m_555Flag)
				{
					col = (m_fillColorB >> 3) | ((m_fillColorG >> 3) << 5) | ((m_fillColorR >> 3) << 10);
				}

				col0 = col & 0xff;
				col1 = (col >> 8) & 0xff;
			}
		}

		unsigned char* ptr0 = ptr;
		for (int j=0;j<m_sizeY;j++)
		{
			ptr = ptr0;

		//	memset(ptr,0x55,sizeX);
			if (type == 0)
			{
				ZeroMemory(ptr,sizeX);
			}
			else if (type == 2)
			{
				for (int i=0;i<m_sizeX;i++)
				{
					*ptr = col0;
					ptr++;
					*ptr = col1;
					ptr++;
				}
			}
			else if (type == 3)
			{
				for (int i=0;i<m_sizeX;i++)
				{
					*ptr = col0;
					ptr++;
					*ptr = col1;
					ptr++;
					*ptr = col2;
					ptr++;
				}
			}
			else if (type == 4)
			{
				for (int i=0;i<m_sizeX;i++)
				{
					*ptr = col0;
					ptr++;
					*ptr = col1;
					ptr++;
					*ptr = col2;
					ptr++;
					*ptr = col3;
					ptr++;
				}
			}

			ptr0 += m_lPitch;
		}

		Unlock();
	}
}

void CMyDirectDraw::SetOutColor(int r,int g,int b)
{

	m_fillColorR = r;
	m_fillColorG = g;
	m_fillColorB = b;
}


/*_*/

