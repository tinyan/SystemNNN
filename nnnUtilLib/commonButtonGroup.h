//
// upcommonButtonGroup.h
//

#if !defined __NNNUTLILIB_COMMONBUTTONGROUP__
#define __NNNUTILLIB_COMMONBUTTONGROUP__

class CCommonButton;
class CNameList;
class CSuperButtonSetup;
class CInputStatus;


class CCommonButtonGroup
{
public:
	CCommonButtonGroup(CNameList* lpSetup,int buttonKosuu = 2,CPicture* lpBG = NULL,LPSTR defaultButtonName = NULL,LPSTR* customButtonName = NULL);
	virtual ~CCommonButtonGroup();
	virtual void End(void);

	void SetExist(int n, BOOL flg = TRUE);
	void SetEnable(int n, BOOL flg = TRUE);
	virtual void Init(void);

	CPicture* GetPicture(int n);
	void SetPicture(int n,CPicture* lpPic);
	LPSTR GetFileName(int n);
	void SetFileName(int n,LPSTR filename);

	POINT GetZahyo(int n);
	void SetZahyo(int n,POINT pt);

	void SetCancelButton(int n,BOOL flg = TRUE);

	virtual int Calcu(CInputStatus* lpInput);
	virtual int CalcuSuper(CInputStatus* lpInput);
	virtual void Print(BOOL mustPrintFlag = FALSE);

	CCommonButton* GetButton(int n){return m_ppButton[n];}

	void ResetAnimeCount(void);

private:
	CSuperButtonSetup** m_ppSuperSetup;
	CCommonButton** m_ppButton;


//	BOOL* m_pExistFlag;
//	BOOL* m_pEnableFlag;

	int m_status;
	int m_buttonNumber;

	int m_buttonKosuu;
	int m_superMode;
};




#endif
/*_*/

