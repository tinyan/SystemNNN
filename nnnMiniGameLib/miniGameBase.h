//
//
//

#if !defined __NNNMINIGAME_MINIGAMEBASE__
#define __NNNMINIGAME_MINIGAMEBASE__

class CAllMiniGame;
class CPicture;

class CInputStatus;
class CMyMouseStatus;
class CMyKeyStatus;

class CMiniGameBase
{
public:
	CMiniGameBase(CAllMiniGame* lpAllMiniGame);
	virtual ~CMiniGameBase();
	virtual void End(void);

	int GeneralInit(void);
	int GeneralCalcu(void);
	int GeneralPrint(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	virtual BOOL CheckClear(void){return m_clearFlag;}
	virtual BOOL CheckGameover(void){return m_gameoverFlag;}
protected:
	CAllMiniGame* m_allMiniGame;

	CInputStatus* m_input;
	CMyKeyStatus* m_keyStatus;
	CMyMouseStatus* m_mouseStatus;

	CPicture* m_pic1;
	CPicture* m_pic2;
	CPicture* m_pic3;

	CPicture* m_commonBG;
	CPicture* m_commonParts;

	BOOL m_clearFlag;
	BOOL m_gameoverFlag;
};

#endif
/*_*/

