#if !defined __NNNUTILLIB_PRINTGAMEDATE__
#define __NNNUTILLIB_PRINTGAMEDATE__

class CPicture;
class CSuuji;
class CNameList;

class CPrintGameDate
{
public:
	CPrintGameDate(CNameList* setup,LPSTR tagName,CPicture* lpBG = NULL);
	~CPrintGameDate();
	void End(void);

	void Print(POINT pt,int date);
	void Print(POINT pt,int month,int day);
	void Print(POINT pt,int year,int month,int day);

	void AppearPrint(int count,int countMax,int type,POINT pt, int year, int month, int day);

	void Print(int date);
	void Print(int month,int day);
	void Print(int year,int month,int day);

private:

	int m_yearPrintFlag;
	int m_monthPrintFlag;
	int m_dayPrintFlag;
	int m_weekPrintFlag;

	int m_gameDateSlashPrintFlag;

	int m_yearSlashPrintFlag;
	int m_monthSlashPrintFlag;
	int m_daySlashPrintFlag;
	int m_weekYouPrintFlag;
	int m_weekBiPrintFlag;

	POINT m_timeZahyo;
	POINT m_yearZahyo;
	POINT m_monthZahyo;
	POINT m_dayZahyo;
	POINT m_weekZahyo;
	SIZE m_timeFontSize;
	SIZE m_weekFontSize;
	int m_timeFontNextX;
	int m_weekFontNextX;

	int m_yearUpZeroFlag;
	int m_monthUpZeroFlag;
	int m_dayUpZeroFlag;

	CPicture* m_timePic;
	CPicture* m_weekPic;

	CSuuji* m_yearSuuji;
	CSuuji* m_monthSuuji;
	CSuuji* m_daySuuji;
	CSuuji* m_weekSuuji;

	CNameList* m_setup;

	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);


	CPicture* m_commonBG;
	int m_bgPrintFlag;

	void Erase(int putX,int putY,int sizeX,int sizeY);

	static char m_defaultPicFileName[];

	int m_printX;
	int m_printY;

};


#endif
/*_*/

