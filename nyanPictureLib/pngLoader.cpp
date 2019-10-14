#include <windows.h>
#include <stdio.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\myFile.h"

//#define ZLIB_WINAPI
#include "d:\libpng\include\zlib.h"
#include "d:\libpng\include\png.h"

#include "pngLoader.h"






BOOL CPngLoader::m_gammaAdjustFlag = FALSE;

CPngLoader::CPngLoader(int bufferSizeMegaByte)
{
	m_buffer = NULL;
	ReCreateBuffer(bufferSizeMegaByte * 1024*1024);

	m_imagePointerKosuu = 0;
	m_imagePointer = NULL;
	ReCreateImagePointer(2048);

	m_paletteBuffer = new unsigned char[256*4+1024];
	m_paletteTable = new int[256];
	//dummy palette
	for (int i=0;i<256;i++)
	{
		int col = (i<<16) | (i<<8) | i;
		m_paletteTable[i] = col;
	}

	m_picSize.cx = 1;
	m_picSize.cy = 1;
}

CPngLoader::~CPngLoader()
{
	End();
}

void CPngLoader::End(void)
{
	DELETEARRAY(m_imagePointer);
	DELETEARRAY(m_paletteTable);
	DELETEARRAY(m_paletteBuffer);
	DELETEARRAY(m_buffer);
}

/*
void CTestZLib::PngReadProc(png_structp png_ptr, png_bytep data, png_size_t length)
{
	ReadFile(png_get_io_ptr(png_ptr), data, length, (DWORD*)&length, NULL);
}
*/
#if _MSC_VER >= 1500

BOOL CPngLoader::LoadFile(FILE* file)
{
//	m_file = file;

	png_struct* png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
//		fclose(file);
		return FALSE;
	}

	png_info* info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
	    png_destroy_read_struct(&png_ptr, NULL, NULL);
//		fclose(file);
		return FALSE;
	}


	png_init_io(png_ptr, file); 
	png_read_info(png_ptr, info_ptr); 

	png_uint_32 nWidth, nHeight;
//	int nDepth, nPal;
	int nPngDepth, nColorType, nInterlaceType, nCompType, nFilterType;

	png_get_IHDR(png_ptr, info_ptr, &nWidth, &nHeight, &nPngDepth, &nColorType, &nInterlaceType, &nCompType, &nFilterType);

	m_picSize.cx = nWidth;
	m_picSize.cy = nHeight;

	int seibun = 1;
	int nPal = 0;

	m_maskFlag = FALSE;
	m_colorType = nColorType;

	if (nColorType == PNG_COLOR_TYPE_GRAY)
	{
		seibun = 1;
	}
	else if (nColorType == PNG_COLOR_TYPE_RGB)
	{
		seibun = 3;
	}
	else if (nColorType == PNG_COLOR_TYPE_PALETTE)
	{
		seibun = 1;
		nPal = 1 << nPngDepth;
	}
	else if (nColorType == PNG_COLOR_TYPE_GA)
	{
		seibun = 2;
		m_maskFlag = TRUE;
	}
	else if (nColorType == PNG_COLOR_TYPE_RGBA)
	{
		seibun = 4;
		m_maskFlag = TRUE;
	}

	m_seibun = seibun;
	m_depth = nPngDepth;

	
	int lineBits = nWidth * nPngDepth * seibun;
	int lineBytes = ((lineBits + 31) / 32) * 4;


	//calcu need buffer size
	int needSize = lineBytes * nHeight;
	if (needSize > m_bufferSize)
	{
		ReCreateBuffer(needSize);
	}

	if ((int)nHeight > m_imagePointerKosuu)
	{
		ReCreateImagePointer(nHeight);
	}

	unsigned char** image = m_imagePointer;
	for (int j=0;j<(int)nHeight;j++)
	{
		image[j] =  m_buffer + lineBytes * j;
	}

	m_gammaExistFlag = FALSE;
	if (png_get_gAMA(png_ptr, info_ptr, &m_gamma) == PNG_INFO_gAMA)
	{
		m_gammaExistFlag;
	}

	if (m_gammaAdjustFlag)
	{
		double display_gamma = 2.2;

		if (m_gammaExistFlag)
		{
	        png_set_gamma(png_ptr, display_gamma, m_gamma);
		}
		else
		{
	        png_set_gamma(png_ptr, display_gamma, 0.5);
		}

		png_read_update_info(png_ptr, info_ptr);
	}



	m_transExistFlag = FALSE;
	
	if ((nColorType != PNG_COLOR_TYPE_RGBA) && (nColorType == PNG_COLOR_TYPE_GA))
	{
		png_byte* lpTransPalette;
		int transPalKosuu = 0;
		png_color_16* lpTransColor;

		if (png_get_tRNS(png_ptr,info_ptr,&lpTransPalette,&transPalKosuu,&lpTransColor) == PNG_INFO_tRNS )
		{
			if (nColorType == PNG_COLOR_TYPE_PALETTE)
			{
				for (int i=0;i<transPalKosuu;i++)
				{
					m_transPalette[i] = lpTransPalette[i];
				}
				for (int i=transPalKosuu;i<256;i++)
				{
					m_transPalette[i] = 255;
				}
			}
			else if (nColorType == PNG_COLOR_TYPE_GRAY)
			{
				m_transGrayColor = lpTransColor->gray;
				m_transGrayColor1 = (unsigned char)(m_transGrayColor >> 8);
				m_transGrayColor2 = (unsigned char)(m_transGrayColor & 0xff);
			}
			else if (nColorType == PNG_COLOR_TYPE_RGB)
			{
				m_transRedColor = lpTransColor[0].red;
				m_transRedColor1 = (unsigned char)(m_transRedColor >> 8);
				m_transRedColor2 = (unsigned char)(m_transRedColor & 0xff);
				m_transGreenColor = lpTransColor[1].green;
				m_transGreenColor1 = (unsigned char)(m_transGreenColor >> 8);
				m_transGreenColor2 = (unsigned char)(m_transGreenColor & 0xff);
				m_transBlueColor = lpTransColor[2].blue;
				m_transBlueColor1 = (unsigned char)(m_transBlueColor >> 8);
				m_transBlueColor2 = (unsigned char)(m_transBlueColor & 0xff);
			}

			m_transExistFlag = TRUE;
			m_maskFlag = TRUE;
		}
	}


	//load palette
	if (nPal > 0)
	{
		png_color* lpPalette = NULL;
		int palKosuu = 0;
		png_get_PLTE(png_ptr,info_ptr,&lpPalette,&palKosuu);

		for (int i=0;i<palKosuu;i++)
		{
			int palR = (int)lpPalette[i].red;
			int palG = (int)lpPalette[i].green;
			int palB = (int)lpPalette[i].blue;

			m_paletteTable[i] = (palR << 16) | (palG << 8) | palB;
		}

		for (int i=palKosuu;i<256;i++)
		{
			m_paletteTable[i] = 0;
		}
	}

	png_read_image(png_ptr, image); 


//	fclose(file);

	png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

	return TRUE;
}
#else
BOOL CPngLoader::LoadFile(FILE* file){return FALSE;}
#endif

BOOL CPngLoader::LoadFile(LPSTR filename)
{
	FILE* file = CMyFile::Open(filename,"rb");
	if (file == NULL) return FALSE;


	BOOL rt = LoadFile(file);
	fclose(file);
	return rt;
}

void CPngLoader::GetPic8AndPalette(char* lpPic8,int* lpPalette)
{
	//8bit color only
	if (m_depth != 8) return;


	int blockSize = (m_depth / 8) * m_seibun;

	int sizeY = m_picSize.cy;
	int sizeX = m_picSize.cx;

	if (m_depth == 8)
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];

			char* dst = lpPic8;
			dst += sizeX * j;
			memcpy(dst,src,sizeX);
		}
		memcpy(lpPalette,m_paletteTable,sizeof(int)*256);
	}


	/*
	else if (m_depth == 4)
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;
			
			int sizeX2 = sizeX / 2;
			for (int i=0;i<sizeX2;i++)
			{
				int pal = (int)(*src);
				int pal0 = pal >> 4;
				int pal1 = pal & 0xf;

				*dst = m_paletteTable[pal0];
				dst++;
				*dst = m_paletteTable[pal1];
				dst++;
				src += blockSize;
			}

			if (sizeX & 1)
			{
				int pal = (int)(*src);
				int pal0 = pal >> 4;
//				int pal1 = pal & 0f;

				*dst = m_paletteTable[pal0];
				dst++;
//				*dst = m_paletteTable[pal1];
//				dst++;
//				src += blockSize;
			}
		}
	}
	else if (m_depth == 2)
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;

			int sizeX4 = sizeX / 4;
			for (int i=0;i<sizeX4;i++)
			{
				int pal = (int)(*src);
				int pal0 = (pal >> 6) & 0x3;
				int pal1 = (pal >> 4) & 0x3;
				int pal2 = (pal >> 2) & 0x3;
				int pal3 = pal  & 0x3;
				*dst = m_paletteTable[pal0];
				dst++;
				*dst = m_paletteTable[pal1];
				dst++;
				*dst = m_paletteTable[pal2];
				dst++;
				*dst = m_paletteTable[pal3];
				dst++;
				src += blockSize;
			}

			int loop2 = sizeX & 3;
			if (loop2 > 0)
			{
				int pal = (int)(*src);
				for (int k=0;k<loop2;k++)
				{
					int pal0 = (pal >> 6) & 0x3;
					pal <<= 2;
					*dst = m_paletteTable[pal0];
					dst++;
				}
			}
		}
	}
	else if (m_depth == 1)
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;

			int sizeX8 = sizeX / 8;
			for (int i=0;i<sizeX8;i++)
			{
				int pal = (int)(*src);
				for (int k=0;k<8;k++)
				{
					if (pal & 0x80)
					{
						*dst = m_paletteTable[1];
					}
					else
					{
						*dst = m_paletteTable[0];
					}
					dst++;
					pal <<= 1;
				}
				src += blockSize;
			}

			int loop3 = sizeX & 7;
			if (loop3 > 0)
			{
				int pal = (int)(*src);
				for (int k=0;k<loop3;k++)
				{
					if (pal & 0x80)
					{
						*dst = m_paletteTable[1];
					}
					else
					{
						*dst = m_paletteTable[0];
					}
					dst++;
					pal <<= 1;
				}
			}
		}
	}
*/
}


void CPngLoader::GetPicData(int* lpPic)
{
	m_tmpPic = lpPic;

	if (m_colorType == PNG_COLOR_TYPE_PALETTE)
	{
		GetPicDataWithPalette(lpPic);
		return;
	}

	//‚Æ‚è‚ ‚¦‚¸8bit 16bit ‚¾‚¯‘Î‰ž‚³‚¹‚é

	if ((m_depth != 8) && (m_depth != 16)) return;//‚ ‚Æ‚Å

	int blockSize = (m_depth / 8) * m_seibun;

	int sizeY = m_picSize.cy;
	int sizeX = m_picSize.cx;

	if ((m_depth == 4) && (m_colorType == PNG_COLOR_TYPE_GRAY))
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;

			int sizeX2 = sizeX / 2;
			for (int i=0;i<sizeX2;i++)
			{
				int colGray01 = (int)(*src);
				int colGray0 = colGray01 & 0xf0;
				int colGray1 = (colGray01 << 4) & 0xf0;
				colGray0 |= (colGray0 >> 4);
				colGray1 |= (colGray1 >> 4);

				*dst = (colGray0 << 16) | (colGray0 << 8) | colGray0;
				dst++;
				*dst = (colGray1 << 16) | (colGray1 << 8) | colGray1;
				dst++;

				src += blockSize;
			}

			if (sizeX & 1)
			{
				int colGray01 = (int)(*src);
				int colGray0 = colGray01 & 0xf0;
				colGray0 |= (colGray0 >> 4);

				*dst = (colGray0 << 16) | (colGray0 << 8) | colGray0;
				dst++;
			}

		}
		return;
	}
	else if ((m_depth == 2) && (m_colorType == PNG_COLOR_TYPE_GRAY))
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;

			int sizeX4 = sizeX / 4;
			for (int i=0;i<sizeX4;i++)
			{
				int colGray0123 = (int)(*src);
				int colGray0 = colGray0123 & 0xc0;
				int colGray1 = (colGray0123<<2) & 0xc0;
				int colGray2 = (colGray0123<<4) & 0xc0;
				int colGray3 = (colGray0123<<6) & 0xc0;

				colGray0 |= (colGray0 >> 2);
				colGray1 |= (colGray1 >> 2);
				colGray2 |= (colGray2 >> 2);
				colGray3 |= (colGray3 >> 2);

				colGray0 |= (colGray0 >> 4);
				colGray1 |= (colGray1 >> 4);
				colGray2 |= (colGray2 >> 4);
				colGray3 |= (colGray3 >> 4);

				*dst = (colGray0 << 16) | (colGray0 << 8) | colGray0;
				dst++;
				*dst = (colGray1 << 16) | (colGray1 << 8) | colGray1;
				dst++;
				*dst = (colGray2 << 16) | (colGray2 << 8) | colGray2;
				dst++;
				*dst = (colGray3 << 16) | (colGray3 << 8) | colGray3;
				dst++;

				src += blockSize;
			}

			int loop2 = sizeX & 3;
			if (loop2 > 0)
			{
				int colGray0123 = (int)(*src);

				for (int k=0;k<loop2;k++)
				{
					int colGray = colGray0123 & 0xc;
					colGray0123 <<= 2;

					colGray |= (colGray >> 2);
					colGray |= (colGray >> 4);

					*dst = (colGray << 16) | (colGray << 8) | colGray;
					dst++;
				}
			}
		}
		return;
	}
	else if ((m_depth == 1) && (m_colorType == PNG_COLOR_TYPE_GRAY))
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;

			int sizeX8 = sizeX / 8;
			for (int i=0;i<sizeX8;i++)
			{
				int colGray8 = (int)(*src);
				for (int k=0;k<8;k++)
				{
					if (colGray8 & 0x80)
					{
						*dst = 0xffffff;
					}
					else
					{
						*dst = 0;
					}
					dst++;

					colGray8 <<= 1;
				}
				src += blockSize;
			}

			int loop3 = sizeX & 7;
			if (loop3 > 0)
			{
				int colGray8 = (int)(*src);
				for (int k=0;k<loop3;k++)
				{
					if (colGray8 & 0x80)
					{
						*dst = 0xffffff;
					}
					else
					{
						*dst = 0;
					}
					dst++;

					colGray8 <<= 1;
				}
			}
		}

		return;
	}

	if ((m_depth != 8) && (m_depth != 16)) return;//error!

	if ((m_colorType == PNG_COLOR_TYPE_GRAY) || (m_colorType == PNG_COLOR_TYPE_GA))
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;

			for (int i=0;i<sizeX;i++)
			{
				int colGray = (int)(*src);
				*dst = (colGray << 16) | (colGray << 8) | colGray;

				src += blockSize;
				dst++;
			}
		}
	}
	else
	{
		//color
		int gOffset = m_depth / 8;
		int bOffset = (m_depth / 8)*2;

		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;

			for (int i=0;i<sizeX;i++)
			{
				int colR = (int)(*src);
				int colG = (int)(*(src + gOffset));
				int colB = (int)(*(src + bOffset));
				*dst = (colR << 16) | (colG << 8) | colB;

				src += blockSize;
				dst++;
			}
		}
	}
}



void CPngLoader::GetPicDataWithPalette(int* lpPic)
{
	//1,2,4,8bit color


	int blockSize = (m_depth / 8) * m_seibun;

	int sizeY = m_picSize.cy;
	int sizeX = m_picSize.cx;

	if (m_depth == 8)
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;

			for (int i=0;i<sizeX;i++)
			{
				int pal = (int)(*src);
				*dst = m_paletteTable[pal];
				src += blockSize;
				dst++;
			}
		}
	}
	else if (m_depth == 4)
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;
			
			int sizeX2 = sizeX / 2;
			for (int i=0;i<sizeX2;i++)
			{
				int pal = (int)(*src);
				int pal0 = pal >> 4;
				int pal1 = pal & 0xf;

				*dst = m_paletteTable[pal0];
				dst++;
				*dst = m_paletteTable[pal1];
				dst++;
				src += blockSize;
			}

			if (sizeX & 1)
			{
				int pal = (int)(*src);
				int pal0 = pal >> 4;
//				int pal1 = pal & 0f;

				*dst = m_paletteTable[pal0];
				dst++;
//				*dst = m_paletteTable[pal1];
//				dst++;
//				src += blockSize;
			}
		}
	}
	else if (m_depth == 2)
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;

			int sizeX4 = sizeX / 4;
			for (int i=0;i<sizeX4;i++)
			{
				int pal = (int)(*src);
				int pal0 = (pal >> 6) & 0x3;
				int pal1 = (pal >> 4) & 0x3;
				int pal2 = (pal >> 2) & 0x3;
				int pal3 = pal  & 0x3;
				*dst = m_paletteTable[pal0];
				dst++;
				*dst = m_paletteTable[pal1];
				dst++;
				*dst = m_paletteTable[pal2];
				dst++;
				*dst = m_paletteTable[pal3];
				dst++;
				src += blockSize;
			}

			int loop2 = sizeX & 3;
			if (loop2 > 0)
			{
				int pal = (int)(*src);
				for (int k=0;k<loop2;k++)
				{
					int pal0 = (pal >> 6) & 0x3;
					pal <<= 2;
					*dst = m_paletteTable[pal0];
					dst++;
				}
			}
		}
	}
	else if (m_depth == 1)
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			int* dst = lpPic;
			dst += sizeX * j;

			int sizeX8 = sizeX / 8;
			for (int i=0;i<sizeX8;i++)
			{
				int pal = (int)(*src);
				for (int k=0;k<8;k++)
				{
					if (pal & 0x80)
					{
						*dst = m_paletteTable[1];
					}
					else
					{
						*dst = m_paletteTable[0];
					}
					dst++;
					pal <<= 1;
				}
				src += blockSize;
			}

			int loop3 = sizeX & 7;
			if (loop3 > 0)
			{
				int pal = (int)(*src);
				for (int k=0;k<loop3;k++)
				{
					if (pal & 0x80)
					{
						*dst = m_paletteTable[1];
					}
					else
					{
						*dst = m_paletteTable[0];
					}
					dst++;
					pal <<= 1;
				}
			}
		}
	}
}



void CPngLoader::GetMaskData(char* lpMask)
{
	int blockSize = (m_depth / 8) * m_seibun;
	int offset = (m_seibun-1) * (m_depth / 8);

	int sizeY = m_picSize.cy;
	int sizeX = m_picSize.cx;

	if ((m_colorType == PNG_COLOR_TYPE_GA) || (m_colorType == PNG_COLOR_TYPE_RGBA))
	{
		for (int j=0;j<sizeY;j++)
		{
			unsigned char* src = m_imagePointer[j];
			src += offset;

			unsigned char* dst = (unsigned char*)lpMask;
			dst += sizeX * j;

			for (int i=0;i<sizeX;i++)
			{
				*dst = *src;
				src += blockSize;
				dst++;
			}
		}
	}
	else if (m_maskFlag)
	{
		if (m_transExistFlag)
		{
			if (m_colorType == PNG_COLOR_TYPE_PALETTE)
			{
				//8bit palette‚Ì‚Ý‘Î‰ž

				if (m_depth == 8)
				{
					for (int j=0;j<sizeY;j++)
					{
						unsigned char* src = m_imagePointer[j];

						unsigned char* dst = (unsigned char*)lpMask;
						dst += sizeX * j;

						for (int i=0;i<sizeX;i++)
						{
							int pal = (int)(*src);
							*dst = m_transPalette[pal];

							src += blockSize;
							dst++;
						}
					}
				}
				else if (m_depth == 4)
				{
					for (int j=0;j<sizeY;j++)
					{
						unsigned char* src = m_imagePointer[j];

						unsigned char* dst = (unsigned char*)lpMask;
						dst += sizeX * j;


						int sizeX2 = sizeX / 2;
						for (int i=0;i<sizeX2;i++)
						{
							int pal01 = (int)(*src);
							int pal0 = pal01 >> 4;
							int pal1 = pal01 & 0xf;

							*dst = m_transPalette[pal0];
							dst++;
							*dst = m_transPalette[pal1];
							dst++;
							src += blockSize;
						}

						if (sizeX & 1)
						{
							int pal01 = (int)(*src);
							int pal0 = pal01 >> 4;
//							int pal1 = pal01 & 0xf;

							*dst = m_transPalette[pal0];
							dst++;
//							*dst = m_transPalette[pal1];
//							dst++;
							src += blockSize;
						}
					}
				}
				else if (m_depth == 2)
				{
					for (int j=0;j<sizeY;j++)
					{
						unsigned char* src = m_imagePointer[j];

						unsigned char* dst = (unsigned char*)lpMask;
						dst += sizeX * j;


						int sizeX4 = sizeX / 4;
						for (int i=0;i<sizeX4;i++)
						{
							int pal0123 = (int)(*src);
							int pal0 = (pal0123 >> 6) & 0x3;
							int pal1 = (pal0123 >> 4) & 0x3;
							int pal2 = (pal0123 >> 2) & 0x3;
							int pal3 = pal0123 & 3;

							*dst = m_transPalette[pal0];
							dst++;
							*dst = m_transPalette[pal1];
							dst++;
							*dst = m_transPalette[pal2];
							dst++;
							*dst = m_transPalette[pal3];
							dst++;
							src += blockSize;
						}

						int loop2 = sizeX & 3;
						if (loop2 > 0)
						{
							int pal0123 = (int)(*src);

							for (int i=0;i<loop2;i++)
							{
								int pal = (pal0123 >> 6) & 0x3;
								pal0123 <<= 2;
								*dst = m_transPalette[pal];
								dst++;
							}
						}

					}
				}
				else if (m_depth == 1)
				{
					for (int j=0;j<sizeY;j++)
					{
						unsigned char* src = m_imagePointer[j];

						unsigned char* dst = (unsigned char*)lpMask;
						dst += sizeX * j;

						int sizeX8 = sizeX / 8;
						for (int i=0;i<sizeX8;i++)
						{
							int pal8 = (int)(*src);
							for (int k=0;k<8;k++)
							{
								int pal = (pal8 >> 7) & 1;
								*dst = m_transPalette[pal];
								dst++;
								pal8 <<= 1;
							}
							src += blockSize;
						}

						int loop3 = sizeX & 7;
						if (loop3 > 0)
						{
							int pal8 = (int)(*src);
							for (int k=0;k<loop3;k++)
							{
								int pal = (pal8 >> 7) & 1;
								*dst = m_transPalette[pal];
								dst++;
								pal8 <<= 1;
							}

						}

					}
				}

			}
			else if (m_colorType == PNG_COLOR_TYPE_GRAY)
			{
				if (m_depth == 8)
				{
					unsigned char transGray1 = m_transGrayColor1;
					for (int j=0;j<sizeY;j++)
					{
						unsigned char* src = m_imagePointer[j];

						unsigned char* dst = (unsigned char*)lpMask;
						dst += sizeX * j;

						for (int i=0;i<sizeX;i++)
						{
							char gray = *src;
							if (gray == transGray1)
							{
								*dst = 0x0;
							}
							else
							{
								*dst = 0xff;
							}

							src += blockSize;
							dst++;
						}
					}
				}
				else if (m_depth == 16)
				{
					unsigned char transGray1 = m_transGrayColor1;
					unsigned char transGray2 = m_transGrayColor2;
					for (int j=0;j<sizeY;j++)
					{
						unsigned char* src = m_imagePointer[j];

						unsigned char* dst = (unsigned char*)lpMask;
						dst += sizeX * j;

						for (int i=0;i<sizeX;i++)
						{
							char gray = *src;
							char gray2 = *(src+1);
							if ((gray == transGray1) && (gray2 == transGray2))
							{
								*dst = 0x0;
							}
							else
							{
								*dst = 0xff;
							}

							src += blockSize;
							dst++;
						}
					}
				}
				else if ((m_depth == 4) || (m_depth == 2) || (m_depth == 1))
				{
					unsigned char colMask = 0xf0;
					if (m_depth == 2) colMask = 0xc0;
					if (m_depth == 1) colMask = 0x80;

					unsigned char transGray1 = m_transGrayColor1;
					transGray1 &= colMask;


					for (int j=0;j<sizeY;j++)
					{
						unsigned char* isrc = (unsigned char*)m_tmpPic;
						isrc += m_picSize.cx * j * sizeof(int);

						unsigned char* dst = (unsigned char*)lpMask;
						dst += sizeX * j;

						for (int i=0;i<sizeX;i++)
						{
							char gray = *isrc;
							gray &= colMask;

							if (gray == transGray1)
							{
								*dst = 0x0;
							}
							else
							{
								*dst = 0xff;
							}
							dst++;

							isrc += sizeof(int);
						}
					}
				}
			}
			else if (m_colorType == PNG_COLOR_TYPE_RGB)
			{
				if (m_depth == 8)
				{
					unsigned char transRed1 = m_transRedColor1;
					unsigned char transGreen1 = m_transGreenColor1;
					unsigned char transBlue1 = m_transBlueColor1;

					for (int j=0;j<sizeY;j++)
					{
						unsigned char* src = m_imagePointer[j];

						unsigned char* dst = (unsigned char*)lpMask;
						dst += sizeX * j;

						for (int i=0;i<sizeX;i++)
						{
							char red = *src;
							char green = *(src+1);
							char blue = *(src+2);
							if ((red == transRed1) && (green == transGreen1) && (blue == transBlue1))
							{
								*dst = 0x0;
							}
							else
							{
								*dst = 0xff;
							}

							src += blockSize;
							dst++;
						}
					}
				}
				else if (m_depth == 16)
				{
					unsigned char transRed1 = m_transRedColor1;
					unsigned char transGreen1 = m_transGreenColor1;
					unsigned char transBlue1 = m_transBlueColor1;
					unsigned char transRed2 = m_transRedColor2;
					unsigned char transGreen2 = m_transGreenColor2;
					unsigned char transBlue2 = m_transBlueColor2;
					for (int j=0;j<sizeY;j++)
					{
						unsigned char* src = m_imagePointer[j];

						unsigned char* dst = (unsigned char*)lpMask;
						dst += sizeX * j;

						for (int i=0;i<sizeX;i++)
						{
							char red = *src;
							char red2 = *(src+1);
							char green = *(src+2);
							char green2 = *(src+3);
							char blue = *(src+4);
							char blue2 = *(src+5);

							if ((red == transRed1) && (green == transGreen1) && (blue == transBlue1) && (red2== transRed2) && (green2 == transGreen2) && (blue2 == transBlue2))
							{
								*dst = 0x0;
							}
							else
							{
								*dst = 0xff;
							}

							src += blockSize;
							dst++;
						}
					}
				}
			}
		}
	}
}


void CPngLoader::ReCreateBuffer(int needSize)
{
	DELETEARRAY(m_buffer);
	int makeSize = (needSize+1024*1024-1) / (1024*1024);
	makeSize *= 1024*1024;

	m_buffer = new unsigned char[makeSize + 1024*4 + 256];
	m_bufferSize = makeSize;
}


void CPngLoader::ReCreateImagePointer(int height)
{
	DELETEARRAY(m_imagePointer);

	m_imagePointer = new unsigned char* [height];
	m_imagePointerKosuu = height;
}

/*_*/




/*_*/

