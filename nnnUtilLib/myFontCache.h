#if !defined __NYANUTILLIB_MYFONTCACHE__
#define __NYANUTILLIB_MYFONTCACHE__

class CPicture;


class CMyFontCache
{
public:
	CMyFontCache(int sizeY = -1,BOOL rubiFlag = FALSE);
	~CMyFontCache();
	void End(void);

	BOOL GetData(int n,CPicture* lpPic);
	SIZE GetSize(int n);
	POINT GetSrc(int n);
	int SearchData(LPSTR message,int fontSize,int colR,int colG,int colB,int sukima,int kageColor);
	int AddData(LPSTR message,int fontSize,int colR,int colG,int colB,int sukima,int kageColor,int sizeX2,int sizeY2,CPicture* lpPic,CPicture* lpRubiPic);
	void Blt(int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL transFlag = TRUE);
	void BltRubi(int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL transFlag = TRUE);
	void GradBlt(int startX,int endX,int fontSize,int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL transFlag = TRUE);
	void GradBltRubi(int startX,int endX,int fontSize,int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL transFlag = TRUE);

	void EffectBlt(int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL transFlag = TRUE,int effectType = 0,int effectCount1000 = 0);

	static void SetEffectColor(int r,int g,int b,int a);

#if defined _TINYAN3DLIB_
	void ClearCache(void);
#endif

	void ClearFontCache(void);

	static int m_gradBunkatsu;

	static int m_effectColorR;
	static int m_effectColorG;
	static int m_effectColorB;
	static int m_effectColorA;

private:
	CPicture* m_fontPic;
	CPicture* m_rubiPic;

	int m_cacheSizeX;
	int m_cacheSizeY;

	int m_dataKosuuMax;
	int* m_table;
	char* m_messageTable;

	int m_rubiFlag;

	int m_dataKosuu;
	int m_useStart;

	int m_bufferStartY;
	int m_bufferSizeY;


	int SetDataSub(int ln,int fontSize,LPSTR message,int colR,int colG,int colB,int sukima,int kageColor,int sizeX2,int sizeY2,CPicture* lpPic,CPicture* lpRubiPic);
	LPVOID m_fontTexture;	//for 3D only
	LPVOID m_fontOffScreen;
};

#endif

/*_*/

