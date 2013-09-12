//
//
//

#if !defined __NNNMINIGAMELIB_ALLMINIGAME__
#define __NNNMINIGAMELIB_ALLMINIGAME__




class CMiniGameBase;
class CPicture;
class CInputStatus;
class CMyMouseStatus;
class CMyKeyStatus;
//class CCommonButton;

class CAllMiniGame
{
public:
	CAllMiniGame(CInputStatus* lpInput,int gameMax = 32);
	virtual ~CAllMiniGame();
	virtual void End(void);

//	void SetBackButton(CCommonButton* button){m_backButton = button;}

	BOOL AddMiniGame(int n,int layoutParamKosuu = 0,int* layoutParam = NULL);
	BOOL AddMiniGame(CMiniGameBase* lpMiniGame,int layoutParamKosuu = 0,int* layoutParam = NULL);

	void SetGameNumber(int n){m_miniGameNumber = n;}

	int Init(void);
	int Calcu(void);
	int Print(void);

	//BOOL CheckExitMiniGame(void);

	CInputStatus* GetInputStatus(void){return m_input;}
	CMyMouseStatus* GetMouseStatus(void){return m_mouseStatus;}
	CMyKeyStatus* GetKeyStatus(void){return m_keyStatus;}

	BOOL SetPicture(CPicture* lpPic,int n);
	void SetCommonBG(CPicture* lpPic){m_commonBG = lpPic;}
	void SetCommonParts(CPicture* lpPic){m_commonParts = lpPic;}

	CPicture* GetPicture(int n);
	CPicture* GetCommonBG(void){return m_commonBG;}
	CPicture* GetCommonParts(void){return m_commonParts;}

	void PlayClickSound(void);
	void PlayGoodSound(void);
	void PlayBadSound(void);
	void PlayStartSound(void);
	void PlayClearSound(void);
	void PlayGameoverSound(void);

	int GetSoundNumber(void){return m_soundNumber;}

	BOOL CheckClear(void);
	BOOL CheckGameover(void);

	void SetCommonPic(int n,CPicture* pic);
	void SetCommonPicSize(int n,SIZE sz);
	CPicture* GetCommonPic(int n);
	SIZE GetCommonPicSize(int n);
	int GetCommonPicKosuu(void);
	LPSTR GetCommonPicName(int n);

	int GetSoundKosuu(void){return m_soundKosuu;}
	LPSTR GetSoundName(int n);
	static char m_commonPicName[][64];
	static int m_defaultCommonPicSize[];
	static char m_soundNameTable[][64];

	void SetPicType(int n,int type){m_picType[n] = type;}
	int GetPicType(int n){return m_picType[n];}
private:
	int m_miniGameKosuuMax;
	int m_miniGameKosuu;
	CMiniGameBase** m_miniGame;
	int* m_miniGameSetTable;
	int m_miniGameNumber;
	CInputStatus* m_input;
	CMyKeyStatus* m_keyStatus;
	CMyMouseStatus* m_mouseStatus;

	CPicture* m_pic[3];
	int m_soundNumber;

	CPicture* m_commonBG;
	CPicture* m_commonParts;

	int m_commonPicKosuu;

	CPicture* m_commonPic[16];
	SIZE m_commonPicSize[16];
	int m_soundKosuu;
	int m_picType[16];

//	CCommonButton* m_backButton;
};




#endif
/*_*/
