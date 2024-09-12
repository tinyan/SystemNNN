//
// picture.cpp
//


#include <windows.h>
#include <stdio.h>

#include "..\nyanlib\include\commonmacro.h"
#include "..\nyanlib\include\myGraphics.h"

#include "..\nyanlib\include\myFile.h"

#include "..\nyanPicturelib\jpegdecoder.h"
#include "..\nyanPicturelib\genshoku16.h"
#include "..\nyanPicturelib\pngLoader.h"

#include "..\nyanlib\include\allPicture.h"


#include "..\nyanlib\include\picture.h"

char CPicture::m_extName[] = "dwq";
char CPicture::m_dirName[16] = "dwq";

SSIZE_T CPicture::m_dataPackLevel = 0;
int CPicture::TmpBufferMeageByte = 0;

//not used!
//BOOL CPicture::m_notAntiAliasFlag = FALSE;

BOOL CPicture::m_genshokuFlag = FALSE;
BOOL CPicture::m_genshokuMiniSizeFlag = FALSE;
BOOL CPicture::m_genshokuJustSizeFlag = TRUE;
BOOL CPicture::m_genshokuOverSizeFlag = TRUE;

int CPicture::m_modeNumber = 0;

char** CPicture::m_ppPackTable = NULL;
BOOL* CPicture::m_pack64Flag = NULL;
LONGLONG** CPicture::m_ppPackTable64 = NULL;

char CPicture::m_packTagName[10][8]=
{
	"ta","bg","ev","sc","sm","sys","","","",""
};


char CPicture::m_old[8192*4] = { 0 };
char CPicture::m_tmp[8192*4] = { 0 };
char CPicture::m_unpack[8192*4] = { 0 };

#if !defined _DEBUG
BOOL CPicture::m_errorPrintFlag = FALSE;
#else
BOOL CPicture::m_errorPrintFlag = TRUE;
#endif

char* CPicture::m_tmpBuffer = NULL;
int CPicture::m_bpp = 32;

CJpegDecoder* CPicture::m_jpegDecoder = NULL;
CGenshoku16* CPicture::m_genshoku16 = NULL;
CPngLoader* CPicture::m_pngLoader = NULL;


void CPicture::InitWork(void)
{
	m_pic = NULL;
	m_pic0 = NULL;
	m_fileName[0] = 0;
	m_loadOkFlag = FALSE;
	m_palette = NULL;
	m_palette0 = NULL;
	m_picBufferSize = 0;
	m_maskPic = NULL;
	m_maskPic0 = NULL;
	m_maskSize = 0;
	m_maskExistFlag = FALSE;
	m_pictureSizeX = 1;
	m_pictureSizeY = 1;
	m_256Flag = FALSE;
	m_texture = NULL;
}

BOOL CPicture::CreateMaskBuffer(int sz)
{
	if (sz<=m_maskSize) return TRUE;

	DELETEARRAY(m_maskPic0);
	m_maskPic = NULL;

#if defined _WIN64
	char* ptr = new char[(long long)sz + 128];
#else
	char* ptr = new char[sz + 128];
#endif

	if (ptr != NULL)
	{
		m_maskPic0 = ptr;
#if defined _WIN64
		long long p2 = (long long)ptr;
#else
		int p2 = (int)ptr;
#endif
		p2 += 63;
		p2 &= (~63);
		m_maskPic = (char*)p2;
		m_maskSize = sz;
		m_maskExistFlag = TRUE;
	}
	else
	{
		//メモリー不足
		return FALSE;
	}
	return TRUE;
}




CPicture::CPicture(LPSTR filename,int nx,int ny, BOOL b256Flag)
{
	InitWork();

//	m_dwqFlag = FALSE;
	m_jpegFlag = FALSE;
	m_maskFlag = FALSE;
	m_packFlag = FALSE;
	m_pngFlag = FALSE;

	if (filename != NULL)
	{
		LoadDWQ(filename,b256Flag);
	}

	if (nx == ny)
	{
		return;//for dummy warning lv4
	}
}



CPicture::CPicture(int sizeX, int sizeY,BOOL createMaskFlag,BOOL b256Flag)
{
	InitWork();

	m_pictureSizeX = sizeX;
	m_pictureSizeY = sizeY;

	m_charaClipXStart = 0;
	m_charaClipXEnd= m_pictureSizeX;
	m_charaClipYStart = 0;
	m_charaClipYEnd= m_pictureSizeY;

	m_256Flag = b256Flag;
	m_pic = nullptr;

	SSIZE_T sz = (SSIZE_T)sizeX * sizeY*sizeof(int);
	if (b256Flag)
	{
		sz = (SSIZE_T)sizeX * sizeY;
	}
	MakeDataBuffer(sz+64);

	m_maskExistFlag = FALSE;
	if (createMaskFlag)
	{
		m_maskExistFlag = CreateMaskBuffer(m_pictureSizeX * m_pictureSizeY);
	}

	m_loadOkFlag = TRUE;
}



CPicture::~CPicture()
{
	End();
}


void CPicture::End(void)
{
	if (m_pic0 != NULL)
	{
		DELETEARRAY(m_pic0);
		m_pic = NULL;
	}

	if (m_palette0 != NULL)
	{
		DELETEARRAY(m_palette0);
		m_palette = NULL;
	}

	if (m_maskPic0 != NULL)
	{
		DELETEARRAY(m_maskPic0);
		m_maskPic = NULL;
	}

	m_maskExistFlag = FALSE;
}

void CPicture::Flush(void)
{
	m_fileName[0] = 0;
	m_makedFileName[0] = 0;
}


int CPicture::LoadBitmapHeaderAndPalette(FILE* file,int* rgbTable,BOOL b256Flag)
{
	int sz = 0;

	if (fread(&m_bmf,sizeof(BITMAPFILEHEADER),1,file) == 1)
	{
		m_restReadSize -= sizeof(BITMAPFILEHEADER);

		if (fread(&m_bmi,sizeof(BITMAPINFOHEADER),1,file) == 1)
		{
			m_restReadSize -= sizeof(BITMAPINFOHEADER);

			RGBQUAD rgbquad[256];

			//load palette
			if (m_bmi.biBitCount == 8)
			{
				int p = m_bmi.biClrUsed;
				if (p == 0) p = 256;
				fread(&rgbquad,sizeof(RGBQUAD),p,file);
				m_restReadSize -= sizeof(RGBQUAD)*p;

				//make table
				for (int i=0;i<p;i++)
				{
					int r = rgbquad[i].rgbRed;
					int g = rgbquad[i].rgbGreen;
					int b = rgbquad[i].rgbBlue;

					rgbTable[i] = ((r<<16) & 0xff0000) | ((g << 8) & 0xff00) | (b & 0xff);
				}

				if (b256Flag)
				{
					if (m_palette0 == NULL)
					{
						m_palette0 = new char[1024+128];
					}

					if (m_palette0 != NULL)
					{
#if defined _WIN64
						m_palette = (LPVOID)((((long long)m_palette0) + 63) & (~63));
#else
						m_palette = (LPVOID)((((int)m_palette0) + 63) & (~63));
#endif
						CopyMemory(m_palette,rgbTable,1024);
					}
				}
			}

			if (b256Flag && (m_bmi.biBitCount == 8))
			{
				sz = sizeof(char) * m_bmi.biWidth * m_bmi.biHeight;
				m_256Flag = TRUE;
			}
			else
			{
				sz = sizeof(int) * m_bmi.biWidth * m_bmi.biHeight;
			}

			if (sz<0) sz *= -1;
		}
	}
	return sz;
}


int CPicture::LoadDWQHeader(FILE* file)
{
	int sz = 0;
	fread(m_dwq,sizeof(char),64,file);

	m_restReadSize -= 64;

	m_alreadyCutFlag = FALSE;
	char* ptr = (char*)m_dwq;


	// 4 2 1
	// J M P
	// P A A
	// G S C
	//   K K


	if (m_dwq[0x39] == '2')
	{
		m_maskFlag = TRUE;
		if ((*(ptr + 48 + 10)) == 'A') m_alreadyCutFlag = TRUE;
	}

	if (m_dwq[0x39] == '3')
	{
		m_packFlag = TRUE;
		m_maskFlag = TRUE;
		if ((*(ptr + 48 + 10)) == 'A') m_alreadyCutFlag = TRUE;
	}

	if (m_dwq[0x39] == '5')
	{
		m_jpegFlag = TRUE;
	}

	if (m_dwq[0x39] == '7')
	{
		m_jpegFlag = TRUE;
		m_maskFlag = TRUE;
		if ((*(ptr + 48 + 10)) == 'A') m_alreadyCutFlag = TRUE;
	}

	//8Aのみ存在
	if (m_dwq[0x39] == '8')
	{
//		m_jpegFlag = TRUE;
//		m_maskFlag = TRUE;
		m_pngFlag = TRUE;
		if ((*(ptr + 48 + 10)) == 'A') m_alreadyCutFlag = TRUE;
	}

	m_dwqSize = *((int*)(&m_dwq[32]));
	int xx0 = *((int*)(&m_dwq[36]));
	int yy0 = *((int*)(&m_dwq[40]));
	sz = xx0 * yy0*4;
	if (sz<0) sz *= -1;

	if (yy0 < 0) yy0 *= -1;
	m_pictureSizeX = xx0;
	m_pictureSizeY = yy0;

	return sz;
}


BOOL CPicture::MakeDataBuffer(SSIZE_T sz)
{
	if ((m_pic0 == NULL) || (( m_pic0 != NULL) && (m_picBufferSize < sz)))
	{
		LPVOID lp = new char[sz+128];


		if (lp == NULL)
		{
			OutputDebugString("LOADDWQ メモリ確保できません File:");
			OutputDebugString(m_fileName);
			OutputDebugString("\n");
		}

		if (m_pic0 != NULL)
		{
			delete [] m_pic0;
			m_pic0 = NULL;
			m_pic = NULL;
		}


		m_pic0 = lp;
		if (m_pic0 != NULL)
		{
			m_picBufferSize = sz;
#if defined _WIN64
			long long p = (long long)m_pic0;
#else
			int p = (int)m_pic0;
#endif
			p += 63;
			p &= (~63);
		//	p += 128;
			m_pic = (LPVOID)p;
		}
		else
		{
			m_picBufferSize = 0;
			return FALSE;
		}
	}
	return TRUE;
}


/*
BOOL CPicture::LoadBitmapData(FILE* file,int* rgbTable, BOOL b256Flag)
{
	char tmp[8192];

	int bitCount = m_bmi.biBitCount;
	int sizeX = m_pictureSizeX;
	int sizeY = m_pictureSizeY;
	int readSize = m_readX;

	int yStart = m_yStart;
	int dy = m_dy;

	//load and change picture
	for (int j=0;j<sizeY;j++)
	{
		fread(tmp,sizeof(char),readSize,file);
		if (bitCount == 8)
		{
			if (b256Flag)
			{
				char* cptr = (char*)m_pic;
				cptr += (yStart + j * dy) * m_pictureSizeX;
				CopyMemory(cptr,tmp,m_pictureSizeX);
			}
			else
			{
				int* ptr = (int*)m_pic;
				ptr += (yStart + j * dy) * m_pictureSizeX;
				for (int i=0;i<sizeX;i++)
				{
					int c = ((int)tmp[i]) & 0xff;
					*ptr = rgbTable[c];
					ptr++;
				}
			}
		}
		else if (bitCount == 24)
		{
			int* ptr = (int*)m_pic;
			ptr += (yStart + j * dy) * m_pictureSizeX;
			for (int i=0;i<sizeX;i++)
			{
				int r = (int)tmp[i*3+2];
				int g = (int)tmp[i*3+1];
				int b = (int)tmp[i*3+0];
				*ptr = ((r<<16) & 0xff0000) | ((g << 8) & 0xff00) | (b & 0xff);
				ptr++;
			}
		}
		else
		{
			//not support
		}
	}
	return TRUE;
}
*/


BOOL CPicture::LoadDWQData(FILE* file, int* rgbTable, BOOL b256Flag)
{
	int sizeX = m_pictureSizeX;
	int sizeY = m_pictureSizeY;
	int readSize = m_readX;

	char tmp[8192*4];

	int colors = m_bmi.biBitCount;


	if ((b256Flag == FALSE) && (colors == 24))
	{
		int readBlockMax = 1024*1024*3 / readSize;
		if (readBlockMax > sizeY) readBlockMax = sizeY;

		CheckTmpBuffer(readSize * readBlockMax);

		int readY = 0;

		while (readY < sizeY)
		{
			int blockY = sizeY - readY;
			if (blockY > readBlockMax) blockY = readBlockMax;

			int rd = (int)fread(m_tmpBuffer,sizeof(char),(SSIZE_T)readSize * blockY,file);
			m_restReadSize -= rd;

			for (int y=0;y<blockY;y++)
			{
				int* ptr = (int*)m_pic;
				ptr += ((SSIZE_T)readY+y) * m_pictureSizeX;

				char* src = m_tmpBuffer;
//				src += y * 3 * sizeX;
				src += (SSIZE_T)y * readSize;

				for (int i=0;i<sizeX;i++)
				{
					int r = (int)(*src);
					r &= 0xff;
					src++;
					int g = (int)(*src);
					g &= 0xff;
					src++;
					int b = (int)(*src);
					b &= 0xff;
					src++;
					*ptr = (r<<16) | (g<<8) | b;
					ptr++;
				}
			}

			readY += blockY;
		}

		return TRUE;
	}



	for (SSIZE_T j=0;j<sizeY;j++)
	{
		fread(tmp,sizeof(char),readSize,file);
		m_restReadSize -= readSize;

		if (b256Flag)
		{
			char* cptr = (char*)m_pic;
			cptr += j * m_pictureSizeX;
			CopyMemory(cptr,tmp,m_pictureSizeX);
		}
		else
		{
			int* ptr = (int*)m_pic;
			ptr += j * m_pictureSizeX;

			if (colors <= 8)//8
			{
				for (int i=0;i<sizeX;i++)
				{
					int c = ((int)tmp[i]) & 0xff;
					*ptr = rgbTable[c];
					ptr++;
				}
			}
			else	//24
			{
				for (int i=0;i<sizeX;i++)
				{
					int r = (int)tmp[i*3];
					r &= 0xff;
					int g = (int)tmp[i*3+1];
					g &= 0xff;
					int b = (int)tmp[i*3+2];
					b &= 0xff;
					*ptr = (r<<16) | (g<<8) | b;
					ptr++;
				}
			}
		}
	}

	return TRUE;
}


BOOL CPicture::LoadPackedDWQData(FILE* file,int* rgbTable, BOOL b256Flag)
{
	int minus = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	int p = m_bmi.biClrUsed;
	if (p == 0) p = 256;
	minus += p* 4;

	CheckTmpBuffer((SSIZE_T)m_dwqSize - minus);

	int readLength = (int)fread(m_tmpBuffer,sizeof(char),(SSIZE_T)m_dwqSize - minus,file);
	m_restReadSize -= readLength;

	int ptr = 0;
	char* tmpBuffer = m_tmpBuffer;

	int sizeX = m_pictureSizeX;
	int sizeY = m_pictureSizeY;


//	char old[8192];
//	char tmp[8192];

	int i;
		
	for (i=0;i<sizeX;i++)
	{
		m_old[i] = 0;
		m_tmp[i] = 0;
	}

	for (SSIZE_T j=0;j<sizeY;j++)
	{
		//unpack
		int xPtr = 0;
		while (xPtr < sizeX)
		{
			char c = tmpBuffer[ptr];
			ptr++;
			if (c != 0)
			{
				m_tmp[xPtr] = c;
				xPtr++;
			}
			else
			{
				int ln = ((int)tmpBuffer[ptr]) & 0xff;
				ptr++;
				for (int ii=0;ii<ln;ii++)
				{
					m_tmp[xPtr] = 0;
					xPtr++;
				}
			}
		}

		//xor
		for (i=0;i<sizeX;i++)
		{
			m_tmp[i] ^= m_old[i];
			m_old[i] = m_tmp[i];
		}


		if (b256Flag)
		{
			char* ptr0 = (char*)m_pic;
			ptr0 += j * m_pictureSizeX;
			CopyMemory(ptr0,m_tmp,m_pictureSizeX);
		}
		else
		{
			int* ptr00 = (int*)m_pic;
			ptr00 += j * m_pictureSizeX;

			for (i=0;i<sizeX;i++)
			{
				int c = ((int)m_tmp[i]) & 0xff;
				*ptr00 = rgbTable[c];
				ptr00++;
			}
		}
	}

	return TRUE;
}

void CPicture::CalcuReadPara(void)
{
	if (m_bmi.biHeight>=0)
	{
		m_yStart = m_bmi.biHeight - 1;
		m_dy = -1;
		m_pictureSizeY = m_bmi.biHeight;
	}
	else
	{
		m_yStart = 0;
		m_dy = 1;
		m_pictureSizeY = - m_bmi.biHeight;
	}

	int picX = (m_bmi.biBitCount>>3) * m_bmi.biWidth;
	m_readX = (picX + 3) & (~3);
	m_pictureSizeX = m_bmi.biWidth;
}



BOOL CPicture::LoadMask(FILE* file)
{
	int sz = m_pictureSizeX * m_pictureSizeY;

//	if (sz > m_maskSize)
//	{
	m_maskExistFlag = CreateMaskBuffer(sz);
//	}
	if (m_maskExistFlag == FALSE) return FALSE;


	//if dwq then read header and check pack type

//	char tmp[1024];

	BITMAPFILEHEADER bmf;
	fread(&bmf,sizeof(BITMAPFILEHEADER),1,file);
	m_restReadSize -= sizeof(BITMAPFILEHEADER);

	BITMAPINFOHEADER bmi;
	fread(&bmi,sizeof(BITMAPINFOHEADER),1,file);
	m_restReadSize -= sizeof(BITMAPINFOHEADER);

	RGBQUAD rgbquad[256];
	int p = bmi.biClrUsed;
	if (p == 0) p = 256;
	fread(&rgbquad,sizeof(RGBQUAD),p,file);
	m_restReadSize -= sizeof(RGBQUAD)*p;

//	int fsize = (m_pictureSizeX + 3) & ~3;

	int readLength = 0;
	
	if (m_packFileFlag == FALSE)
	{
		readLength = (int)fread(m_tmpBuffer,sizeof(char),1024*1024*16,file);
	}
	else
	{
		CheckTmpBuffer(m_restReadSize);
		readLength = (int)fread(m_tmpBuffer,sizeof(char),m_restReadSize,file);
	}
	
	int ptr = 0;

	//char old[8192];
	//char unpack[8192];

	int i;
	
	for (i=0;i<m_pictureSizeX;i++)
	{
		m_old[i] = 0;
		m_unpack[i] = 0;
	}

	for (int j=0;j<m_pictureSizeY;j++)
	{
		//unpack
		int xPtr = 0;
		while (xPtr < m_pictureSizeX)
		{
			char c = m_tmpBuffer[ptr];
			ptr++;
			if (c != 0)
			{
				m_unpack[xPtr] = c;
				xPtr++;
			}
			else
			{
				int ln = m_tmpBuffer[ptr] & 0xff;
				ptr++;
				for (int ii=0;ii<ln;ii++)
				{
					m_unpack[xPtr] = 0;
					xPtr++;
				}
			}
		}

		//xor
		for (i=0;i<m_pictureSizeX;i++)
		{
			m_unpack[i] ^= m_old[i];
			m_old[i] = m_unpack[i];
		}

		for (i=0;i<m_pictureSizeX;i++)
		{
			int c = ((int)m_unpack[i]) & 0xff;
			int r = rgbquad[c].rgbRed;
			*(m_maskPic + i + (SSIZE_T)j * m_pictureSizeX) = (char)r;
		}
	}


	fclose(file);
	SetMaskExist();

	return TRUE;
}



void CPicture::Toumeika(void)
{
	int* dst = (int*)m_pic;
	char* mask = m_maskPic;

	int lPitchDst = m_pictureSizeX * 4;
	int lPitchMask = m_pictureSizeX;

	int loopX = m_pictureSizeX;
	int loopY = m_pictureSizeY;

#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi


		mov esi,mask
		mov edi,dst

		mov edx,[edi]
		mov ebx,edx
		inc bl
		cmp bl,0
		jnz SKIP0
		mov bl,0feh
SKIP0:
		mov ecx,loopY
LOOP1:
		push ecx
		
		push esi
		push edi
	
		mov ecx,loopX
LOOP2:
		mov al,[esi]
		or al,al
		jnz SKIP1
		mov [edi],edx
SKIP1:
		inc esi
		add edi,4
		dec ecx
		jnz LOOP2

		pop edi
		pop esi
		add edi,lPitchDst
		add esi,lPitchMask

		pop ecx
		dec ecx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#endif

}


void CPicture::CutDataByMask(void)
{
	if (m_256Flag) return;

	char* ptr0 = (char*)m_maskPic;
	char* ptr = ptr0;

	int cutY = 0;
	char mask = *ptr;
	
	mask = 0;

	for (int j=0;j<m_pictureSizeY;j++)
	{
		int found = 0;
		for (int i=0;i<m_pictureSizeX;i++)
		{
			if ((*ptr) != mask)
			{
				found = 1;
				break;
			}
			ptr++;
		}
		if (found == 1) break;
		cutY = j+1;
	}

	if (cutY>0) cutY--;
	m_charaClipYStart = cutY;


//	int* ptr1 = (int*)m_pic;
	ptr0 = (char*)m_maskPic;
	int cutX = 0;

	for (int i=0;i<m_pictureSizeX;i++)
	{
		ptr = ptr0;
		int found = 0;
		for (int j=0;j<m_pictureSizeY;j++)
		{
			if ((*ptr) != mask)
			{
				found = 1;
				break;
			}
			ptr += m_pictureSizeX;
		}
		if (found == 1) break;
		cutX = i+1;
		ptr0++;
	}

	if (cutX>0) cutX--;
	m_charaClipXStart = cutX;


//	ptr0 = (int*)m_pic;
	ptr0 = (char*)m_maskPic;
	ptr0 += ((SSIZE_T)m_pictureSizeX-1);
	cutX = m_pictureSizeX;

	for (int i=m_pictureSizeX-1;i>=0;i--)
	{
		ptr = ptr0;
		int found = 0;
		for (int j=0;j<m_pictureSizeY;j++)
		{
			if ((*ptr) != mask)
			{
				found = 1;
				break;
			}
			ptr += m_pictureSizeX;
		}
		if (found == 1) break;
		cutX = i+1;
		ptr0--;
	}
	if (cutX<m_pictureSizeX-1) cutX++;

	m_charaClipXEnd = cutX;
}


BOOL CPicture::LoadDWQ(LPSTR filename,BOOL b256Flag,LPSTR dirName)
{
	if (strcmp(filename,m_fileName)==0) return TRUE;

	m_256Flag = b256Flag;
	m_maskExistFlag = FALSE;

	int fln = (int)strlen(filename);
	memcpy(m_fileName,filename,(SSIZE_T)fln+1);

	int rgbTable[256];

	if (dirName == NULL)
	{
		wsprintf(m_makedFileName,"%s\\%s.%s",m_dirName,m_fileName,m_extName);
	}
	else
	{
		wsprintf(m_makedFileName,"%s\\%s.%s",dirName,m_fileName,m_extName);
	}

	FILE* file = OpenDWQFile(m_makedFileName,filename);


	if (file != NULL)
	{
		//if dwq then read header and check pack type

		m_packFlag = FALSE;
//		m_dwqFlag = FALSE;
		m_jpegFlag = FALSE;
		m_maskFlag = FALSE;
		m_pngFlag = FALSE;

//		int sizeX = 0;
//		int sizeY = 0;

		int sz = LoadDWQHeader(file);

		if ((m_jpegFlag == FALSE) && (m_pngFlag == FALSE))
		{
			sz = LoadBitmapHeaderAndPalette(file,rgbTable,b256Flag);
		}

		sz += 64;
		MakeDataBuffer(sz);

		if (m_jpegFlag)
		{
			//bufferによみこむ
			CheckTmpBuffer(m_dwqSize);
			fread(m_tmpBuffer,sizeof(char),m_dwqSize,file);	//?????????????size ok???
			m_restReadSize -= m_dwqSize;

			m_jpegDecoder->Decode(m_tmpBuffer,this);
//			m_pictureSizeX = 16;
//			m_pictureSizeY = 16;


			m_charaClipXStart = 0;
			m_charaClipXEnd= m_pictureSizeX;
			m_charaClipYStart = 0;
			m_charaClipYEnd= m_pictureSizeY;

		}
		else if (m_pngFlag)
		{
#if _MSC_VER >= 1500
			m_pngLoader->LoadFile(file);

			if (b256Flag)
			{

				if (m_palette0 == NULL)
				{
					m_palette0 = new char[1024+128];
				}

				if (m_palette0 != NULL)
				{
#if defined _WIN64
					m_palette = (LPVOID)((((long long)m_palette0) + 63) & (~63));
#else
					m_palette = (LPVOID)((((int)m_palette0) + 63) & (~63));
#endif
					CopyMemory(m_palette,rgbTable,1024);
				}

				m_pngLoader->GetPic8AndPalette((char*)m_pic,(int*)m_palette);
				m_maskFlag = FALSE;
			}
			else
			{
				m_pngLoader->GetPicData((int*)m_pic);
				m_maskFlag = m_pngLoader->GetMaskFlag();
			}

			m_charaClipXStart = 0;
			m_charaClipXEnd= m_pictureSizeX;
			m_charaClipYStart = 0;
			m_charaClipYEnd= m_pictureSizeY;
#endif
		}
		else
		{
			if (m_pic0 != NULL)
			{
				CalcuReadPara();

				m_charaClipXStart = 0;
				m_charaClipXEnd= m_pictureSizeX;
				m_charaClipYStart = 0;
				m_charaClipYEnd= m_pictureSizeY;

//				if (m_dwqFlag == FALSE)
//				{
//					LoadBitmapData(file,rgbTable,b256Flag);
//				}
//				else
//				{
					if (m_packFlag == FALSE)
					{
						LoadDWQData(file,rgbTable,b256Flag);
					}
					else
					{
						LoadPackedDWQData(file,rgbTable,b256Flag);
					}
//				}
			}
		}

		m_loadOkFlag = TRUE;	//とりあえず絵はあるにゃ

		if (m_maskFlag)
		{
			//load mask data
			if (m_pngFlag == FALSE)
			{
				LoadMask(file);
			}
			else
			{
				GetPngMask();
			}

			if (m_alreadyCutFlag)
			{
				m_charaClipYStart = *((int*)(&m_dwq[16]));
				m_charaClipXStart = *((int*)(&m_dwq[20]));
				m_charaClipXEnd = m_pictureSizeX - *((int*)(&m_dwq[24]));
				m_charaClipYEnd = m_pictureSizeY - *((int*)(&m_dwq[28]));
			}
			else
			{
				CutDataByMask();
			}

			if (m_jpegFlag)
			{
////@@@???				Toumeika();
			}
		}

		fclose(file);

		if (m_genshokuFlag)
		{
			if (m_256Flag == FALSE)
			{
				if (CheckGenshokuSize(m_pictureSizeX,m_pictureSizeY))
				{
					Genshoku16();
				}
			}
		}

		return TRUE;	//load ok
	}

	if (m_errorPrintFlag)
	{
		PrintLoadError(filename);
	}

	m_loadOkFlag = FALSE;
///	m_fileName[0] = 0;	//まいかいエラーでてうざいのでこのまま
	return FALSE;
}




void CPicture::CutData(void)
{
	if (m_256Flag) return;

	int* ptr = (int*)m_pic;
	int cutY = 0;
	int mask = *ptr;


	for (int j=0;j<m_pictureSizeY;j++)
	{
		int found = 0;
		for (int i=0;i<m_pictureSizeX;i++)
		{
			if ((*ptr) != mask)
			{
				found = 1;
				break;
			}
			ptr++;
		}
		if (found == 1) break;
		cutY = j+1;
	}

	if (cutY>0) cutY--;
	m_charaClipYStart = cutY;


	int* ptr0 = (int*)m_pic;
	int cutX = 0;

	for (int i=0;i<m_pictureSizeX;i++)
	{
		int* ptr = ptr0;
		int found = 0;
		for (int j=0;j<m_pictureSizeY;j++)
		{
			if ((*ptr) != mask)
			{
				found = 1;
				break;
			}
			ptr += m_pictureSizeX;
		}
		if (found == 1) break;
		cutX = i+1;
		ptr0++;
	}

	if (cutX>0) cutX--;
	m_charaClipXStart = cutX;


	ptr0 = (int*)m_pic;
	ptr0 += ((SSIZE_T)m_pictureSizeX-1);
	cutX = m_pictureSizeX;

	for (int i=m_pictureSizeX-1;i>=0;i--)
	{
		int* ptr = ptr0;
		int found = 0;
		for (int j=0;j<m_pictureSizeY;j++)
		{
			if ((*ptr) != mask)
			{
				found = 1;
				break;
			}
			ptr += m_pictureSizeX;
		}
		if (found == 1) break;
		cutX = i+1;
		ptr0--;
	}
	if (cutX<m_pictureSizeX-1) cutX++;

	m_charaClipXEnd = cutX;
}



void CPicture::Put(int x, int y, BOOL bTransFlag)
{
	if (m_loadOkFlag == FALSE) return;

	int sx = m_pictureSizeX;
	int sy = m_pictureSizeY;

	int srcX = 0;
	int srcY = 0;

	if (!Clip(x,y,srcX,srcY,sx,sy)) return;

	Blt(x,y,srcX,srcY,sx,sy,bTransFlag);
}



void CPicture::ColorBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag, int r, int g, int b)
{
	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

//	フルカラー部分のみ作成
	if (m_256Flag) return;

//	現時点ではマスクでのみ処理

	if (CheckMaskExist() == FALSE) return;
	char* maskPic = GetMaskPic();

	SIZE srcSize;
	srcSize.cx = m_pictureSizeX;
	srcSize.cy = m_pictureSizeY;

	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;

	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;

	CAllPicture::ColorBlt(putPoint,srcPoint,putSize,maskPic,srcSize,r,g,b);
	if (bTransFlag)
	{
		return;//for warning lv4 dummy
	}
}





//for bg?
void CPicture::TransLucentBlt0(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int transPercent)
{
	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	LPVOID picData = m_pic;
	SIZE srcSize;
	srcSize.cx = m_pictureSizeX;
	srcSize.cy = m_pictureSizeY;
	CAllPicture::TransLucentBlt0(putPoint,srcPoint,putSize,picData,srcSize,transPercent);
}

void CPicture::TransLucentBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int transPercent)
{
	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	LPVOID picData = m_pic;
	SIZE srcSize;
	srcSize.cx = m_pictureSizeX;
	srcSize.cy = m_pictureSizeY;
	CAllPicture::TransLucentBlt(putPoint,srcPoint,putSize,picData,srcSize,transPercent);
}


void CPicture::TransLucentBlt2(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int transPercent)
{
	if (m_maskExistFlag)
	{
		TransLucentBlt3(x,y,srcX,srcY,sizeX,sizeY,transPercent);
		return;
	}

	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	LPVOID picData = m_pic;
	SIZE srcSize;
	srcSize.cx = m_pictureSizeX;
	srcSize.cy = m_pictureSizeY;
	CAllPicture::TransLucentBlt2(putPoint,srcPoint,putSize,picData,srcSize,transPercent);
}


void CPicture::TransLucentBlt3(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int transPercent)
{
	if (m_maskExistFlag == FALSE) return;

	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	LPVOID picData = m_pic;
	LPVOID maskPic = m_maskPic;
	SIZE srcSize;
	srcSize.cx = m_pictureSizeX;
	srcSize.cy = m_pictureSizeY;
	CAllPicture::TransLucentBlt3(putPoint,srcPoint,putSize,picData,maskPic,srcSize,transPercent);
}



void CPicture::SetDirName(LPSTR dirname)
{
	int ln = (int)strlen(dirname);
	if (ln>14) ln = 14;
	memcpy(m_dirName,dirname,ln);
	m_dirName[ln] = 0;
	m_dirName[ln+1] = 0;
}

void CPicture::SetExtName(LPSTR extname)
{
	int ln = (int)strlen(extname);
	if (ln!=3) return;

	memcpy(m_extName,extname,ln);
}


void CPicture::PrintLoadError(LPSTR filename)
{
	char mes[1024];
	wsprintf(mes,"LOAD DWQ ERROR(File Not Found)\n%s\nmode=%d",filename,m_modeNumber);
#if !defined _DEBUG
//	MessageBox(NULL,filename,"LOAD DWQ ERROR File Not Found",MB_OK | MB_ICONEXCLAMATION );
	MessageBox(NULL,mes,"Error",MB_OK | MB_ICONEXCLAMATION );
#else
	OutputDebugString("\n");
	OutputDebugString(mes);
//	OutputDebugString("\nLOAD DWQ ERROR File Not Found:");
//	OutputDebugString(filename);
#endif

}


BOOL CPicture::CheckGenshokuSize(int sizeX,int sizeY)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if ((sizeX == screenSizeX) && (sizeY == screenSizeY))
	{
		return m_genshokuJustSizeFlag;
	}

	if ((sizeX >= screenSizeX) && (sizeY >= screenSizeY))
	{
		return m_genshokuOverSizeFlag;
	}

	return m_genshokuMiniSizeFlag;
}

void CPicture::BltNega(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int ps)
{
	if (Clip(x,y,srcX,srcY,sizeX,sizeY) == FALSE) return;

	int* src = (int*)m_pic;
	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = 0;
	srcPoint.y = 0;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	SIZE picSize;
	picSize.cx = m_pictureSizeX;
	picSize.cy = m_pictureSizeY;

	CAllPicture::NegaBlt(putPoint,srcPoint,putSize,src,picSize,ps);
}



void CPicture::AntiAliasBlt2(int x, int y, int srcX, int srcY, int sizeX, int sizeY)
{
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

	if (sizeX<=0) return;
	if (sizeY<=0) return;

	int* src = (int*)m_pic;
//	int* dst = (int*)m_lpScreenBuffer;
	char* mask = (char*)m_maskPic;
	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	SIZE picSize;
	picSize.cx = m_pictureSizeX;
	picSize.cy = m_pictureSizeY;

	CAllPicture::MaskBlt(putPoint,srcPoint,putSize,src,mask,picSize);
}


void CPicture::Blt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag)
{
	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	SIZE srcSize;
	srcSize.cx = m_pictureSizeX;
	srcSize.cy = m_pictureSizeY;

	BOOL maskExistFlag = CheckMaskExist();
	char* maskData = NULL;
	if (maskExistFlag) maskData = m_maskPic;

	LPVOID picData = m_pic;

	if ((bTransFlag) && maskExistFlag)
	{
		CAllPicture::MaskBlt(putPoint,srcPoint,putSize,picData,maskData,srcSize);
		return;
	}

	if (m_256Flag)
	{
		int* lpPalette = (int*)m_palette;
		if (bTransFlag)
		{
			CAllPicture::Blt256(putPoint,srcPoint,putSize,picData,lpPalette,srcSize);
		}
		else
		{
			CAllPicture::Blt256Beta(putPoint,srcPoint,putSize,picData,lpPalette,srcSize);
		}
		return;
	}


	if (bTransFlag)
	{
		CAllPicture::Blt(putPoint,srcPoint,putSize,picData,srcSize);
		return;
	}

	CAllPicture::BltBeta(putPoint,srcPoint,putSize,picData,srcSize);
}

void CPicture::GreyBlt(int x, int y,int srcX,int srcY,int sizeX,int sizeY,BOOL bTransFlag)
{
	if (m_loadOkFlag == FALSE) return;
//	if (m_lpScreenBuffer == NULL) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	SIZE picSize;
	picSize.cx = m_pictureSizeX;
	picSize.cy = m_pictureSizeY;

	char* maskPic = NULL;
	LPVOID lpPalette = NULL;
	LPVOID srcData = m_pic;

	if (m_256Flag)
	{
		lpPalette = m_palette;
	}
	else
	{
		if (CheckMaskExist())
		{
			maskPic = m_maskPic;
		}
	}

	CAllPicture::GreyBlt(putPoint,srcPoint,putSize,srcData,picSize,maskPic,bTransFlag,lpPalette);
}

void CPicture::GreyBlt2(int x, int y,int srcX,int srcY,int sizeX,int sizeY,int ps256,BOOL bTransFlag)
{
	if (m_loadOkFlag == FALSE) return;
//	if (m_lpScreenBuffer == NULL) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	SIZE picSize;
	picSize.cx = m_pictureSizeX;
	picSize.cy = m_pictureSizeY;

	char* maskPic = NULL;
	LPVOID lpPalette = NULL;
	LPVOID srcData = m_pic;

	if (m_256Flag)
	{
		lpPalette = m_palette;
	}
	else
	{
		if (CheckMaskExist())
		{
			maskPic = m_maskPic;
		}
	}

	CAllPicture::GreyBlt2(putPoint,srcPoint,putSize,srcData,picSize,maskPic,ps256,bTransFlag,lpPalette);
}


void CPicture::SepiaBlt(int x, int y,int srcX,int srcY,int sizeX,int sizeY,int ps256,int r,int g,int b,BOOL bTransFlag)
{
	if (m_loadOkFlag == FALSE) return;
//	if (m_lpScreenBuffer == NULL) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	SIZE picSize;
	picSize.cx = m_pictureSizeX;
	picSize.cy = m_pictureSizeY;

	char* maskPic = NULL;
	LPVOID lpPalette = NULL;
	LPVOID srcData = m_pic;

	if (m_256Flag)
	{
		lpPalette = m_palette;
	}
	else
	{
		if (CheckMaskExist())
		{
			maskPic = m_maskPic;
		}
	}

	CAllPicture::SepiaBlt(putPoint,srcPoint,putSize,srcData,picSize,maskPic,ps256,r,g,b,bTransFlag,lpPalette);
}


void CPicture::ShapeBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int r, int g, int b)
{
	if (Clip(x,y,srcX,srcY,sizeX,sizeY) == FALSE) return;
	if (CheckMaskExist() == FALSE) return;

	LPVOID maskPic = GetMaskPic();
	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	SIZE srcSize = GetPicSize();
	CAllPicture::ShapeBlt(putPoint,srcPoint,putSize,maskPic,srcSize,r,g,b);
}


void CPicture::GradationShapeBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int r, int g, int b, int r2, int g2,int b2, BOOL tateFlag)
{
	if (Clip(x,y,srcX,srcY,sizeX,sizeY) == FALSE) return;
	if (CheckMaskExist() == FALSE) return;

	LPVOID maskPic = GetMaskPic();
	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	SIZE srcSize = GetPicSize();
	CAllPicture::GradationShapeBlt(putPoint,srcPoint,putSize,maskPic,srcSize,r,g,b,r2,g2,b2);
	if (tateFlag)
	{
		return;//for warning lv4 dummy
	}
}



void CPicture::RedBlt(int x, int y,int srcX,int srcY,int sizeX,int sizeY,BOOL bTransFlag)
{
	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;

	POINT dstPoint;
	dstPoint.x = x;
	dstPoint.y = y;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE srcSize = GetPicSize();

	LPVOID srcPic = m_pic;

	char* maskPic = NULL;
	if (CheckMaskExist())
	{
		maskPic = GetMaskPic();
	}
	
	LPVOID lpPalette = NULL;
	if (m_256Flag)
	{
		lpPalette = m_palette;
	}

	CAllPicture::RedBlt(dstPoint,srcPoint,putSize,srcPic,srcSize,maskPic,bTransFlag,lpPalette);
	return;
}


void CPicture::AddBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY)
{
	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;
	if (m_256Flag) return;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	LPVOID picData = m_pic;
	SIZE srcSize;
	srcSize.cx = m_pictureSizeX;
	srcSize.cy = m_pictureSizeY;
	CAllPicture::AddBlt(putPoint,srcPoint,putSize,picData,srcSize);
}


void CPicture::LightBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int lightPercent)
{
	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;
	if (m_256Flag) return;

	POINT putPoint;
	putPoint.x = x;
	putPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	LPVOID picData = m_pic;
	SIZE srcSize;
	srcSize.cx = m_pictureSizeX;
	srcSize.cy = m_pictureSizeY;
	CAllPicture::LightBlt(putPoint,srcPoint,putSize,picData,srcSize,lightPercent);
}

//256不可
//clip不十分
void CPicture::StretchBlt1(int putX, int putY, int sizeX, int sizeY, int srcX, int srcY, int srcSizeX, int srcSizeY, int transPercent , BOOL bTransFlag)
{
	if (Check256()) return;

	POINT dstPoint;
	dstPoint.x = putX;
	dstPoint.y = putY;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE dstSize;
	dstSize.cx = sizeX;
	dstSize.cy = sizeY;
	SIZE srcSize;
	srcSize.cx = srcSizeX;
	srcSize.cy = srcSizeY;
	SIZE picSize = GetPicSize();
	int* picData = (int*)(GetBuffer());

	char* maskData = NULL;
	if (CheckMaskExist())
	{
		maskData = (char*)(GetMaskPic());
	}

	CAllPicture::StrtchBlt1(dstPoint,srcPoint,dstSize,srcSize,picData,maskData,picSize,bTransFlag,transPercent);
}


void CPicture::StretchAddSubBlt(int putX, int putY, int sizeX, int sizeY, int srcX, int srcY, int srcSizeX, int srcSizeY, int transPercent , BOOL bTransFlag,int deltaR,int deltaG,int deltaB)
{
	if (Check256()) return;

	POINT dstPoint;
	dstPoint.x = putX;
	dstPoint.y = putY;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE dstSize;
	dstSize.cx = sizeX;
	dstSize.cy = sizeY;
	SIZE srcSize;
	srcSize.cx = srcSizeX;
	srcSize.cy = srcSizeY;
	SIZE picSize = GetPicSize();
	int* picData = (int*)(GetBuffer());

	char* maskData = NULL;
	if (CheckMaskExist())
	{
		maskData = (char*)(GetMaskPic());
	}

	CAllPicture::StrtchAddSubBlt(dstPoint,srcPoint,dstSize,srcSize,picData,maskData,picSize,bTransFlag,transPercent,deltaR,deltaG,deltaB);
}

void CPicture::ColorAddBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag, int r, int g, int b,int ps)
{
	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;
	if (Check256()) return;

	POINT dstPoint;
	dstPoint.x = x;
	dstPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	SIZE picSize = GetPicSize();
	int* picData = GetPictureBuffer();
	char* maskData = NULL;
	if (CheckMaskExist())
	{
		maskData = GetMaskPic();
	}

	CAllPicture::ColorAddBlt(dstPoint,srcPoint,putSize,picData,maskData,picSize,bTransFlag,r,g,b,ps);
}

void CPicture::YUVChangeBlt(int x,int y,int srcX,int srcY,int sizeX,int sizeY, BOOL yuvReverseFlag,int betaTransPercent255)
{
	if (m_loadOkFlag == FALSE) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;
	if (Check256()) return;

	POINT dstPoint;
	dstPoint.x = x;
	dstPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;
	SIZE picSize = GetPicSize();
	int* picData = GetPictureBuffer();
	char* maskData = NULL;
	if (CheckMaskExist())
	{
		maskData = GetMaskPic();
	}

	CAllPicture::YUVChangeBlt(dstPoint,srcPoint,putSize,picData,maskData,picSize,yuvReverseFlag,betaTransPercent255);
}




//percent2 もつかう
//サイズは同じでないといけない
//mask必要

BOOL CPicture::ChangeTranslateBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int ps1, int ps2, CPicture* pic2, int srcX2,int srcY2)
{
	if (Check256()) return FALSE;
	if (pic2->Check256()) return FALSE;

	BOOL maskFlag = TRUE;

	if ((CheckMaskExist() == FALSE) || (pic2->CheckMaskExist() == FALSE))
	{
		return ChangeBlt(x,y,srcX,srcY,sizeX,sizeY,ps1,ps2,pic2,srcX2,srcY2);
		maskFlag = FALSE;
	}



	int x1 = x;
	int y1 = y;
	int x2 = x;
	int y2 = y;
	int sizeX1 = sizeX;
	int sizeY1 = sizeY;
	int sizeX2 = sizeX;
	int sizeY2 = sizeY;

	int xOrg = x;
	int yOrg = y;
//	int sizeXOrg = sizeX;
//	int sizeYOrg = sizeY;

	int srcXOrg = srcX;
	int srcYOrg = srcY;
	int srcX2Org = srcX2;
	int srcY2Org = srcY2;

	if (!ClipChara(x1,y1,srcX,srcY,sizeX1,sizeY1)) return FALSE;
	if (! pic2->ClipChara(x2,y2,srcX2,srcY2,sizeX2,sizeY2)) return FALSE;

	RECT rc;
	RECT rc1;
	RECT rc2;
	SetRect(&rc1,x1,y1,x1+sizeX1,y1+sizeY1);
	SetRect(&rc2,x2,y2,x2+sizeX2,y2+sizeY2);
	UnionRect(&rc,&rc1,&rc2);


	x = rc.left;
	y = rc.top;
	sizeX = rc.right - rc.left;
	sizeY = rc.bottom - rc.top;

	int deltaX = x - xOrg;
	int deltaY = y - yOrg;

	srcX = srcXOrg + deltaX;
	srcY = srcYOrg + deltaY;

	srcX2 = srcX2Org + deltaX;
	srcY2 = srcY2Org + deltaY;



	xOrg = x;
	yOrg = y;
	if (!ClipEtc(x,y,srcX,srcY,sizeX,sizeY)) return FALSE;
	deltaX = x - xOrg;
	deltaY = y - yOrg;

	srcX2 += deltaX;
	srcY2 += deltaY;

	int xOrg2 = x;
	int yOrg2 = y;
	if (! pic2->ClipEtc(x,y,srcX2,srcY2,sizeX,sizeY)) return FALSE;
	int deltaX2 = x - xOrg2;
	int deltaY2 = y - yOrg2;

	srcX += deltaX2;
	srcY += deltaY2;







	POINT dstPoint;
	dstPoint.x = x;
	dstPoint.y = y;
//	POINT srcPoint;
//	srcPoint.x = srcX;
//	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;

	SIZE srcSize=GetPicSize();
	SIZE srcSize2=pic2->GetPicSize();

//	CAllPicture::ChangeTransLucentBlt3D(texture1,texture2,dstPoint,srcPoint,srcPoint2,putSize,ps1,ps2);

	
	int* srcData = GetPictureBuffer();
	int* srcData2 = pic2->GetPictureBuffer();

	char* maskData = GetMaskPic();
	char* maskData2 = pic2->GetMaskPic();

	srcData += srcX;
	srcData += (SSIZE_T)srcSize.cx * srcY;
	maskData += srcX;
	maskData += (SSIZE_T)srcSize.cx * srcY;

	srcData2 += srcX2;
	srcData2 += (SSIZE_T)srcSize2.cx * srcY2;
	maskData2 += srcX2;
	maskData2 += (SSIZE_T)srcSize2.cx * srcY2;

	CAllPicture::ChangeTransLucentBlt(dstPoint,putSize,srcData,srcData2,maskData,maskData2,srcSize,srcSize2,ps1,ps2);

	return TRUE;
}


//percent2 もつかう
//サイズは同じでないといけない

BOOL CPicture::ChangeBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int ps1, int ps2, CPicture* pic2, int srcX2,int srcY2)
{

	int x1 = x;
	int y1 = y;
	int x2 = x;
	int y2 = y;
	int sizeX1 = sizeX;
	int sizeY1 = sizeY;
	int sizeX2 = sizeX;
	int sizeY2 = sizeY;

	int xOrg = x;
	int yOrg = y;
//	int sizeXOrg = sizeX;
//	int sizeYOrg = sizeY;

	int srcXOrg = srcX;
	int srcYOrg = srcY;
	int srcX2Org = srcX2;
	int srcY2Org = srcY2;

	if (!ClipChara(x1,y1,srcX,srcY,sizeX1,sizeY1)) return FALSE;
	if (! pic2->ClipChara(x2,y2,srcX2,srcY2,sizeX2,sizeY2)) return FALSE;

	RECT rc;
	RECT rc1;
	RECT rc2;
	SetRect(&rc1,x1,y1,x1+sizeX1,y1+sizeY1);
	SetRect(&rc2,x2,y2,x2+sizeX2,y2+sizeY2);
	UnionRect(&rc,&rc1,&rc2);


	x = rc.left;
	y = rc.top;
	sizeX = rc.right - rc.left;
	sizeY = rc.bottom - rc.top;

	int deltaX = x - xOrg;
	int deltaY = y - yOrg;

	srcX = srcXOrg + deltaX;
	srcY = srcYOrg + deltaY;

	srcX2 = srcX2Org + deltaX;
	srcY2 = srcY2Org + deltaY;



	xOrg = x;
	yOrg = y;
	if (!ClipEtc(x,y,srcX,srcY,sizeX,sizeY)) return FALSE;
	deltaX = x - xOrg;
	deltaY = y - yOrg;

	srcX2 += deltaX;
	srcY2 += deltaY;

	int xOrg2 = x;
	int yOrg2 = y;
	if (! pic2->ClipEtc(x,y,srcX2,srcY2,sizeX,sizeY)) return FALSE;
	int deltaX2 = x - xOrg2;
	int deltaY2 = y - yOrg2;

	srcX += deltaX2;
	srcY += deltaY2;







	POINT dstPoint;
	dstPoint.x = x;
	dstPoint.y = y;
//	POINT srcPoint;
//	srcPoint.x = srcX;
//	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;

	SIZE srcSize=GetPicSize();
	SIZE srcSize2=pic2->GetPicSize();

//	CAllPicture::ChangeTransLucentBlt3D(texture1,texture2,dstPoint,srcPoint,srcPoint2,putSize,ps1,ps2);

	if (Check256() && (pic2->Check256()))
	{

		char* srcData = (char*)GetPictureBuffer();
		char* srcData2 = (char*)(pic2->GetPictureBuffer());
		srcData += srcX;
		srcData += (SSIZE_T)srcSize.cx * srcY;
		srcData2 += srcX2;
		srcData2 += (SSIZE_T)srcSize2.cx * srcY2;
		int* paletteData = (int*)GetPalette();
		int* paletteData2 = (int*)(pic2->GetPalette());

		CAllPicture::ChangeBlt256Beta(dstPoint,putSize,srcData,srcData2,paletteData,paletteData2,srcSize,srcSize2,ps1,ps2);

		return TRUE;
	}


	int* srcData = GetPictureBuffer();
	int* srcData2 = pic2->GetPictureBuffer();

	char* maskData = NULL;
	char* maskData2 = NULL;
/*
	if (maskFlag)
	{
		maskData = GetMaskPic();
		maskData2 = pic2->GetMaskPic();
		maskData += srcX;
		maskData += srcSize.cx * srcY;
		maskData2 += srcX2;
		maskData2 += srcSize2.cx * srcY2;
	}
*/

	srcData += srcX;
	srcData += (SSIZE_T)srcSize.cx * srcY;
	srcData2 += srcX2;
	srcData2 += (SSIZE_T)srcSize2.cx * srcY2;


	CAllPicture::ChangeTransLucentBlt(dstPoint,putSize,srcData,srcData2,maskData,maskData2,srcSize,srcSize2,ps1,ps2);

	return TRUE;
}


void CPicture::AddSubBlt(int x,int y,int srcX,int srcY,int sizeX,int sizeY,int ps)
{
	if (m_loadOkFlag == FALSE) return;
	if (Check256()) return;
	if (!Clip(x,y,srcX,srcY,sizeX,sizeY)) return;


	POINT dstPoint;
	dstPoint.x = x;
	dstPoint.y = y;

	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;

	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;

	SIZE picSize = GetPicSize();

	int* picData = GetPictureBuffer();
	char* maskData = NULL;
	if (CheckMaskExist())
	{
		maskData = GetMaskPic();
	}

	CAllPicture::AddSubBlt(dstPoint,srcPoint,putSize,picData,maskData,picSize,ps);
}


//BOOL CPicture::ChangeTranslateBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int ps1, int ps2, int* lpPic2, char* lpMask2, CPicture* pic2)
/*
{
	//clip large
	if (!ClipCharaLarge(x,y,srcX,srcY,sizeX,sizeY,pic2)) return FALSE;
	if (!ClipEtc(x,y,srcX,srcY,sizeX,sizeY)) return FALSE;

	if (Check256()) return FALSE;
	if (pic2->Check256()) return FALSE;


	POINT dstPoint;
	dstPoint.x = x;
	dstPoint.y = y;
	POINT srcPoint;
	srcPoint.x = srcX;
	srcPoint.y = srcY;
	SIZE putSize;
	putSize.cx = sizeX;
	putSize.cy = sizeY;

	SIZE srcSize=GetPicSize();
	SIZE srcSize2=pic2->GetPicSize();
	if (srcSize.cx != srcSize2.cx) return FALSE;
	if (srcSize.cy != srcSize2.cy) return FALSE;

	if (CheckMaskExist() == FALSE) return FALSE;
	if (pic2->CheckMaskExist() == FALSE) return FALSE;

	int* srcData = GetPictureBuffer();
	int* srcData2 = lpPic2;

	char* maskData = GetMaskPic();
	char* maskData2 = lpMask2;

	CAllPicture::ChangeTransLucentBlt(dstPoint,srcPoint,putSize,srcData,srcData2,maskData,maskData2,srcSize,ps1,ps2);
	return TRUE;
}
*/

void CPicture::DarkMaskBlt(int x, int y, int srcX, int srcY, int sizeX, int sizeY, int r, int g, int b)
{
	ColorAddBlt(x,y,srcX,srcY,sizeX,sizeY,TRUE,-r,-g,-b);
}

void CPicture::DeltaBlt(int putX, int putY, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag, int* deltaPtr)
{
	if ((sizeX<=0) || (sizeY<=0)) return;

	//tate clip
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	RECT rc;
	GetPicSize(&rc);
	int picSizeX = rc.right;
//	int picSizeY = rc.bottom;

	int* src = (int*)(GetBuffer());
	int md = 0;
	if (bTransFlag)
	{
		md = 2;
		if (CheckMaskExist() == FALSE) md = 1;
	}

	char* mask = GetMaskPic();
	if (md == 2)
	{
		if (mask == NULL)
		{
			md = 1;
		}
	}


	int lPitch = screenSizeX * sizeof(int);
	int maskPitch = picSizeX * sizeof(char);
	int srcPitch = picSizeX * sizeof(int);


	if (putY<0)
	{
		srcY += (-putY);
		deltaPtr += (-putY);
		sizeY -= (-putY);
		putY = 0;
		if (sizeY<=0) return;
	}

	if (putY>=screenSizeY) return;
	if ((putY+sizeY) > screenSizeY)
	{
		sizeY = screenSizeY - putY;
		if (sizeY<=0) return;
	}

	src += (SSIZE_T)picSizeX * srcY;
	src += srcX;

	if (md == 2)
	{
		mask += (SSIZE_T)picSizeX * srcY;
		mask += srcX;
	}

	//int* dst = (int*)m_lpScreenBuffer;
	int* dst = CMyGraphics::GetScreenBuffer();
	dst += (SSIZE_T)putY * screenSizeX;

	int putX2 = putX;



	int* workPtr = deltaPtr;
	int loopY = sizeY;
	int loopX = sizeX;	//@



	if (md == 2)
	{
#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			pxor mm0,mm0

			mov eax,255
			movd mm7,eax
			punpcklwd mm7,mm7
			punpckldq mm7,mm7

			mov edx,workPtr
			mov esi,src
			mov edi,dst
			mov ebx,mask
			mov ecx,loopY
LOOP1:
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov eax,putX2
			add eax,[edx]
			cmp eax,screenSizeX
			jns SKIP
			mov edx,eax
			shl edx,2
			add edi,edx

			mov ecx,loopX
			mov edx,eax
			cmp eax,0
			jns OK1
			add ecx,eax
			cmp ecx,1
			js SKIP
			sub ebx,eax
			shl eax,2
			sub esi,eax
			sub edi,eax
			xor edx,edx
OK1:
			mov eax,edx
			add eax,ecx
			cmp eax,screenSizeX
			js OK2

			mov ecx,screenSizeX
			sub ecx,edx
			cmp ecx,1
			js SKIP
OK2:

LOOP2:
			xor eax,eax
			mov al,[ebx]
			or eax,eax
			jz SKIP3
			cmp eax,255
			jz NORMAL

			movd mm1,eax
	//		punpcklbw mm1,mm0
			punpcklwd mm1,mm1
			punpckldq mm1,mm1

			movq mm2,mm7
			psubw mm2,mm1

			mov eax,[esi]
			mov edx,[edi]
			movd mm3,eax
			movd mm4,edx
			punpcklbw mm3,mm0
			pmullw mm3,mm1
			punpcklbw mm4,mm0
			pmullw mm4,mm2
			psrlw mm3,8
			//				stall
			psrlw mm4,8
			paddw mm3,mm4
			packuswb mm3,mm0
			movd edx,mm3
			jmp LAST

NORMAL:
			mov edx,[esi]
LAST:
			mov [edi],edx
SKIP3:
			inc ebx
			add esi,4
			add edi,4
			dec ecx
			jnz LOOP2


SKIP:
			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx

			add edi,lPitch
			add esi,srcPitch
			add ebx,maskPitch
			add edx,4
			dec ecx
			jnz LOOP1

			emms

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
#endif
	}

	if (md == 0)
	{
#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			cld

			pxor mm0,mm0

			mov edx,workPtr
			mov esi,src
			mov edi,dst
//			mov ebx,mask
			mov ecx,loopY
LOOP1C:
//			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov eax,putX2
			add eax,[edx]
			cmp eax,screenSizeX
			jns SKIPC

			mov edx,eax
			shl edx,2
			add edi,edx

			mov ecx,loopX
//			mov edx,eax
			cmp eax,0
			jns OK1C
			add ecx,eax
			cmp ecx,1
			js SKIPC
//			sub ebx,eax
//			shl eax,2
			sub esi,edx
			sub edi,edx
			xor eax,eax
OK1C:
			mov edx,eax
			add eax,ecx
			cmp eax,screenSizeX
			js OK2C

			mov ecx,screenSizeX
			sub ecx,edx
			cmp ecx,1
			js SKIPC
OK2C:
			rep movsd

SKIPC:
			pop edi
			pop esi
			pop edx
			pop ecx
//			pop ebx

			add edi,lPitch
			add esi,srcPitch
//			add ebx,maskPitch
			add edx,4
			dec ecx
			jnz LOOP1C


			emms

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
#endif
	}

}

void CPicture::LeftBlt(int putX, int putY, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag, int* cutPtr,int ps)
{
	if (m_loadOkFlag == FALSE) return;
	if (ps>100) ps = 100;//dummy for warning lv4
//	if (m_lpScreenBuffer == NULL) return;

//	int oldPutX = putX;
	int oldPutY = putY;
	if (!Clip(putX,putY,srcX,srcY,sizeX,sizeY)) return;

	if (oldPutY < putY)
	{
		cutPtr += ((SSIZE_T)putY - oldPutY);
	}


	int md = 0;
	if (bTransFlag)
	{
		md = 2;
		if (CheckMaskExist() == FALSE) md = 1;
	}

//	int screenSizeX = m_screenSizeX;
//	int screenSizeY = m_screenSizeY;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int* src = (int*)(GetBuffer());
	char* mask = GetMaskPic();
	int srcStartX = srcX;
	int* dst = CMyGraphics::GetScreenBuffer();

	RECT rc;
	GetPicSize(&rc);
	int picSizeX = rc.right;
//	int picSizeY = rc.bottom;

	if (md == 2)
	{
		if (mask == NULL) md = 1;
	}

	src += srcX;
	src += (SSIZE_T)srcY * picSizeX;

	dst += putX;
	dst += (SSIZE_T)putY * screenSizeX;

	if (md == 2)
	{
		mask += srcX;
		mask += (SSIZE_T)srcY * picSizeX;
	}

	int* workPtr = cutPtr;


	int lPitch = screenSizeX * sizeof(int);
	int srcPitch = picSizeX * sizeof(int);
	int maskPitch = picSizeX;

	int loopY = sizeY;
	int loopX = sizeX;

	int ps256 = (ps * 256) / 100;

	if (md == 2)
	{
#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			pxor mm0,mm0

			mov esi,src
			mov edi,dst
			mov ebx,mask
			mov ecx,loopY
			mov edx,workPtr
LOOP1:
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov ecx,loopX
			mov eax,[edx]
			sub eax,srcStartX
			cmp eax,ecx
			jns OK1
			mov ecx,eax
			cmp ecx,1
			js SKIP1
OK1:
LOOP2:

			xor eax,eax
			mov al,[ebx]
			or eax,eax
			jz SKIP2

			mov edx,ps256
			cmp edx,256
			jz NOTMUL
			mul edx
			shr eax,8
NOTMUL:

			cmp eax,0ffh
			jnz TRANS
			mov eax,[esi]
			mov [edi],eax
			jmp SKIP2
TRANS:
			movd mm1,[esi]
			movd mm4,eax
			neg eax
			movd mm2,[edi]
			add eax,256
			punpcklbw mm1,mm0
			movd mm5,eax
			punpcklbw mm2,mm0

			punpcklwd mm4,mm4
			punpcklwd mm5,mm5
			punpckldq mm4,mm4
			punpckldq mm5,mm5
	
			pmullw mm1,mm4
			pmullw mm2,mm5

			psrlw mm1,8
			psrlw mm2,8

			paddw mm1,mm2
			packuswb mm1,mm0

			movd eax,mm1

			mov [edi],eax
SKIP2:
			add esi,4
			add edi,4
			inc ebx
			dec ecx
			jnz LOOP2

SKIP1:
			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			add edi,lPitch
			add esi,srcPitch
			add edx,4
			add ebx,maskPitch
			dec ecx
			jnz LOOP1

			emms

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
#endif
	}

}

void CPicture::RightBlt(int putX, int putY, int srcX, int srcY, int sizeX, int sizeY, BOOL bTransFlag, int* cutPtr,int ps)
{
	if (m_loadOkFlag == FALSE) return;
//	if (m_lpScreenBuffer == NULL) return;
	if (ps>100) ps = 100;//dummy for warning lv4

//	int oldPutX = putX;
	int oldPutY = putY;
	if (!Clip(putX,putY,srcX,srcY,sizeX,sizeY)) return;

	if (oldPutY < putY)
	{
		cutPtr += ((SSIZE_T)putY - oldPutY);
	}


	int md = 0;
	if (bTransFlag)
	{
		md = 2;
		if (CheckMaskExist() == FALSE) md = 1;
	}


//	int screenSizeX = m_screenSizeX;
//	int screenSizeY = m_screenSizeY;
	int screenSizeX = CMyGraphics::GetScreenSizeX();
//	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int* src = (int*)(GetBuffer());
	char* mask = GetMaskPic();
	int srcStartX = srcX;
	int* dst = CMyGraphics::GetScreenBuffer();

	RECT rc;
	GetPicSize(&rc);
	int picSizeX = rc.right;
//	int picSizeY = rc.bottom;

	if (md == 2)
	{
		if (mask == NULL) md = 1;
	}

	src += srcX;
	src += (SSIZE_T)srcY * picSizeX;

	dst += putX;
	dst += (SSIZE_T)putY * screenSizeX;

	if (md == 2)
	{
		mask += srcX;
		mask += (SSIZE_T)srcY * picSizeX;
	}

	int* workPtr = cutPtr;


	int lPitch = screenSizeX * sizeof(int);
	int srcPitch = picSizeX * sizeof(int);
	int maskPitch = picSizeX;

	int loopY = sizeY;
	int loopX = sizeX;

	int ps256 = (ps * 256) / 100;

	if (md == 2)
	{
#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi

			pxor mm0,mm0

			mov esi,src
			mov edi,dst
			mov ebx,mask
			mov ecx,loopY
			mov edx,workPtr
LOOP1:
			push ebx
			push ecx
			push edx
			push esi
			push edi

			mov ecx,loopX
			mov eax,[edx]
			sub eax,srcStartX
			js OK1
			sub ecx,eax
			cmp ecx,1
			js SKIP1

			add ebx,eax
			shl eax,2
			add edi,eax
			add esi,eax
OK1:
LOOP2:

			xor eax,eax
			mov al,[ebx]
			or eax,eax
			jz SKIP2

			mov edx,ps256
			cmp edx,256
			jz NOTMUL
			mul edx
			shr eax,8
NOTMUL:

			cmp eax,0ffh
			jnz TRANS
			mov eax,[esi]
			mov [edi],eax
			jmp SKIP2
TRANS:
			movd mm1,[esi]
			movd mm4,eax
			neg eax
			movd mm2,[edi]
			add eax,256
			punpcklbw mm1,mm0
			movd mm5,eax
			punpcklbw mm2,mm0

			punpcklwd mm4,mm4
			punpcklwd mm5,mm5
			punpckldq mm4,mm4
			punpckldq mm5,mm5
	
			pmullw mm1,mm4
			pmullw mm2,mm5

			psrlw mm1,8
			psrlw mm2,8

			paddw mm1,mm2
			packuswb mm1,mm0

			movd eax,mm1

			mov [edi],eax
SKIP2:
			add esi,4
			add edi,4
			inc ebx
			dec ecx
			jnz LOOP2

SKIP1:
			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			add edi,lPitch
			add esi,srcPitch
			add edx,4
			add ebx,maskPitch
			dec ecx
			jnz LOOP1

			emms

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}
#endif

	}

}


void CPicture::Overrap2(int percent, POINT* lpPoint)
{
//	if (m_overrap == NULL) return;
	if (Check256()) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	POINT startPoint;
	POINT endPoint;

	startPoint.x = 0;
	startPoint.y = 0;
	endPoint.x = 0;
	endPoint.y = 0;

	if (lpPoint != NULL)
	{
		endPoint = *lpPoint;
	}


	RECT rc;
	GetPicSize(&rc);
	if (rc.right<screenSizeX) return;
	if (rc.bottom<screenSizeY) return;

	if (endPoint.x<0) return;
	if (endPoint.y<0) return;
	if ((endPoint.x + screenSizeX) > rc.right) return;
	if ((endPoint.y + screenSizeY) > rc.bottom) return;

	if (percent<0) percent = 0;
	if (percent>100) percent = 100;

//	m_overrap->PrintWithScreen(this, 100-percent, percent,&endPoint);

	SIZE picSize = GetPicSize();
	int* picData = GetPictureBuffer();
	CAllPicture::OverrapBltWithScreen(endPoint,picData,picSize,100-percent,percent);
}



void CPicture::Overrap(CPicture* nextPic, int nextPercent,POINT* lpStartPoint, POINT* lpEndPoint)
{
//	if (m_overrap == NULL) return;
	if (nextPic == NULL) return;

	if (Check256()) return;
	if (nextPic->Check256()) return;


	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	POINT startPoint;
	POINT endPoint;
	startPoint.x = 0;
	startPoint.y = 0;
	endPoint.x = 0;
	endPoint.y = 0;

	if (lpStartPoint != NULL)
	{
		startPoint = *lpStartPoint;
	}

	if (lpEndPoint != NULL)
	{
		endPoint = *lpEndPoint;
	}


	RECT rc;
	GetPicSize(&rc);
	if (rc.right<screenSizeX) return;
	if (rc.bottom<screenSizeY) return;

	if (startPoint.x<0) return;
	if (startPoint.y<0) return;
	if ((startPoint.x + screenSizeX) > rc.right) return;
	if ((startPoint.y + screenSizeY) > rc.bottom) return;


	nextPic->GetPicSize(&rc);
	if (rc.right<screenSizeX) return;
	if (rc.bottom<screenSizeY) return;

	if (endPoint.x<0) return;
	if (endPoint.y<0) return;
	if ((endPoint.x + screenSizeX) > rc.right) return;
	if ((endPoint.y + screenSizeY) > rc.bottom) return;

	if (nextPercent<0) nextPercent = 0;
	if (nextPercent>100) nextPercent = 100;


	int* startPic = GetPictureBuffer();
	int* endPic = nextPic->GetPictureBuffer();

	SIZE startPicSize = GetPicSize();
	SIZE endPicSize = nextPic->GetPicSize();
//	m_overrap->Print(this, nextPic, 100-nextPercent, nextPercent,&startPoint,&endPoint);
	CAllPicture::OverrapBlt(startPoint,startPic,startPicSize,endPoint,endPic,endPicSize,100-nextPercent,nextPercent);
}


void CPicture::GetPicSize(RECT* lpRect)
{
	lpRect->left = 0;
	lpRect->top = 0;
	lpRect->right = m_pictureSizeX;
	lpRect->bottom = m_pictureSizeY;

}

SIZE CPicture::GetPicSize(void)
{
	SIZE sz;

	sz.cx = m_pictureSizeX;
	sz.cy = m_pictureSizeY;

	return sz;
}


void* CPicture::GetBuffer(void)
{
	return m_pic;
}


BOOL CPicture::ClipChara(int& x,int& y,int& srcX, int& srcY, int& sizeX, int& sizeY)
{
	//src clip by characlip

	if (srcX<m_charaClipXStart)
	{
		int dltX = m_charaClipXStart - srcX;
		srcX = m_charaClipXStart;
		x += dltX;
		sizeX -= dltX;
		if (sizeX<=0) return FALSE;
	}

	if (srcY<m_charaClipYStart)
	{
		int dltY = m_charaClipYStart - srcY;
		srcY = m_charaClipYStart;
		y += dltY;
		sizeY -= dltY;
		if (sizeY<=0) return FALSE;
	}

	if ((srcX+sizeX) > m_charaClipXEnd)
	{
		int dltX = (srcX + sizeX) - m_charaClipXEnd;
		sizeX -= dltX;
		if (sizeX<=0) return FALSE;
	}

	if ((srcY+sizeY) > m_charaClipYEnd)
	{
		int dltY = (srcY + sizeY) - m_charaClipYEnd;
		sizeY -= dltY;
		if (sizeY<=0) return FALSE;
	}

	return TRUE;
}

BOOL CPicture::ClipCharaLarge(int& x,int& y,int& srcX, int& srcY, int& sizeX, int& sizeY,CPicture* pic2)
{
	//src clip by characlip


	int clipXStart = pic2->m_charaClipXStart;
	int clipXEnd = pic2->m_charaClipXEnd;
	int clipYStart = pic2->m_charaClipYStart;
	int clipYEnd = pic2->m_charaClipYEnd;

	if (clipXStart>m_charaClipXStart) clipXStart = m_charaClipXStart;
	if (clipXEnd<m_charaClipXEnd) clipXEnd = m_charaClipXEnd;
	
	if (clipYStart>m_charaClipYStart) clipYStart = m_charaClipYStart;
	if (clipYEnd<m_charaClipYEnd) clipYEnd = m_charaClipYEnd;


	if (srcX<clipXStart)
	{
		int dltX =clipXStart - srcX;
		srcX = clipXStart;
		x += dltX;
		sizeX -= dltX;
		if (sizeX<=0) return FALSE;
	}

	if (srcY<clipYStart)
	{
		int dltY = clipYStart - srcY;
		srcY = clipYStart;
		y += dltY;
		sizeY -= dltY;
		if (sizeY<=0) return FALSE;
	}

	if ((srcX+sizeX) > clipXEnd)
	{
		int dltX = (srcX + sizeX) - clipXEnd;
		sizeX -= dltX;
		if (sizeX<=0) return FALSE;
	}

	if ((srcY+sizeY) > clipYEnd)
	{
		int dltY = (srcY + sizeY) - clipYEnd;
		sizeY -= dltY;
		if (sizeY<=0) return FALSE;
	}

	return TRUE;
}

BOOL CPicture::ClipEtc(int& x,int& y,int& srcX, int& srcY, int& sizeX, int& sizeY)
{
	int ex = x + sizeX;
	int ey = y + sizeY;

	int screenStartX = CMyGraphics::GetScreenClipStartX();
	int screenStartY = CMyGraphics::GetScreenClipStartY();
	int screenEndX = CMyGraphics::GetScreenClipEndX();
	int screenEndY = CMyGraphics::GetScreenClipEndY();

	if (
			(ex <= screenStartX) || 
			(ey <= screenStartY) ||
			(x > screenEndX) ||
			(y > screenEndY)
		)
	{
		sizeX = 0;
		sizeY = 0;
		return FALSE;
	}

	if (x<screenStartX)
	{
		int dx = screenStartX - x;
		x = screenStartX;
		sizeX -= dx;
		srcX += dx;
	}

	if (y<screenStartY)
	{
		int dy = screenStartY - y;
		y = screenStartY;
		sizeY -= dy;
		srcY += dy;
	}

	if (srcX<0)
	{
		int dx = -srcX;
		sizeX -= dx;
		srcX += dx;
	}

	if (srcY<0)
	{
		int dy = -srcY;
		sizeY -= dy;
		srcY += dy;
	}


	if (ex>screenEndX)
	{
		sizeX -= (ex - screenEndX);
	}

	if (ey>screenEndY)
	{
		sizeY -= (ey - screenEndY );
	}

	int ex2 = srcX + sizeX;
	int ey2 = srcY + sizeY;

	if (ex2>m_pictureSizeX)
	{
		sizeX -= (ex2 - m_pictureSizeX);
	}

	if (ey2>m_pictureSizeY)
	{
		sizeY -= (ey2 - m_pictureSizeY);
	}


	if ((sizeX<=0) || (sizeY<=0))
	{
		sizeX = 0;
		sizeY = 0;
		return FALSE;
	}

	if ((srcX>=m_pictureSizeX) || (srcY >= m_pictureSizeY))
	{
		sizeX = 0;
		sizeY = 0;
		return FALSE;
	}

	return TRUE;
}


BOOL CPicture::Clip(int& x,int& y,int& srcX, int& srcY, int& sizeX, int& sizeY)
{
	if (ClipChara(x,y,srcX,srcY,sizeX,sizeY) == FALSE) return FALSE;
	return ClipEtc(x,y,srcX,srcY,sizeX,sizeY);
}


void CPicture::SetMaskExist(BOOL flg)
{
	m_maskExistFlag = flg;
}

BOOL CPicture::CheckMaskExist(void)
{
	return m_maskExistFlag;
}

char* CPicture::GetMaskPic(void)
{
	return m_maskPic;
}

int* CPicture::GetPictureBuffer(void)
{
	return (int*)m_pic;
}

BOOL CPicture::Check256(void)
{
	return m_256Flag;
}


//あとでこうそくか
void CPicture::Genshoku16(void)
{
	if (m_bpp != 16) return;
	if (m_genshoku16 != NULL)
	{
		m_genshoku16->GenshokuMain(this);
	}
}

BOOL CPicture::GetScreen(int x, int y, int sizeX, int sizeY)
{
	if (sizeX == -1) sizeX = m_pictureSizeX;
	if (sizeY == -1) sizeY = m_pictureSizeY;
	if ((sizeX<1) || (sizeY<1)) return FALSE;

	if (m_256Flag) return FALSE;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	if (m_pic == NULL) return FALSE;
	if (m_pictureSizeX<sizeX) return FALSE;
	if (m_pictureSizeY<sizeY) return FALSE;

	int putX = 0;
	int putY = 0;

	if (x<0)
	{
		sizeX -= (-x);
		putX += (-x);
		x = 0;
	}

	if (y<0)
	{
		sizeY -= (-y);
		putY += (-y);
		y = 0;
	}

	if (sizeX<=0) return FALSE;
	if (sizeY<=0) return FALSE;

	if ((x+sizeX)>screenSizeX)
	{
		sizeX = screenSizeX - x;
	}

	if ((y+sizeY)>screenSizeY)
	{
		sizeY = screenSizeY - y;
	}

	if (sizeX<=0) return FALSE;
	if (sizeY<=0) return FALSE;


	int* src = CMyGraphics::GetScreenBuffer();
	int* dst = (int*)m_pic;
	
	dst += putX;
	dst += (SSIZE_T)putY * m_pictureSizeX;

	int lPitch = 4 * m_pictureSizeX;

	src += x;
	src += (SSIZE_T)y * screenSizeX;


	int loopX = sizeX;
	int loopY = sizeY;

	int srcPitch = screenSizeX * 4;

#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

	__asm
	{
		push eax
		push ebx
		push ecx
		push edx
		push esi
		push edi

		cld

		mov esi,src
		mov edi,dst
		mov ebx,lPitch

		mov edx,loopY
LOOP1:
		push esi
		push edi
		mov ecx,loopX
		rep movsd
		pop edi
		pop esi

		add esi,srcPitch
		add edi,ebx

		dec edx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#endif

	SetMaskExist(FALSE);

	Flush();
	return TRUE;
}



BOOL CPicture::GetScreen(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if ((m_pic == NULL)|| (m_pictureSizeX<screenSizeX) ||(m_pictureSizeY<screenSizeY) ||(m_256Flag))
	{
		ReSize(screenSizeX,screenSizeY);
	}

	if (m_pic == NULL) return FALSE;
	if ((m_pictureSizeX<screenSizeX) ||(m_pictureSizeY<screenSizeY) ||(m_256Flag)) return FALSE;


	int* src = CMyGraphics::GetScreenBuffer();
	int* dst = (int*)m_pic;


	int lPitch = 4 * m_pictureSizeX;

	int srcPitch = screenSizeX * 4;
	int srcLoopX = screenSizeX;
	int srcLoopY = screenSizeY;

#if defined _WIN64
#pragma message("ここにc++実装が必要にゃ " __FILE__)

#else

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
		mov ebx,lPitch

		mov edx,srcLoopY
LOOP1:
		push esi
		push edi
		mov ecx,srcLoopX
		cld
		rep movsd
		pop edi
		pop esi

		add esi,srcPitch
		add edi,ebx

		dec edx
		jnz LOOP1

		pop edi
		pop esi
		pop edx
		pop ecx
		pop ebx
		pop eax
	}
#endif

	Flush();
	return TRUE;
}

BOOL CPicture::CheckOnPic(int x, int y,int transPointX,int transPointY)
{
	if (m_pic == NULL) return FALSE;

	if ((x<0) || (y<0) || (x>=m_pictureSizeX) || (y>=m_pictureSizeY)) return FALSE;

	if (m_256Flag)
	{
		char* ptr = (char*)m_pic;
		
		char trans = *(ptr + transPointX + (SSIZE_T)transPointY * m_pictureSizeX);

		ptr += x;
		ptr += (SSIZE_T)y * m_pictureSizeX;

		char dt = *ptr;

		if (dt != trans) return TRUE;
	}
	else
	{
		if (m_maskFlag)
		{
			char* ptr = (char*)m_maskPic;
			if (ptr == NULL) return FALSE;
//			int trans = *(ptr + transPointX + transPointY * m_pictureSizeX);
			ptr += x;
			ptr += (SSIZE_T)y * m_pictureSizeX;
			char dt = *ptr;
//			if (dt != trans) return TRUE;
			if (dt != 0) return TRUE;
		}
		else
		{
			int* ptr = (int*)m_pic;
			if (ptr == NULL) return FALSE;
			int trans = *(ptr + transPointX + (SSIZE_T)transPointY * m_pictureSizeX);
			ptr += x;
			ptr += (SSIZE_T)y * m_pictureSizeX;
			int dt = *ptr;
			if (dt != trans) return TRUE;
		}
	}

	return FALSE;
}



BOOL CPicture::ReSize(int x, int y)
{
	SSIZE_T sz = (SSIZE_T)x * y;
	if (m_256Flag == FALSE) sz *= 4;

	if (sz <= m_picBufferSize)
	{
		m_pictureSizeX = x;
		m_pictureSizeY = y;

		m_charaClipXStart = 0;
		m_charaClipXEnd= m_pictureSizeX;
		m_charaClipYStart = 0;
		m_charaClipYEnd= m_pictureSizeY;

//		m_bmpSizeX = (x + 3) & ~3;
//		m_bmpSizeY = y;

		return TRUE;
	}
	

	if (MakeDataBuffer(sz + 64))
	{
		m_pictureSizeX = x;
		m_pictureSizeY = y;

		m_charaClipXStart = 0;
		m_charaClipXEnd= m_pictureSizeX;
		m_charaClipYStart = 0;
		m_charaClipYEnd= m_pictureSizeY;



		int sz = m_pictureSizeX * m_pictureSizeY;

		if ((sz>m_maskSize) && (m_maskPic0 != NULL))
		{
			DELETEARRAY(m_maskPic0);
			m_maskPic = NULL;
			m_maskSize = 0;
		}

		if (sz>m_maskSize)
		{
			char* ptr = new char[(SSIZE_T)sz+128];
			if (ptr != NULL)
			{
				DELETEARRAY(m_maskPic0);
				m_maskPic0 = ptr;

#if defined _WIN64
				long long p2 = (long long)ptr;
#else
				int p2 = (int)ptr;
#endif
				p2 += 63;
				p2 &= (~63);
				m_maskPic = (char*)p2;

				m_maskSize = sz;
			}
		}

		return TRUE;
	}



	return FALSE;
}

int CPicture::GetlPitch(void)
{
	return m_pictureSizeX;
}

void* CPicture::GetPalette(void)
{
	return m_palette;
}

LPSTR CPicture::GetFileName(void)
{
	return m_fileName;
}

int CPicture::GetFileMode(void)
{
	if (m_maskExistFlag) return 2;
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


void CPicture::Shrink()
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if ((m_pictureSizeX < screenSizeX) || (m_pictureSizeY < screenSizeY))
	{
	//	return;
	}

	SSIZE_T sz = (SSIZE_T)m_pictureSizeX * m_pictureSizeY * sizeof(int);
	//if (b256Flag)
	//{
	//	sz = (SSIZE_T)sizeX * sizeY;
	//}

	LPVOID lp0 = new char[sz + 128];
	if (lp0 != NULL)
	{
#if defined _WIN64
		long long p = (long long)m_pic0;
#else
		int p = (int)lp0;
#endif
		p += 63;
		p &= (~63);
	//	p += 128;
		LPVOID lp = (LPVOID)p;

		//copy
		memcpy(lp, m_pic, sz);
	//	DELETEARRAY(m_pic);
		DELETEARRAY(m_pic0);
		m_pic = lp;
		m_pic0 = lp0;
		m_picBufferSize = sz;
	}
}

void CPicture::CheckTmpBuffer(int checkSize)
{
	if (checkSize + 54 + 1024 > 1024 * 1024 * (SSIZE_T)TmpBufferMeageByte)
	{
		while (checkSize + 54 + 1024 > 1024 * 1024 * (SSIZE_T)TmpBufferMeageByte)
		{
			TmpBufferMeageByte++;
		}

		DELETEARRAY(m_tmpBuffer);
		m_tmpBuffer = new char[54 + 1024 + 1024 * 1024 * (SSIZE_T)TmpBufferMeageByte];
	}
}

void CPicture::InitStaticData(int tmpMegaBytes)
{
//	if (m_lpScreenBuffer == NULL) m_lpScreenBuffer = new int[m_screenSizeX*m_screenSizeY+m_screenSizeX*2];
	TmpBufferMeageByte = tmpMegaBytes;

	if (m_tmpBuffer == NULL) m_tmpBuffer = new char[54+1024+1024*1024*(SSIZE_T)tmpMegaBytes];
	

	if (m_dataPackLevel > 0)
	{
		if (m_ppPackTable == NULL)
		{
			m_ppPackTable = new char*[m_dataPackLevel*10];
			m_ppPackTable64 = new LONGLONG*[m_dataPackLevel*10];
			m_pack64Flag = new BOOL[m_dataPackLevel*10];

			for (int i=0;i<m_dataPackLevel*10;i++)
			{
				m_ppPackTable[i] = NULL;
				m_ppPackTable64[i] = NULL;
				m_pack64Flag[i] = FALSE;
			}

			for (int i=0;i<m_dataPackLevel;i++)
			{
				//bg,ev,ta,sys,syata,syssm
				char filename[256];
				for (int k=0;k<10;k++)
				{
					LPSTR tagName = m_packTagName[k];
					if ((*tagName) != 0)
					{
						wsprintf(filename,"dwq\\%s%d.gtb",m_packTagName[k],i);
						INT64 fileSize;
						FILE* file = CMyFile::Open(filename,"rb",&fileSize);
						if (file != NULL)
						{

							int sz = (int)fileSize;
							m_ppPackTable[i*10+k] = new  char[sz];
							fread(m_ppPackTable[i*10+k],sizeof(char),sz,file);
							fclose(file);

							//check 64bit exp?
							if (sz >= 16)
							{
			//MessageBox(NULL,"64bit対応ファイルチェックかいし",filename,MB_OK);
								BOOL f = TRUE;
								char* ptr = m_ppPackTable[i*10+k];
								ptr += sz;
								ptr -= 16;
								for (int c=0;c<8;c++)
								{
									if ((*ptr) != 0)
									{
										f = FALSE;
										break;
									}
									ptr++;
								}

								if (f)
								{
			//MessageBox(NULL,"64bit対応ファイルチェック１おｋ",filename,MB_OK);
									char check[]="over2G!";
									for (int c=0;c<8;c++)
									{
										if ((*ptr) != check[c])
										{
											f = FALSE;
											break;
										}
										ptr++;
									}
								}

								if (f)
								{
									//MessageBox(NULL,"64bit対応ファイルです",filename,MB_OK);
									m_pack64Flag[i*10+k] = TRUE;

									ptr = m_ppPackTable[i*10+k];
									int nameKosuu = *((int*)(ptr));

									ptr += sz;
									ptr -= 16;
									ptr -= sizeof(LONGLONG) * nameKosuu;
									m_ppPackTable64[i*10+k] = (LONGLONG*)ptr;
								}
							}

						}
					}
				}

			}
		}
	}



//	if (m_redBlt == NULL) m_redBlt = new CRedBlt();
//	if (m_greyBlt == NULL) m_greyBlt = new CGreyBlt();
	
//	if (m_overrap == NULL) m_overrap = new COverrap();
	if (m_genshoku16 == NULL) m_genshoku16 = new CGenshoku16();

//	CMyGraphics::InitStaticData();
	CJpegDecoder::InitStaticData();
	if (m_jpegDecoder == NULL) m_jpegDecoder = new CJpegDecoder();

#if _MSC_VER >= 1500
	if (m_pngLoader == NULL) m_pngLoader = new CPngLoader();
#endif

}


void CPicture::ReleaseStaticData(void)
{
#if _MSC_VER >= 1500
	ENDDELETECLASS(m_pngLoader);
#endif

	ENDDELETECLASS(m_jpegDecoder);
	CJpegDecoder::ReleaseStaticData();

//	CMyGraphics::ReleaseStaticData();

	ENDDELETECLASS(m_genshoku16);
//	ENDDELETECLASS(m_overrap);


//	ENDDELETECLASS(m_greyBlt);
//	ENDDELETECLASS(m_redBlt);

	if (m_ppPackTable != NULL)
	{
		for (int i=0;i<m_dataPackLevel*10;i++)
		{
			DELETEARRAY(m_ppPackTable[i]);
		}
		DELETEARRAY(m_ppPackTable);
		DELETEARRAY(m_ppPackTable64);
		DELETEARRAY(m_pack64Flag);

	}


	DELETEARRAY(m_tmpBuffer);
//	DELETEARRAY(m_lpScreenBuffer);

}



FILE* CPicture::OpenDWQFile(LPSTR fullFileName,LPSTR filename)
{
//	BOOL ff = FALSE;
//	if (_stricmp(filename,"sys\\ta_dummy") == 0)
//	{
//		int kkkkk = 0;
//		kkkkk++;
//		ff = TRUE;
//		MessageBox(NULL,"ta_dummy","opendwq",MB_OK);
//	}
//	OutputDebugString("\n");
//	OutputDebugString(filename);

	/*
	if (strcmp(filename,"ta\\ta_ef_evex060d1") == 0)
	{
		static int aaa = 0;
		aaa++;
	//	return NULL;
	}
	*/



	m_restReadSize = 1024*1024*3;	//dummy

	if ((m_dataPackLevel == 0) || (m_ppPackTable == NULL))
	{
		m_packFileFlag = FALSE;
		return CMyFile::Open(fullFileName,"rb");
	}

//	if (ff)
//	{
//		MessageBox(NULL,"1","opendwq-1",MB_OK);
//	}



	LPSTR foundTagName = NULL;
	int tagNumber = -1;

	char check1[256];
	char check2[256];

	//get tagName
	for (int i=0;i<10;i++)
	{
		LPSTR tagName = m_packTagName[i];
		char checkTag[16];
		if ((i==3) || (i==4))
		{
			wsprintf(checkTag,"sys\\%s",tagName);
		}
		else
		{
			wsprintf(checkTag,"%s",tagName);
		}

		if ((*tagName) != 0)
		{
//			int ln = strlen(tagName);
			int ln = (int)strlen(checkTag);
			int ln2 = (int)strlen(filename);
			if (ln2>=ln)
			{
//				memcpy(check1,tagName,ln);
				memcpy(check1,checkTag,ln);
				memcpy(check2,filename,ln);
				check1[ln] = 0;
				check1[ln+1] = 0;
				check2[ln] = 0;
				check2[ln+1] = 0;
				if (_stricmp(check1,check2) == 0)
				{
					foundTagName = tagName;
					tagNumber = i;
					break;
				}
			}
		}
	}

	if (foundTagName == NULL)
	{
//	if (ff)
//	{
//		MessageBox(NULL,"1","opendwq-2",MB_OK);
//	}
		m_packFileFlag = FALSE;
		return CMyFile::Open(fullFileName,"rb");
	}

//	char* tablePtr = NULL;

	//こもじにしておく


	char komojiFileName[256];

	//serach en
	int ln3 = (int)strlen(filename);
	
	int en = 0;
	int en2 = 0;
	BOOL foundEn = FALSE;
	while (en<ln3)
	{
		char c = *(filename+en);
		if (c & 0x80)
		{
			en += 2;
		}
		else
		{
			if (c == '\\')
			{
				foundEn = TRUE;
				en2 = en+1;
			}
			en++;
		}
	}

	int ln30 = ln3;
	if (foundEn)
	{
		ln30 = (int)strlen(filename+en2);
	}
	else
	{
		en = 0;
	}

	if (ln30>254) ln30 = 254;

	memcpy(komojiFileName,filename+en2,ln30);
	komojiFileName[ln30] = 0;
	komojiFileName[ln30+1] = 0;

	int p = 0;
	while (p<ln3)
	{
		char c = komojiFileName[p];
		if (c & 0x80)
		{
			p+=2;
		}
		else
		{
			if ((c>='A') && (c<='Z'))
			{
				c += 0x20;
				komojiFileName[p] = c;
			}
			p++;
		}
	}

	BOOL foundFlag = FALSE;
	SSIZE_T foundLevel = 0;
	SSIZE_T foundNumber = 0;

	for (SSIZE_T level = m_dataPackLevel-1;level>=0;level--)
	{
		char* ptr = m_ppPackTable[level*10+tagNumber];
		
		if (ptr != NULL)
		{
			//search name
			int* ptr2 = (int*)ptr;

			SSIZE_T nameKosuu = *ptr2;

			if (nameKosuu>0)
			{
				SSIZE_T minN = 0;
				SSIZE_T maxN = nameKosuu-1;
				SSIZE_T centerN = (minN + maxN) / 2;

				BOOL myTrue = TRUE;
				while(myTrue)
				{
					int strOffset = *(ptr2+1+centerN);
					LPSTR checkName = ptr + strOffset + 4 + nameKosuu*8;
					
					int eq = strcmp(komojiFileName,checkName);
					if (eq == 0)
					{
						foundFlag = TRUE;
						foundLevel = level;
						foundNumber = centerN;
						break;
					}

					if (minN >= maxN) break;

					if ((maxN-minN) >= 2)
					{
						if (eq>0)
						{
							minN = centerN;
						}
						else
						{
							maxN = centerN;
						}
					}
					else
					{
						if (centerN == minN)
						{
							minN = maxN;
						}
						else
						{
							maxN = minN;
						}
					}

					centerN = (minN + maxN) / 2;
				}
			}
		}
		if (foundFlag) break;
	}

//	if (ff)
//	{
//		MessageBox(NULL,"1","opendwq-3",MB_OK);
//	}

	if (foundFlag == FALSE)
	{
		m_packFileFlag = FALSE;
		m_restReadSize = 1024*1024*3;	//dummy
		return CMyFile::Open(fullFileName,"rb");
	}

//	/if (ff)
//	{
//		MessageBox(NULL,"1","opendwq-4",MB_OK);
//	}

	char packFilename[256];
	wsprintf(packFilename,"dwq\\%s%d.gpk",m_packTagName[tagNumber],(int)foundLevel);
	FILE* file = CMyFile::Open(packFilename,"rb");

//	if (ff)
//	{
//		MessageBox(NULL,"1","opendwq-5",MB_OK);
//	}

	if (file == NULL)
	{
		m_packFileFlag = FALSE;
		return CMyFile::Open(fullFileName,"rb");
	}

//	if (ff)
//	{
//		MessageBox(NULL,"1","opendwq-6",MB_OK);
//	}

	char* ptr3 = m_ppPackTable[foundLevel*10+tagNumber];
	int* ptr4 = (int*)ptr3;
	int fileKosuu = *ptr4;

	int offset = *(ptr4 + 1 + fileKosuu + foundNumber);
	LONGLONG offset64 = (LONGLONG)offset;
	offset64 &= 0x7fffffff;

	if (m_pack64Flag[foundLevel*10+tagNumber])
	{
		offset64 = *(m_ppPackTable64[foundLevel*10+tagNumber] + foundNumber);
	}

	fpos_t nowPos;
	fgetpos(file,&nowPos);
	nowPos += offset64;
	fsetpos(file,&nowPos);
//	fsetpos(file,&offset64);

	//_fseeki64(file,offset64,SEEK_SET);



	m_packFileFlag = TRUE;

	if (foundNumber < (SSIZE_T)fileKosuu-1)
	{
		int offset2 = *(ptr4 + 1 + fileKosuu + foundNumber + 1);
		LONGLONG offset2_64 = (LONGLONG)offset2;
		offset2_64 &= 0x7fffffff;

		if (m_pack64Flag[foundLevel*10+tagNumber])
		{
			offset2_64 = *(m_ppPackTable64[foundLevel*10+tagNumber] + foundNumber + 1);
		}

		m_restReadSize = (int)(offset2_64 - offset64);
//		m_restReadSize = offset2 - offset;
	}

//	if (ff)
//	{
//		MessageBox(NULL,"1","opendwq-99",MB_OK);
//	}

#if defined _DEBUG
//	char mes[256];
//	wsprintf(mes,"【パックファイルを見つけました %s LEVEL=%d tag=%d num=%d】\n",filename,foundLevel,tagNumber,foundNumber);
//	OutputDebugString(mes);
#endif

	return file;
}


LPVOID CPicture::GetTexture(void)
{
	return m_texture;
}

BOOL CPicture::GetPngMask(void)
{

	int sz = m_pictureSizeX * m_pictureSizeY;

//	if (sz > m_maskSize)
//	{
	m_maskExistFlag = CreateMaskBuffer(sz);
//	}
	if (m_maskExistFlag == FALSE) return FALSE;

#if _MSC_VER >= 1500
	m_pngLoader->GetMaskData(m_maskPic);
#endif

	return TRUE;
}

void CPicture::SetModeNumberForDebug(int md)
{
	m_modeNumber = md;
}

int CPicture::GetBufferSize()
{
	return m_picBufferSize;
}

/*_*/







