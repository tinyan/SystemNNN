#if !defined __TINYAN_NNNUTILLIB_CUTINNAMEDATA__
#define __TINYAN_NNNUTILLIB_CUTINNAMEDATA__

class CNameList;

class CCutinNameData
{
public:
	CCutinNameData(LPSTR name = NULL);
	~CCutinNameData();
	void End(void);

	BOOL CheckNameIsNotAll(int cutin);

	LPSTR GetCharaName(int cutin);
	LPSTR GetFileNameTag(int cutin);

	POINT GetZahyo(int cutin);
	POINT GetNextZahyo(int cutin);
	int GetWindowType(int cutin);
	SIZE GetWindowDXDY(int cutin);
	int GetWindowColorR(int cutin);
	int GetWindowColorG(int cutin);
	int GetWindowColorB(int cutin);
	int GetWindowColorA(int cutin);
	int GetFontSizeDelta(int cutin);

	POINT GetWindowZahyo(int cutin);
	SIZE GetWindowSize(int cutin,int fontSize,int gyo,int ln = 0);

	int SearchFirst(LPSTR charaName);
	int GetNext(void);

private:
	static char m_errorCharaName[];
	static char m_errorFileNameTag[];

	int m_kosuu;

	CNameList* m_list;
	POINT* m_zahyo;
	POINT* m_nextZahyo;
	int* m_windowType;
	SIZE* m_windowDXDY;
	int* m_windowColorRGBA;
	int* m_fontSizeDelta;

	int m_foundNumber;
	char m_searchCharaName[256];
};

#endif
/*_*/

