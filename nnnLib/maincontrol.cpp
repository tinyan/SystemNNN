//
// mainControl.cpp
//

#include <windows.h>
#include <stdio.h>


#include <process.h>
//#include <stdlib.h>

#include <time.h>
#include <WINNLS32.H>

//#include <crtdbg.h>

//#include "resource.h"

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanDirectXLib\mmx.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myFile.h"

#include "..\nnnUtilLib\commongameVersion.h"

#include "..\nnnUtilLib\nameList.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\mySaveFolder.h"

#include "..\nnnUtilLib\CViewControl.h"

#include "mainControl.h"

#include "..\nnnUtilLib\commonSystemFile.h" 
#include "..\nnnUtilLib\wheelMouse.h"

#include "gameCallBack.h"

#include "wm_user.h"

MSG CMainControl::m_msg;


CWheelMouse* CMainControl::m_wheelMouse = NULL;
CGameCallBack* CMainControl::m_game = NULL;

char CMainControl::m_defaultWindowTitle[] = "nnn�W���v���O����";
char CMainControl::m_defaultWindowTitleTaiken[] = "nnn�W���v���O�����̌���";
char CMainControl::m_defaultWindowTitleNet[] = "nnn�W���v���O�����l�b�g��";
char CMainControl::m_defaultWindowTitleDemo[] = "nnn�W���v���O�����f����";

char CMainControl::m_defaultClassName[] = "nnncommongamebytinyan";
char CMainControl::m_defaultMutexName[] = "NNNCommonGameByTinyan";

char CMainControl::m_nullMessage[] = "";

char CMainControl::m_defaultWindowSizeErrorMessage[] = "��ʃT�C�Y��%dx%d�ȏ�ɐݒ肵�Ă�������";
char CMainControl::m_defaultWindowSizeErrorTitle[] = "Error";

char CMainControl::m_defaultMMXErrorMessage[] = "MMX�@�\�������Ɣ��f����܂���\n���̃}�V���ł̓v���C�ł��Ȃ��Ǝv���܂�\n�Q�[���𒆎~���邱�Ƃ������߂��܂�";
char CMainControl::m_defaultMMXErrorTitle[] = "�x��";

char CMainControl::m_defaultBppErrorMessage[] = "%dbit�J���[�ȏ�ɐݒ肵�Ă�������";
char CMainControl::m_defaultBppErrorTitle[] = "Error";

char CMainControl::m_defaultMutexErrorMessage[] = "��d�N���͂ł��܂���";
char CMainControl::m_defaultMutexErrorTitle[] = "Error";

char CMainControl::m_defaultDirectXErrorMessage[] = "DirectX���C���X�g�[������Ă��Ȃ��\��������܂�\n���̂܂ܑ����܂���";
char CMainControl::m_defaultDirectXErrorTitle[] = "�x��";


int CMainControl::m_clientOffsetX = 0;
int CMainControl::m_clientOffsetY = 0;


CMainControl* CMainControl::m_this = NULL;

BOOL CMainControl::m_windowChangingFlag = TRUE;

CMainControl::CMainControl(CCommonSystemFile* lpSystemFile,CWheelMouse* lpWheel)
{
	m_className = nullptr;

	m_this = this;
	m_windowChangingFlag = FALSE;
	m_systemOk = FALSE;


	m_systemBpp = 32;
	m_randomSeed = 0;
	m_directXErrorTitle = nullptr;
	m_hInstance = nullptr;
	m_directXErrorMessage = nullptr;
	m_directXErrorMustAbortFlag = 0;
	m_bppErrorMustAbortFlag = 0;
	m_checkDirectXFlag = 0;

	
	m_highVersion = 0;
	m_middleVersion = 0;
	m_lowVersion = 0;
	m_mmxErrorMustAbortFlag = 0;
	m_mutexCheckFlag = 0;
	m_needBpp = 32;
	m_desktopWindowSizeX = 800;
	m_desktopWindowSizeY = 600;
	m_desktopWindowStartX = 0;
	m_desktopWindowStartY = 0;
	m_desktopWindowEndX = 800;
	m_desktopWindowEndY = 600;
	m_windowSizeX = 800;
	m_windowSizeY = 600;
	m_hWnd = nullptr;
	m_mutexName = nullptr;
	m_wndclass = WNDCLASS();
	m_bppErrorMessage = nullptr;
	m_bppErrorTitle = nullptr;
	m_mmxErrorMessage = nullptr;
	m_mmxErrorTitle = nullptr;
	m_mutexErrorMessage = nullptr;
	m_mutexErrorTitle = nullptr;
	m_windowSizeErrorMessage = nullptr;
	m_windowSizeErrorMustAbortFlag = 0;
	m_windowSizeErrorTitle = nullptr;
	m_windowTitle = nullptr;

//	memset(m_makedBppErrorMessage, 0, sizeof(m_makedBppErrorMessage));
	//memset m_makedWindowSizeErrorMessage

	for (int i = 0; i < 16; i++)
	{
		m_eventHandle[i] = nullptr;
		m_threadHandle[i] = nullptr;
		m_threadID[i] = 0;
	}

	m_myFile = new CMyFile(TRUE);

	//load setup(mainControl.xtx),setup2(game.xtx)
	m_setup = new CNameList();
	m_setup2 = new CNameList();
	LoadSetupFile("mainControl",256);
	LoadSetupFile2("game",256);


	int folderType = 0;
	GetInitGameParam2(&folderType,"saveFolderType");
	LPSTR saveCompanyFolder = NULL;
	GetInitGameString2(&saveCompanyFolder,"saveCompanyFolder");
	LPSTR saveGameFolder = NULL;
	GetInitGameString2(&saveGameFolder,"saveGameFolder");
	CMySaveFolder::ChangeMyFolder(saveCompanyFolder,saveGameFolder,folderType);


	int createFolderFlag = 1;
	GetInitGameString2(&saveGameFolder,"createSaveFolder");
	if (createFolderFlag)
	{
		CMySaveFolder::CreateSubFolder();
	}



	m_oldUseGeneralFlag = 1;
	GetInitGameParam(&m_oldUseGeneralFlag,"oldUseGeneralFlag");

	m_icon = NULL;
	m_mutex = NULL;
	m_userIcon = NULL;


//	m_frameRate = 50;
//	GetInitGameParam(&m_frameRate,"frameRate");

	m_coInitFlag = FALSE;

	m_createSystemFileFlag = FALSE;
	m_createWheelFlag = FALSE;

	m_syskeyaltoff = 0;
	m_syskeywinoff = 0;
	m_syskeyappsoff = 0;
	GetInitGameParam(&m_syskeyaltoff,"altkeyoff");
	GetInitGameParam(&m_syskeywinoff,"winkeyoff");
	GetInitGameParam(&m_syskeyappsoff,"appskeyoff");

	int immoff = 0;
	GetInitGameParam(&immoff,"IMMOff");
	if (immoff)
	{
		ImmDisableIME(0);
	}

//	int maxCGCharaNumber = -1;
//	int maxScriptNumber = -1;

	BOOL reInitFlag = FALSE;


	int maxCGCharaNumber = 0;
	int maxScriptNumber = 64;

	int i;

	for (i=0;i<256;i++)
	{
		char fname[256];
		int k = i + 1;
		if (k<100)
		{
			wsprintf(fname,"spt\\cglist%d%d.xtx",k / 10,k % 10);
		}
		else
		{
			wsprintf(fname,"spt\\cglist_%d.xtx",k % 10);
			fname[10] = 'A'+((k-100) / 10);
		}

		FILE* file = CMyFile::Open(fname,"rb");
		if (file == NULL)
		{
			break;
		}

		fclose(file);
		maxCGCharaNumber++;
	}


	CCommonSystemFile::SetCGCharaNinzu(maxCGCharaNumber);
	if (maxCGCharaNumber == 0) maxCGCharaNumber = 20;

	if (maxCGCharaNumber != 20)
	{
		CCommonSystemFile::SetMaxCGCharaNumber(maxCGCharaNumber);
		reInitFlag = TRUE;
	}



//	if (GetInitGameParam2(&maxCGCharaNumber,"maxCGCharaNumber"))
//	{
//		if (maxCGCharaNumber != -1)
//		{
//			CCommonSystemFile::SetMaxCGCharaNumber(maxCGCharaNumber);
//			reInitFlag = TRUE;
//		}
//	}

	CNameList* nameList = new CNameList();
	int noScriptFlag = 0;
	GetInitGameParam2(&noScriptFlag,"noScriptFlag");
	maxScriptNumber = 1;
	if (noScriptFlag == 0)
	{
		if (nameList->LoadFile("spt\\project.xtx"))
		{
			maxScriptNumber = nameList->GetNameKosuu();
		}
	}
	ENDDELETECLASS(nameList);

	if (maxScriptNumber == 0) maxScriptNumber = 64;

	if (maxScriptNumber != 64)
	{
		CCommonSystemFile::SetMaxScriptNumber(maxScriptNumber);
		reInitFlag = TRUE;
	}

//	if (GetInitGameParam2(&maxScriptNumber,"maxScriptNumber"))
//	{
//		if (maxScriptNumber != -1)
//		{
//			CCommonSystemFile::SetMaxScriptNumber(maxScriptNumber);
//			reInitFlag = TRUE;
//		}
//	}





	if (lpSystemFile != NULL)
	{
		m_systemFile = lpSystemFile;
		if (reInitFlag)
		{
			m_systemFile->CalcuInitParameter();
		}
	}
	else
	{
		m_systemFile = new CCommonSystemFile();
		m_createSystemFileFlag = TRUE;
	}

	//dummy
//	m_realWindowSizeX = 1024;
//	m_realWindowSizeY = 768;


	if (lpWheel != NULL)
	{
		m_wheelMouse = lpWheel;
	}
	else
	{
		m_createWheelFlag = TRUE;
		m_wheelMouse = new CWheelMouse();
	}

	m_systemFile->Load(TRUE);

	m_viewControl = new CViewControl();





	GetSystemDeviceInfo();
}




CMainControl::~CMainControl()
{
	End();
}

void CMainControl::End(void)
{
	ENDDELETECLASS(m_viewControl);

	if (m_userIcon != NULL)
	{
		DestroyIcon(m_userIcon);
		m_userIcon = NULL;
	}

	if (m_wheelMouse != NULL)
	{
		if (m_createWheelFlag)
		{
			ENDDELETECLASS(m_wheelMouse);
			m_createWheelFlag = FALSE;
		}
		m_wheelMouse = NULL;
	}

	if (m_systemFile != NULL)
	{
		if (m_systemOk)
		{
			m_systemFile->Save();
		}
		if (m_createSystemFileFlag)
		{
			ENDDELETECLASS(m_systemFile);
			m_createSystemFileFlag = FALSE;
		}
		m_systemFile = NULL;
	}


	ENDDELETECLASS(m_setup2);
	ENDDELETECLASS(m_setup);

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

	ENDDELETECLASS(m_myFile);
}


SIZE CMainControl::GetWindowSize(void)
{
	SIZE sz;
	
	sz.cx = m_windowSizeX;
	sz.cy = m_windowSizeY;

	return sz;
}
/*
SIZE CMainControl::GetRealWindowSize(void)
{
	SIZE sz;

	sz.cx = m_realWindowSizeX;
	sz.cy = m_realWindowSizeY;

	return sz;
}
*/

SIZE CMainControl::GetDesktopWindowSize(void)
{
	SIZE sz;
	
	sz.cx = m_desktopWindowSizeX;
	sz.cy = m_desktopWindowSizeY;

	return sz;
}

POINT CMainControl::GetDesktopWindowStart(void)
{
	POINT pt;
	pt.x = m_desktopWindowStartX;
	pt.y = m_desktopWindowStartY;
	return pt;
}

POINT CMainControl::GetDesktopWindowEnd(void)
{
	POINT pt;
	pt.x = m_desktopWindowEndX;
	pt.y = m_desktopWindowEndY;
	return pt;
}

BOOL CMainControl::CheckSystem(void)
{
	if (CheckMMX() == FALSE) return FALSE;
	if (CheckBpp() == FALSE) return FALSE;
	if (CheckScreenSize() == FALSE) return FALSE;
	if (CheckMutex() == FALSE) return FALSE;

	m_systemOk = TRUE;

	InitRandomSeed();

	return TRUE;
}


HWND CMainControl::CreateWindowRoutine(HINSTANCE hInstance,HICON icon, WNDPROC lpfnWndProc)
{
	if (CoInitialize(NULL) != S_OK)
	{
		//error!!
		
		return nullptr;
	}

	m_coInitFlag = TRUE;

	if (lpfnWndProc == NULL)
	{
		lpfnWndProc = MainWndProc;
	}

//	m_lpWndProc = lpfnWndProc;


	m_className = m_defaultClassName;
	GetInitGameString(&m_className,"className");

	LPSTR iconName = NULL;
	GetInitGameString(&iconName,"iconName");
	if (iconName != NULL)
	{
		m_userIcon = (HICON)LoadImage(NULL,iconName,IMAGE_ICON,0,0,LR_LOADFROMFILE);
		icon = m_userIcon;
	}

	m_icon = icon;

//    WNDCLASS wndclass;

    m_wndclass.style         = NULL;
    m_wndclass.lpfnWndProc   = lpfnWndProc;
    m_wndclass.cbClsExtra    = 0;
    m_wndclass.cbWndExtra    = 0;
    m_wndclass.hInstance     = hInstance;
    m_wndclass.hIcon         = icon;
    m_wndclass.hCursor       = NULL;
    m_wndclass.hbrBackground = NULL;
    m_wndclass.lpszMenuName  = NULL;
    m_wndclass.lpszClassName = m_className;
    RegisterClass(&m_wndclass);

	GetWindowTitleSetup();
	int addVersionFlag = 1;
	GetInitGameParam(&addVersionFlag,"addVersionToWindowTitleFlag");

	if (addVersionFlag > 0)
	{
		GetGameVersion();
		if (addVersionFlag == 1)
		{
			if ((m_highVersion == 0) && (m_middleVersion == 0) && (m_lowVersion == 0)) addVersionFlag = 0;
		}
	}

	char windowTitle[1024];
	if (addVersionFlag == 0)
	{
		wsprintf(windowTitle,"%s",m_windowTitle);
	}
	else
	{
		LPSTR versionTitleMessage = m_nullMessage;
		GetInitGameString(&versionTitleMessage,"versionTitleMessage");

		int lowVersionNotPrintFlag = 0;
		int middleVersionNotPrintFlag = 0;
		GetInitGameParam(&lowVersionNotPrintFlag,"lowVersionNotPrintFlag");
		GetInitGameParam(&middleVersionNotPrintFlag,"middleVersionNotPrintFlag");


		if (middleVersionNotPrintFlag)
		{
			wsprintf(windowTitle,"%s %s%d",m_windowTitle,versionTitleMessage,m_highVersion+1);
		}
		else if (lowVersionNotPrintFlag)
		{
			wsprintf(windowTitle,"%s %s%d.%d",m_windowTitle,versionTitleMessage,m_highVersion+1,m_middleVersion);
		}
		else
		{
			wsprintf(windowTitle,"%s %s%d.%d%d",m_windowTitle,versionTitleMessage,m_highVersion+1,m_middleVersion,m_lowVersion);
		}
	}


	int windowX = m_systemFile->m_systemdata.windowX;
	int windowY = m_systemFile->m_systemdata.windowY;

//	if (lpWindowZahyo != NULL)
//	{
//		windowX = lpWindowZahyo->x;
//		windowY = lpWindowZahyo->y;
//	}

	int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
	int realWindowSizeY = m_viewControl->GetRealWindowSizeY();

	int nonFullFlag = 0xffffffff;
	if (m_systemFile->m_systemdata.fullScreenFlag) nonFullFlag = 0;

	int sizeX = realWindowSizeX + 2*GetSystemMetrics(SM_CXFIXEDFRAME);
	int sizeY = realWindowSizeY + 2*GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);


	RECT rc;
	rc.top = 0;
	rc.left = 0;
	rc.right = realWindowSizeX;
	rc.bottom = realWindowSizeY;

	//�b��C��Win10���炨�������B�K�v�Ȑ��l��GetSystemMetrics�łƂ��Ă���Ȃ�
	sizeX += 10;
	sizeY += 10;


	DWORD style = ((WS_OVERLAPPED |
		WS_CAPTION |
		WS_SYSMENU |
		//								WS_THICKFRAME |
		WS_MAXIMIZEBOX |
		WS_MINIMIZEBOX |
		WS_BORDER 
		)&nonFullFlag) |
		WS_POPUP |
		WS_VISIBLE
		;
	DWORD exStyle = 0;
	AdjustWindowRectEx(&rc, style, false, exStyle);

	sizeX = rc.right - rc.left;
	sizeY = rc.bottom - rc.top;

	m_clientOffsetX = (sizeX - realWindowSizeX) / 2;
	m_clientOffsetY = (sizeY - GetSystemMetrics(SM_CYCAPTION) - realWindowSizeY) / 2;


//	int sizeX = realWindowSizeX + 2 * (GetSystemMetrics(SM_CXFIXEDFRAME) + GetSystemMetrics(SM_CXPADDEDBORDER));
//	int sizeY = realWindowSizeY + 2 * (GetSystemMetrics(SM_CYFIXEDFRAME) + 0*GetSystemMetrics(0)) + GetSystemMetrics(SM_CYCAPTION);

	/*
	for (int i = 0; i < 100; i++)
	{
		int d = GetSystemMetrics(i);
		char mes[256];
		sprintf_s(mes, 256, "\nsys%d=%d", i, d);
		OutputDebugString(mes);
	}
	*/

	if ((windowX+realWindowSizeX) > m_desktopWindowSizeX) windowX = m_desktopWindowSizeX - sizeX;
	if (windowX<0) windowX = 0;

	if ((windowY+realWindowSizeY) > m_desktopWindowSizeY) windowY = m_desktopWindowSizeY - sizeY;
	if (windowY<0) windowY = 0;




	DWORD dwExStyle = 0;
#if defined _TINYAN3DLIB_
	nonFullFlag = 0xffffffff;
#else


	if (m_systemFile->m_systemdata.fullScreenFlag)
	//if (0)
	{
//		dwExStyle = WS_EX_TOPMOST;

		windowX = 0;
		windowY = 0;
	}

#endif
	
//	MessageBox(NULL,"1","2",MB_OK);
//	char mes[256];
//	sprintf_s(mes,256,"\\x00d\x00a\x00d\x00a****** size=%d %d",sizeX,sizeY);
//	OutputDebugString(mes);


	HWND hWnd = CreateWindowEx(dwExStyle ,m_className,windowTitle,
								
								((
								WS_OVERLAPPED   |						
								WS_CAPTION |
								WS_SYSMENU |
								WS_BORDER | 
							//	WS_THICKFRAME |
								WS_MAXIMIZEBOX | 
								WS_MINIMIZEBOX  
								)&nonFullFlag) | 
								WS_POPUP |
								WS_VISIBLE ,
								windowX, windowY, 
								sizeX,sizeY,
								NULL, NULL, hInstance, NULL );




//	CoInitialize(NULL);
//	m_coInitFlag = TRUE;

	//fill
	int fillWindowFlag = 1;

	GetInitGameParam(&fillWindowFlag,"fillStartWindowFlag");

	if (fillWindowFlag)
	{
		HDC hdc = GetDC(hWnd);
		RECT rc;
		SetRect(&rc,0,0,m_windowSizeX,m_windowSizeY);
#if defined _WIN64
		FillRect(hdc,&rc,(HBRUSH)(COLOR_WINDOW + (long long)fillWindowFlag));
#else
		FillRect(hdc, &rc, (HBRUSH)(COLOR_WINDOW + fillWindowFlag));
#endif
		//	TextOut(hdc,0,0,m_startMessage,(int)strlen(m_startMessage));
		ReleaseDC(m_hWnd,hdc);
	}



    ShowWindow( hWnd, SW_SHOW );
	SetFocus(hWnd);

	m_hWnd = hWnd;


BOOL ff = m_systemFile->m_systemdata.fullScreenFlag;

#if defined _TINYAN3DLIB_
	ff = FALSE;
#endif

//	if (m_systemFile->m_systemdata.fullScreenFlag)
	//if (0)
	if (ff)
	{
		if (0)//old
		{
		DEVMODE devMode;

		ZeroMemory(&devMode,sizeof(devMode));
		devMode.dmSize = sizeof(devMode);

		devMode.dmPelsWidth = realWindowSizeX;
		devMode.dmPelsHeight = realWindowSizeY;
		devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT; 

//		SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE) | WS_EX_TOPMOST);
		int hr = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN); 
		}
		else
		{
	DEVMODE devMode0;
	ZeroMemory(&devMode0,sizeof(devMode0));
	devMode0.dmSize = sizeof(devMode0);
//	devMode.dmPelsWidth = m_windowSizeX;
//	devMode.dmPelsHeight = m_windowSizeY;
	devMode0.dmFields = DM_BITSPERPEL;
	EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&devMode0);


	DEVMODE devMode;
	ZeroMemory(&devMode,sizeof(devMode));
	devMode.dmSize = sizeof(devMode);
	devMode.dmPelsWidth = realWindowSizeX;
	devMode.dmPelsHeight = realWindowSizeY;
	devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT; 
	int hr = ChangeDisplaySettings(&devMode, CDS_FULLSCREEN); 
	Sleep(100);

	if (hr != DISP_CHANGE_SUCCESSFUL)
	{
		char mes[1024];
		int nn = 0;
		if (hr == DISP_CHANGE_SUCCESSFUL) nn = 1;
		if (hr == DISP_CHANGE_RESTART) nn = 2;
		if (hr == DISP_CHANGE_BADFLAGS) nn = 3;
		if (hr == DISP_CHANGE_BADPARAM) nn = 4;
		if (hr == DISP_CHANGE_FAILED) nn = 5;
		if (hr == DISP_CHANGE_BADMODE) nn = 6;
		if (hr == DISP_CHANGE_NOTUPDATED) nn = 7;
		wsprintf(mes,"%d:%d",hr,nn);
//		MessageBox(NULL,mes,"fullerrorret",MB_OK);

		int devNum = 0;
		DEVMODE devMode2;
		ZeroMemory(&devMode2,sizeof(devMode2));
		devMode2.dmSize = sizeof(devMode2);
//		devMode2.dmPelsWidth = m_windowSizeX;
//		devMode2.dmPelsHeight = m_windowSizeY;
		devMode2.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_BITSPERPEL;  
		BOOL cannot = TRUE;



		while (EnumDisplaySettings(NULL,devNum,&devMode2))
		{
			if ((devMode2.dmPelsWidth == realWindowSizeX) && (devMode2.dmPelsHeight == realWindowSizeY))
			{
				if (devMode2.dmDisplayFrequency > 0)
				{
					if (devMode2.dmBitsPerPel == devMode0.dmBitsPerPel)
					{
						devMode2.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY | DM_BITSPERPEL;  
						int hr2 = ChangeDisplaySettings(&devMode2, CDS_FULLSCREEN); 
						Sleep(10);

						int nn2 = 0;
						if (hr2 == DISP_CHANGE_SUCCESSFUL) nn2 = 1;
						if (hr2 == DISP_CHANGE_RESTART) nn2 = 2;
						if (hr2 == DISP_CHANGE_BADFLAGS) nn2 = 3;
						if (hr2 == DISP_CHANGE_BADPARAM) nn2 = 4;
						if (hr2 == DISP_CHANGE_FAILED) nn2 = 5;
						if (hr2 == DISP_CHANGE_BADMODE) nn2 = 6;
						if (hr2 == DISP_CHANGE_NOTUPDATED) nn2 = 7;
						wsprintf(mes,"%d:%d f=%d",hr,nn,devMode2.dmDisplayFrequency);
					//	MessageBox(NULL,mes,"fullerrorret",MB_OK);

						if (hr2 == DISP_CHANGE_SUCCESSFUL)
						{
							Sleep(100);
							cannot = FALSE;
							break;
						}
					}
				}
			}

			devNum++;
		}

		if (cannot)
		{
			MessageBox(m_hWnd,"�t���X�N���[�������Ɏ��s���܂���","Error",MB_ICONEXCLAMATION | MB_OK);
		}
	}

		}







		SetWindowLong(m_hWnd,GWL_STYLE,WS_POPUP | WS_VISIBLE);

		MoveWindow(m_hWnd,0,0, realWindowSizeX,realWindowSizeY,TRUE);
	}




	return hWnd;
}


HWND CMainControl::ReCreateWindow(void)
{
	m_windowChangingFlag = TRUE;
	ShowWindow(m_hWnd,SW_HIDE);
	DestroyWindow(m_hWnd);

//	UnregisterClass(m_className,m_hInstance);
  //  RegisterClass(&m_wndclass);


	int addVersionFlag = 1;
	GetInitGameParam(&addVersionFlag,"addVersionToWindowTitleFlag");

	if (addVersionFlag > 0)
	{
		GetGameVersion();
		if (addVersionFlag == 1)
		{
			if ((m_highVersion == 0) && (m_middleVersion == 0) && (m_lowVersion == 0)) addVersionFlag = 0;
		}
	}

	char windowTitle[1024];
	if (addVersionFlag == 0)
	{
		wsprintf(windowTitle,"%s",m_windowTitle);
	}
	else
	{
		LPSTR versionTitleMessage = m_nullMessage;
		GetInitGameString(&versionTitleMessage,"versionTitleMessage");

		int lowVersionNotPrintFlag = 0;
		int middleVersionNotPrintFlag = 0;
		GetInitGameParam(&lowVersionNotPrintFlag,"lowVersionNotPrintFlag");
		GetInitGameParam(&middleVersionNotPrintFlag,"middleVersionNotPrintFlag");


		if (middleVersionNotPrintFlag)
		{
			wsprintf(windowTitle,"%s %s%d",m_windowTitle,versionTitleMessage,m_highVersion+1);
		}
		else if (lowVersionNotPrintFlag)
		{
			wsprintf(windowTitle,"%s %s%d.%d",m_windowTitle,versionTitleMessage,m_highVersion+1,m_middleVersion);
		}
		else
		{
			wsprintf(windowTitle,"%s %s%d.%d%d",m_windowTitle,versionTitleMessage,m_highVersion+1,m_middleVersion,m_lowVersion);
		}
	}


	int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
	int realWindowSizeY = m_viewControl->GetRealWindowSizeY();


	//??
	int windowX = m_systemFile->m_systemdata.windowX;
	int windowY = m_systemFile->m_systemdata.windowY;

	int sizeX = realWindowSizeX + 2*GetSystemMetrics(SM_CXFIXEDFRAME);
//	int sizeY = m_windowSizeY + 2*GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYMENU);
	int sizeY = realWindowSizeY + 2*GetSystemMetrics(SM_CYFIXEDFRAME) + GetSystemMetrics(SM_CYCAPTION);

	if ((windowX+realWindowSizeX) > m_desktopWindowSizeX) windowX = m_desktopWindowSizeX - sizeX;
	if (windowX<0) windowX = 0;

	if ((windowY+realWindowSizeY) > m_desktopWindowSizeY) windowY = m_desktopWindowSizeY - sizeY;
	if (windowY<0) windowY = 0;

	m_windowChangingFlag = FALSE;

	HWND hWnd = CreateWindowEx(0*WS_EX_TOPMOST ,m_className,windowTitle,
								WS_OVERLAPPED   |						
								WS_CAPTION |
								WS_SYSMENU |
//								WS_THICKFRAME |
								WS_MAXIMIZEBOX | 
								WS_MINIMIZEBOX | 
								WS_POPUP |
								WS_VISIBLE ,
								windowX, windowY, 
								sizeX,sizeY,
								NULL, NULL, m_hInstance, NULL );



	m_hWnd = hWnd;

    ShowWindow( hWnd, SW_SHOW );
	SetFocus(hWnd);

	return m_hWnd;
}




BOOL CMainControl::CheckDirectXInit(BOOL result)
{
	if (result == TRUE) return TRUE;

	GetDirectXErrorSetup();
	if (m_checkDirectXFlag == 0) return TRUE;


	if (m_directXErrorMustAbortFlag == 0)
	{
		int okcan = MessageBox(NULL,m_directXErrorMessage,m_directXErrorTitle,MB_YESNO | MB_ICONWARNING);
		if (okcan == IDYES) return FALSE;
	}
	else
	{
		MessageBox(NULL,m_directXErrorMessage,m_directXErrorTitle,MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	return TRUE;
}


void CMainControl::GetSystemDeviceInfo(void)
{
	HWND hwnd0 = GetDesktopWindow();
	HDC hdc0 = GetDC(hwnd0);
	m_systemBpp = GetDeviceCaps(hdc0,BITSPIXEL);


//	RECT rc;
//	GetWindowRect(hwnd0,&rc);
//	m_desktopWindowSizeX = rc.right;
//	m_desktopWindowSizeY = rc.bottom;

//SM_CXVIRTUALSCREEN �֘A���g��

//SM_XVIRTUALSCREEN,


//	m_desktopWindowSizeX = GetDeviceCaps(hdc0,HORZRES);
//	m_desktopWindowSizeY = GetDeviceCaps(hdc0,VERTRES);


	m_desktopWindowSizeX = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	m_desktopWindowSizeY = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	m_desktopWindowStartX = GetSystemMetrics(SM_XVIRTUALSCREEN);
	m_desktopWindowStartY = GetSystemMetrics(SM_YVIRTUALSCREEN);
	m_desktopWindowEndX = m_desktopWindowStartX + m_desktopWindowSizeX;
	m_desktopWindowEndY = m_desktopWindowStartY + m_desktopWindowSizeY;

//	m_desktopWindowSizeY = GetDeviceCaps(hdc0,VERTRES);


	ReleaseDC(hwnd0,hdc0);
}


BOOL CMainControl::CheckMMX(void)
{
	if (CMMX::CheckMMX() == FALSE)
	{
		GetMMXErrorSetup();

		if (m_mmxErrorMustAbortFlag == 0)
		{
			int okcan = MessageBox(NULL,m_mmxErrorMessage,m_mmxErrorTitle,MB_YESNO | MB_ICONWARNING);
			if (okcan == IDYES) return FALSE;
		}
		else
		{
			MessageBox(NULL,m_mmxErrorMessage,m_mmxErrorTitle,MB_OK | MB_ICONWARNING);
			return FALSE;
		}
	}
	return TRUE;
}


BOOL CMainControl::CheckBpp(void)
{
	m_needBpp = 16;
	GetInitGameParam(&m_needBpp,"needBpp");

	if (m_systemBpp < m_needBpp)
	{
		GetBppErrorSetup();

		if (m_bppErrorMustAbortFlag == 0)
		{
			int okcan = MessageBox(NULL,m_bppErrorMessage,m_bppErrorTitle,MB_YESNO | MB_ICONWARNING);
			if (okcan == IDYES) return FALSE;
		}
		else
		{
			MessageBox(NULL,m_bppErrorMessage,m_bppErrorTitle,MB_OK | MB_ICONWARNING);
			return FALSE;
		}
	}

	return TRUE;
}


BOOL CMainControl::CheckScreenSize(void)
{
	m_windowSizeX = 800;
	GetInitGameParam(&m_windowSizeX,"windowSizeX");
	m_windowSizeY = 600;
	GetInitGameParam(&m_windowSizeY,"windowSizeY");

	int realWindowSizeX = m_windowSizeX;
	int realWindowSizeY = m_windowSizeY;

	int screenSizeType = m_systemFile->m_systemdata.screenSizeType;
//	char mes[256];
	char name[256];
	sprintf_s(name,256,"realWindowSizeX%d",screenSizeType+1);
	GetInitGameParam(&realWindowSizeX,name);
	sprintf_s(name,256,"realWindowSizeY%d",screenSizeType+1);
	GetInitGameParam(&realWindowSizeY,name);

//	sprintf_s(mes,256,"%d %d %d",screenSizeType,realWindowSizeX,realWindowSizeY);
//	MessageBox(NULL,mes,"aaa",MB_OK);


	m_viewControl->SetBufferSize(m_windowSizeX,m_windowSizeY);
	m_viewControl->SetRealWindowSize(realWindowSizeX,realWindowSizeY);
	m_viewControl->SetStretchFlag(m_systemFile->m_systemdata.genericFlag & 1);
	m_viewControl->CalcuParam();

//	int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
//	int realWindowSizeY = m_viewControl->GetRealWindowSizeY();

	if ((m_desktopWindowSizeX < realWindowSizeX) || (m_desktopWindowSizeY < realWindowSizeY))
	{
		GetWindowSizeErrorSetup();

		if (m_windowSizeErrorMustAbortFlag == 0)
		{
//			int okcan = MessageBox(NULL,m_windowSizeErrorMessage,m_windowSizeErrorTitle,MB_YESNO | MB_ICONWARNING);
			int okcan = MessageBox(NULL,m_makedWindowSizeErrorMessage,m_windowSizeErrorTitle,MB_YESNO | MB_ICONWARNING);
			if (okcan == IDYES) return FALSE;
		}
		else
		{
//			MessageBox(NULL,m_windowSizeErrorMessage,m_windowSizeErrorTitle,MB_OK | MB_ICONWARNING);
			MessageBox(NULL,m_makedWindowSizeErrorMessage,m_windowSizeErrorTitle,MB_OK | MB_ICONWARNING);
			return FALSE;
		}

	}

	return TRUE;
}


BOOL CMainControl::CheckMutex(void)
{
	m_mutexCheckFlag = 1;
	GetInitGameParam(&m_mutexCheckFlag,"checkMutexFlag");
	if (m_mutexCheckFlag == 0) return TRUE;

	m_mutexName = m_defaultMutexName;
	GetInitGameString(&m_mutexName,"mutexName");

	m_mutex = CreateMutex(NULL,TRUE,m_mutexName);

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		GetMutexErrorSetup();
		MessageBox(NULL,m_mutexErrorMessage,m_mutexErrorTitle,MB_OK | MB_ICONWARNING);
		return FALSE;
	}

	return TRUE;
}

void CMainControl::InitRandomSeed(void)
{
	m_randomSeed = -1;
	GetInitGameParam(&m_randomSeed,"initRandomSeed");
	if (m_randomSeed == -1)
	{
		srand((unsigned int)time(NULL));
	}
	else if (m_randomSeed > 0)
	{
		srand((unsigned int)m_randomSeed);
	}
}

void CMainControl::GetWindowTitleSetup(void)
{
	m_windowTitle = m_defaultWindowTitle;
	GetInitGameString(&m_windowTitle,"windowTitle");

	if (CCommonGameVersion::CheckTaikenVersion())
	{
		m_windowTitle = m_defaultWindowTitleTaiken;
		GetInitGameString(&m_windowTitle,"windowTitleTaiken");
	}

	if (CCommonGameVersion::CheckNetVersion())
	{
		m_windowTitle = m_defaultWindowTitleNet;
		GetInitGameString(&m_windowTitle,"windowTitleNet");
	}

	if (CCommonGameVersion::CheckDemoVersion())
	{
		m_windowTitle = m_defaultWindowTitleDemo;
		GetInitGameString(&m_windowTitle,"windowTitleDemo");
	}
}


void CMainControl::GetWindowSizeErrorSetup(void)
{
	m_windowSizeErrorMessage = m_defaultWindowSizeErrorMessage;
	m_windowSizeErrorTitle = m_defaultWindowSizeErrorTitle;
	m_windowSizeErrorMustAbortFlag = 1;

	GetInitGameString(&m_windowSizeErrorMessage,"windowSizeErrorMessage");
	GetInitGameString(&m_windowSizeErrorTitle,"windowSizeErrorTitle");
	GetInitGameParam(&m_windowSizeErrorMustAbortFlag,"windowSizeErrorMustAbortFlag");

	int realWindowSizeX = m_viewControl->GetRealWindowSizeX();
	int realWindowSizeY = m_viewControl->GetRealWindowSizeY();
	
	int windowSizeErrorMesAddNumFlag = 1;
	GetInitGameParam(&windowSizeErrorMesAddNumFlag,"windowSizeErrorMesAddNumFlag");

	if (windowSizeErrorMesAddNumFlag == 0)
	{
		wsprintf(m_makedWindowSizeErrorMessage,"%s",m_windowSizeErrorMessage);
	}
	else
	{
		wsprintf(m_makedWindowSizeErrorMessage,m_windowSizeErrorMessage,realWindowSizeX,realWindowSizeY);
	}
}

void CMainControl::GetMMXErrorSetup(void)
{
	m_mmxErrorMessage = m_defaultMMXErrorMessage;
	m_mmxErrorTitle = m_defaultMMXErrorTitle;
	m_mmxErrorMustAbortFlag = 0;

	GetInitGameString(&m_mmxErrorMessage,"mmxErrorMessage");
	GetInitGameString(&m_mmxErrorTitle,"mmxErrorTitle");
	GetInitGameParam(&m_mmxErrorMustAbortFlag,"mmxErrorMustAbortFlag");
}

void CMainControl::GetBppErrorSetup(void)
{
	m_bppErrorMessage = m_defaultBppErrorMessage;
	m_bppErrorTitle = m_defaultBppErrorTitle;
	m_bppErrorMustAbortFlag = 1;

	GetInitGameString(&m_bppErrorMessage,"bppErrorMessage");
	GetInitGameString(&m_bppErrorTitle,"bppErrorTitle");
	GetInitGameParam(&m_bppErrorMustAbortFlag,"bppErrorMustAbortFlag");

	int bppErrorMesAddNumFlag = 1;
	GetInitGameParam(&bppErrorMesAddNumFlag,"bppErrorMesAddNumFlag");

	if (bppErrorMesAddNumFlag == 0)
	{
		wsprintf(m_makedBppErrorMessage,"%s",m_bppErrorMessage);
	}
	else
	{
		wsprintf(m_makedBppErrorMessage,m_bppErrorMessage,m_needBpp);
	}
}


void CMainControl::GetMutexErrorSetup(void)
{
	m_mutexErrorMessage = m_defaultMutexErrorMessage;
	m_mutexErrorTitle = m_defaultMutexErrorTitle;

	GetInitGameString(&m_mutexErrorMessage,"mutexErrorMessage");
	GetInitGameString(&m_mutexErrorTitle,"mutexErrorTitle");
}


void CMainControl::GetDirectXErrorSetup(void)
{
	m_checkDirectXFlag = 1;
	GetInitGameParam(&m_checkDirectXFlag,"checkDirectXFlag");

	m_directXErrorMessage = m_defaultDirectXErrorMessage;
	GetInitGameString(&m_directXErrorMessage,"directXErrorMessage");

	LPSTR m_directXErrorTitle = m_defaultDirectXErrorTitle;
	GetInitGameString(&m_directXErrorTitle,"directXErrorTitle");

	m_directXErrorMustAbortFlag = 1;
	GetInitGameParam(&m_directXErrorMustAbortFlag,"directXErrorMustAbortFlag");
}


void CMainControl::GetGameVersion(void)
{
	m_highVersion = 0;
	m_middleVersion = 0;
	m_lowVersion = 0;

	GetInitGameParam2(&m_highVersion,"highVersion");
	GetInitGameParam2(&m_middleVersion,"middleVersion");
	GetInitGameParam2(&m_lowVersion,"lowVersion");
}



BOOL CMainControl::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}


BOOL CMainControl::GetInitGameParam2(int* lpVar, LPSTR name)
{
	int rNum = m_setup2->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup2->GetName(rNum + 1));

	return TRUE;
}

BOOL CMainControl::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}

BOOL CMainControl::GetInitGameString2(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup2->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup2->GetName(rNum + 1);

	return TRUE;
}


BOOL CMainControl::LoadSetupFile(LPSTR filenameonly, int varKosuu)
{
	if (m_setup == NULL)
	{
		m_setup = new CNameList(varKosuu * 2);
	}

	if (m_setup == NULL) return FALSE;

	return m_setup->LoadInit(filenameonly);

//	char filename2[1024];
//	wsprintf(filename2,"init\\%s.xtx",filenameonly);	

//	return m_setup->LoadFile(filename2);
}


BOOL CMainControl::LoadSetupFile2(LPSTR filenameonly, int varKosuu)
{
	if (m_setup2 == NULL)
	{
		m_setup2 = new CNameList(varKosuu * 2);
	}

	if (m_setup2 == NULL) return FALSE;

	return m_setup2->LoadInit(filenameonly);
//	char filename2[1024];
//	wsprintf(filename2,"init\\%s.xtx",filenameonly);	

//	return m_setup2->LoadFile(filename2);
}


BOOL CMainControl::Game(CGameCallBack* lpGame)
{
	m_game = lpGame;

	m_game->SetMainControl(this);
	m_game->GeneralCreate();

	m_game->Create();

	m_game->AfterCreate();

	if (m_game->CheckInitDirectX() == FALSE) return FALSE;

	m_windowChangingFlag = FALSE;

	m_game->SetMainControl(this);

	SIZE sz2 = GetDesktopWindowSize();
	m_game->SetDesktopWindowSize(sz2.cx,sz2.cy);
	POINT pt2 = GetDesktopWindowStart();
	m_game->SetDesktopWindowStart(pt2);
	POINT pt3 = GetDesktopWindowEnd();
	m_game->SetDesktopWindowEnd(pt3);

//	m_game->SetThreadAddr(ThreadAddr);

	int frame = m_game->GetFrameTime();


	ShowWindow( m_hWnd, SW_SHOW );


	UpdateWindow( m_hWnd );


	SetFocus(m_hWnd);



	TIMECAPS	tc ;
	timeGetDevCaps( &tc , sizeof(TIMECAPS) );

	/* �}���`���f�B�A�^�C�}�[�̃T�[�r�X���x���ő�� */
	timeBeginPeriod( tc.wPeriodMin );

	char mes5[256];
	wsprintf(mes5,"\n\ntimer���x=%d\n\n",tc.wPeriodMin);
	OutputDebugString(mes5);

	int oldTime = (int)timeGetTime();
	int oldTime0 = oldTime;

	MSG msg;
	int sleepFlag = 0;

	while(1)
	{
//Sleep(1);
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
//			timeBeginPeriod(1);
			int tm = (int)timeGetTime();
//			timeEndPeriod(1);


			if ((tm - oldTime) >= (frame - 5))			
			{
				if (m_game != NULL)
				{
					if (m_oldUseGeneralFlag)
					{
						m_game->GeneralMainLoop(tm - oldTime0);
					}
					else
					{
						m_game->MainLoop(tm - oldTime0);
					}
				}	
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

				if (m_game != NULL)
				{
					frame = m_game->GetFrameTime();	//�σt���[���ɑΉ�
				}

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

	m_systemFile->Save(TRUE);
	m_game = NULL;

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CMainControl::MultiThreadGame(CGameCallBack* lpGame)
{
	WINNLSEnableIME(m_hWnd,FALSE);

	m_game = lpGame;
	m_game->SetMainControl(this);


	//0:MultiThreadGame -> Game2
	//1:MultiThreadGame <- Game2
	HANDLE eventHandle[8];
	for (int i=0;i<8;i++)
	{
		eventHandle[i] = CreateEvent(NULL,FALSE,FALSE,NULL);
	}

m_windowChangingFlag = TRUE;

	ShowWindow( m_hWnd, SW_SHOW );
	UpdateWindow( m_hWnd );
	SetFocus(m_hWnd);

	LPVOID para = eventHandle;
	unsigned int threadID = 0;
#if defined _MT
	HANDLE threadHandle = (HANDLE) _beginthreadex(NULL,0,ThreadAddr,para,0,&threadID);
#else
	HANDLE threadHandle = NULL;//dummy
#endif

	m_threadHandle[0] = threadHandle;
	m_threadID[0] = threadID;


	PlaySound("wav\\sys\\gkt_pi01.wav",NULL,SND_FILENAME);
	OutputDebugString("\n\n�X���b�h�J�n�҂�");
	//�X���b�h�J�n�܂�

	MSG msg;

	DWORD rt00 = 0;
	while (1)
	{
		rt00 = MsgWaitForMultipleObjects(1,&eventHandle[1],FALSE,30000,QS_ALLINPUT);
		if (rt00 == WAIT_OBJECT_0)
		{
			break;//ok
		}
		else if (rt00 == WAIT_OBJECT_0 + 1)
		{
			if ( PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) )
			{
				if ( !GetMessage(&msg,NULL,0,0) )
				{
//	OutputDebugString("\nQUIT1");//�܂����Ăق����Ȃ��߂����[��
					break;
				}
				//����
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else//error!
		{
			break;
		}
	}


//���Ƃł���
//	DWORD rt = WaitForSingleObject(waitHandle,6000);
	if (rt00 == WAIT_OBJECT_0)
	{
		PlaySound("wav\\sys\\gkt_ok01.wav",NULL,SND_FILENAME);
		OutputDebugString("\n\n�X���b�h�҂�����");
	}
	else if (rt00 == WAIT_ABANDONED)
	{
		OutputDebugString("\n\n�X���b�h�҂����s");
	}
	else if (rt00 ==WAIT_TIMEOUT )
	{
		PlaySound("wav\\sys\\gkt_pi03.wav",NULL,SND_FILENAME);
		OutputDebugString("\n\n�X���b�h�҂��^�C���A�E�g");
	}

	CloseHandle(eventHandle[1]);
	OutputDebugString("\n\n�X���b�h�J�n�I��");

	msg.hwnd = NULL;
	BOOL gameThreadWaitFlag = FALSE;

	while(1)
	{
		if (m_game->GetQuitFlag())
		{
OutputDebugString("\nQUIT0");
			break;
		}

		if ( PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) )
		{
			if ( !GetMessage(&msg,NULL,0,0) )
			{
OutputDebugString("\nQUIT1");
				break;
			}



//			if (m_game != NULL)
//			{
//				if (gameThreadWaitFlag == FALSE)
//				{
//					m_game->WaitGameThread();
//					gameThreadWaitFlag = TRUE;
//				}
//			}

static int mmm = 0;
if (mmm==0)
{
OutputDebugString("m");
}
mmm++;
mmm%=50;


			if (1)
			{
				int modalLevel = m_game->GetModalLevel();

				switch (msg.message)
				{
				case WM_SYSKEYDOWN:
					if (msg.wParam == VK_MENU)
					{
						if (m_syskeyaltoff)
						{
							break;
						}
					}
					else if (msg.wParam == VK_APPS)
					{
						if (m_syskeyappsoff)
						{
							break;
						}
					}
					else if ((msg.wParam == VK_LWIN) || (msg.wParam == VK_RWIN))
					{
						if (m_syskeywinoff)
						{
							break;
						}
					}

				case WM_SETCURSOR:
				case WM_MOUSEWHEEL:
				case MM_MCINOTIFY:
				case WM_KEYDOWN:
				case WM_KEYUP:
				case WM_LBUTTONDOWN:
				case WM_RBUTTONDOWN:
				case WM_MBUTTONDOWN:
				case WM_LBUTTONUP:
				case WM_RBUTTONUP:
				case WM_MBUTTONUP:
				case WM_ACTIVATEAPP:
				case WM_SIZE:
				case WM_CLOSE:
				case WM_MOUSEMOVE:
				case WM_PAINT:
				case WM_CHAR:
				case WM_MOVE:

					if (m_game != NULL)
					{
						//�C�x���g�ł��Ƃ肷��
						m_msg = msg;
//						m_game->SetEventMessage(&msg);
						SetEvent(eventHandle[0]);
						//wait
						WaitForSingleObject(eventHandle[1],10000);
						ResetEvent(eventHandle[1]);
					}
					TranslateMessage(&msg);
			//		DispatchMessage(&msg);
					break;

				default:
					TranslateMessage(&msg);
					DispatchMessage(&msg);
					break;
				}
			}
		}
		else
		{
//			if (gameThreadWaitFlag)
//			{
//				if (m_game != NULL)
//				{
//					m_game->ResumeGameThread();
//				}
//				gameThreadWaitFlag = FALSE;
//			}
//			else
//			{
//				m_game->CheckAndFree();
//			}
/*
			DWORD rt;
			rt = WaitForMultipleObjects(2,changeScreenEvent,FALSE,1);
			if ((rt == WAIT_OBJECT_0) || (rt == WAIT_OBJECT_0+1))
			{
//OutputDebugString("\n\nMainControl Receive windowchange");
m_windowChangingFlag = TRUE;
				if (rt == WAIT_OBJECT_0)
				{
					m_game->ToWindowScreenRoutine();
					ResetEvent(changeScreenEvent[0]);
				}
				else
				{
					m_game->ToFullScreenRoutine();
					ResetEvent(changeScreenEvent[1]);
				}

//OutputDebugString("\nMainControl Send ack");
				SetEvent(changeScreenEvent[2]);
				WaitForSingleObject(changeScreenEvent[3],10000);
//OutputDebugString("\nMainControl recieve ack");
				ResetEvent(changeScreenEvent[3]);
m_windowChangingFlag = FALSE;
			}
*/
static int sss = 0;
if (sss==0)
{
OutputDebugString("s");
}
sss++;
sss%=50;
WaitMessage();
		//	Sleep(1);
//			sleepFlag = 1;
		}

	}

	for (int ii=7;ii>=0;ii--)
	{
		CloseHandle(eventHandle[ii]);
	}
	CloseHandle(threadHandle);

	m_systemFile->Save(TRUE);
	m_game = NULL;

	return TRUE;
}



unsigned int __stdcall CMainControl::ThreadAddr(void* dummy)
{
	if (CoInitialize(NULL) == S_OK)
	{
		m_this->Game2(dummy);
		CoUninitialize();
	}
#if defined _MT
	_endthreadex(0);
#endif
	return 0;
}



BOOL CMainControl::Game2(LPVOID lpHandle)
{
	m_game->GeneralCreate();
	m_game->Create();
//	m_game->SetEventHandle(lpHandle);	//handle* 8��

	HANDLE* handle = (HANDLE*)lpHandle;

	SetEvent(handle[1]);	//ack

	SIZE sz2 = GetDesktopWindowSize();
	m_game->SetDesktopWindowSize(sz2.cx,sz2.cy);
	POINT pt2 = GetDesktopWindowStart();
	m_game->SetDesktopWindowStart(pt2);
	POINT pt3 = GetDesktopWindowEnd();
	m_game->SetDesktopWindowEnd(pt3);

	m_windowChangingFlag = FALSE;

	TIMECAPS	tc ;
	timeGetDevCaps( &tc , sizeof(TIMECAPS) );

	char mes5[256];
	wsprintf(mes5,"\nGame2::\ntimer���x=%d\n\n",tc.wPeriodMin);
	OutputDebugString(mes5);


	/* �}���`���f�B�A�^�C�}�[�̃T�[�r�X���x���ő�� */
	timeBeginPeriod( tc.wPeriodMin );
	int oldTime = (int)timeGetTime();
//	timeEndPeriod( tc.wPeriodMin );
	int oldTime0 = oldTime;
	int frame = m_game->GetFrameTime();

	MSG msg;

	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	HWND hwnd = m_game->GetGameHWND();


	int sleepFlag = 0;

OutputDebugString("\nStartGmae2\n");
	while(1)
	{
		DWORD wait = WaitForSingleObject(handle[0],0);
		if (wait == WAIT_OBJECT_0)
//		if (WaitForSingleObject(handle[0],1))
		{
			if (m_msg.message == WM_SETCURSOR) OutputDebugString("WM_SETCURSOR");
//			if (m_msg.message == WM_MOUSEWHEEL) OutputDebugString("WM_MOUSEWHEEL");
//			if (m_msg.message == MM_MCINOTIFY) OutputDebugString("MM_MCINOTIFY");
//			if (m_msg.message == WM_KEYDOWN) OutputDebugString("WM_KEYDOWN");
//			if (m_msg.message == WM_KEYUP) OutputDebugString("WM_KEYUP");
//			if (m_msg.message == WM_LBUTTONDOWN) OutputDebugString("WM_LBUTTONDOWN");
//			if (m_msg.message == WM_RBUTTONDOWN) OutputDebugString("WM_RBUTTONDOWN");
//			if (m_msg.message == WM_MBUTTONDOWN) OutputDebugString("WM_MBUTTONDOWN");
//			if (m_msg.message == WM_LBUTTONUP) OutputDebugString("WM_LBUTTONUP");
//			if (m_msg.message == WM_RBUTTONUP) OutputDebugString("WM_RBUTTONUP");
//			if (m_msg.message == WM_MBUTTONUP) OutputDebugString("WM_MBUTTONUP");
//			if (m_msg.message == WM_ACTIVATEAPP) OutputDebugString("WM_ACTIVATEAPP");
//			if (m_msg.message == WM_SIZE) OutputDebugString("WM_SIZE");
//			if (m_msg.message == WM_CLOSE) OutputDebugString("WM_CLOSE");
//			if (m_msg.message == WM_MOUSEMOVE) OutputDebugString("WM_MOUSEMOVE");
//			if (m_msg.message == WM_PAINT) OutputDebugString("WM_PAINTE");
//			if (m_msg.message == WM_CHAR) OutputDebugString("WM_CHAR");
//			if (m_msg.message == WM_MOVE) OutputDebugString("WM_MOVE");
			

static int bbb = 0;
if (bbb == 0)
{
OutputDebugString("*");
}
bbb++;
bbb %= 50;

//char mes[256];
//wsprintf(mes,"*%d ",msg.message);
//OutputDebugString(mes);
//			TranslateMessage(&m_msg);
			m_game->GameProc(hwnd,m_msg.message,m_msg.wParam,m_msg.lParam);
			ResetEvent(handle[0]);
			SetEvent(handle[1]);
		}
		else
		{
			int tm = (int)timeGetTime();
			if ((tm - oldTime) >= (frame - 5))			
			{
				if (m_game != NULL)
				{
static int aaa = 0;
if (aaa == 0)
{
OutputDebugString("o");
}
aaa++;
aaa %= 50;
					m_game->GeneralMainLoop(tm - oldTime0);
				}
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

				if (m_game != NULL)
				{
					frame = m_game->GetFrameTime();	//�σt���[���ɑΉ�
				}
				if (sleepFlag == 0) Sleep(1);
				sleepFlag = 0;
			}
			else
			{
				Sleep(1);
				sleepFlag = 1;
			}
		}
	}

	timeEndPeriod( tc.wPeriodMin );

	return 0;
}


HANDLE CMainControl::StartModalThread(WPARAM wParam,LPARAM lParam)
{
#if defined _MT

	if (m_game == NULL) return NULL;
	int* lpParam = (int*)wParam;
	HANDLE eventHandle = (HANDLE)lParam;

	int modalLevel = m_game->GetModalLevel();
	if (modalLevel >= 15) return NULL;



	int oldMode = m_game->GetGameMode();
	int newMode = *(lpParam + 0);
	int printMode = *(lpParam + 1);
	int stackSize = *(lpParam + 2);

	m_game->SetModalPrintMode(modalLevel,printMode);

	modalLevel += 1;
	m_game->SetModalLevel(modalLevel);
	m_game->SetGameMode(newMode);
	m_eventHandle[modalLevel] = eventHandle;

	m_game->ChangeOmakeClass(oldMode,newMode);
	m_game->StartModeRoutine(newMode);

	CAreaControl::SetNextAllPrint();

	unsigned int threadID = 0;
	LPVOID para = NULL;
	HANDLE threadHandle = NULL;
	threadHandle = (HANDLE) _beginthreadex(NULL,stackSize,ThreadAddr,para,0,&threadID);

	m_threadID[modalLevel] = threadID;
	m_threadHandle[modalLevel] = threadHandle;

	m_game->SetTmpThreadHandle(threadHandle);


	return threadHandle;
#endif

	return NULL;
}


BOOL CMainControl::EndModalThread(WPARAM wParam,LPARAM lParam)
{
	if (m_game == NULL) return FALSE;

	int modalLevel = m_game->GetModalLevel();
	if (modalLevel <= 0) return FALSE;

	HANDLE eventHandle = m_eventHandle[modalLevel];

	int oldMode = m_game->GetGameMode();

	m_game->EndModeRoutine(oldMode);

	modalLevel -= 1;
	m_game->SetModalLevel(modalLevel);

	int newMode = m_game->GetGameMode();
	m_game->ChangeOmakeClass(oldMode,newMode);

	CAreaControl::SetNextAllPrint();

	m_game->SetTmpThreadHandle(NULL);
	SetEvent(eventHandle);

	return TRUE;
}


LRESULT CALLBACK CMainControl::MainWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_wheelMouse != NULL)
	{
		message = m_wheelMouse->TranslateMessage(message);
	}

	if (message == WM_DESTROY)
	{
		if (m_windowChangingFlag == FALSE)
		{
			ShowWindow(hWnd,SW_HIDE);
			PostQuitMessage(0);
			return 0;
		}
	}

	if (message == WM_MYCREATETHREAD)
	{
		if (m_this != NULL)
		{
			return (LRESULT)m_this->StartModalThread(wParam,lParam);
		}
	}

	if (message == WM_MYDESTROYTHREAD)
	{
		if (m_this != NULL)
		{
			return m_this->EndModalThread(wParam,lParam);
		}
	}

	if (m_game != NULL)
	{
		if (m_windowChangingFlag == FALSE)
		{
			return m_game->GameProc(hWnd,message,wParam,lParam);
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

} /* MainWndproc */

int CMainControl::GetClientOffsetX(void)
{
	return m_clientOffsetX;
}

int CMainControl::GetClientOffsetY(void)
{
	return m_clientOffsetY;
}








