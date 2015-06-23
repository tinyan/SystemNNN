#if !defined __NNNUTILIB_MYTEXTINPUTBOX__
#define __NNNUTILIB_MYTEXTINPUTBOX__


class CMyMessage;
class CNameList;
class CInputStatus;

class CMyIME;

#define SOFTKEY_X_MAX 32
#define SOFTKEY_Y_MAX 16


class CSoftKey
{
public:
	CSoftKey(CMyMessage* message);
	~CSoftKey();
	void End(void);

	void Init(LPSTR kakuteiText = NULL);
	int Calcu(CInputStatus* lpInput);
	void Print(void);

	typedef struct _tagMYSOFTKEY
	{
		int page;
		int x,y;
		char key[16];
	}MYSOFTKEY;

	typedef struct _tagMYSOFTCOMMANDKEY
	{
		int cmd;
		char key[16];
	}MYSOFTCOMMANDKEY;

	LPSTR GetKakuteiText(void);
	LPSTR GetHenkanText(void);
	LPSTR GetInputText(void);
	int  GetKakuteiLength(void);
	int GetHenkanLength(void);
	int GetInputLength(void);

	void SetTextLengthMax(int* table);
	BOOL CheckEnableCommandKey(int cmd);

private:
	static char m_to2byteTable[];
	static MYSOFTKEY m_defaultKeySet[];
	static char m_dakutenList[][4];
	static char m_handakutenList[][4];
	static MYSOFTCOMMANDKEY m_commandKeyList[];
	MYSOFTCOMMANDKEY* m_userCommandKeyList;

	int m_shiftKeyList[16];

	int m_textTypeMax;
	int m_textLength[3];
	int m_textLengthMax[3];
	int m_textLengthMaxDefault[3];

//	int m_kakuteiLength;
//	int m_inputLength;
//	int m_henkanLength;
//	int m_kakuteiMax;
//	int m_inputMax;
//	int m_henkanMax;

	char m_text[3][256];
//	char m_kakuteiText[256];
//	char m_inputText[256];
//	char m_henkanText[256];

	int m_softKeyTableNumber;
	MYSOFTKEY* m_softKeyTable;

	POINT m_keyPoint[SOFTKEY_X_MAX][SOFTKEY_Y_MAX];
	SIZE m_keySize[SOFTKEY_X_MAX][SOFTKEY_Y_MAX];

	SIZE m_softKeySize;
	int m_keyPointNextX;
	int m_keyPointNextY;
	int m_keyPointBlockX;
	int m_keyPointBlockY;
	int m_keyPointSkipX;
	int m_keyPointSkipY;
	
	int m_softKeyPrintX;
	int m_softKeyPrintY;
	int m_dialogPrintX;
	int m_dialogPrintY;

	int m_fontSize;
	int m_useFont;
	int m_fontColorR;
	int m_fontColorG;
	int m_fontColorB;

	int m_selectColorR;
	int m_selectColorG;
	int m_selectColorB;
	int m_selectColorA;


	POINT GetKeyZahyo(int nx,int ny,int page = 0);
	SIZE GetKeySize(int nx,int ny,int page = 0);
	BOOL GetOnArea(POINT pt,POINT checkPoint,SIZE checkSize);
	int GetOnNumber(POINT pt);

	int CheckDakutenList(LPSTR mes);
	int CheckHandakutenList(LPSTR mes);

	int CheckCommandKey(LPSTR mes);


	int m_keyPage;
	int m_keyPageMax;

	CMyMessage* m_message;
//	HWND m_hWnd;
//	CViewControl* m_viewControl;

	CNameList* m_setupList;

	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

	int m_userSoftCommandNumber;

	CMyIME* m_ime;

	int m_onNumber;

	void AddKakutei(LPSTR mes);
	void AddInput(LPSTR mes);
	void AddHenkan(LPSTR mes);
	void AddText(int textType,LPSTR mes);

	BOOL CheckKanjiOnly(LPSTR mes);
	void ClearKakutei(void);
	void ClearInput(void);
	void ClearHenkan(void);

	void ReplaceLastText(int textType,LPSTR repText);
	void DeleteLastText(int textType);

	void PageChanged(void);
	void CopySoftBuffer(int from,int to);

	int GetLastTextType(void);
	char m_lastText[4];
	CPicture* m_dialogPic;

	int GetUserCommand(LPSTR text);

	static MYSOFTCOMMANDKEY m_userCommandCheckList[];

	static char m_defaultDialogFilename[32];
	LPSTR m_dialogFilename[16];
};


#endif
/*_*/

