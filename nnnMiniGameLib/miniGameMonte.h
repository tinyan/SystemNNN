

#if !defined __NNNMINIGAME_MINIGAMEMONTE__
#define __NNNMINIGAME_MINIGAMEMONTE__

class CAllMiniGame;
class CMiniGameBase;

class CMiniGameMonte : public CMiniGameBase
{
public:
	CMiniGameMonte(CAllMiniGame* lpAllMiniGame,int layoutParamKosuu = 0,int* layoutParam = NULL);
	virtual ~CMiniGameMonte();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

protected:
	POINT m_cardPrintStart;
	POINT m_cardPrintNext;
	POINT m_yamaPrint;

	int m_subMode;
	int m_firstClick;
	int m_nextClick;

	int m_nowSelect;
	int m_maeSelect;

	int m_yamaMaisuu;
	int m_yama[52];
	int m_ba[4][6];
	int m_mokutekichi[4][6];

	void Shuffle(void);

	void CalcuStartNaraberu(void);
	void CalcuKieru(void);
	void CalcuTsumeru(void);
	void CalcuNaraberu(void);

	void PrintNormal();
	void PrintStartNaraberu(void);
	void PrintKieru(void);
	void PrintTsumeru(void);
	void PrintNaraberu(void);

	void EraseCard(int x,int y);
	void PutCard(int x,int y,int card,int trans = 100,BOOL sel = FALSE,BOOL chk = FALSE);

	void PrintYama(BOOL selFlag = FALSE,BOOL eraseFlag = FALSE);

	void StartNormal(void);
	void StartKieru(void);
	void StartTsumeru(void);
	void StartNaraberu(void);

	int m_startNaraberuCount;
	int m_startNaraberuCountMax;

	int m_kieruCount;
	int m_kieruCountMax;

	int m_tsumeruCount;
	int m_tsumeruCountMax;

	int m_naraberuCount;
	int m_naraberuCountMax;

	int m_normalMaisuu;
	int m_naraberuMaisuu;


	CPicture* m_trumpPic;
	SIZE m_trumpSize;

	BOOL CheckSkip(void);

	BOOL CheckExistOkCard(void);
	BOOL CheckTsumerareru(void);
	BOOL CheckSukimaaru(void);

	void CalcuGameOverCheck(void);
	void CalcuClearCheck(void);

	void ClickYama(void);
	int GetOnCard(POINT pt);
	
	int m_cardPicType;
	POINT GetCardPic(int n);

};

#endif
/*_*/

