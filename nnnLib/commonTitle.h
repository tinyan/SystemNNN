//
// commonTitle.h
//

#if !defined __NNNLIB_COMMONTITLE__
#define __NNNLIB_COMMONTITLE__

class CGameCallBack;

//class CMyButtonGroup;

class CMenuButtonSetup;
class CMenuButtonGroup;
class CAutoSelectControl;

class CCommonTitle : public CCommonGeneral
{
public:
	CCommonTitle(CGameCallBack* lpGame);
	virtual ~CCommonTitle();
	virtual void End(void);

	virtual int Calcu(void);
	virtual int Print(void);
	virtual int Init(void);


	virtual void ReCreateExitScreen(void);
	virtual void CreateStartScreen(void);

	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

protected:
	BOOL m_disableLoadFlag;
	BOOL m_disableOmakeFlag;

//	LPSTR m_filenameBG;
//	LPSTR m_filenameButton;

	static char m_defaultBGFileName[];
//	static char m_defaultButtonFileName[];
//	static char m_defaultSpecialButtonFileNameTag[];

//	int m_menuPrintX;
//	int m_menuPrintY;
//	int m_menuSizeX;
//	int m_menuSizeY;
//	int m_menuNextX;
//	int m_menuNextY;
//	int m_menuKosuuX;
//	int m_menuKosuuY;

	CMenuButtonGroup* m_menu2;

//	CMyButtonGroup* m_menu;

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

//	int m_addButtonKosuu;
//	int m_addModeKosuu;
//	int* m_addButtonVarNumber;
//	int m_addModeVarNumber;
//	int* m_addButtonExeType;
//	int m_addButtonReturnVarNumber;

//	int m_useSpecialButtonFlag;

//	int* m_printZahyoX;
//	int* m_printZahyoY;

	int m_autoRestartTime;
	int m_autoRestartCount;


	int m_extMode;

	int m_extModeKosuu;
	int m_basicButtonKosuu;
	int m_extButtonKosuu;

	int m_extModeCheckVar;
	int m_extModeReturnVar;

	int m_superMode;
	CMenuButtonSetup* m_menuButtonSetup;

	int m_scriptEndIsModeEnd;

	int m_menuStartCount;

	int m_menuStartWaitTime;
	int m_menuStartEffectTime;
	int m_menuStartEffectType;

	int m_menuStartDeltaX;
	int m_menuStartDeltaY;

	int GetStartWaitMode(void);
	void EndStartWaitMode(void);

	int m_restartNextMode;

	int m_newGameFlag;
	int m_extScenario;

	int m_autoDebugWait;
	CAutoSelectControl* m_autoSelectControl;

};



#endif
/*_*/

