//
// PrintCalendar.h
//

#if !defined __NNNLIB_COMMONPRINTCALENDAR__
#define __NNNLIB_COMMONPRINTCALENDAR__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CCommonPrintCalendar : public CCommonGeneral
{
public:
	CCommonPrintCalendar(CGameCallBack* lpGame);
	virtual ~CCommonPrintCalendar();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void Start(int dayMonth, int nokori = -1) {m_dayMonth = dayMonth; m_nokori = nokori;}

	static int m_modeLength[5];
protected:
	int m_dayMonth;
	int m_nokori;

	int m_mode;
	int m_count;
	int m_countMax;

	void PutNokori(BOOL high,int ps = 100);
	void PrintNokori(void);


	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

};

#endif
/*_*/

