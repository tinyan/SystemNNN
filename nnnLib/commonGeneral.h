//
// general.h
//

#if !defined __NNNLIB_GENERAL__
#define __NNNLIB_GENERAL__


//#include "myMouseStruct.h"

class CGameCallBack;
class CPicture;
class CMyMouseStatus;
class CInputStatus;
class CNameList;
class CBackButton;
class CCommonUpDownButtonGroup;
class CUpDownButtonGroup;
class CCommonButton;
class CCommonBackButton;
class CCommonUpdownBack;
class CPrintGameDate;
class CPrintAnimeLayer;

class CCommonSystemModeList;

//class CSuperButtonSetup;

class CCommonGeneral
{
public:
	CCommonGeneral(CGameCallBack* lpGame);
	virtual ~CCommonGeneral();

	int GeneralCalcu(void);
	int GeneralPrint(void);
	int GeneralInit(void);
	int GeneralEndMode(void);

	int OmakeGeneralCalcu(BOOL mustFlag = FALSE);
	int OmakeGeneralPrint(BOOL mustFlag = FALSE);
	int OmakeGeneralInit(void);
	int OmakeGeneralEndMode(void);

	int GeneralFinalExitRoutine(void);

	virtual int GeneralBack(void);

	virtual void SetBackMode(int mode);
	virtual int GetBackMode(void){return m_backMode;}
	virtual void AfterInitNewGame(void){}
	virtual void InitByLoad(void){}
	virtual void CreateExitScreen(void);
	virtual void StartUserCommand(int paraKosuu,int* paraPtr){}

	virtual void GetExtDataForSave(LPVOID ptr,int extNumber = 0) {};
	virtual void SetExtDataByLoad(LPVOID ptr,int extNumber = 0) {};

	virtual void Function(int type,int paraKosuu,int* lpParam){}
	virtual void ExitGame(void){}

	virtual int CheckOtherSetup(int para1,int para2 = 0,LPVOID lpParam = NULL);

protected:
	virtual int Calcu(void) = 0;
	virtual int Print(void) = 0;
	virtual int Init(void) = 0;
	virtual int EndMode(void) {return -1;}
	virtual void FinalExitRoutine(void) {}
	virtual void ParentFinalExitRoutine(void){}


	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}


//	void SetReturnCode(int cd, int cnt=4);

	BOOL CheckClick(BOOL bTrig2Flag = FALSE);

	CPicture* m_commonBG;
	CPicture* m_commonParts;
//	CPicture* m_commonButton;
//	CPicture* m_commonUpDown;
	int* m_commonBuffer;

//	int m_returningCount;
//	BOOL m_returningFlag;

//	int m_returningCode;

	CGameCallBack* m_game;

//	MOUSESTATUS m_mouseStatus;
	CMyMouseStatus* m_mouseStatus;
	CInputStatus* m_inputStatus;

	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);

	CNameList* m_setup;

	BOOL LoadSetupFile(LPSTR filenameonly, int varKosuu = 64);


	int m_backMode;
	int m_classNumber;

	CCommonBackButton* m_back;
	CCommonBackButton* m_createBackButton;

//	CMyCommonButton* m_newBack;
//	CMyCommonButton* m_newCreateBackButton;

	CCommonUpDownButtonGroup* m_updown;
//	CCommonUpdownButtonGroup* m_updown2;
	CCommonUpDownButtonGroup* m_createUpDownButton;
//	CCommonUpdownButtonGroup* m_createUpDownButton2;

	CCommonUpdownBack* m_updownBack;

	int m_enterExitVoiceFlag;
	LPSTR m_enterVoiceFileName;
	LPSTR m_exitVoiceFileName;
	
	int m_dialogVoiceFlag;
	LPSTR m_dialogVoiceFileName;
	LPSTR m_dialogYesVoiceFileName;
	LPSTR m_dialogNoVoiceFileName;

	void GetEnterExitVoiceFileName(void);
	void GetDialogVoiceFileName(void);

	int m_dialogVoiceWaitTime;
	int m_enterVoiceWaitTime;
	int m_exitVoiceWaitTime;
	int m_dialogVoiceCount;
	int m_enterVoiceCount;
	int m_exitVoiceCount;

	void OnEnterExitAreaForVoice(void);
	void OnExitExitAreaForVoice(void);

	int m_exitFadeOutSpecialMode;

	int m_enterFadeInType;
	int m_exitFadeOutType;
	int m_exitFadeOutTypeSpecial;

	int m_enterFadeInCount;
	int m_exitFadeOutCount;
//	int m_exitFadeOutCountSpecial;

	int m_enterFadeInTime;
	int m_exitFadeOutTime;
	int m_exitFadeOutTimeSpecial;

	int m_enterFadeInSkipOkFlag;
	int m_exitFadeOutSkipOkFlag;
	int m_exitFadeOutSkipOkFlagSpecial;

	int m_enterFadeInColorR;
	int m_enterFadeInColorG;
	int m_enterFadeInColorB;

	int m_exitFadeOutColorR;
	int m_exitFadeOutColorG;
	int m_exitFadeOutColorB;

	int m_exitFadeOutColorSpecialR;
	int m_exitFadeOutColorSpecialG;
	int m_exitFadeOutColorSpecialB;

	void GetFadeInOutSetup(void);
	void GetBGMSetup(void);
	void GetBackExecSetup(void);
	void GetAddLayerSetup(void);
	void GetAnimeLayerSetup(void);
	void GetDisableQuickButtonSetup(void);


	void GetKeyMoveSetup(int tateyoko = 0,int updown = 1,int leftRight = 1);

	virtual void PlayCommonBGM(void);
	virtual int PrintEnterFadeIn(void);
	virtual int PrintExitFadeOut(void);

//	virtual void CreateExitScreen(void);
	virtual void ReCreateExitScreen(void) {}
	virtual void CreateEnterScreen(void);

	virtual void CreateStartScreen(void);

	virtual void GetAllPrintSetup(void);

	int m_specialPrintMode;

	CPicture* m_exitScreen;
	CPicture* m_enterScreen;

	void FillPicture(CPicture* lpPic, int colR, int colG, int colB);

	virtual int ReturnFadeOut(int returnCode = -1);

	int m_createExitScreenFlag;
	int m_fillExitScreenFlag;
	int m_createExitScreenFlagSpecial;
	int m_fillExitScreenFlagSpecial;

	BOOL CheckSpecialFadeOutMode(void);

	int m_backButtonPrintX;
	int m_backButtonPrintY;

	int m_backButtonSizeX;
	int m_backButtonSizeY;

	int m_backButtonAnime;	//Šg’£—p
	int m_backButtonType;	//Šg’£—p

	int m_updownButtonType;

	int m_upPrintX;
	int m_upPrintY;
	int m_downPrintX;
	int m_downPrintY;
	int m_updownSizeX;
	int m_updownSizeY;

	int m_updownButtonAnime;

//	virtual void GetBackButtonPara(void);
	virtual void CreateBackButton(void);
	virtual void CreateUpDownButton(void);

	virtual void CreateUpDownBack(void);

	virtual void FillExitScreen(void);
	virtual void SetBackButtonZahyo(void);

	int m_modeBGMNumber;
	int m_modeBGMMustRestartFlag;
	int m_modeBGMLoop;
	int m_modeBGMVolume;

	int m_modeBGMFadeInTime;

	int m_backScriptFlag;
	LPSTR m_backScriptName;

	virtual void PlayButtonSound(CCommonButton* lpButton,int buttonReturnCode);

	void PrintBackScriptOrBG(void);

	void SetBackScriptLoopEnd(BOOL flg = TRUE){m_backScriptEndFlag = flg;}

	BOOL m_backScriptEndFlag;
	int m_backScriptLoopFlag;

//	CSuperButtonSetup* m_superBackButtonSetup;
//	CSuperButtonSetup* m_superUpButtonSetup;
//	CSuperButtonSetup* m_superDownButtonSetup;

	int m_superBackButtonFlag;
	int m_superUpDownButtonFlag;

	BOOL GetModeNumberBySetup(LPSTR name,int *lpVar);
	int GetModeNumberByName(LPSTR name);
	//static char m_systemClassNameList[][32];

	static char m_defaultUpButtonFileName[];
	static char m_defaultDownButtonFileName[];
	static char m_defaultBackButtonFileName[];

	static char m_disableQuickButtonCheckMode[][64];

	int m_nextMode;

	void LoadBackBG(void);
	LPSTR m_filenameBG;
	LPSTR m_filenameBack;
	LPSTR m_filenameUp;
	LPSTR m_filenameDown;
	void LoadUpDownButtonPic(void);
	void LoadBackButtonPic(void);
	void SetUpDownZahyo(void);

	virtual int ProcessUpDownBack(int rt);
	virtual int ProcessButtonGroup(int rt);
	virtual int ProcessCommonButton(int rt);

	int m_mustAllPrintFlag;
	BOOL m_lastPrintExitScreenFlag;

	BOOL m_exitModeFlag;

	int m_miniGameFlag;

	virtual BOOL CheckMiniGame(void);
	virtual void SetFinalExitRoutine(void);


	int m_keyMoveEnable;
	int m_keyMoveUpDownEnable;
	int m_keyMoveLeftRightEnable;
	int m_keyMoveCannotSelectOk;
	int m_lastKeyButton;//??
	int m_keyTateYoko;
	int m_keyActionFlag;

	virtual void ClearKeyMove(void);
	virtual int CalcuKeyMove(void);

	virtual int GetOnKeyArea(POINT pt){return -1;}
	virtual void SetCursorToKeyArea(int pl){}
	virtual int KeyMoveAction(int delta,int deltaX = 0,int deltaY = 0){return -1;};


	CPrintGameDate* m_printGameDate;
	int m_gameDateLayerPrintFlag;
	int m_generalGameYearVarNumber;
	int m_generalGameDateVarNumber;

	virtual void PrintGameLayer(void);
	virtual void PrintAnimeLayer(void);

	int m_animeLayerKosuu;
	CPrintAnimeLayer** m_printAnimeLayer;

	int m_gameLayerFirst;
	int m_animeLayerFirst;

	CCommonSystemModeList* m_systemModeList;

	int* m_disableQuickButtonWork;


	void SetClassNumber(int n);
private:
	void GeneralEnd(void);
	int m_returnFadeOutCode;
//	int* m_screenBuffer;
	BOOL m_finalExitFlag;

};


#endif
/*_*/

