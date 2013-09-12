

#if !defined __NNNMINIGAME_MINIGAMENIKAKU__
#define __NNNMINIGAME_MINIGAMENIKAKU__

class CAllMiniGame;
class CMiniGameBase;
class CMiniGamemahjongCommon;

class CMiniGameNikaku : public CMiniGameMahjongCommon
{
public:
	CMiniGameNikaku(CAllMiniGame* lpAllMiniGame,int layoutParamKosuu = 0,int* layoutParam = NULL);
	virtual ~CMiniGameNikaku();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

//	static int m_slideOkTable[];

protected:
	int* m_map;

	int* m_downMax;
	int* m_downed;
	int m_downSpeed;
	int* m_mapTmp;

	int m_printX;
	int m_printY;

	int GetOnBlockNumber(POINT pt);
	POINT GetNikakuZahyo(int x,int y);

	int m_nikakuMode;

	int m_startWaitCount;

	int CalcuStart(void);
	int CalcuNormal(void);
	int CalcuGetting(void);
	int CalcuErase(void);
	int CalcuDrop(void);
	int CalcuHint(void);

	int PrintStart(void);
	int PrintNormal(void);
	int PrintGetting(void);
	int PrintErase(void);
	int PrintDrop(void);
	int PrintHint(void);

	int m_nowSelect;
	int m_maeSelect;

	void GetRoutine(int first,int second);
	BOOL CheckGetOk(int first,int second);
	BOOL CheckGetExist(void);
	BOOL CheckAllGet(void);

	int m_firstSelect;
	int m_secondSelect;
	int m_fromX;
	int m_fromY;
	int m_toX;
	int m_toY;

	int m_curveKosuu;
	int m_curveX1;
	int m_curveY1;
	int m_curveX2;
	int m_curveY2;

	int m_gettingCount;
	int m_gettingCountMax;
	int m_gettingMode;

	int GetNikakuPai(int n);
	int m_eraseCount;
	int m_eraseCountMax;

	int m_hintCount;
	int m_hintCountMax;
//	int m_haveHint;

	BOOL CheckLine(int x1,int y1,int x2,int y2,BOOL lastCheckFlag = FALSE);
	void PrintBar(int x1,int y1,int x2,int y2,int sz,int r,int g,int b);

	void MakeHint(void);

};


#endif
/*_*/

