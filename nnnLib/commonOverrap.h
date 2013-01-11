//
// Overrap.h
//

#if !defined __NNNLIB_COMMONOVERRAP__
#define __NNNLIB_COMMONOVERRAP__

class CCommonGeneral;
class CGameCallBack;
class CPicture;

class CCommonOverrap : public CCommonGeneral
{
public:
	CCommonOverrap(CGameCallBack* lpGame);
	virtual ~CCommonOverrap();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual void ResetShakin(void);
	virtual int GetShakin(void);
protected:

	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void){}
	virtual void AfterCalcu(void){}
	virtual void BeforePrint(void){}
	virtual void AfterPrint(void){}

private:
	CPicture* m_pic1;
	CPicture* m_pic2;
	int m_type;
	int m_length;
	int m_count;

	int m_shakin;

	int m_optionButtonPrintFlag;
	int m_sceneButtonPrintFlag;
};

#endif
/*_*/

