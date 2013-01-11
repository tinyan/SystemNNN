//
//
//

#if !defined __NNNUTILLIB_COMMONRADIOBUTTONGROUP__
#define __NNNUTILLIB_COMMONRADIOBUTTONGROUP__



class CCommonRadioButton;
class CSuperButtonSetup;
class CPicture;
class CInputStatus;

class CCommonRadioButtonGroup
{
public:
	CCommonRadioButtonGroup(CNameList* lpSetup,LPSTR buttonName,CPicture* lpBG = NULL,int buttonKosuu = 2,CSuperButtonSetup* lpCopySetup = NULL);
	virtual ~CCommonRadioButtonGroup();
	virtual void End(void);

	CSuperButtonSetup* GetSuperSetup(int n = -1,int k = -1);

	CPicture* GetPicture(int n,int k = 0);
	void SetPicture(CPicture* lpPic,int n = -1,int k = -1);
	LPSTR GetFileName(int n,int k = -1);

	void Init(int radio = 0);
	int Calcu(CInputStatus* lpInput);
	void Print(BOOL flg = TRUE);

	void SetEnable(int n,BOOL flg = TRUE);
	void SetExist(int n,BOOL flg = TRUE);
	BOOL CheckEnable(int n);
	BOOL CheckExist(int n);

	void SetAllEnable(BOOL flg = TRUE);
	void SetAllExist(BOOL flg = TRUE);

	int GetRadio(void);
	void SetRadio(int radio);

	int GetButtonKosuu(void){return m_buttonKosuu;}

	void ResetAnimeCount(void);

	CCommonRadioButton* GetRadioButton(int n){return m_ppButton[n];}
protected:
	CNameList* m_setup;
	int m_buttonKosuu;
	int m_radio;

	int m_clickingNumber;
	CCommonRadioButton** m_ppButton;
};





#endif
/*_*/

