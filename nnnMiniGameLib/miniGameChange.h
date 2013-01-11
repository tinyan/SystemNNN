

#if !defined __NNNMINIGAME_MINIGAMECHANGE__
#define __NNNMINIGAME_MINIGAMECHANGE__

class CAllMiniGame;
class CMiniGameBase;

class CMiniGameChange : public CMiniGameBase
{
public:
	CMiniGameChange(CAllMiniGame* lpAllMiniGame);
	virtual ~CMiniGameChange();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);
protected:
	int m_catch;
//	BOOL m_clearFlag;
	int m_map[4][4];

};

#endif
/*_*/

