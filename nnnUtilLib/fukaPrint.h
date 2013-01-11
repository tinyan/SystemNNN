//
//
//



#if !defined __NNNUTILLIB_FUKAPRINT__
#define __NNNUTILLIB_FUKAPRINT__

class CSetupList;
class CPicture;
class CNameList;
class CFukaPrint
{
public:
	CFukaPrint(CNameList* lpSetup);
	virtual ~CFukaPrint();
	void End(void);

	void SetStartTime(int startTime);
	void CalcuFuka(int nowTime);
	void PrintFuka(int fuka = -1);

private:
	CNameList* m_setup;
	CPicture* m_pic;
	int m_fukaStart;
	int m_fuka;

	int m_printX;
	int m_printY;
	int m_sizeX;
	int m_sizeY;

	int m_fukaCount;

	LPSTR m_fontName;
	static char m_defaultFontName[];

	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpVar, LPSTR name);


};

#endif
/*_*/

