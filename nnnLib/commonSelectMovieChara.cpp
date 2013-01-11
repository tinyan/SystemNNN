//
// commonSelectMovieChara.cpp
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
#include "commonSelectMovieChara.h"



CCommonSelectMovieChara::CCommonSelectMovieChara(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTMOVIECHARA_MODE);
	//m_classNumber = SELECTMOVIECHARA_MODE;

	LoadSetupFile("SelectMovieChara",16);

//	GetModeNumberBySetup("nextMode",&m_nextMode);
}



CCommonSelectMovieChara::~CCommonSelectMovieChara()
{
	End();
}

void CCommonSelectMovieChara::End(void)
{
}



int CCommonSelectMovieChara::Init(void)
{
	return -1;
}

int CCommonSelectMovieChara::Calcu(void)
{
	return -1;
	return m_nextMode;
}

int CCommonSelectMovieChara::Print(void)
{
//	CAreaControl::SetNextAllPrint();
//	CAllGraphics::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
//	CPicture::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
	return -1;
}




/*_*/


