

#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\areaControl.h"
#include "..\nnnUtilLib\InputStatus.h"
#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"


#include "miniGameBase.h"

#include "miniGameTrumpCommon.h"
#include "miniGameMahjongCommon.h"


#include "miniGamePuzzle9.h"
#include "miniGameChange.h"
#include "miniGameNurie.h"
#include "miniGameCross.h"
#include "miniGameSlide16.h"
#include "miniGameMonte.h"
#include "miniGamePyramid.h"
#include "miniGameGolf.h"

#include "miniGameDevil.h"

#include "miniGameNikaku.h"
#include "miniGameKushi.h"


#include "allMiniGame.h"

char CAllMiniGame::m_commonPicName[][64]=
{
	"trump","mahjong","panel","number","arrow","shogi","go"
};

char CAllMiniGame::m_soundNameTable[][64]=
{
	"click","good","bad","start","clear","gameover"
};

int CAllMiniGame::m_defaultCommonPicSize[]=
{
	96,144,
	16,16,
	16,16,
	16,16,
	16,16,
	16,16,
	16,16,
};


CAllMiniGame::CAllMiniGame(CInputStatus* lpInput,int gameMax)
{
//	m_backButton = NULL;
	m_input = lpInput;
	m_keyStatus = m_input->GetKeyStatus();
	m_mouseStatus = m_input->GetMouseStatus();

	m_commonPicKosuu = 7;
	m_soundKosuu = 6;

	m_miniGameKosuuMax = gameMax;
	m_miniGameKosuu = 0;
	m_miniGameNumber = -1;
	m_miniGame = new CMiniGameBase*[m_miniGameKosuuMax];

	int i = 0;
	for (i=0;i<m_miniGameKosuuMax;i++)
	{
		m_miniGame[i] = NULL;
	}

	for (i=0;i<16;i++)
	{
		m_commonPic[i] = NULL;
		SIZE sz;
		sz.cx = m_defaultCommonPicSize[i*2];
		sz.cy = m_defaultCommonPicSize[i*2+1];
		m_commonPicSize[i] = sz;
		m_picType[i] = 0;
	}
}

CAllMiniGame::~CAllMiniGame()
{
	End();
}

void CAllMiniGame::End(void)
{
	if (m_miniGame != NULL)
	{
		for (int i=0;i<m_miniGameKosuu;i++)
		{
			ENDDELETECLASS(m_miniGame[i]);
		}

		DELETEARRAY(m_miniGame);
	}
}


int CAllMiniGame::Init(void)
{
//	if (m_backButton != NULL)
//	{
//		m_backButton->Init();
//	}

	m_soundNumber = -1;

	if ((m_miniGameNumber < 0) || (m_miniGameNumber >= m_miniGameKosuu)) return -1;

	CMiniGameBase* miniGame = m_miniGame[m_miniGameNumber];
	if (miniGame != NULL)
	{
		return miniGame->GeneralInit();
	}

	return -1;
}

int CAllMiniGame::Calcu(void)
{
	m_soundNumber = -1;

	if ((m_miniGameNumber < 0) || (m_miniGameNumber >= m_miniGameKosuu)) return -1;

	CMiniGameBase* miniGame = m_miniGame[m_miniGameNumber];
	if (miniGame != NULL)
	{
		return miniGame->GeneralCalcu();
	}

	return -1;
}

int CAllMiniGame::Print(void)
{
	int rt = -1;

	if ((m_miniGameNumber >=0) && (m_miniGameNumber < m_miniGameKosuu))
	{
		CMiniGameBase* miniGame = m_miniGame[m_miniGameNumber];
		if (miniGame != NULL)
		{
			rt = miniGame->GeneralPrint();
		}
	}

//	if (m_backButton != NULL)
//	{
//		BOOL b = CAreaControl::CheckAllPrintMode();
//		m_backButton->Print(b);
//	}

	return -1;
}


BOOL CAllMiniGame::AddMiniGame(int n)
{
	if (m_miniGameKosuu >= m_miniGameKosuuMax) return FALSE;
	if (n<0) return FALSE;

	switch (n)
	{
	case 0:
		m_miniGame[m_miniGameKosuu] = new CMiniGamePuzzle9(this);
		break;
	case 1:
		m_miniGame[m_miniGameKosuu] = new CMiniGameChange(this);
		break;
	case 2:
		m_miniGame[m_miniGameKosuu] = new CMiniGameNurie(this);
		break;
	case 3:
		m_miniGame[m_miniGameKosuu] = new CMiniGameCross(this);
		break;
	case 4:
		m_miniGame[m_miniGameKosuu] = new CMiniGameSlide16(this);
		break;
	case 5:
		m_miniGame[m_miniGameKosuu] = new CMiniGameMonte(this);
		break;
	case 6:
		m_miniGame[m_miniGameKosuu] = new CMiniGamePyramid(this);
		break;
	case 7:
		m_miniGame[m_miniGameKosuu] = new CMiniGameGolf(this);
		break;
	case 8:
		m_miniGame[m_miniGameKosuu] = new CMiniGameNikaku(this);
		break;
	case 9:
		m_miniGame[m_miniGameKosuu] = new CMiniGameKushi(this);
		break;
	}
	
	if (m_miniGame[m_miniGameKosuu] == NULL) return FALSE;
	m_miniGameKosuu++;
	return TRUE;
}


BOOL CAllMiniGame::AddMiniGame(CMiniGameBase* lpMiniGame)
{
	if (lpMiniGame == NULL) return FALSE;
	if (m_miniGameKosuu >= m_miniGameKosuuMax) return FALSE;

	m_miniGame[m_miniGameKosuu] = lpMiniGame;
	m_miniGameKosuu++;
	return TRUE;
}


//BOOL CAllMiniGame::CheckExitMiniGame(void)
//{
/*
	if (m_backButton == NULL)
	{
		if (m_mouseStatus->CheckClick(1))
		{
			return TRUE;
		}
	}
	else
	{
		int rt = m_backButton->Calcu(m_input);
		if (rt == NNNBUTTON_NOTHING) return FALSE;

		int st = CCommonButton::GetButtonStatus(rt);
		if (st == NNNBUTTON_NUMBER)
		{
			return TRUE;
		}
	}
*/

//	return FALSE;
//}

BOOL CAllMiniGame::SetPicture(CPicture* lpPic,int n)
{
	if ((n<0) || (n>=3)) return FALSE;
	m_pic[n] = lpPic;
	return TRUE;
}

CPicture* CAllMiniGame::GetPicture(int n)
{
	if ((n<0) || (n>=3)) n = 0;
	return m_pic[n];
}


void CAllMiniGame::PlayClickSound(void)
{
	m_soundNumber = 0;
}

void CAllMiniGame::PlayGoodSound(void)
{
	m_soundNumber = 1;
}

void CAllMiniGame::PlayBadSound(void)
{
	m_soundNumber = 2;
}

void CAllMiniGame::PlayStartSound(void)
{
	m_soundNumber = 3;
}

void CAllMiniGame::PlayClearSound(void)
{
	m_soundNumber = 4;
}

void CAllMiniGame::PlayGameoverSound(void)
{
	m_soundNumber = 5;
}


BOOL CAllMiniGame::CheckClear(void)
{
	if ((m_miniGameNumber < 0) || (m_miniGameNumber >= m_miniGameKosuu)) return FALSE;

	CMiniGameBase* miniGame = m_miniGame[m_miniGameNumber];
	if (miniGame != NULL)
	{
		return miniGame->CheckClear();
	}

	return FALSE;
}

BOOL CAllMiniGame::CheckGameover(void)
{
	if ((m_miniGameNumber < 0) || (m_miniGameNumber >= m_miniGameKosuu)) return FALSE;
	CMiniGameBase* miniGame = m_miniGame[m_miniGameNumber];
	if (miniGame != NULL)
	{
		return miniGame->CheckGameover();
	}

	return FALSE;
}


void CAllMiniGame::SetCommonPic(int n,CPicture* pic)
{
	if ((n<0) || (n>=16)) return;
	m_commonPic[n] = pic;
}

void CAllMiniGame::SetCommonPicSize(int n,SIZE sz)
{
	if ((n<0) || (n>=16)) return;
	m_commonPicSize[n] = sz;
}

CPicture* CAllMiniGame::GetCommonPic(int n)
{
	if ((n<0) || (n>=16)) return NULL;
	return m_commonPic[n];
}

SIZE CAllMiniGame::GetCommonPicSize(int n)
{
	SIZE sz;
	sz.cx = 16;
	sz.cy = 16;
	if ((n>=0) && (n<16))
	{
		sz = m_commonPicSize[n];
	}
	return sz;
}

int CAllMiniGame::GetCommonPicKosuu(void)
{
	return m_commonPicKosuu;
}

LPSTR CAllMiniGame::GetCommonPicName(int n)
{
	return m_commonPicName[n];
}

LPSTR CAllMiniGame::GetSoundName(int n)
{
	if ((n<0) || (n>=16)) return NULL;
	return m_soundNameTable[n];
}


/*_*/
