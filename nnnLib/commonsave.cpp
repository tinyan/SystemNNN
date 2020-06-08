//
// commonSave.cpp
//

#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanEffectLib\effectstruct.h"

#include "..\nnnUtilLib\suuji.h"

#include "..\nnnUtilLib\superButtonPicture.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"
#include "..\nnnUtilLib\commonUpDOwnBack.h"

#include "..\nnnUtilLib\commonBackButton.h"

#include "..\nnnUtilLib\commonMultiStateButton.h"
#include "..\nnnUtilLib\commonCheckButton.h"
#include "..\nnnUtilLib\commonRadioButton.h"
#include "..\nnnUtilLib\commonRadioButtonGroup.h"

#include "commonGeneral.h"
#include "commonDataFile.h"

#include "commonSystemSoundName.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\scriptcommand.h"

#include "..\nnnUtilLib\commonKeyList.h"

#include "..\nnnUtilLib\myMessage.h"

#include "..\nnnUtilLib\myTextInputBox.h"

#include "commonLoadSave.h"
#include "commonSave.h"

#include "gameCallBack.h"



//char CCommonSave::m_defaultSuujiFileName[] = "ta_sl_font3";


//char CCommonSave::m_defaultBGFileName[] = "save_bg";
char CCommonSave::m_defaultDialogFileName[] = "ta_dialog_4";
//char CCommonSave::m_defaultButtonFileName[] = "ta_dialog_bt1";

char CCommonSave::m_buttonName[][16]=
{
	"dialogOk","dialogCancel","dialogOk2","dialogCancel2",
};

CCommonSave::CCommonSave(CGameCallBack* lpGame) : CCommonLoadSave(lpGame,"save")
{
	SetClassNumber(SAVE_MODE);
//	m_classNumber = SAVE_MODE;

	m_savePic = NULL;
	m_miniCGPrintFlag = 0;
	GetInitGameParam(&m_miniCGPrintFlag,"miniCGPrintFlag");
	if (m_miniCGPrintFlag)
	{
		m_savePic = new CPicture(m_savePicSize.cx,m_savePicSize.cy);
		m_miniCGPrintX = 0;
		m_miniCGPrintY = 0;
		GetInitGameParam(&m_miniCGPrintX,"miniCGPrintX");
		GetInitGameParam(&m_miniCGPrintY,"miniCGPrintY");
	}


	m_gameYearVarNumber = m_game->GetVarNumber("year");
	m_gameDateVarNumber = m_game->GetVarNumber("date");


	m_warningPrintFlag = 0;
	GetInitGameParam(&m_warningPrintFlag,"warningPrintFlag");

	m_dialogButton = NULL;
	m_dialogButton2 = NULL;

	if (m_warningPrintFlag)
	{
		m_dialogFileName = m_defaultDialogFileName;
		GetInitGameString(&m_dialogFileName,"fileNameDialog");

		//make button
		m_dialogSizeX = 340;
		m_dialogSizeY = 145;
		m_dialogX = 236;
		m_dialogY = 160;

		GetInitGameParam(&m_dialogX,"dialogX");
		GetInitGameParam(&m_dialogY,"dialogY");
		GetInitGameParam(&m_dialogSizeX,"dialogSizeX");
		GetInitGameParam(&m_dialogSizeY,"dialogSizeY");


		char* names[2];
		names[0] = m_buttonName[0];
		names[1] = m_buttonName[1];

		m_dialogButton = new CCommonButtonGroup(m_setup,2,NULL,NULL,names);
		//change zahyo
		for (int i=0;i<2;i++)
		{
			POINT pt = m_dialogButton->GetZahyo(i);
			pt.x += m_dialogX;
			pt.y += m_dialogY;
			m_dialogButton->SetZahyo(i,pt);

			m_dialogButton->SetPicture(i,CSuperButtonPicture::GetPicture(3+i));
		}
		m_dialogButton->SetCancelButton(1);
	}



	m_commentInputFlag = 0;
	GetInitGameParam(&m_commentInputFlag,"commentInputFlag");

	m_textInputBox = NULL;

	m_saveCommentLineNumber = 0;

	m_textBoxDateSuuji4 = NULL;
	m_textBoxDateSuuji2 = NULL;
	m_textBoxGameYearSuuji4 = NULL;
	m_textBoxGameDateSuuji2 = NULL;
	m_textBoxGameDateSuuji2B = NULL;

	m_textBoxDatePrintFlag = 0;
	m_textBoxGameYearPrintFlag = 0;
	m_textBoxGameDatePrintFlag = 0;

	m_textBoxAddPicPrintFlag = 0;
	m_textBoxAddPicWithSpecialFlag = 0;

	m_textBoxSpecialNumberPrintFlag = 0;
	m_textBoxSpecialNumberPrintLimit = -1;
	GetInitGameParam(&m_textBoxSpecialNumberPrintLimit,"textBoxSpecialNumberPrintLimit");

	m_textBoxAddPic = NULL;
	m_textBoxSpecialNumberSuuji = NULL;

	if (m_commentInputFlag)
	{
		m_dialogFileName2 = m_defaultDialogFileName;
		GetInitGameString(&m_dialogFileName2,"fileNameDialog2");

		char filename[1024];
		wsprintf(filename,"sys\\%s",m_dialogFileName2);
		m_inputDialog = new CPicture(filename);

		//make button
		m_dialogSizeX2 = 340;
		m_dialogSizeY2 = 145;
		m_dialogX2 = 236;
		m_dialogY2 = 160;

		GetInitGameParam(&m_dialogX2,"dialogX2");
		GetInitGameParam(&m_dialogY2,"dialogY2");
		GetInitGameParam(&m_dialogSizeX2,"dialogSizeX2");
		GetInitGameParam(&m_dialogSizeY2,"dialogSizeY2");


		char* names[2];
		names[0] = m_buttonName[2];
		names[1] = m_buttonName[3];

		m_dialogButton2 = new CCommonButtonGroup(m_setup,2,NULL,NULL,names);
		//change zahyo
		for (int i=0;i<2;i++)
		{
			POINT pt = m_dialogButton2->GetZahyo(i);
			pt.x += m_dialogX2;
			pt.y += m_dialogY2;
			m_dialogButton2->SetZahyo(i,pt);

			m_dialogButton2->SetPicture(i,CSuperButtonPicture::GetPicture(5+i));
		}
		m_dialogButton2->SetCancelButton(1);

//		m_commentInputReturnOkFlag = 1;
		m_commentInputNullNameOk = 1;
//		GetInitGameParam(&m_commentInputReturnOkFlag,"commentReturnOk");
		GetInitGameParam(&m_commentInputNullNameOk,"commentNullOk");

		m_textInputBox = m_game->GetTextInputBox();

		m_textInputBox->SetSetup(m_setup);
		m_textInputBox->SetParameter("",2);
		m_textInputBox->SetParameter("textInput",2);

		m_textBoxPrintX = 0;
		m_textBoxPrintY = 0;
		GetInitGameParam(&m_textBoxPrintX,"textBoxPrintX");
		GetInitGameParam(&m_textBoxPrintY,"textBoxPrintY");

		m_textBoxDatePrintFlag = 0;
		GetInitGameParam(&m_textBoxDatePrintFlag,"textBoxDatePrintFlag");
		if (m_textBoxDatePrintFlag)
		{
			m_textBoxDatePrintX = 0;
			m_textBoxDatePrintY = 0;
			GetInitGameParam(&m_textBoxDatePrintX,"textBoxDatePrintX");
			GetInitGameParam(&m_textBoxDatePrintY,"textBoxDatePrintY");
			LPSTR tbname = NULL;
			GetInitGameString(&tbname,"filenameTextBoxDate");
			CPicture* lpPic = m_game->GetSystemPicture(tbname);
			m_textBoxDateFontSizeX = 8;
			m_textBoxDateFontSizeY = 8;
			GetInitGameParam(&m_textBoxDateFontSizeX,"textBoxDateFontSizeX");
			GetInitGameParam(&m_textBoxDateFontSizeY,"textBoxDateFontSizeY");
			m_textBoxDateFontNextX = m_textBoxDateFontSizeX;
			GetInitGameParam(&m_textBoxDateFontNextX,"textBoxDateFontNextX");

			int upZeroFlag = 1;
			GetInitGameParam(&upZeroFlag,"textBoxDateUpZeroFlag");

			m_textBoxDateSuuji4 = new CSuuji(lpPic,m_textBoxDateFontSizeX,m_textBoxDateFontSizeY,4,m_textBoxDateFontNextX,TRUE);
			m_textBoxDateSuuji2 = new CSuuji(lpPic,m_textBoxDateFontSizeX,m_textBoxDateFontSizeY,2,m_textBoxDateFontNextX,upZeroFlag,TRUE);
		}


		m_textBoxGameYearPrintFlag = 0;
		LPSTR tbname2 = NULL;

		m_textBoxGameYearPrintX = 0;
		m_textBoxGameYearPrintY = 0;
		m_textBoxGameYearFontNextX = 8;
		GetInitGameParam(&m_textBoxGameYearPrintFlag,"textBoxGameYearPrintFlag");
		if (m_textBoxGameYearPrintFlag)
		{
			GetInitGameParam(&m_textBoxGameYearPrintX,"textBoxGameYearPrintX");
			GetInitGameParam(&m_textBoxGameYearPrintY,"textBoxGameYearPrintY");
			
			GetInitGameString(&tbname2,"filenameTextBoxGameYear");
			CPicture* lpPic = m_game->GetSystemPicture(tbname2);
			m_textBoxGameYearFontSizeX = 8;
			m_textBoxGameYearFontSizeY = 8;
			GetInitGameParam(&m_textBoxGameYearFontSizeX,"textBoxGameYearFontSizeX");
			GetInitGameParam(&m_textBoxGameYearFontSizeY,"textBoxGameYearFontSizeY");
			m_textBoxGameYearFontNextX = m_textBoxGameYearFontSizeX;
			GetInitGameParam(&m_textBoxGameYearFontNextX,"textBoxGameyearFontNextX");
			m_textBoxGameYearSuuji4 = new CSuuji(lpPic,m_textBoxGameYearFontSizeX,m_textBoxGameYearFontSizeY,4,m_textBoxGameYearFontNextX);
		}

		m_textBoxGameDatePrintFlag = 0;
		GetInitGameParam(&m_textBoxGameDatePrintFlag,"textBoxGameDatePrintFlag");
		if (m_textBoxGameDatePrintFlag)
		{
			m_textBoxGameDatePrintX = m_textBoxGameYearPrintX + m_textBoxGameYearFontNextX * 5;
			m_textBoxGameDatePrintY = m_textBoxGameYearPrintY;
			GetInitGameParam(&m_textBoxGameDatePrintX,"textBoxGameDatePrintX");
			GetInitGameParam(&m_textBoxGameDatePrintY,"textBoxGameDatePrintY");
			LPSTR tbname3 = tbname2;
			GetInitGameString(&tbname3,"filenameTextBoxGameDate");
			CPicture* lpPic = m_game->GetSystemPicture(tbname3);
			m_textBoxGameDateFontSizeX = m_textBoxGameYearFontSizeX;
			m_textBoxGameDateFontSizeY = m_textBoxGameYearFontSizeY;
			GetInitGameParam(&m_textBoxGameDateFontSizeX,"textBoxGameDateFontSizeX");
			GetInitGameParam(&m_textBoxGameDateFontSizeY,"textBoxGameDateFontSizeY");
			m_textBoxGameDateFontNextX = m_textBoxGameDateFontSizeX;
			GetInitGameParam(&m_textBoxGameDateFontNextX,"textBoxGameDateFontNextX");

			int upzeroFlag = 0;
			GetInitGameParam(&upzeroFlag,"textBoxGameDateUpZeroFlag");
			int upzeroFlag2 = upzeroFlag;
			GetInitGameParam(&upzeroFlag2,"textBoxGameDateUpZeroFlag2");
			int leftFlag = 0;
			GetInitGameParam(&leftFlag,"textBoxGameDateLeftFlag");
			int leftFlag2 = leftFlag;
			GetInitGameParam(&leftFlag2,"textBoxGameDateLeftFlag2");

			m_textBoxGameDateSuuji2 = new CSuuji(lpPic,m_textBoxGameDateFontSizeX,m_textBoxGameDateFontSizeY,2,m_textBoxGameDateFontNextX,upzeroFlag,TRUE,leftFlag);
			m_textBoxGameDateSuuji2B = new CSuuji(lpPic,m_textBoxGameDateFontSizeX,m_textBoxGameDateFontSizeY,2,m_textBoxGameDateFontNextX,upzeroFlag2,TRUE,leftFlag2);
		}


	
		GetInitGameParam(&m_textBoxAddPicPrintFlag,"textBoxAddPicPrintFlag");
		if (m_textBoxAddPicPrintFlag)
		{
			LPSTR name = NULL;
			GetInitGameString(&name,"filenameTextBoxAddPic");
			m_textBoxAddPic = m_game->GetSystemPicture(name);

			GetInitGameParam(&m_textBoxAddPicWithSpecialFlag,"textBoxAddPicWithSpecialFlag");

			int x = 0;
			int y = 0;
			GetInitGameParam(&x,"textBoxAddPicPrintX");
			GetInitGameParam(&y,"textBoxAddPicPrintY");
			m_textBoxAddPicPrintZahyo.x = x;
			m_textBoxAddPicPrintZahyo.y = y;

			int sizeX = 16;
			int sizeY = 16;
			GetInitGameParam(&sizeX,"textBoxAddPicSizeX");
			GetInitGameParam(&sizeY,"textBoxAddPicSizeY");
			m_textBoxAddPicSize.cx = sizeX;
			m_textBoxAddPicSize.cy = sizeY;

			m_textBoxAddPicMultiFlag = 0;
			GetInitGameParam(&m_textBoxAddPicMultiFlag,"textBoxAddPicMultiFlag");
			m_textBoxAddPicMultiKosuuX = 1;
			GetInitGameParam(&m_textBoxAddPicMultiKosuuX,"textBoxAddPicMultiNumberX");
		}


		GetInitGameParam(&m_textBoxSpecialNumberPrintFlag,"textBoxSpecialNumberPrintFlag");
		if (m_textBoxSpecialNumberPrintFlag)
		{
			int x = 0;
			int y = 0;
			GetInitGameParam(&x,"textBoxSpecialNumberPrintX");
			GetInitGameParam(&y,"textBoxSpecialNumberPrintY");
			m_textBoxSpecialNumberPrintZahyo.x = x;
			m_textBoxSpecialNumberPrintZahyo.y = y;

			int sizeX = 16;
			int sizeY = 16;
			GetInitGameParam(&sizeX,"textBoxSpecialNumberFontSizeX");
			GetInitGameParam(&sizeY,"textBoxSpecialNumberFontSizeY");
			int nextX = sizeX;
			GetInitGameParam(&nextX,"textBoxSpecialNumberFontNextX");
			int keta = 2;
			GetInitGameParam(&keta,"textBoxSpecialNumberKeta");

			LPSTR name = NULL;
			GetInitGameString(&name,"filenameTextBoxSpecialNumberFont");
			CPicture* lpPic = m_game->GetSystemPicture(name);

			m_textBoxSpecialNumberSuuji = new CSuuji(lpPic,sizeX,sizeY,keta,nextX);
		}




		int lm = 1;
		GetInitGameParam(&lm,"saveCommentLineNumber");
		m_saveCommentLineNumber = lm-1;
	}




	m_saveSound = 1;
	m_warningSound = -1;
	m_commentSound = -1;
	GetInitGameParam(&m_saveSound,"saveSound");
	GetInitGameParam(&m_warningSound,"warningSound");
	GetInitGameParam(&m_commentSound, "commentSound");


	m_saveVoiceKosuu = 0;
	m_warningVoiceKosuu = 0;
	GetInitGameParam(&m_saveVoiceKosuu,"saveVoiceNumber");
	GetInitGameParam(&m_warningVoiceKosuu,"warningVoiceNumber");
	m_saveVoice = NULL;
	m_warningVoice = NULL;
	
	if (m_saveVoiceKosuu > 0)
	{
		m_saveVoice = new LPSTR[m_saveVoiceKosuu];
		for (int i=0;i<m_saveVoiceKosuu;i++)
		{
			char name[256];
			wsprintf(name,"saveVoice%d",i+1);
			LPSTR filename = NULL;
			GetInitGameString(&filename,name);
			m_saveVoice[i] = filename;
		}
	}

	if (m_warningVoiceKosuu > 0)
	{
		m_warningVoice = new LPSTR[m_warningVoiceKosuu];
		for (int i=0;i<m_warningVoiceKosuu;i++)
		{
			char name[256];
			wsprintf(name,"warningVoice%d",i+1);
			LPSTR filename = NULL;
			GetInitGameString(&filename,name);
			m_warningVoice[i] = filename;
		}
	}

	m_saveVoiceRandomFixVarNumber = -1;
	m_warningVoiceRandomFixVarNumber = -1;
	LPSTR fixName = NULL;
	if (GetInitGameString(&fixName,"saveVoiceFixVar"))
	{
		m_saveVoiceRandomFixVarNumber = m_game->GetVarNumber(fixName);
	}

	fixName = NULL;
	if (GetInitGameString(&fixName,"warningVoiceFixVar"))
	{
		m_warningVoiceRandomFixVarNumber = m_game->GetVarNumber(fixName);
	}



	GetInitGameParam(&m_quickSaveSelectOk,"quickSaveSelectOk");

	m_quickSetLastFlag = 0;
	GetInitGameParam(&m_quickSetLastFlag,"quickSetLastFlag");
}




CCommonSave::~CCommonSave()
{
	End();
}

void CCommonSave::End(void)
{
	DELETEARRAY(m_warningVoice);
	DELETEARRAY(m_saveVoice);

	ENDDELETECLASS(m_textBoxGameDateSuuji2B);
	ENDDELETECLASS(m_textBoxGameDateSuuji2);
	ENDDELETECLASS(m_textBoxGameYearSuuji4);
	ENDDELETECLASS(m_textBoxDateSuuji2);
	ENDDELETECLASS(m_textBoxDateSuuji4);

	ENDDELETECLASS(m_textBoxSpecialNumberSuuji);


	ENDDELETECLASS(m_dialogButton2);
	ENDDELETECLASS(m_inputDialog);
	ENDDELETECLASS(m_dialogButton);

	ENDDELETECLASS(m_savePic);
}

int CCommonSave::Init(void)
{
	return CCommonLoadSave::Init();
}

int CCommonSave::Calcu(void)
{
	return CCommonLoadSave::Calcu();
}

int CCommonSave::Print(void)
{
	return CCommonLoadSave::Print();
}

/*
int CCommonSave::Init(void)
{
	char filename[256];

	if (m_backScriptFlag == FALSE)
	{
		LoadBG();
	}

	sprintf(filename,"sys\\%s",m_dialogFileName);
	m_commonParts->LoadDWQ(filename);

	m_upDownBack->Init();

	m_clickingFlag = FALSE;
	m_clickingCount = 0;
	m_warningFlag = FALSE;

	return -1;
}
*/

/*
int CCommonSave::Calcu(void)
{
	if (m_warningFlag)
	{
		int wrt = m_button->Calcu(m_mouseStatus);
		if (wrt == MYBUTTON_NOTHING) return -1;

		//sound???
		int wst = wrt & MYBUTTON_STATUSMASK;
		int wnm = wrt & MYBUTTON_DATAMASK;

		if (wst == MYBUTTON_STARTCLICK)
		{
			if (wnm == 0)
			{
			}
			if (wnm == 1)
			{
			}
			
			return -1;
		}


		if (wst == MYBUTTON_NUMBER)
		{
			m_warningFlag = FALSE;

			m_button->Init();

			if (wnm == 0)
			{
//				m_fileControl->Save(m_saveNumber);
				LoadBG();
				CAreaControl::SetNextAllPrint();
				return -1;
			}

			if (wnm == 1)
			{
				LoadBG();
				CAreaControl::SetNextAllPrint();
				return -1;
			}
		}

		return -1;
	}


//	int rt = m_fileControl->Calcu();

	int rt = -1;

	if (rt == 0)
	{
		m_game->FuqueAllEffect();
		return ReturnFadeOut(m_backMode);
	}

	if (rt > 0)
	{
		if (m_fileControl->CheckDataExist(rt-1))
		{
//@@@			m_game->PlayDialogVoice(1);

			m_saveNumber = rt - 1;
			m_warningFlag = TRUE;
			m_game->Erase();
			m_commonParts->Blt(m_dialogX,m_dialogY,0,0,m_dialogSizeX,m_dialogSizeY,TRUE);
			m_commonBG->GetScreen();
			CAreaControl::SetNextAllPrint();
		}
		else
		{
			m_fileControl->Save(rt-1);
			m_game->SaveSystemFile();
			CAreaControl::SetNextAllPrint();
		}


	}

	return -1;
}

int CCommonSave::Print(void)
{
	PrintBackScriptOrBG();

	BOOL b = CAreaControl::CheckAllPrintMode();

	if (m_warningFlag == FALSE)
	{
//		m_fileControl->Print(b);
	}
	else
	{
//		if (b)
		if (1)
		{
//			m_commonParts->Put(m_dialogX,m_dialogY,TRUE);
//			m_commonParts->Blt(m_dialogX,m_dialogY,0,0,m_dialogSizeX,m_dialogSizeY,TRUE);
		}

		if (b)
		{
//			m_commonBG->Blt(0,0,0,0,800,600,FALSE);
			m_commonBG->Put(0,0,FALSE);
		}

		m_button->Print(TRUE);
		CAreaControl::AddArea(m_dialogX,m_dialogY,m_dialogSizeX,m_dialogSizeY);
	}

	return -1;
}
*/

/*
void CCommonSave::LoadBG(void)
{
	char filename[256];

	sprintf(filename,"sys\\%s",m_bgFileName);
	m_commonBG->LoadDWQ(filename);

}
*/


int CCommonSave::CalcuWarning(void)
{
	int rt = m_dialogButton->Calcu(m_inputStatus);
	if (rt == NNNBUTTON_NOTHING) return -1;

	int nm = ProcessButtonGroup(rt);
	
	if (nm == 0)
	{
		SaveNowData();

		m_warningFlag = 0;
		m_clickingFlag = FALSE;

		InitPageButton();

//		m_updownBack->Init();
		InitAnime();
		CAreaControl::SetNextAllPrint();
	}
	else if (nm == 1)
	{
		m_warningFlag = 0;

		InitPageButton();

//		m_updownBack->Init();
		InitAnime();
		CAreaControl::SetNextAllPrint();
	}

	return -1;
}

int CCommonSave::CalcuComment(void)
{
	if (m_dialogButton2 == NULL) return -1;//error!

	int rt = m_dialogButton2->Calcu(m_inputStatus);
	if (rt == NNNBUTTON_NOTHING) return -1;
	int nm = ProcessButtonGroup(rt);

	if (nm == 0)
	{
		m_textInputBox->AutoClose();

		BOOL warningFlag = FALSE;
		if (m_clickExistDataFlag)
		{
			//check?
			if (m_warningPrintFlag)
			{
				warningFlag = TRUE;
			}
		}

		if (warningFlag)
		{
			m_warningFlag = 1;
			m_dialogButton->Init();

			if (m_warningSound != -1)
			{
				m_game->PlaySystemSound(m_warningSound-1);
			}
			PlayWarningVoice();
			CAreaControl::SetNextAllPrint();
		}
		else
		{
			m_clickingCount = 0;
			m_clickingFlag = TRUE;
			m_warningFlag = 0;

			if (m_saveSound != -1)
			{
				m_game->PlaySystemSound(m_saveSound-1);
			}
			PlaySaveVoice();
		}
	}
	else if (nm == 1)
	{
		m_textInputBox->AutoClose();

		m_warningFlag = 0;
		InitPageButton();
		InitAnime();
		CAreaControl::SetNextAllPrint();
	}

	return -1;
}

int CCommonSave::ProcessDataClicked(int n)
{
	SaveNowData();
	m_clickingFlag = FALSE;

	if (m_pageMode == 1)
	{
		m_updownBack->SetPage(m_page);
		m_updownBack->SetPageMax(m_pageMax);
		m_updownBack->Init();
	}
	else if (m_pageMode == 2)
	{
		m_back->Init();
		m_tabButton->SetRadio(m_page);
		m_tabButton->Init(m_page);
	}

//	m_updownBack->Init();
	InitAnime();
	CAreaControl::SetNextAllPrint();
	return -1;
}

int CCommonSave::ProcessStartClickExistData(int n)
{
	m_clickExistDataFlag = TRUE;

	if (m_commentInputFlag)
	{
		m_clickButtonNumber = n;
		StartNameInput(m_clickButtonNumber + m_page * m_blockX * m_blockY);
	}
	else
	{
		if (m_warningPrintFlag)
		{
			m_clickButtonNumber = n;
			m_warningFlag = 1;
			m_dialogButton->Init();

			if (m_warningSound != -1)
			{
				m_game->PlaySystemSound(m_warningSound-1);
			}
			PlayWarningVoice();
			CAreaControl::SetNextAllPrint();
		}
		else
		{
			ProcessStartClickNotExistData(n);
		}
	}

	return -1;
}

int CCommonSave::ProcessStartClickNotExistData(int n)
{
	m_clickExistDataFlag = FALSE;

	if (m_commentInputFlag)
	{
		m_clickButtonNumber = n;
		StartNameInput(-1);
	}
	else
	{
		m_clickButtonNumber = n;
		m_clickingCount = 0;
		m_clickingFlag = TRUE;

		if (m_saveSound != -1)
		{
			m_game->PlaySystemSound(m_saveSound-1);
		}
		PlaySaveVoice();
	}
	return -1;
}

void CCommonSave::StartNameInput(int n)
{
	m_warningFlag = 2;
	m_dialogButton2->Init();
	
	if (m_commentSound != -1)
	{
		m_game->PlaySystemSound(m_commentSound - 1);
	}

	//common textbox setup
	m_textInputBox->ChangeParameterNumber(2);

//	m_textInputBox->SetCursorMode(m_commentInputCursorMode);
//	m_textInputBox->SetCursorColor(m_commentInputCursorColor[0],m_commentInputCursorColor[1],m_commentInputCursorColor[2]);
//	m_textInputBox->SetCursorDelta(m_commentInputCursorZahyo);
//	m_textInputBox->SetCursorSize(m_commentInputCursorSize);
//	m_textInputBox->SetCursorTime(m_commentInputCursorOnTime,m_commentInputCursorOffTime);
//	m_textInputBox->SetFontSize(m_commentInputFontSize,m_commentInputFontSukima);


//	int maxLen = 16;//dummy
//	m_textInputBox->SetMaxLength(16*2);

//	int r = 255;
//	int g = 192;
//	int b = 64;
//	m_textInputBox->SetTextColor(r,g,b);

//	int alignMode = 0;
//	m_textInputBox->SetAlignFlag(alignMode);

	int x = m_dialogX2 + m_textBoxPrintX;
	int y = m_dialogY2 + m_textBoxPrintY;
	m_textInputBox->SetZahyo(x,y,2);

	char oldText[256];
	oldText[0] = 0;

	if (n >= 0)
	{
		LPSTR oldSaveText = m_ppDataFile[m_clickButtonNumber]->GetLargeMessage(m_saveCommentLineNumber);
		if (oldSaveText != NULL)
		{
			int ln = (int)strlen(oldSaveText);
			if (ln>254) ln = 254;
			memcpy(oldText,oldSaveText,ln);
			oldText[ln] = 0;
			oldText[ln+1] = 0;
		}
	}

//	m_textInputBox->Init();



	m_textInputBox->Start();
	m_textInputBox->Init();
	m_textInputBox->SetText(oldText,TRUE);
//	m_textInputBox->MoveIMEWindow();

	//minicg
	if (m_miniCGPrintFlag)
	{
		int* dst = (int*)(m_savePic->GetBuffer());
		m_game->GetMiniCGData(dst,-2,m_savePicSize.cx,m_savePicSize.cy);
	}
}


void CCommonSave::SaveNowData(void)
{
	m_game->SaveSystemFile();
	//comment set
	if (m_commentInputFlag)
	{
		m_game->SetSaveComment(m_textInputBox->GetText(),m_saveCommentLineNumber);
	}
	else
	{
	//	m_game->SetSaveComment(NULL,0);
	}

	m_ppDataFile[m_clickButtonNumber]->Save(m_clickButtonNumber + m_page * m_blockX * m_blockY);
	m_ppDataFile[m_clickButtonNumber]->LoadHeaderAndPic(m_clickButtonNumber + m_page * m_blockX * m_blockY);

	m_game->SetLastSelectSaveLoad(m_clickButtonNumber + m_page * m_blockX * m_blockY);

	m_game->SetLastSaveSlot(m_clickButtonNumber + m_page * m_blockX * m_blockY);
}

BOOL CCommonSave::QuickSave(void)
{
	m_ppDataFile[0]->Save(m_quickSaveSlotNumber);
	m_ppDataFile[0]->LoadHeaderAndPic(m_quickSaveSlotNumber);

	m_game->SetLastSelectSaveLoad(m_quickSaveSlotNumber);

	if (m_quickSetLastFlag)
	{
		if (m_quickSetLastFlag == -1)
		{
			m_game->SetLastSaveSlot(-1);
		}
		else
		{
			m_game->SetLastSaveSlot(m_quickSaveSlotNumber);
		}
	}

	return TRUE;
}


void CCommonSave::CreateStartScreen(void)
{
	Print();
}


void CCommonSave::InitPageButton(void)
{
	if (m_pageMode == 1)
	{
		m_updownBack->SetPage(m_page);
		m_updownBack->SetPageMax(m_pageMax);
		m_updownBack->Init();
	}
	else if (m_pageMode == 2)
	{
		m_back->Init();
		m_tabButton->SetRadio(m_page);
		m_tabButton->Init(m_page);
	}
}

void CCommonSave::PrintInputBoxStatus(void)
{
	if (m_miniCGPrintFlag)
	{
		int putX = m_dialogX2 + m_miniCGPrintX;
		int putY = m_dialogY2 + m_miniCGPrintY;
		m_savePic->Put(putX,putY,FALSE);
	}

		//save date
	if (m_textBoxDatePrintFlag)
	{

		SYSTEMTIME systemtime;
		GetLocalTime(&systemtime);


		int year = systemtime.wYear;
		int month = systemtime.wMonth;
		int day = systemtime.wDay;
		int hour = systemtime.wHour;
		int minute = systemtime.wMinute;

		int putX = m_dialogX2 + m_textBoxDatePrintX;
		int putY = m_dialogY2 + m_textBoxDatePrintY;
		int sizeX = m_textBoxDateFontSizeX;
		int sizeY = m_textBoxDateFontSizeY;
		int nextX = m_textBoxDateFontNextX;

		//year
		m_textBoxDateSuuji4->Print(putX,putY,year);
		putX += nextX * 4;
		// /
		m_textBoxDateSuuji4->Put(putX,putY,11);
		putX += nextX;
		//month
		m_textBoxDateSuuji2->Print(putX,putY,month);
		putX += nextX * 2;
		// /
		m_textBoxDateSuuji2->Put(putX,putY,11);
		putX += nextX;
		//day
		m_textBoxDateSuuji2->Print(putX,putY,day);
		putX += nextX * 2;
		// space
		putX += nextX;
		//hour
		m_textBoxDateSuuji2->Print(putX,putY,hour);
		putX += nextX * 2;
		//:
		m_textBoxDateSuuji2->Put(putX,putY,10);
		putX += nextX;
		//minute
		m_textBoxDateSuuji2->Print(putX,putY,minute);
	}

	if (m_textBoxGameYearPrintFlag)
	{
		int putX = m_dialogX2 + m_textBoxGameYearPrintX;
		int putY = m_dialogY2 + m_textBoxGameYearPrintY;
		int sizeX = m_textBoxGameYearFontSizeX;
		int sizeY = m_textBoxGameYearFontSizeY;
		int nextX = m_textBoxGameYearFontNextX;

//		int year = m_lpGameVar->var[m_gameYearVarNumber];
		int year = m_game->GetVarData(m_gameYearVarNumber);

		m_textBoxGameYearSuuji4->Print(putX,putY,year);
		putX += sizeX * 4;

		if (m_textBoxGameDatePrintFlag)
		{
			m_textBoxGameYearSuuji4->Put(putX,putY,11);
			putX += sizeX;
		}
	}

	if (m_textBoxGameDatePrintFlag)
	{
		int putX = m_dialogX2 + m_textBoxGameDatePrintX;
		int putY = m_dialogY2 + m_textBoxGameDatePrintY;
		int sizeX = m_textBoxGameDateFontSizeX;
		int sizeY = m_textBoxGameDateFontSizeY;
		int nextX = m_textBoxGameDateFontNextX;

//	int date = m_lpGameVar->var[m_gameDateVarNumber];
		int date = m_game->GetVarData(m_gameDateVarNumber);
		int month = date /100;
		int day = date % 100;

		//month
		m_textBoxGameDateSuuji2->Print(putX,putY,month);
		putX += nextX * 2;

		m_textBoxGameDateSuuji2->Put(putX,putY,11);
		putX += nextX;

		//day
		m_textBoxGameDateSuuji2B->Print(putX,putY,day);
		putX += nextX * 2;
	}


	if (m_textBoxAddPicPrintFlag)
	{
		if (m_textBoxAddPic != NULL)
		{
			int putX = m_dialogX2 + m_textBoxAddPicPrintZahyo.x;
			int putY = m_dialogY2 + m_textBoxAddPicPrintZahyo.y;
			int sizeX = m_textBoxAddPicSize.cx;
			int sizeY = m_textBoxAddPicSize.cy;

			int srcX = 0;
			int srcY = 0;


			int dat = m_game->GetSpecialNumberForSave();

			if (m_textBoxAddPicMultiFlag)
			{
				int dv = m_textBoxAddPicMultiKosuuX;
				if (dv<1) dv = 1;
				srcX = dat % dv;
				srcY = dat / dv;
				srcX *= sizeX;
				srcY *= sizeY;
			}

			BOOL okflg = TRUE;
			if (m_textBoxAddPicWithSpecialFlag)
			{
				if (dat < m_textBoxSpecialNumberPrintLimit)
				{
					okflg = FALSE;
				}
			}

			if (okflg)
			{
				m_textBoxAddPic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
			}
		}
	}

	if (m_textBoxSpecialNumberPrintFlag)
	{
		int putX = m_dialogX2 + m_textBoxSpecialNumberPrintZahyo.x;
		int putY = m_dialogY2 + m_textBoxSpecialNumberPrintZahyo.y;

		int dat = m_game->GetSpecialNumberForSave();
		if (dat >= m_textBoxSpecialNumberPrintLimit)
		{
			m_textBoxSpecialNumberSuuji->Print(putX,putY,dat);
		}
	}



}


void CCommonSave::PlaySaveVoice(void)
{
	if (m_saveVoiceKosuu > 0)
	{
		int r = rand() % m_saveVoiceKosuu;
		if (m_saveVoiceRandomFixVarNumber != -1)
		{
			int d = m_game->GetVarData(m_saveVoiceRandomFixVarNumber);
			if (d > 0)
			{
				r = d - 1;
			}
		}

		LPSTR voice = m_saveVoice[r];
		if (voice != NULL)
		{
			m_game->ReplayVoice(voice);
		}
	}
}

void CCommonSave::PlayWarningVoice(void)
{
	if (m_warningVoiceKosuu > 0)
	{
		int r = rand() % m_warningVoiceKosuu;
		if (m_warningVoiceRandomFixVarNumber != -1)
		{
			int d = m_game->GetVarData(m_warningVoiceRandomFixVarNumber);
			if (d > 0)
			{
				r = d - 1;
			}
		}

		LPSTR voice = m_warningVoice[r];
		if (voice != NULL)
		{
			m_game->ReplayVoice(voice);
		}
	}
}

/*_*/

