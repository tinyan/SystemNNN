//
// effectFullAnime.cpp
//

#include <windows.h.>

#include "..\nyanEffectLib\includer.h"

#include "..\nyanlib\include\myFile.h"
#include "effectFullAnime.h"



CEffectFullAnime::CEffectFullAnime(CAllEffect* lpAll) : CCommonEffect(lpAll)
{

}

CEffectFullAnime::~CEffectFullAnime()
{
	End();
}

void CEffectFullAnime::End(void)
{
}

BOOL CEffectFullAnime::SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

	int para[16];
	int k = paraKosuu;
	if (k>16) k = 16;
	int i;
	for (i=0;i<k;i++)
	{
		para[i] = paraPtr[i];
	}


	if (paraKosuu<1) para[0] = 20;	//frame
	if (paraKosuu<2) para[1] = 0;	//アニメ番号
	if (paraKosuu<3) para[2] = 1;	//同一コマ個数
	if (paraKosuu<4) para[3] = 0;	//同一コマの時新たに表示しない。

	lp->flag = TRUE;
	lp->command = EFFECT_FULLANIME;
	lp->countMax = para[0];
	lp->count = 0;

	for (i=0;i<16;i++)
	{
		lp->para[i] = para[i];
	}

	m_lastPrintNumber = -1;

	return TRUE;
}


BOOL CEffectFullAnime::CountIsMax(LPVOID lpEffect,int layer)
{
	EFFECT* lp = (EFFECT*)lpEffect;

//	lp->command = EFFECT_NOP;
//	if (lp->pic == -1)
//	{
//		lp->flag = FALSE;
//	}
//
//	return TRUE;
	return FALSE;
}


void CEffectFullAnime::BeginPrint(LPVOID para,int layer)
{

}

void CEffectFullAnime::Init(LPVOID para,int layer)
{
}

void CEffectFullAnime::Calcu(LPVOID lpEffect,int layer)
{
}


void CEffectFullAnime::Print(LPVOID lpEffect,int layer)
{
	int* dst = CMyGraphics::GetScreenBuffer();

	EFFECT* lp = (EFFECT*)lpEffect;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();


	int dv = lp->countMax;
	int c = lp->count;

//	if (c>=dv) return;
//	dv--;
	if (dv<1)
	{
		dv = 1;
		c = 0;
	}

	if (c>=dv)
	{
		c = dv - 1;
	}
	
	int animeNum = lp->para[1];
	int divKoma = lp->para[2];
	if (divKoma<1) divKoma = 1;
	c /= divKoma;

	if (c == m_lastPrintNumber)
	{
		if (lp->para[3])
		{
			return;
		}
	}

	m_lastPrintNumber = c;

	char filename[1024];

	int ah = animeNum / 100;
	int am = (animeNum / 10) % 10;
	int al = animeNum % 10;

	int ch = c / 100;
	int cm = (c / 10) % 10;
	int cl = c % 10;

//	memcpy(filename,"dwq\\an\\an______.dwq",strlen("dwq\\an\\an______.dwq"));

	wsprintf(filename,"dwq\\an\\an%d%d%d%d%d%d.dwq",ah,am,al,ch,cm,cl);

//	FILE* file = fopen(filename,"rb");
	FILE* file = CMyFile::Open(filename,"rb");

	if (file == NULL) return;

//
	int sz = 0;
	char dwq[64];

	BOOL dwqFlag = FALSE;
	BOOL packFlag = FALSE;
	BOOL maskFlag = FALSE;
	BOOL jpegFlag = FALSE;

	fread(dwq,sizeof(char),64,file);

	//now support 0 3 5 7

	if (dwq[0x39] == '3')
	{
		packFlag = TRUE;
		maskFlag = TRUE;
	}

	if (dwq[0x39] == '5')
	{
		jpegFlag = TRUE;
	}

	if (dwq[0x39] == '7')
	{
		jpegFlag = TRUE;
		maskFlag = TRUE;
	}


	int dwqSize = *((int*)(&dwq[32]));
	int xx0 = *((int*)(&dwq[36]));
	int yy0 = *((int*)(&dwq[40]));
	sz = xx0 * yy0*4;
	if (sz<0) sz *= -1;

	if (yy0 < 0) yy0 *= -1;
	int pictureSizeX = xx0;
	int pictureSizeY = yy0;

//	if ((jpegFlag || packFlag) || (xx0 != screenSizeX) || (yy0 != screenSizeY))
	if (0)
	{
		fclose(file);
		return;
	}



	BITMAPFILEHEADER bmf;
	BITMAPINFOHEADER bmi;
//	int* dst = (int*)CPicture::m_lpScreenBuffer;
//	dst += screenSizeX * (screenSizeY-1);

	if (fread(&bmf,sizeof(BITMAPFILEHEADER),1,file) == 1)
	{
		if (fread(&bmi,sizeof(BITMAPINFOHEADER),1,file) == 1)
		{
			RGBQUAD rgbquad[256];
			int rgbTable[256];
//			char buf[MAXSCREENSIZEX];
//			char* buf = (char*)(CEffectSimpleWipe::m_shapeWork);
			char* buf = (char*)(m_allEffect->GetTempWork());

			//load palette
			if (bmi.biBitCount == 8)
			{
				int p = bmi.biClrUsed;
				if (p == 0) p = 256;
				fread(&rgbquad,sizeof(RGBQUAD),p,file);

				//make table
				for (int i=0;i<p;i++)
				{
					int r = rgbquad[i].rgbRed;
					int g = rgbquad[i].rgbGreen;
					int b = rgbquad[i].rgbBlue;

					rgbTable[i] = ((r<<16) & 0xff0000) | ((g << 8) & 0xff00) | (b & 0xff);
				}
			}



			for (int j=0;j<screenSizeY;j++)
			{
				int* dst2 = dst;
				fread(buf,sizeof(char),screenSizeX,file);
				for (int i=0;i<screenSizeX;i++)
				{
					int col = buf[i];
					col &= 0xff;
					*dst2 = rgbTable[col];
					dst2++;
				}

				dst += screenSizeX;
			}
		}
	}

	fclose(file);

	return;
}



BOOL CEffectFullAnime::CheckNeedPicPrint(LPVOID lpEffect,int layer)
{
	return FALSE;
}
