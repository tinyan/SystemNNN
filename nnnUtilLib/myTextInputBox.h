#if !defined __NNNUTILIB_MYTEXTINPUTBOX__
#define __NNNUTILIB_MYTEXTINPUTBOX__


class CMyMessage;
class CNameList;
class CViewControl;

class CMyTextInputBox
{
public:
	CMyTextInputBox(HWND hwnd,CMyMessage* message,CViewControl* viewControl);
	~CMyTextInputBox();
	void End(void);

	void Start(void);
	void Stop(void);

	void Init(void);
	void AddChara(int ch);
	BOOL CheckReturn(void){return m_pushReturnKeyFlag;}
	LPSTR GetText(void){return m_text;}
	void Print(void);
	void SetText(LPSTR name,BOOL moveFlag = FALSE);

	void SetZahyo(int x,int y,int n);
	void SetFontSize(int fontSize,int sukima,int n);
	void SetMaxLength(int mx,int n);
	void SetAlignFlag(int flg,int n);
	void SetTextColor(int r,int g,int b,int n);

	void SetCursorMode(int md,int n);
	void SetCursorTime(int onTime,int offTime,int n);
	void SetCursorSize(SIZE sz,int n);
	void SetCursorDelta(POINT pt,int n);
	void SetCursorColor(int r,int g,int b,int a,int n);

	void AutoClose(void);

	POINT GetTextZahyo(POINT pt,LPSTR name,int maxLen,int alignMode);

	void SetSetup(CNameList* nameList);
	void SetParameter(LPSTR tagName,int n);

	void ChangeParameterNumber(int n);

	void SetAuto(BOOL autoOpen,BOOL autoClose){m_autoOpenFlag = autoOpen; m_autoCloseFlag = autoClose;}
private:

	static char CMyTextInputBox::m_to2byteTable[];

	CMyMessage* m_message;
	HWND m_hWnd;
	CViewControl* m_viewControl;

	int m_notControlIME;

	POINT* m_zahyo;
	int* m_fontSize;
	int* m_sukimaSize;
	int* m_maxLength;
	SIZE* m_areaSize;
	int* m_cursorMode;
	int* m_cursorColor;
//	int m_cursorColorG;
//	int m_cursorColorB;
	int* m_textColor;
//	int m_textColorG;
//	int m_textColorB;
	int* m_cursorTime;
//	int* m_cursorOffTime;
	POINT* m_cursorDelta;
	SIZE* m_cursorSize;
	int* m_alignFlag;

	void CalcuAreaSize(int n);

	BOOL m_enableFlag;
	BOOL m_immMovedFlag;

	void MoveIMEWindow(void);
	void RemoveIMEWindow(void);

	BOOL m_immWindowParamGetFlag;

	POINT m_immZahyo;
	RECT m_immRect;

	BOOL m_changedFlag;

	BOOL m_kanjiFlag;
	int m_kanjiHigh;
	int m_kanjiLow;

	BOOL AddKanji(int high,int low);
	BOOL DelKanji(void);
	BOOL m_pushReturnKeyFlag;

	int m_textBufferSize;
	char* m_text;

	int m_cursorCount;
//	int m_cursorTime;



	void CursorAnime(int cnt = 1);
	void PrintCursor(void);

	POINT GetCursorZahyo(void);
	POINT GetTextZahyo(void);



	int m_nowParameterNumber;
	int m_parameterShuruiKosuu;
	CNameList* m_setupList;

	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

	BOOL m_autoOpenFlag;
	BOOL m_autoCloseFlag;

};


#endif
/*_*/

