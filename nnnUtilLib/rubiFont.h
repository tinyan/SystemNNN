//
// myfont.h
//

#if !defined __NNNUTILLIB_RUBIFONT__
#define __NNNUTILLIB_RUBIFONT__

class CPicture;
//class CGame;

class CRubiFont
{
public:
	CRubiFont(HWND hwnd);
	~CRubiFont();
	void End(void);

	void Reset(void);
	BOOL AddRubi(int x, int y, LPSTR mes, COLORREF col,int ln);
	void PrintRubi(HDC hdc);


	int MakePic(LPSTR message, int colR=-1, int colG=-1, int colB=-1, int sukima = 1, int kageColor = -1,COLORREF* colorPtr = NULL);

	void BeginPrint(int fontsize = 16,BOOL bAntiAliasFlag = TRUE);
	void EndPrint(void);


	HFONT MakeFont(LPSTR fontname, int fontsize);

	static int m_fontSizeTable[7];
	CPicture* GetPic(void);

	static int m_fontType;
	static int m_userFont;
	static char m_userFontName[256];

private:
	int m_rubiKosuu;
	static COLORREF m_rubiColor[];
	static LPSTR m_rubiMessage[];
	static int m_rubiZahyo[];
	static int m_rubiLength[];


//	CGame* m_game;

	HBITMAP m_hBitmap;
	int* m_lpBuffer;

	CPicture* m_pic;
	int* m_picBuffer;
	char* m_antiBuffer;

	CPicture* m_specialFontPic;
	int* m_specialFontPicBuffer;

	HFONT m_font[25];

	HWND m_hWnd;

	int GetFontSize(int fontsize);

	BOOL m_fontFlag;

	HGDIOBJ m_oldBitmap;
	HGDIOBJ m_oldFont;
//	HDC m_hdc;
	HDC m_src;

	int m_nowFontSize;
	int m_specialFontSizeX;

	void Gaiji(int x, int y, int col, int dat);

	BITMAPV4HEADER m_bmi;

};



#endif
/*_*/
