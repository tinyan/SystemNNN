//
// commonLogo.h
//

#if !defined __NNNLIB_PRINTRESULT__
#define __NNNLIB_PRINTRESULT__


class CGame;

class CPicture;
class CSuuji;


class CCommonButton;

class CMyMessage;

class CPagePrint;
class CNameList;

class CCommonResultData;

class CCommonPrintResult : public CCommonGeneral
{
public:
	CCommonPrintResult(CGameCallBack* lpGame);
	~CCommonPrintResult();
	void End(void);

	int Init(void);
	int Calcu(void);
	int Print(void);

	void FinalExitRoutine(void);

//	void SetFromScript(void);

//	void BeforeCalcu(void);
protected:

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}



//	CPicture* m_leftMaskPic;
//	CPicture* m_rightMaskPic;
//	int m_leftMaskPrintX;
//	int m_leftMaskPrintY;
//	int m_rightMaskPrintX;
//	int m_rightMaskPrintY;
//	int m_maskSizeX;
//	int m_maskSizeY;

	int m_messagePrintX;
	int m_messagePrintY;
	int m_messageFontSize;
	int m_messageColorR;
	int m_messageColorG;
	int m_messageColorB;
	int m_messageSukima;

	int m_messageLength;
	int m_messageNextY;
//	int m_messageGyo;

	int m_resultsPrintX;
	int m_resultsPrintY;
	int m_resultsNextX;
	int m_resultsNextY;
	int m_resultsSizeX;
	int m_resultsSizeY;
	LPSTR m_filenameResultsTag;

	static char m_defaultFilenameResultsTag[];

	CPagePrint* m_pagePrint;



	CPicture** m_resultsPic;

	int m_voiceFlag;
	int m_dialogFlag;


//	void PutMessageMask(void);

	void PutResultsPic(int n);

	POINT GetResultsZahyo(int n);
	POINT GetResultsPicSrc(int n);
	CPicture* GetResultsPic(int n);


	int GetOnResults(POINT pt);
	BOOL CheckOnResults(int n,POINT pt);

	int m_page;
	int m_pageMax;

	int m_nowOnNumber;
	int m_maeOnNumber;

	CMyMessage* m_message;
	CNameList* m_resultsDesc;

	LPSTR m_filenameDialogTag;
	static char m_defaultFilenameDialogTag[];


	int m_dialogPrintX;
	int m_dialogPrintY;
	int m_dialogSizeX;
	int m_dialogSizeY;
	CCommonButton* m_okButton;

	void LoadGetDialog(int n);
	int CheckNewResults(void);

	int m_newResults;
	int m_resultsKosuu;
	int m_resultsNumberX;
	int m_resultsNumberY;
	int m_resultsInPage;

	int GetResultsData(int n);
	void SetResultsData(int n,int d);

	int* m_resultsDataTable;
	int m_voiceStartWaitTime;
	int m_voiceCount;
	int m_scrollStartWaitTime;
	int m_scrollSpeed;
	int m_scrollMax;
	int m_scrollCount;

	int m_messageBlockMax;
	char** m_resultsMessageAll;
	int* m_resultsMessageLength;

	void PlayVoice(int voiceNumber);
	void CalcuScrollMax(int n);

	CCommonResultData* m_resultsData;

	static char m_defaultResultDescFileName[];
//	static char m_defaultLeftMaskFileName[];
//	static char m_defaultRightMaskFileName[];

	int m_descPrintType;

private:
};






#endif
/*_*/

