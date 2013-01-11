//
// mmx.h
//

#if !defined __NYANLIB_MMX__
#define __NYANLIB_MMX__


class CMMX
{
public:
	CMMX();
	~CMMX();
	void End(void);

	void SetSurfaceParameter(LPVOID lpSurface,int lPitch);
	void SetBufferParameter(int* lpScreenBuffer, int screenPitch, int screenSizeX, int screenSizeY);

	void MMX32to16(void);
	void MMX32to24(void);
	void MMX32to32(void);

	void MMXPrint(int bpp);

	void MMX32to16(int startX,int startY,int sizeX, int sizeY);
	void MMX32to24(int startX,int startY,int sizeX, int sizeY);
	void MMX32to32(int startX,int startY,int sizeX, int sizeY);

	void MMX32to24BGR(int startX,int startY,int sizeX, int sizeY);
	void MMX32to32BGR(int startX,int startY,int sizeX, int sizeY);

	void MMXPrint(int bpp,int startX,int startY,int sizeX,int sizeY);

	BOOL CheckMMXExist(void);

	void Set565Mode(BOOL md = TRUE);
	void SetRGB24Mode(BOOL md = TRUE);
	void SetRGB32Mode(BOOL md = TRUE);

	static BOOL CheckMMX(void);

private:

	BOOL m_mmxExistFlag;

	LPVOID m_lpSurface;
	int m_lPitch;

	int* m_lpScreenBuffer;
	int m_lScreenPitch;
	int m_screenSizeX;
	int m_screenSizeY;

	BOOL m_565Mode;
	BOOL m_RGB24Mode;
	BOOL m_RGB32Mode;
};

#endif
/*_*/
