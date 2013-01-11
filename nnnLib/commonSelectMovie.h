//
// nothing.h
//

#if !defined __NNNLIB_SELECTMOVIE__
#define __NNNLIB_SELECTMOVIE__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CCommonSelectMovie : public CCommonGeneral
{
public:
	CCommonSelectMovie(CGameCallBack* lpGame);
	virtual ~CCommonSelectMovie();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);
protected:
};

#endif
/*_*/

