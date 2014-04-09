//
// NameInput.h
//

#if !defined __NNNLIB_COMMONNAMEINPUT__
#define __NNNLIB_COMMONNAMEINPUT__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CCommonButton;
class CMyTextInputBox;

class CMyMessage;
//class CViewControl;

class CCommonNameInput : public CCommonGeneral
{
public:
	CCommonNameInput(CGameCallBack* lpGame);
	virtual ~CCommonNameInput();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

//	void SetDefaultName(LPSTR sei,LPSTR mei);

	virtual void FinalExitRoutine(void);

protected:

	CMyMessage* m_message;

	CMyTextInputBox* m_textInputBox;

	CCommonButton* m_okButton;
	CCommonButton* m_cancelButton;

	int m_processMode;
	int m_processMax;

	int m_seimeiType[2];


	int m_seimeiFlag[2];
	int m_seimeiMax[2];
	int m_seimeiFixFlag[2];
	LPSTR m_seimeiFixData[2];
	int m_seimeiDontPrint[2];
	POINT m_seimeiZahyo[2];
	int m_seimeiAlignMode[2];
	int m_seimeiColor[2][2][3];
	LPSTR m_seimeiDialogFileName[2];

	int m_seimeiReverse;
	int m_useDefaultName;
	int m_noNameIsDefault;

//	int m_cursorMode;
//	int m_cursorColor[3];
//	SIZE m_cursorSize;
//	POINT m_cursorZahyo;
//	int m_cursorOnTime;
//	int m_cursorOffTime;

	int m_fontSize[2];
	int m_fontSukima[2];
	POINT m_dialogZahyo;
	SIZE m_dialogSize;

	int m_returnOkFlag;
	int m_nullNameOk;
	int m_returnStatusVarNumber;
	int m_returnTimeVarNumber;

	int m_count;
	BOOL m_inputFlag;
	BOOL m_exitFlag;

	void SetTextInputBox(int n);
	void LoadDialog(int n);
	void SetDefaultNameToName(void);

	void SetButtonEnable(void);

	static char m_defaultSeiFixData[];
	static char m_defaultMeiFixData[];

	static char m_defaultSeiDialogFileName[];
	static char m_defaultMeiDialogFileName[];

//	char* m_defaultSeimeiData[2];
	char* m_seimeiData[2];

	int m_lastEnable[2];

	int m_nullSeiIsDefault;
	int m_nullMeiIsDefault;
	int m_nullNameIsDefault[2];

//	CViewControl* m_viewControl;

};

#endif
/*_*/

