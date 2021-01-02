//
// Config.h
//

#if !defined __NNNLIB_COMMONCONFIG__
#define __NNNLIB_COMMONCONFIG__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

//class CMyCommonButton;
class CMySlider;
//class CBackButton;

class CCommonCheckButton;
class CCommonRadioButtonGroup;

class CMyMessage;


class CCommonConfig : public CCommonGeneral
{
public:
	CCommonConfig(CGameCallBack* lpGame);
	virtual ~CCommonConfig();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void FinalExitRoutine(void) override;

	int* m_checkPrintZahyo;
	int* m_optPrintZahyo;


	int GetVoiceOffButtonNumberByTable(int charaNumber);
	int** m_ppVoiceCutButtonTable;

	static char m_volumeName[][16];
	static char m_modeButtonName[][16];
	static char m_checkButtonName[][32];

	static char m_defaultPageNumberVarName[];

	static char m_defaultSampleText[];

	static int m_defaultVolumeDevideTable[];
	static int m_defaultBunkatsuTable[];
	static int m_defaultIsVoiceTable[];


	static int m_n2VolumeSystemParamTable[];
	static int m_n2VolumeSwitchSystemParamTable[];


	void ReloadScreenButton(void);
	BOOL CheckVolumeExist(int n);

protected:
	BOOL m_disableCDButtonFlag;
	BOOL m_disableMidiButtonFlag;

	int m_radioButtonCustomFlag;
	int m_voiceCutButtonFlag;
	int m_voiceCutNinzu;

	int m_volumeSizeX;
	int m_volumeSizeY;

	int m_voiceCutButtonCheckAppear;

//	int m_musicVolumePrintX;
//	int m_musicVolumePrintY;
///	int m_seVolumePrintX;
//	int m_seVolumePrintY;
//	int m_voiceVolumePrintX;
//	int m_voiceVolumePrintY;
//	int m_messageSpeedPrintX;
//	int m_messageSpeedPrintY;

	CMySlider** m_ppSlider;
	CMySlider** m_ppCharaVoiceSlider;
//	CMySlider* m_seSlider;
//	CMySlider* m_voiceSlider;
//	CMySlider* m_messageSlider;

//	int m_radioButtonKosuu;
//	int* m_radioButtonZahyoX;
//	int* m_radioButtonZahyoY;
//	int m_radioButtonSizeX;
//	int m_radioButtonSizeY;

	int m_radioButtonPrintX;
	int m_radioButtonPrintY;
	int m_radioButtonNextX;
	int m_radioButtonNextY;


//	int* m_voiceCheckBoxZahyoX;
//	int* m_voiceCheckBoxZahyoY;
//	int m_voiceCheckBoxSizeX;
//	int m_voiceCheckBoxSizeY;

//	int m_voiceCheckBoxStartX;
//	int m_voiceCheckBoxStartY;
//	int m_voiceCheckBoxNextX;
//	int m_voiceCheckBoxNextY;
//	int m_voiceCheckBoxKosuuX;
//	int m_voiceCheckBoxKosuuY;
//	int m_voiceCheckBoxYokoFlag;
//	int m_voiceCheckBoxCustomFlag;


	static char m_defaultBGFileName[];
	static char m_defaultBarFileName[];
//	static char m_defaultCheckBoxFileName[];
//	static char m_defaultRadioButtonFileName[];

//	static char m_defaultBadButtonFileName[];

	LPSTR* m_bgFileName;

//	CPicture* m_eyePic;

//	CPicture* m_dmyPic;
//	CMessageWindow* m_dmyWindow;
//	CNameWindow* m_dmyName;
//	CMyBlockButtonMenu* m_menu;
	
//	CPicture* m_radioButtonPic;
//	CPicture* m_checkBoxPic;

	//int GetOnRadioCheckButton(int mouseX, int mouseY);

//	virtual void PrintRadioButtonSub(int n);
//	virtual void PrintCheckButtonSub(int n);

//	CPicture* m_barPic;
//	CPicture* m_backPic;

//	void PrintBarSub(int n, int d, BOOL allPrintFlag);
//	void PrintButtonSub(int n);//, int d,BOOL allPrintFlag);

//	int GetOnRadioButton(int mouseX, int mouseY);
//	int GetOnBar(int mouseX, int mouseY);
//	BOOL CheckOnBack(int mouseX, int mouseY);

//	int m_optPrintX[4][2];
//	int m_optPrintY[4][2];
//	int m_checkPrintX[9];
//	int m_checkPrintY[9];
//	int m_optSizeX;
//	int m_optSizeY;

//	int m_barPrintX[4];
//	int m_barPrintY[4];

//	int m_barSizeX;
//	int m_barSizeY;

//	int m_barMax[4];

//	int m_backPrintX;
//	int m_backPrintY;
//	int m_backSizeX;
//	int m_backSizeY;


	BOOL m_captureFlag;
//	BOOL m_optChangeFlag;
//	BOOL m_barChangeFlag;
//	int m_backMode;

	int m_captureBarNumber;

	BOOL m_changingNumber;
	int m_changingCount;

//	BOOL m_onBackFlag;
//	BOOL m_backChangeFlag;

//	CMyCommonButton* m_back;
//	CBackButton* m_back;

	int m_mode;
	int m_count;

	int m_voiceOffButtonByTableFlag;

//	int m_badButtonPrintFlag;
//	CPicture* m_badButtonPic;

	virtual void BeforeInit(void);
//	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	int m_extSeFlag;
	int m_seListKosuu;
	CNameList* m_seList;

	int m_soundSe;
	int m_voiceSe[11];
	int m_messageSe[5];
	int m_autoSe[5];
	int m_movieSe;
	int m_soundVoiceSe;
	int* m_windowPercentSe;
	int m_windowPercentSeBunkatsu;

	int* m_seTable;
	int* m_volumeDevideTable;
	int* m_bunkatsuTable;
	int* m_isVoiceTable;


//	int m_windowSe[2];
//	int m_readSe[2];
//	int m_autoSe[2];
//	int m_midiCddaSe[2];

//	int* m_voiceOnSe;
//	int* m_voiceOffSe;


	void PlayExtSe(int md,int n = 0,BOOL voiceFlag = FALSE);
	void PlayExtSe2(int md,int vol);

//	int m_addRadioButtonGroupKosuu;
//	int* m_addRadioButtonKosuu;
//	int m_addRadioButtonTotalKosuu;

//	int GetAddRadioButtonGroupNumber(int n);
//	int GetAddRadioButtonNumber(int n);

//	int GetOnAddRadioButton(int mouseX,int mouseY);

//	POINT* m_addRadioButtonZahyo;

//	void PrintAddRadioButtonSub(int group,int nm,int n);


	CCommonCheckButton** m_ppVoiceButton;
	CCommonCheckButton** m_ppVolumeButton;

	CCommonCheckButton** m_ppExpCheckButton;
	CCommonRadioButtonGroup** m_ppModeButton;
	CCommonCheckButton** m_ppCheckButton;
	CCommonButton** m_ppClickButton;

	CCommonRadioButtonGroup** m_ppExpModeButton;

	CCommonRadioButtonGroup* m_tabButton;


	CCommonRadioButtonGroup* m_ppSystemVoiceButton;
	int m_systemVoiceButtonPrintPage;

	int* m_useEffectPicKosuu;
	int* m_useSuperPicKosuu;

	CPicture* GetUseOkPicture(int page = 1);

//	void ReloadAllVoiceOffButtonPic(void);
	void ReLoadAllButtonPic(void);
	void ReLoadBackConfigBG(void);
	void ReLoadAllRadioButtonPic(void);

	void ReLoadTabPic(void);
	void ReLoadSystemVoicePic(void);

	void ReLoadVoiceButtonPic(int n);
	void ReLoadModeButtonPic(int n);
	void ReLoadCheckButtonPic(int n);
	void ReLoadExpModeButtonPic(int n);
	void ReLoadExpCheckButtonPic(int n);
	void ReLoadClickButtonPic(int n);
	void ReLoadVolumeButtonPic(int n);

	int m_voiceAutoLineSetFlag;
	int m_voiceAutoLinePrintX;
	int m_voiceAutoLinePrintY;
	int m_voiceAutoLineNextX;
	int m_voiceAutoLineNextY;
	int m_voiceAutoLineNumberX;
	int m_voiceAutoLineNumberY;

	int m_systemVoiceButtonKosuu;

	int m_page;
	int m_pageMax;
	int m_pageYoyaku;
	BOOL m_pageYoyakuFlag;

	int m_pageMode;

	int m_volumeKosuu;
	int m_modeButtonKosuu;
	int m_checkButtonKosuu;
	int m_expModeButtonKosuu;
	int m_expCheckButtonKosuu;
	int m_clickButtonKosuu;

	int* m_volumePrintPage;
//	int m_messageSpeedPrintPage;
	int m_voicePrintPage;
	int* m_modeButtonPrintPage;
	int* m_modeButtonExistFlag;

	int* m_checkButtonPrintPage;
	int* m_expModeButtonPrintPage;
	int* m_expCheckButtonPrintPage;
	int* m_clickButtonPrintPage;

	int m_mustStartPage1Flag;

	int MyReturnRoutine(void);

	void ChangePage(void);
	void ChangePageYoyaku(void);

	int m_pageNumberVarNumber;
	LPSTR m_pageNumberVarName;
	int m_pageNumberSetFlag;

	void SetPageNumber(void);

	int m_changePageRestartScriptFlag;

	void CreateStartScreen(void);
//	void CreateExitScreen(void);

	int m_volumeMin;
	int m_volumeMax;
	int m_messageIsVoice;
	int m_autoIsVoice;
	int m_windowPercentIsVoice;

	int m_voiceNameChangeFlag;
	int* m_voiceNameCheckChangeVar;


	int m_voiceVoiceChangeFlag;
	int* m_voiceVoiceCheckChangeVar;
	int* m_voiceVoiceChangeVoice;

	BOOL* m_volumeExistFlag;

	int m_windowKosuu;
	int m_windowPrintPage;

	POINT m_windowPrint;
	int m_windowPrintFlag;
	LPSTR m_nameMessage;
	int m_windowMessageKosuu;
	LPSTR* m_windowMessage;

	int m_namePrintX;
	int m_namePrintY;
	int m_nameFontSize;
	int m_nameColorR;
	int m_nameColorG;
	int m_nameColorB;
	int m_nameColorA;

	int m_messagePrintX;
	int m_messagePrintY;
	int m_messageNextX;
	int m_messageNextY;
	int m_messageFontSize;
	int m_messageColorR;
	int m_messageColorG;
	int m_messageColorB;
	int m_messageColorA;

	int m_voiceSameBufferFlag;

	CMyMessage* m_message;

	int m_charaVoiceVolumeFlag;

	int m_charaVoiceSliderMin;
	int m_charaVoiceSliderMax;

	int m_charaVolumePrintX;
	int m_charaVolumePrintY;
	int m_charaVolumeSizeX;
	int m_charaVolumeSizeY;


	int m_playOffToOnSound;
	int m_barVoiceIsSystemVoice;

	void InitAllConfig(void);


	int m_initWindowPercent;
	int m_initWindowNumber;
	int m_initTotalVolume;
//	int m_initMusicVolume;
//	int m_initSoundVolume;
	//int m_initVoiceVolume;
	//int m_initSoundVoiceVolume;
	int m_initSkipMode;
	int m_initMessageSpeed;
	int m_initAutoSpeed;
	int m_initCharaVoiceVolume;
	int m_initAnimeSwitch;
//	int m_initMovieVolume;
	int m_initCharaVoiceOff;

	void CheckAndSetSlider(int n,int vol);

	int m_realVolumeLimitMin;
	int m_realVolumeLimitMax;

	int m_initVolume[10];
	int m_initVolumeSwitch[10];

	int m_realVolumeMinTable[10];
	int m_realVolumeMaxTable[10];

	int m_inSetVar;
	int m_inSetVarData;
	int m_outSetVar;
	int m_outSetVarData;

	CNameList** m_seVoice;
	int m_useConfigSeVoice;

	LPSTR GetSoundName(int nm);

	LPSTR* m_sampleText;
	int m_useSampleText;
	int m_sampleTextPrintX;
	int m_sampleTextPrintY;
	int m_sampleTextNextY;
	int m_sampleTextFontSize;
	int m_sampleTextPrintPage;
	int m_sampleTextCount;
	int m_sampleTextColorR;
	int m_sampleTextColorG;
	int m_sampleTextColorB;
	int m_sampleTextWait;
	int m_sampleTextLoop;

	int m_messageSpeedTable[5];
	int m_autoMessageSpeedTable[5];

	int m_samplePrintGyoCount;
	int m_sampleNowPrintGyo;

	void PrintSampleText(void);
	int m_mojiTime;

	bool CheckAppearCharaVoice(int n);
	bool CheckEnableSystemCharaVoice(int n);

	int* m_systemCharaVoiceCheckCharaNumber;
	int* m_systemCharaVoiceCheckVar;

	int* m_charaVoiceVolumeSE;

	int m_menuStartCount;
	int m_menuStartWaitTime;
	int m_menuStartEffectTime;
	int m_menuStartEffectType;

	int m_appearCount;
	int m_appearCountMax;

	int GetStartWaitMode(void);
	void EndStartWaitMode(void);

private:



};

#endif
/*_*/

