

#if !defined __NNNMINIGAME_MINIGAMECROSS__
#define __NNNMINIGAME_MINIGAMECROSS__

class CAllMiniGame;
class CMiniGameBase;

class CMiniGameCross : public CMiniGameBase
{
public:
	CMiniGameCross(CAllMiniGame* lpAllMiniGame);
	virtual ~CMiniGameCross();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);
protected:
	void Reverse(int x,int y);
	void ReverseSub(int x,int y);
	int m_lastClickX;
	int m_lastClickY;
//	BOOL m_clearFlag;
	int m_map[8][8];

};

#endif
/*_*/

