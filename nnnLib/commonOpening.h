//
// opening.h
//

#if !defined __NNNLIB_COMMONOPENING__
#define __NNNLIB_COMMONOPENING__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CCommonOpening : public CCommonGeneral
{
public:
	CCommonOpening(CGameCallBack* lpGame);
	virtual ~CCommonOpening();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

//	static char m_defaultOpeningVar[];

private:
//	int m_fillColorR;
//	int m_fillColorG;
//	int m_fillColorB;

//	LPSTR m_openingVarName;
//	int m_openingVarNumber;

//	int m_nextMode;
//	CNameList* m_setup;
};

#endif
/*_*/

