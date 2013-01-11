//
// commonselectZukan.cpp
//


#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"
#include "..\nnnUtilLib\inputStatus.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonBackButton.h"

#include "..\nnnUtilLib\namelist.h"

#include "..\nnnUtilLib\commonAnimeParts.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonSelectZukan.h"


char CCommonSelectZukan::m_defaultAppearVarName[] = "ê}ä”å©ÇΩÉtÉâÉO";
char CCommonSelectZukan::m_defaultReturnVarName[] = "ê}ä”î‘çÜ";

char CCommonSelectZukan::m_defaultFunctionName[] = "zukanon";


CCommonSelectZukan::CCommonSelectZukan(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTZUKAN_MODE);
	LoadSetupFile("selectzukan",16);

	GetBackExecSetup();
	GetAllPrintSetup();
	GetBGMSetup();

	//get seat file name
	GetInitGameString(&m_filenameSeat,"filenameSeat");

	m_printX = 0;
	m_printY = 0;
	GetInitGameParam(&m_printX,"zukanPrintX");
	GetInitGameParam(&m_printY,"zukanPrintY");
	m_sizeX = 16;
	m_sizeY = 16;
	GetInitGameParam(&m_sizeX,"zukanSizeX");
	GetInitGameParam(&m_sizeY,"zukanSizeY");
	m_nextX = m_sizeX;
	m_nextY = m_sizeY;
	GetInitGameParam(&m_nextX,"zukanNextX");
	GetInitGameParam(&m_nextY,"zukanNextY");
	m_kosuuX = 5;
	m_kosuuY = 4;
	GetInitGameParam(&m_kosuuX,"zukanNumberX");
	GetInitGameParam(&m_kosuuY,"zukanNumberY");

	m_picKosuuX = m_kosuuX;
	m_picKosuuY = m_kosuuY;


	m_zukanKosuu = 1;
	GetInitGameParam(&m_zukanKosuu,"zukanNumber");

	int blocks = (m_zukanKosuu + 29) / 30;
	m_blocks = blocks;
	m_flag = new int[blocks];
	m_appearVarNumber = new int[blocks];


	for (int i=0;i<blocks;i++)
	{
		LPSTR varname = m_defaultAppearVarName;

		if (i == 0)
		{
			GetInitGameString(&varname,"appearVarName");
		}

		char name[256];
		sprintf_s(name,sizeof(name),"appearVarName%d",i+1);
		GetInitGameString(&varname,name);
		m_appearVarNumber[i] = m_game->GetVarNumber(varname);
	}




	if (1)
	{
		LPSTR varname = m_defaultReturnVarName;
		GetInitGameString(&varname,"returnVarName");
		m_returnVarNumber = m_game->GetVarNumber(varname);
	}


	m_animeCursor = new CCommonAnimeParts("zukanCursor",m_setup);


	int bt = 1;
	for (int i=0;i<31;i++)
	{
		m_bitPattern[i] = bt;
		bt <<= 1;
	}
	m_bitPattern[31] = 0x80000000;



	CreateBackButton();
	LPSTR functionName = m_defaultFunctionName;
	GetInitGameString(&functionName,"functionName");
	m_game->RegistUserFunction(SELECTZUKAN_MODE,"zukanon");


	m_exitFadeOutSpecialMode = OMAKE_MODE;
	m_createExitScreenFlagSpecial = 1;
	GetFadeInOutSetup();
}



CCommonSelectZukan::~CCommonSelectZukan()
{
	End();
}

void CCommonSelectZukan::End(void)
{
	DELETEARRAY(m_flag);
	DELETEARRAY(m_appearVarNumber);
	ENDDELETECLASS(m_animeCursor);
}


void CCommonSelectZukan::BeforeInit(void)
{
	m_zukanNumber = -1;
	SetReturnVar();
	m_game->RestartBackScript();
}


int CCommonSelectZukan::Init(void)
{
	char filename[1024];
	sprintf_s(filename,sizeof(filename),"sys\\%s",m_filenameSeat);
	m_commonParts->LoadDWQ(filename);

	SIZE sz = m_commonParts->GetPicSize();
	m_picKosuuX = sz.cx / m_sizeX;
	m_picKosuuY = sz.cy / m_sizeY;


	//flag
	for (int i=0;i<m_blocks;i++)
	{
		m_flag[i] = 0;
		if (m_appearVarNumber[i] != -1)
		{
			m_flag[i] = m_game->GetVarData(m_appearVarNumber[i]);
		}
	}

	LoadBackButtonPic();
	SetBackButtonZahyo();

	m_back->Init();
	m_animeCursor->Init();

	m_onNumber = -1;
	m_old = -1;

	return -1;
}

int CCommonSelectZukan::Calcu(void)
{
	if (m_zukanNumber == -1)
	{
		int rt = m_back->Calcu(m_inputStatus);
		if (rt != -1)
		{
			int nm = ProcessButtonGroup(rt);
			if (nm >= 0)
			{

				m_game->FuqueAllEffectYoyaku();

				return ReturnFadeOut(m_backMode);
			}
		}


		POINT pt = m_mouseStatus->GetZahyo();
		m_onNumber = GetOnNumber(pt);
		if (m_onNumber != -1)
		{
			if (m_old == -1)
			{
				m_animeCursor->Init();
			}
		}
		m_old = m_onNumber;

		if (m_mouseStatus->CheckClick())
		{
			if (m_onNumber != -1)
			{
				if (CheckSelectOk(m_onNumber))
				{
					m_back->Init();

					m_zukanNumber = m_onNumber;
					SetReturnVar();
					
					//get screen
					m_game->Erase();
					m_game->GetGetScreen();

					m_game->RestartBackScript();
					m_game->CalcuBackScript();
					return -1;
				}
			}
		}

		return -1;
	}



	//dummy
	m_back->Calcu(NULL);
	BOOL flg = FALSE;
	if (m_mouseStatus->CheckClick(0)) flg = TRUE;
	if (m_mouseStatus->CheckClick(1)) flg = TRUE;
	if (m_mouseStatus->CheckClick(2)) flg = TRUE;

	if (flg)
	{
		m_old = -1;
		m_zukanNumber = -1;
		SetReturnVar();
		m_onNumber = -1;
					
		m_game->RestartBackScript();
		m_game->CalcuBackScript();

		return -1;
	}


	return -1;

	return m_nextMode;
}

int CCommonSelectZukan::Print(void)
{
	CAreaControl::SetNextAllPrint();
	PrintBackScriptOrBG();

	if (m_zukanNumber == -1)
	{
		//seat
		for (int i=0;i<m_zukanKosuu;i++)
		{
			if (CheckSelectOk(i))
			{
				POINT pt = GetPrintZahyo(i);
				POINT pt2 = GetPicSrc(i);

				m_commonParts->Blt(pt.x,pt.y,pt2.x,pt2.y,m_sizeX,m_sizeY,TRUE);
			}
		}

		//cursor
		if (m_onNumber != -1)
		{
			POINT pt = GetPrintZahyo(m_onNumber);
			m_animeCursor->Print(pt);
			m_animeCursor->Calcu();
		}



		m_back->Print();
	}

//	CAreaControl::SetNextAllPrint();
//	CAllGraphics::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
//	CPicture::FillScreen(m_fillColorR,m_fillColorG,m_fillColorB);
	return 0;
}

POINT CCommonSelectZukan::GetPrintZahyo(int n)
{
	POINT pt;
	int nx = n % m_kosuuX;
	int ny = n / m_kosuuX;

	pt.x = m_printX + nx * m_nextX;
	pt.y = m_printY + ny * m_nextY;

	return pt;
}

POINT CCommonSelectZukan::GetPicSrc(int n)
{
	POINT pt;
	int nx = n % m_picKosuuX;
	int ny = n / m_picKosuuX;

	pt.x = nx * m_sizeX;
	pt.y = ny * m_sizeY;

	return pt;
}




int CCommonSelectZukan::GetOnNumber(POINT pt)
{
	int dx = pt.x - m_printX;
	int dy = pt.y - m_printY;
	if ((dx<0) || (dy<0)) return -1;
	int nx = dx / m_nextX;
	int ax = dx % m_nextX;
	if ((nx >= m_kosuuX) || (ax >= m_sizeX)) return -1;

	int ny = dy / m_nextY;
	int ay = dy % m_nextY;
	if ((ny >= m_kosuuY) || (ay >= m_sizeY)) return -1;

	int n = nx + ny * m_kosuuX;
	if ((n<0) || (n>=m_zukanKosuu)) return -1;

	if (CheckSelectOk(n)) return n;

	return -1;
}


BOOL CCommonSelectZukan::CheckSelectOk(int n)
{
	int blocks = n / 30;
	int bt = n % 30;
	if ((blocks < 0) || (blocks > m_blocks)) return FALSE;

	if (m_bitPattern[bt] & m_flag[blocks]) return TRUE;

	return FALSE;
}

void CCommonSelectZukan::SetReturnVar(void)
{
	if (m_returnVarNumber != -1)
	{
		m_game->SetVarData(m_returnVarNumber,m_zukanNumber+1);

	}
}

void CCommonSelectZukan::Function(int type,int paraKosuu,int* lpParam)
{
	int nm = *lpParam;
	int blocks = (nm-1) / 30;
	int bt = (nm - 1) % 30;

	if ((blocks >= 0) && (blocks < m_blocks))
	{
		if (m_appearVarNumber[blocks] != -1)
		{
			int d = m_game->GetVarData(m_appearVarNumber[blocks]);
			d |= m_bitPattern[bt];
			m_game->SetVarData(m_appearVarNumber[blocks],d);
		}
	}
}



/*_*/


