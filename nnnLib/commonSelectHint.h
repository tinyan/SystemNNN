#pragma once

#if !defined __NNNLIB_COMMONSELECTHINT____
#define __NNNLIB_COMMONSELECTHINT__

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CMyMessage;

class CCommonButtonGroup;

class CCommonSelectHint : public CCommonGeneral
{
public:
	CCommonSelectHint(CGameCallBack* lpGame, int extMode = 0);
	virtual ~CCommonSelectHint();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void CreateStartScreen(void);


	CMyMessage* m_message;

protected:
	int m_groupNumber;
	CCommonButtonGroup* m_selectButtonGroup;
	int* m_groupFlagVar;

};

#endif


/*_*/
