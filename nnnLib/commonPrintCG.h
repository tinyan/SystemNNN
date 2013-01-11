//
// PrintCG.h
//

#if !defined __NNNLIB_COMMONPRINTCG__
#define __NNNLIB_COMMONPRINTCG__

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CCGDataControl;
class CCGVoice;

class CCommonPrintCG : public CCommonGeneral
{
public:
	CCommonPrintCG(CGameCallBack* lpGame);
	virtual ~CCommonPrintCG();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);


	static char m_defaultTaBGFileName[];
protected:
	void LoadCG(void);

	RECT m_picRect;

	int m_scrollFlagX;
	int m_scrollCountX;
	int m_scrollFlagY;
	int m_scrollCountY;

	int m_scrollHoukouX;
	int m_scrollHoukouY;
	int m_scrollFirstWaitBaseX;
	int m_scrollFirstWaitBaseY;
	int m_scrollTimeBaseX;
	int m_scrollTimeBaseY;

	int m_scrollFirstWaitX;
	int m_scrollFirstWaitY;
	int m_scrollTimeX;
	int m_scrollTimeY;

	int m_scrollHoukouXSpecial;
	int m_scrollHoukouYSpecial;

	virtual void CreateEnterScreen(void);


	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

	int m_nextSound;
	int m_prevSound;
	int m_backSound;

	int m_maisuuX;
	int m_maisuuY;

	BOOL m_taFlag[16];

	void CheckAndEraseBG(void);

	int m_taBGFlag;
	int m_taBGColorR;
	int m_taBGColorG;
	int m_taBGColorB;
	LPSTR m_taBGFileName;
	LPSTR* m_taBGCharaFileName;

	BOOL m_dragedFlag;
	BOOL m_dragFlag;
	int m_dragStartX;
	int m_dragStartY;

	int m_dragedX;
	int m_dragedY;

	CCGDataControl* m_cgDataControl;
	CCGVoice* m_cgVoice;
	void ClearLastCGVoice(void);
	void ChangeCGVoice(void);
	void CheckAndPlayCGVoice(void);
	BOOL m_cgVoicePlayedFlag;
	int m_cgVoiceWaitTime;
	int m_cgVoiceCount;
	char* m_cgVoiceFileName;

private:
};

#endif
/*_*/

