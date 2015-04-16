//
// SelectPlace.h
//

#if !defined __NNNLIB_COMMONPRINTACHIEVEMENT__
#define __NNNLIB_COMMONPRINTACHIEVEMENT__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

//class CPrintGameDate;

class CMyMessage;

class CCommonButtonGroup;
//class CSelectObjectSetup;

class CCommonPrintAchievement : public CCommonGeneral
{
public:
	CCommonPrintAchievement(CGameCallBack* lpGame,int extMode = 0);
	virtual ~CCommonPrintAchievement();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);



	void AchievementChanged(int n,int ps);
protected:
	virtual void FinalExitRoutine(void);
	virtual int EndMode(void);

	int m_achievementNumber;

	typedef struct _tagACHIEVEMENT
	{
		int type;
		int paramNumber;
		int pad2,pad3;
		int param[16];
	}ACHIEVEMENT;


	ACHIEVEMENT* m_achievementTable;
	int* m_achievementResult;

	static char m_typeName[][32];


	void CheckAllResult(BOOL noticePrint = TRUE);

	CMyMessage* m_message;

private:

};

#endif
/*_*/

