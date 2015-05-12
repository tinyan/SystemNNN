//
// nothing.h
//

#if !defined __NNNLIB_KANJIINPUT__
#define __NNNLIB_KANJIINPUT__

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CMyMessage;
class CSoftKey;

class CCommonKanjiInput : public CCommonGeneral
{
public:
	CCommonKanjiInput(CGameCallBack* lpGame);
	virtual ~CCommonKanjiInput();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);
	virtual void StartUserCommand(int paraKosuu,int* paraPtr);

	virtual void FinalExitRoutine(void);

protected:
	CMyMessage* m_message;
	CSoftKey* m_softKey;

	int m_targetNumber;
	int m_targetType;


};

#endif
/*_*/

