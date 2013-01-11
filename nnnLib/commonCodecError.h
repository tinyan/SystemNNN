//
// CodecError.h
//

#if !defined __NNNLIB_COMMONCODECERROR__
#define __NNNLIB_COMMONCODECERROR__

class CCommonGeneral;
class CGameCallBack;
class CNameList;

class CPicture;
//class CMyButtonGroup;


class CMenuButtonSetup;
class CMenuButtonGroup;

class CCommonButtonGroup;

class CCommonCodecError : public CCommonGeneral
{
public:
	CCommonCodecError(CGameCallBack* lpGame);
	virtual ~CCommonCodecError();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	static char m_defaultFileNameBG[];
	static char m_defaultFileNameDialog[];

	static char m_buttonName[][16];
protected:
	int m_dialogFlag;

	int m_dialogX;
	int m_dialogY;


	LPSTR m_filenameBG;
	LPSTR m_filenameDialog;


	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}


	CCommonButtonGroup* m_dialogButtonGroup;

protected:
	int m_codecError;

private:

};

#endif
/*_*/

