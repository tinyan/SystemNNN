//
// menuButtonSetup
//

#if !defined __NNNUTILLIB_MENUBUTTONSETUP__
#define __NNNUTILLIB_MENUBUTTONSETUP__



class CSetupList;

class CSuperButtonSetup;
class CNameList;

class CMenuButtonSetup
{
public:
	CMenuButtonSetup(CNameList* lpNameList,int basicButtonKosuu);
	~CMenuButtonSetup();
	void End(void);


//	static char m_defaultExtModeCheckVarName[];
//	static char m_defaultExtModeReturnVarName[];

//	SIZE GetSize(void) {return m_size;}
//	POINT GetZahyo(int buttonNumber, int extMode = 0);

	BOOL CheckButtonExist(int buttonNumber, int extMode = 0);
	BOOL CheckButtonEnable(int buttonNumber, int extMode = 0);

	int GetBasicSpecialMode(int basicButtonNumber);
	int GetExtSpecialMode(int extButtonNumber);
	
	LPSTR GetExtModeCheckVarName(void){return m_extModeCheckVarName;}
	LPSTR GetExtModeReturnVarName(void){return m_extModeReturnVarName;}

	int GetExtModeKosuu(void) {return m_extModeKosuu;}
	int GetBasicButtonKosuu(void) {return m_basicButtonKosuu;}
	int GetExtButtonKosuu(void) {return m_extButtonKosuu;}

	int GetSuperMode(void){return m_superMode;}

	LPSTR GetNormalFileName(void) {return m_normalFileName;}
//	LPSTR GetSuperFileName(int n) {return m_pSuperFileName[n];}

//	int GetBackScriptFlag(void) {return m_backScriptFlag;}
	CSuperButtonSetup* GetSuperSetup(int n,int extMode = 0);

	int GetMenuAnimeAdjustFlag(void){return m_menuAnimeAdjustFlag;}

private:
//	CSuperButtonSetup* m_superButtonSetup;
	CSetupList* m_setupList;

	SIZE m_size;
	int m_nextX;
	int m_nextY;
//	int m_menuPrintX;
//	int m_menuPrintY;


	int m_basicButtonKosuu;
	int m_extButtonKosuu;
	int m_buttonKosuu;
	int m_extModeKosuu;

	LPSTR m_extModeCheckVarName;
	LPSTR m_extModeReturnVarName;

//	POINT** m_ppZahyo;
	int* m_ppExistFlag;
	int* m_ppEnableFlag;
	int* m_pExtSpecialMode;
	int* m_pBasicSpecialMode;

	int m_superMode;
	CSuperButtonSetup** m_ppSuperSetup;

	LPSTR m_normalFileName;
//	LPSTR* m_pSuperFileName;

//	int m_backScriptFlag;

	int m_menuAnimeAdjustFlag;
};







#endif
/*_*/

