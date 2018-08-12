//
// upDownButtonGroup.h
//

#if !defined __NNNUTLILIB_COMMONUPDOWNBUTTONGROUP__
#define __NNNUTILLIB_COMMONUPDOWNBUTTONGROUP__

class CCommonButton;
class CNameList;
class CSuperButtonSetup;
class CInputStatus;

//#include "myMouseStatus.h"

class CCommonUpDownButtonGroup
{
public:
	CCommonUpDownButtonGroup(CNameList* lpSetup,CPicture* lpBG = NULL);
	CCommonUpDownButtonGroup(LPSTR upName,LPSTR downName,CNameList* lpSetup, CPicture* lpBG = NULL);
	~CCommonUpDownButtonGroup();
	void End(void);
	void Create(LPSTR upName, LPSTR downName, CNameList* lpSetup, CPicture* lpBG);
	void SetExist(int n, BOOL flg = TRUE){m_existFlag[n] = flg;}
	void SetEnable(int n, BOOL flg = TRUE){m_enableFlag[n] = flg;}
	void Init(void);

	CPicture* GetPicture(int n);
	void SetPicture(int n,CPicture* lpPic);
	LPSTR GetFileName(int n);

	int Calcu(CInputStatus* lpInput);
	int CalcuSuper(CInputStatus* lpInput);
	void Print(BOOL mustPrintFlag = FALSE);

	void SetPage(int page);
	void SetPageMax(int pageMax);
	int GetPage(void);
	int GetPageMax(void){return m_pageMax;}
	void AdjustPage(void);


	void SetBG(CPicture* lpBG = NULL,int n = -1);

	void SetUpDownZahyo(int upPrintX,int upPrintY, int downPrintX,int downPrintY);
	void ResetAnimeCount(void);

	POINT GetUpZahyo(void);
	POINT GetDownZahyo(void);

private:
	CSuperButtonSetup* m_updownSetup[2];
	CCommonButton* m_button[2];

	BOOL m_existFlag[2];
	BOOL m_enableFlag[2];

	int m_status;
	int m_buttonNumber;

	int m_page;
	int m_pageMax;

	int m_buttonKosuu;
	int m_superMode;

	BOOL m_appearFlag[2];
	void CalcuAppear(void);

	void ChangePage(int buttonNumber);
};




#endif
/*_*/

