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

	m_fontSize = 24;
	m_printX = 300;
	m_printY = 50;
	GetInitGameParam(&m_fontSize,"fontSize");
	GetInitGameParam(&m_printX,"printX");
	GetInitGameParam(&m_printY,"printY");
	int fontColorR = 255;
	int fontColorG = 255;
	int fontColorB = 255;
	GetInitGameParam(&fontColorR,"fontColorR");
	GetInitGameParam(&fontColorG,"fontColorG");
	GetInitGameParam(&fontColorB,"fontColorB");


	m_kakuteiFontColorR = fontColorR;
	m_kakuteiFontColorG = fontColorG;
	m_kakuteiFontColorB = fontColorB;
	GetInitGameParam(&m_kakuteiFontColorR,"kakuteiFontColorR");
	GetInitGameParam(&m_kakuteiFontColorG,"kakuteiFontColorG");
	GetInitGameParam(&m_kakuteiFontColorB,"kakuteiFontColorB");

	m_henkanFontColorR = fontColorR;
	m_henkanFontColorG = fontColorG;
	m_henkanFontColorB = fontColorB;
	GetInitGameParam(&m_henkanFontColorR,"henkanFontColorR");
	GetInitGameParam(&m_henkanFontColorG,"henkanFontColorG");
	GetInitGameParam(&m_henkanFontColorB,"henkanFontColorB");

	m_inputFontColorR = fontColorR;
	m_inputFontColorG = fontColorG;
	m_inputFontColorB = fontColorB;
	GetInitGameParam(&m_inputFontColorR,"inputFontColorR");
	GetInitGameParam(&m_inputFontColorG,"inputFontColorG");
	GetInitGameParam(&m_inputFontColorB,"inputFontColorB");

	m_henkanSelectColorR = 0;
	m_henkanSelectColorG = 0;
	m_henkanSelectColorB = 255;
	m_henkanSelectColorA = 50;
	GetInitGameParam(&m_henkanSelectColorR,"henkanSelectColorR");
	GetInitGameParam(&m_henkanSelectColorG,"henkanSelectColorG");
	GetInitGameParam(&m_henkanSelectColorB,"henkanSelectColorB");
	GetInitGameParam(&m_henkanSelectColorA,"henkanSelectColorA");

	m_inputSelectColorR = 0;
	m_inputSelectColorG = 0;
	m_inputSelectColorB = 255;
	m_inputSelectColorA = 50;
	GetInitGameParam(&m_inputSelectColorR,"inputSelectColorR");
	GetInitGameParam(&m_inputSelectColorG,"inputSelectColorG");
	GetInitGameParam(&m_inputSelectColorB,"inputSelectColorB");
	GetInitGameParam(&m_inputSelectColorA,"inputSelectColorA");

	for (int j=0;j<4;j++)
	{
		char name[256];
		
		int kakuteiTextMax = 0;
		sprintf_s(name,256,"kakuteiTextMax%d",j+1);
		GetInitGameParam(&kakuteiTextMax,name);
		m_textMax[j][0] = kakuteiTextMax;

		int henkanTextMax = 0;
		sprintf_s(name,256,"henkanTextMax%d",j+1);
		GetInitGameParam(&henkanTextMax,name);
		m_textMax[j][1] = henkanTextMax;

		int inputTextMax = 0;
		sprintf_s(name,256,"inputTextMax%d",j+1);
		GetInitGameParam(&inputTextMax,name);
		m_textMax[j][2] = inputTextMax;

	}

	m_debugPrintFlag = 0;
	GetInitGameParam(&m_debugPrintFlag,"debugPrintFlag");

	m_debugFontSize = 16;
	m_debugPrintX = 300;
	m_debugPrintY = 500;
	m_debugNextY = 20;
	GetInitGameParam(&m_debugFontSize,"debugFontSize");
	GetInitGameParam(&m_debugPrintX,"debugPrintX");
	GetInitGameParam(&m_debugPrintY,"debugPrintY");
	GetInitGameParam(&m_debugNextY,"debugNextY");



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
	if ((m_targetType >= 0) && (m_targetType <= 3))
	{
		int table[3];
		for (int i=0;i<3;i++)
		{
			table[i] = m_textMax[m_targetType][i];
		}
		m_softKey->SetTextLengthMax(table);
	}

	m_softKey->Init();

	return -1;
}

int CCommonKanjiInput::Calcu(void)
{
//	if (m_mouseStatus->CheckClick(1))
//	{
//		return ReturnFadeOut(-1);
//	}

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
			else if (m_targetType == 2)
			{
				m_game->SetSeiMei(text,NULL);
				return ReturnFadeOut(-1);
			}
			else if (m_targetType == 3)
			{
				m_game->SetSeiMei(NULL,text);
				return ReturnFadeOut(-1);
			}
			else
			{
				//error
			}
		}
	}


	return -1;
}

int CCommonKanjiInput::Print(void)
{
	CAreaControl::SetNextAllPrint();
	PrintBackScriptOrBG();


	m_softKey->Print();

	if (1)
	{
		int x = m_printX;
		int y = m_printY;

		int ln = m_softKey->GetKakuteiLength();
		LPSTR kakuteiText = m_softKey->GetKakuteiText();
		if (ln > 0)
		{
			m_message->PrintMessage(x,y,kakuteiText,m_fontSize,m_kakuteiFontColorR,m_kakuteiFontColorG,m_kakuteiFontColorB);
		}
		x += (m_fontSize+1)*ln;


		ln = m_softKey->GetHenkanLength();
		LPSTR henkanText = m_softKey->GetHenkanText();
		if (ln > 0)
		{
			m_message->PrintMessage(x,y,henkanText,m_fontSize,m_henkanFontColorR,m_henkanFontColorG,m_henkanFontColorB);
			if (m_henkanSelectColorA > 0)
			{
				CAllGeo::TransBoxFill(x,y,ln*(m_fontSize+1),m_fontSize+1,m_henkanSelectColorR,m_henkanSelectColorG,m_henkanSelectColorB,m_henkanSelectColorA);
			}
		}
		x += (m_fontSize+1)*ln;


		ln = m_softKey->GetInputLength();
		LPSTR inputText = m_softKey->GetInputText();
		if (ln > 0)
		{
			m_message->PrintMessage(x,y,inputText,m_fontSize,m_inputFontColorR,m_inputFontColorG,m_inputFontColorB);
			if (m_inputSelectColorA > 0)
			{
				CAllGeo::TransBoxFill(x,y,ln*(m_fontSize+1),m_fontSize+1,m_inputSelectColorR,m_inputSelectColorG,m_inputSelectColorB,m_inputSelectColorA);
			}
		}
	}
	
	

	if (m_debugPrintFlag)
	{
		int x = m_debugPrintX;
		int y = m_debugPrintY;

		m_message->PrintMessage(x,y,"デバッグ情報");
		y += m_debugNextY;

		m_message->PrintMessage(x,y,"確定文字列：");
		int ln = m_softKey->GetKakuteiLength();
		LPSTR kakuteiText = m_softKey->GetKakuteiText();
		if (ln > 0)
		{
			m_message->PrintMessage(x+(m_debugFontSize+1)*6,y,kakuteiText,m_debugFontSize,m_kakuteiFontColorR,m_kakuteiFontColorG,m_kakuteiFontColorB);
		}
		y += m_debugNextY;


		m_message->PrintMessage(x,y,"変換文字列：");
		ln = m_softKey->GetHenkanLength();
		LPSTR henkanText = m_softKey->GetHenkanText();
		if (ln > 0)
		{
			m_message->PrintMessage(x+(m_debugFontSize+1)*6,y,henkanText,m_debugFontSize,m_henkanFontColorR,m_henkanFontColorG,m_henkanFontColorB);
			if (m_henkanSelectColorA > 0)
			{
				CAllGeo::TransBoxFill(x+(m_debugFontSize+1)*6,y,ln*(m_debugFontSize+1),m_debugFontSize+1,m_henkanSelectColorR,m_henkanSelectColorG,m_henkanSelectColorB,m_henkanSelectColorA);
			}
		}
		y += m_debugNextY;


		m_message->PrintMessage(x,y,"入力文字列：");
		ln = m_softKey->GetInputLength();
		LPSTR inputText = m_softKey->GetInputText();
		if (ln > 0)
		{
			m_message->PrintMessage(x+(m_debugFontSize+1)*6,y,inputText,m_debugFontSize,m_inputFontColorR,m_inputFontColorG,m_inputFontColorB);
			if (m_inputSelectColorA > 0)
			{
				CAllGeo::TransBoxFill(x+(m_debugFontSize+1)*6,y,ln*(m_debugFontSize+1),m_debugFontSize+1,m_inputSelectColorR,m_inputSelectColorG,m_inputSelectColorB,m_inputSelectColorA);
			}
		}
//		y += 30;


	}

	return -1;
}

void CCommonKanjiInput::FinalExitRoutine(void)
{
	m_game->ClearFontCache();

	m_game->SetYoyaku();

}

/*_*/


