//
// jpegdecoder.h
//

#if !defined __TINYAN_NYANLIB_PICTURE_JPEGDECODER__
#define __TINYAN_NYANLIB_PICTURE_JPEGDECODER__

class CPicture;
class CJpegDecoder
{
public:
	CJpegDecoder();
	~CJpegDecoder();
	void End(void);

	BOOL Decode(char* pJpegData, CPicture* lpPicture);
	static void InitStaticData(void);
	static void ReleaseStaticData(void);

	static short* m_yuvBuffer;
	static short* m_yuvBuffer0;
	static short m_aanscales[];
	static int m_gyakuTable[];
	static int m_dqtGyakuTable[];
	static int m_dctWork[];
	static int m_work[];

	static short m_DQTTable[];

	static int m_huffmanDecodedBuffer[];
//	static int m_rgbBuffer[64*4];
	static int* m_rgbBuffer;
	static int* m_rgbBuffer0;
	static short* m_pad0;

	static BOOL m_calcuFloatFlag;

	static void SetCalcuFloat(BOOL flg = TRUE){m_calcuFloatFlag = flg;}
	float m_aanScalesFloat[64];

private:
	char* HuffmanSearchCommand(char* dataptr, int maxDataSize);

	int HuffmanDecode(char* srcData, int bitNokori, int* dstBuffer, int block = 1);
	BOOL IDCTFastMMX(int* srcData, short* dstBuffer, short* dctTable, int block = 1);
	BOOL YUV2RGB(short* yuvBuffer, int* rgbBuffer);


	BOOL IDCTFastFloat(int* srcData, float* dstBuffer, short* dctTable, int block = 1);
	BOOL YUV2RGBFloat(float* yuvBuffer, int* rgbBuffer);



	void EMMSRoutine(void);
	int GetWORDData(char* jpegPtr);
	int GetBYTEData(char* jpegPtr);
	int GetDQT(char* pDQT);
	int GetDHT(char* pDHT);

	BOOL DecodeMain(char* pJpegData, CPicture* lpPicture);

	int m_markerSize;	//not used

	int m_picSizeX;
	int m_picSizeY;

	int m_oldDCY;
	int m_oldDCU;
	int m_oldDCV;

	static int m_yuvDQTTableNumber[256];	//3‚Å‚¢‚¢‚Í‚¸

	static int m_huffLengthTable[4][256];
	static int m_huffCodeTable[4][256];
	static int m_huffHenkanTable[4][256+16];
	static int m_huffCalcuTable[4][256*2];

	void UVFact4(short* ptr);
	void UVFact4Float(float* ptr);

	char m_hufferr;
};


#endif
/*_*/

