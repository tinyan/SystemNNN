//
// PrintMessage.h
//

#if !defined __NNNLIB_COMMONPRINTMESSAGE__
#define __NNNLIB_COMMONPRINTMESSAGE__




#define MESSAGEKOSUU_MAX 64
//#define MESSAGEPRINT_MAX 32
#define MESSAGEBYTE_MAX 256

class CPicture;
class CGameCallBack;
class CMyMessage;
class CMessageCursor;

class CPrintAnimeLayer;

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CNameColor;
class CCutinNameData;

class CCutinMessageWindow;

class CCommonPrintMessage : public CCommonGeneral
{
public:
	CCommonPrintMessage(CGameCallBack* lpGame);
	virtual ~CCommonPrintMessage();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);



	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);


	void Clear(void);

	void SetMessageMode(int cmd, int nm, LPSTR mes,int cutin = 0);
	void SetDrawMode(int count);
	void SetOverrapMode(int overrapType,int overrapTime);


	void SetMessageRead(void);


//	typedef struct _tagJINBUTSUNAMECOLOR
//	{
//		char name[16];
//		int colR,colG,colB;
//	} JINBUTSUNAMECOLOR;

//	static JINBUTSUNAMECOLOR m_jinbustu[];

	void WindowOn(BOOL flag = TRUE);
//	void CommandOn(BOOL flag = TRUE);


	int GetMessageKosuu(void);
	void SetMessageKosuu(int n);

	LPSTR GetMessagePointer(int n);
	void SetMessageData(int n,LPSTR mes);

	void SetCGMode(BOOL b);
	void SetSceneMode(BOOL b);

//	int GetJinbutsuNumber(LPSTR name);
//	int GetJinbutsuColor(int pl, int rgbNum);


	void SetPrintModeByLoad(int md);
	int GetPrintModeForSave(void);

	BOOL CheckFullMessageMode(void);
	void InitByLoad(void);

	void ResetShakin(void);
	int GetShakin(void);


	static char m_defualtNameColorFileName[];


	virtual void OnEndFilm(void);


	void SetAutoFilmFlag(BOOL flg = TRUE){m_autoFilmFlag = flg;}
	BOOL CheckWindowOn(void);

	void SetCutinMode(int md = 1);
//	void SetCutinFile(int layer,LPSTR filename);
	void SetMessageExpStatus(int st);
	void OnClearAllEffect(void);
	void OnClearEffect(int layer);

	void SetCutinByLoad(int* ptr);
	void GetCutinForSave(int* ptr);


	static char m_defaultNameFileName[];
	static char m_defaultLprintBGFileName[];

	void CheckAndPrintFillWindow(void);
	void PrintFullWindow(void);

	void SetNextMessageEffect(int md);
	void SetNextMessageEffectTime(int md);

	int GetMessageSpeedTable(int n, bool autoFlag);
protected:
	CMyMessage* m_message;
	CMessageCursor* m_cursor;

	CPicture* m_optionPic;
	CPicture* m_backPic;

	int m_shakin;


//	int m_subMode;
	int m_drawCount;

	int m_messageKosuu;

	int m_jinbutsuNameKosuu;
	int m_nameNumber;


//	int GetOnButton(int mouseX, int mouseY);

	int m_messagePrinted[MESSAGEKOSUU_MAX];
	int m_messageLength[MESSAGEKOSUU_MAX];

	char m_messageData[MESSAGEKOSUU_MAX][MESSAGEBYTE_MAX];

	int m_cutinData[MESSAGEKOSUU_MAX*2];

	void MessageIsRead(void);
	BOOL CheckMessageRead(void);

	BOOL m_windowOffFlag;
//	BOOL m_commandOffFlag;

	int m_messagePrintedGyo;

	int m_printMode;
	BOOL m_messagePrintingFlag;
	int m_messagePrintSpeed;
	int m_autoMessagePrintSpeed;
	BOOL m_namePrintedFlag;

	int m_messagePrintMojisuu;
//	int m_messagePrintMojisuuPerSecond;

	int m_messageSpeedTable[5];
	int m_autoMessageSpeedTable[5];
	int m_messageSerialNumber;

	BOOL m_skipFlag;
	BOOL m_maeSkipFlag;
	BOOL m_messageSkipMode;

//	BOOL m_windowFlag;

//	BOOL m_cgMode;
	BOOL m_sceneMode;

	int m_cursorPat;

//	int m_nowSelectNumber;

	int m_optionPrintX;
	int m_optionPrintY;
	int m_optionSizeX;
	int m_optionSizeY;

	int m_backPrintX;
	int m_backPrintY;
	int m_backSizeX;
	int m_backSizeY;

//	int m_th1;
//	int m_th2;
//	int m_deltaTh1;
//	int m_deltaTh2;
//	int m_r1;
//	int m_r2;

	int m_deltaPaste;

	BOOL CheckAuto(void);
	int m_autoLastCount;

	int m_noVoiceWait;


	int m_fontSizeTypeKosuu;

	int m_fontSize0;
	int m_fontSize;

	int m_printX;
	int m_printY;
	int m_nextX;
	int m_nextY;
	int m_printX0;
	int m_printY0;
	int m_nextX0;
	int m_nextY0;
	int m_LPrintX;
	int m_LPrintY;
	int m_LNextX;
	int m_LNextY;

	int m_spaceX;
	int m_spaceX0;
	int m_colorR;
	int m_colorG;
	int m_colorB;
	int m_shadeColor;

	int* m_fontSizeByFontSizeType;
	int* m_printXByFontSizeType;
	int* m_printYByFontSizeType;
	int* m_nextXByFontSizeType;
	int* m_nextYByFontSizeType;
	int* m_spaceByFontSizeType;

	int* m_nameXByFontSizeType;
	int* m_nameYByFontSizeType;
	int* m_nameSpaceByFontSizeType;

	int m_nameX;
	int m_nameY;
	int m_nameX0;
	int m_nameY0;

	int m_nameFontSize;

	int m_nameCenterFlag;
	int m_nameLengthMax;

	int m_blockX;
	int m_blockY;
	int m_LBlockX;
	int m_LBlockY;

	int m_nameFlag;
	int m_nameColorChangeFlag;

	int m_nameColorR;
	int m_nameColorG;
	int m_nameColorB;

	int m_nameShadeColor;

	int m_colorCustomFlag;

	int m_nameSpaceX;
	int m_nameSpaceX0;


//	int m_optionFlag;
//	int m_drawOptionFlag;
//	int m_LPrintOptionFlag;

	int m_drawOverrapOptionFlag;

	CNameColor* m_nameColor;


	virtual int PrintMessageMode(BOOL fromDraw = FALSE);
	virtual int PrintDrawMode(void);
	virtual int PrintOverrapMode(void);
//	virtual int PrintCutinMode(void);


	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	int m_windowMessageKosuuMax;
	int m_fullMessageKosuuMax;

	int m_autoNameWindowFlag;

	BOOL CheckHaveName(void);

	CNameList* m_charaNameList;

	int m_backlogSound;

	int m_kaeshita;

	int m_overrapType;
	int m_overrapTime;
	int m_overrapCount;

	int m_overrapCountForPrint;


	void ShakinHensai(void);

	virtual BOOL CheckOverrapEnd(void);
	virtual int CalcuOpeningMode(void);
	virtual int CalcuDrawMode(int rt);
	virtual int CalcuOverrapMode(int rt);
	virtual int CalcuPrintMode(int rt);
//	virtual int CalcuCutinMode(int rt);


	BOOL CheckWindowOff(void);
	BOOL CheckPrintMode(void);

//	BOOL CheckCommandOn(void);
//	BOOL CheckCommandOff(void);

	BOOL m_autoFilmFlag;
	int m_mojiTimeAmari;
//	int m_autoVoiceWaitLastTime;

	BOOL CheckWindowOffOperation(void);
	BOOL CheckWindowOnOffEnable(void);

	int m_windowOffMouseButton;

	void CalcuFrameMoji(void);
private:
	void MessageScroll(void);

//	int m_fillColorR;
//	int m_fillColorG;
//	int m_fillColorB;

//	int m_nextMode;
//	CNameList* m_setup;

	BOOL CheckAutoMessage(void);
	int GetAutoMessageSpeed(void);

	BOOL CheckCannotSkip(void);
	BOOL CheckCannotClick(void);

	BOOL CheckSceneEnd(int rt);
	BOOL CheckSkipOrClickDrawAndOverrrap(int rt);

	BOOL CheckOkuri(void);
	BOOL CheckOption(void);
	void CheckUserSkipOff(void);

	int CalcuOptionButton(void);
	BOOL CheckMessagePrintEnd(void);
	BOOL CheckSceneMode(void);
	void CalcuPrinting(void);
	BOOL CheckBackLogOk(void);

	int m_autoMessageCount;
	int m_autoMessageLastTime;

	int m_noVoiceLastWait;
	int m_voiceLastWait;
	int m_autoMessageVoiceLastWait;

	int m_noVoiceLastWaitTable[5];
	int m_voiceLastWaitTable[5];
	int m_noVoiceLastWaitTableAutoMode[5];
	int m_voiceLastWaitTableAutoMode[5];

	int m_checkWheelOkuri;
	int m_cutinMode;
	int m_useAutoModeWait;

	int m_nowMessageLayer;
//	POINT m_cutinZahyo[16];
//	int m_cutinMessageKosuu[16];
//	int m_cutinMessagePrinted[16][20];
//	int m_cutinMessageLength[16][20];
//	char* m_cutinMessage[16][20];

	int m_cutinWaitClick;

	int m_useCutinFlag;

	CCutinNameData* m_cutinNameData;
	int m_cutinNamePrintFlag;

	CCutinMessageWindow* m_cutinMessageWindow;

	int m_autoLastCount2;
	int m_autoMessageWaitVoiceFlag;

	int m_noVoiceIsDefaultWait;

	int m_rightSkipOffIsClick;

//	int m_drawOverrapPrintOption;

	CPicture* m_namePic;
	int m_namePicFlag;
	int m_namePicSizeX;
	int m_namePicSizeY;
	int m_namePicDeltaX;
	int m_namePicDeltaY;

	int m_messageFontSizeType;

	int m_drawWindowWithMessageFlag;

	int m_lprintBGMode;
	LPSTR m_lprintBGFilename;
	int m_lprintBGDeltaR;
	int m_lprintBGDeltaG;
	int m_lprintBGDeltaB;
	int m_lprintBGMultiR;
	int m_lprintBGMultiG;
	int m_lprintBGMultiB;
	CPicture* m_lprintBGPic;

	int m_lprintBGScreenEffectNega;
	int m_lprintBGScreenEffectGrey;

	int m_lprintBGPrintX;
	int m_lprintBGPrintY;

	int m_lprintBGClipX;
	int m_lprintBGClipY;
	int m_lprintBGClipSizeX;
	int m_lprintBGClipSizeY;

	int m_lprintBGNegaClipX;
	int m_lprintBGNegaClipY;
	int m_lprintBGNegaClipSizeX;
	int m_lprintBGNegaClipSizeY;

	int m_lprintBGGreyClipX;
	int m_lprintBGGreyClipY;
	int m_lprintBGGreyClipSizeX;
	int m_lprintBGGreyClipSizeY;

	int m_lprintBGMultiClipX;
	int m_lprintBGMultiClipY;
	int m_lprintBGMultiClipSizeX;
	int m_lprintBGMultiClipSizeY;

	int m_lprintBGAddSubClipX;
	int m_lprintBGAddSubClipY;
	int m_lprintBGAddSubClipSizeX;
	int m_lprintBGAddSubClipSizeY;

	int m_printAutoAnimeFlag;
	int m_printSkipAnimeFlag;
	CPrintAnimeLayer* m_printAutoAnime;
	CPrintAnimeLayer* m_printSkipAnime;

	int m_messageEffect;
	int m_messageEffectYoyaku;

	int m_messageEffectTimeYoyaku;
	int m_messageEffectSpeed;

	int m_appendSkipName;
	CPicture* m_lprintAddImagePic;
	int m_lprintAddImageFlag;

};

#endif
/*_*/

