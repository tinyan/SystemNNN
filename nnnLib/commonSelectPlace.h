//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONSELECTPLACE__
#define __NNNLIB_COMMONSELECTPLACE__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

//class CPrintGameDate;

class CCommonButtonGroup;

class CCommonSelectPlace : public CCommonGeneral
{
public:
	CCommonSelectPlace(CGameCallBack* lpGame,int extMode = 0);
	virtual ~CCommonSelectPlace();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	static char m_defaultAnswerName[];
	static char m_defaultAnswerCharaName[];

	static char m_defaultFileNameBG[];
	static char m_defaultFileNameChara[];
	static char m_defaultFileNameCharaBase[];

	virtual void CreateStartScreen(void);

protected:

	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

	int m_placeKosuu;
	int m_placeAppearFlag;
	int m_charaFlag;
	int m_selectOkFlag;
	int m_selectCharaOnlyFlag;
	int m_returnCharaNumberFlag;
	int m_charaPrintUpper;

	int m_selectPlaceResultVarNumber;
	int m_selectCharaResultVarNumber;


	int* m_placeExistVarNumber;
	int* m_placeSelectOkVarNumber;
	int* m_placeCharaVarNumber;


	BOOL* m_existFlag;
	BOOL* m_selectOk;
	BOOL* m_selectOkFlagWork;
	int* m_chara;


	int m_charaDeltaX;
	int m_charaDeltaY;


	POINT* m_areaZahyo;
	POINT* m_charaDelta;
	POINT* m_charaMove;

	int m_charaCustomFlag;

	POINT GetAreaZahyo(int n);
	POINT GetCharaZahyo(int n);

	int m_charaSizeX;
	int m_charaSizeY;

	int m_selectedNumber;

	BOOL CheckSelectOk(int n);


	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	virtual void PrintBeforeButton(void){}
	virtual void PrintAfterButton(void){}


	int m_buttonMode;

	int m_useEffectPicKosuu;
	int m_useSuperPicKosuu;

	CPicture* GetUseOkPicture(void);
	CCommonButtonGroup* m_placeButtonGroup;

	virtual void PrintAllChara(void);

	LPSTR m_allCharaFileName;

	int m_charaAnimePattern;
	int m_charaAnimeSpeed;
	int m_charaAnimeType;
	int m_charaAnimeCount;

	int m_allCharaFlag;
	CPicture** m_charaPic;
	LPSTR m_charaPicName;

	int* m_charaPicPattern;
	void SetCharaPicPattern(int n,int pat);
	void SetCharaMoveDelta(int n,POINT pt);

	int m_firstWait;

	int GetOnPlace(POINT pt,BOOL cannotOk = FALSE);

	int m_lastOnButton;
	int m_autoCannotOk;
	int m_autoPicLoad;
	int m_autoPicLayer[16];
	int m_lastAutoPic;
	LPSTR m_autoPicTag[16];
	int m_autoPicRestartBackScript;
	void LoadAutoPic(int place,BOOL checkRestartFlag = TRUE);

	void ParentFinalExitRoutine(void);

//	int m_keyMoveEnable;
//	int m_lastKeyButton;
//	int m_keyMoveCannotSelectOk;
//	int m_keyMoveUpDownEnable;
//	int m_keyMoveLeftRightEnable;


	void MoveCursorToPlaceButton(int pl);

	int m_backLogOk;
	int m_onButtonVarNumber;


	int m_onButtonChangeToRestartBackScript;

//	CPrintGameDate* m_printGameDate;
//	int m_gameDatePrintFlag;

//	int m_gameYearVarNumber;
//	int m_gameDateVarNumber;
//	POINT m_gameDatePrintZahyo;

private:

};

#endif
/*_*/

