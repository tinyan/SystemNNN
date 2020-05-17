//
// nothing.h
//

#if !defined __NNNLIB_SELECTMOVIE__
#define __NNNLIB_SELECTMOVIE__

class CCommonGeneral;
class CGameCallBack;
class CNameList;
class CPagePrint;
class CSuuji;


class CCommonSelectMovie : public CCommonGeneral
{
public:
	CCommonSelectMovie(CGameCallBack* lpGame);
	virtual ~CCommonSelectMovie();
	virtual void End(void);

	virtual int Init(void);
	virtual int Calcu(void);
	virtual int Print(void);

	static char m_defaultBGFileName[];

	static char m_defaultFont1FileName[];
	static char m_defaultFont2FileName[];
	static char m_defaultFont3FileName[];
	static char m_defaultCursorFileName[];

	static char m_defaultPrefixOff[];
	static char m_defaultPrefixOn[];

protected:
	LPSTR m_prefixOff;
	LPSTR m_prefixOn;

	int m_selectedNumber;
	int m_maeSelectNumber;
	int m_nowSelectNumber;

	int m_page;
	int m_pageMax;
	int m_length;
	int m_count;

	int m_startupWait;

	int m_printX;
	int m_printY;
	int m_nextX;
	int m_nextY;
	int m_sizeX;
	int m_sizeY;

	int m_picPrintX;
	int m_picPrintY;
	int m_picSizeX;
	int m_picSizeY;

	int m_cursorPrintX;
	int m_cursorPrintY;
	int m_cursorSizeX;
	int m_cursorSizeY;


	CPicture* m_cursorPic;
	CPicture** m_miniPic;
	CSuuji* m_suuji;

	void LoadBackMovie(void);
	int GetOnMovie(int mouseX, int mouseY);


	int m_fontSizeX1;
	int m_fontSizeY1;
	int m_fontNextX1;
	//	int m_fontNextY1;

	int m_fontSizeX2;
	int m_fontSizeY2;
	int m_fontNextX2;
	//	int m_fontNextY2;

	int m_fontSizeX3;
	int m_fontSizeY3;
	int m_fontNextX3;
	//	int m_fontNextY3;


	int m_totalPercentPrintFlag;

	int m_totalPercentPrintX;
	int m_totalPercentPrintY;

//	int m_sabunPrintFlag;
//	int m_sabunPrintByGetFlag;

//	int m_differencePrintX;
//	int m_differencePrintY;



	//	int m_pagePrintFlag;
	//	int m_pagePrintX;
	//	int m_pagePrintY;

	//	int m_pageMaxPrintFlag;
	//	int m_pageMaxPrintX;
	//	int m_pageMaxPrintY;

	//	int m_slashPrintFlag;
	//	int m_slashPrintX;
	//	int m_slashPrintY;

//	int m_cgCharaKosuu;
	//	int m_blockSabunKosuu[11];
//	int* m_blockSabunKosuu;

	//	int m_blockSabunStart[11][100];
//	int** m_blockSabunStart;

	//	int m_cgKosuu[11];
//	int* m_cgKosuu;

	//	BOOL m_cgFlag[100];
//	BOOL* m_cgFlag;

	//	int m_blockGetKosuu[100];
//	int* m_blockGetKosuu;

	int m_blockKosuuX;
	int m_blockKosuuY;

	int m_selectColorR;
	int m_selectColorG;
	int m_selectColorB;
	int m_selectPercent;
	int m_selectPrintMode;
	int m_cursorPrintType;

	int m_picMustPrintPercent;


	virtual void BeforeInit(void) {}
	virtual void AfterInit(void) {}
	virtual void BeforeCalcu(void) {}
	virtual void AfterCalcu(void) {}
	virtual void BeforePrint(void) {}
	virtual void AfterPrint(void) {}

//	int m_cgPianoSoundFlag;

	int m_superMode;

	void PrintTotalPercent(void);
	//	void PrintPage(void);
//	void PrintAddPic(void);
	void PrintAllMiniPic(void);

//	CPicture* m_addPic;
//	CPicture** m_miniPic;
//	int* m_miniPicState;
//	int* m_animeFlag;

	int m_futaPrintFlag;
	int m_animePrintFlag;
	CPicture* m_suujiPic3;

//	int m_miniPicTransFlag;

	CPagePrint* m_pagePrint;

	int m_selectSound;
//	CCGDataControl* m_cgDataControl;


	int m_useOpeningMovie;
	int m_movieCount;

	int m_percent;

	int* m_getMovieFlag;
};

#endif
/*_*/

