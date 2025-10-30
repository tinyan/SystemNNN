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
	void SetViewParam(int realSizeX,int realSizeY,int viewOffsetX,int viewOffsetY);

	void _MMX32to16(void);
	void _MMX32to24(void);
	void _MMX32to32(void);

	void _MMXPrint(int bpp);

	void MMX32to16(int startX,int startY,int sizeX, int sizeY);
	void MMX32to24(int startX,int startY,int sizeX, int sizeY);
	void MMX32to32(int startX,int startY,int sizeX, int sizeY);

	void MMX32to24BGR(int startX,int startY,int sizeX, int sizeY);
	void MMX32to32BGR(int startX,int startY,int sizeX, int sizeY);

	void MMXPrint(int bpp,int startX,int startY,int sizeX,int sizeY);
	void CMMX::NonMMXPrint(int bpp);

	BOOL CheckMMXExist(void);

	void Set565Mode(BOOL md = TRUE);
	void SetRGB24Mode(BOOL md = TRUE);
	void SetRGB32Mode(BOOL md = TRUE);

	static BOOL CheckMMX(void);

	bool CheckNeedCreateTable(void);
	void CreateStretchTable(void);
	void CreateSurfaceData(int bpp, int realWindowSizeX, int realWindowSizeY, int screenSizeX, int screenSizeY);

	bool CheckNeedCreateSurfaceBuffer(int bpp, int realWindowSizeX, int realWindowSizeY);
	void CreateSurfaceBuffer(int bpp, int realWindowSizeX, int realWindowSizeY);

	void SetSimpleStretchMode(int bSimple);

	bool CheckSameComplete(int bpp);

private:
	BOOL Clip(int& srcX,int& srcY,int& dstX,int& dstY,int& sizeX,int& sizeY);

	BOOL m_mmxExistFlag;

	LPVOID m_lpSurface;
	int m_lPitch;

	int* m_lpScreenBuffer;
	int m_lScreenPitch;
	int m_screenSizeX;
	int m_screenSizeY;

	int m_realWindowSizeX;
	int m_realWindowSizeY;

	int m_offsetX;
	int m_offsetY;

	BOOL m_565Mode;
	BOOL m_RGB24Mode;
	BOOL m_RGB32Mode;
	bool m_createStretchTable;
	int* m_horizonTable;
	int* m_verticalTable;
	int m_horizonTableSize;
	int m_verticalTableSize;

	bool m_createSurfaceBuffer;
	INT32* m_surfaceBuffer;
	int m_surfaceBufferBpp;
	int m_surfaceBufferSizeX;
	int m_surfaceBufferSizeY;

	int m_simpleStretchMode;
};

#endif
/*_*/
