//
// printDebugParam.h
//

#if !defined __NNNLIB_PRINTDEBUGPARAM__
#define __NNNLIB_PRINTDEBUGPARAM__

class CGameCallBack;
class CNameList;

class CPrintDebugParam
{
public:
	CPrintDebugParam(CGameCallBack* lpGame);
	virtual ~CPrintDebugParam();
	virtual void End(void);

	void Print(int n = -1);
	void PrintDebugBack(void);
	void SetVistaPatch(BOOL flg = TRUE){m_vistaPatch = flg;}

	int GetDebugVarStart(void){return m_debugVarStart;}
	void SetDebugVarStart(int d){m_debugVarStart = d;}
	void AddDebugVarNumber(int d,BOOL loopFlag = FALSE);
	void AddDebugVarPage(int page);
	void SetDebugVarPage(int page){m_page = page;}
	void SetDebugBackPrintMode(int md){m_debugBackPrintMode = md;}
	void ChangeDebugBackPrintMode(void);
	void SetDebugBackPrintColor(int r,int g,int b){m_backR = r;m_backG = g;m_backB = b;}
	void SetDebugBackTransPercent(int ps){m_backPercent = ps;}

protected:
	CGameCallBack* m_game;
	CNameList* m_varList;

	int m_debugVarStart;
	int m_page;

	int m_debugBackPrintMode;
	int m_backR;
	int m_backG;
	int m_backB;
	int m_backPercent;

	BOOL m_vistaPatch;
private:
};







#endif
/*_*/

