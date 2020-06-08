//
// mySlider.cpp
//

#include <windows.h>
#include "..\nyanLib\include\commonmacro.h"

#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\areaControl.h"

//#include "myButtonStatus.h"
#include "myMouseStatus.h"

#include "mySlider.h"

CMySlider::CMySlider(CPicture* lpPic, int devide, int printX, int printY, int sizeX, int sizeY, int srcX, int srcY, BOOL transFlag, CPicture* lpBGPic, BOOL tateCutFlag)
{
	m_gaze = 0;
	m_cursorFlag = FALSE;
	m_cursorPic = NULL;
	m_pic = lpPic;
	m_devide = devide;
	m_printX = printX;
	m_printY = printY;
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_srcX = srcX;
	m_srcY = srcY;
	m_transFlag = transFlag;
	m_bgPic = lpBGPic;
	m_tateCutFlag = tateCutFlag;
	m_dragFlag = FALSE;
	m_tateFlag = FALSE;
	m_digitalFlag = FALSE;

	if (m_devide<1) m_devide = 1;
}

CMySlider::~CMySlider()
{
	End();
}

void CMySlider::End(void)
{
}

void CMySlider::SetCursor(CPicture* lpPic,int deltaX, int deltaY,int sizeX,int sizeY,BOOL flg)
{
	m_cursorFlag = flg;
	m_cursorPic = lpPic;
	m_deltaX = deltaX;
	m_deltaY = deltaY;
	m_cursorSizeX = sizeX;
	m_cursorSizeY = sizeY;
}

void CMySlider::SetDevide(int devide)
{
	if (devide<1) devide = 1;
	m_devide = devide;
}

void CMySlider::Init(int gaze)
{
	m_oldGaze = -1;
	m_gaze = gaze;
	m_dragFlag = FALSE;
}

int CMySlider::Calcu(CMyMouseStatus* lpMouse)
{
	if (lpMouse == NULL)
	{
		return -1;
	}

	m_oldGaze = m_gaze;
	POINT pt = lpMouse->GetZahyo();
	int mouseX = pt.x;
	int mouseY = pt.y;
	BOOL trig1 = lpMouse->GetTrig(0);
	BOOL trig1Mae = lpMouse->GetTrigMae(0);

	if (m_dragFlag)
	{
		m_gaze = CalcuGaze(mouseX,mouseY);
		if (trig1 == FALSE) m_dragFlag = FALSE;
		return m_gaze;
	}

	if (lpMouse->CheckClick())
	{
		if (CheckOnGaze(mouseX,mouseY))
		{
			m_gaze = CalcuGaze(mouseX,mouseY);
			m_dragFlag = TRUE;
			return m_gaze;
		}
	}

	return -1;
}



void CMySlider::Print(BOOL mustPrintFlag,BOOL badFlag)
{
	BOOL b = CAreaControl::CheckAllPrintMode();
	BOOL b2 = FALSE;
	if (m_oldGaze != m_gaze) b2 = TRUE;

	//erase
	if (m_bgPic != NULL)
	{
		if (b || b2 || mustPrintFlag)
		{
			Erase(m_printX,m_printY,m_sizeX,m_sizeY);
		}

		if (m_cursorFlag)
		{
			if (b || b2 || mustPrintFlag)
			{
				if (m_oldGaze != -1)
				{
					int putX = m_printX + m_deltaX + (m_sizeX * m_oldGaze) / m_devide;
					int putY = m_printY + m_deltaY;
					Erase(putX,putY,m_cursorSizeX,m_cursorSizeY);
				}

				if (m_gaze != -1)
				{
					int putX = m_printX + m_deltaX + (m_sizeX * m_gaze) / m_devide;
					int putY = m_printY + m_deltaY;
					Erase(putX,putY,m_cursorSizeX,m_cursorSizeY);
				}
			}
		}
	}

	//print
	if (b || b2 || mustPrintFlag)
	{
		if (m_pic != NULL)
		{
			int sizeX = (m_sizeX * m_gaze) / m_devide;
			if (m_digitalFlag)
			{
				sizeX = (m_sizeX * (m_gaze + 1)) / (m_devide+1);
			}
			int sizeY = m_sizeY;
			if (sizeX>0)
			{
				if (badFlag == FALSE)
				{
					m_pic->Blt(m_printX,m_printY,m_srcX,m_srcY,sizeX,sizeY,m_transFlag);
				}
				else
				{
					if (m_transFlag)
					{
						m_pic->TransLucentBlt3(m_printX,m_printY,m_srcX,m_srcY,sizeX,sizeY,50);
					}
					else
					{
						m_pic->TransLucentBlt0(m_printX,m_printY,m_srcX,m_srcY,sizeX,sizeY,50);
					}
				}
			}
		}

		if (m_cursorFlag)
		{
			if (m_cursorPic != NULL)
			{
				int putX = m_printX + m_deltaX + (m_sizeX * m_gaze) / m_devide;
				int putY = m_printY + m_deltaY;
				m_cursorPic->Blt(putX,putY,0,0,m_cursorSizeX,m_cursorSizeY,TRUE);
			}
		}
	}
}


void CMySlider::AppearPrint(bool badFlag, int count, int countMax, int type, POINT deltaPoint)
{
	BOOL b = CAreaControl::CheckAllPrintMode();
	BOOL b2 = FALSE;
	if (m_oldGaze != m_gaze) b2 = TRUE;

	bool mustPrintFlag = true;

	if ((count == 0) && (countMax > 0)) return;


	int percent = 100;
	int dv = countMax;
	if (dv < 1) dv = 1;
	percent = (100 * count) / dv;
	if (percent < 0) percent = 0;
	if (percent > 100) percent = 100;



	//erase
	if (m_bgPic != NULL)
	{
		if (b || b2 || mustPrintFlag)
		{
			Erase(m_printX, m_printY, m_sizeX, m_sizeY);
		}

		if (m_cursorFlag)
		{
			if (b || b2 || mustPrintFlag)
			{
				if (m_oldGaze != -1)
				{
					int putX = m_printX + m_deltaX + (m_sizeX * m_oldGaze) / m_devide;
					int putY = m_printY + m_deltaY;
					Erase(putX, putY, m_cursorSizeX, m_cursorSizeY);
				}

				if (m_gaze != -1)
				{
					int putX = m_printX + m_deltaX + (m_sizeX * m_gaze) / m_devide;
					int putY = m_printY + m_deltaY;
					Erase(putX, putY, m_cursorSizeX, m_cursorSizeY);
				}
			}
		}
	}

	//print
	if (b || b2 || mustPrintFlag)
	{
		if (m_pic != NULL)
		{
			int sizeX = (m_sizeX * m_gaze) / m_devide;
			if (m_digitalFlag)
			{
				sizeX = (m_sizeX * (m_gaze + 1)) / (m_devide + 1);
			}
			int sizeY = m_sizeY;
			if (sizeX > 0)
			{
				if (badFlag == FALSE)
				{
//					m_pic->Blt(m_printX, m_printY, m_srcX, m_srcY, sizeX, sizeY, m_transFlag);
					m_pic->TransLucentBlt3(m_printX, m_printY, m_srcX, m_srcY, sizeX, sizeY, percent);
				}
				else
				{
					if (m_transFlag)
					{
						m_pic->TransLucentBlt3(m_printX, m_printY, m_srcX, m_srcY, sizeX, sizeY, percent/2);
					}
					else
					{
						m_pic->TransLucentBlt0(m_printX, m_printY, m_srcX, m_srcY, sizeX, sizeY, percent/2);
					}
				}
			}
		}

		if (m_cursorFlag)
		{
			if (m_cursorPic != NULL)
			{
				int putX = m_printX + m_deltaX + (m_sizeX * m_gaze) / m_devide;
				int putY = m_printY + m_deltaY;
//				m_cursorPic->Blt(putX, putY, 0, 0, m_cursorSizeX, m_cursorSizeY, TRUE);
				m_cursorPic->TransLucentBlt3(putX,putY,0,0,m_cursorSizeX, m_cursorSizeY, percent);
			}
		}
	}

}



void CMySlider::Erase(int printX,int printY,int sizeX,int sizeY)
{
	if (m_bgPic != NULL)
	{
		m_bgPic->Blt(printX,printY,printX,printY,sizeX,sizeY,FALSE);
		CAreaControl::AddArea(printX,printY,sizeX,sizeY);
	}
}

BOOL CMySlider::CheckOnGaze(int mouseX,int mouseY)
{
	int checkX = m_printX;
	int checkY = m_printY;

	int sizeX = m_sizeX;
	int sizeY = m_sizeY;
	
	if (m_cursorFlag)
	{
		int sy = m_printY + m_deltaY;
		if (sy<checkY)
		{
			sizeY += checkY - sy;
			checkY = sy;
		}

		int ey = m_printY + m_deltaY + m_cursorSizeY;
		if (ey >= checkY+sizeY)
		{
			sizeY += (ey - (checkY+sizeY));
		}
	}

	mouseX -= checkX;
	mouseY -= checkY;
	if ((mouseX>=0) && (mouseX<=sizeX) && (mouseY>=0) && (mouseY<=sizeY)) return TRUE;

	return FALSE;
}


int CMySlider::CalcuGaze(int mouseX, int mouseY)
{
	int x = mouseX - m_printX;
	if (x<0) x = 0;
	if (x>m_sizeX) x = m_sizeX;

	int gaze = (x * m_devide + m_sizeX / 2) / m_sizeX;

	if (m_digitalFlag)
	{
		gaze = (x * (m_devide+1)) / m_sizeX;
	}


	if (gaze<0) gaze = 0;
	if (gaze>m_devide) gaze = m_devide;
	return gaze;
}

BOOL CMySlider::GetCaptureFlag(void)
{
	return m_dragFlag;
}


/*_*/

