

#if !defined __NNNMINIGAME_MINIGAMENURIE__
#define __NNNMINIGAME_MINIGAMENURIE__

class CAllMiniGame;
class CMiniGameBase;

class CMiniGameNurie : public CMiniGameBase
{
public:
	CMiniGameNurie(CAllMiniGame* lpAllMiniGame);
	virtual ~CMiniGameNurie();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);
protected:
	BOOL m_updateFlag;
	int m_updateAreaX;
	int m_updateAreaY;
	int m_updateAreaSizeX;
	int m_updateAreaSizeY;

	int m_sizeX;
	int m_sizeY;

	int m_oldX;
	int m_oldY;

	char* m_mask;
	BOOL m_bgCreateFlag;
};

#endif
