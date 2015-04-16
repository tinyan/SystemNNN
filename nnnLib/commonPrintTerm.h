//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONPRINTTERM____
#define __NNNLIB_COMMONPRINTTERM__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

//class CPrintGameDate;


class CCommonPrintTerm : public CCommonGeneral
{
public:
	CCommonPrintTerm(CGameCallBack* lpGame,int extMode = 0);
	virtual ~CCommonPrintTerm();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void CreateStartScreen(void);
protected:
	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);





private:

};

#endif
/*_*/

