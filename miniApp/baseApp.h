#if !defined __MINIAPP_BASEAPP__
#define __MINIAPP_BASEAPP__



class CWheelMouse;

class CBaseApp
{
public:
	CBaseApp(HINSTANCE hInstance,int sx,int sy,LPSTR mutexName = NULL,LPSTR className = NULL,LPSTR iconName = NULL);
	virtual ~CBaseApp();
	void End(void);

	void GeneralStart(BOOL tray=TRUE,BOOL rightMenu = TRUE,LPSTR tooltipMessage = NULL);
	virtual void BeforeCreateWindow(void);
	virtual void AfterCreateWindow(void);

	static LRESULT CALLBACK MainWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	static CBaseApp* m_this;
	static CWheelMouse* m_wheelMouse;

	virtual void GeneralMainLoop(int tm);
	virtual HRESULT GameProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

	BOOL ChangeSaveTypeFile(LPSTR filename = NULL,LPSTR folderName = NULL,int saveFileSize = -1);
	BOOL ChangeSaveTypeReg(LPSTR companyName = NULL,LPSTR gameName = NULL, LPSTR dataName = NULL,int dataSize = -1);

	virtual void OnShakeWindow(int x,int y){}
	virtual void OnTurnWindow(int x,int y){}

	virtual void OnWheel(int wheel,int x,int y){}

	void SetExitButtonZahyo(int x=0,int y=0,int alignX=2,int alignY=0);

protected:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	HANDLE m_mutex;
	HICON m_icon;

	LPSTR m_mutexName;
	LPSTR m_className;
	LPSTR m_iconName;
	LPSTR m_tooltipMessage;

	static char m_defaultMutexName[];
	static char m_defaultClassName[];
	static char m_defaultIconName[];
	static char m_defaultTooltipMessage[];

	static char m_defaultFolder[];
	static char m_defaultFilename[];

	int m_windowSizeX;
	int m_windowSizeY;

	void MyLoadIcon(void);

	BOOL m_coInitFlag;

	BOOL m_wheelMoveFlag;
	int m_wheelMove;
	
	virtual BOOL OnLButtonDown(int x,int y);
	virtual BOOL OnRButtonDown(int x,int y);

	BOOL m_captureFlag;
	int m_oldCaptureX;
	int m_oldCaptureY;
	int m_windowX;
	int m_windowY;

	HDC m_backHDC;
	HBITMAP m_backBitmap;

	HMENU m_popupMenu;
	void AddMenu(LPSTR name,int id);
	void AddSeparator();

	int m_menuItemKosuu;
	BOOL m_trayIconFlag;
	BOOL m_rightMenuEnable;

	virtual void PopupMenuRoutine(HWND hwnd,POINT pt);

	void MyPlaySound(LPSTR name);
	void MyStopSound(void);

	HBITMAP m_exitButtonBitmap;
	int m_exitButtonSizeX;
	int m_exitButtonSizeY;
	int m_exitButtonAlignX;
	int m_exitButtonAlignY;
	int m_exitButtonX;
	int m_exitButtonY;

	HBITMAP m_defaultBitmap;

	virtual int GetExitButtonAlignX(void){return 2;}
	virtual int GetExitButtonAlignY(void){return 0;}

	virtual BOOL OnAddButtonDown(int n);

	POINT GetExitButtonZahyo(void);

	BOOL CheckOnExitButton(int x,int y);
	BOOL CheckOnAddButton(int n,int x,int y);

	void PutDefaultScreen(void);

	void PutExitButton(int md = 0);
	void PutAddButton(int n,int md =0);
	BOOL m_onExitButton;

	BOOL CheckAndReprintExitButton(int x,int y);
	BOOL CheckAndReprintAddButton(int x,int y);
	void CheckOutOfWindow(void);

	HCURSOR m_cursor;

	int AddButton(LPSTR name,int x=-1,int y=-1,int n=-1,int sizeX = -1,int sizeY = -1);
	int m_addButtonKosuu;
	int m_addButtonMax;
	POINT* m_addButtonZahyo;
	SIZE* m_addButtonSize;
	HBITMAP* m_addButtonBitmap;
	int* m_addButtonNumber;
	BOOL* m_addButtonEnable;
	BOOL* m_addButtonExist;
	BOOL* m_onAddButton;

	BOOL CheckAddButtonDown(int x,int y);

	void SetAddButtonEnable(int n,BOOL flg = TRUE);
	void SetAddButtonExist(int n,BOOL flg = TRUE);
	BOOL GetAddButtonEnable(int n);
	BOOL GetAddButtonExist(int n);

	int SearchButton(int n);
	void PutAllAddButton(void);

	void PrintAddButton(int btn,int md = 0,BOOL updateFlag = TRUE);

	int LoadMaskPic(LPSTR name);
	int m_maskPicKosuu;
	int m_maskPicKosuuMax;
	HBITMAP* m_maskBitmap;
	SIZE* m_maskPicSize;

	void PutMaskPic(int n,int x,int y,BOOL updateFlag = TRUE);

	int LoadPic(LPSTR name);
	int m_picKosuu;
	int m_picKosuuMax;
	HBITMAP* m_picBitmap;
	SIZE* m_picSize;

	void PutPic(int n,int x,int y,BOOL updateFlag = TRUE);

	void BltMaskPic(int n,int x,int y,int srcX,int srcY,int sizeX,int sizeY,BOOL updateFlag = TRUE);
	void BltPic(int n,int x,int y,int srcX,int srcY,int sizeX,int sizeY,BOOL updateFlag = TRUE);

	int m_saveType;
	BOOL m_dataLoaded;

	LPSTR m_saveFolderName;
	LPSTR m_saveFileName;
	char* m_saveFolderNameBuffer;
	char* m_saveFileNameBuffer;
	int m_saveFileSize;

	BOOL CheckShakeWindow(int dx,int dy);
	BOOL CheckTrunWindow(int dx,int dy);

	int m_shakeSleepTime;
	int m_turnSleepTime;
	int m_shakeCheckMove;
	int m_turnCheckMove;
	int m_shakeCheckTh;
	int m_turnCheckTh1;
	int m_turnCheckTh2;
	int m_shakeCheckCount;
	int m_turnCheckCount;
	int m_shakeCount;
	int m_turnCount;
	int m_shakeLastTh;
	int m_turnLastTh;
	int m_turnLastDeltaTh;
	int m_shakeSleepCount;
	int m_turnSleepCount;

	BOOL LoadData(void);
	BOOL SaveData(void);

//	int m_saveDataSize;
	int* m_saveData;

	void SetLoginoutTime(void);
	SYSTEMTIME m_loginTime;

	int GetIntervalMinute(void);

	void DeleteTaskIcon(void);


	void MyBoxFill(int putX,int putY,int sizeX,int sizeY,int r,int g,int b,BOOL updateFlag = FALSE);
private:
};





#endif
/*_*/

