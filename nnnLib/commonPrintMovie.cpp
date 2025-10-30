//
// commonPrintMovie.cpp
//


#include <windows.h>
//#include <dshow.h>
//#include <qedit.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nyanLib\include\myFile.h"

#if !defined _TINYAN3DLIB_
#include "..\nyanDirectXLib\myDirectShow.h"
#else
#include "..\nyanDirectXLib\myDirectShow.h"
//#include "..\..\systemNNN3D\nyanDirectX3DLib\myDirectShow.h"
#endif

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\namelist.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonPrintMovie.h"


char CCommonPrintMovie::m_defaultFileNameBG[] = "bg_movie";
char CCommonPrintMovie::m_defaultMovieFileName[] = "default.wmv";

char CCommonPrintMovie::m_defaultSelectMovieVarName[] = "ƒ€[ƒr[”Ô†";

CCommonPrintMovie::CCommonPrintMovie(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(PRINTMOVIE_MODE);
//	m_classNumber = PRINTMOVIE_MODE;

	LoadSetupFile("PrintMovie",64);

	m_filenameBG = m_defaultFileNameBG;
	GetInitGameString(&m_filenameBG,"filenameBG");

	m_nextMode = TITLE_MODE;
	GetModeNumberBySetup("nextMode",&m_nextMode);

	m_movieFileName = m_defaultMovieFileName;
	GetInitGameString(&m_movieFileName,"movieFileName");

	m_codecCheckFileName = m_movieFileName;
	GetInitGameString(&m_codecCheckFileName,"codecCheckFileName");

	m_noSkipFlag = 0;
	GetInitGameParam(&m_noSkipFlag,"noSKipFlag");

	SIZE sz = m_game->GetRealWindowSize();
	int fixedMovieSizeX = sz.cx;
	int fixedMovieSizeY = sz.cy;
	if (GetInitGameParam(&fixedMovieSizeX,"fixedMovieSizeX"))
	{
		if (GetInitGameParam(&fixedMovieSizeY,"fixedMovieSizeY"))
		{
			CMyDirectShow::SetFixedMovieSize(fixedMovieSizeX,fixedMovieSizeY);
		}
	}

	m_selectMovieByVarFlag = 0;
	m_selectMovieVarNumber = -1;
	GetInitGameParam(&m_selectMovieByVarFlag,"selectByVarFlag");
	if (m_selectMovieByVarFlag)
	{
		LPSTR varname = m_defaultSelectMovieVarName;
		GetInitGameString(&varname,"selectMovieVarName");

		m_selectMovieVarNumber = m_game->GetVarNumber(varname);
	}

	m_lastWait = 5;
	GetInitGameParam(&m_lastWait,"lastWait");

	m_directShow = m_game->GetMyDirectShow();

	m_selectMovieFlag = FALSE;
	m_codecError = 0;

	m_scriptMovieFlag = FALSE;
	m_dontSaiseiFlag = FALSE;

	m_directMovieFlag = false;

	int mustFlagOn = 0;
	GetInitGameParam(&mustFlagOn, "mustOpeningMovieFlagOn");
	if (mustFlagOn > 0)
	{
		m_game->SetGetMovie(0, mustFlagOn);
	}


	m_fillExitScreenFlag = 1;
	GetInitGameParam(&m_fillExitScreenFlag,"fillExitScreenFlag");
	GetInitGameParam(&m_exitFadeOutColorR,"exitFadeOutColorR");
	GetInitGameParam(&m_exitFadeOutColorG,"exitFadeOutColorG");
	GetInitGameParam(&m_exitFadeOutColorB,"exitFadeOutColorB");

	GetInitGameParam(&m_createExitScreenFlag,"createExitScreenFlag");
}



CCommonPrintMovie::~CCommonPrintMovie()
{
	End();
}

void CCommonPrintMovie::End(void)
{

}



int CCommonPrintMovie::Init(void)
{
	m_firstFrame = TRUE;



	m_dontSaiseiFlag = FALSE;
	m_autoDebugWait = m_game->GetAutoDebugWait();

	if (m_game->CheckSkipMovie())
	{
		return -1;
	}


	m_codecError = m_game->CheckCodec();

	m_game->StopMusic();
	m_exitFlag = FALSE;

	if (1)
	{
		m_game->StopScriptSoundAndVoice();
	}

	CAllGraphics::FillScreen();
	m_game->EndMovie();


	if (m_codecError < 3)
	{
		char filename[256];
		wsprintf(filename,"sys\\%s",m_filenameBG);
		m_commonBG->LoadDWQ(filename);

		return -1;
	}

//	if (m_game->GetCodecErrorRunMode() != 0)
	if (1)
	{
		char filename[1024];
		if (m_directMovieFlag)
		{
			if (m_directMovieNumber == 0)
			{
				wsprintf(filename, "movie\\%s", m_movieFileName);
			}
			else
			{
				LPSTR fname = m_game->GetMovieName(m_directMovieNumber);
				wsprintf(filename, "movie\\%s",fname);
			}
		}
		else
		{
			if (m_selectMovieFlag)
			{
				wsprintf(filename, "movie\\%s", m_selectMovieFileName);
				m_selectMovieFlag = FALSE;
			}
			else
			{
				LPSTR name = m_movieFileName;

				if (m_selectMovieByVarFlag != 0)
				{
					if (m_selectMovieVarNumber != -1)
					{
						int vn = m_game->GetVarData(m_selectMovieVarNumber);

						if (m_selectMovieByVarFlag == -1)
						{
							if (vn == 0)
							{
								//dont Ä¶
								m_dontSaiseiFlag = TRUE;
								return -1;
							}
						}


						if (vn > 0)
						{
							name = m_game->GetMovieName(vn);
							if (name == NULL)
							{
								name = m_movieFileName;
							}
						}
					}
				}

				wsprintf(filename, "movie\\%s", name);
			}
		}

	//	m_directShow->SetWindowMode(m_game->GetSystemParam(NNNPARAM_SCREENMODE));
	//	m_directShow->PlayMovie("movie\\ˆÅ‚ÌºˆÙ•·˜^_0614 OP ‚‰æŽ¿”Å.mpg");
		
		if (m_game->GetSystemParam(NNNPARAM_MOVIESWITCH))
		{
//			char volmes[256];
//			wsprintf(volmes,"%d",m_game->GetSystemParam(NNNPARAM_MOVIEVOLUME));
//MessageBox(NULL,volmes,"vol",MB_OK);
			m_directShow->ChangeVolume(m_game->GetSystemParam(NNNPARAM_MOVIEVOLUME));
		}
		else
		{
//MessageBox(NULL,"0","vol",MB_OK);
			m_directShow->ChangeVolume(0);
		}

		m_game->SetMovieEnable(TRUE);
		m_directShow->PlayMovie(filename);
	}

	return -1;
}


int CCommonPrintMovie::Calcu(void)
{
	if ((m_game->CheckSkipMovie()) || m_dontSaiseiFlag)
	{
		m_game->EraseCursor();
		CAllGraphics::FillScreen();

		if (m_fillExitScreenFlag)
		{
			FillExitScreen();
		}
		m_game->EndMovie();

		if (m_scriptMovieFlag)
		{
			m_game->SetYoyaku();
			m_scriptMovieFlag = FALSE;
			return -1;
		}

		if (m_directMovieFlag)
		{
			return m_backMode;
		}
		return m_nextMode;
	}

	BOOL b = FALSE;

	if (m_codecError < 3)
	{
		if (m_scriptMovieFlag)
		{
			m_game->EraseCursor();

			if (m_fillExitScreenFlag)
			{
				FillExitScreen();
			}

			m_game->SetYoyaku();
			m_scriptMovieFlag = FALSE;
			return -1;
		}
	}

	if (m_exitFlag)
	{
		m_lastCount--;
		if (m_lastCount > 0) return -1;


		if (m_fillExitScreenFlag)
		{
			FillExitScreen();
		}

		if (m_scriptMovieFlag == FALSE)
		{
			if (m_directMovieFlag)
			{
				return m_backMode;
			}
			return m_nextMode;
		}
		
		m_game->SetYoyaku();
		m_scriptMovieFlag = FALSE;

	}


	if (m_directShow->CheckComplete())
	{
		b = TRUE;
//OutputDebugString("[DS:COMP]");
	}

	if (m_noSkipFlag == 0)
	{
		if (CheckClick(0) || CheckClick(1))
		{
			b = TRUE;
//OutputDebugString("[CLICKED]");
		}
	}

	if (m_game->GetAutoDebugMode())
	{
		m_autoDebugWait--;
		if (m_autoDebugWait <= 0)
		{
			b = TRUE;
		}
	}

	if (m_game->GetCodecErrorRunMode() == 0)
	{
///		return m_nextMode;
	}



	if (b)
	{
		m_game->SetMovieEnable(FALSE);
		m_directShow->StopMovie();
	//	m_game->EraseCursor();

		if (m_fillExitScreenFlag)
		{
			FillExitScreen();
		}
		m_game->EraseCursor();
		CAllGraphics::FillScreen();
		m_game->EndMovie();

		m_lastCount = m_lastWait;
		m_exitFlag = TRUE;

		return -1;
	}
	else
	{
static int aaa = 0;
aaa++;
aaa %= 100;
if (aaa == 0)
{
#if defined _TINYAN3DLIB_
///	m_directShow->ToTop();
#endif
}
	}
//OutputDebugString("+");
	return -1;
	return m_nextMode;
}

int CCommonPrintMovie::Print(void)
{



	m_firstFrame = FALSE;

	if (m_game->CheckSkipMovie())
	{
		return -1;
	}

	if (m_dontSaiseiFlag) return -1;


	if (m_codecError < 3)
	{
		if (CAreaControl::CheckAllPrintMode())
		{
			m_commonBG->Put(0,0,FALSE);
		}
	}

	if (m_game->GetCodecErrorRunMode() == 0)
	{
		return -1;
	}


	//movie

	return -1;
}

void CCommonPrintMovie::StartUserCommand(int paraKosuu,int* paraPtr)
{
	int movieNumber = 1;
	if (paraKosuu >= 1)
	{
		movieNumber = *paraPtr;
	}
	m_game->SetGetMovie(0, movieNumber);
	LPSTR filename = m_game->GetMovieName(movieNumber);
	SetMovie(filename);
	m_scriptMovieFlag = TRUE;
	m_dontSaiseiFlag = FALSE;
	m_directMovieFlag = false;
}


void CCommonPrintMovie::SetMovie(LPSTR filename)
{
	m_selectMovieFlag = TRUE;
	m_selectMovieFileName = filename;
}

void CCommonPrintMovie::StartByDirect(int movieNumber)
{
	m_directMovieFlag = true;
	m_directMovieNumber = movieNumber;
	m_scriptMovieFlag = FALSE;
	m_dontSaiseiFlag = FALSE;
}


int CCommonPrintMovie::CheckCodec(void)
{
	if (m_directShow == NULL) return 0;

	char filename[1024];
	wsprintf(filename,"movie\\%s",m_codecCheckFileName);

	return m_directShow->CheckCodec(filename);
}

/*_*/


