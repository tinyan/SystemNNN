//
// Save.h
//

#if !defined __TINYAN_NNNLIB_COMMONLOAD__
#define __TINYAN_NNNLIB_COMMONLOAD__

class CCommonGeneral;
class CCommonLoadSave;
class CGameCallBack;

class CCommonButtonGroup;
class CCommonDataFile;

class CCommonLoad : public CCommonLoadSave
{
public:
	CCommonLoad(CGameCallBack* lpGame);
	virtual ~CCommonLoad();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

//	static char m_defaultBGFileName[];
//	static char m_buttonName[][16];
	//static char m_defaultSuujiFileName[];

	virtual void CreateStartScreen(void);
	virtual BOOL QuickLoad(void);

	virtual BOOL CheckQuickLoadDataExist(void);
	bool CheckExistSaveData(void);


protected:
	virtual int ProcessDataClicked(int n);
	virtual int ProcessStartClickExistData(int n);
	virtual int ProcessStartClickNotExistData(int n);

	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

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

	CCommonButtonGroup* m_dialogButton;


	int m_loadSound;
	int m_cannotLoadSound;

	int m_loadVoiceKosuu;
	int m_cannotLoadVoiceKosuu;
	LPSTR* m_loadVoice;
	LPSTR* m_cannotLoadVoice;

	BOOL m_lastPrintFlag;



};

#endif
/*_*/

