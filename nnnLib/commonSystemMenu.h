//
// SystemMenu.h
//

#if !defined __NNNLIB_COMMONSYSTEMMENU__
#define __NNNLIB_COMMONSYSTEMMENU__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CMenuButtonSetup;
class CMenuButtonGroup;
class CCommonButtonGroup;

//class CSuperButtonSetup;
//class CCommonButtonGroup;

class CCommonSystemMenu : public CCommonGeneral
{
public:
	CCommonSystemMenu(CGameCallBack* lpGame);
	virtual ~CCommonSystemMenu();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	static int m_checkKeyList[];
	static char m_buttonName[][16];

	static char m_defaultDialogFileName[];
//	static char m_defaultDialogButtonFileName[];

//	static char m_defaultMenuFileName[];
	static char m_defaultMenuBaseFileName[];
	static char m_defaultBackScreenFileName[];

	virtual void CreateStartScreen(void);

	void SetSceneMode(BOOL flg = TRUE);

	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

	int GetOptionKosuu(void){return m_optionKosuu;}
	int GetExpOptionMode(int n){return m_expOptionMode[n];}
	int GetExpCommandMode(int n){return m_expOptionCommand[n];}
	int GetExpShortCutKey(int n);
	int GetExpSound(int n){return m_expOptionSound[n];}
protected:
	CMenuButtonGroup* m_menu;
	CMenuButtonSetup* m_menuButtonSetup;

	CCommonButtonGroup* m_dialogButton;

	BOOL m_warningFlag;
	int m_warningPrintFlag;

//	LPSTR m_dialogFileName;

	int m_dialogX;
	int m_dialogY;


	int m_backScreenEffectNega;
	int m_backScreenEffectGrey;
	int m_backScreenEffectMulti;
	int m_backScreenEffectAddSub;


	int m_backScreenColorR;
	int m_backScreenColorG;
	int m_backScreenColorB;

	int m_backScreenMultiR;
	int m_backScreenMultiG;
	int m_backScreenMultiB;

	int m_backScreenType;

	LPSTR m_backScreenFileName;

	int m_saveButtonNumber;
	int m_loadButtonNumber;
	int m_configButtonNumber;
	int m_windowButtonNumber;
	int m_messageSkipButtonNumber;
	int m_backlogButtonNumber;
	int m_autoModeButtonNumber;
	int m_cancelButtonNumber;
	int m_exitButtonNumber;
	int m_messageSkipButtonNumber2;


	int m_outClickReturnFlag;







//	virtual void DisableMenu(int n);
//	BOOL m_disableMenuFlag;
	BOOL m_disableLoadFlag;
	BOOL m_disableSaveFlag;

//	CMyButtonGroup* m_menu;
//	CMyButtonGroup* m_button;

//	CPicture* m_menuBasePic;
//	CPicture* m_menuBaseDown;

//	int m_subMode;

	int m_dialogSizeX;
	int m_dialogSizeY;
//	int m_dialogPrintX;
//	int m_dialogPrintY;
//	int m_buttonSizeX;
//	int m_buttonSizeY;
//	int m_buttonPrintX;
//	int m_buttonPrintY;
//	int m_buttonNextX;
//	int m_buttonNextY;

	BOOL m_clickingFlag;



	int m_optionWait[20];
	int m_optionPercent[20];
	int m_optionSpeed[20];
	int m_optionSrcX[20];
	int m_optionSrcY[20];
	int m_optionSrcMode[20];


	BOOL CheckAllOptionPrint(void);
	int m_optionStartPercent100;
	int m_optionStartSpeed100;

	void CalcuStartOption(void);

	int m_optionPrintMode;

	int m_optionKosuu;

	int m_optionPrintX ;
	int m_optionPrintY;
	int m_optionSizeX;
//	int m_optionUpSizeY;
//	int m_optionDownSizeY;
	int m_optionSizeY;

	int m_optionNextY;

	int m_basePrintX;
	int m_basePrintY;
	int m_baseSizeX;
	int m_baseSizeY;

//	void PutUpMenu(void);
//	void PutDownMenu(int ps = 100);
	void PutMenuBase(int ps = 100);

	void PutOption(int n, int sizeY);

	LPSTR m_filenameDialog;
	LPSTR m_filenameMenu;
	LPSTR m_filenameMenuBase;


	int m_buttonSizeX[2];
	int m_buttonSizeY[2];
	int m_buttonPrintX[2];
	int m_buttonPrintY[2];


	virtual void BeforeInit(void);
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	int m_backScreenEffectType;


//	void ScreenEffectAddSub(void);
//	void ScreenEffectGrey(void);
//	void ScreenEffectNega(void);

//	int m_superMenuFlag;
//	CSuperButtonSetup* m_superMenuSetup[9+1];
//	CPicture* m_superPic[9+1];

	void CalcuCombine(void);
	int m_setDefaultShortCutFlag;

	static int m_defaultAccelKey[];

	int m_optionStartPrintType;
	int m_optionStartPrintTime;

	int m_screenToGetPutFlag;
	int m_getWithMessageFlag;

	LPSTR m_sceneBackFileName;
	LPSTR m_sceneEndFileName;

	BOOL CheckSceneMode(void);

	BOOL m_sceneMode;
	BOOL m_nextIsSceneMode;

	BOOL m_returnToGameFlag;
	int m_warningMenuPrintFlag;

	//int* m_expOptionNumber;
	int* m_expOptionMode;
	int* m_expOptionCommand;
	int* m_expOptionSound;

	int m_exitWarningSound;

private:
};

#endif
/*_*/

