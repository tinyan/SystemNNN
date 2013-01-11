//
//
//



#if !defined __NNNUTILLIB_FPSPRINT__
#define __NNNUTILLIB_FPSPRINT__

class CSetupList;
class CPicture;
class CNameList;
class CFpsPrint
{
public:
	CFpsPrint(CNameList* lpSetup);
	virtual ~CFpsPrint();
	void End(void);

	void Print(void);

private:
	CNameList* m_setup;
	CPicture* m_pic;

	LONGLONG m_oldTime;

	int m_fps;
	int m_fpsCount;

	int m_printX;
	int m_printY;
	int m_sizeX;
	int m_sizeY;

	LPSTR m_fontName;
	static char m_defaultFontName[];

	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpVar, LPSTR name);

	LONGLONG GetLocalTimeCount(void);

};

#endif
/*_*/

