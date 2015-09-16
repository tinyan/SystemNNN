//
// myfont.h
//

#if !defined __NYANUTILLIB_MYFONT__
#define __NYANUTILLIB_MYFONT__

class CPicture;
//class CGame;
class CUserFont;

class CMyFontCache;
#define MYFONT_SIZE_MAX 72

class CMyFont
{
public:
	CMyFont(HWND hwnd, LPSTR fontName = NULL);
	~CMyFont();
	void End(void);

	int MakePic(LPSTR orgMessage,LPSTR message, int colR=-1, int colG=-1, int colB=-1, int sukima = 1, int kageColor = -1,COLORREF* colorPtr = NULL,int rubiKosuu = 0,int kanjiMax = 0,int* rubiKanjiSize = NULL,char** rubiMessage = NULL);

	int MakePicOnly(LPSTR message, int colR=-1, int colG=-1, int colB=-1, int sukima = 1, int kageColor = -1,COLORREF* colorPtr = NULL);
	int MakeBuffer(LPSTR message, int colR=-1, int colG=-1, int colB=-1, int sukima = 1, int kageColor = -1,COLORREF* colorPtr = NULL);

	void BeginPrint(int fontsize = 16,BOOL bAntiAliasFlag = TRUE);
	void EndPrint(void);

	void BeginRubiPrint(int fontsize = 16,BOOL bAntiAliasFlag = TRUE);
	void EndRubiPrint(void);

	HFONT MakeFont(LPSTR fontname, int fontsize);

	static int m_fontSizeTable[7];
	CPicture* GetPic(void);

	HDC GetHDC(void);

	static int GetMaxFontSize(void);

	static int m_rubiSukima;
	static int m_rubiPercent;
	static int m_rubiDeltaY;

	static int m_rubiColorR;
	static int m_rubiColorG;
	static int m_rubiColorB;
	static int m_rubiColorFixFlag;

	static int m_fontType;
	static int m_userFont;
	static char m_userFontName[256];

	static char m_defaultGaijiFilename[];

	static int m_rubiUseFlag;

	BOOL LoadUserFont(LPSTR fontfilename);

	void Print(int putX,int putY,int deltaX,int deltaY,int sizeX,int sizeY);
	void PrintRubi(int putX,int putY,int deltaX,int deltaY,int sizeX,int sizeY);
	void SetUserGaijiFont(LPSTR filename);

	void GradPrint(int startX,int endX,int putX,int putY,int deltaX,int deltaY,int sizeX,int sizeY);
	void GradPrintRubi(int startX,int endX,int putX,int putY,int deltaX,int deltaY,int sizeX,int sizeY);

	void EffectPrint(int putX,int putY,int deltaX,int deltaY,int sizeX,int sizeY,int fontSize,int effectType,int effectCount1000);


#if defined _TINYAN3DLIB_ 
	void ClearCache(void);
#endif
	void ReCreateDIB(void);

	int GetRubiFontSize(void);

	void ClearFontCache(void);

	static int m_codeByte;
//	static int m_fukuroType;
	static int m_fukuroTable[3][3];
	static void SetFukuroType(int type);

	static int m_fontWeight;
	static int m_fontItalic;
private:
//	CGame* m_game;

	HBITMAP m_hBitmap;
	int* m_lpBuffer;

	CPicture* m_pic;
	int* m_picBuffer;
	char* m_antiBuffer;

	CPicture* m_rubiPic;
	int* m_rubiPicBuffer;
	char* m_rubiAntiBuffer;

	CPicture* m_specialFontPic;
	int* m_specialFontPicBuffer;

	HFONT m_font[MYFONT_SIZE_MAX+1];

	HWND m_hWnd;

	int GetFontSize(int fontsize);

	BOOL m_fontFlag;

	HGDIOBJ m_oldBitmap;
	HGDIOBJ m_oldFont;
//	HDC m_hdc;
	HDC m_src;

	int m_oldBkMode;
	COLORREF m_oldTextColor;

	int m_nowFontSize;
	int m_specialFontSizeX;
//	int m_nowRubiFontSize;

	void Gaiji(int x, int y, int col, int dat);

	BITMAPV4HEADER m_bmi;

	CUserFont* m_userCustomFont;
	int m_userCustomFontSize;

	char m_fontName1[256];
	char m_fontName2[256];

	void MakeCustom(int x,int y, int dx,int dy,LPSTR mes, int colR,int colG,int colB);
	CMyFontCache* m_fontCache;
	int m_fontCacheNumber;
	
	CPicture* m_userGaijiFontPic;
	int* m_userGaijiFontPicBuffer;
	int m_userGaijiSizeX;

	int m_mainFontSize;
	int m_rubiFontSize;

	int m_charaSet;

};



#endif
/*_*/
