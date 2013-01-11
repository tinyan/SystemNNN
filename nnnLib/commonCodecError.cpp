//
// commonCodecError.cpp
//


#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"

#include "..\nnnUtilLib\inputStatus.h"

#include "..\nnnUtilLib\superButtonPicture.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\menuButtonGroup.h"
#include "..\nnnUtilLib\menuButtonSetup.h"

#include "..\nnnUtilLib\commonButtonGroup.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonCodecError.h"


char CCommonCodecError::m_defaultFileNameBG[] = "CodecError";


char CCommonCodecError::m_defaultFileNameDialog[] = "ta_dialog5";
//char CCommonCodecError::m_defaultFileNameButton[] = "ta_dialog_bt2";
char CCommonCodecError::m_buttonName[][16] = 
{
	"notButton","canButton","exitButton",
};


CCommonCodecError::CCommonCodecError(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(CODECERROR_MODE);
//	m_classNumber = CODECERROR_MODE;
	LoadSetupFile("CodecError",32);


	m_nextMode = LOGO_MODE;
	GetModeNumberBySetup("nextMode",&m_nextMode);

	GetBackExecSetup();
	GetAllPrintSetup();

	m_filenameBG = m_defaultFileNameBG;
	m_filenameDialog = m_defaultFileNameDialog;

	GetInitGameString(&m_filenameBG,"filenameBG");
	GetInitGameString(&m_filenameDialog,"filenameDialog");

	m_dialogFlag = 1;
	GetInitGameParam(&m_dialogFlag,"dialogFlag");



	CPicture* lpBG = m_commonBG;
	if (m_backScriptFlag) lpBG = NULL;

	char* buttonName[3];
	int i = 0;
	for (i=0;i<3;i++)
	{
		buttonName[i] = m_buttonName[i];
	}
	m_dialogButtonGroup = new CCommonButtonGroup(m_setup,3,lpBG,NULL,buttonName);

	for (i=0;i<3;i++)
	{
		m_dialogButtonGroup->SetPicture(i,CSuperButtonPicture::GetPicture(3+i));
	}

	m_dialogX = -999;
	m_dialogY = -999;

	GetInitGameParam(&m_dialogX,"dialogPrintX");
	GetInitGameParam(&m_dialogY,"dialogPrintY");


	GetFadeInOutSetup();

	GetEnterExitVoiceFileName();
	GetDialogVoiceFileName();
}


CCommonCodecError::~CCommonCodecError()
{
	End();
}

void CCommonCodecError::End(void)
{
	ENDDELETECLASS(m_dialogButtonGroup);
}



int CCommonCodecError::Init(void)
{
	char filename[256];

	if (m_dialogFlag)
	{
		wsprintf(filename,"sys\\%s",m_filenameDialog);
		m_commonParts->LoadDWQ(filename);
		if (m_dialogX == -999)
		{
			SIZE sz = m_commonParts->GetPicSize();
			int screenSizeX = CMyGraphics::GetScreenSizeX();
			int screenSizeY = CMyGraphics::GetScreenSizeY();
			m_dialogX = (screenSizeX - sz.cx) / 2;
			m_dialogY = (screenSizeY - sz.cy) / 2;
		}
	}

	if (m_backScriptFlag)
	{
	}
	else
	{
		wsprintf(filename,"sys\\%s",m_filenameBG);
		m_commonBG->LoadDWQ(filename);
		m_commonBG->Put(0,0,FALSE);
		if (m_dialogFlag)
		{
			m_commonParts->Put(m_dialogX,m_dialogY,TRUE);
		}
		m_commonBG->GetScreen();
	}

	for (int i=0;i<3;i++)
	{
		CPicture* lpPic = m_dialogButtonGroup->GetPicture(i);
		LPSTR name = m_dialogButtonGroup->GetFileName(i);
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}

	m_codecError = m_game->CheckCodec();
	if (m_codecError == 0)
	{
		m_dialogButtonGroup->SetEnable(1,FALSE);
	}

	m_dialogButtonGroup->Init();

	return -1;
}


int CCommonCodecError::Calcu(void)
{
	int rt = m_dialogButtonGroup->Calcu(m_inputStatus);
	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessButtonGroup(rt);
		if (nm >= 0)
		{
			if (nm == 0)		//Ä¶‚µ‚È‚¢
			{
				m_game->SetCodecErrorRunMode(0);
				m_game->SetSkipMovie();
				//
				return ReturnFadeOut(m_nextMode);
			}
			else if (nm == 1)	//‰Â”\‚È•”•ª‚Ì‚ÝÄ¶‚ðŽŽ‚Ý‚é
			{
				m_game->SetCodecErrorRunMode(1);
				//
				return ReturnFadeOut(m_nextMode);
			}
			else if (nm == 2)	//ƒQ[ƒ€‚ðI—¹‚·‚é
			{
				m_game->PostCloseMessage();
				return -1;
			}
		}
	}


	return -1;
}

int CCommonCodecError::Print(void)
{
	BOOL b = CAreaControl::CheckAllPrintMode();
	PrintBackScriptOrBG();

	if (m_backScriptFlag)
	{
		if (m_dialogFlag)
		{
			m_commonParts->Put(m_dialogX,m_dialogY,TRUE);
		}
	}

	m_dialogButtonGroup->Print(TRUE);

	return -1;
}

