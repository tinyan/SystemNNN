//
// loadSave.h
//

#if !defined __TINYAN_NNNLIB_COMMONLOADSAVE__
#define __TINYAN_NNNLIB_COMMONLOADSAVE__

class CCommonGeneral;
class CGameCallBack;
//class CFileControl;


class CCommonButtonGroup;
class CCommonDataFile;
class CSuuji;
class CPagePrint;
class CDataFileSetup;
class CCommonRadioButtonGroup;
class CMyTextInputBox;
class CCommonAnimeParts;

class CCommonLoadSave : public CCommonGeneral
{
public:
	CCommonLoadSave(CGameCallBack* lpGame,LPSTR modename);
	virtual ~CCommonLoadSave();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual int CalcuWarning(void);
	virtual int CalcuComment(void);

	virtual void ChangeExtDataSize(int extNumber,int dataSize);

protected:
	virtual int ProcessDataClicked(int n) = 0;
	virtual int ProcessStartClickExistData(int n) = 0;
	virtual int ProcessStartClickNotExistData(int n) = 0;
	virtual void FinalExitRoutine(void) {}
	virtual int EndMode(void){return -1;}

	virtual void PrintInputBoxStatus(void){}

	void InitAnime(void);

	char m_defaultBGFileName[32];

	LPSTR m_bgFileName;
	LPSTR m_dialogFileName;
	LPSTR m_dialogFileName2;

	int m_warningFlag;
	int m_saveNumber;


	int m_clickButtonNumber;
	BOOL m_clickingFlag;
	int m_clickingCount;
	int m_clickTime;

	int m_dialogX;
	int m_dialogY;

	int m_dialogSizeX;
	int m_dialogSizeY;


	int m_dialogX2;
	int m_dialogY2;

	int m_dialogSizeX2;
	int m_dialogSizeY2;

//	int m_yesPrintX;
//	int m_yesPrintY;

//	int m_noPrintX;
//	int m_noPrintY;

//	int m_yesnoSizeX;
//	int m_yesnoSizeY;


	void LoadBG(void);


	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	CCommonButtonGroup* m_dialogButton;
	CCommonButtonGroup* m_dialogButton2;

	int m_warningPrintFlag;
	int m_dataCustomPrintFlag;

	int m_commentInputFlag;

	int m_pageMax;
	int m_page;

	int m_blockX;
	int m_blockY;

	int m_nextX;
	int m_nextY;
	int m_printX;
	int m_printY;

	CCommonDataFile** m_ppDataFile;
	int m_dataPrintCustomFlag;

	int m_nowSelect;
	int m_maeSelect;

	CPagePrint* m_pagePrint;

	void ChangePage(int page);

	BOOL CheckDataExist(int n);
	BOOL CheckDataVersion(int n);

	BOOL m_loadCommandFlag;
	int m_warningUpDownBackPrintFlag;

	int m_quickLoadEnable;
	int m_quickSaveEnable;

	int m_quickLoadSelectOk;
	int m_quickSaveSelectOk;

	int m_quickLoadSlotNumber;
	int m_quickSaveSlotNumber;

	CDataFileSetup* m_dataFileSetup;

	int m_pageMode;

	CCommonRadioButtonGroup* m_tabButton;
	void ReLoadTabPic(void);

	CPicture* m_inputDialog;
	CMyTextInputBox* m_textInputBox;

	SIZE m_savePicSize;

	CCommonAnimeParts* m_printLastSelect;

};

#endif
/*_*/

