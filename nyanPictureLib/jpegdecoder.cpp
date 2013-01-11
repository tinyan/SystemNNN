//
// jpegdecoder.cpp	JFIF YUV1:1:1最高画質(Photoshop)にのみ対応
//


#include <windows.h>
#include <math.h>

#include "..\nyanlib\include\commonmacro.h"
#include "..\nyanlib\include\picture.h"

#include "jpegdecoder.h"

short* CJpegDecoder::m_yuvBuffer = NULL;
short* CJpegDecoder::m_yuvBuffer0 = NULL;
int* CJpegDecoder::m_rgbBuffer = NULL;
int* CJpegDecoder::m_rgbBuffer0 = NULL;



BOOL CJpegDecoder::m_calcuFloatFlag = FALSE;

#define JPEG_SOI 0xD8
#define JPEG_EOI 0xD9
#define JPEG_APP0 0xE0
#define JPEG_DQT 0xDB
#define JPEG_SOF0 0xC0
#define JPEG_SOF2 0xC2
#define JPEG_DHT 0xC4
#define JPEG_SOS 0xDA
#define JPEG_DRI 0xDD

short CJpegDecoder::m_aanscales[]=
{
	  16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
	  22725, 31521, 29692, 26722, 22725, 17855, 12299,  6270,
	  21407, 29692, 27969, 25172, 21407, 16819, 11585,  5906,
	  19266, 26722, 25172, 22654, 19266, 15137, 10426,  5315,
	  16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520,
	  12873, 17855, 16819, 15137, 12873, 10114,  6967,  3552,
	   8867, 12299, 11585, 10426,  8867,  6967,  4799,  2446,
	   4520,  6270,  5906,  5315,  4520,  3552,  2446,  1247,
};

int CJpegDecoder::m_gyakuTable[]=
{
	0*4,1*4,5*4,6*4,14*4,15*4,27*4,28*4,
	2*4,4*4,7*4,13*4,16*4,26*4,29*4,42*4,
	3*4,8*4,12*4,17*4,25*4,30*4,41*4,43*4,
	9*4,11*4,18*4,24*4,31*4,40*4,44*4,53*4,
	10*4,19*4,23*4,32*4,39*4,45*4,52*4,54*4,
	20*4,22*4,33*4,38*4,46*4,51*4,55*4,60*4,
	21*4,34*4,37*4,47*4,50*4,56*4,59*4,61*4,
	35*4,36*4,48*4,49*4,57*4,58*4,62*4,63*4,
};

int CJpegDecoder::m_dqtGyakuTable[]=
{
	0,1,8,16,9,2,3,10,
	17,24,32,25,18,11,4,5,
	12,19,26,33,40,48,41,34,
	27,20,13,6,7,14,21,28,
	35,42,49,56,57,50,43,36,
	29,22,15,23,30,37,44,51,
	58,59,52,45,38,31,39,46,
	53,60,61,54,47,55,62,63
};


int CJpegDecoder::m_dctWork[64] = {0};

int CJpegDecoder::m_work[64] = {0};

short CJpegDecoder::m_DQTTable[64*16] = {0};	//普通は64*(2+1)で十分

int CJpegDecoder::m_huffmanDecodedBuffer[64*6] = {0};




int CJpegDecoder::m_yuvDQTTableNumber[256] = {0};	//3でいいはず

int CJpegDecoder::m_huffLengthTable[4][256] = {0};
int CJpegDecoder::m_huffCodeTable[4][256] = {0};
int CJpegDecoder::m_huffHenkanTable[4][256+16] = {0};
int CJpegDecoder::m_huffCalcuTable[4][256*2] = {0};

short* CJpegDecoder::m_pad0 = NULL;

CJpegDecoder::CJpegDecoder()
{
	double p = 3.14159265358979;
	for (int j=0;j<8;j++)
	{
		float aj = 1.0f;

		if (j>0)
		{
			aj = (float)(cos(j*p/16) * sqrt(2.0)) * 1.0f;
		}

		for (int i=0;i<8;i++)
		{
			float ai = 1.0f;

			if (i>0)
			{
				ai = (float)(cos(i*p/16) * sqrt(2.0)) * 1.0f;
			}

			m_aanScalesFloat[j*8+i] = ai * aj /8.0f;

//			char mes[1024];
//			wsprintf(mes,"[%d] ",(int)(ai*aj*16384.0f));
//			OutputDebugString(mes);
		}
//OutputDebugString("\n");
	}

}


CJpegDecoder::~CJpegDecoder()
{
	End();
}


void CJpegDecoder::End(void)
{
}


BOOL CJpegDecoder::Decode(char* pJpegData,CPicture* lpPicture)
{
	if (lpPicture == NULL) return FALSE;
	if (m_yuvBuffer == NULL) return FALSE;

	char* jpegPtr = pJpegData;

	m_markerSize = 0;
//static int tmflag = 0;

	BOOL myTrue = TRUE;

	while (myTrue)
	{
		jpegPtr = HuffmanSearchCommand(jpegPtr,0);

		int cmd = GetBYTEData(jpegPtr);
//		int cmd = (int)*jpegPtr;
//		cmd &= 0xff;
		jpegPtr++;

		if (cmd == JPEG_EOI) break;
		if (cmd == JPEG_SOI) continue;

		int k;
		int sz;

		int i;

		switch(cmd)
		{
		case JPEG_APP0:	//nothing to do(SKIP)
			break;
		case JPEG_DQT:
			k = GetWORDData(jpegPtr) - 2;
			sz = 0;
			while (sz<k)
			{
				sz += GetDQT(jpegPtr+2+sz);
			}
			break;
		case JPEG_DHT:
			k = GetWORDData(jpegPtr) - 2;
			sz = 0;
			while (sz<k)
			{
				sz += GetDHT(jpegPtr+2+sz);
			}
			break;
		case JPEG_DRI:
			m_markerSize = GetWORDData(jpegPtr+2);
			break;
		case JPEG_SOF0:


			m_picSizeX = GetWORDData(jpegPtr+5);
			m_picSizeY = GetWORDData(jpegPtr+3);


			//サンプリングファクター無視


			for (i=0;i<3;i++)	//モノクロ非対応
			{
//				int type = GetBYTEData(jpegPtr+8+0+i*3);
				int hv = GetBYTEData(jpegPtr+8+1+i*3);

				m_yuvDQTTableNumber[i*3+0] = hv >> 4;
				m_yuvDQTTableNumber[i*3+1] = hv & 0xf;
				m_yuvDQTTableNumber[i*3+2] = GetBYTEData(jpegPtr+8+2+i*3);

			}

//			m_yuvDQTTableNumber[GetBYTEData(jpegPtr+8+0)-1] = GetBYTEData(jpegPtr+8+2+0);
//			m_yuvDQTTableNumber[GetBYTEData(jpegPtr+8+3)-1] = GetBYTEData(jpegPtr+8+2+3);
//			m_yuvDQTTableNumber[GetBYTEData(jpegPtr+8+6)-1] = GetBYTEData(jpegPtr+8+2+6);

			//resize pic ひつようなら
			if (lpPicture->ReSize(m_picSizeX,m_picSizeY) == FALSE)
			{
//OutputDebugString("Resize Error in CJpegDecoder");
			}
			else
			{
//OutputDebugString("[ResizeOk]");
			}

			break;
		case JPEG_SOS:
			BOOL b;

			b = DecodeMain(jpegPtr,lpPicture);


			EMMSRoutine();

//	if (m_hufferr != 0)
//	{
//		char mes[256];
//		sprintf_s(mes,256,"FF %d",(int)m_hufferr);
//		MessageBox(NULL,mes,"JPEG_??",MB_OK);
//	}

			return b;
			break;

		default:	//unknown
			break;
		}

		jpegPtr += GetWORDData(jpegPtr);
	}


	return TRUE;
}



BOOL CJpegDecoder::DecodeMain(char* pJpegData, CPicture* lpPicture)
{
	int i,j;
//static int tmflag = 0;

	m_oldDCY = 0;
	m_oldDCU = 0;
	m_oldDCV = 0;

	short* yuvBuffer = m_yuvBuffer;
	float* yuvBufferFloat = (float*)m_yuvBuffer;

	int ns = GetBYTEData(pJpegData + 2);
	int csi[4];
	for (i=0;i<ns;i++)
	{
		int k = GetBYTEData(pJpegData + 3+i*2) - 1;
//		if ((k<0) || (k>3))
//		{
//			MessageBox(NULL,"csi","error",MB_OK);
//		}

		csi[k] = GetBYTEData(pJpegData + 3+i*2+1);
	}


//	int ss = GetBYTEData(pJpegData + 3+ns*2);
//	int se = GetBYTEData(pJpegData + 3+ns*2+1);
//	int ahal = GetBYTEData(pJpegData + 3+ns*2);
//	int ah = (ahal >> 4) & 0xf;
//	int al = ahal & 0xf;

	int loopX = (m_picSizeX + 7) / 8;
	int loopY = (m_picSizeY + 7) / 8;

	pJpegData += GetWORDData(pJpegData);
	int bitPlace = 0;

	int* dst = (int*)(lpPicture->GetBuffer());
#if defined _TINYAN3DLIB_
	dst += 128 / sizeof(int);
#endif

	RECT rc;
	lpPicture->GetPicSize(&rc);

	int lPitch = rc.right;

	int* dst0 = dst;

	int mcuKosuu = 0;



	int picSizeX = m_picSizeX;
	int picSizeY = m_picSizeY;


	int sampleFactX = m_yuvDQTTableNumber[0*3];
	int sampleFactY = m_yuvDQTTableNumber[0*3+1];
	int sampleBlock = sampleFactX * sampleFactY;

	int blockX = (loopX + sampleFactX-1) / sampleFactX;
	int blockY = (loopY + sampleFactY-1) / sampleFactY;




//	for (j=0;j<loopY;j++)
	for (j=0;j<blockY;j++)
	{
		dst = dst0;

//		for (i=0;i<loopX;i++)
		for (i=0;i<blockX;i++)
		{



			if (m_markerSize > 0)
			{
				if (mcuKosuu == m_markerSize)
				{
					bitPlace = 0;

					BOOL bf = FALSE;
					while (bf == FALSE)
					{
						char c = *pJpegData;
						if (c == (char)0xff)
//						if (c == 0xff)
						{
							pJpegData++;
							char c2 = *pJpegData;
							if (c2 != 0)
							{
								pJpegData++;
								bf = TRUE;
								break;
							}
						}
						pJpegData++;
					}




					m_oldDCY = 0;
					m_oldDCU = 0;
					m_oldDCV = 0;

					mcuKosuu = 0;
				}
			}

			int rt = HuffmanDecode(pJpegData,bitPlace,m_huffmanDecodedBuffer,1);






			if (rt == -1) return FALSE;

			int delta = rt >>3;
			bitPlace = rt & 0x7;
			pJpegData += delta;



			//idct


			if (m_calcuFloatFlag == FALSE)
			{
				for (int pp=0;pp<sampleBlock;pp++)
				{
					IDCTFastMMX(m_huffmanDecodedBuffer+64*pp,yuvBuffer+pp*64*3,&m_DQTTable[m_yuvDQTTableNumber[0*3+2]*64]);
				}

				IDCTFastMMX(m_huffmanDecodedBuffer+sampleBlock*64,yuvBuffer+64,&m_DQTTable[m_yuvDQTTableNumber[1*3+2]*64]);
				IDCTFastMMX(m_huffmanDecodedBuffer+sampleBlock*64+64,yuvBuffer+64*2,&m_DQTTable[m_yuvDQTTableNumber[2*3+2]*64]);


				//YUV 4:1:1
				if (sampleBlock>1)
				{
					UVFact4(yuvBuffer);
					//
				}


				//yuv->rgb

				//
				for (int ppp=0;ppp<sampleBlock;ppp++)
				{
					YUV2RGB(yuvBuffer+ppp*64*3,m_rgbBuffer+ppp*64);
				}
			}
			else
			{
				for (int pp=0;pp<sampleBlock;pp++)
				{
					IDCTFastFloat(m_huffmanDecodedBuffer+64*pp,yuvBufferFloat+pp*64*3,&m_DQTTable[m_yuvDQTTableNumber[0*3+2]*64]);
				}

				IDCTFastFloat(m_huffmanDecodedBuffer+sampleBlock*64,yuvBufferFloat+64,&m_DQTTable[m_yuvDQTTableNumber[1*3+2]*64]);
				IDCTFastFloat(m_huffmanDecodedBuffer+sampleBlock*64+64,yuvBufferFloat+64*2,&m_DQTTable[m_yuvDQTTableNumber[2*3+2]*64]);


				//YUV 4:1:1
				if (sampleBlock>1)
				{
					UVFact4Float(yuvBufferFloat);
					//
				}


				//yuv->rgb

				//
				for (int ppp=0;ppp<sampleBlock;ppp++)
				{
					YUV2RGBFloat(yuvBufferFloat+ppp*64*3,m_rgbBuffer+ppp*64);
				}

			}




			for (int py=0;py<sampleFactY;py++)
			{
				for (int px=0;px<sampleFactX;px++)
				{
					int psizex = 8;
					int psizey = 8;

					int ex = (i*sampleFactX+px)*8+8;
					int ey = (j*sampleFactY+py)*8+8;

					if (ex>picSizeX)
					{
						psizex = picSizeX - (ex-8);
					}

					if (ey>picSizeY)
					{
						psizey = picSizeY - (ey-8);
					}

					int* rgbBuffer = m_rgbBuffer + (px+py*2)*64;
					int* rgbBuffer0 = rgbBuffer;

					int* dstdst = dst + px*8 + py*lPitch*8;
					int* dstdst0 = dstdst;
	
					for (int jj=0;jj<psizey;jj++)
					{
						rgbBuffer = rgbBuffer0;
						dstdst = dstdst0;

						for (int ii=0;ii<psizex;ii++)
						{
							*dstdst = *rgbBuffer;	//このへんがおかしいにゃ＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠＠
							dstdst++;
							rgbBuffer++;
						}

						rgbBuffer0 += 8;
						dstdst0 += lPitch;
					}
				}
			}


//			for (int jj=0;jj<psizey;jj++)
//			{
//				for (int ii=0;ii<psizex;ii++)
//				{
//					int dt = *(m_rgbBuffer+ii+jj*8);
//					*(dst+ii+jj*lPitch) = dt;
//				}
//			}

			dst += 8*sampleFactX;
			mcuKosuu++;
		}

		dst0 += lPitch*8*sampleFactY;
	}

	return TRUE;
}


void CJpegDecoder::UVFact4(short* ptr)
{
	int sampleFactX = m_yuvDQTTableNumber[0*3];
	int sampleFactY = m_yuvDQTTableNumber[0*3+1];
//	int sampleBlock = sampleFactX * sampleFactY;

	int miniX = 8 / sampleFactX;
	int miniY = 8 / sampleFactY;

	for (int uv=0;uv<2;uv++)
	{
		for (int y=sampleFactY-1;y>=0;y--)
		{
			for (int x=sampleFactX-1;x>=0;x--)
			{
				short* src = ptr + 64 + uv*64 + x * miniX + y * 8*miniY;
				short* dst = ptr + 64 + uv*64 + (x+y*sampleFactX)*64*3;

				for (int j=miniY-1;j>=0;j--)
				{
					for (int i=miniX-1;i>=0;i--)
					{
						short d = *(src+i+j*8);

						for (int jj=0;jj<sampleFactY;jj++)
						{
							for (int ii=0;ii<sampleFactX;ii++)
							{
								*(dst + i*sampleFactX+ii+(j*sampleFactY+jj)*8) = d;
//						*(dst + i*2+1+j*2*8) = d;
//						*(dst + i*2+(j*2+1)*8) = d;
//						*(dst + i*2+1+(j*2+1)*8) = d;
							}
						}
					}
				}
			}
		}
	}
}


int CJpegDecoder::GetWORDData(char* jpegPtr)
{
	int high = *jpegPtr;
	int low = *(jpegPtr+1);
	high &= 0xff;
	low &= 0xff;

	return (high<<8) | low;
}

int CJpegDecoder::GetBYTEData(char* jpegPtr)
{
	int dat = *jpegPtr;
	dat &= 0xff;

	return dat;
}


//8bitにのみ対応
int CJpegDecoder::GetDQT(char* pDQT)
{
	int k = 0;

//	int tableNumber = GetBYTEData(pDQT+k) & 0xf;
	int cc = GetBYTEData(pDQT+k);

	int tableNumber = cc & 0x3;	//0-3
	int bitType = cc >> 4;

	k++;

	short* table = m_DQTTable + 64 * tableNumber;

	for (int i=0;i<64;i++)
	{
		int gyaku = m_dqtGyakuTable[i];
		if (bitType == 0)
		{
			int d = GetBYTEData(pDQT+k);
			table[gyaku] = (short)d;
			k++;
		}
		else
		{
			int d = GetWORDData(pDQT+k);
			table[gyaku] = (short)d;
			k += 2;
		}

//		if (d == 0xff)	//やってはいけない???
//		{
//			k++;
//		}
	}
	return k;
}


int CJpegDecoder::GetDHT(char* pDHT)
{
	int d = GetBYTEData(pDHT);

	int dcac = (d >> 4) & 0xf;
	int yuv = d & 0xf;

	int tableNumber = dcac * 2 + yuv;



	int kosuu = 0;
	int k=0;
	int cd = 0;
	int i = 0;
	for (i=0;i<16;i++)
	{
		int ln = GetBYTEData(pDHT+1+i);

		m_huffHenkanTable[tableNumber][i] = k;

		if (ln > 0)
		{
			m_huffCalcuTable[tableNumber][i*2] = cd;
			for (int j=0;j<ln;j++)
			{
				m_huffLengthTable[tableNumber][k] = i+1;
				m_huffCodeTable[tableNumber][k] = cd;

				cd++;
				k++;
			}
			m_huffCalcuTable[tableNumber][i*2+1] = cd;
		}
		else
		{
			m_huffCalcuTable[tableNumber][i*2] = -1;
			m_huffCalcuTable[tableNumber][i*2+1] = 0;
		}

		cd <<= 1;
		kosuu += ln;
	}

	for (i=0;i<kosuu;i++)
	{
		m_huffHenkanTable[tableNumber][16+i] = GetBYTEData(pDHT+1+16+i);
	}

	return 1+16+kosuu;
}


void CJpegDecoder::InitStaticData(void)
{
	if (m_yuvBuffer == NULL)
	{
		m_yuvBuffer0 = new short[8*8*(1280/8)*2 + 8];
		int p = (int)m_yuvBuffer0;
		p += 7;
		p &= ~7;

		m_yuvBuffer = (short*)p;
	}

	if (m_rgbBuffer == NULL)
	{
		m_rgbBuffer0 = new int[64*4+8];
		int p = (int)m_rgbBuffer0;
		p += 7;
		p &= ~7;

		m_rgbBuffer = (int*)p;
	}

}


void CJpegDecoder::ReleaseStaticData(void)
{
	if (m_yuvBuffer != NULL)
	{
		DELETEARRAY(m_yuvBuffer0);
		m_yuvBuffer = NULL;
	}

	if (m_rgbBuffer != NULL)
	{
		DELETEARRAY(m_rgbBuffer0);
		m_rgbBuffer = NULL;
	}
}


BOOL CJpegDecoder::YUV2RGB(short* yuvBuffer, int* rgbBuffer)
{
	LONGLONG const_0080 = 0x0080008000800080;
	LONGLONG const_0200 = 0x0200020002000200;

	LONGLONG fix_1402 = 0x059ba59ba59ba59ba;
	LONGLONG fix_n714 = 0x0d24dd24dd24dd24d;
	LONGLONG fix_n344 = 0x0e9fbe9fbe9fbe9fb;
	LONGLONG fix_1772 = 0x07168716871687168;

	LONGLONG tempRRRRRRRR;
	LONGLONG tempGGGGGGGG;
/*
#if defined _DEBUG
static int aaa = 0;
if (aaa == 0)
{
	aaa = 1;
	OutputDebugString("\n\nYUV DATA\n\n");
	short* dmy = yuvBuffer;
	for (int jj=0;jj<8;jj++)
	{
		for (int ii=0;ii<8;ii++)
		{
			short yy = *(dmy+ii+jj*8);
			short uu = *(dmy+ii+jj*8+64);
			short vv = *(dmy+ii+jj*8+64*2);

			char mes[256];
			wsprintf(mes,"[%d %d %d] ",(int)yy,(int)uu,int(vv));
			OutputDebugString(mes);
		}
		OutputDebugString("\n");
	}
}
#endif
*/
	short* src = yuvBuffer;
	int* dst = rgbBuffer;
	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov ebx,src
		mov edi,dst
		
		mov esi,ebx
		mov edx,ebx

		add esi,8*8*2
		add edx,8*8*2*2

		mov ecx,8
LOOP1:
		movq mm7,const_0080

		movq mm2,[ebx]	//Y1
		movq mm4,[edx]	//V1
		add ebx,8
		add edx,8

		movq mm3,[ebx]	//Y2
		movq mm5,[edx]	//V2
		psubw mm4,mm7
		add ebx,8
		psubw mm5,mm7
		add edx,8
//		movq mm4,[esi]	//U1
//		add esi,8
//		movq mm5,[esi]	//U2
//		add esi,8



//push eax
//mov eax,007f007fh
//movd mm4,eax
//punpckldq mm4,mm4
//movq mm5,mm4
//pop eax


//pxor mm4,mm4
//pxor mm5,mm5

		psllw mm4,2
		movq mm0,fix_1402
	
		psllw mm5,2
		movq mm1,mm0

		pmulhw mm0,mm4
		pmulhw mm1,mm5

		movq mm7,const_0200

		paddw mm0,mm2
		paddw mm1,mm3


		paddw mm0,mm7
		paddw mm1,mm7
		psubusw mm0,mm7
		psubusw mm1,mm7

		packuswb mm0,mm1
		movq mm7,fix_n714

		movq tempRRRRRRRR,mm0

		pmulhw mm4,mm7
		pmulhw mm5,mm7
		movq mm7,const_0080

		paddw mm4,mm2
		paddw mm5,mm3


		movq mm0,[esi]		//U1
		add esi,8

		movq mm1,[esi]		//U2
		add esi,8
//		movq mm0,[edx]		//V1
//		add edx,8
//		movq mm1,[edx]		//V2
//		add edx,8




		psubw mm0,mm7
		psubw mm1,mm7

//pxor mm0,mm0
//pxor mm1,mm1

		psllw mm0,2
		psllw mm1,2



		movq mm6,fix_n344
		movq mm7,mm6

		pmulhw mm6,mm0
		pmulhw mm7,mm1

		//;stall

		paddw mm4,mm6
		paddw mm5,mm7


		movq mm7,const_0200

		paddw mm4,mm7
		paddw mm5,mm7
		psubusw mm4,mm7
		psubusw mm5,mm7


		packuswb mm4,mm5
		movq tempGGGGGGGG,mm4



		movq mm4,fix_1772
		movq mm5,mm4

		pmulhw mm4,mm0
		pmulhw mm5,mm1

		movq mm7,const_0200

		paddw mm4,mm2
		paddw mm5,mm3




		paddw mm4,mm7
		paddw mm5,mm7
		psubusw mm4,mm7
		psubusw mm5,mm7

		packuswb mm4,mm5		//BBBBBBBB

		



		pxor mm7,mm7

		movq mm1,mm4
		movq mm3,mm4

		punpcklbw mm1,mm7
		punpckhbw mm3,mm7

		movq mm5,tempGGGGGGGG

		movq mm2,mm1
		movq mm4,mm3
		punpcklwd mm1,mm7
		punpckhwd mm2,mm7
		punpcklwd mm3,mm7
		punpckhwd mm4,mm7

//		pslld mm1,16
//		pslld mm2,16
//		pslld mm3,16
//		pslld mm4,16


		movq mm6,mm5
		punpcklbw mm5,mm7
		punpckhbw mm6,mm7

		movq mm0,mm5
		punpcklwd mm0,mm7
		punpckhwd mm5,mm7
		pslld mm0,8
		pslld mm5,8
		por mm1,mm0
		por mm2,mm5

		movq mm0,mm6
		punpcklwd mm0,mm7
		punpckhwd mm6,mm7
		pslld mm0,8
		pslld mm6,8
		por mm3,mm0
		por mm4,mm6


		movq mm5,tempRRRRRRRR
		movq mm6,mm5
		punpcklbw mm5,mm7
		punpckhbw mm6,mm7

		movq mm0,mm5
		punpcklwd mm0,mm7
		punpckhwd mm5,mm7
	pslld mm0,16
	pslld mm5,16
		por mm1,mm0
		por mm2,mm5

		movq mm0,mm6
		punpcklwd mm0,mm7
		punpckhwd mm6,mm7
	pslld mm0,16
	pslld mm6,16
		por mm3,mm0
		por mm4,mm6


//mov eax,0ff0000h
//movd mm0,eax
//punpckldq mm0,mm0
//pand mm1,mm0
//pand mm2,mm0
//pand mm3,mm0
//pand mm4,mm0

		movq [edi],mm1
		add edi,8
		movq [edi],mm2
		add edi,8
		movq [edi],mm3
		add edi,8
		movq [edi],mm4
		add edi,8

///		add ebx,8*2
		dec ecx
		jnz LOOP1



		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
		jmp EXIT0

		emms
EXIT0:
	}

	return TRUE;
}



void CJpegDecoder::EMMSRoutine(void)
{
	__asm
	{
		emms
	}
}





/*
;
; jdcolorm.asm for width = 64*x only
;
; MMXをつかって 16x2 dot のブロックごとに変換する
;

BITS 32
SECTION .text



global yuv_rgb_convert_mmx


yuv_rgb_convert_mmx:
	
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp

	mov esi,[esp+4+24]
	mov ebx,[esp+8+24]
	mov edx,[esp+12+24]
	mov edi,[esp+16+24]

	mov ecx,16/2
LOOP1:
	push ecx
	push esi
	push edi

	mov ecx,320/16
LOOP2:
	push ecx

	movq mm4,[ebx]			;U(0123)
	movq mm5,mm4
	punpcklwd mm4,mm4		;U(0011)
	punpckhwd mm5,mm5		;U(2233)
	psubw mm4,[const_0080]
	psubw mm5,[const_0080]
	psllw mm4,2
	psllw mm5,2
	movq [TEMPU],mm4
	movq [TEMPU+8],mm5


	movq mm2,[edx]			;V(0123)
	movq mm3,mm2
	punpcklwd mm2,mm2		;V(0011)
	punpckhwd mm3,mm3		;V(2233)
	psubw mm2,[const_0080]
	psubw mm3,[const_0080]
	psllw mm2,2
	psllw mm3,2
	movq [TEMPV],mm2
	movq [TEMPV+8],mm3

	movq mm4,[ebx+8]		;U(4567)
	movq mm5,mm4
	punpcklwd mm4,mm4		;U(4455)
	punpckhwd mm5,mm5		;U(6677)
	psubw mm4,[const_0080]
	psubw mm5,[const_0080]
	psllw mm4,2
	psllw mm5,2
	movq [TEMPU+16],mm4
	movq [TEMPU+24],mm5


	movq mm2,[edx+8]		;V(4567)
	movq mm3,mm2
	punpcklwd mm2,mm2		;V(4455)
	punpckhwd mm3,mm3		;V(6677)
	psubw mm2,[const_0080]
	psubw mm3,[const_0080]
	psllw mm2,2
	psllw mm3,2
	movq [TEMPV+16],mm2
	movq [TEMPV+24],mm3




	movq mm2,[TEMPU]
	movq mm3,[TEMPU+8]
	movq mm4,[TEMPV]
	movq mm5,[TEMPV+8]
	call calcusub

	add esi,8*2
	add edi,3*8
	movq mm2,[TEMPU+16]
	movq mm3,[TEMPU+24]
	movq mm4,[TEMPV+16]
	movq mm5,[TEMPV+24]
	call calcusub

	add esi,320*2-8*2
	add edi,320*3-3*8
	movq mm2,[TEMPU]
	movq mm3,[TEMPU+8]
	movq mm4,[TEMPV]
	movq mm5,[TEMPV+8]
	call calcusub

	add esi,8*2
	add edi,3*8
	movq mm2,[TEMPU+16]
	movq mm3,[TEMPU+24]
	movq mm4,[TEMPV+16]
	movq mm5,[TEMPV+24]
	call calcusub

	add esi,-320*2-8*2 + 8*4
	add edi,-320*3-3*8 + 3*16

	add ebx,16
	add edx,16
	pop ecx
	dec ecx
	jnz near LOOP2

	pop edi
	pop esi
	pop ecx

	add esi,320*2*2
	add edi,320*3*2
	dec ecx
	jnz near LOOP1

	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	ret


calcusub:
	pxor mm7,mm7

	movq mm0,[esi]			;Y(0-3)
	movq mm1,[esi+8]		;Y(4-7)

	movq mm6,mm4
	pmulhw mm6,[fix_1402]

	movq mm7,mm5
	pmulhw mm7,[fix_1402]

	paddw mm6,mm0
	;stall
	paddw mm7,mm1

	paddw mm6,[const_0200]
	paddw mm7,[const_0200]

	psubusw mm6,[const_0200]
	psubusw mm7,[const_0200]

	packuswb mm6,mm7
	movq [tmp],mm6				;RRRRRRRR

	pmulhw mm4,[fix_n714]
	movq mm6,mm2

	pmulhw mm5,[fix_n714]
	movq mm7,mm3

	pmulhw mm6,[fix_n344]
	pmulhw mm7,[fix_n344]

	pmulhw mm2,[fix_1772]
	paddw mm6,mm4


	pmulhw mm3,[fix_1772]
	paddw mm7,mm5

	paddw mm6,mm0
	paddw mm7,mm1

	movq mm5,[const_0200]

	paddw mm6,mm5
	paddw mm7,mm5

	psubusw mm6,mm5
	psubusw mm7,mm5

	packuswb mm6,mm7		;GGGGGGGG





	paddw mm2,mm0
	paddw mm3,mm1




	paddw mm2,mm5
	paddw mm3,mm5

	psubusw mm2,mm5
	psubusw mm3,mm5

	packuswb mm2,mm3		;BBBBBBBB


	movq mm0,[tmp]
	movq mm1,mm6



;	mm0 mm1 mm2 RRRRRRRR GGGGGGGG BBBBBBBB

	
	movq mm3,mm2
	movq mm4,mm2

	punpcklbw mm3,mm1	;BGBGBGBG(0-3)
	movq mm5,mm0

	punpckhbw mm4,mm1	;BGBGBGBG(4-7)
	movq mm6,mm0

	punpcklbw mm5,mm5	;R*R*R*R*(0-3)
	punpckhbw mm6,mm6	;R*R*R*R*(4-7)

	movq mm7,mm3
	punpcklwd mm3,mm5	;BGR*BGR*(0-1)

	movq mm1,mm4
	punpckhwd mm7,mm5	;BGR*BGR*(2-3)

	punpcklwd mm4,mm6	;BGR*BGR*(4-5)

	punpckhwd mm1,mm6	;BGR*BGR*(6-7)

;	mm3 mm7 mm4 mm1 BGR*BGR* 0-1,2-3,4-5,6-7

	movq mm2,mm3	;BGR*BGR* (0-1)

	movq mm0,mm7						;BGR0BGR0 (2-3)
	pand mm3,[mask_00FFFFFF00000000]	;0000BGR0 (1)

	pand mm2,[mask_0000000000FFFFFF]	;BGR00000 (0)
	psrlq mm3,8							;000BGR00 (1)

	psllq mm0,48						;000000BG (2)
	por mm2,mm3							;BGRBGR00 (0-1)


	por mm2,mm0							;BGRBGRBG(0-1,2)

	movq [edi],mm2

;	* mm7 mm4 mm1 RGBB	* 2-3,4-5,6-7


	movq mm6,mm7						;BGR0BGR0 (2-3)

	movq mm3,mm4						;BGR0BGR0 (4-5)
	pand mm6,[mask_0000000000FF0000]	;00R00000 (2)

	movq mm5,mm4						;BGR0BGR0 (4-5)
	pand mm7,[mask_00FFFFFF00000000]	;0000BGR0 (3)
	 
	psrlq mm6,16						;R0000000 (2)
	pand mm3,[mask_0000000000FFFFFF]	;BGR00000 (4)

	psrlq mm7,24						;0BGR0000 (3)
	pand mm5,[mask_000000FF00000000]	;0000B000 (5)

	psllq mm3,32						;0000BGR0 (4)
	por mm6,mm7							;RBGR0000 (2,3)
	
	psllq mm5,24						;0000000B (5)
	por mm3,mm6							;RBGRBGR0 (2,3-4)

	por mm3,mm5							;RBGRBGRB (2,3-4,5)

	movq [edi+8],mm3

;	* * mm4 mm1 RGBB * * 4-5,6-7

	pand mm4,[mask_00FFFF0000000000]	;00000GR0 (5)

	movq mm5,mm1

	pand mm1,[mask_0000000000FFFFFF]	;BGR00000 (6)
	pand mm5,[mask_00FFFFFF00000000]	;0000BGR0 (7)

	psrlq mm4,40						;GR000000 (5)
	psllq mm1,16						;00BGR000 (6)

	por mm4,mm1							;GRBGR000 (5,6)
	psllq mm5,8							;00000BGR (7)


	por mm4,mm5

	movq [edi+16],mm4

	ret

















SECTION .data

align 32
mask_00FFFFFF00000000 dd 0,00ffffffh
mask_0000000000FFFFFF dd 00ffffffh,0
mask_0000000000FF0000 dd 00ff0000h,0
mask_000000FF00000000 dd 0,000000ffh
mask_00FFFF0000000000 dd 0,00ffff00h

;;fix_1402 dd 42b042b0h,42b042b0h
fix_1402 dd 59ba59bah,59ba59bah
fix_n714 dd 0d24dd24dh,0d24dd24dh
fix_n344 dd 0e9fbe9fbh,0e9fbe9fbh
fix_1772 dd 71687168h,71687168h

const_0080 dd 00800080h,00800080h
;;;const_0080 dd 0,0
const_0200 dd 02000200h,02000200h

TEMPU dd 0,0,0,0,0,0,0,0
TEMPV dd 0,0,0,0,0,0,0,0

dmy_ff dd 0ffffffffh,0ffffffffh
tmp dd 0,0


*/





#define MYSHIFT 4
BOOL CJpegDecoder::IDCTFastMMX(int* srcData, short* dstBuffer, short* dctTable,int block)
{
	if (block)
	{
	}

	int* gyakuTable = m_gyakuTable;
	short* aanscales = m_aanscales;
	int* dctWork = m_dctWork;

	int* work = m_work;

	LONGLONG fix_141 = 0x05a825a825a825a82;
	LONGLONG fix_184 = 0x07642764276427642;
	LONGLONG fix_108 = 0x04646464646464646;
	LONGLONG fix_n261x2 = 0x0ac61ac61ac61ac61;

	LONGLONG const_0080 = 0x0080008000800080;
	LONGLONG const_0010 = 0x0010001000100010;

//	LONGLONG const_MYHALF = 0x0004000400040004;
//	LONGLONG const_MYHALF = 0x0002000200020002;
	LONGLONG const_MYHALF = 0x0008000800080008;

	LONGLONG ans_5 = 0;
	LONGLONG ans_6 = 0;
	LONGLONG ans_7 = 0;

	int tmp = 0;
	void* table = dctTable;
	void* dst = dstBuffer;
	void* src = srcData;

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

//PASS0
		mov ecx,64/4
		mov ebx,gyakuTable
		mov edi,dctWork
		mov esi,src

		mov eax,aanscales
LOOP00:
		push ecx

		mov edx,[ebx+0]
		mov ecx,[edx+esi]
		movd mm0,ecx

		mov edx,[ebx+4]
		mov ecx,[edx+esi]
		movd mm1,ecx

		mov edx,[ebx+8]
		mov ecx,[edx+esi]
		movd mm2,ecx

		mov edx,[ebx+12]
		mov ecx,[edx+esi]
		movd mm3,ecx

		punpcklwd mm0,mm1
		punpcklwd mm2,mm3

		punpckldq mm0,mm2

		psllw mm0,4					//;x16 /2 (AANSCLAES is div 2)
//		psllw mm0,3					//;x16 /2 (AANSCLAES is div 2)

		movq mm7,mm0
		pmulhw mm0,[eax]
		pmullw mm7,[eax]
		psrlw mm7,11
		paddw mm7,const_0010
		psrlw mm7,5
		paddw mm0,mm7


		add ebx,16
		add eax,8
								psraw mm0,1//16bitで計算すると後半でオーバーフローする
		movq [edi],mm0

		add edi,8

		pop ecx
		dec ecx
		jnz LOOP00
/*
emms
	}

#if defined _DEBUG
	static int aaa = 0;
	if (aaa < 3)
	{
		aaa++;
		OutputDebugString("\n\nDCT DATA\n\n");
		short* dmy = (short*)dctWork;
		for (int jj=0;jj<8;jj++)
		{
			for (int ii=0;ii<8;ii++)
			{
				short yy = *(dmy+ii+jj*8);
				short uu = *(dmy+ii+jj*8+64);
				short vv = *(dmy+ii+jj*8+64*2);

				char mes[256];
				wsprintf(mes,"[%d %d %d] ",(int)yy,(int)uu,int(vv));
				OutputDebugString(mes);
			}
			OutputDebugString("\n");
		}

	}
#endif

	_asm{
*/

		mov ecx,2
		mov edi,work
		mov esi,dctWork
		mov ebx,table
// PASS 1

LOOP1:
// Even part 

	movq mm0,[esi+8*2*0]

	pmullw mm0,[ebx+8*2*0]

	movq mm1,[esi+8*2*2]

	pmullw mm1,[ebx+8*2*2]


	movq mm2,[esi+8*2*4]
	movq mm4,mm0

	pmullw mm2,[ebx+8*2*4]
	movq mm5,mm1

	movq mm3,[esi+8*2*6]

	paddw mm0,mm2	//;tmp10 = D0+D4
	pmullw mm3,[ebx+8*2*6]


	psubw mm4,mm2	//;tmp11 = D0-D4
	movq mm6,mm0

	paddw mm5,mm3	//;tmp13 = D2+D6
	psubw mm1,mm3	//;tmp12'= D2-D6


	psllw mm1,2
	pmulhw mm1,fix_141		//tmp12'' = 1.41*(D2-D6)

	paddw mm0,mm5			//;tmp0 = D0+D2+D4+D6

	psubw mm6,mm5			//;tmp3 = D0-D2+D4-D6
	psubw mm1,mm5			//;tmp12 = 1.41*(D2-D6)-D2-D6

	movq [edi+8*2*0],mm0

	movq mm7,mm4
	paddw mm4,mm1			//;tmp1 = tmp11+tmp12

	movq [edi+8*2*3],mm6
	psubw mm7,mm1			//;tmp2 = tmp11-tmp12





;    // Odd part 

	movq mm2,[esi+8*2*5]

	movq [edi+8*2*1],mm4	//;even

	pmullw mm2,[ebx+8*2*5]

	movq mm0,[esi+8*2*1]

	movq [edi+8*2*2],mm7	//;even

	pmullw mm0,[ebx+8*2*1]

	movq mm4,mm2
	movq mm1,[esi+8*2*3]

	pmullw mm1,[ebx+8*2*3]
	movq mm3,[esi+8*2*7]

	movq mm6,mm0
	pmullw mm3,[ebx+8*2*7]


	paddw mm2,mm1	//;z13 = D5+D3
	psubw mm4,mm1	//;z10 = D5-D3

	paddw mm0,mm3	//;z11 = D1+D7
	psubw mm6,mm3	//;z12 = D1-D7


	movq mm7,mm0	//;z11
	psubw mm0,mm2	//;z11-z13

	paddw mm7,mm2		//;tmp7 = z11+z13

	psllw mm0,2			
	pmulhw mm0,fix_141	//;tmp11 = 1.41*(z11-z13)

	movq mm2,mm4		//;z10

	paddw mm2,mm6		//;z10+z12
	psllw mm4,2+1

	psllw mm2,2
	pmulhw mm2,fix_184	//;z5=1.84*(z10+z12)

	psllw mm6,2
	pmulhw mm6,fix_108	//;tmp10=1.08*z12

	pmulhw mm4,fix_n261x2//;tmp12= -2.61*z10

	movq mm3,[edi+8*2*0]			//;tmp0

	psubw mm6,mm2		//;tmp10 = 1.08*z12 - z5
	paddw mm4,mm2		//;tmp12 = -2.61*z10 + z5

	psubw mm4,mm7		//;tmp6 = tmp12-tmp7
	movq mm2,mm3		//;tmp0

	psubw mm0,mm4		//;tmp5 = tmp11-tmp6
	movq mm5,[edi+8*2*1]			//;tmp1

	paddw mm6,mm0		//;tmp4=tmp10+tmp5

	paddw mm2,mm7		//;ans0 = tmp0+tmp7

	psubw mm3,mm7		//;ans7 = tmp0-tmp7
	movq mm1,mm5		//tmp1

	movq [edi+8*2*0],mm2
	paddw mm1,mm4		//;ans1=tmp1+tmp6

	movq [edi+8*2*7],mm3
	psubw mm5,mm4		//;ans6=tmp1-tmp6

	movq mm2,[edi+8*2*2]			//;tmp2
	movq mm3,mm2					//tmp2

	movq [edi+8*2*1],mm1
	paddw mm2,mm0		//;ans2 = tmp2+tmp5

	movq [edi+8*2*6],mm5
	psubw mm3,mm0		//;ans5 = tmp2-tmp5

	movq mm1,[edi+8*2*3]			//;tmp3
	movq mm5,mm1					//;tmp3

	movq [edi+8*2*2],mm2
	paddw mm1,mm6		//;ans4	= tmp3+tmp4

	movq [edi+8*2*5],mm3
	psubw mm5,mm6		//;ans3 = tmp3-tmp4

	movq [edi+8*2*4],mm1
	add ebx,8

	movq [edi+8*2*3],mm5
	add esi,8

	add edi,8

	dec ecx
	jnz near LOOP1

/*
emms
	}


#if defined _DEBUG
	static int bbb = 0;
	if (bbb == 0)
	{
		bbb = 1;
		OutputDebugString("\n\nPASS1 DATA\n\n");
		short* dmy = (short*)work;
		for (int jj=0;jj<8;jj++)
		{
			for (int ii=0;ii<8;ii++)
			{

				short yy = *(dmy+ii+jj*8);
				short uu = *(dmy+ii+jj*8+64);
				short vv = *(dmy+ii+jj*8+64*2);

				char mes[256];
				wsprintf(mes,"[%d %d %d] ",(int)yy,(int)uu,int(vv));
				OutputDebugString(mes);
			}
			OutputDebugString("\n");
		}

	}
#endif


		_asm{
*/

// PASS 2 

	mov esi,work
	mov edi,dst

//	mov edx,[SCREEN_PITCH]
	mov edx,8*2

	mov ecx,edx
	add ecx,ecx
	add ecx,edx

	mov tmp,ecx

	mov ecx,2
LOOP2:
	push ecx
	mov ecx,tmp

// Even part 

	movq mm0,[esi+8*2*0]	//;00 01 02 03

	movq mm2,[esi+8*2*0+8]	//;04 05 06 07
	movq mm1,mm0

	paddw mm0,mm2			//;0:tmp10 x 0:tmp13 x
	movq mm4,[esi+8*2*1]	//;10 11 12 13

	psubw mm1,mm2			//;0:tmp11 x 0:tmp12' x
	movq mm6,[esi+8*2*1+8]	//;14 15 16 17

	movq mm5,mm4

	paddw mm4,mm6			//;1:tmp10 x 1:tmp13 x
	psubw mm5,mm6			//;1:tmp11 x 1:tmp12' x

	movq mm2,mm0
	movq mm3,mm1

	punpcklwd mm0,mm4		//;0:tmp10  1:tmp10  x x
	movq mm6,[esi+8*2*2]	//;20 21 22 23

	punpckhwd mm2,mm4		//;0:tmp13 1:tmp13 x x

	punpcklwd mm1,mm5		//;0:tmp11 1:tmp11 x x

	punpckhwd mm3,mm5		//;0:tmp12' 1:tmp12' x x

	punpckldq mm0,mm2		//;0:tmp10 1:tmp10 0:tmp13 1:tmp13
	movq mm5,[esi+8*2*2+8]	//;24 25 26 27

	punpckldq mm1,mm3		//;0:tmp11 1:tmp11 0:tmp12' 1:tmp12'
	movq mm7,mm6

	paddw mm6,mm5			//;2:tmp10 x 2:tmp13 x
	movq mm4,[esi+8*2*3]

	psubw mm7,mm5			//;2:tmp11 x 2:tmp12' x
	movq mm3,[esi+8*2*3+8]

	movq mm5,mm4

	paddw mm4,mm3			//;3:tmp10 x 3:tmp13 x
	psubw mm5,mm3			//;3:tmp11 x 3:tmp12' x

	movq mm2,mm6

	punpcklwd mm6,mm4		//;2:tmp10 3:tmp10  x x
	movq mm3,mm7

	punpckhwd mm2,mm4		//;2:tmp13 3:tmp13 x x

	punpcklwd mm7,mm5		//;2:tmp11 3:tmp11 x x

	punpckhwd mm3,mm5		//;2:tmp12' 3:tmp12' x x

	punpckldq mm6,mm2		//;2:tmp10 3:tmp10 2:tmp13 3:tmp13

	punpckldq mm7,mm3		//;2:tmp11 3:tmp11 2:tmp12' 3:tmp12'


	movq mm2,mm0
	punpckldq mm0,mm6		//;0-3:tmp10

	punpckhdq mm2,mm6		//;0-3:tmp13
	
	movq mm3,mm1
	punpckldq mm1,mm7		//;0-3:tmp11

	punpckhdq mm3,mm7		//;0-3:tmp12'

	psllw mm3,2
	pmulhw mm3,fix_141		//	;0-3:tmp12''

	movq mm4,mm0
	paddw mm0,mm2			//;0-3:tmp0
	psubw mm4,mm2			//;0-3:tmp3

	psubw mm3,mm2			//;tmp12

	movq mm5,mm1
	paddw mm1,mm3			//;0-3:tmp1


   // Odd part


	movq mm2,[esi+8*2*0]	//;00 01 02 03
	psubw mm5,mm3			//;0-3:tmp2		;this is even part

	movq mm6,[esi+8*2*0+8]	//;04 05 06 07
	movq mm3,mm2

	punpckldq mm2,mm6		//;00 01 04 05
	movq [esi+8*2*0],mm0	//;tmp0

	punpckhdq mm6,mm3		//;06 07 02 03
	movq [esi+8*2*0+8],mm1	//;tmp1

	movq mm3,mm2
	paddw mm2,mm6			//;x 0:z11 x 0:z13

	movq mm0,[esi+8*2*1]	//;10 11 12 13
	psubw mm3,mm6			//;x 0:z12 x 0:x10

	movq mm1,mm0
	movq mm6,[esi+8*2*1+8]	//;14 15 16 17


	punpckldq mm0,mm6		//;10 11 14 15
	movq [esi+8*2*1],mm5	//;tmp2

	punpckhdq mm6,mm1		//;16 17 12 13
	movq [esi+8*2*1+8],mm4	//;tmp3

	movq mm1,mm0
	paddw mm0,mm6			//;x 1:z11 x 1:z13
	psubw mm1,mm6			//;x 1:z12 x 1:z10

	
	movq mm6,mm2
	punpcklwd mm2,mm0		//;x x 0:z11 1:z11

	punpckhwd mm6,mm0		//;x x 0:z13 1:z13

	movq mm7,mm3
	punpcklwd mm3,mm1		//;x x 0:z12 1:z12

	punpckhwd mm7,mm1		//;x x 0:z10 1:z10

	punpckhdq mm6,mm2		//;0:z13 1:z13 0:z11 1:z11
	movq mm0,[esi+8*2*2]	//;20 21 22 23

	punpckhdq mm7,mm3		//;0:z10 1:z10 0:z12 1:z12
	movq mm4,[esi+8*2*2+8]	//;24 25 26 27


	movq mm1,mm0

	punpckldq mm0,mm4		//;20 21 24 25

	punpckhdq mm4,mm1		//;26 27 22 23

	movq mm1,mm0

	paddw mm0,mm4			//;x 2:z11 x 2:z13
	movq mm2,[esi+8*2*3]	//;30 31 32 33

	psubw mm1,mm4			//;x 2:z12 x 2:x10
	movq mm5,[esi+8*2*3+8]	//;34 35 36 37



	movq mm3,mm2

	punpckldq mm2,mm5		//;30 31 34 35
	punpckhdq mm5,mm3		//;36 37 32 33

	movq mm3,mm2
	paddw mm2,mm5			//;x 3:z11 x 3:z13


	movq mm4,mm0

	punpcklwd mm0,mm2		//;x x 2:z11 3:z11
	psubw mm3,mm5			//;x 3:z12 x 3:z10

	punpckhwd mm4,mm2		//;x x 2:z13 3:z13
	movq mm5,mm1

	punpcklwd mm1,mm3		//;x x 2:z12 3:z12

	punpckhwd mm5,mm3		//;x x 2:z10 3:z10

	punpckhdq mm4,mm0		//;2:z13 3:z13 2:z11 3:z11

	punpckhdq mm5,mm1		//;2:z10 3:z10 2:z12 3:z12
	movq mm3,mm6

	punpckldq mm3,mm4		//;0-3:z13

	punpckhdq mm6,mm4		//;0-3:z11
	movq mm2,mm7

	punpckldq mm7,mm5		//;0-3:z10
	movq mm1,mm6

	punpckhdq mm2,mm5		//;0-3:z12
	paddw mm6,mm3			//;tmp7

	psubw mm1,mm3			//;tmp8
	movq mm4,mm7

//	psllw mm1,2
	paddw mm4,mm2

	psllw mm1,2
	pmulhw mm1,fix_141		//;tmp21 = tmp8*1.41
	psllw mm4,2


// tmp20 = MULTIPLY(z12, (FIX_1_082392200- FIX_1_847759065))  /* 2*(c2-c6) */
//                      + MULTIPLY(z10, - FIX_1_847759065); /* 2*c2 */
//1.08z12 -1.84z12 -1.84z10


	pmulhw mm4,fix_184	//;z5 mm4=1.84*(z10+z12) = 1.84z10 + 1.84z12
	psllw mm2,2

	pmulhw mm2,fix_108		//mm2=1.08*z12

	psllw mm7,2+1

	psubw mm2,mm4			//;tmp20 = 1.08z12 - 1.84z10 - 1.84z12



// tmp22 = MULTIPLY(z10,(FIX_1_847759065 - FIX_2_613125930)) /* -2*(c2+c6) */ 
//                + MULTIPLY(z12, FIX_1_847759065); /* 2*c2 */ 
//1,84z10-2.61z10+1.84z12






	pmulhw mm7,fix_n261x2	//z10*2.61






	paddw mm7,mm4			//;tmp22
	
	psubw mm7,mm6			//;tmp6=tmp22-tmp7
	movq mm0,[esi+8*2*0+0]	//;tmp0

	psubw mm1,mm7			//;tmp5=tmp21-tmp6
	movq mm3,mm0

	paddw mm2,mm1			//;tmp4=tmp20+tmp5
	paddw mm0,mm6			//final0=tmp0+tmp7

	psubw mm3,mm6			//final7=tmp0-tmp7
	movq mm4,[esi+8*2*0+8]	//;tmp1







paddw mm0,const_MYHALF	
	psraw mm0,MYSHIFT

	paddw mm0,const_0080							//;00 10 20 30
paddw mm3,const_MYHALF	
	psraw mm3,MYSHIFT

	paddw mm3,const_0080							//;07 17 27 37
	movq mm5,mm4
	movq ans_7,mm3

	paddw mm4,mm7			//final1=tmp1+tmp6
paddw mm4,const_MYHALF	
	psraw mm4,MYSHIFT

	psubw mm5,mm7			//final6=tmp1-tmp6
	paddw mm4,const_0080							//;01 11 21 31

paddw mm5,const_MYHALF	
	psraw mm5,MYSHIFT
	paddw mm5,const_0080							//;06 16 26 36
	movq ans_6,mm5


	movq mm7,mm0
	punpcklwd mm0,mm4								//;00 01 10 11
	punpckhwd mm7,mm4								//;20 21 30 31












	movq mm6,[esi+8*2*1+0]	//;tmp2

	movq mm4,mm6
	
	paddw mm6,mm1	//final2=tmp2+tmp5
	
paddw mm6,const_MYHALF	
	psraw mm6,MYSHIFT
	
	psubw mm4,mm1	//final5=tmp2-tmp5
	paddw mm6,const_0080							//;02 12 22 32





paddw mm4,const_MYHALF	

	psraw mm4,MYSHIFT
	movq mm1,[esi+8*2*1+8]	//;tmp3

	movq mm3,mm1
	paddw mm4,const_0080							//;05 15 25 35
	movq ans_5,mm4




	psubw mm1,mm2			//final3=tmp3-tmp4
paddw mm1,const_MYHALF	

	psraw mm1,MYSHIFT
	paddw mm3,mm2			//final4=tmp3+tmp3

	paddw mm1,const_0080							//;03 13 23 33


	movq mm2,mm6
	punpcklwd mm6,mm1								//;02 03 12 13
	punpckhwd mm2,mm1								//;22 23 32 33



	movq mm1,mm0
	punpckldq mm0,mm6								//;00 01 02 03
	punpckhdq mm1,mm6								//;10 11 12 13


	movq [edi],mm0
	movq [edi+edx],mm1


	movq mm1,mm7
	punpckldq mm7,mm2								//;20 21 22 23
	punpckhdq mm1,mm2								//;30 31 32 33

	mov ecx,tmp

	movq[edi+edx*2],mm7
	movq[edi+ecx],mm1




paddw mm3,const_MYHALF	
	psraw mm3,MYSHIFT

	paddw mm3,const_0080							//;04 14 24 34

	movq mm2,ans_5
	movq mm4,mm3

	punpcklwd mm3,mm2								//;04 05 14 15
	punpckhwd mm4,mm2								//;24 25 34 35


	movq mm0,ans_6
	movq mm1,ans_7
	movq mm7,mm0

	punpcklwd mm0,mm1								//;06 07 16 17
	punpckhwd mm7,mm1								//;26 27 37 37

	movq mm6,mm3
	punpckldq mm3,mm0								//;04 05 06 07
	punpckhdq mm6,mm0								//;14 15 16 17

	movq [edi+8],mm3
	movq [edi+edx+8],mm6


	movq mm5,mm4
	punpckldq mm4,mm7								//;24 25 26 27
	punpckhdq mm5,mm7								//;34 35 36 37

	mov ecx,tmp
	movq [edi+edx*2+8],mm4
	movq [edi+ecx+8],mm5


	add esi,8*2*4
//;	add edi,8*2*4
	add edi,edx
	add edi,edx
	add edi,edx
	add edi,edx

//;%endrep

	pop ecx
	dec ecx
	jnz near LOOP2



//EXIT:

//	pop edi
//	pop esi
//	pop edx
//	pop ebx
//
//	add edi,8*2
//	add esi,64*4
//	dec edx
//	jnz near LOOP0





		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax

		jmp EXIT0
		emms
EXIT0:
	}

	return TRUE;
}





char* CJpegDecoder::HuffmanSearchCommand(char* dataPtr, int maxDataSize)
{
	char* src = dataPtr;
	int loopSize = maxDataSize;
	char* ans;

	__asm
	{
		push eax
		push ecx
		push esi

		mov esi,src
		mov ecx,loopSize

		xor eax,eax
		mov al,0ffh
LOOP0:
		cmp al,[esi]
		jz FOUND1
		inc esi
		dec ecx
		jnz LOOP0
NOT_FOUND:
		mov eax,-1
		jmp LAST
FOUND1:
		inc esi
		dec ecx
		jz NOT_FOUND
		cmp al,[esi]	;FF FF
		jz LOOP0
;
		cmp ah,[esi]
		jz LOOP0

		mov eax,esi
LAST:
		mov ans,eax

		pop esi
		pop ecx
		pop eax
	}

	return ans;
}




//64*3*blockこのdataをdecodeするにゃ
//mmx使わないように修正
int CJpegDecoder::HuffmanDecode(char* srcData, int bitNokori, int* dstBuffer, int block)
{
	int oldDCY = m_oldDCY;
	int oldDCU = m_oldDCU;
	int oldDCV = m_oldDCV;


	int loopBlock = block;
	char* src = srcData;
	char* srcEnd;
	int* dst = dstBuffer;
//	int bits = bitNokori;
	int bitsEnd;

	short* table1;
	short* table2;

	int* table1DCY = &m_huffCalcuTable[0][0];
	int* table2DCY = &m_huffHenkanTable[0][0];
	int* table1DCUV = &m_huffCalcuTable[1][0];
	int* table2DCUV = &m_huffHenkanTable[1][0];

	int* table1ACY = &m_huffCalcuTable[2][0];
	int* table2ACY = &m_huffHenkanTable[2][0];
	int* table1ACUV = &m_huffCalcuTable[3][0];
	int* table2ACUV = &m_huffHenkanTable[3][0];


	int sampleFactX = m_yuvDQTTableNumber[0*3];
	int sampleFactY = m_yuvDQTTableNumber[0*3+1];

	int sampleBlock = sampleFactX * sampleFactY;

	int startBitData = 0;

	if (bitNokori>0)
	{
		int d = *(src-1) & 0xff;

		if (d == 0)
		{
			if ( ((*(src-2)) & 0xff) == 0xff)
			{
				d = 0xff;
			}
		}


		d <<= (8-bitNokori);
		d &= 0xff;
		startBitData = d;
	}

	int huffTempLoopCount;

	char hufferr = 0;


	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		mov esi,src
		mov edi,dst

		//pxor mm5,mm5
		//pxor mm6,mm6

		mov eax,startBitData
		mov ecx,bitNokori
		
		mov edx,loopBlock
LOOP00:
		push edx



//Y

		mov edx,sampleBlock
LOOP000:
		push edx

		mov edx,table1DCY
		mov table1,edx
		mov edx,table2DCY
		mov table2,edx

		call GetHuffCode
		call CodeToDataDC
		add edx,oldDCY

//mov edx,80h

		mov [edi],edx
		mov oldDCY,edx
		add edi,4

		mov edx,table1ACY
		mov table1,edx
		mov edx,table2ACY
		mov table2,edx

		mov edx,63
		mov huffTempLoopCount,edx
LOOP1:
		call GetHuffCode
		call CodeToDataAC
		mov edx,huffTempLoopCount
		or edx,edx
		jnz LOOP1


		pop edx
		dec edx
		jnz LOOP000








//U
		mov edx,table1DCUV
		mov table1,edx
		mov edx,table2DCUV
		mov table2,edx

		call GetHuffCode
		call CodeToDataDC
		add edx,oldDCU
		mov [edi],edx
		mov oldDCU,edx
		add edi,4

		mov edx,table1ACUV
		mov table1,edx
		mov edx,table2ACUV
		mov table2,edx

		mov edx,63
		mov huffTempLoopCount,edx
LOOP2:
		call GetHuffCode
		call CodeToDataAC
		mov edx,huffTempLoopCount
		or edx,edx
		jnz LOOP2








//V
		mov edx,table1DCUV
		mov table1,edx
		mov edx,table2DCUV
		mov table2,edx

		call GetHuffCode
		call CodeToDataDC

		add edx,oldDCV
//		add edx,oldDCU

		mov [edi],edx
		mov oldDCV,edx
//		mov oldDCU,edx

		add edi,4

		mov edx,table1ACUV
		mov table1,edx
		mov edx,table2ACUV
		mov table2,edx

		mov edx,63
		mov huffTempLoopCount,edx
LOOP3:
		call GetHuffCode
		call CodeToDataAC
		mov edx,huffTempLoopCount
		or edx,edx
		jnz LOOP3

		pop edx
		dec edx
		jnz LOOP00

		mov srcEnd,esi
		mov bitsEnd,ecx

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
		jmp EXIT0
//		emms

//		*************** subroutine

GetHuffCode:
		mov ebx,table1
		
		xor edx,edx

		push edi
		xor edi,edi
//		xor eax,eax
LOOP001:
		or ecx,ecx
		jnz SKIP001
//LOOP0010:
		mov al,[esi]
		mov ecx,8
		inc esi
		cmp al,0ffh
		jnz SKIP001
		mov ah,[esi]
		inc esi
		cmp ah,0
		jnz HUFF_ERROR
SKIP001:
		add al,al
		adc edx,edx
		dec ecx
//;
		cmp edx,[ebx+0]	//;min
		jb SKIP002
		cmp edx,[ebx+4]
		jnb SKIP002
//;found
		sub edx,[ebx+0]
		
		mov ebx,table2


		add edx,[ebx+edi*4]			//;huffcode
		mov edx,[ebx+edx*4+4*16]	//;変換後のcode

		pop edi
		ret

SKIP002:
		add ebx,4*2
//	inc ebp
		inc edi
//	cmp ebp,16
		cmp edi,16
		jb LOOP001

HUFF_ERROR:
		mov edx,-1
		pop edi
		ret


CodeToDataSub:
CodeToDataDC:
//CodeToDataAC:
		or edx,edx
		jnz CodeToDataDCStart
		ret
CodeToDataDCStart:
		push ebx
		push edi

		mov ebx,edx
		xor edx,edx
		mov edi,1	
CodeToDataDCLOOP:
//;get bitdata

		or ecx,ecx
		jnz GETTODATACDSKIP001
//;
		mov al,[esi]
		mov ecx,8
		inc esi
		cmp al,0ffh
		jnz GETTODATACDSKIP001
//GETTODATACDLOOP0010:
//		mov al,[esi]
//		inc esi
//
//		cmp al,0ffh
//		jnz GETTODATACDSKIP001

		mov ah,[esi]
		inc esi
		cmp ah,0
		jz GETTODATACDSKIP001
		//unknown error対応わからにゃい
		mov hufferr,ah


GETTODATACDSKIP001:
		add al,al

		adc edx,edx
		dec ecx

		dec ebx
		jz CodeToDataDCEXIT

		add edi,edi
		jmp CodeToDataDCLOOP

CodeToDataDCEXIT:
		test edi,edx
		jnz CodeToDataDCOK
//;minus
		inc edx
		sub edx,edi
		sub edx,edi

CodeToDataDCOK:


		pop edi
		pop ebx

		ret





//;-------------------------------------------------------------------------------------

CodeToDataAC:
	test dl,0fh
	jz AC1_EOBORZRL

//;run
	push edx
	shr edx,4
	or edx,edx
	jz AC1SKIP1



//	sub ebp,edx


	push eax
	mov eax,huffTempLoopCount
	sub eax,edx
	mov huffTempLoopCount,eax

//test eax,eax
//js BADBAD2

	test eax,eax
	jns AC1RUN1OKOK

	add eax,edx
	mov edx,eax

	xor eax,eax
	mov huffTempLoopCount,eax



//	add edx,eax
//	cmp edx,1
//	js 


AC1RUN1OKOK:
	xor eax,eax
AC1RUNLOOP:
	mov [edi],eax
	add edi,4
	dec edx
	jnz AC1RUNLOOP
	pop eax

	mov edx,huffTempLoopCount
	or edx,edx
	jz AC1OKOK3B


AC1SKIP1:
	pop edx
;data
	and dl,0fh
	call CodeToDataSub
	mov [edi],edx
	add edi,4

	mov edx,huffTempLoopCount
	dec edx
	mov huffTempLoopCount,edx

test edx,edx
jns AC1OKOK3
	mov edx,0
	mov huffTempLoopCount,edx

AC1OKOK3:
	ret
AC1OKOK3B:


	pop edx
	and dl,0fh
//	call CodeToDataSub	//このコードはすてるにゃ

	ret


AC1_EOBORZRL:
	cmp dl,0f0h
	jz AC1_ZRL

//	shr edx,4
//;EOB
	
	push eax

	mov edx,huffTempLoopCount
	or edx,edx
	jz EOBSKIP999
	
	xor eax,eax
EOBLOOP1:
	mov [edi],eax
	add edi,4
	dec edx
	jnz EOBLOOP1

	xor edx,edx
	mov huffTempLoopCount,edx
EOBSKIP999:
	pop eax
	ret


AC1_ZRL:
	xor edx,edx
	push ecx
	mov ecx,16
ECXLOOP:
	mov [edi],edx
	add edi,4
	dec ecx
	jnz ECXLOOP
	pop ecx

//	movq [edi],mm5
//	movq [edi+8],mm6
//	movq [edi+16],mm5
//	movq [edi+24],mm6
//	movq [edi+32],mm5
//	movq [edi+40],mm6
//	movq [edi+48],mm5
//	movq [edi+56],mm6
//	add edi,64

	mov edx,huffTempLoopCount
	sub edx,16
	mov huffTempLoopCount,edx

test edx,edx
jns AC1ZRLOKOKOKOK
mov edx,0
mov huffTempLoopCount,edx

AC1ZRLOKOKOKOK:
	ret

//BADBAD:
//	ret
//BADBAD2:
//	ret
//BADBAD3:
//	ret


//	emms
EXIT0:
	emms

	}


	m_oldDCY = oldDCY;
	m_oldDCU = oldDCU;
	m_oldDCV = oldDCV;

	m_hufferr = hufferr;

	return ((srcEnd - src)<<3) | bitsEnd;
}




/*


//global Huff_Search_Command
//global Huff_DC1_MMX
//global Huff_AC1_MMX
//global Huff_DC2_MMX
//global GetErrorData

GetErrorData:
	mov eax,[ERROR_DATA]
	ret

Huff_DC1_MMX:
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp

	mov eax,0
	mov [ERROR_DATA],eax


	mov eax,[esp+12+24]
	mov [table1Y],eax
	mov eax,[esp+16+24]
	mov [table2Y],eax

	mov eax,[esp+20+24]
	mov [table1UV],eax
	mov eax,[esp+24+24]
	mov [table2UV],eax

	mov eax,[esp+28+24]
	mov [Y_PTR],eax
	mov eax,[esp+32+24]
	mov [U_PTR],eax
	mov eax,[esp+36+24]
	mov [V_PTR],eax

	mov esi,[esp+4+24]
	mov ecx,0
	mov ebp,[esp+8+24]
	add ebp,esi

;;	mov [jpegdata_last],ebp
	inc ebp
	mov [jpegdata_last_plus1],ebp			;;debug 2000-03-28


	mov al,[esi]
	inc esi
	mov ecx,8

;	debug 2000-03-28
	cmp al,0ffh
	jnz DEBUG20000328_1
	inc al
	cmp al,[esi]
	jnz near DC1DATABAD
	inc esi
	dec al
DEBUG20000328_1:



	mov ebp,20*15
	mov edi,TEMP_DC1_BUFFER
DC1LOOP:	
	mov edx,[table1Y]
	mov [table1],edx
	mov edx,[table2Y]
	mov [table2],edx
	
	push ebp
	call GetHuffCode
	pop ebp

	cmp edx,-1
	jz near DC1DATABAD
	call CodeToDataDC
	mov [edi],edx

	cmp esi,[jpegdata_last_plus1]		;debug 2000-03-28
	jnb near DC1DATAEND
	add edi,4

	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		 ;debug 2000-03-28
	jnb near DC1DATAEND
	add edi,4

	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		;debug 2000-03-28
	jnb near DC1DATAEND
	add edi,4

	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		;debug 2000-03-28
	jnb near DC1DATAEND
	add edi,4


	mov edx,[table1UV]
	mov [table1],edx
	mov edx,[table2UV]
	mov [table2],edx


	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		;debug 2000-03-28	 
	jnb near DC1DATAEND
	add edi,4

	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near  DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		;debug 2000-03-28	 
	jnb near DC1DATAEND
	add edi,4

	dec ebp
	jnz near DC1LOOP
DC1DATA1OK:
;data move

;Y
	push esi	


	mov ecx,15
	mov esi,TEMP_DC1_BUFFER
	mov edi,[Y_PTR]
	mov ebp,0
DC1LOOP2:
	push ecx
	mov ecx,20
DC1LOOP3:
	mov eax,[esi]
	add eax,eax
	add eax,ebp
	mov [edi],eax
	mov ebp,eax

	mov eax,[esi+4]
	add eax,eax
	add eax,ebp
	mov [edi+64*4],eax
	mov ebp,eax

	mov eax,[esi+8]
	add eax,eax
	add eax,ebp
	mov [edi+40*64*4],eax
	mov ebp,eax

	mov eax,[esi+12]
	add eax,eax
	add eax,ebp
	mov [edi+40*64*4+64*4],eax
	mov ebp,eax

	add esi,24
	add edi,64*4*2

	dec ecx
	jnz DC1LOOP3

	pop ecx
	add edi,64*40*4
	dec ecx
	jnz DC1LOOP2

;UV
	mov ecx,20*15
	mov esi,TEMP_DC1_BUFFER + 4*4
	mov edi,[U_PTR]
	mov ebx,[V_PTR]
	mov ebp,0
	mov edx,0
DC1LOOP4:
	mov eax,[esi]
	add eax,eax
	add eax,ebp
;xor eax,eax
	mov [edi],eax
	mov ebp,eax

	mov eax,[esi+4]
	add eax,eax
	add eax,edx
;xor eax,eax
	mov [ebx],eax
	mov edx,eax

	add esi,24
	add edi,64*4
	add ebx,64*4

	dec ecx
	jnz DC1LOOP4


	pop esi
	mov eax,esi
	jmp EXIT_DC1
DC1DATAEND:
	dec ebp
	jz near DC1DATA1OK
DC1DATABAD:
	mov eax,-1

EXIT_DC1:
	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	ret



;-------------------------------------------------------------------------------------
Huff_DC2_MMX:
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp

	mov esi,[esp+4+24]
	mov ebp,[esp+8+24]
	mov edi,[esp+12+24]
	mov ebx,[esp+16+24]
	mov edx,[esp+20+24]

	add ebp,esi
	inc ebp
	mov [jpegdata_last_plus1],ebp

	mov ecx,15
DC2LOOP1:
	push ecx

	mov ecx,20/4
DC2LOOP2:

	xor eax,eax

	mov al,[esi]
	inc esi
	cmp al,0ffh
	jnz DC2OK1
	inc al
	cmp al,[esi]
	jnz near DC2ERROR
;DEBUG2000-03-28
	inc esi
	dec al
DC2OK1:
	movd mm0,eax
	psllq mm0,24

	mov al,[esi]
	inc esi
	cmp al,0ffh
	jnz DC2OK2
	inc al
	cmp al,[esi]
	jnz near DC2ERROR
;DEBUG2000-03-28
	inc esi
	dec al
DC2OK2:
	movd mm1,eax
	psllq mm1,16

	mov al,[esi]
	inc esi
	cmp al,0ffh
	jnz DC2OK3
	inc al
	cmp al,[esi]
	jnz near DC2ERROR
;DEBUG2000-03-28
	inc esi
	dec al
DC2OK3:
	cmp esi,[jpegdata_last_plus1]
	jnb DC2ERROR

	movd mm2,eax
	psllq mm2,8

	por mm0,mm1
	por mm0,mm2

	push ecx
	push ebp

	mov ebp,4
	mov ecx,1
	movd eax,mm0

DC2LOOP3:
	add eax,eax
	jnb DC2SKIP2
	or [edi],ecx
DC2SKIP2:
	add eax,eax
	jnb DC2SKIP3
	or [edi+64*4],ecx
DC2SKIP3:
	add eax,eax
	jnb DC2SKIP4
	or [edi+64*40*4],ecx
DC2SKIP4:
	add eax,eax
	jnb DC2SKIP5
	or [edi+64*40*4+64*4],ecx
DC2SKIP5:

	add eax,eax
	jnb DC2SKIP6
	or [ebx],ecx
DC2SKIP6:
	add eax,eax
	jnb DC2SKIP7
	or [edx],ecx
DC2SKIP7:

	add edi,64*4*2
	add ebx,64*4
	add edx,64*4
	dec ebp
	jnz DC2LOOP3

	pop ebp
	pop ecx

	dec ecx
	jnz near DC2LOOP2

	pop ecx
	add edi,64*40*4
	dec ecx
	jnz near DC2LOOP1

	mov eax,esi
	jmp DC2EXIT


DC2ERROR:
	mov eax,-1
	pop ecx

DC2EXIT:
	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx

	ret


;-------------------------------------------------------------------------------------
Huff_AC1_MMX:
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp

	mov eax,333
	mov [ERROR_DATA],eax

	mov eax,[esp+12+24]
	mov [table1],eax
	mov eax,[esp+16+24]
	mov [table2],eax
	mov edi,[esp+20+24]
	mov esi,[esp+4+24]
	mov ebp,[esp+8+24]
	mov edx,[esp+24+24]
	mov eax,[esp+28+24]
	mov [dct_start],eax
	mov eax,[esp+32+24]
	mov [dct_end],eax
	add ebp,esi
	inc ebp
	mov [jpegdata_last_plus1],ebp


	mov eax,[dct_start]
	shl eax,2
	add edi,eax

	mov eax,[dct_end]
	sub eax,[dct_start]
	inc eax
	mov [dct_loops],eax

	mov al,[esi]
	inc esi
	mov ecx,8

;	debug 2000-03-28
	cmp al,0ffh
	jnz DEBUG20000328_2
	inc al
	cmp al,[esi]
	jnz near AC1EXITBAD
	inc esi
	dec al
DEBUG20000328_2:


	pxor mm5,mm5
	pxor mm6,mm6


AC1LOOP1:
	push edx
	push edi

	mov ebp,[dct_loops]
AC1LOOP2:

	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near AC1_BAD2

	test dl,0fh
	jz AC1_EOBORZRL

;run
	push edx
	shr edx,4
	or edx,edx
	jz AC1SKIP1
	sub ebp,edx
	push eax
	xor eax,eax
AC1RUNLOOP:
	mov [edi],eax
	add edi,4
	dec edx
	jnz AC1RUNLOOP
	pop eax
AC1SKIP1:
	pop edx
;data
	and dl,0fh
	call CodeToDataAC

	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]	 
	jnb near AC1_BAD2
	add edi,4
	dec ebp
	jnz AC1LOOP2

AC1_NEXT:
	pop edi
	pop edx
	add edi,64*4
	dec edx
	jnz near AC1LOOP1
AC1_LAST:
	mov eax,esi
	jmp near EXIT_AC1

AC1_EOBORZRL:
	cmp dl,0f0h
	jz AC1_ZRL
	shr edx,4
;EOBn
	call CodeToDataEOBRUN
	movd mm7,edx

	push edx
	xor edx,edx
AC1EOB_n_LOOP:
	mov [edi],edx
	add edi,4
	dec ebp
	jnz AC1EOB_n_LOOP
	pop edx

	pop edi
	add edi,64*4
	dec edx
	jz AC1EOB_n_SKIP


	push eax
	
	xor eax,eax
AC1EOB_n_LOOP2:
	push edx
	push edi

	mov edx,[dct_loops]
AC1EOB_n_LOOP3:
	mov [edi],eax
	add edi,4
	dec edx
	jnz AC1EOB_n_LOOP3
;
	pop edi
	pop edx
	add edi,64*4
	dec edx
	jnz AC1EOB_n_LOOP2
	
	pop eax




AC1EOB_n_SKIP:
	pop edx

	push eax
	movd eax,mm7
	sub edx,eax
	pop eax

	jz AC1_LAST
	js AC1_LAST	;youjin naihazu

	jmp AC1LOOP1



AC1_ZRL:
	sub ebp,16
	movq [edi],mm5
	movq [edi+8],mm6
	movq [edi+16],mm5
	movq [edi+24],mm6
	movq [edi+32],mm5
	movq [edi+40],mm6
	movq [edi+48],mm5
	movq [edi+56],mm6
	add edi,64
	jmp AC1LOOP2


AC1_BAD2:
	pop edi
	pop edx

;push eax
;mov eax,666
;mov [ERROR_DATA],eax
;pop eax
;mov eax,-1
;jmp near EXIT_AC1

AC1EXITBAD:
;push eax
;mov eax,777
;mov [ERROR_DATA],eax
;pop eax

	mov eax,-1
;;	jmp near EXIT_AC1
	
EXIT_AC1:
	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	ret
















//;-------------------------------------------------------------------------------------


GetHuffCode:
	mov ebx,[table1]
	xor edx,edx

	push edi
	xor edi,edi
	xor eax,eax

LOOP001:
	or ecx,ecx
	jnz SKIP001

	mov al,[esi]
	mov ecx,8
	inc esi
	cmp al,0ffh
	jnz SKIP001
	mov al,[esi]
	inc esi
	or al,al
	jnz HUFF_ERROR
	dec al
SKIP001:
	add al,al
	adc edx,edx
	dec ecx
//;
	cmp edx,[ebx+0]	;min
	jb SKIP002
	cmp edx,[ebx+4]
	jnb SKIP002
//;found
	sub edx,[ebx+0]
	mov ebx,[table2]


	add edx,[ebx+edi*4]	//;huffcode
	mov edx,[ebx+edx*4+4*16]	//;変換後のcode

	pop edi
	ret

SKIP002:
	add ebx,4*2
//	inc ebp
	inc edi
//	cmp ebp,16
	cmp edi,16
	jb LOOP001

HUFF_ERROR:
	mov edx,-1
	pop edi
	ret



;-------------------------------------------------------------------------------------

CodeToDataEOBRUN:
	or edx,edx
	jnz CodeToDataEOBStart
	mov edx,1
	ret
CodeToDataEOBStart:
	push ebx
	push edi

	mov ebx,edx
	xor edx,edx
	mov edi,2	
CodeToDataEOBLOOP:
;get bitdata

	or ecx,ecx
	jnz GETTODATAEOBSKIP001
;
	mov al,[esi]
	mov ecx,8
	inc esi
	cmp al,0ffh
	jnz GETTODATAEOBSKIP001
;
	mov al,[esi]
	inc esi
	or al,al
;;	jnz HUFF_ERROR
	dec al
GETTODATAEOBSKIP001:
	add al,al
	adc edx,edx
	dec ecx

	dec ebx
	jz CodeToDataEOBEXIT

	add edi,edi
	jmp CodeToDataEOBLOOP

CodeToDataEOBEXIT:
	add edx,edi

	pop edi
	pop ebx

	ret




CodeToDataDC:
CodeToDataAC:
	or edx,edx
	jnz CodeToDataDCStart
	ret
CodeToDataDCStart:
	push ebx
	push edi

	mov ebx,edx
	xor edx,edx
	mov edi,1	
CodeToDataDCLOOP:
;get bitdata

	or ecx,ecx
	jnz GETTODATACDSKIP001
;
	mov al,[esi]
	mov ecx,8
	inc esi
	cmp al,0ffh
	jnz GETTODATACDSKIP001
;
	mov al,[esi]
	inc esi
	or al,al
;;	jnz HUFF_ERROR
	dec al
GETTODATACDSKIP001:
	add al,al
	adc edx,edx
	dec ecx

	dec ebx
	jz CodeToDataDCEXIT

	add edi,edi
	jmp CodeToDataDCLOOP

CodeToDataDCEXIT:
	test edi,edx
	jnz CodeToDataDCOK
;minus
	inc edx
	sub edx,edi
	sub edx,edi

CodeToDataDCOK:


	pop edi
	pop ebx

	ret


;-------------------------------------------------------------------------------------
INC_ERROR:
	push eax
	mov eax,[ERROR_DATA]
	inc eax
	mov [ERROR_DATA],eax
	pop eax
	ret


SECTION .data
align 32
table1 dd 0,0
table2 dd 0,0
;;;;jpegdata_last dd 0,0			;;debug 2000-03-28
jpegdata_last_plus1 dd 0,0
Y_PTR dd 0,0
U_PTR dd 0,0
V_PTR dd 0,0
table1Y dd 0,0
table1UV dd 0,0
table2Y dd 0,0
table2UV dd 0,0
dct_start dd 0,0
dct_end dd 0,0
dct_loops dd 0,0

ERROR_DATA dd -1,0
DMY_FLAG dd 0,0

SECTION .bss
TEMP_DC1_BUFFER resd 40*30 + 20*15 + 20*15






		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
		jmp EXIT0



		emms
EXIT0:
	}


}

*/


/*
BITS 32

SECTION .text

global jpeg_idct_ifastMMX

jpeg_idct_ifastMMX:


	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp


	mov esi,[esp+4+24]
	mov edx,[esp+8+24]
	mov edi,[esp+12+24]
	mov ebx,[esp+16+24]
	mov eax,[esp+20+24]
	mov [SCREEN_PITCH],eax


LOOP0:
	push ebx
	push edx
	push esi
	push edi


	push ebx

	mov ecx,64/4
	mov ebx,GYAKU_TABLE
	mov edi,DCT_WORK


	mov eax,AANSCALES
LOOP00:
	mov edx,[ebx+0]
	mov ebp,[edx+esi]
	movd mm0,ebp

	mov edx,[ebx+4]
	mov ebp,[edx+esi]
	movd mm1,ebp

	mov edx,[ebx+8]
	mov ebp,[edx+esi]
	movd mm2,ebp

	mov edx,[ebx+12]
	mov ebp,[edx+esi]
	movd mm3,ebp

	punpcklwd mm0,mm1
	punpcklwd mm2,mm3

	punpckldq mm0,mm2

	psllw mm0,4					;x16 /2 (AANSCLAES is div 2)

	pmulhw mm0,[eax]
	add ebx,16
	add eax,8

	movq [edi],mm0

	add edi,8

	dec ecx
	jnz LOOP00


	pop ebx



	mov ecx,2
	mov edi,work
	mov esi,DCT_WORK

;// PASS 1


LOOP1:
;    // Even part 

	movq mm0,[esi+8*2*0]

	pmullw mm0,[ebx+8*2*0]

	movq mm1,[esi+8*2*2]

	pmullw mm1,[ebx+8*2*2]


	movq mm2,[esi+8*2*4]
	movq mm4,mm0

	pmullw mm2,[ebx+8*2*4]
	movq mm5,mm1

	movq mm3,[esi+8*2*6]

	paddw mm0,mm2	;tmp10
	pmullw mm3,[ebx+8*2*6]


	psubw mm4,mm2	;tmp11
	movq mm6,mm0

	paddw mm5,mm3	;tmp13
	psubw mm1,mm3	;tmp12'


	psllw mm1,2

	pmulhw mm1,[fix_141]
	paddw mm0,mm5			;tmp0

	psubw mm6,mm5			;tmp3
	psubw mm1,mm5	;tmp12

	movq [edi+8*2*0],mm0

	movq mm7,mm4
	paddw mm4,mm1			;tmp1

	movq [edi+8*2*3],mm6
	psubw mm7,mm1			;tmp2





;    // Odd part 

	movq mm2,[esi+8*2*5]

	movq [edi+8*2*1],mm4	;even

	pmullw mm2,[ebx+8*2*5]

	movq mm0,[esi+8*2*1]

	movq [edi+8*2*2],mm7	;even

	pmullw mm0,[ebx+8*2*1]

	movq mm4,mm2
	movq mm1,[esi+8*2*3]

	pmullw mm1,[ebx+8*2*3]
	movq mm3,[esi+8*2*7]

	movq mm6,mm0
	pmullw mm3,[ebx+8*2*7]


	paddw mm2,mm1	;z13
	psubw mm4,mm1	;z10

	paddw mm0,mm3	;z11
	psubw mm6,mm3	;z12


	movq mm7,mm0
	psubw mm0,mm2

	paddw mm7,mm2			;tmp7
	psllw mm0,2

	pmulhw mm0,[fix_141];tmp11
	movq mm2,mm4

	paddw mm2,mm6
	psllw mm4,2+1

	psllw mm2,2

	pmulhw mm2,[fix_184];z5

	psllw mm6,2

	pmulhw mm6,[fix_108]

	pmulhw mm4,[fix_n261x2]

	movq mm3,[edi+8*2*0]			;tmp0

	psubw mm6,mm2		;tmp10
	paddw mm4,mm2		;tmp12

	psubw mm4,mm7		;tmp6
	movq mm2,mm3

	psubw mm0,mm4		;tmp5
	movq mm5,[edi+8*2*1]			;tmp1

	paddw mm6,mm0		;tmp4

	paddw mm2,mm7		;ans0

	psubw mm3,mm7		;ans7
	movq mm1,mm5

	movq [edi+8*2*0],mm2
	paddw mm1,mm4		;ans1

	movq [edi+8*2*7],mm3
	psubw mm5,mm4		;ans6

	movq mm2,[edi+8*2*2]			;tmp2
	movq mm3,mm2

	movq [edi+8*2*1],mm1
	paddw mm2,mm0		;ans2

	movq [edi+8*2*6],mm5
	psubw mm3,mm0		;ans5

	movq mm1,[edi+8*2*3]			;tmp3
	movq mm5,mm1

	movq [edi+8*2*2],mm2
	paddw mm1,mm6		;ans4

	movq [edi+8*2*5],mm3
	psubw mm5,mm6		;ans3

	movq [edi+8*2*4],mm1
	add ebx,8

	movq [edi+8*2*3],mm5
	add esi,8

	add edi,8

	dec ecx
	jnz near LOOP1


;// PASS 2 

	mov esi,work

	pop edi
	push edi

	mov edx,[SCREEN_PITCH]
	mov ebp,edx
	add ebp,ebp
	add ebp,edx

	mov ecx,2
LOOP2:

// Even part 

	movq mm0,[esi+8*2*0]	;00 01 02 03

	movq mm2,[esi+8*2*0+8]	;04 05 06 07
	movq mm1,mm0

	paddw mm0,mm2			;0:tmp10 x 0:tmp13 x
	movq mm4,[esi+8*2*1]	;10 11 12 13

	psubw mm1,mm2			;0:tmp11 x 0:tmp12' x
	movq mm6,[esi+8*2*1+8]	;14 15 16 17

	movq mm5,mm4

	paddw mm4,mm6			;1:tmp10 x 1:tmp13 x
	psubw mm5,mm6			;1:tmp11 x 1:tmp12' x

	movq mm2,mm0
	movq mm3,mm1

	punpcklwd mm0,mm4		;0:tmp10  1:tmp10  x x
	movq mm6,[esi+8*2*2]	;20 21 22 23

	punpckhwd mm2,mm4		;0:tmp13 1:tmp13 x x

	punpcklwd mm1,mm5		;0:tmp11 1:tmp11 x x

	punpckhwd mm3,mm5		;0:tmp12' 1:tmp12' x x

	punpckldq mm0,mm2		;0:tmp10 1:tmp10 0:tmp13 1:tmp13
	movq mm5,[esi+8*2*2+8]	;24 25 26 27

	punpckldq mm1,mm3		;0:tmp11 1:tmp11 0:tmp12' 1:tmp12'
	movq mm7,mm6

	paddw mm6,mm5			;2:tmp10 x 2:tmp13 x
	movq mm4,[esi+8*2*3]

	psubw mm7,mm5			;2:tmp11 x 2:tmp12' x
	movq mm3,[esi+8*2*3+8]

	movq mm5,mm4

	paddw mm4,mm3			;3:tmp10 x 3:tmp13 x
	psubw mm5,mm3			;3:tmp11 x 3:tmp12' x

	movq mm2,mm6

	punpcklwd mm6,mm4		;2:tmp10 3:tmp10  x x
	movq mm3,mm7

	punpckhwd mm2,mm4		;2:tmp13 3:tmp13 x x

	punpcklwd mm7,mm5		;2:tmp11 3:tmp11 x x

	punpckhwd mm3,mm5		;2:tmp12' 3:tmp12' x x

	punpckldq mm6,mm2		;2:tmp10 3:tmp10 2:tmp13 3:tmp13

	punpckldq mm7,mm3		;2:tmp11 3:tmp11 2:tmp12' 3:tmp12'


	movq mm2,mm0
	punpckldq mm0,mm6		;0-3:tmp10

	punpckhdq mm2,mm6		;0-3:tmp13
	
	movq mm3,mm1
	punpckldq mm1,mm7		;0-3:tmp11

	punpckhdq mm3,mm7		;0-3:tmp12'

	psllw mm3,2
	pmulhw mm3,[fix_141]	;0-3:tmp12''

	movq mm4,mm0
	paddw mm0,mm2			;0-3:tmp0
	psubw mm4,mm2			;0-3:tmp3

	psubw mm3,mm2			;tmp12

	movq mm5,mm1
	paddw mm1,mm3			;0-3:tmp1


   // Odd part


	movq mm2,[esi+8*2*0]	;00 01 02 03
	psubw mm5,mm3			;0-3:tmp2		;this is even part

	movq mm6,[esi+8*2*0+8]	;04 05 06 07
	movq mm3,mm2

	punpckldq mm2,mm6		;00 01 04 05
	movq [esi+8*2*0],mm0	;tmp0

	punpckhdq mm6,mm3		;06 07 02 03
	movq [esi+8*2*0+8],mm1	;tmp1

	movq mm3,mm2
	paddw mm2,mm6			;x 0:z11 x 0:z13

	movq mm0,[esi+8*2*1]	;10 11 12 13
	psubw mm3,mm6			;x 0:z12 x 0:x10

	movq mm1,mm0
	movq mm6,[esi+8*2*1+8]	;14 15 16 17


	punpckldq mm0,mm6		;10 11 14 15
	movq [esi+8*2*1],mm5	;tmp2

	punpckhdq mm6,mm1		;16 17 12 13
	movq [esi+8*2*1+8],mm4	;tmp3

	movq mm1,mm0
	paddw mm0,mm6			;x 1:z11 x 1:z13
	psubw mm1,mm6			;x 1:z12 x 1:z10

	
	movq mm6,mm2
	punpcklwd mm2,mm0		;x x 0:z11 1:z11

	punpckhwd mm6,mm0		;x x 0:z13 1:z13

	movq mm7,mm3
	punpcklwd mm3,mm1		;x x 0:z12 1:z12

	punpckhwd mm7,mm1		;x x 0:z10 1:z10

	punpckhdq mm6,mm2		;0:z13 1:z13 0:z11 1:z11
	movq mm0,[esi+8*2*2]	;20 21 22 23

	punpckhdq mm7,mm3		;0:z10 1:z10 0:z12 1:z12
	movq mm4,[esi+8*2*2+8]	;24 25 26 27


	movq mm1,mm0

	punpckldq mm0,mm4		;20 21 24 25

	punpckhdq mm4,mm1		;26 27 22 23

	movq mm1,mm0

	paddw mm0,mm4			;x 2:z11 x 2:z13
	movq mm2,[esi+8*2*3]	;30 31 32 33

	psubw mm1,mm4			;x 2:z12 x 2:x10
	movq mm5,[esi+8*2*3+8]	;34 35 36 37



	movq mm3,mm2

	punpckldq mm2,mm5		;30 31 34 35
	punpckhdq mm5,mm3		;36 37 32 33

	movq mm3,mm2
	paddw mm2,mm5			;x 3:z11 x 3:z13


	movq mm4,mm0

	punpcklwd mm0,mm2		;x x 2:z11 3:z11
	psubw mm3,mm5			;x 3:z12 x 3:z10

	punpckhwd mm4,mm2		;x x 2:z13 3:z13
	movq mm5,mm1

	punpcklwd mm1,mm3		;x x 2:z12 3:z12

	punpckhwd mm5,mm3		;x x 2:z10 3:z10

	punpckhdq mm4,mm0		;2:z13 3:z13 2:z11 3:z11

	punpckhdq mm5,mm1		;2:z10 3:z10 2:z12 3:z12
	movq mm3,mm6

	punpckldq mm3,mm4		;0-3:z13

	punpckhdq mm6,mm4		;0-3:z11
	movq mm2,mm7

	punpckldq mm7,mm5		;0-3:z10
	movq mm1,mm6

	punpckhdq mm2,mm5		;0-3:z12
	paddw mm6,mm3			;tmp7

	psubw mm1,mm3
	movq mm4,mm7

	psllw mm1,2
	paddw mm4,mm2

	pmulhw mm1,[fix_141]		;tmp11
	psllw mm4,2

	pmulhw mm4,[fix_184]	;z5
	psllw mm2,2

	pmulhw mm2,[fix_108]
	psllw mm7,2+1

	psubw mm2,mm4			;tmp10

	pmulhw mm7,[fix_n261x2]
	paddw mm7,mm4			;tmp12
	
	psubw mm7,mm6			;tmp6
	movq mm0,[esi+8*2*0+0]	;tmp0

	psubw mm1,mm7			;tmp5
	movq mm3,mm0

	paddw mm2,mm1			;tmp4
	paddw mm0,mm6

	psubw mm3,mm6
	movq mm4,[esi+8*2*0+8]	;tmp1







	psraw mm0,5

	paddw mm0,[const_0080]							;00 10 20 30
	psraw mm3,5

	paddw mm3,[const_0080]							;07 17 27 37
	movq mm5,mm4
	movq [ANS_7],mm3

	paddw mm4,mm7
	psraw mm4,5

	psubw mm5,mm7
	paddw mm4,[const_0080]							;01 11 21 31

	psraw mm5,5
	paddw mm5,[const_0080]							;06 16 26 36
	movq [ANS_6],mm5


	movq mm7,mm0
	punpcklwd mm0,mm4								;00 01 10 11
	punpckhwd mm7,mm4								;20 21 30 31












	movq mm6,[esi+8*2*1+0]	;tmp2

	movq mm4,mm6
	
	paddw mm6,mm1
	
	psraw mm6,5
	
	psubw mm4,mm1
	paddw mm6,[const_0080]							;02 12 22 32






	psraw mm4,5
	movq mm1,[esi+8*2*1+8]	;tmp3

	movq mm3,mm1
	paddw mm4,[const_0080]							;05 15 25 35
	movq [ANS_5],mm4




	psubw mm1,mm2

	psraw mm1,5
	paddw mm3,mm2

	paddw mm1,[const_0080]							;03 13 23 33


	movq mm2,mm6
	punpcklwd mm6,mm1								;02 03 12 13
	punpckhwd mm2,mm1								;22 23 32 33



	movq mm1,mm0
	punpckldq mm0,mm6								;00 01 02 03
	punpckhdq mm1,mm6								;10 11 12 13


	movq [edi],mm0
	movq [edi+edx],mm1


	movq mm1,mm7
	punpckldq mm7,mm2								;20 21 22 23
	punpckhdq mm1,mm2								;30 31 32 33

	movq[edi+edx*2],mm7
	movq[edi+ebp],mm1




	psraw mm3,5

	paddw mm3,[const_0080]							;04 14 24 34

	movq mm2,[ANS_5]
	movq mm4,mm3

	punpcklwd mm3,mm2								;04 05 14 15
	punpckhwd mm4,mm2								;24 25 34 35


	movq mm0,[ANS_6]
	movq mm1,[ANS_7]
	movq mm7,mm0

	punpcklwd mm0,mm1								;06 07 16 17
	punpckhwd mm7,mm1								;26 27 37 37

	movq mm6,mm3
	punpckldq mm3,mm0								;04 05 06 07
	punpckhdq mm6,mm0								;14 15 16 17

	movq [edi+8],mm3
	movq [edi+edx+8],mm6


	movq mm5,mm4
	punpckldq mm4,mm7								;24 25 26 27
	punpckhdq mm5,mm7								;34 35 36 37


	movq [edi+edx*2+8],mm4
	movq [edi+ebp+8],mm5


	add esi,8*2*4
;	add edi,8*2*4
	add edi,edx
	add edi,edx
	add edi,edx
	add edi,edx

;%endrep

	dec ecx
	jnz near LOOP2

EXIT:

	pop edi
	pop esi
	pop edx
	pop ebx

	add edi,8*2
	add esi,64*4
	dec edx
	jnz near LOOP0


	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx

	ret




SECTION .data

align 32
fix_141			dd	5a825a82h,5a825a82h
fix_184			dd	76417641h,76417641h
fix_108			dd	45454545h,45454545h
fix_n261x2		dd	0ac61ac61h,0ac61ac61h
const_0080		dd	00800080h,00800080h

delta1 dw 512,512,512,512

SCREEN_PITCH dd 320*2

ANS_4 dd 0,0
ANS_5 dd 0,0
ANS_6 dd 0,0
ANS_7 dd 0,0

align 32

AANSCALES	dw	  16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520
			dw	  22725, 31521, 29692, 26722, 22725, 17855, 12299,  6270
			dw	  21407, 29692, 27969, 25172, 21407, 16819, 11585,  5906
			dw	  19266, 26722, 25172, 22654, 19266, 15137, 10426,  5315
			dw	  16384, 22725, 21407, 19266, 16384, 12873,  8867,  4520
			dw	  12873, 17855, 16819, 15137, 12873, 10114,  6967,  3552
			dw	   8867, 12299, 11585, 10426,  8867,  6967,  4799,  2446
			dw	   4520,  6270,  5906,  5315,  4520,  3552,  2446,  1247



CCTABLE	dw 16384,23170,23170,23170,23170,23170,23170,23170
		dw 23170,32767,32767,32767,32767,32767,32767,32767
		dw 23170,32767,32767,32767,32767,32767,32767,32767
		dw 23170,32767,32767,32767,32767,32767,32767,32767
		dw 23170,32767,32767,32767,32767,32767,32767,32767
		dw 23170,32767,32767,32767,32767,32767,32767,32767
		dw 23170,32767,32767,32767,32767,32767,32767,32767
		dw 23170,32767,32767,32767,32767,32767,32767,32767


align 32
GYAKU_TABLE dd 0*4,1*4,5*4,6*4,14*4,15*4,27*4,28*4
			dd 2*4,4*4,7*4,13*4,16*4,26*4,29*4,42*4
			dd 3*4,8*4,12*4,17*4,25*4,30*4,41*4,43*4
			dd 9*4,11*4,18*4,24*4,31*4,40*4,44*4,53*4
			dd 10*4,19*4,23*4,32*4,39*4,45*4,52*4,54*4
			dd 20*4,22*4,33*4,38*4,46*4,51*4,55*4,60*4
			dd 21*4,34*4,37*4,47*4,50*4,56*4,59*4,61*4
			dd 35*4,36*4,48*4,49*4,57*4,58*4,62*4,63*4


align 32
DCT_WORK dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0

align 32
work dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0
dd 0,0,0,0,0,0,0,0


*/


/*
;
; Huffman Decode (MMXはほとんどつかってない)
;
;
;
;

BITS 32
SECTION .text

global Huff_Search_Command
global Huff_DC1_MMX
global Huff_AC1_MMX
global Huff_DC2_MMX
global GetErrorData

GetErrorData:
	mov eax,[ERROR_DATA]
	ret

Huff_DC1_MMX:
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp

	mov eax,0
	mov [ERROR_DATA],eax


	mov eax,[esp+12+24]
	mov [table1Y],eax
	mov eax,[esp+16+24]
	mov [table2Y],eax

	mov eax,[esp+20+24]
	mov [table1UV],eax
	mov eax,[esp+24+24]
	mov [table2UV],eax

	mov eax,[esp+28+24]
	mov [Y_PTR],eax
	mov eax,[esp+32+24]
	mov [U_PTR],eax
	mov eax,[esp+36+24]
	mov [V_PTR],eax

	mov esi,[esp+4+24]
	mov ecx,0
	mov ebp,[esp+8+24]
	add ebp,esi

;;	mov [jpegdata_last],ebp
	inc ebp
	mov [jpegdata_last_plus1],ebp			;;debug 2000-03-28


	mov al,[esi]
	inc esi
	mov ecx,8

;	debug 2000-03-28
	cmp al,0ffh
	jnz DEBUG20000328_1
	inc al
	cmp al,[esi]
	jnz near DC1DATABAD
	inc esi
	dec al
DEBUG20000328_1:



	mov ebp,20*15
	mov edi,TEMP_DC1_BUFFER
DC1LOOP:	
	mov edx,[table1Y]
	mov [table1],edx
	mov edx,[table2Y]
	mov [table2],edx
	
	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		;debug 2000-03-28
	jnb near DC1DATAEND
	add edi,4

	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		 ;debug 2000-03-28
	jnb near DC1DATAEND
	add edi,4

	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		;debug 2000-03-28
	jnb near DC1DATAEND
	add edi,4

	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		;debug 2000-03-28
	jnb near DC1DATAEND
	add edi,4


	mov edx,[table1UV]
	mov [table1],edx
	mov edx,[table2UV]
	mov [table2],edx


	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		;debug 2000-03-28	 
	jnb near DC1DATAEND
	add edi,4

	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near  DC1DATABAD
	call CodeToDataDC
	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]		;debug 2000-03-28	 
	jnb near DC1DATAEND
	add edi,4

	dec ebp
	jnz near DC1LOOP
DC1DATA1OK:
;data move

;Y
	push esi	


	mov ecx,15
	mov esi,TEMP_DC1_BUFFER
	mov edi,[Y_PTR]
	mov ebp,0
DC1LOOP2:
	push ecx
	mov ecx,20
DC1LOOP3:
	mov eax,[esi]
	add eax,eax
	add eax,ebp
	mov [edi],eax
	mov ebp,eax

	mov eax,[esi+4]
	add eax,eax
	add eax,ebp
	mov [edi+64*4],eax
	mov ebp,eax

	mov eax,[esi+8]
	add eax,eax
	add eax,ebp
	mov [edi+40*64*4],eax
	mov ebp,eax

	mov eax,[esi+12]
	add eax,eax
	add eax,ebp
	mov [edi+40*64*4+64*4],eax
	mov ebp,eax

	add esi,24
	add edi,64*4*2

	dec ecx
	jnz DC1LOOP3

	pop ecx
	add edi,64*40*4
	dec ecx
	jnz DC1LOOP2

;UV
	mov ecx,20*15
	mov esi,TEMP_DC1_BUFFER + 4*4
	mov edi,[U_PTR]
	mov ebx,[V_PTR]
	mov ebp,0
	mov edx,0
DC1LOOP4:
	mov eax,[esi]
	add eax,eax
	add eax,ebp
;xor eax,eax
	mov [edi],eax
	mov ebp,eax

	mov eax,[esi+4]
	add eax,eax
	add eax,edx
;xor eax,eax
	mov [ebx],eax
	mov edx,eax

	add esi,24
	add edi,64*4
	add ebx,64*4

	dec ecx
	jnz DC1LOOP4


	pop esi
	mov eax,esi
	jmp EXIT_DC1
DC1DATAEND:
	dec ebp
	jz near DC1DATA1OK
DC1DATABAD:
	mov eax,-1

EXIT_DC1:
	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	ret



;-------------------------------------------------------------------------------------
Huff_DC2_MMX:
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp

	mov esi,[esp+4+24]
	mov ebp,[esp+8+24]
	mov edi,[esp+12+24]
	mov ebx,[esp+16+24]
	mov edx,[esp+20+24]

	add ebp,esi
	inc ebp
	mov [jpegdata_last_plus1],ebp

	mov ecx,15
DC2LOOP1:
	push ecx

	mov ecx,20/4
DC2LOOP2:

	xor eax,eax

	mov al,[esi]
	inc esi
	cmp al,0ffh
	jnz DC2OK1
	inc al
	cmp al,[esi]
	jnz near DC2ERROR
;DEBUG2000-03-28
	inc esi
	dec al
DC2OK1:
	movd mm0,eax
	psllq mm0,24

	mov al,[esi]
	inc esi
	cmp al,0ffh
	jnz DC2OK2
	inc al
	cmp al,[esi]
	jnz near DC2ERROR
;DEBUG2000-03-28
	inc esi
	dec al
DC2OK2:
	movd mm1,eax
	psllq mm1,16

	mov al,[esi]
	inc esi
	cmp al,0ffh
	jnz DC2OK3
	inc al
	cmp al,[esi]
	jnz near DC2ERROR
;DEBUG2000-03-28
	inc esi
	dec al
DC2OK3:
	cmp esi,[jpegdata_last_plus1]
	jnb DC2ERROR

	movd mm2,eax
	psllq mm2,8

	por mm0,mm1
	por mm0,mm2

	push ecx
	push ebp

	mov ebp,4
	mov ecx,1
	movd eax,mm0

DC2LOOP3:
	add eax,eax
	jnb DC2SKIP2
	or [edi],ecx
DC2SKIP2:
	add eax,eax
	jnb DC2SKIP3
	or [edi+64*4],ecx
DC2SKIP3:
	add eax,eax
	jnb DC2SKIP4
	or [edi+64*40*4],ecx
DC2SKIP4:
	add eax,eax
	jnb DC2SKIP5
	or [edi+64*40*4+64*4],ecx
DC2SKIP5:

	add eax,eax
	jnb DC2SKIP6
	or [ebx],ecx
DC2SKIP6:
	add eax,eax
	jnb DC2SKIP7
	or [edx],ecx
DC2SKIP7:

	add edi,64*4*2
	add ebx,64*4
	add edx,64*4
	dec ebp
	jnz DC2LOOP3

	pop ebp
	pop ecx

	dec ecx
	jnz near DC2LOOP2

	pop ecx
	add edi,64*40*4
	dec ecx
	jnz near DC2LOOP1

	mov eax,esi
	jmp DC2EXIT


DC2ERROR:
	mov eax,-1
	pop ecx

DC2EXIT:
	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx

	ret


;-------------------------------------------------------------------------------------
Huff_AC1_MMX:
	push ebx
	push ecx
	push edx
	push esi
	push edi
	push ebp

	mov eax,333
	mov [ERROR_DATA],eax

	mov eax,[esp+12+24]
	mov [table1],eax
	mov eax,[esp+16+24]
	mov [table2],eax
	mov edi,[esp+20+24]
	mov esi,[esp+4+24]
	mov ebp,[esp+8+24]
	mov edx,[esp+24+24]
	mov eax,[esp+28+24]
	mov [dct_start],eax
	mov eax,[esp+32+24]
	mov [dct_end],eax
	add ebp,esi
	inc ebp
	mov [jpegdata_last_plus1],ebp


	mov eax,[dct_start]
	shl eax,2
	add edi,eax

	mov eax,[dct_end]
	sub eax,[dct_start]
	inc eax
	mov [dct_loops],eax

	mov al,[esi]
	inc esi
	mov ecx,8

;	debug 2000-03-28
	cmp al,0ffh
	jnz DEBUG20000328_2
	inc al
	cmp al,[esi]
	jnz near AC1EXITBAD
	inc esi
	dec al
DEBUG20000328_2:


	pxor mm5,mm5
	pxor mm6,mm6


AC1LOOP1:
	push edx
	push edi

	mov ebp,[dct_loops]
AC1LOOP2:

	push ebp
	call GetHuffCode
	pop ebp
	cmp edx,-1
	jz near AC1_BAD2

	test dl,0fh
	jz AC1_EOBORZRL

;run
	push edx
	shr edx,4
	or edx,edx
	jz AC1SKIP1
	sub ebp,edx
	push eax
	xor eax,eax
AC1RUNLOOP:
	mov [edi],eax
	add edi,4
	dec edx
	jnz AC1RUNLOOP
	pop eax
AC1SKIP1:
	pop edx
;data
	and dl,0fh
	call CodeToDataAC

	mov [edi],edx
	cmp esi,[jpegdata_last_plus1]	 
	jnb near AC1_BAD2
	add edi,4
	dec ebp
	jnz AC1LOOP2

AC1_NEXT:
	pop edi
	pop edx
	add edi,64*4
	dec edx
	jnz near AC1LOOP1
AC1_LAST:
	mov eax,esi
	jmp near EXIT_AC1

AC1_EOBORZRL:
	cmp dl,0f0h
	jz AC1_ZRL
	shr edx,4
;EOBn
	call CodeToDataEOBRUN
	movd mm7,edx

	push edx
	xor edx,edx
AC1EOB_n_LOOP:
	mov [edi],edx
	add edi,4
	dec ebp
	jnz AC1EOB_n_LOOP
	pop edx

	pop edi
	add edi,64*4
	dec edx
	jz AC1EOB_n_SKIP


	push eax
	
	xor eax,eax
AC1EOB_n_LOOP2:
	push edx
	push edi

	mov edx,[dct_loops]
AC1EOB_n_LOOP3:
	mov [edi],eax
	add edi,4
	dec edx
	jnz AC1EOB_n_LOOP3
;
	pop edi
	pop edx
	add edi,64*4
	dec edx
	jnz AC1EOB_n_LOOP2
	
	pop eax




AC1EOB_n_SKIP:
	pop edx

	push eax
	movd eax,mm7
	sub edx,eax
	pop eax

	jz AC1_LAST
	js AC1_LAST	;youjin naihazu

	jmp AC1LOOP1



AC1_ZRL:
	sub ebp,16
	movq [edi],mm5
	movq [edi+8],mm6
	movq [edi+16],mm5
	movq [edi+24],mm6
	movq [edi+32],mm5
	movq [edi+40],mm6
	movq [edi+48],mm5
	movq [edi+56],mm6
	add edi,64
	jmp AC1LOOP2


AC1_BAD2:
	pop edi
	pop edx

;push eax
;mov eax,666
;mov [ERROR_DATA],eax
;pop eax
;mov eax,-1
;jmp near EXIT_AC1

AC1EXITBAD:
;push eax
;mov eax,777
;mov [ERROR_DATA],eax
;pop eax

	mov eax,-1
;;	jmp near EXIT_AC1
	
EXIT_AC1:
	pop ebp
	pop edi
	pop esi
	pop edx
	pop ecx
	pop ebx
	ret


;-------------------------------------------------------------------------------------
Huff_Search_Command:
	push ecx
	push esi
	mov esi,[esp+4+8]
	mov ecx,[esp+8+8]

	xor eax,eax
	mov al,0ffh
LOOP0:
	cmp al,[esi]
	jz FOUND1
	inc esi
	dec ecx
	jnz LOOP0
NOT_FOUND:
	mov eax,-1
	pop esi
	pop ecx
	ret
FOUND1:
	inc esi
	dec ecx
	jz NOT_FOUND
	cmp al,[esi]	;FF FF
	jz LOOP0
;
	cmp ah,[esi]
	jz LOOP0
FOUNDOK:
	mov eax,esi
	pop esi
	pop ecx
	ret



;ecx:のこりbit
;esi:data ptr
;edx:ret code












;-------------------------------------------------------------------------------------
GetHuffCode:
	mov ebx,[table1]
	xor edx,edx
	mov ebp,0
LOOP001:
	or ecx,ecx
	jnz SKIP001

	mov al,[esi]
	mov ecx,8
	inc esi
	cmp al,0ffh
	jnz SKIP001
	mov al,[esi]
	inc esi
	or al,al
	jnz HUFF_ERROR
	dec al
SKIP001:
	add al,al
	adc edx,edx
	dec ecx
;
	cmp edx,[ebx+0]	;min
	jb SKIP002
	cmp edx,[ebx+4]
	jnb SKIP002
;found
	sub edx,[ebx+0]
	mov ebx,[table2]

	add edx,[ebx+ebp*4]	;huffcode
	mov edx,[ebx+edx*4+4*16]	;変換後のcode

	ret
SKIP002:
	add ebx,4*2
	inc ebp
	cmp ebp,16
	jb LOOP001
HUFF_ERROR:
	mov edx,-1
	ret



;-------------------------------------------------------------------------------------

CodeToDataEOBRUN:
	or edx,edx
	jnz CodeToDataEOBStart
	mov edx,1
	ret
CodeToDataEOBStart:
	push ebx
	push edi

	mov ebx,edx
	xor edx,edx
	mov edi,2	
CodeToDataEOBLOOP:
;get bitdata

	or ecx,ecx
	jnz GETTODATAEOBSKIP001
;
	mov al,[esi]
	mov ecx,8
	inc esi
	cmp al,0ffh
	jnz GETTODATAEOBSKIP001
;
	mov al,[esi]
	inc esi
	or al,al
;;	jnz HUFF_ERROR
	dec al
GETTODATAEOBSKIP001:
	add al,al
	adc edx,edx
	dec ecx

	dec ebx
	jz CodeToDataEOBEXIT

	add edi,edi
	jmp CodeToDataEOBLOOP

CodeToDataEOBEXIT:
	add edx,edi

	pop edi
	pop ebx

	ret




CodeToDataDC:
CodeToDataAC:
	or edx,edx
	jnz CodeToDataDCStart
	ret
CodeToDataDCStart:
	push ebx
	push edi

	mov ebx,edx
	xor edx,edx
	mov edi,1	
CodeToDataDCLOOP:
;get bitdata

	or ecx,ecx
	jnz GETTODATACDSKIP001
;
	mov al,[esi]
	mov ecx,8
	inc esi
	cmp al,0ffh
	jnz GETTODATACDSKIP001
;
	mov al,[esi]
	inc esi
	or al,al
;;	jnz HUFF_ERROR
	dec al
GETTODATACDSKIP001:
	add al,al
	adc edx,edx
	dec ecx

	dec ebx
	jz CodeToDataDCEXIT

	add edi,edi
	jmp CodeToDataDCLOOP

CodeToDataDCEXIT:
	test edi,edx
	jnz CodeToDataDCOK
;minus
	inc edx
	sub edx,edi
	sub edx,edi

CodeToDataDCOK:


	pop edi
	pop ebx

	ret


;-------------------------------------------------------------------------------------
INC_ERROR:
	push eax
	mov eax,[ERROR_DATA]
	inc eax
	mov [ERROR_DATA],eax
	pop eax
	ret


SECTION .data
align 32
table1 dd 0,0
table2 dd 0,0
;;;;jpegdata_last dd 0,0			;;debug 2000-03-28
jpegdata_last_plus1 dd 0,0
Y_PTR dd 0,0
U_PTR dd 0,0
V_PTR dd 0,0
table1Y dd 0,0
table1UV dd 0,0
table2Y dd 0,0
table2UV dd 0,0
dct_start dd 0,0
dct_end dd 0,0
dct_loops dd 0,0

ERROR_DATA dd -1,0
DMY_FLAG dd 0,0

SECTION .bss
TEMP_DC1_BUFFER resd 40*30 + 20*15 + 20*15

  */


/*

	tmp10 = D0+D4
	tmp11 = D0-D4
	tmp13 = D2+D6
	tmp12'= D2-D6
	tmp12'' = 1.41*(D2-D6)
	tmp0 = D0+D2+D4+D6
	tmp3 = D0-D2+D4-D6
	tmp12 = 1.41*(D2-D6)-D2-D6
	tmp1 = tmp11+tmp12
	tmp2 = tmp11-tmp12

	z13 = D5+D3
	z10 = D5-D3

	z11 = D1+D7
	z12 = D1-D7

	tmp7 = z11+z13
	tmp11 = 1.41*(z11-z13)
	z5=1.84*(z10+z12)
	tmp10=1.08*z12
	tmp12= -2.61*z10

	tmp10 = 1.08*z12 - z5
	tmp12 = -2.61*z10 + z5

	tmp6 = tmp12-tmp7
	tmp5 = tmp11-tmp6
	tmp4=tmp10+tmp5

	ans0 = tmp0+tmp7
	ans7 = tmp0-tmp7
	ans1 = tmp1+tmp6
	ans6 = tmp1-tmp6
	ans2 = tmp2+tmp5
	ans5 = tmp2-tmp5
	ans4 = tmp3+tmp4
	ans3 = tmp3-tmp4


*/


//#define FIX_0_382683433  0.382683433f
//#define FIX_0_541196100  0.541196100f
//#define FIX_0_707106781  0.707106781f
//#define FIX_1_306562965  1.306562965f

#define FIX_F_141 1.414213562f
#define FIX_F_108 1.082392200f
#define FIX_F_n261 -2.61312593f
#define FIX_F_184 1.847759065f


//
//2.61312593
//1.089790214
//1.847759065

BOOL CJpegDecoder::IDCTFastFloat(int* srcData, float* dstBuffer, short* dctTable,int block)
{
	if (block)
	{
	}

	float* work = dstBuffer;


	for (int i=0;i<64;i++)
	{
		int tbl1 = m_gyakuTable[i] / 4;
		float f1 = (float)srcData[tbl1];
		f1 *= m_aanScalesFloat[i];
		float dct = (float)(dctTable[i]);
		f1 *= dct;
	//	f1 /= 65536.0f;
		*(work+i) = f1;
	}



	float D0,D1,D2,D3,D4,D5,D6,D7;
	float tmp10,tmp11,tmp12,tmp13,tmp12_,tmp12__;
	float tmp0,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7;
	float z10,z11,z12,z13;
	float z5;

//	float tmp0,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6,tmp7;
//	float tmp10,tmp11,tmp12,tmp13;
//	float z1,z2,z3,z4,z5,z11,z13;


	work = dstBuffer;

//		float dct = (float)(dctTable[i]);
//		f1 *= dct;

	short* taihi = dctTable;

	//pass1
	for (int i=0;i<8;i++)
	{
		D0 = work[0];
		D1 = work[1];
		D2 = work[2];
		D3 = work[3];
		D4 = work[4];
		D5 = work[5];
		D6 = work[6];
		D7 = work[7];

//		D0 = work[0] * (float)(dctTable[0]);
//		D1 = work[1] * (float)(dctTable[1]);
//		D2 = work[2] * (float)(dctTable[2]);
//		D3 = work[3] * (float)(dctTable[3]);
//		D4 = work[4] * (float)(dctTable[4]);
//		D5 = work[5] * (float)(dctTable[5]);
//		D6 = work[6] * (float)(dctTable[6]);
//		D7 = work[7] * (float)(dctTable[7]);


		tmp10 = D0+D4;
		tmp11 = D0-D4;
		tmp13 = D2+D6;
		tmp12_= D2-D6;
		tmp12__ = FIX_F_141*tmp12_;
		tmp0 = tmp10+tmp13;
		tmp3 = tmp10-tmp13;
		tmp12 = tmp12__ - tmp13;
		tmp1 = tmp11+tmp12;
		tmp2 = tmp11-tmp12;

		z13 = D5+D3;
		z10 = D5-D3;

		z11 = D1+D7;
		z12 = D1-D7;

		tmp7 = z11+z13;
		tmp11 = FIX_F_141*(z11-z13);
		z5=FIX_F_184*(z10+z12);

		tmp10 = FIX_F_108*z12 - z5;
		tmp12 = FIX_F_n261*z10 + z5;

		tmp6 = tmp12-tmp7;
		tmp5 = tmp11-tmp6;
		tmp4=tmp10+tmp5;

		work[0] = tmp0 + tmp7;
		work[7] = tmp0 - tmp7;
		work[1] = tmp1 + tmp6;
		work[6] = tmp1 - tmp6;
		work[2] = tmp2 + tmp5;
		work[5] = tmp2 - tmp5;
		work[4] = tmp3 + tmp4;
		work[3] = tmp3 - tmp4;

/*
	ans0 = tmp0+tmp7;
	ans7 = tmp0-tmp7;
	ans1 = tmp1+tmp6;
	ans6 = tmp1-tmp6;
	ans2 = tmp2+tmp5;
	ans5 = tmp2-tmp5;
	ans4 = tmp3+tmp4;
	ans3 = tmp3-tmp4;



		tmp0 = work[0] + work[7];
		tmp7 = work[0] - work[7];
		tmp1 = work[1] + work[6];
		tmp6 = work[1] - work[6];
		tmp2 = work[2] + work[5];
		tmp5 = work[2] - work[5];
		tmp3 = work[3] + work[4];
		tmp4 = work[3] - work[4];









		//even

		//phase2
		tmp10 = tmp0 + tmp3;
		tmp13 = tmp0 - tmp3;
		tmp11 = tmp1 + tmp2;
		tmp12 = tmp1 - tmp2;

		//phase3
		work[0] = tmp10 + tmp11;
		work[4] = tmp10 - tmp11;

		z1 = (tmp12 + tmp13) * FIX_0_707106781;
		work[2] = tmp13 + z1;
		work[6] = tmp13 - z1;

		//odd

		tmp10 = tmp4 + tmp5;
		tmp11 = tmp5 + tmp6;
		tmp12 = tmp6 + tmp7;

		z5 = (tmp10 - tmp12) * FIX_0_382683433;
		z2 = tmp10 * FIX_0_541196100 + z5;
		z4 = tmp12 * FIX_1_306562965 + z5;
		z3 = tmp11 * FIX_0_707106781;

		z11 = tmp7 + z3;
		z13 = tmp7 - z3;

		work[5] = z13 + z2;
		work[3] = z13 - z2;
		work[1] = z11 + z4;
		work[7] = z11 - z4;
*/


		work += 8;
		dctTable += 8;
	}

	dctTable = taihi;

	//pass2
	work = dstBuffer;
	for (int i=0;i<8;i++)
	{
		D0 = work[0*8];
		D1 = work[1*8];
		D2 = work[2*8];
		D3 = work[3*8];
		D4 = work[4*8];
		D5 = work[5*8];
		D6 = work[6*8];
		D7 = work[7*8];

//		D0 = work[0*8] * (float)(dctTable[0*8]);
//		D1 = work[1*8] * (float)(dctTable[1*8]);
//		D2 = work[2*8] * (float)(dctTable[2*8]);
//		D3 = work[3*8] * (float)(dctTable[3*8]);
//		D4 = work[4*8] * (float)(dctTable[4*8]);
//		D5 = work[5*8] * (float)(dctTable[5*8]);
//		D6 = work[6*8] * (float)(dctTable[6*8]);
//		D7 = work[7*8] * (float)(dctTable[7*8]);


		tmp10 = D0+D4;
		tmp11 = D0-D4;
		tmp13 = D2+D6;
		tmp12_= D2-D6;
		tmp12__ = FIX_F_141*tmp12_;
		tmp0 = tmp10+tmp13;
		tmp3 = tmp10-tmp13;
		tmp12 = tmp12__ - tmp13;
		tmp1 = tmp11+tmp12;
		tmp2 = tmp11-tmp12;

		z13 = D5+D3;
		z10 = D5-D3;

		z11 = D1+D7;
		z12 = D1-D7;

		tmp7 = z11+z13;
		tmp11 = FIX_F_141*(z11-z13);
		z5=FIX_F_184*(z10+z12);

		tmp10 = FIX_F_108*z12 - z5;
		tmp12 = FIX_F_n261*z10 + z5;

		tmp6 = tmp12-tmp7;
		tmp5 = tmp11-tmp6;
		tmp4=tmp10+tmp5;

		work[0*8] = tmp0 + tmp7;
		work[7*8] = tmp0 - tmp7;
		work[1*8] = tmp1 + tmp6;
		work[6*8] = tmp1 - tmp6;
		work[2*8] = tmp2 + tmp5;
		work[5*8] = tmp2 - tmp5;
		work[4*8] = tmp3 + tmp4;
		work[3*8] = tmp3 - tmp4;



/*
		tmp0 = work[8*0] + work[8*7];
		tmp7 = work[8*0] - work[8*7];
		tmp1 = work[8*1] + work[8*6];
		tmp6 = work[8*1] - work[8*6];
		tmp2 = work[8*2] + work[8*5];
		tmp5 = work[8*2] - work[8*5];
		tmp3 = work[8*3] + work[8*4];
		tmp4 = work[8*3] - work[8*4];

		//even

		//phase2
		tmp10 = tmp0 + tmp3;
		tmp13 = tmp0 - tmp3;
		tmp11 = tmp1 + tmp2;
		tmp12 = tmp1 - tmp2;

		//phase3
		work[0*8] = tmp10 + tmp11;
		work[4*8] = tmp10 - tmp11;

		z1 = (tmp12 + tmp13) * FIX_0_707106781;
		work[2*8] = tmp13 + z1;
		work[6*8] = tmp13 - z1;

		//odd

		tmp10 = tmp4 + tmp5;
		tmp11 = tmp5 + tmp6;
		tmp12 = tmp6 + tmp7;

		z5 = (tmp10 - tmp12) * FIX_0_382683433;
		z2 = tmp10 * FIX_0_541196100 + z5;
		z4 = tmp12 * FIX_1_306562965 + z5;
		z3 = tmp11 * FIX_0_707106781;

		z11 = tmp7 + z3;
		z13 = tmp7 - z3;

		work[5*8] = z13 + z2;
		work[3*8] = z13 - z2;
		work[1*8] = z11 + z4;
		work[7*8] = z11 - z4;
*/

		work += 1;
		dctTable += 1;
	}

	return TRUE;
}




BOOL CJpegDecoder::YUV2RGBFloat(float* yuvBuffer, int* rgbBuffer)
{
	for (int i=0;i<64;i++)
	{
		float y = *yuvBuffer + 128.0f;
		float u = *(yuvBuffer+64);// - 128.0f;
		float v = *(yuvBuffer+64*2);// - 128.0f;
//u=0.0;
//v=0.0;
//		if (y<0.0f) y = 0.0f;
//		if (y>255.0f) y = 255.0f;
//		if (u<-128.0f) u = -128.0f;
//		if (u>127.0f) u = 127.0f;
//		if (v<-128.0f) v = -128.0f;
//		if (v>127.0f) v = 127.0f;

	
		float r = y              + 1.402f * v;
		float g = y - 0.344f * u - 0.714f * v;
		float b = y + 1.772f * u;

//		y -= 16.0f;
//		y *= 1.164f;
//		float r = y              + 1.596f * v;
//		float g = y - 0.391f * u - 0.813f * v;
//		float b = y + 2.018f * u;

//		int rr = (int)(r*1.0f+0.5f);
//		int gg = (int)(g*1.0f+0.5f);
//		int bb = (int)(b*1.0f+0.5f);
		int rr = (int)(r+0.5f);
		int gg = (int)(g+0.5f);
		int bb = (int)(b+0.5f);
		if (rr<0) rr = 0;
		if (rr>255) rr = 255;
		if (gg<0) gg = 0;
		if (gg>255) gg = 255;
		if (bb<0) bb = 0;
		if (bb>255) bb = 255;


		*rgbBuffer = (rr<<16) | (gg<<8) | bb;

		yuvBuffer++;
		rgbBuffer++;
	}


	return TRUE;
}


void CJpegDecoder::UVFact4Float(float* ptr)
{
	int sampleFactX = m_yuvDQTTableNumber[0*3];
	int sampleFactY = m_yuvDQTTableNumber[0*3+1];
//	int sampleBlock = sampleFactX * sampleFactY;

	int miniX = 8 / sampleFactX;
	int miniY = 8 / sampleFactY;

	for (int uv=0;uv<2;uv++)
	{
		for (int y=sampleFactY-1;y>=0;y--)
		{
			for (int x=sampleFactX-1;x>=0;x--)
			{
				float* src = ptr + 64 + uv*64 + x * miniX + y * 8*miniY;
				float* dst = ptr + 64 + uv*64 + (x+y*sampleFactX)*64*3;

				for (int j=miniY-1;j>=0;j--)
				{
					for (int i=miniX-1;i>=0;i--)
					{
						float d = *(src+i+j*8);

						for (int jj=0;jj<sampleFactY;jj++)
						{
							for (int ii=0;ii<sampleFactX;ii++)
							{
								*(dst + i*sampleFactX+ii+(j*sampleFactY+jj)*8) = d;
//						*(dst + i*2+1+j*2*8) = d;
//						*(dst + i*2+(j*2+1)*8) = d;
//						*(dst + i*2+1+(j*2+1)*8) = d;
							}
						}
					}
				}
			}
		}
	}
}


/*_*/



