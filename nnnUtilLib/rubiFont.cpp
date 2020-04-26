//
// rubiFont.cpp
//

#include <windows.h>
#include "..\nyanLib\include\commonmacro.h"

#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"


//#include "game.h"

#define RUBI_KOSUU_MAX 100

#include "rubiFont.h"

#define DIB_MASK_COLOR 0x00C0E080
#define MYGRAY_COLOR 0x505050


int CRubiFont::m_fontType = 0;
int CRubiFont::m_userFont = 0;
char CRubiFont::m_userFontName[256] ="‚l‚r ƒSƒVƒbƒN";



COLORREF CRubiFont::m_rubiColor[RUBI_KOSUU_MAX];
LPSTR CRubiFont::m_rubiMessage[RUBI_KOSUU_MAX];
int CRubiFont::m_rubiZahyo[RUBI_KOSUU_MAX*2];
int CRubiFont::m_rubiLength[RUBI_KOSUU_MAX];


int CRubiFont::m_fontSizeTable[7]=
{
	12,14,16,18,20,22,24
};


CRubiFont::CRubiFont(HWND hwnd)
{
	m_rubiKosuu = 0;
//	m_game = lpGame;
//	m_hWnd = m_game->GetHWND();
	m_hWnd = hwnd;


//	BITMAPV4HEADER bmi;

	ZeroMemory(&m_bmi,sizeof(BITMAPV4HEADER));


	m_bmi.bV4BitCount = 32;
	m_bmi.bV4AlphaMask = 0xff000000;
	m_bmi.bV4BlueMask = 0x000000ff;
	m_bmi.bV4GreenMask = 0x0000ff00;
	m_bmi.bV4Width = 640*2;
	m_bmi.bV4V4Compression = BI_RGB;
	m_bmi.bV4Size = sizeof(BITMAPV4HEADER);
	m_bmi.bV4RedMask = 0x00ff0000;
	m_bmi.bV4Planes = 1;
	m_bmi.bV4Height = -32*2;





	HDC hdc = GetDC(m_hWnd);
	m_hBitmap = CreateDIBSection(hdc,(BITMAPINFO*)&m_bmi,DIB_RGB_COLORS,(void**)(&m_lpBuffer),NULL,0);

	m_src = CreateCompatibleDC(hdc);
	m_oldBitmap = SelectObject(m_src,m_hBitmap);
	SetBkMode(m_src,TRANSPARENT);

	ReleaseDC(m_hWnd,hdc);


//	m_pic = new CPicture("sys\\w640x32");
//	m_pic->LoadAntiAlias2("sys\\w640x32");
	m_pic = new CPicture(640,32,TRUE);

	m_specialFontPic = new CPicture("sys\\spfont24");
	m_picBuffer = (int*)(m_pic->GetBuffer());
	m_antiBuffer = m_pic->GetMaskPic();

	m_specialFontPicBuffer = (int*)(m_specialFontPic->GetBuffer());

	RECT rc;
	m_specialFontPic->GetPicSize(&rc);
	m_specialFontSizeX = rc.right;

	m_fontAdjustWidth = 16;
	m_fontAdjustHeight = 32;


	char gothic[] = "‚l‚r ƒSƒVƒbƒN";
	char mincho[] = "‚l‚r –¾’©";

	LPSTR fontname1;
	if (m_fontType == 0)
	{
		fontname1 = gothic;
	}
	else
	{
		fontname1 = mincho;
	}
	LPSTR fontname2 = fontname1;

	if (m_userFont != 0)
	{
		fontname1 = m_userFontName;
	}

	int i = 0;
	for (i=0;i<=24;i++)
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

//	m_src = NULL;
//	m_hdc = NULL;
	m_oldFont = NULL;
//	m_oldBitmap = NULL;
}



CRubiFont::~CRubiFont()
{
	End();
}

void CRubiFont::End(void)
{
	EndPrint();

	if (m_src != NULL)
	{
		if (m_oldFont != NULL)
		{
			SelectObject(m_src,(HGDIOBJ)m_oldFont);
			m_oldFont = NULL;
		}


		if (m_oldBitmap != NULL)
		{
			SelectObject(m_src,(HGDIOBJ)m_oldBitmap);
			m_oldBitmap = NULL;
		}

		DeleteDC(m_src);
		m_src = NULL;
	}

	if (m_hBitmap != NULL)
	{
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}

	ENDDELETECLASS(m_pic);
	ENDDELETECLASS(m_specialFontPic);

	for (int i=0;i<=24;i++)
	{
		if (m_font[i] != NULL)
		{
			DeleteObject(m_font[i]);
			m_font[i] = NULL;
		}
	}
}


void CRubiFont::Reset(void)
{
	m_rubiKosuu = 0;
}

BOOL CRubiFont::AddRubi(int x, int y, LPSTR mes, COLORREF col,int ln)
{
	if (m_rubiKosuu>=RUBI_KOSUU_MAX) return FALSE;
	m_rubiColor[m_rubiKosuu] = col;
	m_rubiZahyo[m_rubiKosuu*2] = x;
	m_rubiZahyo[m_rubiKosuu*2+1] = y;
	m_rubiMessage[m_rubiKosuu] = mes;
	m_rubiLength[m_rubiKosuu] = ln;
	
	m_rubiKosuu++;

	return TRUE;
}


void CRubiFont::PrintRubi(HDC hdc)
{
	if (m_rubiKosuu<=0) return;
	if (hdc == NULL) return;


	int md = GetBkMode(hdc);

	COLORREF colMae = m_rubiColor[0];
	//set color?
	SetTextColor(hdc,colMae);

	
	for (int i=0;i<m_rubiKosuu;i++)
	{
		COLORREF col = m_rubiColor[i];
		if (col != colMae)
		{
			colMae = col;
			//set color
			SetTextColor(hdc,col);


		}

		LPSTR mes = m_rubiMessage[i];
		int x = m_rubiZahyo[i*2];
		int y = m_rubiZahyo[i*2+1];
		int ln = m_rubiLength[i];

		TextOut(hdc,x,y,mes,ln);
char mes0[256];
memcpy(mes0,mes,16);
mes0[16]=0;
char mes1[256];
wsprintf(mes1,"[%s x=%d y=%d ln=%d]",mes0,x,y,ln);
OutputDebugString(mes1);

	}

	SetBkMode(hdc,md);

}



CPicture* CRubiFont::GetPic(void)
{
	return m_pic;
}

void CRubiFont::BeginPrint(int fontsize, BOOL bAntiAliasFlag)
{
	if (m_fontFlag == TRUE) return;



	int newFontSize = GetFontSize(fontsize);
	if (m_nowFontSize != newFontSize)
	{
		m_nowFontSize = newFontSize;

		HFONT hfont = m_font[m_nowFontSize];

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

	m_fontFlag = TRUE;
}


void CRubiFont::EndPrint(void)
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



int CRubiFont::MakePic(LPSTR message, int colR, int colG, int colB ,int sukima, int kageColor, COLORREF* colorPtr)
{
//return 640 | (32<<16);//picsize

	int i,j;

	if (m_fontFlag == FALSE) return 0;

	HDC hdc = m_src;


	if (colR == -1) colR = 255;
	if (colG == -1) colG = colR;
	if (colB == -1) colB = colG;

	COLORREF col = COLORREF(colR | (colG << 8) | (colB<<16));

	if (colorPtr != NULL)
	{
		col = *colorPtr;
		colB = (col >> 16) & 0xff;
		colG = (col >> 8 ) & 0xff;
		colR = (col      ) & 0xff;
	}

	int ln = (int)strlen(message);
	ln /= 2;


	//Fill GREY
	int sizeY = m_nowFontSize*2;
	int sizeX = (m_nowFontSize+sukima)*2*ln;
	if (sizeX>640*2) sizeX = 640*2;

	int* dst0 = (int*)m_lpBuffer;
	
	for (j=0;j<sizeY;j++)
	{
		int* dst = dst0;
		for (i=0;i<sizeX;i++)
		{
			*dst = MYGRAY_COLOR;
			dst++;
		}
		dst0 += 640*2;
	}





	int x = 2;
	int y = 2;
	int stp = (m_nowFontSize+sukima) * 2;

	if (kageColor != -1)
	{
		SetTextColor(m_src,COLORREF(kageColor));

		for (i=0;i<ln;i++)
		{
			char ckc = *(message+i*2);
			if (ckc != (char)0x80)
			{
				TextOut(hdc,x,y,message+i*2,2);
			}
			else
			{
				Gaiji(x,y,kageColor,*(message+i*2+1));
			}

			x += stp;
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

		if ((*(message + i* 2)) != (char)0x80)
		{
			TextOut(hdc,x,y,message+i*2,2);
		}
		else
		{
			int col2 = (colR<<16) | (colG<<8) | (colB);
			Gaiji(x,y,col2,*(message + i*2+1));
		}
		x += stp;

		lastColor = col;
	}


	//Fill DIB_MASK_COLOR
	int sizeY2 = m_nowFontSize;
	int sizeX2 = (m_nowFontSize+sukima)*ln;
	if (sizeX2>640) sizeX2 = 640;

	dst0 = (int*)m_picBuffer;
	
	for (j=0;j<sizeY2;j++)
	{
		int* dst = dst0;
		for (i=0;i<sizeX2;i++)
		{
			*dst = DIB_MASK_COLOR;
			dst++;
		}
		dst0 += 640;
	}

	//antialias copy

	int* src0 = (int*)m_lpBuffer;
	dst0 = (int*)m_picBuffer;

	unsigned char* anti0 = (unsigned char*)m_antiBuffer;

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
					int d = *(src+ii+jj*640*2);
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
				}
				else if (kosuu == 1)
				{
//					rr /= kosuu;
//					gg /= kosuu;
//					bb /= kosuu;
					*anti = 64;
				}
				else	//kosuu == 3
				{
					rr /= kosuu;
					gg /= kosuu;
					bb /= kosuu;
					*anti = 192;
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


		src0 += (640*2)*2;
		dst0 += 640;
		anti0 += 640;
	}



	//¶ã‚ð“§–¾F‚É
	*(m_picBuffer) = DIB_MASK_COLOR;


	//ƒAƒ“ƒ`ƒGƒŠƒAƒXƒf[ƒ^‚ð‚Â‚­‚é‚©???



	return sizeX2 | (sizeY2<<16);//picsize
}



int CRubiFont::GetFontSize(int fontsize)
{
	for (int i=0;i<7;i++)
	{
		if (fontsize <= m_fontSizeTable[i]) return m_fontSizeTable[i];
	}

	return m_fontSizeTable[6];
}



HFONT CRubiFont::MakeFont(LPSTR fontname,int fontsize)
{
	return CreateFont(	fontsize*2,fontsize*2/2,0,0,FW_BOLD,FALSE,FALSE,FALSE,
						SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS ,DEFAULT_QUALITY,
						FIXED_PITCH | FF_DONTCARE,
						fontname);
}


void CRubiFont::Gaiji(int x,int y,int col,int dat)
{
	if ((dat < 1) || (dat > 11)) return;	//not support gaiji

	int* dst = (int*)m_lpBuffer;
	int* src = (int*)m_specialFontPicBuffer;

	dst += x;
	dst += y * 640 * 2;

	src += (dat-1) * 50;

	int c = col;

	if (m_nowFontSize == 24)
	{
		for (int j=0;j<48;j++)
		{
			int* src0 = src;
			int* dst0 = dst;

			for (int i=0;i<50;i++)
			{
				if ((*src) != 0)
				{
					*dst = c;
				}
				dst++;
				src++;
			}
			
			src = src0;
			src += m_specialFontSizeX; 
			dst = dst0;
			dst += 640*2;
		}

		return;
	}

	int sy = m_nowFontSize*2;
	int sx = sy*2 + 2;

	int* src0 = src;
	for (int j=0;j<sy;j++)
	{
		int* dst0 = dst;

		int* src1 = src0 + ((j*48)/sy) * m_specialFontSizeX;
		for (int i=0;i<sx;i++)
		{
			int* src2 = src1 + (i*50)/sx;

			if ((*src2) != 0)
			{
				*dst = c;
			}
			dst++;
		}

		dst = dst0;
		dst += 640*2;
	}


}