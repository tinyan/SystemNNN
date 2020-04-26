//
// picture.h
//

#if !defined __NYANLIB_PICTURE__
#define __NYANLIB_PICTURE__

#include <stdio.h>

class CRedBlt;
class CGreyBlt;

//class COverrap;
class CGenshoku16;

class CJpegDecoder;
class CPngLoader;

class CPicture
{
public:
	CPicture(LPSTR filename = NULL,int nx = 1,int ny = 1,BOOL b256Flag = FALSE);
	CPicture(int sizeX, int sizeY, BOOL cretaeMaskFlag = FALSE,BOOL b256Flag = FALSE);

	virtual ~CPicture();
//	void Init(void);
	void End(void);

	BOOL LoadDWQ(LPSTR filename, BOOL b256Flag = FALSE,LPSTR dirName = NULL);
//	BOOL LoadPicture(LPSTR filename, BOOL b256Flag = FALSE,BOOL bAntiAliasFlag = FALSE,LPSTR antiAliasFilename = NULL);

	void Flush(void);


//	void Put(void);
//	void Put(int x , int y);
	void Put(int x =0, int y = 0,BOOL bTransFlag = FALSE);


	void Blt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag);

	void DeltaBlt(int putX, int putY, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag, int* deltaPtr);
	void LeftBlt(int putX, int putY, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag, int* cutPtr,int ps = 100);
	void RightBlt(int putX, int putY, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag, int* cutPtr,int ps = 100);

	void GreyBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY,BOOL bTransFlag = TRUE);
	void GreyBlt2(int x, int y, int srcX, int srcY, int sizeX, int sizeY,int ps256,BOOL bTransFlag = TRUE);
	void SepiaBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY,int ps256,int r=107,int g=74,int b=43,BOOL bTransFlag = TRUE);
	void RedBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY,BOOL bTransFlag = TRUE);



	void DarkMaskBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int r, int g, int b);//old routine->ColorAddBlt




//	void BltWithZ(int zStart, int x, int y, int srcX, int srcY, int sizeX, int sizeY);
//	void BltWithZHeimen(int zStart, int x, int y, int srcX, int srcY, int sizeX, int sizeY);
//	void BltCheckZHeimen(int zStart, int x, int y, int srcX, int srcY, int sizeX, int sizeY,int transPercent = 100);
//	void BltNanameZ(int zStart, int deltaZ, int x, int y, int srcX ,int srcY, int sizeX,int sizeY);
//	void BltNanameCheckZ(int zStart, int deltaZ, int x, int y, int srcX ,int srcY, int sizeX,int sizeY,int transPercent = 100);
//	void BltCheckZ(int zStart, int x, int y, int srcX, int srcY, int sizeX, int sizeY, int transPercent = 100);

//	void StretchYBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int srcSizeX, int srcSizeY, BOOL bTransFlag);

//	void StretchBlt1(int putX, int putY, int multiXPercent, int multiYPercent,int transPercent = 100, int centerDeltaX = 0, int centerDeltaY = 0,int srcX = 0, int srcY = 0, int srcSizeX = 0, int srcSizeY = 0, BOOL bTransFlag = TRUE);
	void StretchBlt1(int putX, int putY, int sizeX, int sizeY, int srcX, int srcY, int srcSizeX, int srcSizeY, int transPercent = 100, BOOL bTransFlag = TRUE);
	void StretchAddSubBlt(int putX, int putY, int sizeX, int sizeY, int srcX, int srcY, int srcSizeX, int srcSizeY, int transPercent = 100, BOOL bTransFlag = TRUE,int deltaR = 0,int deltaG = 0,int deltaB = 0);




	void BltNega(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int ps);

	void AddBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY);
	void LightBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int transPercent);

	void TransLucentBlt0(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int transPercent);
	void TransLucentBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int transPercent);
	void TransLucentBlt2(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int transPercent);
	void TransLucentBlt3(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int transPercent);

	BOOL Clip(int& x, int& y, int& srcX, int& srcY, int& sizeX, int& sizeY);

	BOOL ClipChara(int& x, int& y, int& srcX, int& srcY, int& sizeX, int& sizeY);
	BOOL ClipCharaLarge(int& x, int& y, int& srcX, int& srcY, int& sizeX, int& sizeY,CPicture* pic2);
	BOOL ClipEtc(int& x, int& y, int& srcX, int& srcY, int& sizeX, int& sizeY);

	void GetPicSize(RECT* lpRect);
	SIZE GetPicSize(void);

	//	static CGame* m_lpCGame;
//	static LPVOID m_lpScreenBuffer;
//	static BOOL m_mmxFlag;

//	static LPVOID m_ZBuffer;

//	static BOOL m_notAntiAliasFlag;
	static BOOL m_genshokuFlag;
	static BOOL m_genshokuMiniSizeFlag;
	static BOOL m_genshokuJustSizeFlag;
	static BOOL m_genshokuOverSizeFlag;
	static BOOL m_errorPrintFlag;

	void* GetBuffer(void);
	int GetlPitch(void);

	char* GetMaskPic(void);

	void* GetPalette(void);

	LPSTR GetFileName(void);
	int GetFileMode(void);

	static char m_dirName[16];
	static char m_extName[4];

	static void SetDirName(LPSTR dirname);
	static void SetExtName(LPSTR extname);

//	void MakeAntiMask(void);

/////	void AntiAliasBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY);
	void AntiAliasBlt2(int x, int y, int srcX, int srcY, int sizeX, int sizeY);

	void ColorAddBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag, int r, int g, int b,int ps = 100);

	void ColorBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag, int r, int g, int b);

	void CutData(void);

	void ShapeBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int r, int g, int b);
	void GradationShapeBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int r, int g, int b, int r2, int g2,int b2, BOOL tateFlag = TRUE);


	void YUVChangeBlt(int x,int y,int srcX,int srcY,int sizeX,int sizeY, BOOL reverseFlag = FALSE,int betaTransPercent255 = 255);

	void AddSubBlt(int x,int y,int srcX,int srcY,int sizeX,int sizeY,int ps);


	BOOL Check256(void);
	int* GetPictureBuffer(void);

	BOOL LoadAntiAlias2(LPSTR filename);

//@@	BOOL ChangeTranslateBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int ps1, int ps2, int* lpPic2, char* lpMask2,CPicture* pic2);
	BOOL ChangeTranslateBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int ps1, int ps2, CPicture* pic2, int srcX2,int srcY2);
	BOOL ChangeBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int ps1, int ps2, CPicture* pic2, int srcX2,int srcY2);

//	char* GetAntiMask(void);

	int m_charaClipXStart;
	int m_charaClipXEnd;
	int m_charaClipYStart;
	int m_charaClipYEnd;

//	static char m_tmpBuffer[64 + 54 + 1024 + 640*480];
	static char* m_tmpBuffer;

	static int m_bpp;

	BOOL CheckOnPic(int x, int y, int transPointX = 0,int transPointY = 0);

//	static void ClearZBuffer(void);

	BOOL GetScreen(void);
	BOOL GetScreen(int x, int y, int sizeX = -1,int sizeY = -1);


	void Overrap(CPicture* nextPic, int nowPercent, POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);
	void Overrap2(int perrcent, POINT* lpPoint = NULL);



//	static void FillScreen(int r = 0, int g = 0, int b = 0);
//	static void Box(int x, int y, int sizeX, int sizeY, int r, int g, int b);
//	static void TransBox(int x, int y, int sizeX, int sizeY, int r, int g, int b, int percent);

	BOOL ReSize(int x, int y);

	static void InitStaticData(int tmpMegaBytes = 3);
	static void ReleaseStaticData(void);


//	static COverrap* m_overrap;
	static CGenshoku16* m_genshoku16;

//	static CRedBlt* m_redBlt;
//	static CGreyBlt* m_greyBlt;
	static CJpegDecoder* m_jpegDecoder;

	static CPngLoader* m_pngLoader;

//	BOOL CheckAntiMask(void);	//old
	BOOL CheckMaskExist(void);	//new

//	static int m_screenSizeX;
//	static int m_screenSizeY;
	BOOL CheckGenshokuSize(int sizeX,int sizeY);

	static SSIZE_T m_dataPackLevel;
	static void SetDataPackLevel(SSIZE_T level){m_dataPackLevel = level;}

	static char** m_ppPackTable;
	static BOOL* m_pack64Flag;
	static LONGLONG** m_ppPackTable64;

	static char m_packTagName[10][8];

	LPVOID GetTexture(void);
	static void SetModeNumberForDebug(int md);
	static int m_modeNumber;

	static char m_old[8192];
	static char m_tmp[8192];
	static char m_unpack[8192];

protected:
//	int m_bmpSizeX;			//n byte
//	int m_bmpSizeY;

	int m_pictureSizeX;		//n dot
	int m_pictureSizeY;
//	int m_patternSizeX;		//n dot
//	int m_patternSizeY;
//	int m_patternKosuuX;
//	int m_patternKosuuY;


	LPVOID m_pic0;
	LPVOID m_pic;
	SSIZE_T m_picBufferSize;

//	char* m_antiMask;
//	int m_antiMaskSize;

	char* m_maskPic;
	char* m_maskPic0;
	int m_maskSize;

	LPVOID m_palette0;
	LPVOID m_palette;
	BOOL m_256Flag;

//	int m_defaultPutX;
//	int m_defaultPutY;
//	BOOL m_defaultTransFlag;

//	BOOL m_antiAliasFlag;	//old
//	BOOL m_antiType2Flag;	//old

	BOOL m_maskExistFlag;	//new


//	int m_screenStartX;
//	int m_screenStartY;
//	int m_screenEndX;
//	int m_screenEndY;

	int m_yStart;
	int m_dy;
	int m_readX;
	int m_dwqSize;
	BOOL m_loadOkFlag;

//	BOOL m_dwqFlag;
	BOOL m_jpegFlag;
	BOOL m_maskFlag;
	BOOL m_packFlag;
	BOOL m_pngFlag;

	BOOL m_alreadyCutFlag;

	BOOL m_packFileFlag;
	int m_restReadSize;

	char m_fileName[256];
//	char m_antifileName[256];
	char m_makedFileName[256];

	char m_dwq[64];
	void Genshoku16(void);

	BITMAPFILEHEADER m_bmf;
	BITMAPINFOHEADER m_bmi;

	int LoadBitmapHeaderAndPalette(FILE* file,int* rgbTable,BOOL b256Flag = FALSE);
	int LoadDWQHeader(FILE* file);
	BOOL MakeDataBuffer(SSIZE_T sz);
//	BOOL LoadBitmapData(FILE* file,int* rgbTable,BOOL b256Flag);
	BOOL LoadDWQData(FILE* file,int* rgbTable, BOOL b256Flag = FALSE);
	BOOL LoadPackedDWQData(FILE* file, int* rgbTable, BOOL b256Flag = FALSE);
	void CalcuReadPara(void);
	BOOL LoadMask(FILE* file);
	BOOL GetPngMask(void);

	void CutDataByMask(void);
	void Toumeika(void);

	void PrintLoadError(LPSTR filename);
	void SetMaskExist(BOOL flg = TRUE);

	void InitWork(void);
	BOOL CreateMaskBuffer(int sz);

	FILE* OpenDWQFile(LPSTR fullFileName,LPSTR filename);

	LPVOID m_texture;
};


#endif
/*_*/

