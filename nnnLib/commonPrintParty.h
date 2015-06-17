//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONPRINTPARTY____
#define __NNNLIB_COMMONPRINTPARTY____

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CMyMessage;

//class CPrintGameDate;
class CCommonAnimeParts;
class CHaveItemData;


class CCommonPartyStatusData;

class CCommonPrintParty : public CCommonGeneral
{
public:
	CCommonPrintParty(CGameCallBack* lpGame,int extMode = 0);
	virtual ~CCommonPrintParty();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void CreateStartScreen(void);


protected:
	int m_setNumber;
	CCommonPartyStatusData* m_partyStatusData;
	int m_partyNumber;
	int m_printNumberMax;
	int m_statusNumber;
	int m_etcNumber;


	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

	CMyMessage* m_message;

	int m_effectTime;
	int m_effectCount;

private:

};

#endif
/*_*/

