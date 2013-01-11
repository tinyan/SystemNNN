//
// nothing.h
//

#if !defined __NNNLIB_NOTHING__
#define __NNNLIB_NOTHING__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CCommonNothing : public CCommonGeneral
{
public:
	CCommonNothing(CGameCallBack* lpGame);
	virtual ~CCommonNothing();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);
protected:
	int m_fillColorR;
	int m_fillColorG;
	int m_fillColorB;

//	int m_nextMode;
	int m_cdCheckFlag;
	int m_codecCheckFlag;
	int m_codecChecked;

	int m_codecLimit;
	int m_startupJumpScriptFlag;
};

#endif
/*_*/

