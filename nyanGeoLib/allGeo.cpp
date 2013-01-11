//
//
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"


#include "boxFill.h"
#include "daikei.h"
//#include "fade.h"
//#include "fillScreen.h"
//#include "multi.h"
#include "transBoxFill.h"
#include "transCircleFill.h"
#include "transGradationBoxV.h"
#include "transTorusFill.h"
#include "addCircleFill.h"
#include "addTorusFill.h"
#include "line.h"
#include "addBoxFill.h"

#include "..\nyanLib\include\allGeo.h"

CBoxFill* CAllGeo::m_boxFill = NULL;
CDaikei* CAllGeo::m_daikei = NULL;
//CFade* CAllGeo::m_fade = NULL;
//CFillScreen* CAllGeo::m_fillScreen = NULL;
//CMulti* CAllGeo::m_multi = NULL;
CTransBoxFill* CAllGeo::m_transBoxFill = NULL;
CTransCircleFill* CAllGeo::m_transCircleFill = NULL;
CTransGradationBoxV* CAllGeo::m_transGradationBoxV = NULL;
CTransTorusFill* CAllGeo::m_transTorusFill = NULL;
CAddCircleFill* CAllGeo::m_addCircleFill = NULL;
CAddTorusFill* CAllGeo::m_addTorusFill = NULL;
CLine* CAllGeo::m_line = NULL;
CAddBoxFill* CAllGeo::m_addBoxFill = NULL;


CAllGeo::CAllGeo()
{

	m_boxFill = new CBoxFill();
	m_daikei = new CDaikei();
//	m_fade = new CFade();
//	m_fillScreen = new CFillScreen();
//	m_multi = new CMulti();
	m_transBoxFill = new CTransBoxFill();

	m_transCircleFill = new CTransCircleFill();
//	m_transCircleFill = NULL;

	m_transGradationBoxV = new CTransGradationBoxV();

	m_transTorusFill = new CTransTorusFill();
//	m_transTorusFill = NULL;

	m_addCircleFill = new CAddCircleFill();
	m_addTorusFill = new CAddTorusFill();
	
	m_line = new CLine();
	m_addBoxFill = new CAddBoxFill();


}


CAllGeo::~CAllGeo()
{
	End();
}



void CAllGeo::End(void)
{
//	MessageBox(NULL,"dstrct","allgeo",MB_OK);

	ENDDELETECLASS(m_addBoxFill);
	ENDDELETECLASS(m_line);
	ENDDELETECLASS(m_addTorusFill);
	ENDDELETECLASS(m_addCircleFill);
	ENDDELETECLASS(m_transTorusFill);
	ENDDELETECLASS(m_transGradationBoxV);
	ENDDELETECLASS(m_transCircleFill);
	ENDDELETECLASS(m_transBoxFill);
//	ENDDELETECLASS(m_multi);
//	ENDDELETECLASS(m_fillScreen);
//	ENDDELETECLASS(m_fade);
	ENDDELETECLASS(m_daikei);
	ENDDELETECLASS(m_boxFill);
}

//static method
void CAllGeo::BoxFill(int x,int y,int sizeX,int sizeY,int r,int g,int b)
{
//	static int aaa = 0;
//	aaa++;
//	if (aaa <= 6)
//	{
		//char mes[256];
//		sprintf_s(mes,256,"boxfillobj:%d",(int)m_boxFill);
		//MessageBox(NULL,mes,"boxfill:s",MB_OK);
	//}
	if (m_boxFill == NULL) return;
//	if (aaa <= 6)
//	{
		//MessageBox(NULL,"boxfill:e","allgeo",MB_OK);
	//}

	m_boxFill->Print(x,y,sizeX,sizeY,r,g,b);
}

void CAllGeo::Daikei(POINT leftUpperPoint, int sizeUpperX, POINT leftBottomPoint, int sizeBottomX, int r, int g, int b)
{
	if (m_daikei == NULL) return;
	m_daikei->Print(leftUpperPoint,sizeUpperX,leftBottomPoint,sizeBottomX,r,g,b);
}
/*
void CAllGeo::Fade(int ps1,int r,int g,int b,int ps2)
{
	if (m_fade == NULL) return;
	m_fade->Print(ps1,r,g,b,ps2);
}

void CAllGeo::FillScreen(int r,int g, int b)
{
	if (m_fillScreen == NULL) return;
	m_fillScreen->Print(r,g,b);
}

void CAllGeo::Multi(int percentR,int percentG,int percentB)
{
	if (m_multi == NULL) return;
	m_multi->Print(percentR,percentG,percentB);
}
*/
void CAllGeo::TransBoxFill(int x,int y,int sizeX,int sizeY,int r,int g,int b,int ps)
{
	if (m_transBoxFill == NULL) return;
	m_transBoxFill->Print(x,y,sizeX,sizeY,r,g,b,ps);
}

void CAllGeo::TransCircleFill(int x, int y, int rx, int ry, int r, int g, int b,int ps)
{
	if (m_transCircleFill == NULL) return;
	m_transCircleFill->Print(x,y,rx,ry,r,g,b,ps);
}

void CAllGeo::TransGradationBoxV(POINT leftTop,SIZE size,int r1, int g1, int b1, int r4, int g4, int b4)
{
	if (m_transGradationBoxV == NULL) return;
	m_transGradationBoxV->Print(leftTop,size,r1,g1,b1,r4,g4,b4);
}

void CAllGeo::TransGradationBoxV(POINT leftTop,POINT rightBottom,int r1, int g1, int b1, int r4, int g4, int b4)
{
	if (m_transGradationBoxV == NULL) return;
	m_transGradationBoxV->Print(leftTop,rightBottom,r1,g1,b1,r4,g4,b4);
}

void CAllGeo::TransTorusFill(int x, int y, int rx, int ry, int x2,int y2,int rx2, int ry2,int r, int g, int b,int ps)
{
	if (m_transTorusFill == NULL) return;
	m_transTorusFill->Print(x,y,rx,ry,x2,y2,rx2,ry2,r,g,b,ps);
}

void CAllGeo::AddCircleFill(int x, int y, int rx, int ry, int dr, int dg, int db,int ps)
{
	if (m_addCircleFill == NULL) return;
	m_addCircleFill->Print(x,y,rx,ry,dr,dg,db,ps);
}

void CAllGeo::AddTorusFill(int x, int y, int rx, int ry, int x2,int y2,int rx2, int ry2,int dr, int dg, int db,int ps)
{
	if (m_addTorusFill == NULL) return;
	m_addTorusFill->Print(x,y,rx,ry,x2,y2,rx2,ry2,dr,dg,db,ps);
}

void CAllGeo::Line(int startX,int startY,int endX,int endY, int r,int g,int b,int ps)
{
	if (m_line == NULL) return;
	if (ps == 100)
	{
		m_line->Print(startX,startY,endX,endY,r,g,b);//,ps
	}
	else if (ps > 0)
	{
		m_line->TransPrint(startX,startY,endX,endY,r,g,b,ps);
	}
}


void CAllGeo::LineF(float startX,float startY,float endX,float endY, int r,int g,int b,int ps)
{
	if (m_line == NULL) return;
	if (ps == 100)
	{
		m_line->PrintF(startX,startY,endX,endY,r,g,b,ps);//,ps
	}
	else if (ps > 0)
	{
		m_line->PrintF(startX,startY,endX,endY,r,g,b,ps);
	}
}

void CAllGeo::AddBoxFill(int x,int y,int sizeX,int sizeY,int dr,int dg,int db,int ps)
{
	if (m_addBoxFill == NULL) return;
	m_addBoxFill->Print(x,y,sizeX,sizeY,dr,dg,db,ps);
}
	

/*_*/


