//
//
//

#include <windows.h>
//#include <stdio.h>
//#include <Math.h>

#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myGraphics.h"

#include "fade.h"
#include "fillScreen.h"
#include "multi.h"
#include "addSub.h"
#include "nega.h"
#include "grey.h"
#include "layerSepia.h"
#include "layerGrey.h"

#include "..\nyanLib\include\allGraphics.h"

CFade* CAllGraphics::m_fade = NULL;
CFillScreen* CAllGraphics::m_fillScreen = NULL;
CMulti* CAllGraphics::m_multi = NULL;
CAddSub* CAllGraphics::m_addSub = NULL;
CGrey* CAllGraphics::m_grey = NULL;
CNega* CAllGraphics::m_nega = NULL;
CLayerSepia* CAllGraphics::m_layerSepia = NULL;
CLayerGrey* CAllGraphics::m_layerGrey = NULL;

CAllGraphics::CAllGraphics()
{
	m_fade = new CFade();
	m_fillScreen = new CFillScreen();
	m_multi = new CMulti();
	m_addSub = new CAddSub();
	m_grey = new CGrey();
	m_nega = new CNega();
	m_layerSepia = new CLayerSepia();
	m_layerGrey = new CLayerGrey();
}


CAllGraphics::~CAllGraphics()
{
}

void CAllGraphics::End(void)
{
	ENDDELETECLASS(m_layerGrey);
	ENDDELETECLASS(m_layerSepia);
	ENDDELETECLASS(m_nega);
	ENDDELETECLASS(m_grey);
	ENDDELETECLASS(m_addSub);
	ENDDELETECLASS(m_multi);
	ENDDELETECLASS(m_fillScreen);
	ENDDELETECLASS(m_fade);
}




void CAllGraphics::Fade(int ps1,int r,int g,int b,int ps2)
{
	if (m_fade == NULL) return;
	m_fade->Print(ps1,r,g,b,ps2);
}

void CAllGraphics::FillScreen(int r,int g, int b)
{
	if (m_fillScreen == NULL) return;
	m_fillScreen->Print(r,g,b);
}

void CAllGraphics::Multi(int percentR,int percentG,int percentB)
{
	if (m_multi == NULL) return;
	m_multi->Print(percentR,percentG,percentB);
}

void CAllGraphics::AddSub(int deltaR,int deltaG,int deltaB)
{
	if (m_addSub == NULL) return;
	m_addSub->Print(deltaR,deltaG,deltaB);
}

void CAllGraphics::Grey(void)
{
	if (m_grey == NULL) return;
	m_grey->Print();
}

void CAllGraphics::Nega(void)
{
	if (m_nega == NULL) return;
	m_nega->Print();
}

void CAllGraphics::MultiClip(int startX,int startY,int sizeX,int sizeY,int percentR,int percentG,int percentB)
{
	if (m_multi == NULL) return;
	m_multi->PrintClip(startX,startY,sizeX,sizeY,percentR,percentG,percentB);
}

void CAllGraphics::AddSubClip(int startX,int startY,int sizeX,int sizeY,int deltaR,int deltaG,int deltaB)
{
	if (m_addSub == NULL) return;
	m_addSub->PrintClip(startX,startY,sizeX,sizeY,deltaR,deltaG,deltaB);
}

void CAllGraphics::GreyClip(int startX,int startY,int sizeX,int sizeY)
{
	if (m_grey == NULL) return;
	m_grey->PrintClip(startX,startY,sizeX,sizeY);
}

void CAllGraphics::NegaClip(int startX,int startY,int sizeX,int sizeY)
{
	if (m_nega == NULL) return;
	m_nega->PrintClip(startX,startY,sizeX,sizeY);
}


void CAllGraphics::LayerGrey(int ps256)
{
	if (m_layerGrey == NULL) return;
	m_layerGrey->Print(ps256);
}

void CAllGraphics::LayerSepia(int ps256,int r,int g,int b)
{
	if (m_layerSepia == NULL) return;
	m_layerSepia->Print(ps256,r,g,b);
}


BOOL CAllGraphics::Clip(int& startX,int& startY,int& sizeX,int& sizeY)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY = CMyGraphics::GetScreenSizeY();
	if (startX >= screenSizeX) return FALSE;
	if (startY >= screenSizeY) return FALSE;
	if ((startX+sizeX) <= 0) return FALSE;
	if ((startY+sizeY) <= 0) return FALSE;

	if (startX<0)
	{
		sizeX += startX;
		startX = 0;
		if (sizeX<=0) return FALSE;
	}

	if (startY<0)
	{
		sizeY += startY;
		startY = 0;
		if (sizeY <= 0) return FALSE;
	}

	if ((startX+sizeX) > screenSizeX)
	{
		sizeX = screenSizeX - startX;
		if (sizeX <= 0) return FALSE;
	}

	if ((startY+sizeY) > screenSizeY)
	{
		sizeY = screenSizeY - startY;
		if (sizeY <= 0) return FALSE;
	}

	return TRUE;
}

/*_*/


