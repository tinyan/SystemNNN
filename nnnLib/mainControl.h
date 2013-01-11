//
// mainControl.h
//

#if !defined __TINYANGAMELIB_MAINCONTROL__
#define __TINYANGAMELIB_MAINCONTROL__


class CWheelMouse;
class CCommonSystemFile;

class CGameCallBack;
class CNameList;

class CMainControl
{
public:
	CMainControl(CCommonSystemFile* lpSystemFile = NULL,CWheelMouse* lpWheelMouse = NULL);
	~CMainControl();
	void End(void);

	BOOL CheckSystem(void);
	SIZE GetWindowSize(void);
	SIZE GetDesktopWindowSize(void);
	POINT GetDesktopWindowStart(void);
	POINT GetDesktopWindowEnd(void);

	int GetBpp(void) {return m_systemBpp;}
//	HWND CreateWindowRoutine(HINSTANCE hInstance,WNDPROC lpfnWndProc, POINT* lpWindowZahyo = NULL,HICON icon = NULL);
	HWND CreateWindowRoutine(HINSTANCE hInstance,HICON icon, WNDPROC lpfnWndProc = NULL);

	BOOL MultiThreadGame(CGameCallBack* lpGame);
	BOOL Game(CGameCallBack* lpGame);
	BOOL Game2(LPVOID param = NULL);

	BOOL CheckDirectXInit(BOOL result);
//	int GetFrameRate(void) {return m_frameRate;}

	static CGameCallBack* m_game;
	static CWheelMouse* m_wheelMouse;

	static LRESULT CALLBACK MainWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	
	CCommonSystemFile* GetSystemFile(void) {return m_systemFile;}

	static unsigned int __stdcall ThreadAddr(void* dummy);

	static CMainControl* m_this;

	HANDLE StartModalThread(WPARAM wParam,LPARAM lParam);
	BOOL EndModalThread(WPARAM wParam,LPARAM lParam);

	void ChangeOmakeClass(void);

	HWND ReCreateWindow(void);

	static MSG m_msg;
protected:
	HANDLE m_eventHandle[16];
	HANDLE m_threadHandle[16];
	unsigned int m_threadID[16];
private:
	CCommonSystemFile* m_systemFile;

	BOOL m_createSystemFileFlag;
	BOOL m_createWheelFlag;


	static char m_defaultWindowTitle[];
	static char m_defaultWindowTitleTaiken[];
	static char m_defaultWindowTitleNet[];
	static char m_defaultWindowTitleDemo[];

	static char m_defaultClassName[];
	static char m_defaultMutexName[];

	static char m_nullMessage[];
	
	static char m_defaultWindowSizeErrorMessage[];
	static char m_defaultWindowSizeErrorTitle[];

	static char m_defaultMMXErrorMessage[];
	static char m_defaultMMXErrorTitle[];

	static char m_defaultBppErrorMessage[];
	static char m_defaultBppErrorTitle[];

	static char m_defaultMutexErrorMessage[];
	static char m_defaultMutexErrorTitle[];

	static char m_defaultDirectXErrorMessage[];
	static char m_defaultDirectXErrorTitle[];

	LPSTR m_windowTitle;
	int m_windowSizeX;
	int m_windowSizeY;

	int m_randomSeed;
	int m_needBpp;


	int m_highVersion;
	int m_middleVersion;
	int m_lowVersion;

	int m_checkDirectXFlag;
	int m_directXErrorMustAbortFlag;
	LPSTR m_directXErrorMessage;
	LPSTR m_directXErrorTitle;


	int m_mmxErrorMustAbortFlag;
	LPSTR m_mmxErrorMessage;
	LPSTR m_mmxErrorTitle;


	int m_bppErrorMustAbortFlag;
	LPSTR m_bppErrorMessage;
	LPSTR m_bppErrorTitle;


	int m_windowSizeErrorMustAbortFlag;
	LPSTR m_windowSizeErrorMessage;
	LPSTR m_windowSizeErrorTitle;

	int m_mutexCheckFlag;
	LPSTR m_mutexErrorMessage;
	LPSTR m_mutexErrorTitle;


	LPSTR m_className;
	LPSTR m_mutexName;

	HANDLE m_mutex;
	HICON m_icon;

	HICON m_userIcon;


	void GetSystemDeviceInfo(void);

	int m_systemBpp;
	int m_desktopWindowSizeX;
	int m_desktopWindowSizeY;

	int m_desktopWindowStartX;
	int m_desktopWindowStartY;
	int m_desktopWindowEndX;
	int m_desktopWindowEndY;

//	int m_frameRate;

	CNameList* m_setup;
	CNameList* m_setup2;


	BOOL CheckMMX(void);
	BOOL CheckBpp(void);
	BOOL CheckScreenSize(void);
	BOOL CheckMutex(void);
	void InitRandomSeed(void);

	void GetGameVersion(void);


	void GetWindowTitleSetup(void);
	void GetWindowSizeErrorSetup(void);
	void GetMMXErrorSetup(void);
	void GetBppErrorSetup(void);
	void GetMutexErrorSetup(void);
	void GetDirectXErrorSetup(void);

	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameParam2(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);
	BOOL GetInitGameString2(LPSTR* lpStr, LPSTR name);
	BOOL LoadSetupFile(LPSTR filenameonly, int varKosuu);
	BOOL LoadSetupFile2(LPSTR filenameonly, int varKosuu);

	BOOL m_coInitFlag;
	HWND m_hWnd;
	char m_makedWindowSizeErrorMessage[1024];
	char m_makedBppErrorMessage[1024];

	int m_oldUseGeneralFlag;

	HINSTANCE m_hInstance;
//	LRESULT CALLBACK* m_lpWndProc;

	WNDCLASS m_wndclass;

	int m_syskeyaltoff;
	int m_syskeywinoff;
	int m_syskeyappsoff;

	BOOL m_systemOk;

	static BOOL m_windowChangingFlag;
};




#endif
/*_*/

