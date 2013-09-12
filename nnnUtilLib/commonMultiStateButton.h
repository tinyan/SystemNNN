//
//
//

#if !defined __NNNUTILLIB_COMMONMULTISTATEBUTTON__
#define __NNNUTILLIB_COMMONMULTISTATEBUTTON__


class CNameList;
class CCommonButton;
class CSUperButtonSetup;
class CInputStatus;
class CPicture;

class CCommonMultiStateButton
{
public:

	CCommonMultiStateButton(CNameList* lpSetup,CPicture* lpBG,LPSTR buttonName = NULL,int n = 2,POINT* lpPoint = NULL,CSuperButtonSetup* lpCopySetup = NULL,BOOL notSrcPicCopy = FALSE);
	virtual ~CCommonMultiStateButton();
	virtual void End(void);

	void Init(void);
	int Calcu(CInputStatus* lpInput);
	void Print(BOOL flg = TRUE);

//	void SetButton(int n,CCommonButton* button);
	void SetState(int n);
	int GetState(void);

	CPicture* GetPicture(int n = 0);
	void SetPicture(CPicture* lpPic,int n = -1);
	LPSTR GetFileName(int n);

	SIZE GetSize(int n = 0);
	void SetZahyo(POINT pt,int n = -1);

	static char m_defaultButtonName[];

	CSuperButtonSetup* GetSuperButtonSetup(int n){return m_superSetup[n];}

	void SetAllEnable(BOOL flg = TRUE);
	void SetAllExist(BOOL flg = TRUE);
	BOOL GetAllEnable(void);
	BOOL GetAllExist(void);

	void ResetAnimeCount(void);

	CCommonButton* GetButton(int n){return m_button[n];}
protected:
	CCommonButton** m_button;
	CSuperButtonSetup** m_superSetup;
	CNameList* m_setup;
	int m_buttonKosuu;
	int m_state;

	BOOL* m_existFlag;
	BOOL* m_enableFlag;

	BOOL m_allExistFlag;
	BOOL m_allEnableFlag;

};

#endif
/*_*/

