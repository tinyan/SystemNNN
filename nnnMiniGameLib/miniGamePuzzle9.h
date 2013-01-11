

#if !defined __NNNMINIGAME_MINIGAMEPUZZLE9__
#define __NNNMINIGAME_MINIGAMEPUZZLE9__

class CAllMiniGame;
class CMiniGameBase;

class CMiniGamePuzzle9 : public CMiniGameBase
{
public:
	CMiniGamePuzzle9(CAllMiniGame* lpAllMiniGame);
	virtual ~CMiniGamePuzzle9();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	typedef struct _tagPANEL
	{
		BOOL flag;
		int answer;
		int pic;
		int srcX;
		int srcY;
		int x;
		int y;
		int speedX;
		int speedY;
	} PANEL;

	PANEL m_panel[18];

protected:
	int m_catch;
//	BOOL m_clearFlag;
	int m_answer[3][3];

	void SetPanelStartBad(int n);
	void SetStartPanelZahyo(int n);

	int SearchMovingPanel(POINT pt);
	int GetAreaNumber(POINT pt);
	BOOL CheckAllSet(void);
	void ReleasePanel(void);

};

#endif
/*_*/

