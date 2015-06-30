#include <windows.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanlib\include\myGraphics.h"

#include "..\nyanLib\include\myFile.h"

#include "..\nnnUtilLib\nameList.h"

#include "polygonShape.h"


CPolygonShape::CPolygonShape(int sizeX,int sizeY)
{
	m_sizeX = sizeY;
	if (sizeY < 0) sizeY = sizeX;
	m_sizeY = sizeY;

	m_type = -1;
	m_work = new int[sizeY*4];
}

CPolygonShape::~CPolygonShape()
{
	End();
}

void CPolygonShape::End(void)
{
	DELETEARRAY(m_work);

}



void CPolygonShape::SetCircleShape(int end,int start,int mx)
{
	if ((m_type == 1) && (m_start=start) && (m_end == end) && (m_max == mx)) return;

	m_type = 1;
	m_start = start;
	m_end = end;
	m_max = mx;

	ZeroMemory(m_work,sizeof(int)*m_sizeY*4);

	int centerX = m_sizeX / 2;
	int centerY = m_sizeY / 2;


	double th1 = (double)start;
	th1 *= M_PI * 2.0;
	th1 /= (double)m_max;

	int end0 = m_end;
	if (end0 > m_max)
	{
		end0 = m_max;
	}

	double th2 = (double)end0;
	th2 *= M_PI * 2.0;
	th2 /= (double)m_max;

	double rr = (double)(m_sizeY/2)-1;

	if (th1 < M_PI*0.5)
	{
		int leftStartX = centerX + (int)(rr * sin(th1));
		int leftStartY = centerY - (int)(rr * cos(th1));
		int rightEndX = centerX + (int)rr;
		int rightEndY = centerY;
		if (th2 < M_PI*0.5)
		{
			rightEndY = centerY - (int)(rr * cos(th2));
		}

		m_leftX1 = leftStartX;
		m_leftY1 = leftStartY;
		m_leftX2 = centerX;
		m_leftY2 = centerY;

		MakeCircleTableRight(leftStartY,rightEndY-leftStartY);

		if (rightEndY<centerY)
		{
			m_rightX1 = rightEndX;
			m_rightY1 = rightEndY;
			m_rightX2 = centerX;
			m_rightY2 = centerY;
			MakeTable(rightEndY,centerY-rightEndY,rightEndY-leftStartY,0);
		}

	}

	if ((th1 < M_PI*1.0) && (th2 >=M_PI*0.5))
	{
		double th = th1;
		if (th<=M_PI*0.5) th = M_PI*0.5;
		if (th>=M_PI*1.0) th = M_PI*1.0;

		int rightX = centerX + (int)(rr * sin(th));
		int rightY = centerY - (int)(rr * cos(th));

		th = th2;
		if (th<=M_PI*0.5) th = M_PI*0.5;
		if (th>=M_PI*1.0) th = M_PI*1.0;


		int leftX = centerX + (int)(rr * sin(th));
		int leftY = centerY - (int)(rr * cos(th));


		m_leftX1 = centerX;
		m_leftY1 = centerY;
		m_leftX2 = leftX;
		m_leftY2 = leftY;
		m_rightX1 = centerX;
		m_rightY1 = centerY;
		m_rightX2 = rightX;
		m_rightY2 = rightY;

		MakeTable(centerY,rightY-centerY,0,0);
		MakeCircleTableRight(rightY,leftY-rightY+1,rightY-centerY);
	}


	if ((th1 < M_PI*1.5) && (th2 >= M_PI*1.0))
	{
		double th = th1;
		if (th<=M_PI*1.0) th = M_PI*1.0;
		if (th>=M_PI*1.5) th = M_PI*1.5;

		int rightX = centerX + (int)(rr * sin(th));
		int rightY = centerY - (int)(rr * cos(th));

		th = th2;
		if (th<=M_PI*1.0) th = M_PI*1.0;
		if (th>=M_PI*1.5) th = M_PI*1.5;


		int leftX = centerX + (int)(rr * sin(th));
		int leftY = centerY - (int)(rr * cos(th));


		m_leftX1 = centerX;
		m_leftY1 = centerY;
		m_leftX2 = leftX;
		m_leftY2 = leftY;
		m_rightX1 = centerX;
		m_rightY1 = centerY;
		m_rightX2 = rightX;
		m_rightY2 = rightY;

		MakeTable(centerY,leftY-centerY,0,0);
		MakeCircleTableLeft(leftY,rightY-leftY+1,leftY-centerY);
	}

	if ((th1 < M_PI*2.0) && (th2 >= M_PI*1.5))
	{
		double th = th1;
		if (th<=M_PI*1.5) th = M_PI*1.5;
		if (th>=M_PI*2.0) th = M_PI*2.0;

		int leftX = centerX + (int)(rr * sin(th));
		int leftY = centerY - (int)(rr * cos(th));

		th = th2;
		if (th<=M_PI*1.5) th = M_PI*1.5;
		if (th>=M_PI*2.0) th = M_PI*2.0;


		int rightX = centerX + (int)(rr * sin(th));
		int rightY = centerY - (int)(rr * cos(th));




		m_rightX2 = centerX;
		m_rightY2 = centerY;
		m_rightX1 = rightX;
		m_rightY1 = rightY;
		MakeCircleTableLeft(rightY,leftY-rightY,leftY-centerY);


		m_leftX2 = centerX;
		m_leftY2 = centerY;
		m_leftX1 = leftX;
		m_leftY1 = leftY;
		m_rightX2 = centerX;
		m_rightY2 = centerY;
		m_rightX1 = rightX;
		m_rightY1 = rightY;

		MakeTable(leftY,centerY-leftY,0,leftY-rightY);
	}
}

void CPolygonShape::SetRadarShape(int n,int n1,int data1,int data2,int mx)
{
	if (n<3) return;

	BOOL f = TRUE;
	if (m_type != 2) f = FALSE;
	if (n != m_n) f = FALSE;
	if (n1 != m_n1) f = FALSE;
	if (data1 != m_data1) f = FALSE;
	if (data2 != m_data2) f = FALSE;
	if (mx != m_max) f = FALSE;

	if (f) return;

	m_type = 2;
	m_max = mx;
	m_n = n;
	m_n1 = n1;
	m_data1 = data1;
	m_data2 = data2;


	ZeroMemory(m_work,sizeof(int)*m_sizeY*4);

	int centerX = m_sizeX / 2;
	int centerY = m_sizeY / 2;
	int x[3];
	int y[3];
	x[0] = centerX;
	y[0] = centerY;
	double r = (double)m_sizeX;
	r /= 2.0;
	r -= 1.0;

	double th1 = (double)n1;
	th1 /= (double)m_n;
	th1 *= M_PI;
	th1 *= 2.0;
	th1 -= M_PI / 2.0;

	double th2 = (double)(n1+1);
	th2 /= (double)m_n;
	th2 *= M_PI;
	th2 *= 2.0;
	th2 -= M_PI / 2.0;

	double r1 = (double)data1;
	r1 /= (double)m_max;
	r1 *= r;
	if (r1>r) r1 = r;

	double r2 = (double)data2;
	r2 /= (double)m_max;
	r2 *= r;
	if (r2>r) r2 = r;

	double c1 = cos(th1) * r1;
	double s1 = sin(th1) * r1;
	double c2 = cos(th2) * r2;
	double s2 = sin(th2) * r2;

	x[2] = (int)((double)centerX + c1 + 0.5);
	y[2] = (int)((double)centerY + s1 + 0.5);
	x[1] = (int)((double)centerX + c2 + 0.5);
	y[1] = (int)((double)centerY + s2 + 0.5);

	int topN = 0;
	int yTop = y[0];

	for (int i=1;i<3;i++)
	{
		if (y[i] < yTop)
		{
			yTop = y[i];
			topN = i;
		}
	}

	if (topN < 2)
	{
		if (y[topN] == y[topN+1])
		{
			topN = topN + 1;
		}
	}

	if ((y[0] == y[1]) && (y[1] == y[2])) return;

	int xx[3];
	int yy[3];
	for (int i=0;i<3;i++)
	{
		int k = (i+topN) % 3;
		xx[i] = x[k];
		yy[i] = y[k];
	}

	if (yy[0] == yy[2])
	{
		m_leftX1 = xx[0];
		m_leftY1 = yy[0];
		m_leftX2 = xx[1];
		m_leftY2 = yy[1];
		m_rightX1 = xx[2];
		m_rightY1 = yy[2];
		m_rightX2 = xx[1];
		m_rightY2 = yy[1];

		int loop = yy[1]-yy[0];
		if (loop>0)
		{
			MakeTable(yy[0],loop, 0,0);
		}
	}
	else
	{
		m_leftX1 = xx[0];
		m_leftY1 = yy[0];
		m_leftX2 = xx[1];
		m_leftY2 = yy[1];
		m_rightX1 = xx[0];
		m_rightY1 = yy[0];
		m_rightX2 = xx[2];
		m_rightY2 = yy[2];

		if (yy[1] == yy[2])
		{
			int loop = yy[1]-yy[0];

			if (loop>0)
			{
				MakeTable(yy[0],loop, 0,0);
			}
		}
		else if (yy[1] < yy[2])
		{
			int loop1 = yy[1]-yy[0];
			if (loop1>0)
			{
				MakeTable(yy[0],loop1, 0,0);
			}

			int loop2 = yy[2] - yy[1];
			if (loop2 > 0)
			{
				m_leftX1 = xx[1];
				m_leftY1 = yy[1];
				m_leftX2 = xx[2];
				m_leftY2 = yy[2];
				
				MakeTable(yy[1],loop2, 0,yy[1]-yy[0]);
			}
		}
		else
		{
			int loop1 = yy[2]-yy[0];
			if (loop1>0)
			{
				MakeTable(yy[0],loop1, 0,0);
			}

			int loop2 = yy[1] - yy[2];
			if (loop2 > 0)
			{
				m_rightX1 = xx[2];
				m_rightY1 = yy[2];
				m_rightX2 = xx[1];
				m_rightY2 = yy[1];
				
				MakeTable(yy[2],loop2, yy[2]-yy[0],0);
			}
		}
	}


}

void CPolygonShape::MakeTable(int baseY,int loop,int leftStart,int rightStart)
{
	int leftDiv = m_leftY2 - m_leftY1;
	if (leftDiv < 1) leftDiv = 1;
	int rightDiv = m_rightY2 - m_rightY1;
	if (rightDiv < 1) rightDiv = 1;

	for (int i=0;i<loop;i++)
	{
		int leftY = leftStart + i;
		int rightY = rightStart + i;

		int leftX = m_leftX1 + ((m_leftX2 - m_leftX1) * leftY) / leftDiv;
		int rightX = m_rightX1 + ((m_rightX2 - m_rightX1) * rightY) / rightDiv;

		int sz = rightX - leftX;
		if (sz > 0)
		{
			if (*(m_work + (baseY+i)*4 + 1) == 0)
			{
				*(m_work + (baseY+i)*4 + 0) = leftX;
				*(m_work + (baseY+i)*4 + 1) = sz;
			}
			else if (*(m_work + (baseY+i)*4 + 3) == 0)
			{
				*(m_work + (baseY+i)*4 + 2) = leftX;
				*(m_work + (baseY+i)*4 + 3) = sz;
			}
		}
	}

}

void CPolygonShape::MakeCircleTableRight(int baseY,int loop,int skp)
{
	int leftDiv = m_leftY2 - m_leftY1;
	if (leftDiv < 1) leftDiv = 1;

	int centerX = m_sizeX / 2;
	int centerY = m_sizeY / 2;

	double rr0 = (double)(m_sizeY/2)-1.0;
	double rr02 = rr0*rr0;


	for (int i=0;i<loop;i++)
	{
		int leftY = m_leftY1 + i + skp;
		int leftX = m_leftX1 + ((m_leftX2 - m_leftX1) * (i+skp)) / leftDiv;

		double yy = (double)leftY;
		yy -= (double)centerY;
		double rr = rr02 - yy*yy;
		if (rr<0.0) rr = 0.0;

		double xx = sqrt(rr);
		int rightX = centerX + (int)(xx);

		int sz = rightX - leftX;
		if (sz > 0)
		{
			if (*(m_work + (baseY+i)*4 + 1) == 0)
			{
				*(m_work + (baseY+i)*4 + 0) = leftX;
				*(m_work + (baseY+i)*4 + 1) = sz;
			}
			else if (*(m_work + (baseY+i)*4 + 3) == 0)
			{
				*(m_work + (baseY+i)*4 + 2) = leftX;
				*(m_work + (baseY+i)*4 + 3) = sz;
			}
		}
	}

}

void CPolygonShape::MakeCircleTableLeft(int baseY,int loop,int skp)
{
	int rightDiv = m_rightY2 - m_rightY1;
	if (rightDiv < 1) rightDiv = 1;

	int centerX = m_sizeX / 2;
	int centerY = m_sizeY / 2;

	double rr0 = (double)(m_sizeY/2)-1.0;
	double rr02 = rr0*rr0;


	for (int i=0;i<loop;i++)
	{
		int rightY = m_rightY1 + i + skp;
		int rightX = m_rightX1 + ((m_rightX2 - m_rightX1) * (i+skp)) / rightDiv;

		double yy = (double)rightY;
		yy -= (double)centerY;
		double rr = rr02 - yy*yy;
		if (rr<0.0) rr = 0.0;

		double xx = sqrt(rr);
		int leftX = centerX - (int)(xx);

		int sz = rightX - leftX;
		if (sz > 0)
		{
			if (*(m_work + (baseY+i)*4 + 1) == 0)
			{
				*(m_work + (baseY+i)*4 + 0) = leftX;
				*(m_work + (baseY+i)*4 + 1) = sz;
			}
			else if (*(m_work + (baseY+i)*4 + 3) == 0)
			{
				*(m_work + (baseY+i)*4 + 2) = leftX;
				*(m_work + (baseY+i)*4 + 3) = sz;
			}
		}
	}

}

void CPolygonShape::PrintCircleGraph(CPicture* lpPic,int x,int y)
{
	if (m_type != 1) return;
	PrintPic(lpPic,x,y);
}

void CPolygonShape::PrintCircleGraph(int r,int g,int b,int a,int x,int y)
{
	if (m_type != 1) return;
	PrintPolygon(r,g,b,a,x,y);
}

void CPolygonShape::PrintRadar(CPicture* lpPic,int x,int y)
{
	if (m_type != 2) return;
	if (m_n < 3) return;
	PrintPic(lpPic,x,y);
}

void CPolygonShape::PrintRadar(int r,int g,int b,int a,int x,int y)
{
	if (m_type != 2) return;
	if (m_n < 3) return;
	PrintPolygon(r,g,b,a,x,y);
}

void CPolygonShape::PrintPolygon(int r,int g, int b, int a,int x,int y)
{
	int srcX = 0;
	int srcY = 0;
	int dstX = x;
	int dstY = y;
	int sizeX = m_sizeX;
	int sizeY = m_sizeY;
	if (!Clip(srcX,srcY,dstX,dstY,sizeX,sizeY)) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();

	int* dst0 = CMyGraphics::GetScreenBuffer();
	dst0 += dstX;
	dst0 += dstY * screenSizeX;
	int* table = m_work;
	table += srcY*4;

	int col = (r << 16) | (g << 8) | b;
	int ra = (r * a ) /256;
	int ga = (g * a ) /256;
	int ba = (b * a ) /256;
	int aa = a;

	for (int j=0;j<sizeY;j++)
	{
		for (int ii=0;ii<2;ii++)
		{
			int start = *table;
			table++;
			int loop = *table;
			table++;
			start += srcX;
			loop -= srcX;

			if (loop > 0)
			{

				int* dst = dst0 + start;
				for (int i=0;i<loop;i++)
				{
					if (a == 255)
					{
						*dst = col;
					}
					else
					{
						int d = *dst;
						int rr = (d >> 16) & 0xff;
						int gg = (d >> 8) & 0xff;
						int bb = (d  ) & 0xff;
						rr *= aa;
						gg *= aa;
						bb *= aa;
						rr >>= 8;
						gg >>= 8;
						bb >>= 8;

						rr += ra;
						gg += ga;
						bb += ba;
						int c = (rr << 16) | (gg << 8) | bb;
						*dst = c;
					}

					dst++;
				}
			}
		}
		dst0 += screenSizeX;
	}

}

void CPolygonShape::PrintPic(CPicture* lpPic,int x,int y)
{
	int srcX = 0;
	int srcY = 0;
	int dstX = x;
	int dstY = y;
	int sizeX = m_sizeX;
	int sizeY = m_sizeY;
	if (!Clip(srcX,srcY,dstX,dstY,sizeX,sizeY)) return;

	int screenSizeX = CMyGraphics::GetScreenSizeX();

	int* dst0 = CMyGraphics::GetScreenBuffer();
	dst0 += dstX;
	dst0 += dstY * screenSizeX;
	int* table = m_work;
	table += srcY*4;


	int* srcPic0 = lpPic->GetPictureBuffer();
	char* mask0 = lpPic->GetMaskPic();
	SIZE picSize = lpPic->GetPicSize();
	int picSizeX = picSize.cx;
	int picSizeY = picSize.cy;
	srcPic0 += picSizeX * srcY;
	mask0 += picSizeX * srcY;


	for (int j=0;j<sizeY;j++)
	{
		for (int ii=0;ii<2;ii++)
		{
			int start = *table;
			table++;
			int loop = *table;
			table++;

			start += srcX;
			loop -= srcX;

			if (loop > 0)
			{
				int* dst = dst0 + start;
				int* srcPic = srcPic0 + start;
				char* mask = mask0 + start;

				for (int i=0;i<loop;i++)
				{
					char m = *mask;
					int col = *srcPic;

					if (m == 0xff)
					{
						*dst = col;
					}
					else
					{
						int a = (int)m;
						a &= 0xff;
						int aa = 255-a;

						int dd = *dst;
						int rr = (dd >> 16) & 0xff;
						int gg = (dd >> 8) & 0xff;
						int bb = (dd ) & 0xff;
						rr *= aa;
						gg *= aa;
						bb *= aa;
						rr >>= 8;
						gg >>= 8;
						bb >>= 8;

						int d = *srcPic;
						int r = (d >> 16) & 0xff;
						int g = (d >> 8) & 0xff;
						int b = (d ) & 0xff;
						r *= a;
						g *= a;
						b *= a;
						r >>= 8;
						g >>= 8;
						b >>= 8;

						r += rr;
						g += gg;
						b += bb;

						int c = (r << 16) | (g << 8) | b;

						*dst = c;
					}

					mask++;
					srcPic++;
					dst++;
				}
			}
		}
		mask0 += picSizeX;
		srcPic0 += picSizeX;
		dst0 += screenSizeX;
	}

}


BOOL CPolygonShape::Clip(int& srcX,int& srcY,int& dstX,int& dstY, int& sizeX,int& sizeY)
{

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();

	if (dstX >= screenSizeX) return FALSE;
	if (dstY >= screenSizeY) return FALSE;
	if (dstX+sizeX <= 0) return FALSE;
	if (dstY+sizeY <= 0) return FALSE;

	if (dstX < 0)
	{
		sizeX -= (-dstX);
		srcX += -(dstX);
		dstX = 0;
		if (sizeX <= 0) return FALSE;
	}

	if (dstY < 0)
	{
		sizeY -= (-dstY);
		srcY += -(dstY);
		dstY = 0;
		if (sizeX <= 0) return FALSE;
	}

	if (dstX+sizeX >= screenSizeX)
	{
		sizeX = screenSizeX - dstX;
		if (sizeX<=0) return FALSE;
	}

	if (dstY+sizeY >= screenSizeY)
	{
		sizeY = screenSizeY - dstY;
		if (sizeY<=0) return FALSE;
	}



	return TRUE;
}

/*_*/

