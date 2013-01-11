#if !defined __NNNMINIGAME_MINIGAMETRUMPCOMMON__
#define __NNNMINIGAME_MINIGAMETRUMPCOMMON__

class CAllMiniGame;
class CMiniGameBase;

class CMiniGameTrumpCommon : public CMiniGameBase
{
public:
	CMiniGameTrumpCommon(CAllMiniGame* lpAllMiniGame);
	virtual ~CMiniGameTrumpCommon();
	virtual void End(void);

	virtual int Init(void) = 0;
	virtual int Calcu(void) = 0;
	virtual int Print(void) = 0;

	virtual BOOL CheckClear(void){return m_clearFlag;}
	virtual BOOL CheckGameover(void){return m_gameoverFlag;}

protected:
	void EraseCard(int x,int y);
	void PutCard(int x,int y,int card,int trans = 100,BOOL sel = FALSE,BOOL chk = FALSE);

	CPicture* m_trumpPic;
	SIZE m_trumpSize;
	int m_cardPicType;
	POINT GetCardPic(int n);
};

#endif
/*_*/

