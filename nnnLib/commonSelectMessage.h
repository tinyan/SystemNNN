//
// SelectMessage.h
//

#if !defined __NNNLIB_COMMONSELECTMESSAGE__
#define __NNNLIB_COMMONSELECTMESSAGE__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CMyMessage;
class CSuuji;

class CAutoSelectControl;


class CCommonSelectMessage : public CCommonGeneral
{
public:
	CCommonSelectMessage(CGameCallBack* lpGame);
	virtual ~CCommonSelectMessage();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);


//	void SetMessage(int kosuu, LPSTR* lpPtr,int* lpMessageNumber);

	int GetMessageKosuu(void) {return m_messageKosuu + m_addMessageKosuu;}
	int GetAddMessageKosuu(void){return m_addMessageKosuu;}
	void SetMessageKosuu(int selectKosuu,int addMessageKosuu = 0) {m_messageKosuu = selectKosuu;m_addMessageKosuu = addMessageKosuu;}

	LPSTR GetMessagePointer(int n);
	void SetMessageData(int n,LPSTR mes);
	void SetTimeLimit(int timeLimit,int autoSelect);

	int GetTimeLimit(void){return m_timeLimit;}
	int GetAutoSelect(void){return m_autoSelect;}
	int GetTimeLimitCount(void){return m_timeLimitCount;}
	int GetSpecialFlag(void){return m_specialFlag;}


	void SetTimeLimitCount(int count){m_timeLimitCount = count;}
	void SetSpecialFlag(int flg){m_specialFlag = flg;}

	static char m_defaultCursorFileName[];
	static char m_defaultBackFileName[];

	static char m_defaultWindowFileName[];

	static char m_defaultBacklogMessage[];
	static char m_defaultBacklogMessage_1byte[];

	static char m_defaultSelectedMessage[];
	static char m_defaultSelectedMessage_1byte[];

	static char m_defaultTimeupMessage[];
	static char m_defaultTimeupMessage_1Byte[];

	virtual void SetBackLogMessage(void);
	BOOL CheckWindowOn(void);

	int m_autoDebugWait;
	CAutoSelectControl* m_autoSelectControl;

protected:

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}


	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

	void CalcuCursorAnime(void);

	CMyMessage* m_message;
//	CMessageWindow* m_messageWindow;
	CPicture* m_selectPic;
	int* m_picBuffer;

	CPicture* m_optionPic;

	void PrintMessageSub(int printN,int dataN = -1,BOOL bAllFlag = TRUE,BOOL addMessageFlag = FALSE);
	int GetOnPlace(int mouseX,int mouseY);

	int m_messageKosuu;
	int m_addMessageKosuu;
	char m_messageData[64][256];
	int m_messageNumber[64];

	int m_windowOffMouseButton;


	int m_nowSelect;
	int m_maeSelect;

	BOOL m_clickingFlag;
	int m_clickingCount;

	int m_messagePrintX;
	int m_messagePrintY;
	int m_messageNextX;
	int m_messageNextY;

//	int m_messageSizeX;
//	int m_messageSizeY;

//	int m_selPiclPitch;
	int m_selectAnimeCount;

//	BOOL m_appearingFlag;
//	int m_appearingCount;

	BOOL m_windowOffFlag;

	int m_nowOptionSelectNumber;
	int m_maeOptionSelectNumber;

	int m_optionPrintX;
	int m_optionPrintY;
	int m_optionSizeX;
	int m_optionSizeY;

	int m_nowSelectNumber;


	int GetOnOptionButton(int mouseX, int mouseY);

	int m_cursorDeltaX;
	int m_cursorDeltaY;
	int m_cursorSizeX;
	int m_cursorSizeY;

	int m_firstWait;


//	int m_fillColorR;
//	int m_fillColorG;
//	int m_fillColorB;

//	int m_nextMode;
//	CNameList* m_setup;

	int m_fontSize;

	int m_firstAppearTime;
	int m_firstAppearCount;
	int m_firstAppearType;

	int m_optionOk;
	int m_backLogOk;

	int m_animePatternKosuu;
	
	int m_animeFrame;
	int m_animeReverse;
	int m_animePrintType;
	int m_animePercent;
	int m_animePic1;
	int m_animePic2;

	int m_cursorIsOnMessage;



	int m_specialAnimePatternKosuu;
	
	int m_specialAnimeFrame;
	int m_specialAnimeReverse;
	int m_specialAnimePrintType;
	int m_specialAnimePercent;
	int m_specialAnimePic1;
	int m_specialAnimePic2;

	int m_specialCursorIsOnMessage;


	int m_backPrintMode;
	int m_backColorR;
	int m_backColorG;
	int m_backColorB;
	LPSTR m_filenameBack;

	LPSTR m_filenameUpDown;
	int m_scrollSelectFlag;

	int m_messagePrintGyo;

	int m_useSelectScrollButtonFlag;
	int m_page;
	int m_pageMax;

	int m_windowPrintFlag;
	LPSTR m_windowFileName;
	int m_windowPrintX;
	int m_windowPrintY;
	int m_windowSizeX;
	int m_windowSizeY;

	int m_timeLimitWindowPrintFlag;
	LPSTR m_timeLimitWindowFileName;
	int m_timeLimitWindowPrintX;
	int m_timeLimitWindowPrintY;
	int m_timeLimitWindowSizeX;
	int m_timeLimitWindowSizeY;

	LPSTR m_backlogMessage;
	int m_backlogMessageColorR;
	int m_backlogMessageColorG;
	int m_backlogMessageColorB;

	int m_backlogSelectColorR;
	int m_backlogSelectColorG;
	int m_backlogSelectColorB;

	int m_selectSound;
	int m_windowOnSound;
	int m_windowOffSound;
	int m_backlogSound;

	int m_timeLimit;
	int m_autoSelect;
	int m_timeLimitCount;

	int m_timerColorR1;
	int m_timerColorG1;
	int m_timerColorB1;

	int m_timerColorR2;
	int m_timerColorG2;
	int m_timerColorB2;

	int m_timerPrintType;
	int m_timerPrintX;
	int m_timerPrintY;
	int m_timerPicSizeX;
	int m_timerPicSizeY;
	int m_timerPicKosuu;
	int m_timerBarHoukou;

	CPicture* m_timerPic;

	int m_timerSuujiPrintFlag;
	CSuuji* m_timerSuuji;
	CSuuji* m_timerSuuji2;

	int m_timerSuujiPrintX;
	int m_timerSuujiPrintY;

	int m_timerSuujiPrintX2;
	int m_timerSuujiPrintY2;

	BOOL CheckOptionOk(void);
	int m_timeLimitOptionOk;

	POINT GetSrcPoint(CPicture* lpPic,int n,int sizeX,int sizeY);
	POINT GetSrcPoint2(CPicture* lpPic,int n,int sizeX,int sizeY);
	BOOL CheckTimeLimitActionOk(void);
	int m_clickingTime;
	int m_selected;

//	int m_keyMoveEnable;
//	int m_keyMoveUpDownEnable;
//	int m_keyMoveLeftRightEnable;
//	int m_lastKeyButton;


	//åpè≥
	int GetOnKeyArea(POINT pt);
	void SetCursorToKeyArea(int pl);
	int KeyMoveAction(int delta,int deltaX,int deltaY);

	int m_specialFlag;

	int m_useSpecialFlagKosuu;
	int m_specialWindowSizeX;
	int m_specialWindowSizeY;
	int* m_specialWindowPrintX;
	int* m_specialWindowPrintY;
	int* m_specialCheckVar;

	int m_specialMessagePrintX;
	int m_specialMessagePrintY;

	CPicture* m_specialSelectPic;
	int m_specialFontSize;

	int m_specialCursorDeltaX;
	int m_specialCursorDeltaY;
	int m_specialCursorSizeX;
	int m_specialCursorSizeY;

	BOOL CheckSpecial(void);

	SIZE GetSelectCursorSize(void);
	POINT GetSelectCursorDelta(void);

	POINT GetMessageZahyo(int place);
	POINT GetAddMessageZahyo(int place);
	POINT GetSelectCursorZahyo(int place);

	POINT GetSpecialWindowZahyo(int place);

	CPicture* GetSelectCursorPic(void);

	void PrintSpecialWindow(int place,int windowNumber);

	CPicture* m_specialWindowPic;

	int m_centeringFlag;
	int m_centerAreaSizeX;

	void CheckAndAutoOff(void);

	int m_messageColorR;
	int m_messageColorG;
	int m_messageColorB;
	int m_selectedColorR;
	int m_selectedColorG;
	int m_selectedColorB;

	LPSTR m_timeupMessage;
	int m_selectedDotNumber;

	LPSTR* m_selectedDotMessage;

	int m_dotColorR;
	int m_dotColorG;
	int m_dotColorB;
	int m_timeupColorR;
	int m_timeupColorG;
	int m_timeupColorB;

private:

};


#endif
/*_*/

