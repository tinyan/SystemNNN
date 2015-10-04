//
// myfont.cpp
//

#include <windows.h>
//#include <d3dx9.h>

#include "..\nyanLib\include\commonmacro.h"

#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"


#if defined _TINYAN3DLIB_
#include "..\..\systemNNN3D\nyanDirectX3DLib/myDirect3D.h"
#include "..\..\systemNNN3D\nyanDirectX3DLib/myTexture.h"
#endif


#include "..\nyanLib\include\areaControl.h"

#include "userFont.h"



//#include "game.h"

#include "myFontCache.h"

#include "myfont.h"

#define DIB_MASK_COLOR 0x00C0E080
#define MYGRAY_COLOR 0x505050


int CMyFont::m_fontType = 0;
int CMyFont::m_userFont = 0;
int CMyFont::m_rubiUseFlag = 0;

int CMyFont::m_rubiSukima = 1;
int CMyFont::m_rubiPercent = 40;
int CMyFont::m_rubiDeltaY = 0;

int CMyFont::m_rubiColorR = 255;
int CMyFont::m_rubiColorG = 255;
int CMyFont::m_rubiColorB = 255;
int CMyFont::m_rubiColorFixFlag = 0;

char CMyFont::m_userFontName[256] ="‚l‚r ƒSƒVƒbƒN";

char CMyFont::m_defaultGaijiFilename[256] = "sys\\spfont24";

int CMyFont::m_fontSizeTable[7]=
{
	10,14,16,18,20,22,24
};

int CMyFont::m_codeByte = 2;
//int CMyFont::m_fukuroType = 0;

int CMyFont::m_fontWeight = FW_BOLD;
int CMyFont::m_fontItalic = 0;


int CMyFont::m_fukuroTable[3][3] = 
{
	{0,0,0},
	{0,0,0},
	{0,0,1},
};


void CMyFont::SetFukuroType(int type)
{
	int i,j;

	for (j=0;j<=2;j++)
	{
		for (i=0;i<=2;i++)
		{
			m_fukuroTable[j][i] = 0;
		}
	}


	if (type == 0)
	{
//		fkr[1][0] = 0;
//		fkr[1][2] = 0;
//		fkr[0][1] = 0;
//		fkr[2][1] = 0;
		m_fukuroTable[2][2] = 1;
	}
	else if (type == 1)

	{
		m_fukuroTable[1][0] = 1;
		m_fukuroTable[1][2] = 1;
		m_fukuroTable[0][1] = 1;
		m_fukuroTable[2][1] = 1;
//		fkr[2][2] = 0;
	}
	else if (type == 2)
	{
		for (j=0;j<=2;j++)
		{
			for (i=0;i<=2;i++)
			{
				m_fukuroTable[j][i] = 1;
			}
		}
		m_fukuroTable[1][1] = 0;
	}
	else if (type == 3)
	{
		m_fukuroTable[1][2] = 1;
		m_fukuroTable[2][2] = 1;
		m_fukuroTable[2][1] = 1;
	}
	else if (type == 4)
	{
		m_fukuroTable[0][0] = 1;
	}
	else if (type == 5)
	{
		m_fukuroTable[0][0] = 1;
		m_fukuroTable[1][0] = 1;
		m_fukuroTable[0][1] = 1;
	}
	else if (type == 6)
	{
		m_fukuroTable[0][1] = 1;
		m_fukuroTable[2][1] = 1;
	}
	else if (type == 7)
	{
		m_fukuroTable[1][0] = 1;
		m_fukuroTable[1][2] = 1;
	}

}

int CMyFont::GetMaxFontSize(void)
{
	return MYFONT_SIZE_MAX;
}


CMyFont::CMyFont(HWND hwnd,LPSTR fontName)
{
//	m_game = lpGame;
//	m_hWnd = m_game->GetHWND();
	m_hWnd = hwnd;
//return;

	m_charaSet = SHIFTJIS_CHARSET;

	if (m_codeByte == 1)
	{
		m_charaSet = ANSI_CHARSET;
	}

	m_fontCacheNumber = -1;

//	BITMAPV4HEADER bmi;

	ZeroMemory(&m_bmi,sizeof(BITMAPV4HEADER));

	int screenSizeX = CMyGraphics::GetScreenSizeX();


	m_bmi.bV4BitCount = 32;
	m_bmi.bV4AlphaMask = 0xff000000;
	m_bmi.bV4BlueMask = 0x000000ff;
	m_bmi.bV4GreenMask = 0x0000ff00;
	m_bmi.bV4Width = screenSizeX*2;
	m_bmi.bV4V4Compression = BI_RGB;
	m_bmi.bV4Size = sizeof(BITMAPV4HEADER);
	m_bmi.bV4RedMask = 0x00ff0000;
	m_bmi.bV4Planes = 1;
	m_bmi.bV4Height = -MYFONT_SIZE_MAX*2;

	HDC hdc = GetDC(m_hWnd);
	m_hBitmap = CreateDIBSection(hdc,(BITMAPINFO*)&m_bmi,DIB_RGB_COLORS,(void**)(&m_lpBuffer),NULL,0);

	m_src = CreateCompatibleDC(hdc);
	m_oldBitmap = SelectObject(m_src,m_hBitmap);
	m_oldBkMode = SetBkMode(m_src,TRANSPARENT);
	m_oldTextColor = SetTextColor(hdc,0);

	ReleaseDC(m_hWnd,hdc);


	m_rubiPic = NULL;

///	m_pic = new CPicture("sys\\w640x32");
///	m_pic->LoadAntiAlias2("sys\\w640x32");
	m_pic = new CPicture(screenSizeX,MYFONT_SIZE_MAX,TRUE);
	if (m_rubiUseFlag)
	{
		m_rubiPic = new CPicture(screenSizeX,MYFONT_SIZE_MAX,TRUE);
	}
#if defined _TINYAN3DLIB_
	CMyTexture* texture = (CMyTexture*)(m_pic->GetTexture());
	texture->SetFix();
	if (m_rubiUseFlag)
	{
		CMyTexture* rubitexture = (CMyTexture*)(m_rubiPic->GetTexture());
		rubitexture->SetFix();
	}
#endif
//	m_pic->LoadDWQ();
	
	m_fontCache = new CMyFontCache(-1,m_rubiUseFlag);

	char filename[256];
	if (m_codeByte == 2)
	{
		sprintf_s(filename,256,"%s",m_defaultGaijiFilename);
	}
	else
	{
		sprintf_s(filename,256,"%s_1byte",m_defaultGaijiFilename);
	}

	m_specialFontPic = new CPicture();
	m_specialFontPic->LoadDWQ(filename);



	m_picBuffer = (int*)(m_pic->GetBuffer());
	m_antiBuffer = m_pic->GetMaskPic();

	if (m_rubiUseFlag)
	{
		m_rubiPicBuffer = (int*)(m_rubiPic->GetBuffer());
		m_rubiAntiBuffer = m_rubiPic->GetMaskPic();
	}

	m_specialFontPicBuffer = (int*)(m_specialFontPic->GetBuffer());
#if defined _TINYAN3DLIB_
	m_specialFontPicBuffer += 128 / sizeof(int);
#endif

	m_userGaijiSizeX = 0;
	m_userGaijiFontPic = NULL;

	RECT rc;
	m_specialFontPic->GetPicSize(&rc);
	m_specialFontSizeX = rc.right;


	char gothic[] = "‚l‚r ƒSƒVƒbƒN";
	char mincho[] = "‚l‚r –¾’©";

	char gothic1Byte[] = "Consolas";
	char mincho1Byte[] = "Courier New";



	LPSTR fontname1;
	if (m_fontType == 0)
	{
		fontname1 = gothic;
	}
	else
	{
		fontname1 = mincho;
	}

	if (m_codeByte == 1)
	{
		if (m_fontType == 0)
		{
			fontname1 = gothic1Byte;
		}
		else
		{
			fontname1 = mincho1Byte;
		}
	}



	LPSTR fontname2 = fontname1;

	if (m_userFont != 0)
	{
		fontname1 = m_userFontName;
	}

	if (fontName != NULL) fontname1 = fontName;

	int ln1 = strlen(fontname1);
	int ln2 = strlen(fontname2);

	if (ln1>255) ln1 = 255;
	if (ln2>255) ln2 = 255;

	memcpy(m_fontName1,fontname1,ln1+1);
	memcpy(m_fontName2,fontname2,ln2+1);


	int i = 0;
	for (i=0;i<=MYFONT_SIZE_MAX;i++)
	{
		m_font[i] = NULL;
	}

	for (i=0;i<7;i++)
	{
		int fontsize = m_fontSizeTable[i];
		HFONT hfont = MakeFont(fontname1,fontsize);
		if (hfont == NULL)
		{
			hfont = MakeFont(fontname2,fontsize);
		}

		m_font[fontsize] = hfont;
	}

	m_fontFlag = FALSE;
	m_nowFontSize = -1;
//	m_nowRubiFontSize = -1;

	m_userCustomFont = NULL;
	m_userCustomFontSize = -1;

//	m_src = NULL;
//	m_hdc = NULL;
	m_oldFont = NULL;
//	m_oldBitmap = NULL;
}


CMyFont::~CMyFont()
{
	End();
}

void CMyFont::End(void)
{
	ENDDELETECLASS(m_userGaijiFontPic);
	ENDDELETECLASS(m_userCustomFont);


//return;
//OutputDebugString("MyFont::End() 0\n");
//Sleep(1000);
	EndPrint();

//OutputDebugString("MyFont::End() 1\n");
//Sleep(1000);

	if (m_src != NULL)
	{
		if (m_oldFont != NULL)
		{
//OutputDebugString("MyFont::End() oldfont\n");
//Sleep(100);
			SelectObject(m_src,(HGDIOBJ)m_oldFont);
			m_oldFont = NULL;
		}


		if (m_oldBitmap != NULL)
		{
//OutputDebugString("MyFont::End() oldbitmap\n");
//Sleep(100);
			SelectObject(m_src,(HGDIOBJ)m_oldBitmap);
			m_oldBitmap = NULL;
		}

		if (m_oldBkMode != 0)
		{
//OutputDebugString("MyFont::End() oldbkmode\n");
//Sleep(100);
			SetBkMode(m_src,m_oldBkMode);
			m_oldBkMode = 0;
		}

		if (m_oldTextColor != CLR_INVALID)
		{
//OutputDebugString("MyFont::End() oldcolor\n");
//Sleep(100);
			SetTextColor(m_src,m_oldTextColor);
			m_oldTextColor = CLR_INVALID;
		}

//OutputDebugString("MyFont::End() delete m_src\n");
//Sleep(100);
		DeleteDC(m_src);
		m_src = NULL;
	}

	if (m_hBitmap != NULL)
	{
//OutputDebugString("MyFont::End() delete bitmap\n");
//Sleep(100);
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}

//OutputDebugString("MyFont::End() delete pic\n");
//Sleep(1000);

	ENDDELETECLASS(m_fontCache);
	ENDDELETECLASS(m_rubiPic);
	ENDDELETECLASS(m_pic);
//OutputDebugString("MyFont::End() delete specialfontpic\n");
//Sleep(100);

	ENDDELETECLASS(m_specialFontPic);

	for (int i=0;i<=MYFONT_SIZE_MAX;i++)
	{
		if (m_font[i] != NULL)
		{
			DeleteObject(m_font[i]);
			m_font[i] = NULL;
		}
	}
}

#if defined _TINYAN3DLIB_
void CMyFont::ClearCache(void)
{
	m_nowFontSize = -1;
	m_fontFlag = FALSE;
	if (m_fontCache != NULL)
	{
		m_fontCache->ClearCache();
	}
}
#endif


CPicture* CMyFont::GetPic(void)
{
	return m_pic;
}

void CMyFont::BeginPrint(int fontsize, BOOL bAntiAliasFlag)
{
	if (m_fontFlag == TRUE) return;


	m_mainFontSize = fontsize;
	m_rubiFontSize = (m_mainFontSize * m_rubiPercent) / 100;



	int newFontSize = GetFontSize(fontsize);
	if (m_nowFontSize != newFontSize)
	{
		m_nowFontSize = newFontSize;

		HFONT hfont = m_font[m_nowFontSize];

		if (hfont == NULL)
		{
			hfont = MakeFont(m_fontName1,m_nowFontSize);
			if (hfont == NULL)
			{
				hfont = MakeFont(m_fontName2,m_nowFontSize);
			}

			m_font[m_nowFontSize] = hfont;
		}

//	m_hdc = GetDC(m_hWnd);
//	m_src = CreateCompatibleDC(m_hdc);
//	m_oldBitmap = SelectObject(m_src,m_hBitmap);
	
		if (hfont != NULL)
		{
			if (m_oldFont == NULL)
			{
				m_oldFont = SelectObject(m_src,(HGDIOBJ)hfont);
			}
			else
			{
				SelectObject(m_src,(HGDIOBJ)hfont);
			}
		}
	}

	//rubi?
//	if (rubiFontSize > 0)
//	{
//	}


	m_fontFlag = TRUE;
}


void CMyFont::EndPrint(void)
{
	if (m_fontFlag == FALSE) return;


	if ((m_src != NULL) && (m_oldBitmap != NULL))
	{
//		SelectObject(m_src,m_oldBitmap);
	}

	if (m_src != NULL)
	{
//		DeleteDC(m_src);
	}


//	if (m_hdc != NULL)
//	{
//		ReleaseDC(m_hWnd,m_hdc);
//	}

//	m_oldFont = NULL;
//	m_oldBitmap = NULL;
//	m_src = NULL;
//	m_hdc = NULL;


	m_fontFlag = FALSE;
}


void CMyFont::BeginRubiPrint(int fontsize, BOOL bAntiAliasFlag)
{
//	if (m_fontFlag == TRUE) return;

	int newFontSize = GetFontSize(fontsize);
	if (m_nowFontSize != newFontSize)
	{
		m_nowFontSize = newFontSize;

		HFONT hfont = m_font[m_nowFontSize];

		if (hfont == NULL)
		{
			hfont = MakeFont(m_fontName1,m_nowFontSize);
			if (hfont == NULL)
			{
				hfont = MakeFont(m_fontName2,m_nowFontSize);
			}

			m_font[m_nowFontSize] = hfont;
		}

//	m_hdc = GetDC(m_hWnd);
//	m_src = CreateCompatibleDC(m_hdc);
//	m_oldBitmap = SelectObject(m_src,m_hBitmap);
	
		if (hfont != NULL)
		{
			if (m_oldFont == NULL)
			{
				m_oldFont = SelectObject(m_src,(HGDIOBJ)hfont);
			}
			else
			{
				SelectObject(m_src,(HGDIOBJ)hfont);
			}
		}
	}

	//rubi?
//	if (rubiFontSize > 0)
//	{
//	}

	m_fontFlag = FALSE;

//	m_fontFlag = TRUE;
}

void CMyFont::EndRubiPrint(void)
{
}


int CMyFont::MakePic(LPSTR orgMessage,LPSTR message, int colR, int colG, int colB ,int sukima, int kageColor, COLORREF* colorPtr,int rubiKosuu,int kanjiMax,int* rubiParam,char** rubiMessage)
{
	if (colR == -1) colR = 255;
	if (colG == -1) colG = colR;
	if (colB == -1) colB = colG;

	int colR0 = colR;
	int colG0 = colG;
	int colB0 = colB;

	COLORREF col = COLORREF(colR | (colG << 8) | (colB<<16));

	if (colorPtr != NULL)
	{
		col = *colorPtr;
		colB = (col >> 16) & 0xff;
		colG = (col >> 8 ) & 0xff;
		colR = (col      ) & 0xff;
	}

	int colorChangeStart = -1;
	if (colorPtr != NULL)
	{
		if (m_rubiUseFlag)
		{
			if (m_rubiColorFixFlag == 0)
			{
				//if ((colR != colR0) || (colB != colB0) || (colG != colG0))
				//{
					//colorChangeStart = 0;
				//}

				for (int i=0;i<kanjiMax;i++)
				{
					COLORREF col000 = *(colorPtr+i);
					int colR000 = (col000 >> 16) & 0xff;
					int colG000 = (col000 >>  8) & 0xff;
					int colB000 = (col000      ) & 0xff;

					if ((colR000 != colR0) || (colB000 != colB0) || (colB000 != colB0))
					{
						colorChangeStart = i;
						break;
					}
				}
			}
		}
	}

	int rubiColorR = m_rubiColorR;
	int rubiColorG = m_rubiColorG;
	int rubiColorB = m_rubiColorB;
	COLORREF rubiColor = COLORREF(m_rubiColorR | (m_rubiColorG << 8) | (m_rubiColorB<<16));


	int cache = m_fontCache->SearchData(orgMessage,m_mainFontSize,colR,colG,colB,sukima,kageColor);
//	int cache = m_fontCache->SearchData(orgMessage,m_nowFontSize,colR,colG,colB,sukima,kageColor);
	if (cache != -1)
	{
//OutputDebugString("found");
		m_fontCacheNumber = cache;
		SIZE sz4 = m_fontCache->GetSize(cache);
		int sizeX4 = sz4.cx;
		int sizeY4 = sz4.cy;
		return sizeX4 | (sizeY4<<16);//picsize


		//old
		if (m_fontCache->GetData(cache,m_pic))
		{
			SIZE sz3 = m_fontCache->GetSize(cache);
			int sizeX3 = sz3.cx;
			int sizeY3 = sz3.cy;
			return sizeX3 | (sizeY3<<16);//picsize
		}
	}

//OutputDebugString("\nCreate font pic::");
//OutputDebugString(orgMessage);
//OutputDebugString("\n");


	int checkColorR = colR;
	int checkColorG = colG;
	int checkColorB = colB;


//return 640 | (32<<16);//picsize

	BOOL customFontFlag = FALSE;

	if (m_userCustomFont != NULL)
	{
		if (m_nowFontSize == m_userCustomFontSize)
		{
			customFontFlag = TRUE;
		}
	}

	int i,j;

	int screenSizeX = CMyGraphics::GetScreenSizeX();

	if (m_fontFlag == FALSE) return 0;

	HDC hdc = m_src;



	int ln = 0;
	if (m_codeByte == 2)
	{
		ln = strlen(message) / 2;
	}
	else
	{
		ln = strlen(message) / 2;
	}


	//Fill GREY
	int sizeY = m_nowFontSize*2;
	
	int sizeX;
	if (m_codeByte == 2)
	{
		sizeX = (m_nowFontSize+sukima)*2*ln;
	}
	else
	{
//		sizeX = (m_nowFontSize/2+sukima)*2*ln;
		sizeX = (m_nowFontSize/2+sukima)*2*ln;
	}
	if (sizeX>screenSizeX*2) sizeX = screenSizeX*2;


	int* dst0 = (int*)m_lpBuffer;

	if (customFontFlag == FALSE)
	{
		for (j=0;j<sizeY;j++)
		{
			int* dst = dst0;
			for (i=0;i<sizeX;i++)
			{
				*dst = MYGRAY_COLOR;
				dst++;
			}
			dst0 += screenSizeX*2;
		}
	}

	if (customFontFlag)
	{
		//fill mask 0
		char* anti00 = (char*)m_antiBuffer;
		int antiSizeX = sizeX / 2;
		for (int j=0;j<sizeY;j++)
		{

			ZeroMemory(anti00,antiSizeX);
			anti00 += screenSizeX;
		}
	}



	int fkr[3][3];
	for (j=0;j<=2;j++)
	{
		for (i=0;i<=2;i++)
		{
			fkr[j][i] = m_fukuroTable[j][i];
		}
	}



	int x = 2;
	int y = 2;
	int stp;
	if (m_codeByte == 2)
	{
		stp = (m_nowFontSize+sukima) * 2;
	}
	else
	{
		stp = (m_nowFontSize/2+sukima) * 2;
//		stp = (m_nowFontSize+sukima*2) ;
	}

	if (1)
	{

		int kageColorR = (kageColor >> 16) & 0xff;
		int kageColorG = (kageColor >> 8) & 0xff;
		int kageColorB = (kageColor  ) & 0xff;



		if (kageColor != -1)
		{
//			SetTextColor(m_src,COLORREF(kageColor));
			SetTextColor(m_src,COLORREF(kageColorR | (kageColorG << 8) | (kageColorB << 16)));

			if (m_codeByte == 2)
			{
				for (i=0;i<ln;i++)
				{
					char ckc = *(message+i*2);
					if (ckc != (char)0x80)
					{
						if (customFontFlag == FALSE)
						{
							for (int jj=0;jj<=2;jj++)
							{
								for (int ii=0;ii<=2;ii++)
								{
									if (fkr[jj][ii])
									{
										TextOut(hdc,x+ii*2-4,y+jj*2-4,message+i*2,2);
									}
								}
							}
						}
						else
						{
							MakeCustom(x/2,y/2,1,1,message+i*2,kageColorR,kageColorG,kageColorB);
						}
					}
					else
					{
						for (int jj=0;jj<=2;jj++)
						{
							for (int ii=0;ii<=2;ii++)
							{
								if (fkr[jj][ii])
								{
									Gaiji(x+ii*2-4,y+jj*2-4,kageColor,*(message+i*2+1));
								}
							}
						}
					}

					x += stp;
				}
			}
			else
			{
				for (i=0;i<ln;i++)
				{
					char ckc = *(message+i*2);
					if (ckc != (char)0x80)
					{
//						if (customFontFlag == FALSE)
//						{
							TextOut(hdc,x,y,message+i*2,1);
//						}
//						else
//						{
//							MakeCustom(x/2,y/2,1,1,message+i*2,kageColorR,kageColorG,kageColorB);
//						}
					}
					else
					{
						Gaiji(x,y,kageColor,*(message+i*2+1));
					}

					x += stp;
				}
			}
		}
	}

	//Fill DIB_MASK_COLOR
	int sizeY2 = m_nowFontSize;
	int sizeX2;
	if (m_codeByte == 2)
	{
		sizeX2 = (m_nowFontSize+sukima)*ln;
	}
	else
	{
		sizeX2 = (m_nowFontSize/2+sukima)*ln;
//		sizeX2 = ((m_nowFontSize+sukima*2)*ln)/2;
	}


	if (sizeX2>screenSizeX) sizeX2 = screenSizeX;

	dst0 = (int*)m_picBuffer;
	
	if (customFontFlag == FALSE)
	{
		for (j=0;j<sizeY2;j++)
		{
			int* dst = dst0;
			for (i=0;i<sizeX2;i++)
			{
				*dst = DIB_MASK_COLOR;
				dst++;
			}
			dst0 += screenSizeX;
		}
	}

//return sizeX | (sizeY<<16);//picsize





	//antialias copy kage

	int* src0 = (int*)m_lpBuffer;
	dst0 = (int*)m_picBuffer;

	unsigned char* anti0 = (unsigned char*)m_antiBuffer;

	if (customFontFlag == FALSE)
	{
		for (j=0;j<sizeY2;j++)
		{
			int* dst = dst0;
			int* src = src0;
			unsigned char* anti = anti0;

			for (i=0;i<sizeX2;i++)
			{
				int kosuu = 0;
				int rr = 0;
				int gg = 0;
				int bb = 0;

				for (int jj=0;jj<2;jj++)
				{
					for (int ii=0;ii<2;ii++)
					{
						int d = *(src+ii+jj*screenSizeX*2);
						if (d != MYGRAY_COLOR)
						{
							kosuu++;

							int r = (d>>16) & 0xff;
							int g = (d>>8) & 0xff;
							int b = d & 0xff;

							rr += r;
							gg += g;
							bb += b;
						}
					}
				}

	//			rr += 2;
	//			gg += 2;
	//			bb += 2;

				if (kosuu > 0)
				{
					if (kosuu == 4)
					{
						rr >>= 2;
						gg >>= 2;
						bb >>= 2;
						*anti = 255;
					}
					else if (kosuu ==2)
					{
						rr >>= 1;
						gg >>= 1;
						bb >>= 1;
						*anti = 128;
	//					*anti = 208;
					}
					else if (kosuu == 1)
					{
	//					rr /= kosuu;
	//					gg /= kosuu;
	//					bb /= kosuu;
						*anti = 64;
	//					*anti = 160;
					}
					else	//kosuu == 3
					{
						rr /= kosuu;
						gg /= kosuu;
						bb /= kosuu;
						*anti = 192;
	//					*anti = 240;
					}

					*dst = (rr<<16) | (gg<<8) | bb;

				}
				else
				{
					*anti = 0;
				}

				src += 2;
				dst++;
				anti++;
			}


			src0 += (screenSizeX*2)*2;
			dst0 += screenSizeX;
			anti0 += screenSizeX;
		}
	}








	dst0 = (int*)m_lpBuffer;


	//FillGrey
	if (customFontFlag == FALSE)
	{
		for (j=0;j<sizeY;j++)
		{
			int* dst = dst0;
			for (i=0;i<sizeX;i++)
			{
				*dst = MYGRAY_COLOR;
				dst++;
			}
			dst0 += screenSizeX*2;
		}
	}


	COLORREF lastColor = col;
	SetTextColor(m_src,col);

	x = 0;
	y = 0;
	for (i=0;i<ln;i++)
	{
		if (colorPtr != NULL)
		{
			col = *(colorPtr+i);
		}

		if (col != lastColor)
		{
			colB = (col >> 16) & 0xff;
			colG = (col >> 8 ) & 0xff;
			colR = (col      ) & 0xff;

			SetTextColor(hdc,col);
		}

		if (m_codeByte == 2)
		{
			if ((*(message + i* 2)) != (char)0x80)
			{
				if (customFontFlag == FALSE)
				{
					TextOut(hdc,x,y,message+i*2,2);
				}
				else
				{
					MakeCustom(x/2,y/2,0,0,message+i*2,colR,colG,colB);
	//				char* buf2 = m_userCustomFont->GetFont1Moji(message+i*2);
				}
			}
			else
			{
				int col2 = (colR<<16) | (colG<<8) | (colB);
				Gaiji(x,y,col2,*(message + i*2+1));
			}
		}
		else
		{
			if ((*(message + i* 2)) != (char)0x80)
			{
//				if (customFontFlag == FALSE)
				TextOut(hdc,x,y,message+i*2,1);
			}
			else
			{
				int col2 = (colR<<16) | (colG<<8) | (colB);
				Gaiji(x,y,col2,*(message + i*2+1));
			}
		}
		x += stp;

		lastColor = col;
	}



	//antialias copy2

	src0 = (int*)m_lpBuffer;
	dst0 = (int*)m_picBuffer;

	anti0 = (unsigned char*)m_antiBuffer;

	if (customFontFlag == FALSE)
	{
		for (j=0;j<sizeY2;j++)
		{
			int* dst = dst0;
			int* src = src0;
			unsigned char* anti = anti0;

			for (i=0;i<sizeX2;i++)
			{
				int kosuu = 0;
				int rr = 0;
				int gg = 0;
				int bb = 0;

				for (int jj=0;jj<2;jj++)
				{
					for (int ii=0;ii<2;ii++)
					{
						int d = *(src+ii+jj*screenSizeX*2);
						if (d != MYGRAY_COLOR)
						{
							kosuu++;

							int r = (d>>16) & 0xff;
							int g = (d>>8) & 0xff;
							int b = d & 0xff;

							rr += r;
							gg += g;
							bb += b;
						}
					}
				}

	//			rr += 2;
	//			gg += 2;
	//			bb += 2;

				if (kosuu > 0)
				{
					if (kosuu == 4)
					{
						rr >>= 2;
						gg >>= 2;
						bb >>= 2;
						*anti = 255;
					}
					else if (kosuu ==2)
					{
						rr >>= 1;
						gg >>= 1;
						bb >>= 1;
						*anti = 128;
	//					*anti = 208;
					}
					else if (kosuu == 1)
					{
	//					rr /= kosuu;
	//					gg /= kosuu;
	//					bb /= kosuu;
						*anti = 64;
	//					*anti = 160;
					}
					else	//kosuu == 3
					{
						rr /= kosuu;
						gg /= kosuu;
						bb /= kosuu;
						*anti = 192;
	//					*anti = 240;
					}

					*dst = (rr<<16) | (gg<<8) | bb;

				}
				else
				{
	///				*anti = 0;
				}

				src += 2;
				dst++;
				anti++;
			}


			src0 += (screenSizeX*2)*2;
			dst0 += screenSizeX;
			anti0 += screenSizeX;
		}
	}


	//¶ã‚ð“§–¾F‚É
	if (customFontFlag == FALSE)
	{
		*(m_picBuffer) = DIB_MASK_COLOR;
	}


	//ƒAƒ“ƒ`ƒGƒŠƒAƒXƒf[ƒ^‚ð‚Â‚­‚é‚©???

	CPicture* lpRubiPic = NULL;

	if (m_rubiUseFlag)
	{
		//rubi‚ ‚é‚©
		if (rubiKosuu > 0)
		{

			int rubiFontSize = GetRubiFontSize();
			int rightMax = (m_nowFontSize + sukima) * kanjiMax;
			int kanjiWidth = m_nowFontSize + sukima;
			int rubiWidth = rubiFontSize + m_rubiSukima;
			rightMax -= rubiWidth;

			BeginRubiPrint(rubiFontSize);

			unsigned char* anti00 = (unsigned char*)m_rubiAntiBuffer;
			int size00 = kanjiWidth * kanjiMax;
			for (j=0;j<rubiFontSize;j++)
			{
				ZeroMemory(anti00,size00);
				anti00 += screenSizeX;
			}

			int leftLimit = 0;



			for (int rubi = 0;rubi < rubiKosuu; rubi++)
			{
				int rubiKanjiLength = rubiParam[rubi*4+0];
				int rubiLength = rubiParam[rubi*4+1];
				int rubiKanjiStart = rubiParam[rubi*4+2];
				LPSTR rubiStart = rubiMessage[rubi];

				if (colorPtr != NULL)
				{
					if (m_rubiColorFixFlag == 0)
					{
						if (colorChangeStart != -1)
						{
							if (rubiKanjiStart >= colorChangeStart)
							{
								rubiColor = *(colorPtr+rubiKanjiStart);

								rubiColorR = (rubiColor >> 16) & 0xff;
								rubiColorG = (rubiColor >> 8 ) & 0xff;
								rubiColorB = (rubiColor      ) & 0xff;
							}
						}
					}
				}


				//adjust left right haba
				int rubiPutX = rubiKanjiStart * kanjiWidth + rubiKanjiLength * kanjiWidth / 2 - (rubiWidth * rubiLength) / 2;
				int rubiPutXLast = rubiPutX + rubiWidth * (rubiLength-1);


				if (rubiLength == -1)
				{
					rubiLength = rubiKanjiLength;
					rubiPutX = rubiKanjiStart * kanjiWidth + (kanjiWidth - rubiWidth) / 2;
					rubiPutXLast = rubiPutX + kanjiWidth * (rubiLength-1);
				}

				if (m_codeByte == 1)
				{
					rubiPutX /= 2;
					rubiPutXLast /= 2;
				}


				if (rubiPutX < leftLimit)
				{
					rubiPutXLast += (leftLimit - rubiPutX);
					rubiPutX = leftLimit;
				}

				if (rubiPutXLast > rightMax)
				{
					rubiPutX -= (rubiPutXLast - rightMax);
					rubiPutXLast = rightMax;
				}

				//‚¨‚µ‚à‚Ç‚³‚ê‚½‚Æ‚«‚æ‚¤
				if (rubiPutX < leftLimit)
				{
					rubiPutX = leftLimit;
				}


				//
				if (rubiPutXLast < rubiPutX)
				{
					rubiPutXLast = rubiPutX;
				}

				leftLimit = rubiPutXLast + rubiWidth;
				if (leftLimit > rightMax)
				{
					leftLimit = rightMax;
				}

				int dv = rubiLength-1;
				if (dv<1) dv = 1;//youjin

				int rubiNextX = (rubiPutXLast - rubiPutX) / dv;


//				int ln = strlen(message);
//				ln /= 2;



				//Fill GREY
				int sizeYRubi = rubiFontSize*2;
//				int sizeXRubi = rubiNextX * rubiLength * 2;
				int sizeXRubi = (rubiNextX * (rubiLength-1) +rubiWidth)* 2;
//				if (m_codeByte == 1)
//				{
//					sizeXRubi /= 2;
//				}

				if ((rubiPutX+sizeXRubi) > screenSizeX*2)
				{
					int d = rubiPutX+sizeXRubi - screenSizeX*2;
					sizeXRubi -= d;
				}

//				if (sizeX>screenSizeX*2) sizeX = screenSizeX*2;
				int* dst0 = (int*)m_lpBuffer;
				dst0 += rubiPutX*2;

				if (customFontFlag == FALSE)
				{
					for (j=0;j<sizeYRubi;j++)
					{
						int* dst = dst0;
						for (i=0;i<sizeXRubi;i++)
						{
							*dst = MYGRAY_COLOR;
							dst++;
						}
						dst0 += screenSizeX*2;
					}
				}


				if (customFontFlag)
				{
					//fill mask 0
					char* anti00 = (char*)m_rubiAntiBuffer;
					int antiSizeX = sizeXRubi / 2;
					for (int j=0;j<sizeYRubi;j++)
					{

						ZeroMemory(anti00,antiSizeX);
						anti00 += screenSizeX;
					}
				}




				x = 2;
				y = 2;
				stp = rubiNextX * 2;

				int kageColorR = (kageColor >> 16) & 0xff;
				int kageColorG = (kageColor >> 8) & 0xff;
				int kageColorB = (kageColor  ) & 0xff;


			//	COLORREF col = COLORREF(colR | (colG << 8) | (colB<<16));


				x += rubiPutX * 2;

				if (kageColor != -1)
				{
//					SetTextColor(m_src,COLORREF(kageColor));
					SetTextColor(m_src,COLORREF(kageColorR | (kageColorG << 8) | (kageColorB << 16)));

					for (i=0;i<rubiLength;i++)
					{
//						char ckc = *(message+i*2);
//						if (ckc != (char)0x80)
//						{
							if (customFontFlag == FALSE)
							{
								TextOut(hdc,x,y,rubiStart+i*m_codeByte,m_codeByte);
							}
							else
							{
								MakeCustom(x/2,y/2,1,1,rubiStart+i*2,kageColorR,kageColorG,kageColorB);
							}
//						}
//						else
//						{
//							Gaiji(x,y,kageColor,*(message+i*2+1));
//						}

						x += stp;
					}
				}


				//Fill DIB_MASK_COLOR
				int sizeY2Rubi = rubiFontSize;
//				int sizeX2Rubi = rubiNextX*rubiLength;

				int sizeX2Rubi = rubiNextX * (rubiLength-1) +rubiWidth;
				if (m_codeByte == 1)
				{
					sizeX2Rubi = rubiNextX * (rubiLength-1) + rubiWidth / 2;
				}

				if ((rubiPutX+sizeX2Rubi) > screenSizeX)
				{
					int d = rubiPutX+sizeX2Rubi - screenSizeX;
					sizeX2Rubi -= d;
				}
//				if (sizeX2>screenSizeX) sizeX2 = screenSizeX;

				dst0 = (int*)m_rubiPicBuffer;
				dst0 += rubiPutX;
				
				if (customFontFlag == FALSE)
				{
					for (j=0;j<sizeY2Rubi;j++)
					{
						int* dst = dst0;
						for (i=0;i<sizeX2Rubi;i++)
						{
							*dst = DIB_MASK_COLOR;
							dst++;
						}
						dst0 += screenSizeX;
					}
				}

//return sizeX | (sizeY<<16);//picsize





				//antialias copy kage

				int* src0 = (int*)m_lpBuffer;
				dst0 = (int*)m_rubiPicBuffer;

				unsigned char* anti0 = (unsigned char*)m_rubiAntiBuffer;

				src0 += rubiPutX * 2;
				dst0 += rubiPutX;
				anti0 += rubiPutX;

				if (customFontFlag == FALSE)
				{
					for (j=0;j<sizeY2Rubi;j++)
					{
						int* dst = dst0;
						int* src = src0;
						unsigned char* anti = anti0;

						for (i=0;i<sizeX2Rubi;i++)
						{
							int kosuu = 0;
							int rr = 0;
							int gg = 0;
							int bb = 0;

							for (int jj=0;jj<2;jj++)
							{
								for (int ii=0;ii<2;ii++)
								{
									int d = *(src+ii+jj*screenSizeX*2);
									if (d != MYGRAY_COLOR)
									{
										kosuu++;

										int r = (d>>16) & 0xff;
										int g = (d>>8) & 0xff;
										int b = d & 0xff;

										rr += r;
										gg += g;
										bb += b;
									}
								}
							}

				//			rr += 2;
				//			gg += 2;
				//			bb += 2;

							if (kosuu > 0)
							{
								if (kosuu == 4)
								{
									rr >>= 2;
									gg >>= 2;
									bb >>= 2;
									*anti = 255;
								}
								else if (kosuu ==2)
								{
									rr >>= 1;
									gg >>= 1;
									bb >>= 1;
									*anti = 128;
				//					*anti = 208;
								}
								else if (kosuu == 1)
								{
				//					rr /= kosuu;
				//					gg /= kosuu;
				//					bb /= kosuu;
									*anti = 64;
				//					*anti = 160;
								}
								else	//kosuu == 3
								{
									rr /= kosuu;
									gg /= kosuu;
									bb /= kosuu;
									*anti = 192;

				//					*anti = 240;
								}

								*dst = (rr<<16) | (gg<<8) | bb;

							}
							else
							{
								*anti = 0;

							}

							src += 2;
							dst++;
							anti++;
						}


						src0 += (screenSizeX*2)*2;
						dst0 += screenSizeX;
						anti0 += screenSizeX;
					}
				}







				dst0 = (int*)m_lpBuffer;
				dst0 += rubiPutX*2;
				//FillGrey
				if (customFontFlag == FALSE)
				{
					for (j=0;j<sizeYRubi;j++)
					{
						int* dst = dst0;
						for (i=0;i<sizeXRubi;i++)
						{
							*dst = MYGRAY_COLOR;
							dst++;
						}
						dst0 += screenSizeX*2;
					}
				}


//				COLORREF lastColor = col;
				SetTextColor(m_src,rubiColor);

				x = 0;
				y = 0;

				x += rubiPutX * 2;

				for (i=0;i<rubiLength;i++)
				{
//					if ((*(message + i* 2)) != (char)0x80)
//					{
						if (customFontFlag == FALSE)
						{
							TextOut(hdc,x,y,rubiStart+i*m_codeByte,m_codeByte);
						}
						else
						{
							MakeCustom(x/2,y/2,0,0,rubiStart+i*2,rubiColorR,rubiColorG,rubiColorB);
			//				char* buf2 = m_userCustomFont->GetFont1Moji(message+i*2);
						}
//					}
//					else
//					{
//						int col2 = (colR<<16) | (colG<<8) | (colB);
//						Gaiji(x,y,col2,*(message + i*2+1));
//					}
					x += stp;

//					lastColor = col;
				}



				//antialias copy2

				src0 = (int*)m_lpBuffer;
				dst0 = (int*)m_rubiPicBuffer;

				anti0 = (unsigned char*)m_rubiAntiBuffer;

				src0 += rubiPutX * 2;
				dst0 += rubiPutX;
				anti0 += rubiPutX;

				if (customFontFlag == FALSE)
				{
					for (j=0;j<sizeY2Rubi;j++)
					{
						int* dst = dst0;
						int* src = src0;
						unsigned char* anti = anti0;

						for (i=0;i<sizeX2Rubi;i++)
						{
							int kosuu = 0;
							int rr = 0;
							int gg = 0;
							int bb = 0;

							for (int jj=0;jj<2;jj++)
							{
								for (int ii=0;ii<2;ii++)
								{
									int d = *(src+ii+jj*screenSizeX*2);
									if (d != MYGRAY_COLOR)
									{
										kosuu++;

										int r = (d>>16) & 0xff;
										int g = (d>>8) & 0xff;
										int b = d & 0xff;

										rr += r;
										gg += g;
										bb += b;
									}
								}
							}

				//			rr += 2;
				//			gg += 2;
				//			bb += 2;

							if (kosuu > 0)
							{
								if (kosuu == 4)
								{
									rr >>= 2;
									gg >>= 2;
									bb >>= 2;
									*anti = 255;
								}
								else if (kosuu ==2)
								{
									rr >>= 1;
									gg >>= 1;
									bb >>= 1;
									*anti = 128;
				//					*anti = 208;
								}
								else if (kosuu == 1)
								{
				//					rr /= kosuu;
				//					gg /= kosuu;
				//					bb /= kosuu;
									*anti = 64;
				//					*anti = 160;
								}
								else	//kosuu == 3
								{
									rr /= kosuu;
									gg /= kosuu;
									bb /= kosuu;
									*anti = 192;
				//					*anti = 240;
								}

								*dst = (rr<<16) | (gg<<8) | bb;

							}
							else
							{
				///				*anti = 0;
							}

							src += 2;
							dst++;
							anti++;
						}


						src0 += (screenSizeX*2)*2;
						dst0 += screenSizeX;
						anti0 += screenSizeX;
					}
				}


				//¶ã‚ð“§–¾F‚É
				if (customFontFlag == FALSE)
				{
					*(m_rubiPicBuffer) = DIB_MASK_COLOR;
				}


			}

			EndRubiPrint();


			lpRubiPic = m_rubiPic;
		}
	}

	m_fontCacheNumber = m_fontCache->AddData(orgMessage,m_mainFontSize,checkColorR,checkColorG,checkColorB,sukima,kageColor,sizeX2,sizeY2,m_pic,lpRubiPic);
//	m_fontCacheNumber = m_fontCache->AddData(orgMessage,m_nowFontSize,checkColorR,checkColorG,checkColorB,sukima,kageColor,sizeX2,sizeY2,m_pic);

	return sizeX2 | (sizeY2<<16);//picsize
}


int CMyFont::MakePicOnly(LPSTR message, int colR, int colG, int colB, int sukima, int kageColor, COLORREF* colorPtr)
{
	return 0;
}

int CMyFont::MakeBuffer(LPSTR message, int colR, int colG, int colB, int sukima, int kageColor, COLORREF* colorPtr)
{
	return 0;
}





int CMyFont::GetFontSize(int fontsize)
{
	if (fontsize < 1) fontsize = 1;
	if (fontsize > MYFONT_SIZE_MAX) fontsize = MYFONT_SIZE_MAX;

	return fontsize;
/*
	for (int i=0;i<7;i++)
	{
		if (fontsize <= m_fontSizeTable[i]) return m_fontSizeTable[i];
	}

	return m_fontSizeTable[6];
	*/
}



HFONT CMyFont::MakeFont(LPSTR fontname,int fontsize)
{
	return CreateFont(	fontsize*2,fontsize*2/2,0,0,m_fontWeight,m_fontItalic,FALSE,FALSE,
						m_charaSet,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS ,DEFAULT_QUALITY,
						FIXED_PITCH | FF_DONTCARE,
						fontname);
}


void CMyFont::Gaiji(int x,int y,int col,int dat)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();

	if (dat < 1) return;	//not support gaiji
	if (dat > 50) return;	//not support gaiji

	int* dst = (int*)m_lpBuffer;
	int* src = (int*)m_specialFontPicBuffer;
	int fontPicSizeX = m_specialFontSizeX;
	dat -= 1;

	/*
	static int kkk = 0;
	if ( kkk == 0 )
	{
		kkk=1;
		for (int j=0;j<48;j++)
		{
			for (int i=0;i<=26*5;i++)
			{
				if (((*(src+i+j*fontPicSizeX)) & 0xffffff) != 0)
				{
					OutputDebugString("o");
				}
				else
				{
					OutputDebugString(".");
				}

			}
			OutputDebugString("\x00d\x00a");
		}
	}
	*/



	int codeByte = m_codeByte;

	if (dat >= 20)
	{
		src = (int*)m_userGaijiFontPicBuffer;
		fontPicSizeX = m_userGaijiSizeX;
		dat -= 19;
	}

	int loopX = m_nowFontSize* codeByte + 2;
	int loopY = m_nowFontSize* 2;
	int srcDeltaX = 0;
	int srcDeltaY = 0;
	int yMax = MYFONT_SIZE_MAX * 2;


	if (x<0)
	{
		srcDeltaX = -x;
		loopX += x;
		x = 0;
	}
	if (y<0)
	{
		srcDeltaY = -y;
		loopY += y;
		y = 0;
	}


	if ((x+loopX) > screenSizeX*2)
	{
		loopX = screenSizeX*2 - x;
	}
	if ((y+loopY) > yMax)
	{
		loopY = yMax - y;
	}

	if ((loopX<=0) || (loopY<=0)) return;

	dst += x;
	dst += y * screenSizeX * 2;

	int width = 24 * codeByte + 2;

	src += dat * width;
//	src += srcDeltaX;
//	src += srcDeltaY * fontPicSizeX;



	if (((dat+1) * width) > fontPicSizeX) return;	//no data

	int c = col;

	if (m_nowFontSize == 24)
	{
		src += srcDeltaX;
		src += srcDeltaY * fontPicSizeX;

		for (int j=0;j<loopY;j++)
		{
			int* src0 = src;
			int* dst0 = dst;

			for (int i=0;i<loopX;i++)
			{
				if (((*src) & 0xffffff) != 0)
				{
					*dst = c;
				}
				dst++;
				src++;
			}
			
			src = src0;
		//	src += m_specialFontSizeX; 
			src += fontPicSizeX;
			dst = dst0;
			dst += screenSizeX*2;
		}

		return;
	}

	int sy = m_nowFontSize*2;
	int sx = m_nowFontSize*codeByte + 2;

	int* src0 = src;
	for (int j=0;j<loopY;j++)
//	for (int j=0;j<sy;j++)
	{
		int* dst0 = dst;

//		int* src1 = src0 + ((j*48)/sy) * m_specialFontSizeX;
		int* src1 = src0 + ((j*48+srcDeltaY*48)/sy) * fontPicSizeX;
//		for (int i=0;i<sx;i++)
		for (int i=0;i<loopX;i++)
		{
			int* src2 = src1 + (i*width+srcDeltaX*width)/sx;

			if (((*src2) & 0xffffff) != 0)
			{
				*dst = c;
			}
			dst++;
		}

		dst = dst0;
		dst += screenSizeX*2;
	}


}


HDC CMyFont::GetHDC(void)
{
	return m_src;
}



BOOL CMyFont::LoadUserFont(LPSTR fontfilename)
{
	m_userCustomFont = new CUserFont(fontfilename);
	m_userCustomFontSize = m_userCustomFont->GetUserFontSize();



	return TRUE;
}


void CMyFont::MakeCustom(int x,int y,int dx,int dy,LPSTR mes,int colR,int colG,int colB)
{
	char* ptr = m_userCustomFont->GetFont1Moji(mes);

//	int fontDataSize = m_userCustomFont->GetUserFontDataSize();
//	int fontDataSize = 24;

	int screenSizeX = CMyGraphics::GetScreenSizeX();

	int loopX = m_nowFontSize - dx;
	int loopY = m_nowFontSize - dy;

	if ((loopX<=0) || (loopY<=0)) return;


	char* mask = (char*)m_antiBuffer;
	int* dst = (int*)m_picBuffer;

	mask += x;
	mask += y*screenSizeX;

	dst += x;
	dst += y*screenSizeX;

	char* ptr0 = ptr;
	char* mask0 = mask;
	int* dst0 = dst;

	int col = (colR<<16) | (colG<<8) | colB;

	int srcPitch = m_nowFontSize;

	for (int j=0;j<loopY;j++)
	{
		ptr = ptr0;
		mask = mask0;
		dst = dst0;

		for (int i=0;i<loopX;i++)
		{
			char c = *ptr;

			if (c != 0)
			{
				*mask = c;
				*dst = col;
			}

			ptr++;
			mask++;
			dst++;
		}

		ptr0 += srcPitch;
		mask0 += screenSizeX;
		dst0 += screenSizeX;
	}


}


void CMyFont::Print(int putX,int putY,int deltaX,int deltaY,int sizeX,int sizeY)
{
	if (m_fontCacheNumber == -1) return;	//error!

//	char mes[256];
//	wsprintf(mes,"[%d]",m_fontCacheNumber);
//	OutputDebugString(mes);

	POINT pt = m_fontCache->GetSrc(m_fontCacheNumber);

	int srcX = pt.x + deltaX;
	int srcY = pt.y + deltaY;
	putX += deltaX;
	putY += deltaY;

	m_fontCache->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
//	m_pic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	CAreaControl::AddArea(putX,putY,sizeX,sizeY);
}

void CMyFont::EffectPrint(int putX,int putY,int deltaX,int deltaY,int sizeX,int sizeY,int fontSize,int effectType,int effectCount1000)
{
	if (m_fontCacheNumber == -1) return;	//error!

//	char mes[256];
//	wsprintf(mes,"[%d]",m_fontCacheNumber);
//	OutputDebugString(mes);

	POINT pt = m_fontCache->GetSrc(m_fontCacheNumber);

	int srcX = pt.x + deltaX;
	int srcY = pt.y + deltaY;
	putX += deltaX;
	putY += deltaY;

	m_fontCache->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);

	//effect
	m_fontCache->EffectBlt(putX+sizeX,putY,srcX+sizeX,srcY,fontSize,fontSize,TRUE,effectType,effectCount1000);

//	m_pic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	CAreaControl::AddArea(putX,putY,sizeX+fontSize,sizeY);
}

void CMyFont::GradPrint(int startX,int endX,int putX,int putY,int deltaX,int deltaY,int sizeX,int sizeY)
{
	if (m_fontCacheNumber == -1) return;	//error!

//	char mes[256];
//	wsprintf(mes,"[%d]",m_fontCacheNumber);
//	OutputDebugString(mes);

	POINT pt = m_fontCache->GetSrc(m_fontCacheNumber);

	int srcX = pt.x + deltaX;
	int srcY = pt.y + deltaY;
	putX += deltaX;
	putY += deltaY;

	m_fontCache->GradBlt(startX,endX,m_mainFontSize,putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
//	m_pic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	CAreaControl::AddArea(putX,putY,sizeX,sizeY);
}


void CMyFont::PrintRubi(int putX,int putY,int deltaX,int deltaY,int sizeX,int sizeY)
{
	if (m_fontCacheNumber == -1) return;	//error!

//	char mes[256];
//	wsprintf(mes,"[%d]",m_fontCacheNumber);
//	OutputDebugString(mes);

	int rubiFontSize = GetRubiFontSize();

	if ((deltaY+sizeY) > rubiFontSize)
	{
		sizeY = rubiFontSize - deltaY;
		if (sizeY <= 0) return;
	}

	POINT pt = m_fontCache->GetSrc(m_fontCacheNumber);

	int srcX = pt.x + deltaX;
	int srcY = pt.y + deltaY;
	putX += deltaX;
	putY += deltaY;

	putY -= rubiFontSize;
	putY += m_rubiDeltaY;

//	CAllGeo::BoxFill(putX,putY,sizeX,sizeY,128,128,128);
	m_fontCache->BltRubi(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);


//	m_pic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	CAreaControl::AddArea(putX,putY,sizeX,sizeY);
}

void CMyFont::GradPrintRubi(int startX,int endX,int putX,int putY,int deltaX,int deltaY,int sizeX,int sizeY)
{
	if (m_fontCacheNumber == -1) return;	//error!

//	char mes[256];
//	wsprintf(mes,"[%d]",m_fontCacheNumber);
//	OutputDebugString(mes);

	int rubiFontSize = GetRubiFontSize();

	if ((deltaY+sizeY) > rubiFontSize)
	{
		sizeY = rubiFontSize - deltaY;
		if (sizeY <= 0) return;
	}

	POINT pt = m_fontCache->GetSrc(m_fontCacheNumber);

	int srcX = pt.x + deltaX;
	int srcY = pt.y + deltaY;
	putX += deltaX;
	putY += deltaY;

	putY -= rubiFontSize;
	putY += m_rubiDeltaY;

//	int fontSize = GetFontSize();

	m_fontCache->GradBltRubi(startX,endX,m_mainFontSize,putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
//	m_pic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	CAreaControl::AddArea(putX,putY,sizeX,sizeY);
}

void CMyFont::SetUserGaijiFont(LPSTR filenameonly)
{
	char filename[256];
	wsprintf(filename,"sys\\%s",filenameonly);
	m_userGaijiFontPic = new CPicture();
	if (m_userGaijiFontPic->LoadDWQ(filename))
	{
		m_userGaijiFontPicBuffer = (int*)(m_userGaijiFontPic->GetBuffer());
#if defined _TINYAN3DLIB_
		m_userGaijiFontPicBuffer += 128 / sizeof(int);
#endif	

		SIZE sz = m_userGaijiFontPic->GetPicSize();
		m_userGaijiSizeX = sz.cx;
	}
}


void CMyFont::ReCreateDIB(void)
{
return;
	if (m_src != NULL)
	{
		DeleteDC(m_src);
		m_src = NULL;
	}

	if (m_hBitmap != NULL)
	{
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}
/*	
	for (int i=0;i<=MYFONT_SIZE_MAX;i++)
	{
		if (m_font[i] != NULL)
		{
			DeleteObject(m_font[i]);
			m_font[i] = NULL;
		}
	}
*/

	ZeroMemory(&m_bmi,sizeof(BITMAPV4HEADER));

	int screenSizeX = CMyGraphics::GetScreenSizeX();


	m_bmi.bV4BitCount = 32;
	m_bmi.bV4AlphaMask = 0xff000000;
	m_bmi.bV4BlueMask = 0x000000ff;
	m_bmi.bV4GreenMask = 0x0000ff00;
	m_bmi.bV4Width = screenSizeX*2;
	m_bmi.bV4V4Compression = BI_RGB;
	m_bmi.bV4Size = sizeof(BITMAPV4HEADER);
	m_bmi.bV4RedMask = 0x00ff0000;
	m_bmi.bV4Planes = 1;
	m_bmi.bV4Height = -MYFONT_SIZE_MAX*2;

	HDC hdc = GetDC(m_hWnd);
	m_hBitmap = CreateDIBSection(hdc,(BITMAPINFO*)&m_bmi,DIB_RGB_COLORS,(void**)(&m_lpBuffer),NULL,0);

	m_src = CreateCompatibleDC(hdc);
	m_oldBitmap = SelectObject(m_src,m_hBitmap);
	m_oldBkMode = SetBkMode(m_src,TRANSPARENT);
	m_oldTextColor = SetTextColor(hdc,0);

	ReleaseDC(m_hWnd,hdc);

/*
	for (int i=0;i<=MYFONT_SIZE_MAX;i++)
	{
		m_font[i] = NULL;
	}

	for (int i=0;i<7;i++)
	{
		int fontsize = m_fontSizeTable[i];
		HFONT hfont = MakeFont(m_fontName1,fontsize);
		if (hfont == NULL)
		{
			hfont = MakeFont(m_fontName2,fontsize);
		}

		m_font[fontsize] = hfont;
	}
	*/
}


int CMyFont::GetRubiFontSize(void)
{
	return m_rubiFontSize;
}

void CMyFont::ClearFontCache(void)
{
	if (m_fontCache != NULL)
	{
		m_fontCache->ClearFontCache();
	}
}
