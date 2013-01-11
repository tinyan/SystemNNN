#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\areaControl.h"
#include "..\nyanlib\include\picture.h"
#include "..\nyanlib\include\myGraphics.h"
#include "..\nyanlib\include\allGeo.h"
#include "..\nyanlib\include\allGraphics.h"

#include "..\nnnUtilLib\nameList.h"
#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\InputStatus.h"


#include "myScrollBar.h"

char CMyScrollBar::m_defaultBasePicFileName[] = "ta_scrollBarBase";
char CMyScrollBar::m_defaultBoxPicFileName[] = "ta_scrollBarBox";


CMyScrollBar::CMyScrollBar(LPSTR barname,CNameList* lpSetup,CPicture* lpBG)
{
	m_bg = lpBG;
	m_setup = lpSetup;

	char name[1024];
	char filename[1024];

	int spt = 0;
	GetInitGameParam(&spt,"backScriptFlag");
	if (spt)
	{
		m_bg = NULL;
	}
	int alls = 0;
	GetInitGameParam(&alls,"mustAllPrintFlag");
	if (alls)
	{
		m_bg = NULL;
	}

	wsprintf(name,"%sBaseFileName",barname);
	LPSTR fname = m_defaultBasePicFileName;
	SIZE sz;
	sz.cx = 16;
	sz.cy = 16;

	m_basePic = NULL;
	if (GetInitGameString(&fname,name))
	{
		wsprintf(filename,"sys\\%s",fname);
		m_basePic = new CPicture(filename);
		sz = m_basePic->GetPicSize();
	}


	int x = 0;
	int y = 0;

	wsprintf(name,"%sPrintX",barname);
	GetInitGameParam(&x,name);
	wsprintf(name,"%sPrintY",barname);
	GetInitGameParam(&y,name);
	m_printZahyo.x = x;
	m_printZahyo.y = y;
	wsprintf(name,"%sAreaX",barname);
	GetInitGameParam(&x,name);
	wsprintf(name,"%sAreaY",barname);
	GetInitGameParam(&y,name);
	m_zahyo.x = x;
	m_zahyo.y = y;

	int sizeX = sz.cx;
	int sizeY = sz.cy;
	wsprintf(name,"%sSizeX",barname);
	GetInitGameParam(&sizeX,name);
	wsprintf(name,"%sSizeY",barname);
	GetInitGameParam(&sizeY,name);
	m_printSize.cx = sizeX;
	m_printSize.cy = sizeY;
	wsprintf(name,"%sAreaSizeX",barname);
	GetInitGameParam(&sizeX,name);
	wsprintf(name,"%sAreaSizeY",barname);
	GetInitGameParam(&sizeY,name);
	m_size.cx = sizeX;
	m_size.cy = sizeY;



	wsprintf(name,"%sBoxFileName",barname);
	fname = m_defaultBoxPicFileName;
	if (sz.cx < sz.cy)
	{
		sz.cy = sz.cx;
	}
	else
	{
		sz.cx = sz.cy;
	}

	m_boxPic = NULL;
	if (GetInitGameString(&fname,name))
	{
		wsprintf(filename,"sys\\%s",fname);
		m_boxPic = new CPicture(filename);
		sz = m_boxPic->GetPicSize();
	}
	sizeX = sz.cy;
	sizeY = sz.cy;
	wsprintf(name,"%sBoxSizeX",barname);
	GetInitGameParam(&sizeX,name);
	wsprintf(name,"%sBoxSizeY",barname);
	GetInitGameParam(&sizeY,name);
	m_boxSize.cx = sizeX;
	m_boxSize.cy = sizeY;

	m_tate = 1;
	wsprintf(name,"%sTate",barname);
	GetInitGameParam(&m_tate,name);

	m_captureOk = 1;
	wsprintf(name,"%sCaptureOk",barname);
	GetInitGameParam(&m_captureOk,name);



	m_min = 0;
	m_max = 0;
	wsprintf(name,"%sMin",barname);
	wsprintf(name,"%sMax",barname);
	GetInitGameParam(&m_min,name);

	m_scrollPage = 2;
	wsprintf(name,"%sPage",barname);
	GetInitGameParam(&m_scrollPage,name);

	m_wheelPage = 1;
	wsprintf(name,"%sWheelPage",barname);
	GetInitGameParam(&m_wheelPage,name);

	SetExist();
	SetEnable();

	//button


	//pic auto


	Init();
}


CMyScrollBar::~CMyScrollBar()
{
	End();
}

void CMyScrollBar::End(void)
{
	ENDDELETECLASS(m_basePic);
}


void CMyScrollBar::Init(int pos)
{
	m_pos = pos;
	m_captureFlag = FALSE;
	PosToPrintPos();
}


int CMyScrollBar::Calcu(CInputStatus* lpInput)
{
	if (lpInput == NULL) return -1;

	CMyMouseStatus* mouseStatus = lpInput->GetMouseStatus();

	int scrollSizeX = m_size.cx - m_boxSize.cx;
	int scrollSizeY = m_size.cy - m_boxSize.cy;

	POINT pt = mouseStatus->GetZahyo();

	if (m_captureFlag)
	{
		int oldPos = m_pos;

		int x = pt.x - m_captureDelta.x;
		int y = pt.y - m_captureDelta.y;

		if (m_tate)
		{
			x = 0;
			y -= m_zahyo.y;
			if (y<0) y = 0;
			if (y>scrollSizeY)
			{
				y = scrollSizeY;
			}
		}
		else
		{
			y = 0;
			x -= m_zahyo.x;
			if (x<0) x = 0;
			if (x>scrollSizeX)
			{
				x = scrollSizeX;
			}
		}

		m_printPos.x = x;
		m_printPos.y = y;

		PrintPosToPos();

		if (mouseStatus->GetTrig(0) == FALSE)
		{
			m_captureFlag = FALSE;
		}
		
		if (m_pos != oldPos)
		{
			return m_pos;
		}
		return -1;
	}


	int ud = -1;

	if (mouseStatus->CheckClick())
	{
		if (CheckOnBox(pt))
		{
			POINT pt2 = GetBoxZahyo();
			m_captureDelta.x = pt.x - pt2.x;
			m_captureDelta.y = pt.y - pt2.y;
			m_captureFlag = TRUE;
			return -1;
		}


		int oldPos = m_pos;
		int ud = CheckOnBar(pt);
		if (ud == 0)
		{
			m_pos -= m_scrollPage;
			AdjustInScroll();
			PosToPrintPos();
		}
		else if (ud == 1)
		{
			m_pos += m_scrollPage;
			AdjustInScroll();
			PosToPrintPos();
		}

		if (m_pos != oldPos)
		{
			return m_pos;
		}
	}

	int wheel = mouseStatus->GetWheel();
	if (wheel != 0)
	{
		int oldPos = m_pos;
		if (wheel > 0)
		{
			m_pos -= m_wheelPage;
			AdjustInScroll();
			PosToPrintPos();
		}
		else if (wheel < 0)
		{
			m_pos += m_wheelPage;
			AdjustInScroll();
			PosToPrintPos();
		}

		if (m_pos != oldPos)
		{
			return m_pos;
		}
	}



	return -1;
}


void CMyScrollBar::Print(BOOL flg)
{
	if (m_existFlag == FALSE) return;
	

	if (m_basePic != NULL)
	{
		int putX = m_printZahyo.x;
		int putY = m_printZahyo.y;
		int srcX = 0;
		int srcY = 0;
		int sizeX = m_printSize.cx;
		int sizeY = m_printSize.cy;

		if (m_bg != NULL)
		{
			m_bg->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
		}

		m_basePic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}

	if (m_boxPic != NULL)
	{
		int putX = m_zahyo.x + m_printPos.x;
		int putY = m_zahyo.y + m_printPos.y;
		int srcX = 0;
		int srcY = 0;
		int sizeX = m_boxSize.cx;
		int sizeY = m_boxSize.cy;
		m_boxPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
	}
}


void CMyScrollBar::SetExist(BOOL flg)
{
	m_existFlag = flg;
}

void CMyScrollBar::SetEnable(BOOL flg)
{
	m_enableFlag = flg;
	//button

}

void CMyScrollBar::SetZahyo(POINT pt)
{
	m_zahyo = pt;
	//button?
}

void CMyScrollBar::SetSize(SIZE sz)
{
	m_size = sz;
}





BOOL CMyScrollBar::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}


BOOL CMyScrollBar::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}


void CMyScrollBar::PosToPrintPos(void)
{
	int dv = m_max - m_min;
	if (dv<1) dv = 1;
	int mulX = 0;
	int mulY = 0;

	if (m_tate)
	{
		mulY = m_size.cy - m_boxSize.cy;
	}
	else
	{
		mulX = m_size.cx - m_boxSize.cx;
	}

	int x = (m_pos * mulX) / dv;
	int y = (m_pos * mulY) / dv;

	m_printPos.x = x;
	m_printPos.y = y;
}

void CMyScrollBar::PrintPosToPos(void)
{
	int ml = 0;
	int dv = 1;
	
	if (m_tate)
	{
		ml = m_printPos.y;
		dv = m_size.cy - m_boxSize.cy;
	}
	else
	{
		ml = m_printPos.x;
		dv = m_size.cx - m_boxSize.cx;
	}
	if (dv<1) dv = 1;
	
	m_pos = (ml * (m_max - m_min + 1)) / dv;
	AdjustInScroll();
}


BOOL CMyScrollBar::CheckOnBox(POINT pt)
{
	POINT pt2 = GetBoxZahyo();
	int dx = pt.x - pt2.x;
	int dy = pt.y - pt2.y;
	if ((dx>=0) && (dx<m_boxSize.cx) && (dy>=0) && (dy<m_boxSize.cy)) return TRUE;
	return FALSE;
}


int CMyScrollBar::CheckOnBar(POINT pt)
{
	int dx = pt.x - m_zahyo.x;
	int dy = pt.y - m_zahyo.y;
	if ((dx<0) || (dx>=m_size.cx) || (dy<0) || (dy>=m_size.cy)) return -1;

	if (m_tate)
	{
		if (dy<m_printPos.y) return 0;
		if (dy>=(m_printPos.y+m_boxSize.cy)) return 1;
	}
	else
	{
		if (dx<m_printPos.x) return 0;
		if (dx>=(m_printPos.x+m_boxSize.cx)) return 1;
	}

	return -1;
}

POINT CMyScrollBar::GetBoxZahyo(void)
{
	POINT pt = m_zahyo;

	pt.x += m_printPos.x;
	pt.y += m_printPos.y;

	return pt;
}

void CMyScrollBar::AdjustInScroll(void)
{
	if (m_pos<m_min) m_pos = m_min;
	if (m_pos>m_max) m_pos = m_max;
}


/*_*/




