//
// mainControl.cpp
//

#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <stdlib.h>

#include <math.h>

#include <time.h>
#include <WINNLS32.H>

#include "..\..\systemNNN\nnnlib\wm_user.h"

//#include <crtdbg.h>
//#include "resource.h"

#include "..\..\systemNNN\nyanLib\include\commonmacro.h"
#include "..\..\systemNNN\nnnUtilLib\wheelMouse.h"

#include "..\..\systemNNN\nnnUtilLib\mySaveFolder.h"

#include "baseApp.h"

CBaseApp* CBaseApp::m_this = NULL;

CWheelMouse* CBaseApp::m_wheelMouse = NULL;

char CBaseApp::m_defaultMutexName[] = "nyanBaseAppMutex";
char CBaseApp::m_defaultClassName[] = "nyanBaseAppClass";
char CBaseApp::m_defaultIconName[] = "ICON";
char CBaseApp::m_defaultTooltipMessage[] = "MiniApp";

char CBaseApp::m_defaultFolder[] = "sav";
char CBaseApp::m_defaultFilename[] = "miniapp.sav";

#define MYMSG_TRAY WM_USER
#define MYMSG_TRAY_RIGHTCLICK (WM_USER+1)
#define ID_MYTRAY 121


CBaseApp::CBaseApp(HINSTANCE hInstance,int sx,int sy,LPSTR mutexName,LPSTR className,LPSTR iconName)
{
	GetLocalTime(&m_loginTime);

	m_windowSizeX = sx;
	m_windowSizeY = sy;
	m_hInstance = hInstance;
	m_mutexName = m_defaultMutexName;
	m_className = m_defaultClassName;
	m_iconName = m_defaultIconName;

	if (mutexName != NULL)
	{
		m_mutexName = mutexName;
	}
	
	if (className != NULL)
	{
		m_className = className;
	}

	if (iconName != NULL)
	{
		m_iconName = iconName;
	}

	m_wheelMouse = NULL;
	m_icon = NULL;
	m_mutex = NULL;

	m_wheelMoveFlag = FALSE;
	m_wheelMove = 0;

	m_coInitFlag = FALSE;

	m_captureFlag = FALSE;

	m_windowX = 0;
	m_windowY = 0;

	m_backHDC = NULL;
	m_backBitmap = NULL;

	m_popupMenu = NULL;
	m_menuItemKosuu = 0;

	m_trayIconFlag = FALSE;
	m_rightMenuEnable = FALSE;

	m_exitButtonBitmap = NULL;
	m_defaultBitmap = NULL;

	m_exitButtonSizeX = 0;
	m_exitButtonSizeY = 0;
	m_exitButtonAlignX = 0;
	m_exitButtonAlignY = 0;

	m_onExitButton = FALSE;

	m_cursor = NULL;

	m_addButtonKosuu = 0;
	m_addButtonMax = 256;

	m_addButtonZahyo = NULL;
	m_addButtonSize = NULL;

	m_addButtonBitmap = NULL;

	m_addButtonNumber = NULL;
	m_addButtonEnable = NULL;
	m_addButtonExist = NULL;
	m_onAddButton = NULL;

	m_maskPicKosuu = 0;
	m_maskPicKosuuMax = 256;
	m_maskBitmap = NULL;
	m_maskPicSize = NULL;

	m_picKosuu = 0;
	m_picKosuuMax = 256;
	m_picBitmap = NULL;
	m_picSize = NULL;


	m_shakeSleepCount = 0;
	m_turnSleepCount = 0;

	m_shakeSleepTime = 100;
	m_turnSleepTime = 100;
	
	m_shakeCheckMove = 40;
	m_turnCheckMove = 20;
	
	m_shakeCheckTh = 20;
	
	m_turnCheckTh1 = 30;
	m_turnCheckTh2 = 27;

	m_shakeCheckCount = 10;
	m_turnCheckCount = 20;
	m_shakeCount = 0;
	m_turnCount = 0;

	m_shakeLastTh = 0;
	m_turnLastTh = 0;
	m_turnLastDeltaTh = 0;

	m_saveData = NULL;
//	m_saveDataSize = 256;

	m_this = this;

	m_saveType = 0;

	m_saveFolderName = m_defaultFolder;
	m_saveFileName = m_defaultFilename;
	m_saveFolderNameBuffer = NULL;
	m_saveFileNameBuffer = NULL;

	m_saveFileSize = 1024;

	m_dataLoaded = FALSE;
}


CBaseApp::~CBaseApp()
{
	End();
}

void CBaseApp::End(void)
{
	DELETEARRAY(m_saveFolderNameBuffer);
	DELETEARRAY(m_saveFileNameBuffer);

	DELETEARRAY(m_picSize);
	if (m_picBitmap != NULL)
	{
		for (int i=0;i<m_picKosuu;i++)
		{
			HBITMAP bitmap = m_picBitmap[i];
			if (bitmap != NULL)
			{
				DeleteObject(bitmap);
				m_picBitmap[i] = NULL;
			}
		}
		DELETEARRAY(m_picBitmap);
	}

	DELETEARRAY(m_maskPicSize);
	if (m_maskBitmap != NULL)
	{
		for (int i=0;i<m_maskPicKosuu;i++)
		{
			HBITMAP bitmap = m_maskBitmap[i];
			if (bitmap != NULL)
			{
				DeleteObject(bitmap);
				m_maskBitmap[i] = NULL;
			}

		}
		DELETEARRAY(m_maskBitmap);
	}

	DELETEARRAY(m_onAddButton);
	DELETEARRAY(m_addButtonExist);
	DELETEARRAY(m_addButtonEnable);
	DELETEARRAY(m_addButtonNumber);

	if (m_addButtonBitmap != NULL)
	{
		for (int i=0;i<m_addButtonKosuu;i++)
		{
			HBITMAP bitmap = m_addButtonBitmap[i];
			if (bitmap != NULL)
			{
				DeleteObject(bitmap);
				m_addButtonBitmap[i] = NULL;
			}
		}

		DELETEARRAY(m_addButtonBitmap);
	}

	DELETEARRAY(m_addButtonSize);
	DELETEARRAY(m_addButtonZahyo);

	if (m_defaultBitmap != NULL)
	{
		DeleteObject(m_defaultBitmap);
		m_defaultBitmap = NULL;
	}

	if (m_exitButtonBitmap != NULL)
	{
		DeleteObject(m_exitButtonBitmap);
		m_exitButtonBitmap = NULL;
	}

	DeleteTaskIcon();


	if (m_popupMenu != NULL)
	{
		DestroyMenu(m_popupMenu);
		m_popupMenu = NULL;
	}

	if (m_backBitmap != NULL)
	{
		DeleteObject(m_backBitmap);
		m_backBitmap = NULL;
	}

	if (m_backHDC != NULL)
	{
		DeleteDC(m_backHDC);
		m_backHDC = NULL;
	}

	if (m_coInitFlag)
	{
		CoUninitialize();
		m_coInitFlag = FALSE;
	}

	if (m_mutex != NULL)
	{
		Sleep(10);
		ReleaseMutex(m_mutex);
		Sleep(10);
		CloseHandle(m_mutex);
		m_mutex = NULL;
	}

	ENDDELETECLASS(m_wheelMouse);
}


void CBaseApp::GeneralStart(BOOL tray,BOOL rightMenu,LPSTR tooltipMessage)
{
	m_mutex = CreateMutex(NULL,TRUE,m_mutexName);
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		return;
	}

	LoadData();
	m_saveData[0]++;
	m_windowX = m_saveData[1];
	m_windowY = m_saveData[2];

	m_addButtonZahyo = new POINT[m_addButtonMax];
	m_addButtonSize = new SIZE[m_addButtonMax];

	m_addButtonBitmap = new HBITMAP[m_addButtonMax];
	for (int i=0;i<m_addButtonMax;i++)
	{
		m_addButtonBitmap[i] = NULL;
	}

	m_addButtonNumber = new int[m_addButtonMax];
	m_addButtonExist = new BOOL[m_addButtonMax];
	m_addButtonEnable = new BOOL[m_addButtonMax];
	m_onAddButton = new BOOL[m_addButtonMax];

	m_maskPicSize = new SIZE[m_maskPicKosuuMax];
	m_maskBitmap = new HBITMAP[m_maskPicKosuuMax];
	for (int i=0;i<m_maskPicKosuuMax;i++)
	{
		m_maskBitmap[i] = NULL;
	}

	m_picSize = new SIZE[m_picKosuuMax];
	m_picBitmap = new HBITMAP[m_picKosuuMax];
	for (int i=0;i<m_picKosuuMax;i++)
	{
		m_picBitmap[i] = NULL;
	}

	BeforeCreateWindow();


	m_tooltipMessage = m_defaultTooltipMessage;
	if (tooltipMessage != NULL)
	{
		m_tooltipMessage = tooltipMessage;
	}


	m_icon = LoadIcon(m_hInstance,m_iconName);

    WNDCLASS wndclass;

	wndclass.style         = NULL;
    wndclass.lpfnWndProc   = MainWndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.hInstance     = m_hInstance;
    wndclass.hIcon         = m_icon;
    wndclass.hCursor       = NULL;
    wndclass.hbrBackground = NULL;
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = m_className;
    RegisterClass(&wndclass);


	DWORD dwExStyle = WS_EX_TOOLWINDOW;

	LPSTR windowTitle = NULL;

	int windowX = m_windowX;
	int windowY = m_windowY;


	HWND desktop = GetDesktopWindow();
	RECT rc;
	GetWindowRect(desktop,&rc);

//	if (windowX<rc.left) windowX = rc.left;
//	if (windowY<rc.top) windowY = rc.top;
//	if ((windowX+m_windowSizeX) > rc.right) windowX = rc.right - m_windowSizeX;
//	if ((windowY+m_windowSizeY) > rc.bottom) windowY = rc.bottom - m_windowSizeY;




	HWND hWnd = CreateWindowEx(dwExStyle ,m_className,windowTitle,
							//	WS_THICKFRAME |
								WS_POPUP |
								WS_VISIBLE ,
								windowX, windowY, 
								m_windowSizeX,m_windowSizeY,
								NULL, NULL, m_hInstance, NULL );



	m_hWnd = hWnd;


	HDC hdc = GetDC(m_hWnd);
	m_backHDC = CreateCompatibleDC(hdc);
	m_backBitmap = CreateCompatibleBitmap(hdc,m_windowSizeX,m_windowSizeY);
	SelectObject(m_backHDC,m_backBitmap);
	SelectObject(m_backHDC,GetStockObject(WHITE_BRUSH));
	PatBlt(m_backHDC,0,0,m_windowSizeX,m_windowSizeY,PATCOPY);
	ReleaseDC(m_hWnd,hdc);

	//標準背景
	m_defaultBitmap = LoadBitmap(m_hInstance,"SCREEN");

	m_exitButtonBitmap = LoadBitmap(m_hInstance,"EXITBUTTON");
	if (m_exitButtonBitmap != NULL)
	{
		BITMAP bmp;
		GetObject(m_exitButtonBitmap,sizeof(bmp),&bmp);
		m_exitButtonSizeX = (int)(bmp.bmWidth);
		m_exitButtonSizeX /= 4;
		m_exitButtonSizeY = (int)(bmp.bmHeight);
		m_exitButtonAlignX = GetExitButtonAlignX();
		m_exitButtonAlignY = GetExitButtonAlignY();
	}





	PutDefaultScreen();
	PutExitButton();
	PutAllAddButton();

	m_cursor = LoadCursor(m_hInstance,"CURSOR");
	if (m_cursor == NULL)
	{
		m_cursor = LoadCursor(0,IDC_ARROW);
	}

	CoInitialize(NULL);
	m_coInitFlag = TRUE;

    ShowWindow( hWnd, SW_SHOW );
	SetFocus(hWnd);


	AfterCreateWindow();

	if (tray)
	{
		NOTIFYICONDATA ncd;
		ncd.cbSize = sizeof(NOTIFYICONDATA);
		ncd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		ncd.hIcon = m_icon;
		ncd.hWnd = m_hWnd;
		ncd.uCallbackMessage = MYMSG_TRAY;
		ncd.uID = ID_MYTRAY;
		memcpy(ncd.szTip,m_tooltipMessage,strlen(m_tooltipMessage)+1);

		Shell_NotifyIcon(NIM_ADD,&ncd);
		m_trayIconFlag = TRUE;
	}


	m_rightMenuEnable = rightMenu;


	m_popupMenu = CreatePopupMenu();
	if (tray)
	{
		AddMenu("表示",1);
		AddMenu("隠す",2);
		AddSeparator();
	}
	AddMenu("終了",3);





	TIMECAPS	tc ;
	timeGetDevCaps( &tc , sizeof(TIMECAPS) );

	/* マルチメディアタイマーのサービス精度を最大に */
	timeBeginPeriod( tc.wPeriodMin );

	int oldTime = (int)timeGetTime();
	int oldTime0 = oldTime;

	MSG msg;
	int sleepFlag = 0;

	int frame = 20;
	while(1)
	{
		if ( PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) )
		{
			if ( !GetMessage(&msg,NULL,0,0) )
			{
				break;
			}

//			m_game->GameProc(hWnd,msg.message,msg.wParam,msg.lParam);
//			if (!IsDialogMessage(hChat,&msg))
//			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
//			}

		}
		else
		{
			int tm = (int)timeGetTime();

			if ((tm - oldTime) >= (frame - 5))			
			{
				if (m_shakeSleepCount > 0) m_shakeSleepCount--;
				if (m_turnSleepCount > 0) m_turnSleepCount--;

				CheckOutOfWindow();
				GeneralMainLoop(tm - oldTime0);

				int ps = tm - oldTime;
				if (ps<0) ps = 0;
				
				oldTime0 = tm;
				if (ps>=frame)
				{
					oldTime = tm;
				}
				else
				{
					oldTime = tm;
					oldTime += (frame - ps);
				}

//				if (m_game != NULL)
//				{
//					frame = m_game->GetFrameTime();	//可変フレームに対応
//				}

				if (sleepFlag == 0) Sleep(1);

				sleepFlag = 0;
			}
			else
			{
//					MsgWaitForMultipleObjectsEx(0,NULL,1,QS_POSTMESSAGE | QS_SENDMESSAGE,0);
//					MsgWaitForMultipleObjects(0,NULL,FALSE,1,QS_POSTMESSAGE | QS_SENDMESSAGE);
				Sleep(1);
				sleepFlag = 1;
			}
		}
	}

	timeEndPeriod( tc.wPeriodMin );

	SetLoginoutTime();
	SaveData();
}

void CBaseApp::GeneralMainLoop(int tm)
{
//	static int aaa = 0;
//	aaa++;
//	aaa %= 50;
//	if (aaa == 0)
//	{
//		OutputDebugString("[1sec]");
//	}
}


BOOL CBaseApp::OnLButtonDown(int x,int y)
{
	return FALSE;
}

BOOL CBaseApp::OnRButtonDown(int x,int y)
{
	return FALSE;
}

HRESULT CBaseApp::GameProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int xPos,yPos;
	int wheel = 0;

	switch (message)
	{
	case WM_SETCURSOR:
		SetCursor(m_cursor);
		break;

	case WM_MOUSEWHEEL:
		xPos = (int)(short) LOWORD(lParam);    // horizontal position 
		yPos = (int)(short) HIWORD(lParam);    // vertical position 
		wheel = (int)(short)HIWORD(wParam);
		OnWheel(wheel,xPos,yPos);
//		if (m_wheelWaitCount<=0)	
//		{
//			m_wheelMove = (int)(short)HIWORD(wParam);
//			m_wheelMoveFlag = TRUE;
//		}
		break;

	case WM_LBUTTONDOWN:
		xPos = (int)(short) LOWORD(lParam);    // horizontal position 
		yPos = (int)(short) HIWORD(lParam);    // vertical position 
		if (CheckOnExitButton(xPos,yPos))
		{
			PostMessage(m_hWnd,WM_CLOSE,0,0);
			return 0;
		}
		else if (CheckAddButtonDown(xPos,yPos))
		{
			return 0;
		}
		else if (OnLButtonDown(xPos,yPos) == FALSE)
		{
			//window drag mode start!
			m_captureFlag = TRUE;

			POINT point;
			point.x = xPos;
			point.y = yPos;
			ClientToScreen(hwnd,&point);
			m_oldCaptureX = point.x;
			m_oldCaptureY = point.y;

			SetCapture(hwnd);
		}
//		if (m_mouseStatus != NULL)
//		{
//			m_mouseStatus->SetTrig(0);
//		}
//		m_trig1 = TRUE;
//		m_downed1 = TRUE;
		break;
	case WM_RBUTTONDOWN:
		xPos = (int)(short) LOWORD(lParam);    // horizontal position 
		yPos = (int)(short) HIWORD(lParam);    // vertical position 
		if (m_rightMenuEnable)
		{
			POINT point;
			point.x = xPos;
			point.y = yPos;
			ClientToScreen(hwnd,&point);

			PopupMenuRoutine(hwnd,point);
		}
		else
		{
			OnRButtonDown(xPos,yPos);
		}

//		if (m_mouseStatus != NULL)
//		{
//			m_mouseStatus->SetTrig(1);
//		}
//		m_trig2 = TRUE;
//		m_downed2 = TRUE;
		break;
	case WM_MBUTTONDOWN:
//		if (m_mouseStatus != NULL)
//		{
//			m_mouseStatus->SetTrig(2);
//		}
//		m_trig3 = TRUE;
//		m_downed3 = TRUE;
		break;

	case WM_LBUTTONUP:
		ReleaseCapture();
		m_captureFlag = FALSE;
//OutputDebugString("↑");
//		if (m_mouseStatus != NULL)
//		{
//			m_mouseStatus->SetTrig(0,FALSE);
//		}

		break;
	case WM_RBUTTONUP:
//		if (m_mouseStatus != NULL)
//		{
//			m_mouseStatus->SetTrig(1,FALSE);
//		}

		break;
	case WM_MBUTTONUP:
//		if (m_mouseStatus != NULL)
//		{
//			m_mouseStatus->SetTrig(2,FALSE);
//		}

		break;



	case WM_CLOSE:
		DeleteTaskIcon();
		Sleep(100);
//		PostQuitMessage();
//		EndGame();
		break;

	case WM_MOUSEMOVE:
		if (m_captureFlag)
		{
			xPos = (int)(short) LOWORD(lParam);    // horizontal position 
			yPos = (int)(short) HIWORD(lParam);    // vertical position 
			POINT point;
			point.x = xPos;
			point.y = yPos;
			ClientToScreen(hwnd,&point);

			int dx = point.x - m_oldCaptureX;
			int dy = point.y - m_oldCaptureY;

			m_windowX += dx;
			m_windowY += dy;

			MoveWindow(hwnd,m_windowX,m_windowY,m_windowSizeX,m_windowSizeY,TRUE);
			m_oldCaptureX = point.x;
			m_oldCaptureY = point.y;

			if (CheckShakeWindow(dx,dy))
			{
				if (m_saveData != NULL)
				{
					m_saveData[4]++;
				}
				OnShakeWindow(point.x,point.y);
			}

			if (CheckTrunWindow(dx,dy))
			{
				if (m_saveData != NULL)
				{
					m_saveData[5]++;
				}
				OnTurnWindow(point.x,point.y);
			}
		}
		else
		{
			xPos = (int)(short) LOWORD(lParam);    // horizontal position 
			yPos = (int)(short) HIWORD(lParam);    // vertical position 
			CheckAndReprintExitButton(xPos,yPos);
			CheckAndReprintAddButton(xPos,yPos);
		}


/*
		if (m_mouseStatus != NULL)
		{
			m_mouseStatus->SetZahyo( LOWORD(lParam), HIWORD(lParam) );
		
			if (wParam & MK_LBUTTON)
			{
				if (m_mouseStatus->GetTrig(0) == FALSE)
				{
					m_mouseStatus->SetTrigOnly(0);
	//				m_downed1 = TRUE;
				}
			}
			else
			{
				if (m_mouseStatus->GetTrig(0))
				{
					m_mouseStatus->SetTrig(0,FALSE);
				}
			}

			if (wParam & MK_RBUTTON)
			{
				if (m_mouseStatus->GetTrig(1) == FALSE)
				{
					m_mouseStatus->SetTrigOnly(1);
	//				m_downed2 = TRUE;
				}
			}
			else
			{
				if (m_mouseStatus->GetTrig(1))
				{
					m_mouseStatus->SetTrig(1,FALSE);
				}
			}

			if (wParam & MK_MBUTTON)
			{
				if (m_mouseStatus->GetTrig(2) == FALSE)
				{
					m_mouseStatus->SetTrigOnly(2);
	//				m_downed3 = TRUE;
				}
			}
			else
			{
				if (m_mouseStatus->GetTrig(2))
				{
					m_mouseStatus->SetTrig(2,FALSE);
				}
			}
		}
*/
		break;


	case WM_PAINT:
		if (1)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd,&ps);
			BitBlt(hdc,0,0,m_windowSizeX,m_windowSizeY,m_backHDC,0,0,SRCCOPY);
			EndPaint(hwnd,&ps);
			return 0;
		}

		/*
		RECT updateRect;
		RECT rcMax;
		int screenSizeX;
		int screenSizeY;
		screenSizeX = CMyGraphics::GetScreenSizeX();
		screenSizeY = CMyGraphics::GetScreenSizeY();

		SetRect(&rcMax,0,0,screenSizeX,screenSizeY);
		if (GetUpdateRect(hWnd,NULL,FALSE))
		{
			GetUpdateRect(hWnd,&updateRect,FALSE);
			if (IntersectRect(&updateRect,&updateRect,&rcMax))
			{
				YoyakuArea(&updateRect);
			}
		}
		else
		{
				YoyakuArea(&rcMax);
		}
		*/

		break;



	case WM_MOVE:
		xPos = (int)(short) LOWORD(lParam);    // horizontal position 
		yPos = (int)(short) HIWORD(lParam);    // vertical position 
		if (m_saveData != NULL)
		{
			m_saveData[1] = xPos;
			m_saveData[2] = yPos;
		}
/*		
		if (GetSystemParam(NNNPARAM_SCREENMODE) == 0)
		{
			if (!IsZoomed(m_hWnd))
			{
				m_windowX = xPos;
				m_windowY = yPos;

				m_systemFile->m_systemdata.windowX = m_windowX;
				m_systemFile->m_systemdata.windowY = m_windowY;

				CAreaControl::SetNextAllPrint();
			}
		}
*/

		break;

		/*
	case MYMSG_TRAY_RIGHTCLICK:
		if (1)
		{
			Sleep(100);
			SetForegroundWindow(hwnd);
			POINT pt;
			GetCursorPos(&pt);
			int rt = TrackPopupMenu(m_popupMenu,TPM_TOPALIGN | TPM_LEFTBUTTON ,pt.x,pt.y,0,hwnd,NULL);
		}

		OutputDebugString("[USER+1]");
		break;
*/

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostMessage(hwnd,WM_CLOSE,0,0);
		}

		break;

	case MYMSG_TRAY:
		if (wParam == ID_MYTRAY)
		{
			if (lParam == WM_RBUTTONUP)
			{
				POINT pt;
				GetCursorPos(&pt);
				PopupMenuRoutine(hwnd,pt);
			}
			else if (lParam == WM_LBUTTONDBLCLK)
			{
				//??
			}
		}
		return 0;
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

void CBaseApp::PopupMenuRoutine(HWND hwnd,POINT pt)
{
	SetForegroundWindow(hwnd);
	int rt = TrackPopupMenu(m_popupMenu,TPM_TOPALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD ,pt.x,pt.y,0,hwnd,NULL);

	if (rt == 1)
	{
		ShowWindow(hwnd,SW_SHOW);
	}
	else if (rt == 2)
	{
		ShowWindow(hwnd,SW_HIDE);
	}
	else if (rt == 3)
	{
		PostMessage(hwnd,WM_CLOSE,0,0);
	}
	else if (rt > 3)
	{
	}
}

void CBaseApp::BeforeCreateWindow(void)
{
	//virtual dummy routine
}

void CBaseApp::AfterCreateWindow(void)
{
	//virtual dummy routine
}


LRESULT CALLBACK CBaseApp::MainWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_wheelMouse != NULL)
	{
		message = m_wheelMouse->TranslateMessage(message);
	}

	if (message == WM_DESTROY)
	{
//		if (m_windowChangingFlag == FALSE)
//		{
			ShowWindow(hWnd,SW_HIDE);
			PostQuitMessage(0);
			return 0;
//		}
	}

	return m_this->GameProc(hWnd,message,wParam,lParam);

	//dummy?
	return DefWindowProc(hWnd, message, wParam, lParam);
	return TRUE;
}


void CBaseApp::AddMenu(LPSTR name,int id)
{
	MENUITEMINFO mif;
	ZeroMemory(&mif,sizeof(mif));
	mif.cbSize = sizeof(mif);

	mif.fMask = MIIM_TYPE | MIIM_ID;
	mif.wID = id;
	mif.fType = MFT_STRING;
	mif.dwTypeData = name;
	mif.cch = strlen(name);

	InsertMenuItem(m_popupMenu,m_menuItemKosuu,TRUE,&mif);
	m_menuItemKosuu++;
}

void CBaseApp::AddSeparator(void)
{
	MENUITEMINFO mif;
	ZeroMemory(&mif,sizeof(mif));
	mif.cbSize = sizeof(mif);

	mif.fMask = MIIM_TYPE;
	mif.fType = MFT_SEPARATOR;

	InsertMenuItem(m_popupMenu,m_menuItemKosuu,TRUE,&mif);

	m_menuItemKosuu++;
}

void CBaseApp::MyPlaySound(LPSTR name)
{
	PlaySound(name,m_hInstance,SND_ASYNC | SND_RESOURCE);
}

void CBaseApp::MyStopSound(void)
{
	PlaySound(NULL,NULL,SND_ASYNC);
}

POINT CBaseApp::GetExitButtonZahyo(void)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;

	pt.x = m_exitButtonX;
	pt.y = m_exitButtonY;

	if (m_exitButtonAlignX == 1)
	{
		pt.x = m_windowSizeX / 2 - m_exitButtonSizeX / 2;
	}
	else if (m_exitButtonAlignX == 2)
	{
		pt.x = m_windowSizeX - m_exitButtonSizeX - m_exitButtonX;
	}

	if (m_exitButtonAlignY == 1)
	{
		pt.y = m_windowSizeY / 2 - m_exitButtonSizeY / 2;
	}
	else if (m_exitButtonAlignY == 2)
	{
		pt.y = m_windowSizeY - m_exitButtonSizeY - m_exitButtonY;
	}

	return pt;
}

BOOL CBaseApp::CheckOnAddButton(int n,int x,int y)
{
	if (m_addButtonExist[n] == FALSE) return FALSE;
	if (m_addButtonEnable[n] == FALSE) return FALSE;

	int dx = x-m_addButtonZahyo[n].x;
	int dy = y-m_addButtonZahyo[n].y;
	int sizeX = m_addButtonSize[n].cx;
	int sizeY = m_addButtonSize[n].cy;
	
	if ((dx>=0) && (dx<sizeX) && (dy>=0) && (dy<sizeY))
	{
		return TRUE;
	}

	return FALSE;
}


BOOL CBaseApp::CheckOnExitButton(int x,int y)
{
	if (m_exitButtonBitmap == NULL)
	{
		return FALSE;
	}

	POINT pt = GetExitButtonZahyo();
	int dx = x - pt.x;
	int dy = y - pt.y;
	if ((dx>=0) && (dx<m_exitButtonSizeX) && (dy>=0) && (dy<m_exitButtonSizeY))
	{
		return TRUE;
	}

	return FALSE;
}

void CBaseApp::PutDefaultScreen(void)
{
	if (m_defaultBitmap == NULL)
	{
		return;
	}

	int putX = 0;
	int putY = 0;
	int sizeX = m_windowSizeX;
	int sizeY = m_windowSizeY;
	int srcX = 0;
	int srcY = 0;

	HDC hdc = CreateCompatibleDC(m_backHDC);
	SelectObject(hdc,m_defaultBitmap);
	BitBlt(m_backHDC,putX,putY,sizeX,sizeY,hdc,srcX,srcY,SRCCOPY);
	RECT rc;
	rc.left = putX;
	rc.top = putY;
	rc.right = putX + sizeX;
	rc.bottom = putY + sizeY;
	InvalidateRect(m_hWnd,&rc,FALSE);
	DeleteDC(hdc);

}

void CBaseApp::PutAllAddButton(void)
{
	for (int i=0;i<m_addButtonKosuu;i++)
	{
		if (m_addButtonExist[i])
		{
			int md = 0;
			if (m_addButtonEnable[i] == FALSE)
			{
				md = 3;
			}
			else
			{
				if (m_onAddButton[i])
				{
					md = 1;
				}
			}
			PutAddButton(i,md);
		}
	}
}

void CBaseApp::PutExitButton(int md)
{
	if (m_exitButtonBitmap == NULL)
	{
		return;
	}

	POINT pt = GetExitButtonZahyo();
	int putX = pt.x;
	int putY = pt.y;
	int sizeX = m_exitButtonSizeX;
	int sizeY = m_exitButtonSizeY;
	int srcX = md * sizeX;
	int srcY = 0;
	
	HDC hdc = CreateCompatibleDC(m_backHDC);
	SelectObject(hdc,m_exitButtonBitmap);
	BitBlt(m_backHDC,putX,putY,sizeX,sizeY,hdc,srcX,srcY,SRCCOPY);
	RECT rc;
	rc.left = putX;
	rc.top = putY;
	rc.right = putX + sizeX;
	rc.bottom = putY + sizeY;
	InvalidateRect(m_hWnd,&rc,FALSE);
	DeleteDC(hdc);

}

void CBaseApp::PrintAddButton(int btn,int md,BOOL updateFlag)
{
	int n = SearchButton(btn);
	if (n == -1) return;
	PutAddButton(n,md);
	if (updateFlag)
	{
		RECT rc;
		rc.left = m_addButtonZahyo[n].x;
		rc.top = m_addButtonZahyo[n].y;
		rc.right = rc.left + m_addButtonSize[n].cx;
		rc.bottom = rc.top + m_addButtonSize[n].cy;
		InvalidateRect(m_hWnd,&rc,FALSE);

	}
}


void CBaseApp::PutAddButton(int n,int md)
{
	if (m_addButtonBitmap[n] == NULL)
	{
		return;
	}
	if (m_addButtonExist[n] == FALSE) return;

	int putX = m_addButtonZahyo[n].x;
	int putY = m_addButtonZahyo[n].y;
	int sizeX = m_addButtonSize[n].cx;
	int sizeY = m_addButtonSize[n].cy;
	int srcX = md * sizeX;
	int srcY = 0;
	
	HDC hdc = CreateCompatibleDC(m_backHDC);
	SelectObject(hdc,m_addButtonBitmap[n]);
	BitBlt(m_backHDC,putX,putY,sizeX,sizeY,hdc,srcX,srcY,SRCCOPY);
	RECT rc;
	rc.left = putX;
	rc.top = putY;
	rc.right = putX + sizeX;
	rc.bottom = putY + sizeY;
	InvalidateRect(m_hWnd,&rc,FALSE);
	DeleteDC(hdc);
}


BOOL CBaseApp::CheckAndReprintAddButton(int x,int y)
{
	BOOL flg = FALSE;

	for (int i=0;i<m_addButtonKosuu;i++)
	{
		if (m_addButtonExist[i])
		{
			if (m_addButtonEnable[i])
			{
				BOOL old = m_onAddButton[i];
				m_onAddButton[i] = CheckOnAddButton(i,x,y);

				if (old != m_onAddButton[i])
				{
					int md = 0;
					if (m_onAddButton[i])
					{
						md = 1;
					}
					PutAddButton(i,md);
					flg = TRUE;
				}
			}
		}
	}

	return flg;
}

BOOL CBaseApp::CheckAndReprintExitButton(int x,int y)
{

	BOOL old = m_onExitButton;
	m_onExitButton = CheckOnExitButton(x,y);

	BOOL flg = FALSE;
	if (old != m_onExitButton)
	{
		int md = 0;
		if (m_onExitButton)
		{
			md = 1;
		}
		PutExitButton(md);
		flg = TRUE;
	}

	return flg;
}


void CBaseApp::CheckOutOfWindow(void)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd,&pt);

	int x = pt.x;
	int y = pt.y;

	if ((x<0) || (x>=m_windowSizeX) || (y<0) || (y>=m_windowSizeY))
	{
		CheckAndReprintExitButton(pt.x,pt.y);
		CheckAndReprintAddButton(pt.x,pt.y);
	}

}


int CBaseApp::AddButton(LPSTR name,int x,int y,int n,int sizeX,int sizeY)
{
	if (m_addButtonKosuu >= m_addButtonMax) return -1;
	
	if (x==-1)
	{
		x = 0;
		y = 0;
		if (m_addButtonKosuu>0)
		{
			x = m_addButtonZahyo[m_addButtonKosuu-1].x;
			y = m_addButtonZahyo[m_addButtonKosuu-1].y;
			x += m_addButtonSize[m_addButtonKosuu-1].cx;
		}
	}

	if (n == -1)
	{
		n = m_addButtonKosuu+1;
	}

	


	m_addButtonBitmap[m_addButtonKosuu] = LoadBitmap(m_hInstance,name);



	if (sizeX == -1)
	{
		if (m_addButtonBitmap[m_addButtonKosuu] != NULL)
		{
			BITMAP bmp;
			GetObject(m_addButtonBitmap[m_addButtonKosuu],sizeof(bmp),&bmp);
			sizeX = (int)(bmp.bmWidth);
			sizeX /= 4;
			sizeY = (int)(bmp.bmHeight);
		}
		else
		{
			sizeX = 16;
			sizeY = 16;
		}
	}

	m_addButtonZahyo[m_addButtonKosuu].x = x;
	m_addButtonZahyo[m_addButtonKosuu].y = y;
	m_addButtonSize[m_addButtonKosuu].cx = sizeX;
	m_addButtonSize[m_addButtonKosuu].cy = sizeY;

	m_addButtonEnable[m_addButtonKosuu] = TRUE;
	m_addButtonExist[m_addButtonKosuu] = TRUE;
	m_addButtonNumber[m_addButtonKosuu] = n;
	m_onAddButton[m_addButtonKosuu] = FALSE;

	m_addButtonKosuu++;
	return n;
}

BOOL CBaseApp::CheckAddButtonDown(int x,int y)
{
	for (int i=0;i<m_addButtonKosuu;i++)
	{
		if (m_addButtonExist[i])
		{
			if (m_addButtonEnable[i])
			{
				int dx = x - m_addButtonZahyo[i].x;
				int dy = y - m_addButtonZahyo[i].y;
				int sizeX = m_addButtonSize[i].cx;
				int sizeY = m_addButtonSize[i].cy;
				if ((dx>=0) && (dx<sizeX) && (dy>=0) && (dy<sizeY))
				{
					if (OnAddButtonDown(m_addButtonNumber[i]))
					{
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL CBaseApp::OnAddButtonDown(int n)
{
	return TRUE;
}


void CBaseApp:: SetAddButtonEnable(int n,BOOL flg)
{
	int btn = SearchButton(n);
	if (btn == -1) return;

	m_addButtonEnable[btn] = flg;
}

void CBaseApp::SetAddButtonExist(int n,BOOL flg)
{
	int btn = SearchButton(n);
	if (btn == -1) return;

	m_addButtonExist[btn] = flg;
}

BOOL CBaseApp::GetAddButtonEnable(int n)
{
	int btn = SearchButton(n);
	if (btn == -1) return FALSE;

	if (m_addButtonExist[btn] == FALSE) return FALSE;
	return m_addButtonEnable[btn];
}

BOOL CBaseApp::GetAddButtonExist(int n)
{
	int btn = SearchButton(n);
	if (btn == -1) return FALSE;

	return m_addButtonExist[btn];
}

int CBaseApp::SearchButton(int n)
{
	for (int i=0;i<m_addButtonKosuu;i++)
	{
		if (m_addButtonNumber[i] == n) return i;
	}

	return -1;
}

int CBaseApp::LoadMaskPic(LPSTR name)
{
	if (m_maskPicKosuu >= m_maskPicKosuuMax) return -1;

	m_maskBitmap[m_maskPicKosuu] = LoadBitmap(m_hInstance,name);
	if (m_maskBitmap[m_maskPicKosuu] == NULL) return -1;

	int sizeX = 16;
	int sizeY = 16;

	BITMAP bmp;
	GetObject(m_maskBitmap[m_maskPicKosuu],sizeof(bmp),&bmp);
	sizeX = (int)(bmp.bmWidth);
	sizeX /= 2;
	sizeY = (int)(bmp.bmHeight);

	m_maskPicSize[m_maskPicKosuu].cx = sizeX;
	m_maskPicSize[m_maskPicKosuu].cy = sizeY;

	int n = m_maskPicKosuu;
	m_maskPicKosuu++;
	return n;
}

void CBaseApp::PutMaskPic(int n,int x,int y,BOOL updateFlag)
{
	if ((n < 0) || (n>=m_maskPicKosuu)) return;

	HBITMAP bitmap = m_maskBitmap[n];
	if (bitmap == NULL) return;

	int sizeX = m_maskPicSize[n].cx;
	int sizeY = m_maskPicSize[n].cy;


	HDC hdc = CreateCompatibleDC(m_backHDC);
	SelectObject(hdc,bitmap);
	int srcX = sizeX;
	int srcY = 0;
	BitBlt(m_backHDC,x,y,sizeX,sizeY,hdc,srcX,srcY,SRCAND);
	srcX = 0;
	BitBlt(m_backHDC,x,y,sizeX,sizeY,hdc,srcX,srcY,SRCPAINT);

	DeleteDC(hdc);

	if (updateFlag)
	{
		RECT rc;
		rc.left = x;
		rc.top = y;
		rc.right = x + sizeX;
		rc.bottom = y + sizeY;
		InvalidateRect(m_hWnd,&rc,FALSE);
	}

}

void CBaseApp::BltMaskPic(int n,int x,int y,int srcX,int srcY,int sizeX,int sizeY,BOOL updateFlag)
{
	if ((n < 0) || (n>=m_maskPicKosuu)) return;

	HBITMAP bitmap = m_maskBitmap[n];
	if (bitmap == NULL) return;

	int picSizeX = m_maskPicSize[n].cx;
	int picSizeY = m_maskPicSize[n].cy;


	HDC hdc = CreateCompatibleDC(m_backHDC);
	SelectObject(hdc,bitmap);

	srcX += picSizeX;
//	int srcY = 0;
	BitBlt(m_backHDC,x,y,sizeX,sizeY,hdc,srcX,srcY,SRCAND);
	srcX -= picSizeX;
	BitBlt(m_backHDC,x,y,sizeX,sizeY,hdc,srcX,srcY,SRCPAINT);

	DeleteDC(hdc);

	if (updateFlag)
	{
		RECT rc;
		rc.left = x;
		rc.top = y;
		rc.right = x + sizeX;
		rc.bottom = y + sizeY;
		InvalidateRect(m_hWnd,&rc,FALSE);
	}
}


int CBaseApp::LoadPic(LPSTR name)
{
	if (m_picKosuu >= m_picKosuuMax) return -1;

	m_picBitmap[m_picKosuu] = LoadBitmap(m_hInstance,name);
	if (m_picBitmap[m_picKosuu] == NULL) return -1;

	int sizeX = 16;
	int sizeY = 16;

	BITMAP bmp;
	GetObject(m_picBitmap[m_picKosuu],sizeof(bmp),&bmp);
	sizeX = (int)(bmp.bmWidth);
//	sizeX /= 1;
	sizeY = (int)(bmp.bmHeight);

	m_picSize[m_picKosuu].cx = sizeX;
	m_picSize[m_picKosuu].cy = sizeY;

	int n = m_picKosuu;
	m_picKosuu++;
	return n;
}


void CBaseApp::PutPic(int n,int x,int y,BOOL updateFlag)
{
	if ((n < 0) || (n>=m_picKosuu)) return;

	HBITMAP bitmap = m_picBitmap[n];
	if (bitmap == NULL) return;

	int sizeX = m_picSize[n].cx;
	int sizeY = m_picSize[n].cy;


	HDC hdc = CreateCompatibleDC(m_backHDC);
	SelectObject(hdc,bitmap);
	int srcX = 0;
	int srcY = 0;
	BitBlt(m_backHDC,x,y,sizeX,sizeY,hdc,srcX,srcY,SRCCOPY);
//	srcX = 0;
//	BitBlt(m_backHDC,x,y,sizeX,sizeY,hdc,srcX,srcY,SRCPAINT);

	DeleteDC(hdc);

	if (updateFlag)
	{
		RECT rc;
		rc.left = x;
		rc.top = y;
		rc.right = x + sizeX;
		rc.bottom = y + sizeY;
		InvalidateRect(m_hWnd,&rc,FALSE);
	}

}

void CBaseApp::BltPic(int n,int x,int y,int srcX,int srcY,int sizeX,int sizeY,BOOL updateFlag)
{
	if ((n < 0) || (n>=m_picKosuu)) return;

	HBITMAP bitmap = m_picBitmap[n];
	if (bitmap == NULL) return;

//	int sizeX = m_picSize[n].cx;
//	int sizeY = m_picSize[n].cy;


	HDC hdc = CreateCompatibleDC(m_backHDC);
	SelectObject(hdc,bitmap);
//	int srcX = 0;
//	int srcY = 0;
	BitBlt(m_backHDC,x,y,sizeX,sizeY,hdc,srcX,srcY,SRCCOPY);
//	srcX = 0;
//	BitBlt(m_backHDC,x,y,sizeX,sizeY,hdc,srcX,srcY,SRCPAINT);

	DeleteDC(hdc);

	if (updateFlag)
	{
		RECT rc;
		rc.left = x;
		rc.top = y;
		rc.right = x + sizeX;
		rc.bottom = y + sizeY;
		InvalidateRect(m_hWnd,&rc,FALSE);
	}
}

BOOL CBaseApp::ChangeSaveTypeFile(LPSTR filename,LPSTR folderName,int saveFileSize)
{
	if (m_saveType != 0) return FALSE;
	if (m_dataLoaded) return FALSE;

	m_saveType = 1;

	if (folderName != NULL)
	{
		int ln = strlen(folderName);
		m_saveFolderNameBuffer = new char[ln+1];
		memcpy(m_saveFolderNameBuffer,folderName,ln+1);
		m_saveFolderName = m_saveFolderNameBuffer;
	}

	if (filename != NULL)
	{
		int ln = strlen(filename);
		m_saveFileNameBuffer = new char[ln+1];
		memcpy(m_saveFileNameBuffer,filename,ln+1);
		m_saveFileName = m_saveFileNameBuffer;
	}

	if (saveFileSize > 0)
	{
		m_saveFileSize = saveFileSize;
	}

	//load?


	return TRUE;
}


BOOL CBaseApp::ChangeSaveTypeReg(LPSTR companyName,LPSTR gameName, LPSTR dataName,int dataSize)
{
	if (m_saveType != 0) return FALSE;
	if (m_dataLoaded) return FALSE;

	m_saveType = 2;

	if (companyName != NULL)
	{
	}

	if (gameName != NULL)
	{
	}

	if (dataName != NULL)
	{
	}

	if (dataSize > 0)
	{
		
	}



	return FALSE;
}


BOOL CBaseApp::CheckShakeWindow(int dx,int dy)
{
	if (m_shakeSleepCount > 0) return FALSE;

	double l = (double)(dx*dx+dy*dy);
	double lmt = (double)(m_shakeCheckMove*m_shakeCheckMove);
	if (l<lmt)
	{
		return FALSE;
	}

	//vector to th
	double th = atan2((double)dy,(double)dx);
	int thInt = ((int)(360.0 + th*180.0/3.14159 + 0.5)) % 360;

	int deltaTh = (thInt - m_shakeLastTh + 360 - 180 + 360) % 360;
	if (deltaTh > 180)
	{
		deltaTh -= 360;
	}

	m_shakeLastTh = thInt;

	if ((deltaTh >= -m_shakeCheckTh) && (deltaTh <= m_shakeCheckTh))
	{

		m_shakeCount++;
		if (m_shakeCount >= m_shakeCheckCount)
		{
			m_shakeCount = 0;
			m_shakeSleepCount = m_shakeSleepTime;
			return TRUE;
		}
	}



	return FALSE;
}

BOOL CBaseApp::CheckTrunWindow(int dx,int dy)
{
	if (m_turnSleepCount > 0) return FALSE;

	double l = (double)(dx*dx+dy*dy);
	double lmt = (double)(m_turnCheckMove*m_turnCheckMove);
	if (l<lmt)
	{
		return FALSE;
	}

	double th = atan2((double)dy,(double)dx);
	int thInt = ((int)(360.0 + th*180.0/3.14159 + 0.5)) % 360;


	int deltaTh = (thInt - m_turnLastTh + 360) % 360;
	if (deltaTh > 180)
	{
		deltaTh -= 360;
	}

	m_turnLastTh = thInt;
	if (deltaTh == 0) return FALSE;

//char mes[256];
//wsprintf(mes,"\n[check turn %d]",deltaTh);
//OutputDebugString(mes);

	if (m_turnLastDeltaTh == 0)
	{
		m_turnCount++;
		m_turnLastDeltaTh = deltaTh;
	}
	else if (m_turnLastDeltaTh > 0)
	{
		if (deltaTh < 0)
		{
			m_turnCount = 0;
			m_turnLastDeltaTh = deltaTh;
		}
		else
		{
			if (deltaTh > (m_turnCheckTh1 - m_turnCheckTh2))
			{
				if (deltaTh < (m_turnCheckTh1 + m_turnCheckTh2))
				{
//OutputDebugString("*");
					m_turnCount++;
				}
			}
		}
	}
	else
	{
		if (deltaTh > 0)
		{
			m_turnCount = 0;
			m_turnLastDeltaTh = deltaTh;
		}
		else
		{
			if ((-deltaTh) > (m_turnCheckTh1 - m_turnCheckTh2))
			{
				if ((-deltaTh) < (m_turnCheckTh1 + m_turnCheckTh2))
				{
					m_turnCount++;
//OutputDebugString("*");
				}
			}
		}
	}


	if (m_turnCount >= m_turnCheckCount)
	{
		m_turnCount = 0;
		m_turnSleepCount = m_turnSleepTime;
		return TRUE;
	}

	return FALSE;
}


BOOL CBaseApp::LoadData(void)
{
	if (m_saveData == NULL)
	{
		m_saveData = new int[m_saveFileSize / 4 + 1];
	}

	ZeroMemory(m_saveData,m_saveFileSize);

	if (m_saveType == 1)
	{
		char filename[1024];

		LPSTR mySaveFolder = CMySaveFolder::GetFullFolder();
		wsprintf(filename,"%s\\%s",mySaveFolder,m_saveFileName);

//		wsprintf(filename,"%s\\%s",m_saveFolderName,m_saveFileName);
		FILE* file = NULL;

		fopen_s(&file,filename,"rb");
		if (file != NULL)
		{
			fread(m_saveData,sizeof(int),m_saveFileSize / 4,file);
			fclose(file);
			return TRUE;
		}
		return FALSE;
	}

	return FALSE;
}

BOOL CBaseApp::SaveData(void)
{
	if (m_saveData == NULL) return FALSE;//error!!

	if (m_saveType == 1)
	{
		char filename[1024];

		LPSTR mySaveFolder = CMySaveFolder::GetFullFolder();
		wsprintf(filename,"%s\\%s",mySaveFolder,m_saveFileName);

//		wsprintf(filename,"%s\\%s",m_saveFolderName,m_saveFileName);
		FILE* file = NULL;

		fopen_s(&file,filename,"wb");
		if (file != NULL)
		{
			fwrite(m_saveData,sizeof(int),m_saveFileSize / 4,file);
			fclose(file);
			return TRUE;
		}
		return FALSE;
	}

	return FALSE;

}

void CBaseApp::SetExitButtonZahyo(int x,int y,int alignX,int alignY)
{
	m_exitButtonX = x;
	m_exitButtonY = y;
	m_exitButtonAlignX = alignX;
	m_exitButtonAlignY = alignY;
}

void CBaseApp::SetLoginoutTime(void)
{
	SYSTEMTIME logoutTime;
	GetLocalTime(&logoutTime);

	if (m_saveData != NULL)
	{
		m_saveData[16+0] = m_loginTime.wYear;
		m_saveData[16+1] = m_loginTime.wMonth;
		m_saveData[16+2] = m_loginTime.wDay;
		m_saveData[16+3] = m_loginTime.wDayOfWeek;
		m_saveData[16+4] = m_loginTime.wHour;
		m_saveData[16+5] = m_loginTime.wMinute;
		m_saveData[16+6] = m_loginTime.wSecond;
		m_saveData[16+7] = m_loginTime.wMilliseconds;

		m_saveData[32+0] = logoutTime.wYear;
		m_saveData[32+1] = logoutTime.wMonth;
		m_saveData[32+2] = logoutTime.wDay;
		m_saveData[32+3] = logoutTime.wDayOfWeek;
		m_saveData[32+4] = logoutTime.wHour;
		m_saveData[32+5] = logoutTime.wMinute;
		m_saveData[32+6] = logoutTime.wSecond;
		m_saveData[32+7] = logoutTime.wMilliseconds;
	}
}


int CBaseApp::GetIntervalMinute(void)
{
	if (m_saveData[0] <= 1) return -1;

	int year1 = m_saveData[32+0];
	int month1 = m_saveData[32+1];
	int day1 = m_saveData[32+2];
	int hour1 = m_saveData[32+4];
	int minute1 = m_saveData[32+5];

	int year2 = m_loginTime.wYear;
	int month2 = m_loginTime.wMonth;
	int day2 = m_loginTime.wDay;
	int hour2 = m_loginTime.wHour;
	int minute2 = m_loginTime.wMinute;

	//簡易計算
	LONGLONG past1 = (LONGLONG)year1 * 365*30*24*60 + (LONGLONG)month1 * 30*24*60 + (LONGLONG)day1 * 24*60 + (LONGLONG)hour1 * 60 + (LONGLONG)minute1;
	LONGLONG past2 = (LONGLONG)year2 * 365*30*24*60 + (LONGLONG)month2 * 30*24*60 + (LONGLONG)day2 * 24*60 + (LONGLONG)hour2 * 60 + (LONGLONG)minute2;

	LONGLONG past = past2 - past1;

	return (int)past;


}

void CBaseApp::DeleteTaskIcon(void)
{
	if (m_trayIconFlag)
	{
		NOTIFYICONDATA ncd;
		ncd.cbSize = sizeof(NOTIFYICONDATA);
		ncd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		ncd.hIcon = m_icon;
		ncd.hWnd = m_hWnd;
		ncd.uCallbackMessage = MYMSG_TRAY;
		ncd.uID = ID_MYTRAY;
		memcpy(ncd.szTip,m_tooltipMessage,strlen(m_tooltipMessage)+1);

		Shell_NotifyIcon(NIM_DELETE,&ncd);

		m_trayIconFlag = FALSE;
	}

}

void CBaseApp::MyBoxFill(int putX,int putY,int sizeX,int sizeY,int r,int g,int b,BOOL updateFlag)
{
//	HDC hdc = CreateCompatibleDC(m_backHDC);
	HDC hdc = m_backHDC;
	HBRUSH brush = CreateSolidBrush(RGB(r,g,b));
	HGDIOBJ old = SelectObject(hdc,brush);

	RECT rcFill;
	rcFill.left = putX;
	rcFill.top = putY;
	rcFill.right = putX + sizeX;
	rcFill.bottom = putY + sizeY;

	FillRect(hdc,&rcFill,brush);
//	Rectangle(hdc,putX,putY,putX+sizeX,putY+sizeY);
//	PatBlt(hdc,putX,putY,sizeX,sizeY,SRCCOPY);

	if (updateFlag)
	{
		RECT rc;
		rc.left = putX;
		rc.top = putY;
		rc.right = putX + sizeX;
		rc.bottom = putY + sizeY;
		InvalidateRect(m_hWnd,&rc,FALSE);
	}

	SelectObject(hdc,old);
	DeleteObject(brush);
//	DeleteDC(hdc);
}

/*_*/

