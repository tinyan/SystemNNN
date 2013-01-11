//
// commonMiniGame.h
//

#if !defined __NNNLIB_COMMONMINIGAME__
#define __NNNLIB_COMMONMINIGAME__

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CInputStatus;
class CMiniGameBase;

class CCommonButton;

class CCGDataControl;
class CAllMiniGame;
class CTaihi;

class CCommonMiniGame : public CCommonGeneral
{
public:
	CCommonMiniGame(CGameCallBack* lpGame);
	virtual ~CCommonMiniGame();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);
	static char m_defaultCGFileName[];
	static char m_defaultCongraFileName[];
	static char m_defaultDescFileName[];

	BOOL AddMiniGame(int n);
	BOOL AddMiniGame(CMiniGameBase* lpMiniGame);

	CInputStatus* GetInputStatus(void);
	CPicture* GetPicture(int n);

//	void PlayClickSound(void);
//	void PlayClearSound(void);
//	void PlayMissSound(void);
//	void PlayGoodSound(void);

	void CalcuCongra(void);
	void PrintCongra(void);
	void CalcuGameover(void);
	void PrintGameover(void);

	int GetOnMiniGame(int mode);

	int GetAreaButtonMode(void){return m_areaButtonMode;}
	int GetMiniGameCheckKosuu(void){return m_miniGameCheckKosuu;}

	void InitMiniGameButton(int md);
	void PrintMiniGameButton(void);

	int CalcuMiniGameButton(void);
	CAllMiniGame* GetAllMiniGame(void){return m_allMiniGame;}

private:
	CAllMiniGame* m_allMiniGame;

	int m_allCGKosuu;
	int m_cgCharaKosuu;
	int* m_cgKosuu;
	int* m_cgTable;
	int** m_cgFlag;
	int m_getCGKosuu;
	LPSTR m_noCGFileName;
	LPSTR m_congraFileName;
	int m_miniGameNumber;

	int m_congraSizeX;
	int m_congraSizeY;

	int m_miniGameDescCount;
	int m_miniGameDescCountMax;

	int m_x;
	int m_y;
	int m_speedX;
	int m_speedY;

//	int m_gameClickSound;
//	int m_gameClearSound;
//	int m_gameMissSound;
//	int m_gameGoodSound;

	int m_miniGameCheckKosuu;
	POINT* m_miniGameCheckPoint;
	SIZE* m_miniGameCheckSize;
	int* m_miniGameCheckMode;
	int* m_miniGameCheckVar;
	int* m_miniGameSetVar;
	int* m_miniGameSetType;
	int* m_miniGameDescKosuu;
	LPSTR** m_miniGameDescFileName;
	POINT* m_miniGameExitButtonZahyo;
	int* m_miniGameSetCGSceneWork;

//	int m_userGameKosuu;
	CPicture* m_congraPic;
//	int* m_miniGameTable;
//	int m_miniGameKosuu;
//	int m_miniGameKosuuMax;
//	int m_miniGameTypeMax;
//	CMiniGameBase** m_miniGame;

	CCommonButton* m_exitButton;
	CTaihi* m_taihi;
	int m_exitButtonPrintX;
	int m_exitButtonPrintY;
	int m_exitButtonSizeX;
	int m_exitButtonSizeY;
	LPSTR m_filenameExit;
	BOOL m_clearToSetFlag;

	int m_sabunOkFlag;
	int m_soundTable[16];

	int m_allOkFlag;

	void LoadDescFile(void);

	int m_areaButtonMode;

	CCommonButtonGroup* m_buttonGroup;

	int m_miniGameButtonEnableMode;

	CCGDataControl* m_cgDataControl;
};

#endif
/*_*/

