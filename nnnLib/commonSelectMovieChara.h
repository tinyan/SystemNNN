//
// nothing.h
//

#if !defined __NNNLIB_SELECTMOVIECHARA__
#define __NNNLIB_SELECTMOVIECHARA__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CCommonSelectMovieChara : public CCommonGeneral
{
public:
	CCommonSelectMovieChara(CGameCallBack* lpGame);
	virtual ~CCommonSelectMovieChara();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);
protected:
};

#endif
/*_*/

