//
// BackLog.h
//

#if !defined __NNNLIB_COMMONBACKLOG__
#define __NNNLIB_COMMONBACKLOG__

class CCommonGeneral;
class CGameCallBack;
class CNameList;


class CPicture;
class CMyMessage;

#define BACKLOG_KOSUU 256
#define BACKLOG_LENGTH 256
#define VOICEFILE_LENGTH 16



class CCommonBackLog : public CCommonGeneral
{
public:
	CCommonBackLog(CGameCallBack* lpGame);
	virtual ~CCommonBackLog();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);


//	void SetBackMode(int md);
	void Clear(void);

	void AddMessage(LPSTR mes,int colR = 255, int colG = 255, int colB = 255);
	void ChangePreColor(int backNumber, int colR, int colG, int colB);
	void AddBar(void);

	void AddVoice(LPSTR filename);

	static char m_defaultTitleMessage[];
	static char m_defualtFirstMessage[];
	static char m_defaultBarMessage[];

	static char m_defaultUpArrow[];
	static char m_defaultDownArrow[];
	static char m_defaultVoice[];

	static char m_defaultBackFilename[];

	static char m_defaultTitlePicFileName[];

	static char m_defaultUpdownArrowFileName[];
	static char m_defaultUpArrowFileName[];
	static char m_defaultDownArrowFileName[];
	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

protected:
	BOOL UpScroll(int n = 1);
	BOOL DownScroll(int n = 1);
	int CheckOnArrow(int mouseX,int mouseY);
	BOOL CheckUpOk(void);
	BOOL CheckDownOk(void);
	int CheckOnVoice(int mouseX, int mouseY);
	POINT GetVoicePrintZahyo(int n);



	CMyMessage* m_message;

	int* m_logColor;
	char* m_logMessage;
	char* m_voiceFile;

	int m_printGyosuuMax;
	int m_printStartGyo;
	int m_messageKosuu;

	int m_nowPointer;
	int m_printPointer;


	int m_printX;
	int m_printY;
	int m_nextX;
	int m_nextY;


	int m_startWait;

	int m_fontSize;

	int m_voiceFlag;

	int m_upArrowPrintX;
	int m_upArrowPrintY;
	int m_downArrowPrintX;
	int m_downArrowPrintY;

	int m_titleMessagePrintX;
	int m_titleMessagePrintY;


	LPSTR m_titleMessage;
	char m_firstMessage[512];
	LPSTR m_barMessage;

	LPSTR m_upArrowMessage;
	LPSTR m_downArrowMessage;
	LPSTR m_voiceMessage;

	int m_updownArrowSizeX;
	int m_updownArrowSizeY;

	int m_updownArrowPicFlag;
	int m_voicePicFlag;

	CPicture* m_updownArrowPic;
	CPicture* m_voicePic;

	CPicture* m_upArrowPic;
	CPicture* m_downArrowPic;

	int m_voiceSizeX;
	int m_voiceSizeY;
	int m_voicePrintX;
	int m_voicePrintY;

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	int m_backlogBGMode;

	int m_backColorR;
	int m_backColorG;
	int m_backColorB;

	int m_backDeltaR;
	int m_backDeltaG;
	int m_backDeltaB;

	int m_backMultiR;
	int m_backMultiG;
	int m_backMultiB;

	LPSTR m_backFilename;

	int ReturnToBackMode(void);

	int m_titlePrintFlag;
	int m_titlePicPrintFlag;
	
	LPSTR m_titlePicFileName;
	int m_titlePicPrintX;
	int m_titlePicPrintY;

	int m_titlePicUpperFlag;

	int m_voicePicAnimeFlag;

	int m_voicePicAnimeCount;
	int m_voicePicAnimeType;
	int m_voicePicAnimeSpeed;
	int m_voicePicAnimePattern;

	void VoicePicAnime(void);

	int m_voicePicPattern1;
	int m_voicePicPattern2;
	int m_voicePicPercent;

	int m_updownArrowAnimeFlag;
	int m_updownArrowAnimeCount;
	int m_updownArrowAnimeType;
	int m_updownArrowAnimeSpeed;
	int m_updownArrowAnimePattern;

	int m_updownArrowPattern1;
	int m_updownArrowPattern2;
	int m_updownArrowPercent;

	void UpdownArrowPicAnime(void);

	void PutVoicePic(int x,int y,int pt);
	int m_onVoiceNumber;

	int m_backScreenEffectNega;
	int m_backScreenEffectGrey;

	int m_returnSoundNumber;

	BOOL m_onUpArrow;
	BOOL m_onDownArrow;

	void PutUpdownArrowPic(int n,int x,int y, int md);

private:


};

#endif
/*_*/

