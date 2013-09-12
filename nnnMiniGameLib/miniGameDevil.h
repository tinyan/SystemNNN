

#if !defined __NNNMINIGAME_MINIGAMEDEVIL__
#define __NNNMINIGAME_MINIGAMEDEVIL__

class CAllMiniGame;
class CMiniGameBase;

class CMiniGameDevil : public CMiniGameBase
{
public:
	CMiniGameDevil(CAllMiniGame* lpAllMiniGame,int layoutParamKosuu = 0,int* layoutParam = NULL);
	virtual ~CMiniGameDevil();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	static int m_slideOkTable[];

protected:
	void SlidePanel(int n);
	int SearchSlideOkPanel(int x,int y);

//	void Reverse(int x,int y);
//	void ReverseSub(int x,int y);
	int m_lastClickN;
	int m_lastClickY;
//	BOOL m_clearFlag;
	int m_map[4][4];

	CPicture* m_trumpPic;
	SIZE m_trumpSize;
};

#endif
/*_*/

