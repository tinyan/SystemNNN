//
// commonnothing.cpp
//


#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"
#include "..\nyanlib\include\allGeo.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"
#include "..\nnnUtilLib\inputStatus.h"
#include "..\nnnUtilLib\mymessage.h"

#include "..\nnnUtilLib\namelist.h"
#include "..\nnnUtilLib\softKey.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonKanjiInput.h"



CCommonKanjiInput::CCommonKanjiInput(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(KANJIINPUT_MODE);

	LoadSetupFile("kanjiInput",256);

	m_message = m_game->GetMyMessage();
	m_softKey = new CSoftKey(m_message);

	GetInitGameString(&m_filenameBG,"filenameBG");
	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;

	m_targetNumber = 0;
	m_targetType = 0;



	CreateBackButton();
	GetDisableQuickButtonSetup();
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();

}



CCommonKanjiInput::~CCommonKanjiInput()
{
	End();
}

void CCommonKanjiInput::End(void)
{
	ENDDELETECLASS(m_softKey);
}

void CCommonKanjiInput::StartUserCommand(int paraKosuu,int* paraPtr)
{
	m_targetNumber = 0;
	m_targetType = 0;
	if (paraKosuu > 0)
	{
		m_targetNumber = paraPtr[0];
	}
	if (paraKosuu > 1)
	{
		m_targetType = paraPtr[1];
	}


}



int CCommonKanjiInput::Init(void)
{
	m_softKey->Init();

	return -1;
}

int CCommonKanjiInput::Calcu(void)
{
	if (m_mouseStatus->CheckClick(1))
	{
		return ReturnFadeOut(-1);
	}

	int softKey = m_softKey->Calcu(m_inputStatus);
	if (softKey >= 0)
	{

		if (softKey > 0)
		{
			LPSTR text = m_softKey->GetKakuteiText();

			if (m_targetType == 0)
			{
				m_game->SetOkikaeMessage(m_targetNumber,text);
				return ReturnFadeOut(-1);
			}
			else if (m_targetType == 1)
			{
				m_game->SetSystemOkikaeMessage(m_targetNumber,text);
				return ReturnFadeOut(-1);
			}
			else
			{
				//name input?
			}
		}
	}


	return -1;
}

int CCommonKanjiInput::Print(void)
{
	CAreaControl::SetNextAllPrint();
	CAllGraphics::FillScreen();
	m_message->PrintMessage(100,100,"漢字入力画面");

	m_softKey->Print();

	if (1)
	{
		int x = 300;
		int y = 50;

		int ln = m_softKey->GetKakuteiLength();
		LPSTR kakuteiText = m_softKey->GetKakuteiText();
		if (ln > 0)
		{
			m_message->PrintMessage(x,y,kakuteiText);
		}
		x += 16*ln;


		ln = m_softKey->GetHenkanLength();
		LPSTR henkanText = m_softKey->GetHenkanText();
		if (ln > 0)
		{
			m_message->PrintMessage(x,y,henkanText);
			CAllGeo::TransBoxFill(x,y,ln*16,16,0,0,255,50);
		}
		x += 16*ln;


		ln = m_softKey->GetInputLength();
		LPSTR inputText = m_softKey->GetInputText();
		if (ln > 0)
		{
			m_message->PrintMessage(x,y,inputText);
			CAllGeo::TransBoxFill(x,y,ln*16,16,0,255,0,50);
		}
	}
	
	

	if (1)
	{
		int x = 100;
		int y = 400;

		m_message->PrintMessage(x,y,"デバッグ情報");
		y += 50;

		m_message->PrintMessage(x,y,"確定文字列：");
		int ln = m_softKey->GetKakuteiLength();
		LPSTR kakuteiText = m_softKey->GetKakuteiText();
		if (ln > 0)
		{
			m_message->PrintMessage(x+16*6,y,kakuteiText);
		}
		y += 30;


		m_message->PrintMessage(x,y,"変換文字列：");
		ln = m_softKey->GetHenkanLength();
		LPSTR henkanText = m_softKey->GetHenkanText();
		if (ln > 0)
		{
			m_message->PrintMessage(x+16*6,y,henkanText);
			CAllGeo::TransBoxFill(x+16*6,y,ln*16,16,0,0,255,50);
		}
		y += 30;


		m_message->PrintMessage(x,y,"入力文字列：");
		ln = m_softKey->GetInputLength();
		LPSTR inputText = m_softKey->GetInputText();
		if (ln > 0)
		{
			m_message->PrintMessage(x+16*6,y,inputText);
			CAllGeo::TransBoxFill(x+16*6,y,ln*16,16,0,255,0,50);
		}
		y += 30;


	}

	return -1;
}

void CCommonKanjiInput::FinalExitRoutine(void)
{
	m_game->ClearFontCache();

	m_game->SetYoyaku();

}

/*_*/


