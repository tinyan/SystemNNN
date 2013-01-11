#if !defined __NNNUTILLIB_COMMONOKCANCEL
#define __NNNUTILLIB_COMMONOKCANCEL

class CInputStatus;
class CCommonButton;
class CCommonBackButton;

class CCommonButton;

class CCommonOkCancel
{
public:
	CCommonOkCancel(CCommonButton* okButton,CCommonBackButton* lpBack);
	virtual ~CCommonOkCancel();
	virtual void End(void);

	void Init(void);
	int Calcu(CInputStatus* lpInput);
	void Print(BOOL flg);

//	virtual void SetPageMax(int pageMax);
//	virtual int GetPageMax(void);
//	virtual void SetPage(int page);
//	virtual int GetPage(void);

	void ResetAnimeCount(void);

protected:
	CCommonBackButton * m_back;
	CCommonButton* m_ok;
	int m_clickingNumber;
};



#endif
/*_*/

