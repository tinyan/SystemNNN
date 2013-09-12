#if !defined __NNNUTILLIB_PRINTANIMELAYER__
#define __NNNUTILLIB_PRINTANIMELAYER__

class CPicture;
class CTaihi;

class CPrintAnimeLayer
{
public:
	CPrintAnimeLayer(CNameList* setup,LPSTR tagName,CPicture* lpBG = NULL,CTaihi* taihi = NULL,int layer = 0,BOOL createPicFlag = FALSE);
	~CPrintAnimeLayer();
	void End(void);

	LPSTR GetPictureFileName(void);
	void SetPicture(CPicture* lpPic);

	void Clear(void);
	void Print(int anime,BOOL dontErase = FALSE);
	void Print(POINT pt,int anime,BOOL dontErase = FALSE);

	LPSTR GetVarName(void){return m_varName;}
	int GetVarNumber(void){return m_varNumber;}
	void SetVarNumber(int n){m_varNumber = n;}

private:
	int m_animeCount;
	int m_animeCountMax;
	int m_animeNumber;

	CPicture* m_commonBG;
	CPicture* m_pic;

	int m_picCreateFlag;

	int m_bgPrintFlag;

	POINT m_animePrintZahyo;
	int m_animeType;
	int m_animePattern;
	int m_animeSpeed;
	int m_limitFlag;

	SIZE m_animePicSize;
	int m_yokoKosuu;
	int m_varNumber;
	LPSTR m_varName;

	LPSTR m_picFileName;

	CNameList* m_setup;

	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);

	POINT GetPicSrc(int n);

	CTaihi* m_taihi;
	int m_taihiLayer;

	static char m_defaultPicFileName[];
};




#endif

/*_*/

