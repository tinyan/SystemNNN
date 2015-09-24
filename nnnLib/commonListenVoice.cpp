//
// CommonSelectObject.cpp
//


#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"
#include "..\nyanLib\include\allGraphics.h"
#include "..\nyanLib\include\myFile.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"
#include "..\nnnUtilLib\nnnButtonStatus.h"
//#include "..\nnnUtilLib\selectObjectSetup.h"

#include "..\nnnUtilLib\Myfont.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"
#include "..\nnnUtilLib\commonRadioButtonGroup.h"

#include "..\nnnUtilLib\commonBackButton.h"
#include "..\nnnUtilLib\commonUpDownButtonGroup.h"
#include "..\nnnUtilLib\commonUpDownBack.h"

#include "..\nnnUtilLib\superButtonPicture.h"
#include "..\nnnUtilLib\nameList.h"

#include "..\nnnUtilLib\mymessage.h"

#include "commonMode.h"
#include "commonSystemParamName.h"


#include "commonSystemSoundName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"


#include "commonListenVoice.h"

#include "commonKeyList.h"

char CCommonListenVoice::m_defaultUnknownVoice[] = "？？？";
char CCommonListenVoice::m_defaultUnknownVoice1[] = "???";


CCommonListenVoice::CCommonListenVoice(CGameCallBack* lpGame,int extMode) : CCommonGeneral(lpGame)
{
	SetClassNumber(LISTENVOICE_MODE);
	LoadSetupFile("ListenVoice",256);

	int codeByte = CMyFont::m_codeByte;

	m_message = m_game->GetMyMessage();

	GetBackExecSetup();
	GetAllPrintSetup();
	m_mustAllPrintFlag = TRUE;

	m_charaVoiceFilename = NULL;
	m_charaVoiceFileNumber = 0;
	LoadCharaVoiceFilename();

	GetInitGameString(&m_filenameBG,"filenameBG");

	m_voiceCharaNumber = 1;
	GetInitGameParam(&m_voiceCharaNumber,"voiceCharaNumber");

	m_voiceList = new CNameList*[m_voiceCharaNumber];
	m_voiceNumber = new int[m_voiceCharaNumber];
	m_voiceTypeOrVar = new int*[m_voiceCharaNumber];
	m_voiceFlag = new int*[m_voiceCharaNumber];
	m_charaVoiceRange = new int*[m_voiceCharaNumber];

	int errorLimit = 0;

	m_unknownVoice = m_defaultUnknownVoice;
	if (codeByte == 1)
	{
		m_unknownVoice = m_defaultUnknownVoice1;
	}
	GetInitGameString(&m_unknownVoice,"unknownVoice");


	for (int i=0;i<m_voiceCharaNumber;i++)
	{
		m_voiceList[i] = new CNameList();
		char filename[256];
		sprintf_s(filename,"nya\\charaVoiceList%d.xtx",i+1);
		m_voiceList[i]->LoadFile(filename);

		m_voiceNumber[i] = m_voiceList[i]->GetNameKosuu() / 3;
		m_voiceTypeOrVar[i] = new int[ m_voiceNumber[i] * 1 ];
		m_charaVoiceRange[i] = new int[ m_voiceNumber[i] * 2 ];

		for (int k=0;k<m_voiceNumber[i];k++)
		{
			m_charaVoiceRange[i][k*2+0] = 0;
			m_charaVoiceRange[i][k*2+1] = 0;

			LPSTR name = m_voiceList[i]->GetName(k*3);
			char c = *name;
			if ((c >= '0') && (c<='9'))
			{
				m_voiceTypeOrVar[i][k] = atoi(name);


				int st = 0;
				int ed = 0;

				LPSTR filename = m_voiceList[i]->GetName(k*3+1);
				st = SearchFilename(filename);
				if (st != -1)
				{
					ed = st;
					short* ptr = (short*)(m_charaVoiceFilename + st * (8+8) + 10);
					short pre = *ptr;
					st -= pre;
					int ed0 = ed;

					for (int p=ed0+1;p<m_charaVoiceFileNumber;p++)
					{
						short* ptr2 = (short*)(m_charaVoiceFilename + p * (8+8) + 10);
						short d = *ptr2;
						if (d == 0) break;
						ed++;
					}

					m_charaVoiceRange[i][k*2+0] = st;
					m_charaVoiceRange[i][k*2+1] = ed;
				}
				else
				{
					if (errorLimit < 3)
					{
						char errorMessage[256];
						if (codeByte == 2)
						{
							sprintf_s(errorMessage,256,"音声ファイル(%s)がみつかりません。\nボイスキャラ番号=%d\nボイス番号%d",filename,i+1,k+1);
						}
						else
						{
							sprintf_s(errorMessage,256,"voicefile(%s)not found.\nvoiceCharaNumber=%d\nvoiceNumber%d",filename,i+1,k+1);
						}
						MessageBox(NULL,errorMessage,"ERROR",MB_ICONEXCLAMATION | MB_OK);
						errorLimit++;
					}
				}
			}
			else
			{
				int varNumber = m_game->GetVarNumber(name);
				m_voiceTypeOrVar[i][k] = varNumber;
				if (varNumber == -1)
				{
					if (errorLimit < 3)
					{
						char errorMessage[256];
						if (codeByte == 2)
						{
							sprintf_s(errorMessage,256,"ボイス制御変数(%s)がみつかりません。\nボイスキャラ番号=%d\nボイス番号%d",name,i+1,k+1);
						}
						else
						{
							sprintf_s(errorMessage,256,"voiceControlVar(%s)not found.\nvoiceCharaNumber=%d\nvoiceNumber%d",name,i+1,k+1);
						}
						MessageBox(NULL,errorMessage,"ERROR",MB_ICONEXCLAMATION | MB_OK);
						errorLimit++;
					}
				}
			}
		}

		m_voiceFlag[i] = new int[ m_voiceNumber[i] ];
	}


	m_voicePerPage = 10;
	GetInitGameParam(&m_voicePerPage,"voicePerPage");

	CreateBackButton();
	CreateUpDownButton();
	CreateUpDownBack();



	m_listPrintX = 100;
	m_listPrintY = 200;
	m_listNextX = 30;
	m_listNextY = 50;
	m_listSizeX = 300;
	m_listSizeY = 40;

	m_radio = NULL;
	if (m_voiceCharaNumber > 1)
	{
		m_radio = new CCommonRadioButtonGroup(m_setup,"voiceChara",NULL,m_voiceCharaNumber);
		for (int i=0;i<m_voiceCharaNumber;i++)
		{
			CPicture* lpPic = CSuperButtonPicture::GetPicture(3+i);
			m_radio->SetPicture(lpPic,i,-1);
		}
	}

	GetDisableQuickButtonSetup();
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();
	GetAddLayerSetup();
	GetAnimeLayerSetup();
}



CCommonListenVoice::~CCommonListenVoice()
{
	End();
}

void CCommonListenVoice::End(void)
{
	ENDDELETECLASS(m_radio);

	DELETEARRAY(m_charaVoiceFilename);

	if (m_charaVoiceRange != NULL)
	{
		for (int i=0;i<m_voiceCharaNumber;i++)
		{
			DELETEARRAY(m_charaVoiceRange[i]);
		}
		DELETEARRAY(m_charaVoiceRange);
	}
	if (m_voiceFlag != NULL)
	{
		for (int i=0;i<m_voiceCharaNumber;i++)
		{
			DELETEARRAY(m_voiceFlag[i]);
		}
		DELETEARRAY(m_voiceFlag);
	}

	if (m_voiceTypeOrVar != NULL)
	{
		for (int i=0;i<m_voiceCharaNumber;i++)
		{
			DELETEARRAY(m_voiceTypeOrVar[i]);
		}
		DELETEARRAY(m_voiceTypeOrVar);
	}

	DELETEARRAY(m_voiceNumber);
	if (m_voiceList != NULL)
	{
		for (int i=0;i<m_voiceCharaNumber;i++)
		{
			ENDDELETECLASS(m_voiceList[i]);
		}
		DELETEARRAY(m_voiceList);
	}
}


int CCommonListenVoice::Init(void)
{
	m_charaNumber = 0;
	LoadBackBG();

	//check voice enable etc
	for (int i=0;i<m_voiceCharaNumber;i++)
	{
		for (int k=0;k<m_voiceNumber[i];k++)
		{
			int type = m_voiceTypeOrVar[i][k];
			m_voiceFlag[i][k] = 0;
			if (type <= 0)
			{
				m_voiceFlag[i][k] = 1;
			}
			else if (type <= 1)
			{
				char* filename = m_voiceList[i]->GetName(k*3);

				int st = m_charaVoiceRange[i][k*2];
				int ed = m_charaVoiceRange[i][k*2+1];

				//serach chara voice number
				for (int p=st;p<=ed;p++)
				{
					int* vp = (int*)(m_charaVoiceFilename + (8+8)*p + 12);
					int v = *vp;
					if (m_game->CheckCharaVoice(v))
					{
						m_voiceFlag[i][k] = 1;
						break;
					}
				}


			}
			else
			{
				if (m_game->GetVarData(type))
				{
					m_voiceFlag[i][k] = 1;
				}
			}


		}
	}

	m_page = 0;
	m_pageMax = (m_voiceNumber[m_charaNumber] + m_voicePerPage - 1) / m_voicePerPage;

	m_radio->SetRadio(m_charaNumber);
	ReloadButtonPic();
	m_radio->Init(m_charaNumber);
	m_updownBack->Init();



	return -1;
}


int CCommonListenVoice::Calcu(void)
{

	int udb = m_updownBack->Calcu(m_inputStatus);

	if (udb != NNNBUTTON_NOTHING)
	{
		int nm = ProcessUpDownBack(udb);
		if (nm >= 0)
		{
			if (nm == 0)
			{
				return ReturnFadeOut(OMAKE_MODE);
			}
			else
			{
				if (nm == 1)
				{
					if (m_page>0)
					{
						m_page--;
					}
				}
				else
				{
					if (m_page<m_pageMax-1)
					{
						m_page++;
					}
				}


				m_updownBack->Init();
				m_updownBack->SetPage(m_page);
			}
		}
	}


	m_onNumber = GetOnNumber(m_mouseStatus->GetZahyo());

	if (m_mouseStatus->CheckClick(0))
	{
		if (m_onNumber != -1)
		{
			if (m_voiceFlag[m_charaNumber][m_page*m_voicePerPage+m_onNumber])
			{
				LPSTR filename = m_voiceList[m_charaNumber]->GetName((m_page*m_voicePerPage+m_onNumber)*3+1);
				m_game->ReplayVoice(filename);
			}
		}
	}


	if (m_radio != NULL)
	{
		int rt = m_radio->Calcu(m_inputStatus);
		if (rt != -1)
		{
			int nm = ProcessButtonGroup(rt);
			if ((nm >= 0) && (nm < m_voiceCharaNumber))
			{
				m_charaNumber = nm;
				m_page = 0;
				m_pageMax = (m_voiceNumber[m_charaNumber] + m_voicePerPage - 1) / m_voicePerPage;

				m_updownBack->Init();
				m_updownBack->SetPageMax(m_pageMax);
				m_updownBack->SetPage(m_page);

				m_radio->SetRadio(nm);
				ReloadButtonPic();
				m_radio->Init(nm);


				//reset pagebutton

				return -1;
			}
		}
	}


	return -1;
}

int CCommonListenVoice::Print(void)
{
	CAreaControl::SetNextAllPrint();

	CAllGraphics::FillScreen();

	PrintBackScriptOrBG();

	int codeByte = CMyFont::m_codeByte;



	//m_message->PrintMessage(100,100,"ＬｉｓｔｅｎＶｏｉｃｅ");
	//m_game->PrintOptionButtonYoyaku();

	if (m_radio != NULL)
	{
		m_radio->Print();
	}

	if (m_updownBack != NULL)
	{
		m_updownBack->Print(TRUE);
	}

	int st = m_voicePerPage * m_page;
	int ed = st + m_voicePerPage;
	if (ed >= m_voiceNumber[m_charaNumber])
	{
		ed = m_voiceNumber[m_charaNumber];
	}
	int lp = ed - st;
	for (int i=0;i<lp;i++)
	{
		int flag = m_voiceFlag[m_charaNumber][st+i];
		POINT pt = GetListPoint(i);
		int x = pt.x;
		int y = pt.y;

		if (flag == 0)
		{
			m_message->PrintMessage(x,y,m_unknownVoice);
			/*
			if (codeByte == 2)
			{
				m_message->PrintMessage(x,y,"？？？");
			}
			else
			{
				m_message->PrintMessage(x,y,"???");
			}
			*/
		}
		else
		{
			LPSTR desc = m_voiceList[m_charaNumber]->GetName((st+i)*3+2);
			m_message->PrintMessage(x,y,desc);

			if (i == m_onNumber)
			{
				CAllGeo::TransBoxFill(x,y,m_listSizeX,m_listSizeY,120,192,64,50);
			}
		}
	}


	return -1;
}


POINT CCommonListenVoice::GetListPoint(int n)
{
	POINT pt;
	pt.x = m_listPrintX + m_listNextX * n;
	pt.y = m_listPrintY + m_listNextY * n;
	return pt;
}




void CCommonListenVoice::FinalExitRoutine(void)
{

	if (m_exitModeFlag)
	{
//		m_game->SetYoyaku();
	}
}

int CCommonListenVoice::EndMode(void)
{
	return -1;

	/*
	if (m_exitModeFlag)
	{
		m_game->SetVarData(m_selectPlaceResultVarNumber,m_selectedNumber + 1);


		m_game->SetYoyaku();
	}
	*/

}




void CCommonListenVoice::CreateStartScreen(void)
{
	Print();
}



void CCommonListenVoice::LoadCharaVoiceFilename(void)
{
	FILE* file =  CMyFile::Open("spt\\voiceflag.tbl","rb");
	if (file != NULL)
	{
		char header[16];
		fread(header,sizeof(char),16,file);

		fread(&m_charaVoiceFileNumber,sizeof(int),1,file);
		int dmy[3];
		fread(dmy,sizeof(int),3,file);

		m_charaVoiceFilename = new char[m_charaVoiceFileNumber * (8+8)+32];
		fread(m_charaVoiceFilename,sizeof(char),m_charaVoiceFileNumber * (8+8),file);
		fclose(file);
	}
}

int CCommonListenVoice::SearchFilename(LPSTR filename)
{
	int st = 0;
	int ed = m_charaVoiceFileNumber-1;
	if (ed<0) return -1;
	int center = (st+ed)/2;

	int limit = 100;
	while (limit>0)
	{
		char* ptr = m_charaVoiceFilename + center * (8+8);
		int f = _stricmp(filename,ptr);
		if (f == 0)
		{
			return center;
		}

		if (st >= ed) return -1;

		if (f < 0)
		{
			ed = center;
			center = (st+ed) / 2;
		}
		else
		{
			st = center;
			center = (st+ed) / 2;
		}

		if (st == ed-1)
		{
			char* ptr2 = m_charaVoiceFilename + ed * (8+8);
			int f2 = _stricmp(filename,ptr2);
			if (f2 == 0)
			{
				return ed;
			}
		}


		limit--;
	}

	OutputDebugString("\n\nlimit over error*****\n");
	return -1;
}


void CCommonListenVoice::ReloadButtonPic(void)
{
	if (m_radio != NULL)
	{
		int sel = m_radio->GetRadio();

		for (int i=0;i<m_voiceCharaNumber;i++)
		{
			int st = 0;
			if (i == sel) st = 1;

			CPicture* lpPic = m_radio->GetPicture(i,st);
			LPSTR name = m_radio->GetFileName(i,st);
			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);
		}

	}

	LoadUpDownButtonPic();
	LoadBackButtonPic();



}


int CCommonListenVoice::GetOnNumber(POINT pt)
{
	//page
	int mx = m_voiceNumber[m_charaNumber] -  m_page * m_voicePerPage;
	if (mx>m_voicePerPage) mx = m_voicePerPage;

	for (int i=0;i<mx;i++)
	{
		POINT pt2 = GetListPoint(i);
		int dx = pt.x - pt2.x;
		int dy = pt.y - pt2.y;

		if ((dx>=0) && (dx<m_listSizeX) && (dy>=0) && (dy<m_listSizeY))
		{
			return i;
		}


	}

	return -1;
}



