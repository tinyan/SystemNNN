#if !defined __NNNUTILLIB_COMMONANIMEPARTS__
#define __NNNUTILLIB_COMMONANIMEPARTS__

class CPicture;
class CNameList;

class CCommonAnimeParts
{
public:
	CCommonAnimeParts(LPSTR tagName,CNameList* setup,BOOL createFlag = TRUE);
	~CCommonAnimeParts();
	void End(void);

	LPSTR GetPictureFileName(void);
	void SetPicture(CPicture* lpPic);

	void Init(void);
	void Calcu(int cnt = 1);
	void Print(void);
	void Print(POINT pt);
	void DeltaPrint(POINT pt);

	SIZE GetSize(void){return m_animePicSize;}
	
private:
	int m_animeCount;
	int m_animeCountMax;
	int m_animeNumber;

	CPicture* m_pic;

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

	int m_createFlag;
	static char m_defaultPicFileName[];
};




#endif

/*_*/

