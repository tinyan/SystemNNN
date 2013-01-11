//
// commonOmake.h
//

#if !defined __NNNLIB_COMMONOMAKE__
#define __NNNLIB_COMMONOMAKE__


class CGameCallBack;

class CMenuButtonSetup;
class CMenuButtonGroup;

class CMyButtonGroup;
class CCGDataControl;
class CSceneDataControl;

class CCommonOmake : public CCommonGeneral
{
public:
	CCommonOmake(CGameCallBack* lpGame);
	virtual ~CCommonOmake();
	virtual void End(void);

	virtual int Calcu(void);
	virtual int Print(void);
	virtual int Init(void);

	virtual void ReCreateExitScreen(void);
	virtual void CreateStartScreen(void);

protected:
//	LPSTR m_filenameBG;
//	LPSTR m_filenameButton;

	static char m_defaultBGFileName[];
	static char m_defaultButtonFileName[];

	int m_existFlag[4];

	int m_menuPrintX;
	int m_menuPrintY;
	int m_menuSizeX;
	int m_menuSizeY;
	int m_menuNextX;
	int m_menuNextY;
	int m_menuKosuuX;
	int m_menuKosuuY;

	int m_autoCGCharaFlag;
	int m_autoSceneCharaFlag;

//	CMyButtonGroup* m_menu;
	CMenuButtonGroup* m_menu2;

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	int m_extMode;

	int m_extModeKosuu;
	int m_basicButtonKosuu;
	int m_extButtonKosuu;

	int m_extModeCheckVar;
	int m_extModeReturnVar;

	int m_superMode;
	CMenuButtonSetup* m_menuButtonSetup;
//	int m_useSpecialButtonFlag;
//	virtual void CreateStartScreen(void);

//	int m_noMidiFlag;

	int m_menuStartCount;

	int m_menuStartWaitTime;
	int m_menuStartEffectTime;
	int m_menuStartEffectType;

	int m_menuStartDeltaX;
	int m_menuStartDeltaY;

	int GetStartWaitMode(void);
	void EndStartWaitMode(void);

	CCGDataControl* m_cgDataControl;
	CSceneDataControl* m_sceneDataControl;
//	int m_miniGameAreaKosuu;
//	RECT* m_miniGameArea;

//	int CheckInMiniGameArea(POINT pt);
//	int m_miniGameAreaNumber;
//	int m_miniGameOkKosuu;

//	int m_miniGameCheckVar;
private:
};



#endif
/*_*/

