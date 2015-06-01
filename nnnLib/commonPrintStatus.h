//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONPRINTSTATUS____
#define __NNNLIB_COMMONPRINTSTATUS____

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CMyMessage;

//class CPrintGameDate;
class CCommonAnimeParts;
class CHaveItemData;


class CCommonPlayStatusData;

class CCommonPrintStatus : public CCommonGeneral
{
public:
	CCommonPrintStatus(CGameCallBack* lpGame,int extMode = 0);
	virtual ~CCommonPrintStatus();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void CreateStartScreen(void);


protected:
	int m_setNumber;
	CCommonPlayStatusData** m_playStatusData;


	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

	CMyMessage* m_message;

	int m_effectTime;
	int m_effectCount;

private:

};

#endif
/*_*/

