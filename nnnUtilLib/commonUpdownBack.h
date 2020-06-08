//
//
//

#if !defined __NNNUTILLIB_COMMONUPDOWNBACK
#define __NNNUTILLIB_COMMONUPDOWNBACK

class CInputStatus;
class CCommonButton;
class CCommonBackButton;
class CCommonUpDownButtonGroup;

class CCommonUpdownBack
{
public:
	CCommonUpdownBack(CCommonBackButton* lpBack,CCommonUpDownButtonGroup* lpUpDown);
	virtual ~CCommonUpdownBack();
	virtual void End(void);

	void Init(void);
	int Calcu(CInputStatus* lpInput);
	void Print(BOOL flg);
	void AppearPrint(int count, int countMax, int type = 1, POINT deltaPoint = POINT{ 0,0 });

	virtual void SetPageMax(int pageMax);
	virtual int GetPageMax(void);
	virtual void SetPage(int page);
	virtual int GetPage(void);

	void ResetAnimeCount(void);

protected:
	CCommonBackButton * m_back;
	CCommonUpDownButtonGroup* m_updown;
	int m_clickingNumber;

};


#endif
/*_*/

