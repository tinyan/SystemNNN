//
// Save.h
//

#if !defined __TINYAN_NNNLIB_COMMONSAVE__
#define __TINYAN_NNNLIB_COMMONSAVE__

class CCommonGeneral;
class CCommonLoadSave;
class CGameCallBack;
//class CFileControl;

//class CMyTextInputBox;

class CCommonButtonGroup;
class CCommonDataFile;

class CCommonSave : public CCommonLoadSave
{
public:
	CCommonSave(CGameCallBack* lpGame);
	virtual ~CCommonSave();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	static char m_defaultBGFileName[];
	static char m_defaultDialogFileName[];
//	static char m_defaultButtonFileName[];

	static char CCommonSave::m_buttonName[][16];

	static char m_defaultSuujiFileName[];

//	static char m_defaultUpFileName[];
//	static char m_defaultDownFileName[];

	virtual void CreateStartScreen(void);
	virtual BOOL QuickSave(void);


protected:
	virtual int ProcessDataClicked(int n);
	virtual int ProcessStartClickExistData(int n);
	virtual int ProcessStartClickNotExistData(int n);

	virtual int CalcuWarning(void);

	virtual int CalcuComment(void);

	virtual void SaveNowData(void);
	//LPSTR m_bgFileName;
	//LPSTR m_dialogFileName;

	//BOOL m_warningFlag;
	int m_saveNumber;

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	virtual void PrintInputBoxStatus(void);


	int m_saveSound;
	int m_warningSound;
//	CCommonButtonGroup* m_dialogButton;
//	int m_commentInputFlag;

	virtual void StartNameInput(int n);
//	CMyTextInputBox* m_textInputBox;

//	int m_commentInputCursorMode;
//	int m_commentInputCursorColor[4];
//	POINT m_commentInputCursorZahyo;
//	SIZE m_commentInputCursorSize;

//	int m_commentInputCursorOnTime;
//	int m_commentInputCursorOffTime;

//	int m_commentInputFontSize;
//	int m_commentInputFontSukima;
//	int m_commentInputReturnOkFlag;
	int m_commentInputNullNameOk;


	void InitPageButton(void);
	BOOL m_clickExistDataFlag;



	int m_saveCommentLineNumber;

	int m_textBoxPrintX;
	int m_textBoxPrintY;

	CSuuji* m_textBoxDateSuuji4;
	CSuuji* m_textBoxDateSuuji2;
	CSuuji* m_textBoxGameYearSuuji4;
	CSuuji* m_textBoxGameDateSuuji2;
	CSuuji* m_textBoxGameDateSuuji2B;

	int m_textBoxDatePrintFlag;
	int m_textBoxDatePrintX;
	int m_textBoxDatePrintY;
	int m_textBoxDateFontSizeX;
	int m_textBoxDateFontSizeY;
	int m_textBoxDateFontNextX;


	int m_textBoxGameYearPrintFlag;
	int m_textBoxGameYearFontSizeX;
	int m_textBoxGameYearFontSizeY;
	int m_textBoxGameYearFontNextX;
	int m_textBoxGameYearPrintX;
	int m_textBoxGameYearPrintY;

	int m_textBoxGameDatePrintFlag;
	int m_textBoxGameDateFontSizeX;
	int m_textBoxGameDateFontSizeY;
	int m_textBoxGameDateFontNextX;
	int m_textBoxGameDatePrintX;
	int m_textBoxGameDatePrintY;
	int m_textBoxGameDateLeftFlag;

	CPicture* m_textBoxAddPic;
	int m_textBoxAddPicPrintFlag;
	int m_textBoxAddPicWithSpecialFlag;
	POINT m_textBoxAddPicPrintZahyo;
	SIZE m_textBoxAddPicSize;
	int m_textBoxAddPicMultiFlag;
	int m_textBoxAddPicMultiKosuuX;


	int m_textBoxSpecialNumberPrintFlag;
	int m_textBoxSpecialNumberPrintLimit;
	CSuuji* m_textBoxSpecialNumberSuuji;
	POINT m_textBoxSpecialNumberPrintZahyo;


	int m_gameYearVarNumber;
	int m_gameDateVarNumber;


	CPicture* m_savePic;
	int m_miniCGPrintFlag;
	int m_miniCGPrintX;
	int m_miniCGPrintY;

	int m_saveVoiceKosuu;
	int m_warningVoiceKosuu;
	LPSTR* m_saveVoice;
	LPSTR* m_warningVoice;
	void PlaySaveVoice(void);
	void PlayWarningVoice(void);

	int m_quickSetLastFlag;

	int m_saveVoiceRandomFixVarNumber;
	int m_warningVoiceRandomFixVarNumber;


};

#endif
/*_*/

