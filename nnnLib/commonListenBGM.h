//
// ListenBGM.h
//

#if !defined __NNNLIB_COMMONLISTENBGM__
#define __NNNLIB_COMMONLISTENBGM__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CMySlider;
class CMyMessage;
//class CBackButton;
//class CUpDownButtonGroup;
//class CMIDIPlayer;
//class CMyOldRadioButton;
class CSuuji;

class CCommonCheckButton;

class CFFT;

class CPrintSpectrum;

class CMusicControl;
class CAnimeControl;

//#define MUSIC_KOSUU_MAX 30

class CCommonListenBGM : public CCommonGeneral
{
public:
	CCommonListenBGM(CGameCallBack* lpGame);
	virtual ~CCommonListenBGM();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	static char m_defaultBGFileName[];

	static char m_defaultButtonFileName[];
	static char m_defaultVolumeFileName[];
	static char m_defaultNumberFileName[];
	static char m_defaultCursorFileName[];

	static char m_defaultUpFileName[];
	static char m_defaultDownFileName[];

	static char m_defaultMusicTitleGraphicsFilename[];


	//static char m_defaultBGMListFileName[];

//	static int m_musicOrgLength[MUSIC_KOSUU_MAX][2];

	static int m_defaultPrintX[];
	static int m_defaultCheckSizeX[];

	static char m_buttonName[][8];

	void CreateStartScreen(void);

	static char m_defaultCannotMusicName[];
	static char m_defaultCannotMusicName1Byte[];

protected:
	CCommonCheckButton* m_button[5];

//	LPSTR m_filenameButton;

	void PlayButton(void);
	void FWButton(void);
	void BKButton(void);
	void PauseButton(void);
	void StopButton(void);

	void ChangePage(int deltaPage);

	void PrintMusicName(int n);
	void PrintCursor(int y);

	int GetOnMouse(int mouseX,int mouseY);


	CSuuji* m_suuji;
	CPicture* m_cursorPic;
	CMyMessage* m_message;
	CMySlider* m_volumeSlider;

//	CNameList* m_bgmList;
	int m_bgmKosuu;

	int m_scrollY;

	int m_musicPlayMode;
	int m_timeCount;
	int m_nowTime;
//	int m_musicPauseTenmetsuCount;

	int m_playingNumber;

//	int m_barPicCount;

//	BOOL m_lengthGetFlag[MUSIC_KOSUU_MAX];
//	int m_musicLength[MUSIC_KOSUU_MAX];
//	int m_musicNameLength[MUSIC_KOSUU_MAX];

	BOOL* m_lengthGetFlag;
	int* m_musicLength;
	int* m_musicNameLength;
	int* m_musicNameLength2;


	int m_volume;

	int m_maeVolume;
	int m_nowVolume;

	int m_backVolume;

	int m_page;
	int m_pageMax;


//	int m_volumeCursorPrintX;
//	int m_volumeCursorPrintY;
	
//	int m_volumeGazePrintX;
//	int m_volumeGazePrintY;
//	int m_volumeGazeSizeX;
//	int m_volumeGazeSizeY;

	int m_trackNumberPrintX;
	int m_trackNumberPrintY;

	int m_minutePrintX;
	int m_minutePrintY;

	int m_secondPrintX;
	int m_secondPrintY;

	int m_musicNamePrintX;
	int m_musicNamePrintY;
//	int m_musicNameSizeX;
//	int m_musicNameSizeY;
//	int m_musicNameNextY;

	int m_cursorPrintX;
	int m_cursorPrintY;
	int m_cursorNextX;
	int m_cursorNextY;
	int m_cursorSizeX;
	int m_cursorSizeY;

	int m_fontSizeX;
	int m_fontSizeY;

	int m_fontNextX;
	int m_fontNextY;

	int m_messageFontSize;

	CPicture* m_eyePic;


	void StopBGM(void);
	int GetPlayTime(void);
	BOOL CheckPlaying(void);
	int GetMusicLength(int n);
	void PlayBGM(int n, int lp);

	void MusicResume(void);
	void MusicPause(void);

//	CNameList* m_bgmLengthList;
	CNameList* m_bgmList;


	int m_musicPrintKosuu;

	int m_musicNameColorR;
	int m_musicNameColorG;
	int m_musicNameColorB;

	int m_cannotMusicNameColorR;
	int m_cannotMusicNameColorG;
	int m_cannotMusicNameColorB;

	int m_trackAndTimePrintFlag;
//	int m_oldSelectCursorType;
//	int m_oldCursorPicType;

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	int m_musicFadeInTime;
	int m_musicFadeOutTime;
	int m_bgmLoopFlag;
	
	void CalcuCursorAnime(void);
	void GetCursorAnimePic(void);

	int m_cursorPattern1;
	int m_cursorPattern2;
	int m_cursorPercent;
	int m_cursorAnimeCount;

	int m_cursorAnimeType;
	int m_cursorAnimeSpeed;
	int m_cursorAnimePattern;

	int m_cursorAnimeFlag;

	CMusicControl* m_musicControl;

	int m_volumeMin;
	int m_volumeMax;

	int* m_listenedFlag;
	LPSTR* m_musicName2;

	LPSTR m_cannotMusicName;
	int m_checkListen;
	int m_useCannotByList;

	int* m_systemMusicNumber;
	int* m_checkVar;

	void ChangeMusicMode(int md);

	int m_playRestartScriptFlag;
	int m_stopRestartScriptFlag;
	int m_pauseRestartScriptFlag;

	int m_lastMusicNumber;
	int m_musicNameMax;

	int m_spectrumPrintFlag;
	virtual void PrintSpectrum(void);

	CFFT* m_fft;
	int* m_logNTable;
	int m_spectrumPrintKosuu;
	int m_spectrumCalcuPoint;

	float* m_ar;
	float* m_ai;
	float* m_windowFunction;
	int* m_spectrumData;

	CPrintSpectrum* m_printSpectrum;

	int m_useMusicTitleGraphics;
	CPicture* m_musicTitlePic;
//	int m_musicTitleAnimePattern;
//	int m_musicTitleAnimeSpeed;
//	int m_musicTitleAnimeType;
	int m_musicTitleSizeX;
	int m_musicTitleSizeY;
	int m_musicTitlePrintX;
	int m_musicTitlePrintY;
	int m_musicTitleCount;
	CAnimeControl* m_musicTitleAnimeControl;

	int m_cursorIsUpper;


	int m_musicNameCenterFlag;
	LPSTR m_replaceChara;


	int m_menuStartCount;
	int m_menuStartWaitTime;
	int m_menuStartEffectTime;
	int m_menuStartEffectType;

	int m_appearCount;
	int m_appearCountMax;

	int GetStartWaitMode(void);
	void EndStartWaitMode(void);

};

#endif
/*_*/

