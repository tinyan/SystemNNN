#if !defined __NNNUTILLIB_PAGEPRINT__
#define __NNNUTILLIB_PAGEPRINT__


class CPicture;
class CNameList;

class CPagePrint
{
public:
	CPagePrint(CNameList* namelist,CPicture* lpBG = NULL);
	~CPagePrint();
	void End(void);

	void Print(int page,int pageMax);
	void AppearPrint(int appearCount, int appearCountMax, int appearType, int page, int pageMax);

private:
	CNameList* m_setup;

	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

	static char m_defaultPageFontFileName[];

	int m_keta;

	CPicture* m_fontPic;
	CSuuji* m_suuji;
	CSuuji* m_suujiMax;

	int m_pagePrintFlag;
	int m_pageMaxPrintFlag;
	int m_slashPrintFlag;

	int m_pagePrintX;
	int m_pagePrintY;
	int m_fontSizeX;
	int m_fontSizeY;
	int m_fontNextX;

	int m_pageMaxPrintX;
	int m_pageMaxPrintY;

	int m_slashPrintX;
	int m_slashPrintY;

	CPicture* m_bg;

	int m_upZeroPrintFlag;
	int m_upZeroPrintFlagMax;

};


#endif

/*_*/

















