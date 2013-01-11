#if !defined __NYANPICTURELIB_PNGLOADER__
#define __NYANPICTURELIB_PNGLOADER__


class CPngLoader
{
public:
	CPngLoader(int bufferSizeMegaByte = 4);
	~CPngLoader();
	void End(void);


	BOOL LoadFile(FILE* file);
	BOOL LoadFile(LPSTR filename);

	SIZE GetPicSize(void){return m_picSize;}
	BOOL GetMaskFlag(void){return m_maskFlag;}

	void GetPicData(int* lpPic);
	void GetMaskData(char* lpMask);

	static BOOL m_gammaAdjustFlag;

private:
	unsigned char* m_buffer;
	int m_bufferSize;
	SIZE m_picSize;
	BOOL m_maskFlag;

	int* m_tmpPic;

	unsigned char** m_imagePointer;
	int m_imagePointerKosuu;

	int m_seibun;
	int m_depth;
	int m_colorType;

	void ReCreateBuffer(int needSize);
	void ReCreateImagePointer(int height);

	unsigned char* m_paletteBuffer;
	int* m_paletteTable;

	void GetPicDataWithPalette(int* lpPic);
	BOOL m_gammaExistFlag;
	double m_gamma;

	BOOL m_transExistFlag;
	unsigned short m_transGrayColor;
	unsigned char m_transGrayColor1;
	unsigned char m_transGrayColor2;
	unsigned short m_transRedColor;
	unsigned char m_transRedColor1;
	unsigned char m_transRedColor2;
	unsigned short m_transGreenColor;
	unsigned char m_transGreenColor1;
	unsigned char m_transGreenColor2;
	unsigned short m_transBlueColor;
	unsigned char m_transBlueColor1;
	unsigned char m_transBlueColor2;

	unsigned char m_transPalette[256];
};


#endif
/*_*/

