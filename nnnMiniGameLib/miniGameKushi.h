

#if !defined __NNNMINIGAME_MINIGAMEKUSHI__
#define __NNNMINIGAME_MINIGAMEKUSHI__

class CAllMiniGame;
class CMiniGameBase;
class CMiniGamemahjongCommon;

class CMiniGameKushi : public CMiniGameMahjongCommon
{
public:
	CMiniGameKushi(CAllMiniGame* lpAllMiniGame);
	virtual ~CMiniGameKushi();
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
	int* m_yattana;
	int* m_erasedPai;


	int m_printX;
	int m_printY;

	int GetOnBlockNumber(POINT pt);
	POINT GetKushiZahyo(int x,int y);

	int m_kushiMode;

	int m_startWaitCount;

	int CalcuStart(void);
	int CalcuNormal(void);
//	int CalcuGetting(void);
	int CalcuErase(void);
	int CalcuDrop(void);
	int CalcuLeft(void);
	int CalcuHint(void);
	int CalcuYattana(void);

	int PrintStart(void);
	int PrintNormal(void);
//	int PrintGetting(void);
	int PrintErase(void);
	int PrintDrop(void);
	int PrintLeft(void);
	int PrintHint(void);
	int PrintYattana(void);

	int m_nowSelect;
	int m_maeSelect;

	void GetRoutine(int first,int second);
	BOOL CheckGetOk(int first,int second);
	BOOL CheckGetExist(void);
	BOOL CheckAllGet(void);

	int m_firstSelect;
	int m_secondSelect;
//	int m_fromX;
//	int m_fromY;
//	int m_toX;
//	int m_toY;

//	int m_curveKosuu;
//	int m_curveX1;
//	int m_curveY1;
//	int m_curveX2;
//	int m_curveY2;

	//int m_gettingCount;
	//int m_gettingCountMax;
	//int m_gettingMode;

	int GetKushiPai(int n);
	int m_eraseCount;
	int m_eraseCountMax;

	int m_hintCount;
	int m_hintCountMax;
//	int m_haveHint;

	//BOOL CheckLine(int x1,int y1,int x2,int y2,BOOL lastCheckFlag = FALSE);
	//void PrintBar(int x1,int y1,int x2,int y2,int sz,int r,int g,int b);

	void MakeHint(void);

	int m_erasedKosuu;

	BOOL CheckBottomSukima(void);
	BOOL CheckYattanaAru(void);

	int m_yattanaSpeed;
	int m_yattanaKosuu;
	void SetNewYattana(void);

};


#endif
/*_*/

