//
// commonSelectMovie.cpp
//


#include <windows.h>



#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\namelist.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonSelectMovie.h"



CCommonSelectMovie::CCommonSelectMovie(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTMOVIE_MODE);
	m_classNumber = SELECTMOVIE_MODE;

	LoadSetupFile("SelectMovie",16);

//	GetModeNumberBySetup("nextMode",&m_nextMode);
}



CCommonSelectMovie::~CCommonSelectMovie()
{
	End();
}

void CCommonSelectMovie::End(void)
{
}



int CCommonSelectMovie::Init(void)
{
	return -1;
}

int CCommonSelectMovie::Calcu(void)
{
	return -1;
	return m_nextMode;
}

int CCommonSelectMovie::Print(void)
{
//	CAreaControl::SetNextAllPrint();
//	CAllGraphics::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
//	CPicture::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
	return -1;
}




/*_*/


