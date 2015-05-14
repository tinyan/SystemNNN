//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONSELECTOBJECT__
#define __NNNLIB_COMMONSELECTOBJECT__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

//class CPrintGameDate;

class CCommonButtonGroup;
class CSelectObjectSetup;
class CPicture;

class CCommonSelectObject : public CCommonGeneral
{
public:
	CCommonSelectObject(CGameCallBack* lpGame,int extMode = 0);
	virtual ~CCommonSelectObject();
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

	virtual void StartUserCommand(int paraKosuu,int* paraPtr);

protected:
	int m_selectObjectMax;
	CSelectObjectSetup** m_selectObjectSetup;
	int m_selectObjectType;

	int m_selectObjectTypeVarNumber;
	int m_selectObjectResultVarNumber;
	int m_selectObjectAddResultVarNumber;

	int m_lastType;

	CPicture** m_objectPicture;
	CPicture** m_addPicture;
	int m_objectPictureMax;
	int m_addPictureMax;

	CPicture* GetObjectPicture(int n);
	CPicture* GetAddPicture(int n);
	void ExpandObjectPicture(int n);
	void ExpandAddPicture(int n);

	CCommonButtonGroup* m_placeButtonGroup;
	CCommonButtonGroup* m_charaButtonGroup;


	int m_addPrintX;
	int m_addPrintY;

	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

//	int m_placeAppearFlag;
	int m_charaFlag;
	int m_selectOkFlag;
	int m_selectCharaOnlyFlag;
//	int m_returnCharaNumberFlag;
	int m_charaPrintUpper;

//	int m_selectPlaceResultVarNumber;
//	int m_selectCharaResultVarNumber;


	int* m_placeExistVarNumber;
	int* m_placeSelectOkVarNumber;
	int* m_placeCharaVarNumber;


	BOOL* m_existFlag;
	BOOL* m_selectOk;
	BOOL* m_selectOkFlagWork;
	int* m_chara;





	int m_charaCustomFlag;



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

