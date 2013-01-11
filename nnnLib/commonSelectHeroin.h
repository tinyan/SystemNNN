//
// SelectHeroin.h
//

#if !defined __NNNLIB_SELECTHEROIN__
#define __NNNLIB_SELECTHEROIN__

class CCommonGeneral;
class CGameCallBack;
class CPicture;
class CSuuji;
class CGame;
class CSuperButtonSetup;
class CCommonButton;
class CMyMessage;

class CCommonSelectHeroin : public CCommonGeneral
{
public:
	CCommonSelectHeroin(CGameCallBack* lpGame);
	virtual ~CCommonSelectHeroin();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	void CreateStartScreen(void);

	static char m_defaultBGFileName[];

//	static char m_defaultOkFileName[];
//	static char m_defaultNextFileName[];


	void StartSelectHeroin(void);

	virtual void StartUserCommand(int paraKosuu,int* paraPtr);

protected:
	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

private:
	int m_nextButtonFlag;
	int m_okButtonFlag;

	CSuperButtonSetup* m_nextButtonSetup;
	CSuperButtonSetup* m_okButtonSetup;
	CCommonButton* m_okButton;
	CCommonButton* m_nextButton;

	int m_createBufferFlag;
	int m_heroinPrintMax;


	CPicture* m_heroinPic[12];
//	CGame* m_game2;

	CPicture* m_platePic;

	int m_heroinNinzu;
	int m_heroinNumber[12];
	int m_heroinFace[12];

	int m_heroinCheckVarNumber[12];
	int m_nextCheckVarNumber;
	int m_returnVarNumber;
//	int m_nextReturnVarNumber;



//	LPSTR m_filenameBG;
	LPSTR m_filenamePlate;

	int m_page;
	int m_pageMax;

	int m_startupWait;

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	int m_superMode;
	CNameList* m_heroinList;

//	CSuperButtonSetup* m_superButtonSetup;
//	CSuperButtonSetup* m_superButtonSetupOk;
//	void CreateNextButton(void);
//	void CreateOkButton(void);

//	CCommonButton* m_nextButton;
//	int m_nextPrintX;
//	int m_nextPrintY;
//	int m_nextSizeX;
//	int m_nextSizeY;

	int m_nextButtonExistFlag;

//	CCommonButton* m_okButton;
//	int m_okPrintX;
////	int m_okPrintY;
//	int m_okSizeX;
//	int m_okSizeY;

	int m_errorFlag;

	void SetReturnHeroinData(int n);

	int GetLastSelect(void);
	void SetLastSelect(int n);

	int m_nowSelectHeroin;

	int m_minTurnNumber;
	int m_turnFrame;
	int m_turnHoukou;
	int m_turnCount;
	int m_deltaAngle;

	void InitAllButton(void);

	int m_devideTh;

	int m_buttonMode;

	int m_percent1;
	int m_percent2;

	int m_circleX;
	int m_circleY;

	CMyMessage* m_message;

	int m_platePrintX;
	int m_platePrintY;

};


#endif
/*_*/

