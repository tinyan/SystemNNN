//
// mygraphics.h
//

#if !defined __NYANLIB_MYGRAPHICS__
#define __NYANLIB_MYGRAPHICS__


class CPicture;

class CTransCircleFill;
class CTransTorusFill;
class CBoxFill;
class CTransBoxFill;

class CAllGraphics;
class CAllGeo;
class CAllPicture;

class CMyGraphics
{
public:
	CMyGraphics(int sizeX=800,int sizeY=600,int notUseDirectDraw = 0);
	~CMyGraphics();
	void End(void);

	static int* GetScreenBuffer(void);
	static int* GetCommonX8Buffer(void);
	static SIZE GetScreenSize(void);
	static int GetScreenSizeX(void);
	static int GetScreenSizeY(void);

	static int GetScreenClipStartX(void);
	static int GetScreenClipStartY(void);
	static int GetScreenClipEndX(void);
	static int GetScreenClipEndY(void);

	static void SetScreenClip(POINT startPoint,POINT endPoint);


	static BOOL Clip(int* px, int* py, int* pSizeX, int* pSizeY);
	static BOOL Clip(POINT* lpDstPoint,POINT* lpSrcPoint,SIZE* lpSize);
	static BOOL Clip(POINT* lpDstPoint,POINT* lpSrcPoint,SIZE* lpSize,SIZE* lpSrcSize);

//	static BOOL InitStaticData(int sizeX = 800,int sizeY = 600);
//	static BOOL ReleaseStaticData(void);

	void ReCreateAllShader(void);

	static void NiseFlip(HWND hwnd,int x,int y,int sizeX,int sizeY,int waitFlag = FALSE);

private:
	static int* m_lpScreenBuffer;
	static int* m_commonX8Buffer;
	static SIZE m_screenSize;
	static POINT m_screenClipStart;
	static POINT m_screenClipEnd;

	int m_notUseDirectDraw;

	CAllGraphics* m_allGraphics;
	CAllGeo* m_allGeo;
	CAllPicture* m_allPicture;

	static HBITMAP m_dib;
};

#endif
/*_*/

