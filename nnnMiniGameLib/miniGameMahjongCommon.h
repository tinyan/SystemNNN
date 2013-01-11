#if !defined __NNNMINIGAME_MINIGAMEMAHJONGCOMMON__
#define __NNNMINIGAME_MINIGAMEMAHJONGCOMMON__

class CAllMiniGame;
class CMiniGameBase;

class CMiniGameMahjongCommon : public CMiniGameBase
{
public:
	CMiniGameMahjongCommon(CAllMiniGame* lpAllMiniGame);
	virtual ~CMiniGameMahjongCommon();
	virtual void End(void);

	virtual int Init(void) = 0;
	virtual int Calcu(void) = 0;
	virtual int Print(void) = 0;

	virtual BOOL CheckClear(void){return m_clearFlag;}
	virtual BOOL CheckGameover(void){return m_gameoverFlag;}

protected:
	void ErasePai(int x,int y);
	void PutPai(int x,int y,int pai,int trans = 100,BOOL sel = FALSE,BOOL chk = FALSE);

	POINT* m_paiSrcZahyo;
	int m_paiSrcInitFlag;

	CPicture* m_paiPic;
	SIZE m_paiSize;
	POINT GetPaiPic(int n);

	void InitPaiSrcZahyo(void);

	int m_haveHint;

	void PrintHaveHint(void);
	int m_hintPrintX;
	int m_hintPrintY;
	BOOL CheckOnHint(POINT pt);
};

#endif
/*_*/

