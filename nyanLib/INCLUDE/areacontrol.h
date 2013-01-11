//
// areacontrol.h
//

#if !defined __NYANLIB_AREACONTROL__
#define __NYANLIB_AREACONTROL__

class CAreaControl
{
public:
	CAreaControl();
	~CAreaControl();

	static int m_areaKosuu;
	static int m_areaSize;
	static BOOL m_allPrintFlag;

	static BOOL m_nextAllPrintFlag;
	static int m_nextAllPrintFlag2;
	static BOOL m_skipPrintFlag;
	static BOOL m_skippedFlag;
	static int m_fullScreenCount;
	static BOOL m_fullScreenFlag;

	static void ClearArea(void);
	static void AddArea(int startX,int startY,int sizeX,int sizeY);
	static void SetAllPrintMode(BOOL bFlag = TRUE);
	static int GetAreaKosuu(void);
	static BOOL GetArea(int n, int& startX, int& startY, int& sizeX, int& sizeY);
	static void SetNextAllPrint(int cnt = 0);
	static void ToSkipMode(void);
	static void StartScene(void);
	static void EndScene(void);
	static BOOL CheckSkipMode(void);
	static BOOL CheckAllPrintMode(void);
	static void ToFullScreen(void);
	static void ToWindowScreen(void);
	static void SetVista(void);
	static BOOL m_vista;

private:
	typedef struct
	{
		int startX;
		int startY;
		int sizeX;
		int sizeY;
	} AREACONTROL;
	
	static AREACONTROL m_area[256];
};


#endif

/*_*/
