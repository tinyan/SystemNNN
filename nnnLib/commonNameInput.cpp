//
// commonNameInput.cpp
//


#include <windows.h>

#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"

#include "..\nnnUtilLib\superButtonPicture.h"

#include "..\nnnUtilLib\myMouseStatus.h"

#include "..\nnnUtilLib\nnnButtonStatus.h"
#include "..\nnnUtilLib\commonButton.h"


#include "commonMode.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\myMessage.h"

#include "..\nnnUtilLib\inputStatus.h"
#include "..\nnnUtilLib\myTextInputBox.h"

#include "gameCallBack.h"

#include "commonGeneral.h"

#include "commonNameInput.h"


char CCommonNameInput::m_defaultSeiFixData[] = "ŽOç‰@";
char CCommonNameInput::m_defaultMeiFixData[] = "‚à‚å‚à‚Æ";

char CCommonNameInput::m_defaultSeiDialogFileName[] = "ta_sei_dialog";
char CCommonNameInput::m_defaultMeiDialogFileName[] = "ta_mei_dialog";

CCommonNameInput::CCommonNameInput(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(NAMEINPUT_MODE);
	m_message = m_game->GetMyMessage();

//	m_classNumber = NAMEINPUT_MODE;
	LoadSetupFile("nameInput",2048);

	GetBackExecSetup();
	GetAllPrintSetup();

	m_useDefaultName = 0;
	GetInitGameParam(&m_useDefaultName,"useDefaultName");
	m_noNameIsDefault = 0;
	GetInitGameParam(&m_noNameIsDefault,"noNameIsDefault");

//	m_viewControl = m_game->GetViewControl();
	m_textInputBox = m_game->GetTextInputBox();

	m_textInputBox->SetSetup(m_setup);
	m_textInputBox->SetParameter("",0);
	m_textInputBox->SetParameter("sei",0);
	m_textInputBox->SetParameter("",1);
	m_textInputBox->SetParameter("mei",1);



	//sei mei

	//dialog sei mei
	//zahyo sei mei
	//limit sei mei
	//kotei sei mei
	//button ok cancel
	//color input,kotei

	//cursor

	//first back ok flag
	//status
	//time








	m_processMode = 0;
	int flg = 1;
	GetInitGameParam(&flg,"seiFlag");
	m_seimeiFlag[0] = flg;
	flg = 1;
	GetInitGameParam(&flg,"meiFlag");
	m_seimeiFlag[1] = flg;
	m_processMax = 0;

	m_seimeiReverse = 0;
	GetInitGameParam(&m_seimeiReverse,"seimeiReverse");
	if (m_seimeiReverse != 0)
	{
		m_seimeiReverse = 1;
	}

	m_seimeiType[0] = 0;//—pS
	m_seimeiType[1] = 1;

	m_processMax = 0;
	if (m_seimeiFlag[m_seimeiReverse])
	{
		m_seimeiType[m_processMax] = m_seimeiReverse;
		m_processMax++;
	}
	if (m_seimeiFlag[1-m_seimeiReverse])
	{
		m_seimeiType[m_processMax] = 1-m_seimeiReverse;
		m_processMax++;
	}


	int mx = 4;
	GetInitGameParam(&mx,"seiMax");
	m_seimeiMax[0] = mx;
	mx = 4;
	GetInitGameParam(&mx,"MeiMax");
	m_seimeiMax[1] = mx;

	flg = 0;
	GetInitGameParam(&flg,"seiFixFlag");
	m_seimeiFixFlag[0] = flg;
	flg = 0;
	GetInitGameParam(&flg,"meiFixFlag");
	m_seimeiFixFlag[1] = flg;

	LPSTR fixData = m_defaultSeiFixData;
	GetInitGameString(&fixData,"seiFixData");
	m_seimeiFixData[0] = fixData;
	fixData = m_defaultMeiFixData;
	GetInitGameString(&fixData,"meiFixData");
	m_seimeiFixData[1] = fixData;


	flg = 0;
	GetInitGameParam(&flg,"seiDontPrint");
	m_seimeiDontPrint[0] = flg;
	flg = 1;
	GetInitGameParam(&flg,"meiDontPrint");
	m_seimeiDontPrint[1] = flg;

	int x = 0;
	int y = 0;
	GetInitGameParam(&x,"seiPrintX");
	GetInitGameParam(&y,"seiPrintY");
	m_seimeiZahyo[0].x = x;
	m_seimeiZahyo[0].y = y;
//	x = 0;
//	y = 0;
	GetInitGameParam(&x,"meiPrintX");
	GetInitGameParam(&y,"meiPrintY");
	m_seimeiZahyo[1].x = x;
	m_seimeiZahyo[1].y = y;


	flg = 0;
	GetInitGameParam(&flg,"seiAlignMode");
	m_seimeiAlignMode[0] = flg;
	flg = 0;
	GetInitGameParam(&flg,"meiAlignMode");
	m_seimeiAlignMode[1] = flg;


	int r = 192;
	int g = 192;
	int b = 192;
	GetInitGameParam(&r,"seiColorR");
	GetInitGameParam(&g,"seiColorG");
	GetInitGameParam(&b,"seiColorB");
	m_seimeiColor[0][0][0] = r;
	m_seimeiColor[0][0][1] = g;
	m_seimeiColor[0][0][2] = b;
	GetInitGameParam(&r,"meiColorR");
	GetInitGameParam(&g,"meiColorG");
	GetInitGameParam(&b,"meiColorB");
	m_seimeiColor[1][0][0] = r;
	m_seimeiColor[1][0][1] = g;
	m_seimeiColor[1][0][2] = b;

	r = 255;
	g = 255;
	b = 255;
	GetInitGameParam(&r,"seiFixColorR");
	GetInitGameParam(&g,"seiFixColorG");
	GetInitGameParam(&b,"seiFixColorB");
	m_seimeiColor[0][1][0] = r;
	m_seimeiColor[0][1][1] = g;
	m_seimeiColor[0][1][2] = b;
	GetInitGameParam(&r,"meiFixColorR");
	GetInitGameParam(&g,"meiFixColorG");
	GetInitGameParam(&b,"meiFixColorB");
	m_seimeiColor[1][1][0] = r;
	m_seimeiColor[1][1][1] = g;
	m_seimeiColor[1][1][2] = b;

	




	LPSTR seiDialogFileName = m_defaultSeiDialogFileName;
	LPSTR meiDialogFileName = m_defaultMeiDialogFileName;
	GetInitGameString(&seiDialogFileName,"seiDialogFileName");
	GetInitGameString(&meiDialogFileName,"meiDialogFileName");
	m_seimeiDialogFileName[0] = seiDialogFileName;
	m_seimeiDialogFileName[1] = meiDialogFileName;


	x = 300;
	y = 250;
	GetInitGameParam(&x,"dialogPrintX");
	GetInitGameParam(&y,"dialogPrintY");
	m_dialogZahyo.x = x;
	m_dialogZahyo.y = y;

	int sizeX = 200;
	int sizeY = 100;
	GetInitGameParam(&sizeX,"dialogSizeX");
	GetInitGameParam(&sizeY,"dialogSizeY");
	m_dialogSize.cx = sizeX;
	m_dialogSize.cy = sizeY;


//	m_cursorMode = 1;
//	GetInitGameParam(&m_cursorMode,"cursorMode");
//	r = 255;
//	GetInitGameParam(&r,"cursorColorR");
//	g = r;
//	GetInitGameParam(&g,"cursorColorG");
//	b = g;
//	GetInitGameParam(&b,"cursorColorB");
//	m_cursorColor[0] = r;
//	m_cursorColor[1] = g;
//	m_cursorColor[2] = b;

//	sizeX = 3;
//	sizeY = 24;
//	GetInitGameParam(&sizeX,"cursorSizeX");
//	GetInitGameParam(&sizeY,"cursorSizeY");
//	m_cursorSize.cx = sizeX;
//	m_cursorSize.cy = sizeY;

//	x = 0;
//	y = 0;
//	GetInitGameParam(&x,"cursorPrintX");
//	GetInitGameParam(&y,"cursorPrintY");
//	m_cursorZahyo.x = x;
//	m_cursorZahyo.y = y;

//	m_cursorOnTime = 25;
//	GetInitGameParam(&m_cursorOnTime,"cursorOnTime");
//	m_cursorOffTime = m_cursorOnTime;
//	GetInitGameParam(&m_cursorOffTime,"cursorOffTime");

	m_fontSize[0] = 24;
	GetInitGameParam(&m_fontSize[0],"seiFontSize");
	m_fontSukima[0] = 1;
	GetInitGameParam(&m_fontSukima[0],"seiFontSukima");

	m_fontSize[1] = m_fontSize[0];
	GetInitGameParam(&m_fontSize[1],"meiFontSize");
	m_fontSukima[1] = m_fontSukima[0];
	GetInitGameParam(&m_fontSukima[1],"meiFontSukima");

	m_returnOkFlag = 1;
	GetInitGameParam(&m_returnOkFlag,"returnOk");
	m_nullNameOk = 0;
	GetInitGameParam(&m_nullNameOk,"nullNameOk");



	m_nullSeiIsDefault = 0;
	m_nullMeiIsDefault = 0;
	GetInitGameParam(&m_nullSeiIsDefault,"nullSeiIsDefault");
	GetInitGameParam(&m_nullMeiIsDefault,"nullMeiIsDefault");
	if (m_nullNameOk)
	{
		m_nullSeiIsDefault = 1;
		m_nullMeiIsDefault = 1;
	}

	m_nullNameIsDefault[0] = m_nullSeiIsDefault;
	m_nullNameIsDefault[1] = m_nullMeiIsDefault;



	m_returnStatusVarNumber = -1;
	m_returnTimeVarNumber = -1;
	LPSTR varName = NULL;
	if (GetInitGameString(&varName,"statusVarName"))
	{
		m_returnStatusVarNumber = m_game->GetVarNumber(varName);
	}
	LPSTR varName2 = NULL;
	if (GetInitGameString(&varName2,"timeVarName"))
	{
		m_returnTimeVarNumber = m_game->GetVarNumber(varName2);
	}


	m_seimeiData[0] = new char[256];
	m_seimeiData[1] = new char[256];

	int ln1 = (int)strlen(m_defaultSeiFixData);
	int ln2 = (int)strlen(m_defaultMeiFixData);

	memcpy(m_seimeiData[0],m_defaultSeiFixData,ln1+1);
	memcpy(m_seimeiData[1],m_defaultMeiFixData,ln2+1);






	CPicture* lpBG = m_commonBG;
	if (m_backScriptFlag) lpBG = NULL;

	m_okButton = new CCommonButton(m_setup,"ok",lpBG);
	m_cancelButton = new CCommonButton(m_setup,"cancel",lpBG);

	CPicture* lpPic = CSuperButtonPicture::GetPicture(0);
	m_okButton->SetPicture(lpPic);
	CPicture* lpPic2 = CSuperButtonPicture::GetPicture(1);
	m_cancelButton->SetPicture(lpPic2);

	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();

}


CCommonNameInput::~CCommonNameInput()
{
	End();
}

void CCommonNameInput::End(void)
{
	DELETEARRAY(m_seimeiData[1]);
	DELETEARRAY(m_seimeiData[0]);

	ENDDELETECLASS(m_cancelButton);
	ENDDELETECLASS(m_okButton);
}



int CCommonNameInput::Init(void)
{
	m_processMode = 0;
	m_count = 0;
	
	m_textInputBox->ChangeParameterNumber(m_seimeiType[m_processMode]);


	//common textbox setup
//	m_textInputBox->SetCursorMode(m_cursorMode);
//	m_textInputBox->SetCursorColor(m_cursorColor[0],m_cursorColor[1],m_cursorColor[2]);
//	m_textInputBox->SetCursorDelta(m_cursorZahyo);
//	m_textInputBox->SetCursorSize(m_cursorSize);
//	m_textInputBox->SetCursorTime(m_cursorOnTime,m_cursorOffTime);
//	m_textInputBox->SetFontSize(m_fontSize,m_fontSukima);

	SetTextInputBox(m_seimeiType[m_processMode]);
	SetDefaultNameToName();

	LoadDialog(m_seimeiType[m_processMode]);

	m_textInputBox->Start();
	m_textInputBox->Init();

	//load button pic
	LPSTR picName = m_okButton->GetFileName();
	char filename[1024];
	wsprintf(filename,"sys\\%s",picName);
	CPicture* lpPic = m_okButton->GetPicture();
	lpPic->LoadDWQ(filename);

	picName = m_cancelButton->GetFileName();
	wsprintf(filename,"sys\\%s",picName);
	lpPic = m_cancelButton->GetPicture();
	lpPic->LoadDWQ(filename);

	m_lastEnable[0] = 1;
	m_lastEnable[1] = 1;

	m_okButton->SetEnable();
	m_cancelButton->SetEnable();


	if (1)
	{
		int md = m_seimeiType[0];
		if (md >= 0)
		{
			LPSTR names = m_seimeiData[md];
			m_textInputBox->SetText(names,TRUE);
		}
	}



	SetButtonEnable();

	m_okButton->Init();
	m_cancelButton->Init();

	m_inputFlag = FALSE;
	m_exitFlag = FALSE;

	return -1;
}

int CCommonNameInput::Calcu(void)
{
	if (m_exitFlag)
	{
		return -1;
	}

	m_count++;
	if (m_count > 9999) m_count = 9999;

	int rt1 = m_okButton->Calcu(m_inputStatus);
	if (rt1 != -1)
	{
		int nm1 = ProcessCommonButton(rt1);
		if (nm1 >= 0)
		{
			//ok!
			//check data
			LPSTR name = m_textInputBox->GetText();
			if ((*name) == 0)
			{
				if (m_nullNameOk == 0)
				{
					//cannot!
					SetButtonEnable();
					m_okButton->Init();
					m_cancelButton->Init();
					return -1;
				}

				int md = m_seimeiType[m_processMode];
				if (md >= 0)
				{
					if (m_nullNameIsDefault[md])
					{
						if(m_useDefaultName == 0)
						{
							name = m_game->GetDefaultSeiMei(md);
						}
						else
						{
							name = m_game->GetGameDefaultSeiMei(md);
						}
					}
				}
			}

			int ln = (int)strlen(name);
			int md = m_seimeiType[m_processMode];
			if (md >= 0)
			{
				memcpy(m_seimeiData[md],name,ln+1);
				if ((m_processMode+1) >= m_processMax)
				{
					//set!
					m_inputFlag = TRUE;
					m_exitFlag = TRUE;
					m_textInputBox->AutoClose();
					return ReturnFadeOut(-1);
				}

				m_processMode++;
				//init!

				m_textInputBox->Init();
				SetTextInputBox(m_seimeiType[m_processMode]);
				//SetDefaultNameToName();

				LoadDialog(m_seimeiType[m_processMode]);

				SetButtonEnable();

				m_okButton->Init();
				m_cancelButton->Init();

				return -1;
			}
		}
	}

	int rt2 = m_cancelButton->Calcu(m_inputStatus);
	if (rt2 != -1)
	{
		int nm2 = ProcessCommonButton(rt2);
		if (nm2 >= 0)
		{
			//cancel
			if ((m_processMode == 0) && (m_returnOkFlag == 0))
			{
				//cannot!
				SetButtonEnable();

				m_okButton->Init();
				m_cancelButton->Init();
				return -1;
			}

			if (m_processMode == 0)
			{
				m_exitFlag = TRUE;
				m_textInputBox->AutoClose();
				return ReturnFadeOut(-1);
			}


			m_processMode--;
			//init!

			m_textInputBox->Init();
			SetTextInputBox(m_seimeiType[m_processMode]);

			LoadDialog(m_seimeiType[m_processMode]);

			SetButtonEnable();

			m_okButton->Init();
			m_cancelButton->Init();

			return -1;
		}
	}

	SetButtonEnable();


	return -1;
}

int CCommonNameInput::Print(void)
{
	PrintBackScriptOrBG();


	//dialog
	m_commonParts->Blt(m_dialogZahyo.x, m_dialogZahyo.y, 0,0,m_dialogSize.cx, m_dialogSize.cy, TRUE);

	//name
	for (int i=0;i<2;i++)
	{
		int md = i;
		if (md != m_seimeiType[m_processMode])
		{
			if (m_seimeiDontPrint[md] == 0)
			{
				POINT pt = m_seimeiZahyo[md];
				pt.x += m_dialogZahyo.x;
				pt.y += m_dialogZahyo.y;
				int align = m_seimeiAlignMode[md];
				int maxLen = m_seimeiMax[md];
				LPSTR name = m_seimeiData[md];

				POINT pt2 = m_textInputBox->GetTextZahyo(pt,name,maxLen*2,align);

				int r = m_seimeiColor[md][1][0];
				int g = m_seimeiColor[md][1][1];
				int b = m_seimeiColor[md][1][2];

				m_message->PrintMessage(pt2.x, pt2.y, name, m_fontSize[md], r,g,b, m_fontSukima[md]);
			}
		}
	}

	//textbox
	m_textInputBox->Print();


	m_okButton->Print();
	m_cancelButton->Print();

	return 0;
}

void CCommonNameInput::SetTextInputBox(int n)
{
	if (n < 0) return;

	m_textInputBox->ChangeParameterNumber(n);

//	int maxLen = m_seimeiMax[n];
//	m_textInputBox->SetMaxLength(maxLen * 2);


//	int r = m_seimeiColor[n][0][0];
//	int g = m_seimeiColor[n][0][1];
//	int b = m_seimeiColor[n][0][2];
//	m_textInputBox->SetTextColor(r,g,b);

//	int alignMode = m_seimeiAlignMode[n];
//	m_textInputBox->SetAlignFlag(alignMode);

	POINT pt = m_dialogZahyo;
	POINT pt2 = m_seimeiZahyo[n];
	int x = pt.x + pt2.x;
	int y = pt.y + pt2.y;

	//adjust zahyo
	POINT pt3;
	pt3.x = x;
	pt3.y = y;
	POINT pt4 = m_game->GameToView(pt3);

	m_textInputBox->SetZahyo(x,y,n);
//	m_textInputBox->SetIMEZahyo(pt4.x,pt4.y,n);

	m_textInputBox->Init();

	LPSTR name = m_seimeiData[n];
	m_textInputBox->SetText(name,TRUE);

}


void CCommonNameInput::LoadDialog(int n)
{
	if (n < 0) return;

	LPSTR dialogName = m_seimeiDialogFileName[n];
	char filename[1024];
	wsprintf(filename,"sys\\%s",dialogName);
	m_commonParts->LoadDWQ(filename);
}



void CCommonNameInput::SetDefaultNameToName(void)
{
	LPSTR sei = m_game->GetSystemSei();
	LPSTR mei = m_game->GetSystemMei();

	if (m_useDefaultName)
	{
		sei = m_game->GetGameDefaultSei();
		mei = m_game->GetGameDefaultMei();
	}

	int ln1 = (int)strlen(sei);
	int ln2 = (int)strlen(mei);

	if (ln1 > 254) ln1 = 254;
	if (ln2 > 254) ln2 = 254;

	memcpy(m_seimeiData[0],sei,ln1+1);
	memcpy(m_seimeiData[1],mei,ln2+1);

	//ŒÅ’è?
	for (int i=0;i<2;i++)
	{
		if ((m_seimeiFlag[i] == 0) && m_seimeiFixFlag[i])
		{
			int ln3 = (int)strlen(m_seimeiFixData[i]);
			memcpy(m_seimeiData[i],m_seimeiFixData[i],ln3+1);
		}
	}
}

void CCommonNameInput::SetButtonEnable(void)
{
	int oldFlag1 = m_lastEnable[0];
	int oldFlag2 = m_lastEnable[1];

	int newEnable1 = oldFlag1;
	int newEnable2 = oldFlag2;

	LPSTR name = m_textInputBox->GetText();
	if ((*name) == 0)
	{
		if (m_nullNameOk)
		{
			m_okButton->SetEnable();
			newEnable1 = 1;
		}
		else
		{
			m_okButton->SetEnable(FALSE);
			newEnable1 = 0;
		}
	}
	else
	{
		m_okButton->SetEnable();
		newEnable1 = 1;
	}

	if ((m_processMode == 0) && (m_returnOkFlag == 0))
	{
		m_cancelButton->SetEnable(FALSE);
		newEnable2 = 0;
	}
	else
	{
		m_cancelButton->SetEnable();
		newEnable2 = 1;
	}

	if (oldFlag1 != newEnable1)
	{
		m_lastEnable[0] = newEnable1;
		m_okButton->Init();
	}

	if (oldFlag2 != newEnable2)
	{
		m_lastEnable[1] = newEnable2;
		m_cancelButton->Init();
	}
}


void CCommonNameInput::FinalExitRoutine(void)
{
	if (m_inputFlag)
	{
		LPSTR sei = m_seimeiData[0];
		LPSTR mei = m_seimeiData[1];
		m_game->SetSeiMei(sei,mei);

		if (m_returnStatusVarNumber != -1)
		{
			m_game->SetVarData(m_returnStatusVarNumber,1);
		}
	}
	else
	{
		if (m_returnStatusVarNumber != -1)
		{
			m_game->SetVarData(m_returnStatusVarNumber,0);
		}
	}

	if (m_returnTimeVarNumber != -1)
	{
		m_game->SetVarData(m_returnTimeVarNumber,m_count);
	}

	m_game->ClearFontCache();

	m_game->SetYoyaku();
}

/*_*/

