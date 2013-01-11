//
// floatingLayer.cpp
//

#include <windows.h>
#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"



#include "taihi.h"
//#include "namelist.h"
#include "setupList.h"
#include "floatinglayer.h"

CFloatingLayer::CFloatingLayer(CTaihi* lpTaihi, int layerNumber ,int layerKosuu)
{
	m_taihi = lpTaihi;
	m_layerNumber = layerNumber;
	m_layerKosuu = layerKosuu;

	m_pSizeX = NULL;
	m_pSizeY = NULL;
	if (m_layerKosuu != 0)
	{
		m_pSizeX = new int[m_layerKosuu];
		m_pSizeY = new int[m_layerKosuu];
	}

	m_setup = NULL;
}

CFloatingLayer::~CFloatingLayer()
{
	End();
}

void CFloatingLayer::End(void)
{
	DELETEARRAY(m_pSizeX);
	DELETEARRAY(m_pSizeY);

	ENDDELETECLASS(m_setup);
}


BOOL CFloatingLayer::GetInitGameParam(int* lpVar, LPSTR name)
{
	if (m_setup == NULL) return FALSE;
	return m_setup->GetInitGameParam(lpVar,name);

//	int rNum = m_setup->SearchName2(name);
//	if (rNum == -1) return FALSE;
//
//	*lpVar = atoi(m_setup->GetName(rNum + 1));
//
//	return TRUE;
}


BOOL CFloatingLayer::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	if (m_setup == NULL) return FALSE;

	return m_setup->GetInitGameString(lpStr,name);
//	int rNum = m_setup->SearchName2(name);
//	if (rNum == -1) return FALSE;
//
//	*lpStr = m_setup->GetName(rNum + 1);
//
//	return TRUE;
}


BOOL CFloatingLayer::LoadSetupFile(LPSTR filenameonly, int varKosuu)
{
	if (m_setup == NULL)
	{
//		m_setup = new CNameList(varKosuu * 2);
		m_setup = new CSetupList();
	}

	if (m_setup == NULL) return FALSE;
	return m_setup->LoadSetupFile(filenameonly,varKosuu);
}


void CFloatingLayer::Taihi(int x, int y, int subNumber)
{
	m_taihi->Taihi(m_layerNumber+subNumber,x,y);
}


void CFloatingLayer::ChangeLayerKosuu(int kosuu)
{
	DELETEARRAY(m_pSizeX);
	DELETEARRAY(m_pSizeY);
	m_layerKosuu = kosuu;
	m_pSizeX = new int[m_layerKosuu];
	m_pSizeY = new int[m_layerKosuu];
}

void CFloatingLayer::CreateLayer(int sizeX, int sizeY, int subNumber)
{
	m_taihi->CreateBuffer(m_layerNumber+subNumber,sizeX,sizeY);
	m_pSizeX[subNumber] = sizeX;
	m_pSizeY[subNumber] = sizeY;
}
