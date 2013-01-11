//
// menuybuttongroup.h
//

#if !defined __NNNUTILLIB_MENUBUTTONGROUP__
#define __NNNUTILLIB_MENUBUTTONGROUP__

class CCommonButton;
class CMenuButtonSetup;
//class CMyMouseStatus;

//class CGameCallBack;

//#include "myMouseStatus.h"
class CInputStatus;

class CMenuButtonGroup
{
public:
	CMenuButtonGroup(CMenuButtonSetup* lpMenuButtonSetup,CPicture* lpBG = NULL);
	~CMenuButtonGroup();
	void End(void);



	void SetExtMode(int extMode);
	LPSTR GetExtModeCheckVarName(void);
	LPSTR GetExtReturnVarName(void);

	void SetCancelButton(int n,BOOL flg = TRUE);
	void SetExist(int n, BOOL flg = TRUE,int extMode = -1);
	void SetEnable(int n, BOOL flg = TRUE,int extMode = -1);
	void Init(void);



	CPicture* GetPicture(int n,int extMode = 0);
	void SetPicture(int n,CPicture* lpPic,int extMode = -1);
	LPSTR GetFileName(int n,int extMode = 0);


//	void InitButtonOnly(void);
	int Calcu(CInputStatus* lpInput,int clickFlag = 0);
	int CalcuSuper(CInputStatus* lpInput,int clickFlag = 0);
	void Print(BOOL mustPrintFlag = FALSE);
	void AppearPrint(int count,int countMax,int type,POINT deltaPoint);

	void SpecialPrint(int count,int countMax,int type);


//	void SetAllButtonZahyo(int extMode = 0);

	int GetNowExtMode(void){return m_extMode;}
	int GetSuperMode(void){return m_superMode;}


	int GetExtModeReturnVarNumber(void){return m_extModeReturnVarNumber;}

	CCommonButton* GetButton(int n,int ext = 0){return m_ppButton[n+ext*m_buttonKosuu];}


private:
	CMenuButtonSetup* m_menuButtonSetup;
	CCommonButton** m_ppButton;

	int m_basicButtonKosuu;
	int m_extButtonKosuu;


	BOOL* m_pExistFlag;
	BOOL* m_pEnableFlag;




//	CGameCallBack* m_game;


	int m_buttonKosuu;
//	int m_cancelButtonNumber;

	int m_status;
	int m_buttonNumber;

	int m_extModeKosuu;
	int m_extModeCheckVarNumber;
	int m_extModeReturnVarNumber;

	int m_superMode;
	int m_extMode;

//	void PutSpecialSub0(CCommonButton* button,int n,int ps100);
//	void PutSpecialSub1(CCommonButton* button,int n,int ps100);
//	void PutSpecialSub2(CCommonButton* button,int n,int ps100);
//	void PutSpecialSub3(CCommonButton* button,int n,int ps100);
//	void PutSpecialSub4(CCommonButton* button,int n,int ps100);
//	void PutSpecialSub5(CCommonButton* button,int n,int ps100);
};




#endif
/*_*/

