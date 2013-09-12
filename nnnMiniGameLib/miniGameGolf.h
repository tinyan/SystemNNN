

#if !defined __NNNMINIGAME_MINIGAMEGOLF__
#define __NNNMINIGAME_MINIGAMEGOLF__

class CAllMiniGame;
class CMiniGameBase;

class CMiniGameGolf : public CMiniGameBase
{
public:
	CMiniGameGolf(CAllMiniGame* lpAllMiniGame,int layoutParamKosuu = 0,int* layoutParam = NULL);
	virtual ~CMiniGameGolf();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	static int m_checkTable[];

protected:
	POINT GetCardZahyo(int n);

	int m_yamaMaisuu;
	int m_yama[54];

	int m_daifuda;

	int m_ba[7][5];
	int m_baMaisuu[7];

	int m_subMode;
	int m_nowSelect;
	int m_maeSelect;

	void Shuffle(void);

	void CalcuStartNaraberu(void);
	void CalcuKieru(void);
	void CalcuMekuru(void);
//	void CalcuModosu(void);

	void PrintNormal();

	void PrintStartNaraberu(void);
	void PrintKieru(void);
	void PrintMekuru(void);
//	void PrintModosu(void);
	
	void StartNormal(void);
	void StartNaraberu(void);
	void StartKieru(int place);
	void StartMekuru(void);
//	void StartModosu(void);

	int m_kieru;
//	int m_kieru2;

	int m_mekuruCard;

	void CheckAllGet(void);
	void CheckCannot(void);

	void PutCard(POINT pt,int card,int trans = 100,BOOL sel = FALSE);
	void PutCard(int x,int y,int card,int trans = 100,BOOL sel = FALSE);

	void PrintYama(BOOL selFlag = FALSE,int ps = 100);
	void PrintDai(BOOL selFlag = FALSE,BOOL chkFlag = FALSE,int ps = 100);

	int m_startNaraberuCount;
	int m_startNaraberuCountMax;

	int m_kieruCount;
	int m_kieruCountMax;

	int m_mekuruCount;
	int m_mekuruCountMax;

//	int m_modosuCount;
//	int m_modosuCountMax;

	BOOL CheckClickOk(int n);


	CPicture* m_trumpPic;
	SIZE m_trumpSize;

	BOOL CheckSkip(void);

	int GetOnCard(POINT pt);
	int GetCard(int n);
	BOOL CheckOnCard(POINT pt,POINT pt2);

	POINT m_cardZahyo[37];
	int m_reShuffleCount;

	POINT GetCardPic(int n);
	int m_cardPicType;

};

#endif
/*_*/

