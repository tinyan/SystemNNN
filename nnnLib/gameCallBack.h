//
// gameCallBack.h
//

#if !defined __NNNLIB_GAMECALLBACK__
#define __NNNLIB_GAMECALLBACK__

#define MODE_MAX 100
#define OMAKEMODE_KOSUU 32

#include "scriptCallBack.h"
#include "..\..\systemNNN\nyanEffectLib\allEffect.h"

class CFukaPrint;
class CFpsPrint;

//class CScriptCallBack;

class CPicture;

class CVarNumber;
class CNameList;
class CSaijitsuList;


class CCommonGeneral;
class CMyFont;
class CMyMessage;
class CCommonBackButton;
class CCommonUpDownButtonGroup;

class CCommonFileControl;

class CMyDirectDraw;
class CMMX;

class CCommonSystemFile;
class CEffect;
class CAllEffect;
class CSceneList;
class CSceneDataControl;
class CCGDataControl;

//class CViewControl;

class CExecScript;
class CMIDIPlayer;
class CMixerControl;
class CMyDirectSound;

class CInputStatus;
class CMyMouseStatus;
class CMyKeyStatus;


//class CCDControl;


class CCommonMessageWindow;

class CSystemPicture;

class CMovingLayer;
class CTaihi;
class CGameUtil;
//class CCommonWave;
class CWaveData;

class CPrintDebugParam;

class CMessageCursor;
class CGameMouse;

class CSceneOptionButton;

class CDataFileSetup;

class CMainControl;

class CBackExecClass;
class CMyCommonButton;
class CSuperButtonSetup;

class CMyGraphics;
class CSuperButtonPicture;
//class CWaveMusic;

class CMusicControl;

class CMyDirectSoundBuffer;

class CSceneVoice;
class CMyDirectShow;

class CTextureCacheControl;

class CMiniGameBase;
class CShakin;

class CMyTextInputBox;

class CNotice;
class CCommonResultData;

class COmakeClassSupport;

class CCommonSystemModeList;
class CCommonUserCommandList;

class CScriptSoundControl;
class CScriptVoiceControl;

class CAutoSaveDataList;
class CAutoSaveSubData;
class CFaceControl;
class COkikaeData;

class CPrintPlayerStatus;

class CViewControl;

class CAutoSelectControl;

class CGameCallBack : public CScriptCallBack
{
public:
	CGameCallBack(HWND hwnd, HINSTANCE hinstance, CCommonSystemFile* lpSystemFile,int windowSizeX, int windowSizeY, int bpp);
	virtual ~CGameCallBack();
	void End(void);

	virtual void ReceiveUserCommand(int cmd, int paraKosuu, int* paraPtr){}
	virtual void ReceiveUserCommand0(int cmd, int paraKosuu, int* paraPtr);
	virtual void ReceiveUserFunction(int cmd, int paraKosuu, int* paraPtr){}
	virtual void ReceiveUserFunction0(int cmd, int paraKosuu, int* paraPtr);

	virtual int GetVarData(int varNum);
	virtual int GetCalcuVarData(int varNum);
	virtual void SetVarData(int varNum, int dat);


	virtual CPicture* GetCommonBG(void){return m_commonBG;}
	virtual CPicture* GetCommonParts(void){return m_commonParts;}
	virtual CMyMouseStatus* GetMouseStatus(void){return m_mouseStatus;}
	virtual CInputStatus* GetInputStatus(void){return m_inputStatus;}
	virtual CMyFont* GetMyFont(void) {return m_font;}
	virtual CMyMessage* GetMyMessage(void) {return m_message;}


	virtual void ClearF5(void) {m_skipNextCommandFlag = FALSE;}

	virtual void SetYoyaku(BOOL b = TRUE) {	m_yoyakuExecFlag = b;}
	virtual BOOL CheckClickKey(int key);
	virtual void SetSceneMode(BOOL md = TRUE);
	virtual void SetCommonBackMode(int mode, int backMode);
	virtual void ToWindowScreen(BOOL directFlag = FALSE);
	virtual void ToFullScreen(BOOL directFlag = FALSE);
	virtual void ToWindowScreenRoutine(void);
	virtual void ToFullScreenRoutine(void);
	virtual BOOL CheckMessageSkipFlag(void) {return m_messageSkipFlag;}
	virtual void SetMessageSkipFlag(BOOL flg = TRUE) {m_messageSkipFlag = flg;}
	virtual void CalcuEffectOnly(void);
	virtual void CountUpOnly(int n = 1);
	virtual void StopVoice(void);
	virtual void SkipToEffectEnd(void);
	virtual void PrintEffect(BOOL bScreenFlag = FALSE);
	virtual void PrintEffectLayer(int startLayer,int endLayer);

	virtual int* GetCommonBuffer(void) {return m_commonBuffer;}
	virtual void SearchCase(int caseNumber);
	virtual CPicture* GetOverrapPic(int n);
	virtual int GetOverrapType(void) {return m_overrapType;}
	virtual int GetOverrapLength(void) {return m_overrapLength;}
	virtual BOOL CheckMessageSkipMode(void);
	virtual BOOL CheckVoiceFlag(int voiceCharaNumber);
	virtual BOOL CheckVoiceUsedFlag(int voiceCharaNumber);

	virtual void SetVoiceFlag(int voiceCharaNumber, BOOL flg = TRUE);
	virtual void SetSaveMode(int mode) {m_saveMode = mode;}
	virtual void PrintOverrap(int count);
	virtual BOOL CheckDemoMode(void);
	
	virtual bool CheckPlayerVoice(int playerNumber);

	virtual void AddBackLogMessage(LPSTR mes,int colR=255, int colG=255, int colB=255);
	virtual BOOL CheckMessageHaveVoice(void) {return m_messageHaveVoiceFlag;}
	virtual int GetVoiceLength(void) {return m_messageVoiceLength;}
	virtual void SetMessageRead(int mesNum, int sptNum = -1);
	virtual BOOL CheckMessageRead(int mesNum, int sptNum = -1);
	virtual void ChangePreColor(int n, int colorR, int colorG, int colorB);
	virtual int GetPastTime(void) {return m_pastTime2;}
	virtual BOOL CheckNoSkipFrame(void);
	virtual BOOL CheckSceneMode(void) {return m_sceneMode;}
	virtual void PrintMessageWindow(BOOL bFlag = FALSE,BOOL nameWindowPrintFlag = FALSE,POINT* lpDeltaPoint = NULL);
	virtual void PrintMessageWindowDirect(BOOL bFlag = FALSE,BOOL nameWindowPrintFlag = FALSE,POINT* lpDeltaPoint = NULL);
	virtual void PrintMessageWindowByCheck(BOOL bFlag = FALSE,BOOL nameWindowPrintFlag = FALSE,POINT* lpDeltaPoint = NULL);
	virtual CPicture* GetSystemPicture(LPSTR filename,BOOL b256Flag = FALSE);
	virtual int GetSystemParam(int param);
	virtual void SetSystemParam(int param, int dat);
	virtual void PostCloseMessage(void);
	virtual CCommonBackButton* GetBackButton(void) {return m_backButton;}
	virtual CMyCommonButton* GetNewBackButton(void){return m_newBackButton;}

	virtual CCommonFileControl* GetFileControl(void) {return m_fileControl;}
	virtual void ReplayVoice(LPSTR voiceFileName);
	virtual void SetOption(BOOL flg = TRUE) {m_optionFlag = flg;}
	virtual void SetSceneButton(BOOL flg = TRUE) {m_sceneButtonFlag = flg;}
	virtual void PreInitGameCallBack(int classNumber) {}

	virtual void GetForSave(int cd, LPVOID ptr);

	virtual void GetGameStatusForSave(LPVOID ptr);
	virtual void GetMiniCGForSave(LPVOID ptr, int type = -2, int customSizeX = 132,int customSizeY = 100);
	virtual void GetVarForSave(LPVOID ptr);
	virtual void GetEffectForSave(LPVOID ptr);
	virtual void GetEffectFileNameForSave(LPVOID ptr);
	virtual void GetMessageForSave(LPVOID ptr);
	virtual void GetOmakeClassDataForSave(LPVOID ptr);
	virtual void GetCutinForSave(LPVOID pt);
	virtual void GetLogForSave(LPVOID pt);

	virtual void SetByLoad(int cd, LPVOID ptr);

	virtual void SetGameInfoByLoad(LPVOID ptr);
	virtual void SetGameStatusByLoad(LPVOID ptr);
	virtual void SetVarByLoad(LPVOID ptr);
	virtual void SetEffectByLoad(LPVOID ptr);
	virtual void SetEffectFileNameByLoad(LPVOID ptr);
	virtual void SetMessageByLoad(LPVOID ptr);
	virtual void SetOmakeClassDataByLoad(LPVOID ptr);
	virtual void SetCutinByLoad(LPVOID ptr);
	virtual void SetLogByLoad(LPVOID ptr);


	virtual int GetWeek(int dayMonth);
	virtual void PlayCommonSystemSound(int commonSoundNumber);
	virtual int GetMusicMode(void);
	virtual void MakeMiniCG(void);
	virtual int InitNewGame(int uraMode = 0, BOOL demoFlag = FALSE,int setVar = -1,int setData = 0);
	virtual void InitLoadGame(void);
	virtual void InitOpeningMode(int para1 = -1,int para2 = 1);
	virtual void InitLoadOmake(void);


//	virtual void SetUraMode(int md) {}
	virtual void SetDemoMode(BOOL b = TRUE);
	virtual void ResetAllShakin(void);

//	virtual BOOL CheckOptionOff(void);

	virtual	void FrameControl(int cnt);
	virtual void AdjustMouseZahyo(void);

	virtual LRESULT GameProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//	virtual MCIDEVICEID GetCDDeviceID(void);
//	virtual void EndCD(void){}

	virtual void ClearAllKey(void);
	virtual void ChangeScreenMode(BOOL directFlag = FALSE);

	virtual void EndGame(void);
	virtual void YoyakuArea(RECT* lpRect);

//	virtual void ShakinHensai(void);
	virtual void YoyakuShori(void);

	virtual BOOL CheckSaijitsu(int year,int month, int day);

	virtual void SetSystemVarNumber(void);
	virtual void PrintInitializeMessage(void);

	virtual BOOL CheckInitDirectX(void);
	virtual BOOL NextSceneFilm(void);
	
	virtual BOOL StartSceneMode(void);

	virtual void SetDesktopWindowSize(int sizeX,int sizeY);
	virtual void SetDesktopWindowStart(POINT pt);
	virtual void SetDesktopWindowEnd(POINT pt);

	virtual void Erase(void);
	virtual void Flush(void);

	virtual int GetVarNumber(LPSTR varName);

	virtual void AfterInitNewGame(int uraMode = 0, BOOL demoFlag = FALSE);
	virtual void AfterInitLoadGame(void);
	virtual CCommonUpDownButtonGroup* GetCommonUpDown(void) {return m_upDown;}

	virtual void SaveSystemFile(void);


//	virtual void OptionAnime(int cnt = 1);
//	virtual void SceneButtonAnime(int cnt = 1);
	virtual void CursorAnime(int cnt = 1);
	virtual void SetMyCursor(int x, int y, int pat);
	virtual void SetMyCursor(int pat = 0);

//	virtual CMIDIPlayer* GetMIDI(void) {return m_midi;}

	virtual void SetBGMVolumeOnly(int volume);



	virtual CMyDirectSound* GetMyDirectSound(void) {return m_directSound;}
	virtual CMyDirectShow* GetMyDirectShow(void){return m_directShow;}

	virtual BOOL CheckBossMode(void) {return m_bossMode;}
	virtual void SetBossMode(BOOL flg = TRUE) {m_bossMode = flg;}

	virtual void SetOptionVarOn(BOOL flg = TRUE);
	virtual void WindowOn(BOOL flg = TRUE);

	virtual void PlaySystemSound(int n,int volumeType = 0);
//	virtual void PlaySoundRoutine(CCommonWave* wave,int n);
	virtual void PlaySystemWaveFilename(LPSTR filename,int deltaVolume = 0);



	virtual int GetExtDataBlockKosuu(void) {return m_extSaveDataKosuu + m_autoExtDataLoadKosuu + m_autoExtSubDataLoadKosuu;}
	virtual int GetExtDataBlockSize(int extNumber);

	virtual void GetExtDataForSaveGeneral(LPVOID ptr,int extNumber = 0);
	virtual void SetExtDataByLoadGeneral(LPVOID ptr,int extNumber = 0);
	virtual void GetExtDataForSave(LPVOID ptr,int extNumber = 0) {};
	virtual void SetExtDataByLoad(LPVOID ptr,int extNumber = 0) {};

	virtual int GetGameVersion(void) {return m_gameVersion;}
	virtual void SetGameVersion(int highVersion = 0, int middleVersion = 0, int lowVersion = 0);

//	virtual void CreateCGList(int kosuu);

	virtual int GetBGMKosuu(void) {return m_bgmKosuu;}
	virtual LPSTR GetBGMFileName(int n);
	virtual LPSTR GetBGMName(int n);

	virtual void PlaySystemVoiceByFileName(LPSTR filename,BOOL firstOffFlag = TRUE,BOOL sameBufferFlag = FALSE);

	virtual BOOL CheckResetVolume(int volumeType);

	virtual HWND GetGameHWND(void) {return m_hWnd;}

	CNameList* GetVarList(void) {return m_varList;}

	virtual void PrintDebugParam(void);
	virtual void PrintDebugBack(void);

	virtual void ReceiveScriptCommand(int cmd, int para1, LPVOID para2,int para3 = 0);
	virtual void PreReceiveScriptData(int cmd, int para1, LPVOID para2);

	BOOL CreateCommonClass(int modeNumber);
	void CreateAllClass(BOOL taikenFlag = FALSE);





	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);
//	BOOL GetInitGameParam2(int* lpVar, LPSTR name);
//	BOOL GetInitGameString2(LPSTR* lpStr, LPSTR name);

	BOOL GetInitGameParam3(int* lpVar, LPSTR name);

	BOOL LoadSetupFile(LPSTR filenameonly, int varKosuu);
	BOOL LoadSetupFile2(LPSTR filenameonly, int varKosuu);
	BOOL LoadSetupFile3(LPSTR filenameonly, int varKosuu);

	BOOL LoadSetupFileConfig(LPSTR filenameonly, int varKosuu);
	BOOL GetInitConfigParam(int* lpVar, LPSTR name);

	virtual void UserCommandCallBack(void) {}

	CPicture* GetEffectPicture(int n);

	int VoiceToCharaNumber(LPSTR name);
	virtual BOOL CheckVoiceOffByName(LPSTR name);
	virtual int GetVoiceVolumeByName(LPSTR name);

	virtual void GetUserPara(int paraKosuu, int* paraPtr);

	virtual void PrintBackBuffer(void);
	virtual void BltToFront(void);

//	virtual void PrintOption(void);
//	virtual void PrintSceneButton(void);

	virtual BOOL CheckVoiceSpeak(void) {return m_voiceSpeakFlag;}
	void CalcuVoiceSpeak(int cnt = 50);

	virtual LPSTR GetSaveHeaderName(void) {return m_saveHeaderName;}

	virtual void EraseMouse(void);


	virtual void PrintSimpleWipe(int count, int countMax, int type = 2);
	virtual void PrintSimpleWipe(CPicture* lpFromPic,CPicture* lpToPic,int count, int countMax, int type = 2);

	virtual int GetCGBlockNumber(int cgCharaNumber,int cgNumber);

	int GetLayerOff(int var);


	virtual int GetFrameTime(void) {return m_frameTime;}
	virtual int GetDefaultFrameTime(void) {return m_defaultFrameTime;}
	virtual SIZE GetMiniCGSize(void);

	virtual void SetDefaultFrameRate(void) {SetFrameRate(GetDefaultFrameTime());}

	
	int GetConfigData(int n);

	virtual CDataFileSetup* GetDataFileSetup(void) {return m_dataFileSetup;}


	virtual int MainLoop(int cnt) {return 0;};

	void SetReturnCode(int code);
	int GetReturnCode(void);

	virtual BOOL StartModalThread(int modeNumber, int printMode = 0,int stackSize = 0);
	virtual BOOL EndModalThread(void);

//	void SetThreadAddr(LPVOID addr);

	int GetGameMode(void);
	int GetGameMode(int level);
	void SetGameMode(int gameMode);

	BOOL GetQuitFlag(void) {return m_quitFlag;}

	int GetModalLevel(void) {return m_modalLevel;}
	void SetModalLevel(int level) {m_modalLevel = level;}
//	HANDLE GetThreadHandle(int level = -1);
//	unsigned int GetThreadID(int level = -1);

	void SetMainControl(CMainControl* lpMainControl) {m_mainControl = lpMainControl;}

	void StartModeRoutine(int mode);
	void EndModeRoutine(int mode);

	void ChangeOmakeClass(int oldMode, int newMode);
	void ChangeOmakeEnd(int oldMode, int newMode);
	void ChangeOmakeInit(int oldMode, int newMode);



	void CalcuOmake(void);
	void PrintOmake(void);

	int GeneralMainLoop(int cnt);

	virtual void StartMainLoop(int cnt) {}
	virtual void BeforeCalcu(void) {}
	virtual void AfterCalcu(void) {}
	virtual void BeforeOmakeCalcu(void) {}
	virtual void AfterOmakeCalcu(void) {}
	virtual void BeforePrint(void) {}
	virtual void AfterPrint(void) {}
	virtual void BeforeOmakePrint(void) {}
	virtual void AfterOmakePrint(void) {}
	virtual void BeforePrintBackBuffer(void) {}
	virtual void BeforeFlip(void) {}
	virtual void AfterFlip(void) {}

	virtual void BeforeChangeMode(void){}
	virtual void AfterChangeMode(void){}

	virtual void EndMainLoop(void) {}

	void SetModalPrintMode(int level, int md);
	int GetModalPrintMode(int level);

	virtual void SetFrameRate(int frameRate);
	virtual void PreChangeMode(int md){}

	virtual LPSTR GetSaveComment(void) {return NULL;}

	int GetOmakeClassExistFlag(void);

	virtual BOOL CheckOpeningMode(void) {return m_openingModeFlag;}
	virtual void SetOpeningMode(BOOL md = TRUE) {m_openingModeFlag = md;}

	virtual CNameList* GetCharaNamelsit(void) {return m_charaNameList;}

	virtual void SetBackScriptMode(BOOL flg = TRUE){m_backScriptModeFlag = flg;}
	virtual BOOL CheckBackScriptMode(void);
	virtual void RestartBackScript(void);

	virtual CNameList* GetSptList(void){return m_sptList;}

	virtual BOOL LoadBackScript(LPSTR filename);
	virtual BOOL CalcuBackScript(BOOL loopFlag = TRUE);
	virtual void PrintBackScript(void);
	virtual void PrintBackScriptLayers(int startLayer,int endLayer);

	virtual int CalcuCommonBackButton(CMyMouseStatus* lpMouse);
	virtual void PrintCommonBackButton(BOOL mustPrintFlag, int deltaX = 0,int deltaY = 0,int patNum = -1);
	virtual int CalcuCommonUpDownButton(CMyMouseStatus* lpMouse);
	virtual void PrintCommonUpDownButton(BOOL mustPrintFlag, int deltaX = 0,int deltaY = 0,int patNum = -1);


	virtual void CreateCommonBackButton(void);

//	int CheckNoMidi(void){return m_noMidiFlag;}

	virtual void PlaySystemPiano(int n);

	virtual void PrintBossComing(void);
	virtual void BossModeSoundOff(void);

	virtual void SetAdditionalSystemParam(int addGroup,int d){}
	virtual int GetAdditionalSystemParam(int addGroup){return 0;}

	virtual int ExecGameScript(int pc = -1);




	virtual void TaihiAllEffect(void);
	virtual void FuqueAllEffect(void);


	void AddDebugLibDesc(void);

	virtual int ProcessGameKey(int modeNumber);

	virtual void PlayMusic(int n,int loopCount = 0,int volume = -9999,int fadeInTime = -1, int fadeOutTime = -1);
	virtual void PlayMusic(LPSTR filename,int loopCount = 0,int volume = -9999,int fadeInTime = -1,int fadeOutTime = -1);
	virtual void StopMusic(int fadeOutTime = -1);

	int GetNowMusicNumber(void);

	int GetDefaultFadeInTime(void){return m_defaultFadeInTime;}
	int GetDefaultFadeOutTime(void){return m_defaultFadeOutTime;}

	void FuqueAllEffectYoyaku(void){m_fuqueAllEffectYoyaku = TRUE;}

	virtual void CreateNowExitScreen(void);

	virtual CMusicControl* GetMusicControl(void){return m_musicControl;}
	CSceneVoice* GetSceneVoice(void){return m_sceneVoice;}


	virtual int CalcuOptionButton(void);
	virtual int CalcuSceneButton(void);
	virtual BOOL CalcuSkipFilmButton(void);
//	virtual int CalcuQuickSaveButton(void);
//	virtual int CalcuQuickLoadButton(void);
	virtual BOOL CalcuFreeButton(CSceneOptionButton* button,int rt,int cmd,int* lpRT,int* lpSound);

	virtual void InitOptionButton(void);
	virtual void InitFreeButton(CSceneOptionButton* button,int md);
	virtual void InitSceneButton(void);
	virtual void InitSkipFilmButton(void);
//	virtual void InitQuickSaveButton(void);
//	virtual void InitQuickLoadButton(void);

	virtual void PrintOptionButtonYoyaku(void);
	virtual void PrintSceneButtonYoyaku(void);
	virtual void PrintSkipFilmButtonYoyaku(void);
//	virtual void PrintQuickSaveButtonYoyaku(void);
//	virtual void PrintQuickLoadButtonYoyaku(void);

	virtual void PrintOptionButton(void);
	virtual void PrintSceneButton(void);
	virtual void PrintSkipFilmButton(void);
//	virtual void PrintQuickSaveButton(void);
//	virtual void PrintQuickLoadButton(void);
	virtual void PrintFreeButton(CSceneOptionButton* button,int md);

	void SetDontPlay(int md);

	int GetDontPlayMode(void){return m_dontPlayMode;}

	int CheckListenMusic(int musicNumber);
	int SearchMusicNumber(LPSTR filename);

	void LaunchCountUp(void);
	int GetLaunchCount(void);

	virtual int CheckCodec(void);

	void SetCodecErrorRunMode(int md){m_codecErrorRunMode = md;}
	int GetCodecErrorRunMode(void){return m_codecErrorRunMode;}

	void SetMovieCursor(HCURSOR cursor){m_movieCursor = cursor;}

	void StopScriptSoundAndVoice(void);

	int GetLastSelectHeroinNumber(void){return m_lastSelectHeroinNumber;}
	void SetLastSelectHeroinNumber(int heroin){m_lastSelectHeroinNumber = heroin;}

	LPSTR GetMovieName(int n);
	void ResetLaunch(void);
	BOOL CheckDebugFlag(void){return m_debugOkFlag;}

	CMyDirectSoundBuffer* GetScriptSoundBuffer0(int n);

	void EraseCursor(void);
	void SetCodecError(int err = 1);

	void SetListenBGMParam(int md,int musicNumber);


	void GetGetScreen(void);
	void PutGetScreen(void);

	int GetShakinFrame(int kaeseru = -1);
	int ShakinHensai(int kaeseru = 1);

//	void ShakinHensaiFrame(int frame = 1);

	int GetConfigMask(void){return m_configMask;}
	void SetConfigMask(int mask){m_configMask = mask;}

	void SetSystemMenuSceneMode(BOOL flg = TRUE);

	void RestartLoopSoundAndVoice(void);

	BOOL PlayScriptSe(int ch,int systemSE = 0);
	BOOL PlayScriptVoice(int ch);

	void SetLastSaveOkGameMode(int md);

	virtual int ChangeToSystemMode(int nextMode,int nowMode = 0);

	void SetWindowNumberByConfig(int d);
	void SetWindowNumberByScript(int d);
	void SetWindowNumberByFontSize(int d);
	void SetMouseNumberByConfig(int d);
	void SetMouseNumberByScript(int d);
	void SetCursorNumberByConfig(int d);
	void SetCursorNumberByScript(int d);

	int GetWindowNumberByConfig(void);
	int GetMouseNumberByConfig(void);
	int GetCursorNumberByConfig(void);

	void ClearWindowMouseCursorNumberByScript(void);

	int GetWindowShurui(void);
	int GetMouseShurui(void);
	int GetCursorShurui(void);

	BOOL CheckOnMessageWindowSize(POINT pt);

	void CheckAndWaitMainThread(void);

//	BOOL PauseMainThread(void);
//	BOOL ResumeMainThread(void);

	virtual int WaitGameThread(void);
	virtual BOOL ResumeGameThread(void);
	virtual BOOL SetTmpThreadHandle(HANDLE threadHandle);

	virtual BOOL CheckAndFree(void);
	virtual int GetAutoMessage(void){return m_autoMessage;}
	virtual int GetCannotClick(void){return m_cannotClick;}
	virtual int GetCannotSkip(void){return m_cannotSkip;}
	virtual int GetOptionOff(void){return m_optionOff;}

	virtual void ClearWork(void);
	int GetNowFrameCount(void){return m_nowFrameCount;}

	void SetMiniGameNumber(int n){m_miniGameNumber = n;}
	int GetMiniGameNumber(void){return m_miniGameNumber;}

	void SetOnMiniGameArea(BOOL flg = TRUE){m_onMiniGameArea = flg;}

	BOOL AddMiniGame(int n);
	BOOL AddMiniGame(CMiniGameBase* lpMiniGame);

	int GetSceneButtonMode(void);
	BOOL Set3DMode(BOOL flg = TRUE);

	virtual BOOL CheckMiniGame(int modeNumber);

	virtual BOOL BeginScene(BOOL targetChangeFlag = TRUE);
	virtual void EndScene(void);

	virtual BOOL BeginGet(CPicture* lpPic);
	virtual void EndGet(void);

	void SetLayerOff(int layeroff = 0);
	void SetDontLoadDWQ(int layer,int dontFlag = 1){m_dontLoadDWQ[layer] = dontFlag;}

	void SetGameMouseDontPrintFlag(BOOL flg = TRUE){m_gameMouseDontPrintFlag = flg;}
	void SetMovieEnable(BOOL flg = TRUE);

	void GeneralCreate(void);
	virtual void Create(void){}
	void AfterCreate(void);

//	void SetChangeScreenEvent(HANDLE* lpHandle);

//	virtual void ScreenModeIsChanged(void){}

	virtual void BeforeChangeScreen(void){}
	virtual void AfterChangeScreen(void){}
	virtual void BeforeChangeScreenByConfig(void) {}
	virtual void AfterChangeScreenByConfig(void) {}

	virtual void BeforeByConfig(void);
	virtual void AfterByConfig(void);

	CMyTextInputBox* GetTextInputBox(void){return m_textInputBox;}

	virtual LPSTR GetSystemSei(void);
	virtual LPSTR GetSystemMei(void);
	virtual LPSTR GetGameDefaultSei(void);
	virtual LPSTR GetGameDefaultMei(void);
	virtual void SetSeiMei(LPSTR sei,LPSTR mei);

	void SetupNameDefault(void);

	void ClearFontCache(void);
	void ClearBackLog(void);

	int GetWindowOffMouseButton(void){return m_windowOffMouseButton;}
	int ExpOptionCommand(int cmd);
	virtual int UserSystemMenu(int cmd);

	int GetQuickLoadEnable(void){return m_quickLoadEnable;}
	int GetQuickSaveEnable(void){return m_quickSaveEnable;}

	void SetSaveComment(LPSTR comment = NULL,int n = 0);

	virtual void GetMiniCGData(int* dst, int type = -2,int customSizeX = 132,int customSizeY = 100);

	virtual int GetUseCutin(void);

	int GetMiniGameCheckKosuu(void){return m_miniGameCheckKosuu;}
	int GetMiniGameAreaButtomMode(void){return m_miniGameAreaButtonMode;}
//	BOOL GetSpectrum(int* spectrum,int block = 16,int point = 256);

	void InitMiniGameButton(int md);
	void PrintMiniGameButton(void);

	void SkipToFilmEnd(void);

	int GetSpecialNumberForSave(void);

	CNameList* GetGameSetup(void){return m_setup;}
	void SetSkipMovie(void);
	BOOL CheckSkipMovie(void);

	CCommonResultData* GetCommonResultData(void){return m_commonResultData;}

	BOOL CheckExistQuickLoadData(void);
	BOOL CheckUseQuickLoad(void);

	POINT GetMouseHotPoint(void);

	virtual void OnFilmExpStatus(int para){};

	CSceneList* GetSceneList(void){return m_sceneList;}
	CSceneDataControl* GetSceneDataControl(void){return m_sceneDataControl;}
	CCGDataControl* GetCGDataControl(void){return m_cgDataControl;}
	void SetBackLogOk(int mode,int flg = 1);
	int GetBackLogOk(int mode);
	int GetBackLogMax(void);


	LPSTR GetDefaultSeiMei(int md);
	LPSTR GetGameDefaultSeiMei(int md);

	BOOL CheckExpModeByVar(int mode);

	int SetExpParam(int n,int para,LPVOID lpPara = NULL);
	CCommonSystemModeList* GetSystemModeList(void){return m_systemModeList;}

	void ChangeAutoExtDataSize(int mode,int dataSize);
	void ChangeAutoExtSubDataSize(int n,int dataSize);
	
	virtual BOOL RegistUserFunction(int classNumber,LPSTR functionName,int functionNumber = 0);

	void StartNotice(int n);
	int CheckQuickLoadDelay(void){return m_quickLoadDelay;}
	void SetQuickLoadDelay(BOOL flg = TRUE){m_quickLoadYoyaku = 1;}
	void SetLastSaveSlot(int slot);
	int GetLastSaveSlot(void);

	void ClearYoyaku(void);

	void EndMovie(void);

	BOOL CheckWheelDisable(void);

	int GetMessageFontSizeType(void){return m_messageFontSizeType;}

	void PrintFace(int check,LPSTR name);

	virtual void CheckAndSetMouseAndCursor(int para,int dat);

	void StopReplayVoice(int fadeTime = 0);

	void SetCG(int cgPlayer,int cgParam);
	void SetAchievement(int achievement,int param=100);
	int GetAchievement(int achievement);


	BOOL CheckMessageWindowFlag(void){return m_messageWindowPrintFlag;}
	void SetMessageWindowFlag(BOOL flg = TRUE){m_messageWindowPrintFlag = flg;}
	int GetNextMessageType(void){return m_nextMessageType;}

	void AllOnOmakeFlag(int mask = 0xff);
	BOOL CheckVolumeExist(int n);

	BOOL CheckOnFreeAutoSkipButton(POINT pt);
	void SetAnimeOff(int offMode);
	virtual BOOL AfterChangeSystemParamExpCheck(int n,int md);
	virtual BOOL AfterChangeSystemParamExpRadio(int n,int md);
	virtual void AddBacklogSeparator(void);
	CPicture* GetAnimeBuffer(int n);
	LPSTR GetAnimeTag(void);

	void InitFreeButton(int buttonType);
	CTaihi* GetTaihi(void){return m_taihi;}

	int GetAutoDebugMode(void){return m_autoDebugMode;}
	int GetAutoDebugWait(void){return m_autoDebugWait;}
	void DebugF5Routine(void);
	CAutoSelectControl* GetAutoSelectControl(void){return m_autoSelectControl;}

	POINT GameToView(POINT pt);
	CViewControl* GetViewControl(void){return m_viewControl;}

	COkikaeData* GetOkikae(void){return m_okikaeData;}
	void SetOkikaeMessage(int n,char* mes);
	void SetSystemOkikaeMessage(int n,char* mes);

	BOOL CheckCharaVoice(int flagNumber);
	BOOL CheckTerm(int term);
	BOOL CheckTermLook(int term);
	void SetTermLook(int term,BOOL flag = TRUE);

	void AddDebugLog(LPSTR mes = NULL);
	int m_debugLogFlag;

	int GetVarType(void);
	int GetVarMax(void);

	void SetHintNumber(int n);
	int GetHintNumber(void);

	BOOL CheckUseDirect2D(void);
	bool CheckExistSaveData(void);
	int GetLastSelectSaveLoad(void);
	void SetLastSelectSaveLoad(int n);

	bool CheckExistLastSaveData(void);
	bool ExecSaveData(int n);

	bool CheckPoolVoiceFlag(int ch);
	void SetPoolVoiceFlag(int ch, bool flag);
	void CheckAndPlayPoolVoice(void);
	void PlayPoolVoice(int ch);

	void StopAllScriptVoice(void);
	void ReLoadSystemSound(void);

	int GetUseSystemVoiceCount(void);
	int GetUseSystemVoice(void);
	void SetUseSystemVoice(int n);

	int GetMovieCount(void);
	void SetDirectMovie(int movieNumber);

	void SetGetMovie(int playerNumber, int n);
	bool CheckGetMovie(int playerNumber,int n);

	int GetMessageSpeedTable(int n, bool autoFlag);
	int GetSelectSerialID(void);
	void SetSelectSerialID(int serial, int n, bool flag = true);
	bool CheckSelectSerialID(int serial, int n);

	void PlayButtonVoice(int voice);
	int GetSaveLog(void);
	int GetMessageSerial(void) { return m_messageSerial; }

	void PlayButtonVoiceByFilename(LPSTR filename);
	void SetSkipVoiceOffCheck(bool bSkip = true,bool bSkipChara = true);

	virtual void OnDelayEnterSE(int seNumber);
	virtual void OnDelayExitSE(int seNumber);

	virtual void OnDelayExitVoice(LPSTR filename, int delayCount);

	virtual void CalcuDelayEnterExistSE(void);
	virtual void CalcuDelayEnterExistVoice(void);

	virtual void SetSpecialMouseType(int type);

	//void MakeSaveDataForBackLog(void);

	int GetJumpFlag();
	void CreateJumpBuffer(void);
	void TestJump(int n);

	int GetUseGoreFlag();
	int GetGoreFlag();
	void SetGoreFlag(int goreFlag);

	void SetGoreLayer(void);

	SIZE GetRealWindowSize();

protected:
	virtual void BeforeSaveSystemFile(void){}
	virtual void AfterSaveSystemFile(void){}

	CSuperButtonPicture* m_superButtonPicture;

	CCommonGeneral* m_general[MODE_MAX];
//	int m_omakeClass[MODE_MAX][OMAKEMODE_KOSUU];

	virtual void OOnamiCommand(int d){}

	virtual BOOL RegistUserCommand(int classNumber,LPSTR commandName);

	HANDLE m_changeScreenEvent[4];


//	BOOL CheckCdExist(MCIDEVICEID id);

	int m_modalLevel;
	int m_returnCode[16];
//	HANDLE m_eventHandle[16];
	int m_modalPrintMode[16];
//	unsigned int m_threadID[16];
	HANDLE m_threadHandle[16];
	int m_gameMode[16];


	HWND m_hWnd;
	HINSTANCE m_hInstance;
	int m_windowSizeX,m_windowSizeY;

	int m_bpp;

	int m_floatingLayerFlashFlag;

	CMyFont* m_font;
	CMyMessage* m_message;

	BOOL m_messageHaveVoiceFlag;
	int m_messageVoiceLength;
	int m_loadVoiceLength;

	CCommonBackButton* m_backButton;
	CMyCommonButton* m_newBackButton;
	CCommonFileControl* m_fileControl;


	BOOL m_skipNextCommandFlag;
	BOOL m_skipEffectCommandFlag;
	BOOL m_yoyakuExecFlag;
	BOOL m_skipToFilmEndFlag;
	BOOL m_skipToFilmEndEnable;

	BOOL m_shiftKey;
	BOOL m_ctrlKey;


	BOOL m_downed1;
	BOOL m_downed2;
	BOOL m_downed3;
	int m_wheelDelta;
	BOOL m_wheelMoveFlag;
	int m_wheelMove;

	BOOL m_spaceKey;
	BOOL m_returnKey;

	BOOL m_sceneMode;

	CMyDirectDraw* m_directDraw;
	CMMX* m_mmx;
	CMyDirectShow* m_directShow;

	LPVOID m_myDirect3D;
	CTextureCacheControl* m_textureCacheControl;

	int m_windowX;
	int m_windowY;
	int m_deskTopWindowSizeX;
	int m_deskTopWindowSizeY;
	int m_desktopWindowStartX;
	int m_desktopWindowStartY;
	int m_desktopWindowEndX;
	int m_desktopWindowEndY;

	int m_wheelWaitCount;


	BOOL m_messageSkipFlag;

	CCommonSystemFile* m_systemFile;
	CViewControl* m_viewControl;

	CEffect* m_effect;
	CAllEffect* m_allEffect;
	CSceneList* m_sceneList;
	CSceneDataControl* m_sceneDataControl;
	CCGDataControl* m_cgDataControl;

	int* m_commonBuffer;

	CExecScript* m_controlScript;
	CExecScript* m_execScript;
	CExecScript* m_execSubScript;
	CExecScript* m_execSubSubScript;

	int m_overrapType;
	int m_overrapLength;

	CPicture* m_overrapPic1;
	CPicture* m_overrapPic2;
	int m_saveMode;


//	CMIDIPlayer* m_midi;

	CVarNumber* m_varNumber;

	CNameList* m_systemSeList;
	CNameList* m_bgmList;
	CNameList* m_sptList;
	CNameList* m_varList;
	CNameList* m_seList;
	CNameList* m_charaNameList;
	CNameList* m_faceList;
	CNameList* m_functionList;
	CNameList* m_commandList;
	CNameList* m_sceneVoiceList;
	CNameList* m_movieList;
	CNameList* m_varInitData;

//	BOOL m_cdPlayingFlag;

	int m_sptFileNumber[4];
//	int* m_cgKosuu;
	int m_pastTime2;

	CCommonMessageWindow* m_messageWindow;
//	BOOL m_noMessageWindowFlag;

	BOOL m_messageWindowDontPrintFlag;
	BOOL m_messageWindowPrintFlag;

	int m_messageFontSizeType;


//	CPicture* m_messageWindowPic;

	CSystemPicture* m_systemPicture;
//	CNameList** m_cgList;

//	int m_cgListKosuu;

	CMixerControl* m_mixer;
	CMyDirectSound* m_directSound;

	int m_lastSoundVoiceVolume;

	BOOL m_optionFlag;
	BOOL m_sceneButtonFlag;

	BOOL m_onSceneFlag;
	BOOL m_onOptionFlag;


	CSceneOptionButton* m_sceneButton;
	CSceneOptionButton* m_optionButton;
	CSceneOptionButton* m_skipFilmButton;
	CSceneOptionButton* m_quickSaveButton;
	CSceneOptionButton* m_quickLoadButton;
	CSceneOptionButton* m_quickConfigButton;
	CSceneOptionButton* m_quickBackLogButton;

	CSceneOptionButton* m_freeSaveButton;
	CSceneOptionButton* m_freeLoadButton;
	CSceneOptionButton* m_freeAutoButton;
	CSceneOptionButton* m_freeSkipButton;
	CSceneOptionButton* m_freeWindowOffButton;





	int m_optionOffVar;
	int m_messageKosuu;
	int m_dataFileVersion;
	int m_selectMessageKosuu;
	int m_selectMessageAddKosuu;
	int m_nokori;
	int m_lastMessageID;
	int m_lastSelectID;


	int m_var[2224];
	int m_dayMonthVar;
	int m_yearVar;

	int* m_miniCG;
	BOOL m_demoFlag;
	int m_demoFlagVar;

	int m_miniCGReduce;
	int m_miniCGSizeX;
	int m_miniCGSizeY;

	int m_pastTime;
	int m_totalCount;
	int m_skipCount;
	int m_shakin;
	int m_shakin1;
	int m_shakin2;
	int m_shakin3;

	int m_totalTime;
	int m_nextShakinFumitaoshi;

	int m_jumpFlag;
	BOOL m_requestCreateJumpSaveDataFlag;
	int m_createJumpSaveNumber;

	CMyMouseStatus* m_mouseStatus;
	CMyKeyStatus* m_keyStatus;
	CInputStatus* m_inputStatus;

	BOOL m_debugVarFlag;
//	int m_debugVarStart;
//	int m_debugVarDelta;

	BOOL m_debugOkFlag;
	BOOL m_motionGetFlag;
	BOOL m_memPrintFlag;
	int m_motionGetCount;
	BOOL m_fpsPrintFlag;
	int m_debugVarKosuuMax;

	BOOL m_quitFlag;
	int m_yoyaku;
	int m_eraseYoyakuX[100];
	int m_eraseYoyakuY[100];
	int m_eraseYoyakuSizeX[100];
	int m_eraseYoyakuSizeY[100];

	CPicture* m_commonBG;
	CPicture* m_commonParts;

	int m_rndVar;
	int m_weekVar;
	int m_holidayVar;


	int m_adjustDateFunction;
	int m_setsceneFunction;
	int m_stopF5Function;
	int m_saveSystemFileFunction;
	int m_layerOnOffFunction;
	int m_noticeFunction;
	int m_getresultFunction;
	int m_setresultFunction;
	int m_setachievementFunction;
	int m_compareStringFunction;
	int m_compareSystemStringFunction;

	int m_compareResultVarNumber;

	int m_answerStringNumber;
	char* m_answerStringData;

	int m_useSaijitsu;
	CSaijitsuList* m_saijitsuList;

//	static int m_saijitsu2000[];

//	int m_scenePlayerOffsetStart[100];
//	int m_sceneKosuuPerPlayer[100];
//	int m_sceneOffset[1000];

//	int m_movingLayerKosuuMax;
//	CMovingLayer* m_movingLayer[20];

//	BOOL m_calendarFlag;
	BOOL m_cursorFlag;

	int m_cursorPrintX;
	int m_cursorPrintY;
	int m_cursorPat;

	int m_userCommand;
	int m_userFunction;

	int m_userParaKosuu;
	int m_userParam[256];

	CTaihi* m_taihi;
	CCommonUpDownButtonGroup* m_upDown;

	CGameUtil* m_gameUtil;

//	CCommonWave* m_wave;
	CWaveData** m_systemWaveArray;

	BOOL m_bossMode;
	int m_bossComingType;
	int m_bossComingColorR;
	int m_bossComingColorG;
	int m_bossComingColorB;
	CPicture* m_bossComingPic;

	int m_systemWaveLoadKosuu;
//	int m_extDataBlockKosuu;
//	int m_sceneSptNumber;

	int m_gameVersion;

	BOOL m_disableLoadSaveShortCutKeyFlag;

	int m_bgmKosuu;

	CPrintDebugParam* m_printDebugParam;
	CNameList* m_setup;
	CNameList* m_setup2;
	CNameList* m_setup3;
	CNameList* m_setupConfig;

	LPSTR m_companyName;
	LPSTR m_productName;

	void YoyakuExecRoutine(void);

	CMessageCursor* m_messageCursor;
	CGameMouse* m_gameMouse;

	BOOL m_voiceSpeakFlag;
	int m_voiceSpeakCount;

	LPSTR m_saveHeaderName;
	static char m_defaultSaveHeader[];

	static char m_defaultStartMessage[];

	int m_extSaveDataKosuu;
	int* m_extSaveDataSizeTable;


	LPSTR m_filenameBackButton;	//@@@
	int m_backSizeX;
	int m_backSizeY;

	int m_backButtonCreateFlag;
	int m_superBackButtonFlag;


	static char m_defaultSpecialNumberForSaveName[];

//	static char m_defaultBackButtonFileName[];
	static char m_defaultOoptionOffVarName[];

	int m_directXInitVolumeFlag;
	int m_directXInitVolume;

	int m_frameTime;
	int m_defaultFrameTime;

	int m_f9KeyExitOffFlag;
	int m_escKeyExitOffFlag;

//	int m_enableMidiButtonFlag;
//	int m_enableCDButtonFlag;

	int m_specialNumberForSaveSetFlag;
	int m_specialNumberForSaveVarNumber;

	int m_noScriptFlag;
	int m_scriptRunMode;

//	int m_omakeClassExistFlag;

	CDataFileSetup* m_dataFileSetup;

	void ChangeMode(void);

	CMainControl* m_mainControl;

//	LPVOID m_threadAddr;
	int SearchOmakeMode(int parentModeNumber, int omakeModeNumber);

	void PrintParentClass(void);

	BOOL m_openingModeFlag;
	BOOL m_backScriptModeFlag;

	CBackExecClass* m_backExecClass;

	int m_backScriptSetCGOkFlag;

	int m_fukaPrintFlag;
	int m_noWaitVSync;

	CSuperButtonSetup* m_superBackButtonSetup;
	CSuperButtonSetup* m_superUpButtonSetup;
	CSuperButtonSetup* m_superDownButtonSetup;

	int m_maxSkipFrame;
	int m_maxSkipFrameBackScript;
	int m_skipAdjustFrame;


	CFukaPrint* m_fukaPrint;
	CFpsPrint* m_fpsPrint;

	virtual void SetupBossComing(void);
	virtual void SetupFukaPrint(void);
	virtual void SetupFpsPrint(void);

	virtual void SetupAndCreateCommonBackButton(void);
	virtual void CreateBackButton(void);

	CMyGraphics* m_myGraphics;

	CExecScript* GetScript(void);

	int m_debugMessageKosuu;
	char m_debugMessage[20][256];

	void AddDebugMessage(LPSTR mes);

	BOOL m_skipF4Mode;
	BOOL m_skipF5Mode;

	BOOL m_createModeDisableFlag[100];

//	BOOL m_defaultUserCommandFlag[50];

	void CheckCreateBadFlag(void);
	void CheckDefaultUserCommandFlag(void);


//	static char m_userCommandName[][64];
//	static int m_userCommandClass[];

	int m_defaultUserCommandNumber[50];
	int m_defaultUserCommandClass[50];
	int m_defaultUserCommandKosuu;

	int m_autoFunctionNumber[50];
	int m_autoFunctionClass[50];
	int m_autoFunctionParam[50];
	int m_autoFunctionKosuu;



	char m_taihiFileName[PICTURE_KOSUU_MAX][256];

	int m_taihiPC;
	int m_taihiPC2;
	int m_taihiPC3;
	int m_taihiPC4;

	int m_taihiStackPointer;
	int m_taihiStackPointer2;
	int m_taihiStackPointer3;
	int m_taihiStackPointer4;

//	int m_taihiStack[256];
//	int m_taihiStack2[256];
//	int m_taihiStack3[256];
//	int m_taihiStack4[256];

//	int m_taihiID[256];
//	int m_taihiID2[256];
//	int m_taihiID3[256];
//	int m_taihiID4[256];
	int* m_taihiStack;
	int* m_taihiStack2;
	int* m_taihiStack3;
	int* m_taihiStack4;

	int* m_taihiID;
	int* m_taihiID2;
	int* m_taihiID3;
	int* m_taihiID4;


	int m_taihiScriptRunMode;
	int m_taihiSptFileNumber[4];


//	int m_noCGModeFlag;
//	int m_noSceneModeFlag;
//	int m_noListenBGMModeFlag;

	void DisableMode(int modeNumber);

	void StartInitialMessage(void);
	LPSTR m_startMessage;
	int m_printStartMessageFlag;

	int m_nextMessageWindowPrintMode;

	void ChangeMessageWindowModeByNext(void);
	BOOL m_taihiMessageWindowPrintFlag;


	int m_shortCutSystemMenuSound;
	int m_shortCutLoadSound;
	int m_shortCutSaveSound;
	int m_shortCutConfigSound;

	virtual BOOL CheckDebugOk(void);
	void SetDebugFlag(BOOL flg = TRUE);

	int m_systemYearVar;
	int m_systemMonthVar;
	int m_systemDayVar;
	int m_systemHourVar;
	int m_systemMinuteVar;
	int m_systemSecondVar;

	int m_systemWeekVar;
	int m_systemMilliSecondVar;

	int m_modeVar;

	int m_direct3DVar;
	int m_pixelShaderVar;
	int m_vertexShaderVar;

	int m_mouseXVar;
	int m_mouseYVar;
	int m_trig1Var;
	int m_trig2Var;
	int m_trig3Var;
	int m_click1Var;
	int m_click2Var;
	int m_click3Var;
	int m_wheelVar;


	int m_listenbgmnumberVar;
	int m_listenbgmmodeVar;

	int m_cgPercentVar;
	int m_scenePercentVar;


	int GetNowSystemTime(int varNumber);

//	CWaveMusic* m_waveMusic[2];


//	int m_useWaveMusicNumber;

	int m_defaultFadeInTime;
	int m_defaultFadeOutTime;

	int m_musicNumber;
	int m_lastMusicNumber;
	int m_musicKaisuu;

	int m_soundChannel;
	int m_samplingRate;
	int m_samplingBit;
	int m_3dSoundFlag;

	LPSTR m_preReceiveFileName;

	CMyDirectSoundBuffer* m_systemSound[2];
	CMyDirectSoundBuffer* m_buttonVoice[2];
	//	CMyDirectSoundBuffer* m_scriptVoice[4];
//	CMyDirectSoundBuffer* m_scriptSound[8];

	BOOL m_fuqueAllEffectYoyaku;

	CMusicControl* m_musicControl;

	int m_useSystemSoundNumber;
	int m_useButtonVoiceNumber;

	CSceneVoice* m_sceneVoice;

	BOOL m_optionButtonPrintYoyaku;
	BOOL m_sceneButtonPrintYoyaku;
	BOOL m_skipFilmButtonPrintYoyaku;
//	BOOL m_quickSaveButtonPrintYoyaku;
//	BOOL m_quickLoadButtonPrintYoyaku;

	int m_gameMouseCreateFlag;
	int m_messageCursorCreateFlag;
	int m_optionButtonCreateFlag;
	int m_sceneButtonCreateFlag;
	int m_skipFilmButtonCreateFlag;
//	int m_quickSaveButtonCreateFlag;
//	int m_quickLoadButtonCreateFlag;
//	int m_quickConfigButtonCreateFlag;
//	int m_quickBackLogButtonCreateFlag;

	void CheckAndSetQuickLoadButtonEnable(void);

	int m_dontPlayMode;

	int m_userFontKosuu;

	int m_allMusicSetFlag;
	BOOL m_launchFlag;

//	BOOL m_loopingFlag[8];

	int m_mustSetVoiceFlag;
	int m_mustSetMusicFlag;
	int m_mustSetCGFlag;
	int m_mustSetFilmFlag;

	int m_codecError;
	int m_codecErrorRunMode;

	HCURSOR m_movieCursor;
//	int m_errorLogFlag;

	int m_startWidth;
	int m_startHeight;
	int m_startFrequency;

//	void TaihiWindow(void);
//	void FuqueWindow(void);

//	int m_taihiX;
//	int m_taihiY;

	int m_lastSelectHeroinNumber;

//	int m_selectPlaceCommandNumber;
//	int m_selectHeroinCommandNumber;
//	int m_printCalendarCommandNumber;
//	int m_printMovieCommandNumber;

	int m_movieVolumeNotUse;
	int m_soundVoiceVolumeNotUse;

//	int m_loopSoundWork[8*16];
	char m_lastFilmName[64];
	char m_lastStoryName[64];

//	int m_loopVoiceWork[8*16];
	char m_loopVoiceFileName[8*64];

	void PrintScriptFileName(void);
	int m_expButtonKosuu;
	int m_expButtonVarNumber[16];

	int m_expCheckButtonKosuu;
	int m_expCheckButtonVarNumber[16];

	CShakin* m_shakinControl;

	void SystemFunctionSetAchievement(int para1,LPVOID para2);
	void SystemFunctionSetCG(int para1,LPVOID para2);
	void SystemFunctionSetVoiceFlag(int para1,LPVOID para2);
	void SystemFunctionSetTerm(int para1,LPVOID para2);
	void SystemFunctionMessageEffect(int para1,LPVOID para2);
	void SystemFunctionMessageEffectTime(int para1,LPVOID para2);

	void SystemFunctionSetFilm(int para1,LPVOID para2);
	void SystemFunctionPrepareOverrap(int para1,LPVOID para2);

	void SystemFunctionSound(int para1,LPVOID para2);
	void SystemFunctionVoice(int para1,LPVOID para2,int defVoiceFlag = 0);
	void SystemFunctionMusic(int para1,LPVOID para2);

	void SystemFunctionVolumeOnlySe(int para1,LPVOID para2);
	void SystemFunctionVolumeOnlyVoice(int para1,LPVOID para2);
	void SystemFunctionNextFadeSe(int para1,LPVOID para2);
	void SystemFunctionNextFadeVoice(int para1,LPVOID para2);

	void SystemFunctionMusicVolumeOnly(int para1,LPVOID para2);


	void SystemFunctionStartKoma(int para1,LPVOID para2);
	void SystemFunctionStartMessage(int para1,LPVOID para2);

	void SystemFunctionChangeMessageFontSizeType(int para1,LPVOID para2);
	void SystemFunctionRenamelayer(int para1,LPVOID para2);

	void SystemFunctionFilmName(int para1,LPVOID para2);
	void SystemFunctionStoryName(int para1,LPVOID para2);

	void SystemFunctionLoadDWQ(int para1,LPVOID para2);
	void SystemFunctionPreLoadDWQ(int para1,LPVOID para2);
	void SystemFunctionSetEffectRect(int para1,LPVOID para2);

	void SystemFunctionClearAllEffect(int para1,LPVOID para2);
	void SystemFunctionClearEffectLayer(int para1,LPVOID para2);

	void SystemCommandPrint(int para1,LPVOID para2,int para3 = 0);
	void SystemCommandLPrint(int para1,LPVOID para2,int para3 = 0);
	void SystemCommandAppend(int para1,LPVOID para2,int para3 = 0);
	void SystemCommandDraw(int para1,LPVOID para2);
	void SystemCommandSelect(int para1,LPVOID para2);

//	void SystemFunctionNoMessageWindow(int para1,LPVOID para2);
//	void SystemFunctionSetDemoFlag(int para1,LPVOID para2);
//	void SystemFunctionDebug(int para1,LPVOID para2);
	void SystemFunctionSetEffect(int para1,LPVOID para2);

	void SystemFunctionScript(int cmd,int para1,LPVOID para2);
	void SystemCommandOverrap(int para1,LPVOID para2);
	void SystemFunctionFrameControl(int para1,LPVOID para2);
	void SystemFunctionSetDefaultFrame(int para1,LPVOID para2);

//	void SystemFunctionFilmTypeTime(int para1,LPVOID para2);
//	void SystemFunctionConfigMask(int para1,LPVOID para2);

//	void SystemFunctionSetWindowNumber(int para1,LPVOID para2);
//	void SystemFunctionSetMouseNumber(int para1,LPVOID para2);
//	void SystemFunctionSetCursorNumber(int para1,LPVOID para2);

//	void SystemFunctionSetAutoMessage(int para1,LPVOID para2);
//	void SystemFunctionSetCannotClick(int para1,LPVOID para2);
//	void SystemFunctionSetCannotSkip(int para1,LPVOID para2);
//	void SystemFunctionSetOptionOff(int para1,LPVOID para2);

	void SystemFunctionCutin(int para1,LPVOID para2);
	void SystemFunctionMessageExpStatus(int para1,LPVOID para2);
	void SystemFunctionFilmEndEnable(int para1,LPVOID para2);
	void SystemFunctionFilmExpStatus(int para1,LPVOID para2);
	void SystemFunctionRenameLayer(int para1,LPVOID para2);

	void SystemFunctionSetCGByVar(int para1,LPVOID para2);
	void SystemFunctionSetVar(int para1,LPVOID para2);
	void SystemFunctionVarControlLayer(int para1,LPVOID para2);
	void SystemFunctionFace(int para1,LPVOID para2);
	void SystemFunctionMustFace(int para1,LPVOID para2);

	int AdjustDate(int daymonth);

	void CreateJumpSaveData(void);

	static int m_daysOfMonth[13];

	int m_configMask;

	int m_cutinFlag;

	int m_lastSaveOkMode;

	int m_scriptWindowNumber;
	int m_scriptCursorNumber;
	int m_scriptMouseNumber;

	int m_autoMessage;
	int m_cannotClick;
	int m_cannotSkip;
	int m_optionOff;

	int m_renameLayer;

	int m_modalCannotCloseFlag;

	HANDLE m_tmpThreadHandle;

	HANDLE m_threadControlHandle[4];

	int m_miniGameNumber;
	BOOL m_onMiniGameArea;


	int m_sceneButtonMode;


	BOOL m_3dMode;
	void SetMessageReadSkipMode(int mes,int sptNum = -1);
	
	int m_mustMessageReadSkip;

	CWaveData* m_waveData;

	int m_f4Ok;
	int m_f5Ok;

	BOOL m_gameMouseDontPrintFlag;

	BOOL m_movieEnableFlag;

	int m_layerOff;
	int m_dontLoadDWQ[PICTURE_KOSUU_MAX];
	BOOL m_screenModeChangedFlag;

	void TaihiForScreenChange0(void);
	void FuqueByScreenChange0(void);

	int m_startupWindowMode;
	CMyTextInputBox* m_textInputBox;

	int m_expSystemMenuStart;
	int m_expSystemMenuKosuu;
	int* m_expSystemMenuMode;
	int* m_expSystemMenuCommand;
	int* m_expSystemMenuShortCut;
	int* m_expSystemMenuSound;

	int m_optionStartMouseButton;

	int m_windowOffMouseButton;

	int m_quickSaveEnable;
	int m_quickLoadEnable;
	int m_quickSavePrint;
	int m_quickLoadPrint;

	int m_noticeFlag;
	CNotice* m_notice;

	int m_resultFlag;
//	int m_getResultFlag;
	CCommonResultData* m_commonResultData;

	int m_loadNoticeNumber;
	int m_saveNoticeNumber;

	int m_quickSaveKey;
	int m_quickLoadKey;

	int m_saveCommentKosuuMax;
	int m_saveCommentLength;

	char** m_saveComment;

	int m_quickSaveSound;
	int m_quickLoadSound;
	int m_quickLoadErrorSound;


	int m_loadVoiceErrorPrintFlag;
	int m_loadSeErrorPrintFlag;

	int m_useCutinFlag;

	int m_miniGameCheckKosuu;
	int m_miniGameAreaButtonMode;

	int m_quickSaveCommentFlag;

	int m_imeAutoOpenFlag;
	int m_imeAutoCloseFlag;

	int m_varInitFlag;
	int m_getResultVarNumber;


	int m_hintNumber;


	int m_autoExtDataLoadKosuu;
	int* m_autoExtDataLoadMode;

	int m_autoExtSubDataLoadKosuu;
	int* m_autoExtDataLoadSub;
	CAutoSaveSubData** m_autoSaveSubDataClass;

	COmakeClassSupport* m_omakeClassSupport;

	int m_autoResultNotice;
	int* m_backLogOkTable;

	void SetMessageWindowPercent(void);

	static char m_errorName[];
	int* m_expModeCheckVarNumber;

	int m_noVoiceIsDefaultWait;

	CCommonSystemModeList* m_systemModeList;
	CCommonUserCommandList* m_commonUserCommandList;


	BOOL CheckQuickButtonOkMode(int nowMode,int checkMode);
	int CheckFreeButtonOkMode(int nowMode,int checkMode);

	int* m_layerOffVar;


	int m_lastLoadLayer;
	int m_offLayerDontSetCG;

	void ClickShiftKey(void);

	int m_shiftSkipMessageOnly;

	int m_autoMessageCheckKillShift;
	int m_cannotSkipCheckKillShift;

	int m_quickLoadGetScreen;

	int m_quickLoadYoyaku;
	int m_quickLoadDelay;

	int m_adjustFullScreenLost;
	int m_adjustFullWait;

	int m_backLogDisableCount;
	int m_backLogDisableTime;
	int m_backLogDisableCheckTime;
	int m_backLogDisableCheckFlag;
	int m_backLogDisableOldTime;

	void LogMessage(int msg,WPARAM wParam,LPARAM lParam);
	void LogMessage(LPSTR mes);


	CScriptSoundControl* m_scriptSoundControl;
	CScriptVoiceControl* m_scriptVoiceControl;

	int m_renameLayerVarNumber;
	char* m_renameTag;
	int m_renameTagKosuu;


	short m_varControlLayer[LAYER_KOSUU_MAX];
	short m_taihiVarControlLayer[LAYER_KOSUU_MAX];

	int m_varControlLoadDWQErrorPrint;

	int m_facePrintFlag;

	CFaceControl* m_faceControl;
	COkikaeData* m_okikaeData;

	void SetAutoSaveSubClass(int type,CAutoSaveSubData* subClass);

	CAutoSaveDataList* m_autoSaveDataList;

	int m_nextFadeSe;
	int m_nextFadeVoice;

	int m_expModeButtonIsMouse;
	int m_expModeButtonIsMessageCursor;

	int m_charaVoiceVolumeDelta;
	int m_enableButtonVoiceCharaVolume;

	int m_koukaonOnseiDontStopFlag;
	int m_skipToScriptVoiceStopFlag;

	int m_notUseDirectDraw;

	int m_nextMessageType;

	int m_layerKosuuMax;
	int m_pictureKosuuMax;

	int m_totalVolumeUseFlag;

	BOOL CheckTotalVolumeOff(void);

	int m_useHsavemask;
	CNameList* m_hSaveList;
	CPicture* m_hSaveMaskPic;

	int m_clearAutoAfterLoad;

	int m_autoDebugMode;
	int m_autoDebugWait;

	CAutoSelectControl* m_autoSelectControl;
	BOOL m_displaySettingChanged;

	int m_resetNameByStartTitle;

	int m_specialVoiceNameKosuu;
	char* m_specialVoiceName;
	int m_nameIsSpecialVoiceFlag;

	BOOL CheckNameIsSpecialVoice(void);

	int m_systemSoundMulti;
	BOOL m_skipMovieFlag;
	BOOL m_skipMovieFlag0;

	BOOL m_newSkipMovieFlag;

	int m_printPlayerStatusFlag;
	CPrintPlayerStatus* m_printPlayerStatus;

	int m_useDirect2D;
	int m_useXAudio2;

	int m_buttonVoiceNumber;

//private:
	//dummy
	int m_nowFrameCount;

	int m_notPlaySameMusic;

	BOOL m_gameCreateFlagGeneral;
	int m_overrunBuffer;

	bool m_poolVoiceFlag[4];
	int m_noWaitSameChara[4];

	int m_checkSameCharaMustChannel1;

	int m_useSystemVoice;
	CNameList** m_systemVoiceList;
	CNameList** m_buttonVoiceList;

	int m_selectSerialID;

	int m_saveLog;

	int m_messageSerial;

	char m_buttonPlayingFilename[2][256];
	int m_voiceExistCount[4];
	int m_playLoadVoiceFlag;

	bool m_skipVoiceOffCheck;
	bool m_skipVoiceOffCharaCheck;

	int m_delayEnterSECount;
	int m_delayExitSECount;
	int m_delayEnterSENumber;
	int m_delayExitSENumber;
	int m_delayEnterSEWait;
	int m_delayExitSEWait;


	LPSTR m_delayExitVoiceFilename;
	int m_delayExitVoiceCount;

	int m_notUseYearVar;

	int m_useGoreFlag;
	int m_goreFlag;
	int m_goreVarNumber;
	LPSTR m_goreVarNumberName;
	int m_goreLayerCount;
	int m_nonGoreLayerCount;
	int* m_goreEffectLayer;
	int* m_nonGoreEffectLayer;

};

#endif

/*_*/

