//
// commonSelectScene.cpp
//


#include <windows.h>


#include <stdio.h>


#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\nnnButtonStatus.h"
#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"

#include "..\nnnUtilLib\sceneVoice.h"
#include "..\nnnUtilLib\sceneList.h"

#include "..\nnnUtilLib\sceneDataControl.h"


#include "commonSystemSoundName.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "gameCallBack.h"

#include "commonGeneral.h"




#include "commonSelectScene.h"

#include "..\nnnUtilLib\myMessage.h"
#include "..\nnnUtilLib\suuji.h"

#include "..\nnnUtilLib\pagePrint.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonBackButton.h"
#include "..\nnnUtilLib\commonUpdownButtonGroup.h"
#include "..\nnnUtilLib\commonUpdownBack.h"



char CCommonSelectScene::m_defaultBGFileName[] = "scene_bg";
char CCommonSelectScene::m_defaultAddFileName[] = "scene_bg_title";
char CCommonSelectScene::m_defaultFont1FileName[] = "ta_font_cg1";
char CCommonSelectScene::m_defaultFont3FileName[] = "ta_font_cg1";

char CCommonSelectScene::m_defaultUpFileName[] = "ta_bgm_cur1";
char CCommonSelectScene::m_defaultDownFileName[] = "ta_bgm_cur2";

char CCommonSelectScene::m_defaultCursorFileName[] = "ta_cg_cur";

char CCommonSelectScene::m_defaultFutaFileName[] = "ta_futa1";

CCommonSelectScene::CCommonSelectScene(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(SELECTSCENE_MODE);
//	m_classNumber = SELECTSCENE_MODE;
//	m_fillColorR = 255;
//	m_fillColorG = 255;
//	m_fillColorB = 255;
//	m_nextMode = LOGO_MODE;
	m_sceneCommandFlag = FALSE;
	m_message = m_game->GetMyMessage();
	
	m_sceneVoice = m_game->GetSceneVoice();
	m_sceneList = m_game->GetSceneList();
	m_sceneDataControl = m_game->GetSceneDataControl();


	LoadSetupFile("SelectScene",32);

	int listCheckFlag = 1;
	GetInitGameParam(&listCheckFlag,"listCheckFlag");
	
	if (listCheckFlag)
	{
		CheckSceneList();
	}



	m_sceneCharaKosuu = 1;
	if (m_sceneDataControl != NULL)
	{
		m_sceneCharaKosuu = m_sceneDataControl->GetSceneCharaKosuu();
	}

	GetBackExecSetup();

	m_superMode = 0;
	GetInitGameParam(&m_superMode,"superButtonFlag");

	m_scenePianoSoundFlag = 0;
	GetInitGameParam(&m_scenePianoSoundFlag,"scenePianoSoundFlag");

	m_filenameBG = m_defaultBGFileName;
	GetInitGameString(&m_filenameBG,"filenameBG");

	m_blockKosuuX = 4;
	m_blockKosuuY = 3;

	GetInitGameParam(&m_blockKosuuX,"blockNumberX");
	GetInitGameParam(&m_blockKosuuY,"blockNumberY");

	m_picMustPrintPercent = 0;
	GetInitGameParam(&m_picMustPrintPercent,"picMustPrintPercent");

	m_filenameAdd = m_defaultAddFileName;
	m_addPicFlag = 0;
	m_addPicPrintPercent = 0;	//特例:0はマスクなし100% それ以外はマスクあり透過
	m_addPicPrintX = 217;
	m_addPicPrintY = 26;
	m_addPicSizeX = 355;
	m_addPicSizeY = 22;
	m_addPicSrcKosuuX = 1;
	m_addPicSrcKosuuY = m_sceneCharaKosuu;


	m_exitStopVoiceFlag = 0;
	GetInitGameParam(&m_exitStopVoiceFlag,"exitStopVoiceFlag");
	m_exitStopVoiceFadeOutTime = 0;
	GetInitGameParam(&m_exitStopVoiceFadeOutTime,"exitStopVoiceFadeOutTime");

	

	GetInitGameParam(&m_addPicFlag,"addPicFlag");
	m_addPic = NULL;
	if (m_addPicFlag != 0)
	{
		GetInitGameParam(&m_addPicPrintPercent,"addPicPrintPercent");
		GetInitGameParam(&m_addPicPrintX,"addPicPrintX");
		GetInitGameParam(&m_addPicPrintY,"addPicPrintY");
		GetInitGameParam(&m_addPicSizeX,"addPicSizeX");
		GetInitGameParam(&m_addPicSizeY,"addPicSizeY");
		GetInitGameParam(&m_addPicSrcKosuuX,"addPicSrcNumX");
		GetInitGameParam(&m_addPicSrcKosuuY,"addPicSrcNumY");
		GetInitGameString(&m_filenameAdd,"filenameAdd");

		m_addPic = new CPicture();
		char filename[256];
		wsprintf(filename,"sys\\%s",m_filenameAdd);
		m_addPic->LoadDWQ(filename);
	}


	m_miniPic = NULL;
	m_miniPic = new CPicture*[m_blockKosuuX*m_blockKosuuY];
	for (int i=0;i<m_blockKosuuX*m_blockKosuuY;i++)
	{
		m_miniPic[i] = new CPicture();
	}
	m_miniPicState = new int[m_blockKosuuX*m_blockKosuuY];

	m_totalPercentPrintFlag = 1;
	GetInitGameParam(&m_totalPercentPrintFlag,"totalPercentPrintFlag");
	m_suuji = NULL;
	if (m_totalPercentPrintFlag)
	{
		LPSTR font1Name = m_defaultFont1FileName;
		GetInitGameString(&font1Name,"fileNameTotalPercent");
		CPicture* suujiPic = m_game->GetSystemPicture(font1Name);

		m_fontSizeX1 = 16;
		m_fontSizeY1 = 22;
		GetInitGameParam(&m_fontSizeX1,"totalPercentFontSizeX");
		GetInitGameParam(&m_fontSizeY1,"totalPercentFontSizeY");
		m_fontNextX1 = m_fontSizeX1;
		GetInitGameParam(&m_fontNextX1,"totalPercentFontNextX");

		m_totalPercentPrintX = 688;
		m_totalPercentPrintY = 25;
		GetInitGameParam(&m_totalPercentPrintX,"totalPercentPrintX");
		GetInitGameParam(&m_totalPercentPrintY,"totalPercentPrintY");

		m_suuji = new CSuuji(suujiPic,m_fontSizeX1,m_fontSizeY1,3,m_fontNextX1);
	}


	CPicture* lpBG = m_commonBG;
	if (m_backScriptFlag) lpBG = NULL;

	m_pagePrint = new CPagePrint(m_setup,lpBG);


//	m_pagePrintFlag = 0;
//	m_pageMaxPrintFlag = 0;
//	m_slashPrintFlag = 0;

//	GetInitGameParam(&m_pagePrintFlag,"pagePrintFlag");
//	m_suuji3 = NULL;
	/*
	if (m_pagePrintFlag)
	{
		int keta = 2;

		m_fontSizeX3 = 21;
		m_fontSizeY3 = 27;

		GetInitGameParam(&m_fontSizeX3,"pageFontSizeX");
		GetInitGameParam(&m_fontSizeY3,"pageFontSizeY");
		m_fontNextX3 = m_fontSizeX3;
		GetInitGameParam(&m_fontNextX3,"pageFontNextX");

		m_pagePrintX = 0;
		m_pagePrintY = 0;

		GetInitGameParam(&m_pagePrintX,"pagePrintX");
		GetInitGameParam(&m_pagePrintY,"pagePrintY");

		LPSTR font3Name = m_defaultFont3FileName;
		GetInitGameString(&font3Name,"fileNamePageFont");
		CPicture* suujiPic3 = m_game->GetSystemPicture(font3Name);
		m_suuji3 = new CSuuji(suujiPic3,m_fontSizeX3,m_fontSizeY3,2,m_fontNextX3);

		m_suujiPic3 = suujiPic3;


		GetInitGameParam(&m_pageMaxPrintFlag,"pageMaxPrintFlag");

		if (m_pageMaxPrintFlag)
		{
			m_pageMaxPrintX = m_pagePrintX + m_fontNextX3 * (keta+1);
			m_pageMaxPrintY = m_pagePrintY;

			GetInitGameParam(&m_pageMaxPrintX,"pageMaxPrintX");
			GetInitGameParam(&m_pageMaxPrintY,"pageMaxPrintY");

			GetInitGameParam(&m_slashPrintFlag,"slashPrintFlag");
			if (m_slashPrintFlag)
			{
				m_slashPrintX = m_pagePrintX + m_fontNextX3 * keta;
				m_slashPrintY = m_pagePrintY;

				GetInitGameParam(&m_slashPrintX,"slashPrintX");
				GetInitGameParam(&m_slashPrintY,"slashPrintY");
			}
		}

	}
*/


	m_smTransFlag = 0;
	GetInitGameParam(&m_smTransFlag,"miniPicTransFlag");

/*
	LPSTR filenameUp = m_defaultUpFileName;
	GetInitGameString(&filenameUp,"fileNameUp");
	LPSTR filenameDown = m_defaultDownFileName;
	GetInitGameString(&filenameDown,"fileNameDown");

	CPicture* pic = m_game->GetSystemPicture(filenameUp);
	CPicture* pic2 = m_game->GetSystemPicture(filenameDown);

	int updownSizeX = 41;
	int updownSizeY = 20;
	int updownAnime = 5;

	int upPrintX = 207;
	int upPrintY = 182;
	int downPrintX = 207;
	int downPrintY = 182 + 230;

	GetInitGameParam(&updownSizeX,"updownSizeX");
	GetInitGameParam(&updownSizeY,"updownSizeY");
	GetInitGameParam(&updownAnime,"updownAnime");
	GetInitGameParam(&upPrintX,"upPrintX");
	GetInitGameParam(&upPrintY,"upPrintY");
	GetInitGameParam(&downPrintX,"downPrintX");
	GetInitGameParam(&downPrintY,"downPrintY");
	m_updown = new CUpDownButtonGroup();
//	m_updown->CreateUpDownButton(pic,pic2,207,182,207,182+230,41,20,TRUE,m_commonBG,FALSE,5);
	m_updown->CreateUpDownButton(pic,pic2,upPrintX,upPrintY,downPrintX,downPrintY,updownSizeX,updownSizeY,TRUE,m_commonBG,FALSE,updownAnime);

*/

	m_selectPrintMode = 1;
	GetInitGameParam(&m_selectPrintMode,"selectPrintMode");

	m_selectPercent = 50;
	GetInitGameParam(&m_selectPercent,"selectPercent");

	if (m_selectPrintMode == 1)
	{
		m_selectColorR = 230;
		m_selectColorG = 0;
		m_selectColorB = 50;

		GetInitGameParam(&m_selectColorR,"cursorColorR");
		GetInitGameParam(&m_selectColorG,"cursorColorG");
		GetInitGameParam(&m_selectColorB,"cursorColorB");
	}
	else if (m_selectPrintMode == 2)
	{
		LPSTR cursorName = m_defaultCursorFileName;
		GetInitGameString(&cursorName,"fileNameCursor");
		m_cursorPic = m_game->GetSystemPicture(cursorName);

		m_cursorPrintType = 0;
		GetInitGameParam(&m_cursorPrintType,"cursorPrintType");
	}



//	CPicture* suujiPic = m_game->GetSystemPicture("ta_font_cg1");
//	m_suuji = new CSuuji(suujiPic,16,22,3);

///	m_cursorPic = m_game->GetSystemPicture("ta_cg_cur");

	m_printX = 85;
	m_printY = 113;
	m_nextX = 166;
	m_nextY = 124;
	m_sizeX = 133;
	m_sizeY = 100;

	m_picPrintX = 0;
	m_picPrintY = 0;

	GetInitGameParam(&m_printX,"printX");
	GetInitGameParam(&m_printY,"printY");
	GetInitGameParam(&m_nextX,"nextX");
	GetInitGameParam(&m_nextY,"nextY");
	GetInitGameParam(&m_sizeX,"sizeX");
	GetInitGameParam(&m_sizeY,"sizeY");

	m_picSizeX = m_sizeX;
	m_picSizeY = m_sizeY;

	GetInitGameParam(&m_picPrintX,"picPrintX");
	GetInitGameParam(&m_picPrintY,"picPrintY");

	GetInitGameParam(&m_picSizeX,"picSizeX");
	GetInitGameParam(&m_picSizeY,"picSizeY");


	m_cursorSizeX = m_picSizeX;
	m_cursorSizeY = m_picSizeY;
	m_cursorPrintX = m_picPrintX;
	m_cursorPrintY = m_picPrintY;

	GetInitGameParam(&m_cursorPrintX,"cursorPrintX");
	GetInitGameParam(&m_cursorPrintY,"cursorPrintY");
	GetInitGameParam(&m_cursorSizeX,"cursprSizeX");
	GetInitGameParam(&m_cursorSizeY,"cursprSizeY");






	m_nowSelectNumber = -1;
	m_maeSelectNumber = -1;


	LPSTR futaName = m_defaultFutaFileName;
	GetInitGameString(&futaName,"fileNameFuta");

	m_futaPrintFlag = 1;
	GetInitGameParam(&m_futaPrintFlag,"futaPrintFlag");
	if (m_futaPrintFlag)
	{
		m_futaPic = m_game->GetSystemPicture(futaName);
	}

//	m_futaPic = m_game->GetSystemPicture("ta_futa1");

//	m_kosuuPerPage = 12;
	m_kosuuPerPage = m_blockKosuuX * m_blockKosuuY;

	m_length = 8;

	m_page = 0;

	m_selectSound = 1;
	GetInitGameParam(&m_selectSound,"selectSound");

	m_modeBGMNumber = 1;
	GetBGMSetup();
	GetFadeInOutSetup();
	GetEnterExitVoiceFileName();

	CreateBackButton();
	CreateUpDownButton();
	CreateUpDownBack();


//	GetInitGameParam(&m_fillColorR,"fillColorR");
//	GetInitGameParam(&m_fillColorG,"fillColorG");
//	GetInitGameParam(&m_fillColorB,"fillColorB");

//	GetInitGameParam(&m_nextMode,"nextMode");
}



CCommonSelectScene::~CCommonSelectScene()
{
	End();
}

void CCommonSelectScene::End(void)
{
	DELETEARRAY(m_miniPicState);

	if (m_miniPic != NULL)
	{
		for (int i=0;i<m_blockKosuuX*m_blockKosuuY;i++)
		{
			ENDDELETECLASS(m_miniPic[i]);
		}
		DELETEARRAY(m_miniPic);
	}


	ENDDELETECLASS(m_addPic);
//	ENDDELETECLASS(m_updown);
//	ENDDELETECLASS(m_suuji3);
	ENDDELETECLASS(m_suuji);

	ENDDELETECLASS(m_pagePrint);
}



int CCommonSelectScene::Init(void)
{
	m_game->SetLayerOff();

	m_game->StopScriptSoundAndVoice();

	m_game->ClearWork();
	for (int i=100;i<200;i++)
	{
		m_game->SetVarData(i,0);
	}
	for (int i=300;i<1000;i++)
	{
		m_game->SetVarData(i,0);
	}

	m_game->SetDefaultFrameRate();

	m_sceneCommandFlag = FALSE;

	m_sceneCharaNumber = 0;
	if (m_sceneDataControl != NULL)
	{
		m_sceneCharaNumber = m_sceneDataControl->GetSceneCharaNumber();
	}
	m_sceneKosuu = 0;
	if (m_sceneDataControl != NULL) m_sceneKosuu = m_sceneDataControl->GetSceneKosuu(m_sceneCharaNumber);

	m_pageMax = ((m_sceneKosuu-1) / m_kosuuPerPage) + 1;
	if (m_page>=m_pageMax) m_page = m_pageMax - 1;
	if (m_page<0) m_page = 0;

	SetUpDownZahyo();
	m_updown->SetPageMax(m_pageMax);
	m_updown->SetPage(m_page);


//	int kosuu = 0;
	for (int i=0;i<m_sceneKosuu;i++)
	{
		m_sceneFlag[i] = 0;
		m_hSceneFlag[i] = 0;
		if (m_sceneDataControl != NULL)
		{
			m_sceneFlag[i] = m_sceneDataControl->CheckGetScene(m_sceneCharaNumber,i);
			m_hSceneFlag[i] = m_sceneDataControl->CheckHScene(m_sceneCharaNumber,i);
		}
//		if (m_sceneFlag[i]) kosuu++;
	}

//	int ps = (100 * kosuu) / m_sceneKosuu;
//	if (ps<0) ps = 0;
//	if (ps>100) ps = 100;
//	if ((ps == 0) && (kosuu>0)) ps = 1;
//	if ((ps == 100) && (kosuu < m_sceneKosuu)) ps = 99;


	m_percent = 0;
	if (m_sceneDataControl != NULL) 	m_percent = m_sceneDataControl->GetScenePercent(m_sceneCharaNumber);

	LoadBackCG();

	LoadUpDownButtonPic();

	LoadBackButtonPic();

//	m_commonParts->LoadDWQ("sys\\futa1");

	m_nowSelectNumber = -1;
	m_maeSelectNumber = -1;

	m_yoyakuVoiceNumber = -1;
	m_voiceStartWait = 0;


	//m_back->Init();
	SetBackButtonZahyo();

	m_updownBack->Init();

	m_selectedNumber = -1;

//	CPicture* pic = m_game->GetEffectPicture(1);
//	pic->LoadDWQ("sys\\scn_tip");

//	m_game->PlayBGM(13);






	m_sceneVoiceNumber = -1;
	m_startupWait = 3;

//	m_game->PlayBGM(0);

	return -1;
}

int CCommonSelectScene::Calcu(void)
{

	POINT pt = m_mouseStatus->GetZahyo();
	int mouseX = pt.x;
	int mouseY = pt.y;


	if (m_selectedNumber >= 0)
	{
		m_count--;
		if (m_count<=0)
		{
			m_sceneCommandFlag = TRUE;
			return ReturnFadeOut(-1);

//			return OMAKE_MODE;	//エラーです！！！

			return -1;
		}
		return -1;
	}


	int rt = m_updownBack->Calcu(m_inputStatus);


	if (rt != NNNBUTTON_NOTHING)
	{
		int nm = ProcessUpDownBack(rt);
		int st = CCommonButton::GetButtonStatus(rt);

		if (nm == 0)
		{
			return ReturnFadeOut(m_backMode);
		}
		else if (nm > 0)
		{
			m_selectedNumber = -1;

			m_page = nm - 1;
			m_startupWait = 3;
			LoadBackCG();
			CAreaControl::SetNextAllPrint();
			return -1;
		}

		if (st == NNNBUTTON_STARTCLICK)
		{
			int nm = CCommonButton::GetButtonData(rt);
			 m_selectedNumber = -2;
		}
	}


	m_maeSelectNumber = m_nowSelectNumber;
	m_nowSelectNumber = GetOnScene(mouseX,mouseY);

	if (m_mouseStatus->CheckClick())
	{
		if (m_nowSelectNumber != -1)
		{
			m_selectedNumber = m_nowSelectNumber;
			m_count = m_length;
			if (m_selectSound != -1)
			{
				m_game->PlaySystemSound(m_selectSound-1);
			}
			return -1;
		}
	}

	if (m_startupWait>0)
	{
		m_startupWait--;
	}
	else
	{
		if ((m_nowSelectNumber != m_maeSelectNumber) && (m_nowSelectNumber != -1))
		{
			if (m_scenePianoSoundFlag)
			{
				m_game->PlaySystemPiano(m_nowSelectNumber);
			}
		}
	}



	if (m_nowSelectNumber != -1)
	{
		int scene = m_page * (m_blockKosuuX * m_blockKosuuY) + m_nowSelectNumber;
///		int buf[16];
///		int kosuu = m_game->GetScenePlayer(scene,buf);
///		m_game->SetSceneTip(mouseX+32,mouseY+32,kosuu,buf);
	}

	if (m_nowSelectNumber != m_maeSelectNumber)
	{
		if (m_nowSelectNumber != -1)
		{
			int scene = m_page * (m_blockKosuuX * m_blockKosuuY) +m_nowSelectNumber;
//			int subKosuuMax = m_game->GetSceneSubKosuuMax(scene);
//			int subKosuu = m_game->GetSceneSubKosuu(scene);
			if (m_startupWait == 0)
			{
///				m_game->PlaySystemVoice(scene);
				m_yoyakuVoiceNumber = scene;
				m_voiceStartWait = 16;
			}
			m_sceneVoiceNumber = scene;


		}
		else
		{
			if (m_sceneVoiceNumber != -1)
			{
				if (m_yoyakuVoiceNumber == -1)
				{
					m_game->StopVoice();
//					m_game->PlaySystemVoice(-1);
				}
				m_sceneVoiceNumber = -1;
				m_yoyakuVoiceNumber = -1;
			}
		}
	}

	if (m_yoyakuVoiceNumber != -1)
	{
		if (m_voiceStartWait>0)
		{
			m_voiceStartWait--;
		}
		else
		{
			LPSTR filename = m_sceneVoice->GetSceneVoiceFileName(m_sceneCharaNumber,m_yoyakuVoiceNumber);
			if (filename != NULL)
			{
				if (m_game->CheckVoiceOffByName(filename) == FALSE)
				{
					m_game->ReplayVoice(filename);
				}
			}
			m_yoyakuVoiceNumber = -1;
		}
	}

	return -1;
//	return m_nextMode;
}

int CCommonSelectScene::Print(void)
{
	PrintBackScriptOrBG();

//	GetBackExecSetup();

	BOOL b = CAreaControl::CheckAllPrintMode();

	if (m_backScriptFlag)
	{
		if (m_totalPercentPrintFlag) PrintTotalPercent();
		if (m_addPicFlag) PutAddPic();
//		if (m_pagePrintFlag) PrintPage();
		m_pagePrint->Print(m_page+1,m_pageMax);

		PrintAllMiniPic();
	}

	m_updownBack->Print(TRUE);

	for (int j=0;j<m_blockKosuuY;j++)
	{
		for (int i=0;i<m_blockKosuuX;i++)
		{
			int k = i + j * m_blockKosuuX;
			BOOL bb = b;
			if (m_nowSelectNumber != m_maeSelectNumber)
			{
				if ((k == m_nowSelectNumber) || (k == m_maeSelectNumber))
				{
					bb = TRUE;
				}
			}
		
			if (k == m_selectedNumber) bb = TRUE;

			if (bb)
			{
				int putX = m_printX + m_nextX * i;
				int putY = m_printY + m_nextY * j;
				int sizeX = m_sizeX;
				int sizeY = m_sizeY;

				int scene = m_page * (m_blockKosuuX * m_blockKosuuY) + k;


				if (m_sceneFlag[scene] == FALSE)	//dummy
				{
					if (scene<m_sceneKosuu)
					{
						if (m_backScriptFlag == 0)
						{
							m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
						}
//						m_commonParts->Blt(putX,putY,0,0,sizeX,sizeY,FALSE);
					}
				}
				else
				{
					if (m_backScriptFlag == 0)
					{
						m_commonBG->Blt(putX,putY,putX,putY,sizeX,sizeY,FALSE);
					}
/////					CheckAndPutHeart(scene);

					if ((k == m_nowSelectNumber) || (k == m_selectedNumber))
					{
						if ((m_selectedNumber == -1) || (m_count & 1))
						{
//							CPicture::TransBox(putX,putY,sizeX,sizeY,0,128,64,50);
//							CPicture::TransBox(putX,putY,sizeX,sizeY,230,0,255,50);
//							m_cursorPic->AddBlt(putX-1,putY-1,0,0,sizeX+2,sizeY+1);
							int putX1 = putX + m_cursorPrintX;
							int putY1 = putY + m_cursorPrintY;
							int sizeX1 = m_cursorSizeX;
							int sizeY1 = m_cursorSizeY;



							if (m_selectPrintMode == 1)
							{
								CAllGeo::TransBoxFill(putX1,putY1,sizeX1,sizeY1,m_selectColorR,m_selectColorG,m_selectColorB,m_selectPercent);
							}
							else if (m_selectPrintMode == 2)
							{
								if (m_cursorPrintType == 0)
								{
									m_cursorPic->Blt(putX1,putY1,0,0,sizeX1,sizeY1,TRUE);
								}
								else if (m_cursorPrintType == 1)
								{
									m_cursorPic->TransLucentBlt3(putX1,putY1,0,0,sizeX1,sizeY1,m_selectPercent);
								}
								else if (m_cursorPrintType == 2)
								{
									m_cursorPic->AddBlt(putX1,putY1,0,0,sizeX1,sizeY1);
								}
//								m_cursorPic->Blt(putX,putY,0,0,sizeX,sizeY,TRUE);
							}



						}
					}

					if (b == FALSE)
					{
						CAreaControl::AddArea(putX,putY,sizeX,sizeY);
					}
				}
			}
		}
	}


	return -1;
}


void CCommonSelectScene::LoadBackCG(void)
{
	int i,j;
	char filename[256];

	if (m_backScriptFlag == 0)
	{
		wsprintf(filename,"sys\\%s",m_filenameBG);
		m_commonBG->LoadDWQ(filename);
		m_commonBG->Put(0,0,FALSE);
	}


	for (j=0;j<m_blockKosuuY;j++)
	{
		for (i=0;i<m_blockKosuuX;i++)
		{
			int n0 = j * m_blockKosuuX + i;
			int n = m_page * (m_blockKosuuX * m_blockKosuuY) + n0;

			if (n < m_sceneKosuu)
			{
				if (m_futaPrintFlag) m_miniPicState[n0] = 0;

				BOOL fl = FALSE;
				if (m_sceneDataControl != NULL)
				{
					fl = m_sceneDataControl->CheckGetScene(m_sceneCharaNumber,n);
				}

//				if (m_game->CheckGetScene(m_sceneCharaNumber,n))
				if (fl)
				{
					m_miniPicState[n0] = 1;
					LPSTR name = m_sceneVoice->GetSceneFileName(m_sceneCharaNumber,n);

					wsprintf(filename,"sys\\sc\\%s",name);
					m_miniPic[n0]->LoadDWQ(filename);
				}
				else
				{
					if (m_picMustPrintPercent != 0)
					{
						m_miniPicState[n0] = 2;

						LPSTR name = m_sceneVoice->GetSceneFileName(m_sceneCharaNumber,n);

						wsprintf(filename,"sys\\sc\\%s",name);
						m_miniPic[n0]->LoadDWQ(filename);
					}
				}
			}
			else
			{
				m_miniPicState[n0] = -1;
			}
		}
	}

	if (m_backScriptFlag == 0)
	{
		PrintAllMiniPic();

		//put percent
		if (m_totalPercentPrintFlag)
		{
			PrintTotalPercent();
		}


		//put titlebar?
		if (m_addPicFlag)
		{
			PutAddPic();
		}

		//put page
		//page
//		if (m_pagePrintFlag)
//		{
//			//PrintPage();
//		}
		m_pagePrint->Print(m_page+1,m_pageMax);

		m_commonBG->GetScreen();

	}

}


int CCommonSelectScene::GetOnScene(int mouseX,int mouseY)
{
	int x = mouseX - m_printX;
	int y = mouseY - m_printY;

	if ((x<0) || (x>=m_nextX*m_blockKosuuX)) return -1;
	if ((y<0) || (y>=m_nextY*m_blockKosuuY)) return -1;

	int ax = x % m_nextX;
	int ay = y % m_nextY;
	if (ax >= m_sizeX) return -1;
	if (ay >= m_sizeY) return -1;

	int d = x / m_nextX;
	d += ((y / m_nextY) * m_blockKosuuX);
	int scene = d + m_page * (m_blockKosuuX * m_blockKosuuY);

	if ((scene<0) || (scene>=m_sceneKosuu)) return -1;
	if (m_sceneFlag[scene]) return d;

	return -1;
}



void CCommonSelectScene::CreateStartScreen(void)
{
	//menu setup?

	//script exec?

	Print();
}

void CCommonSelectScene::PutAddPic(void)
{
	int srcX = (m_sceneCharaNumber % m_addPicSrcKosuuX) * m_addPicSizeX;
	int srcY = (m_sceneCharaNumber / m_addPicSrcKosuuX) * m_addPicSizeY;

	if (m_addPicPrintPercent == 0)
	{
		m_addPic->Blt(m_addPicPrintX,m_addPicPrintY,srcX,srcY,m_addPicSizeX,m_addPicSizeY,FALSE);
	}
	else if (m_addPicPrintPercent == 100)
	{
		m_addPic->Blt(m_addPicPrintX,m_addPicPrintY,srcX,srcY,m_addPicSizeX,m_addPicSizeY,TRUE);
	}
	else
	{
		m_addPic->TransLucentBlt3(m_addPicPrintX,m_addPicPrintY,srcX,srcY,m_addPicSizeX,m_addPicSizeY,m_addPicPrintPercent);
	}
}

void CCommonSelectScene::PrintTotalPercent(void)
{
	m_suuji->Print(m_totalPercentPrintX,m_totalPercentPrintY,m_percent);
	m_suuji->Put(m_totalPercentPrintX + m_fontNextX1 * 3,m_totalPercentPrintY,12,0);
}

/*
void CCommonSelectScene::PrintPage(void)
{
	int pg = m_updown->GetPage() + 1;
	m_suuji3->Print(m_pagePrintX,m_pagePrintY,pg);


	if (m_pageMaxPrintFlag)
	{
		m_suuji3->Print(m_pageMaxPrintX,m_pageMaxPrintY,m_pageMax);
	}

	//slash?
	if (m_slashPrintFlag)
	{
		int sizeX = m_fontSizeX3;
		int sizeY = m_fontSizeY3;
		int srcX = sizeX * 11;
		int srcY = 0;

		m_suujiPic3->Blt(m_slashPrintX,m_slashPrintY,srcX,srcY,sizeX,sizeY,TRUE);
	}

}
*/


void CCommonSelectScene::PrintAllMiniPic(void)
{
	for (int j=0;j<m_blockKosuuY;j++)
	{
		for (int i=0;i<m_blockKosuuX;i++)
		{
			int n0 = j * m_blockKosuuX + i;
			int n = m_page * (m_blockKosuuX * m_blockKosuuY) + n0;

			if (n<m_sceneKosuu)
			{
				int st = m_miniPicState[n0];
				if (st != -1)
				{
					int putX = m_printX + i * m_nextX;
					int putY = m_printY + j * m_nextY;

					if (m_futaPrintFlag) m_futaPic->Put(putX,putY,TRUE);

					if (st == 1)
					{
						if (m_smTransFlag)
						{
							m_miniPic[n0]->Put(putX + m_picPrintX,putY+m_picPrintY,TRUE);
						}
						else
						{
							m_miniPic[n0]->Put(putX + m_picPrintX,putY+m_picPrintY,FALSE);
						}

						int mesKosuu = m_sceneVoice->GetSceneVoiceParaKosuu(m_sceneCharaNumber,n) - 2;
						if (mesKosuu > 0)
						{
							for (int k=0;k<mesKosuu;k++)
							{
								LPSTR mes = m_sceneVoice->GetSceneVoiceMessage(m_sceneCharaNumber,n,k);
								if (mes != NULL)
								{
									m_message->PrintMessage(putX+2,putY+2 + 16*k,mes,16,255,255,255,1,16,0);
								}
							}
						}
					}
					else if (st == 2)
					{
						if (m_picMustPrintPercent != 0)
						{
							SIZE sz = m_miniPic[n0]->GetPicSize();
							int sizeX = sz.cx;
							int sizeY = sz.cy;

							if (m_picMustPrintPercent < 0)
							{
								m_miniPic[n0]->GreyBlt(putX+m_picPrintX,putY+m_picPrintY,0,0,sizeX,sizeY,FALSE);
							}
							else
							{
								if (m_smTransFlag)
								{
									m_miniPic[n0]->TransLucentBlt3(putX+m_picPrintX,putY+m_picPrintY,0,0,sizeX,sizeY,m_picMustPrintPercent);							
								}
								else
								{
									m_miniPic[n0]->TransLucentBlt(putX+m_picPrintX,putY+m_picPrintY,0,0,sizeX,sizeY,m_picMustPrintPercent);							
								}
							}
						}
					}
				}
			}
		}
	}
}

void CCommonSelectScene::FinalExitRoutine(void)
{
	if (m_exitStopVoiceFlag)
	{
//		m_game->StopScriptSoundAndVoice();
		m_game->StopReplayVoice(m_exitStopVoiceFadeOutTime);
	}


	if (m_sceneCommandFlag)
	{
		int scene = m_page * (m_blockKosuuX * m_blockKosuuY) + m_selectedNumber;
		if (m_sceneDataControl != NULL)
		{
			m_sceneDataControl->SetSceneNumber(scene);
		}
//		m_game->SetSceneNumber(scene);
		m_game->SetDefaultFrameRate();
		m_game->SetBackScriptMode(FALSE);
			
		m_game->SetSceneMode();

//		layer on off@@@@@@@@@@@@@@@@@@@@@@@@@@


		int layerOff = m_sceneVoice->GetLayerOff(m_sceneCharaNumber,scene);
//char mes[256];
//wsprintf(mes,"layeroff = %d",layerOff);
//MessageBox(NULL,mes,"layeroff",MB_OK);
		m_game->SetLayerOff(layerOff);

		if (m_game->StartSceneMode())
		{
//MessageBox(NULL,"1","1",MB_OK);
			m_game->StopMusic();
			return;
		}

		//error
	}
}


void CCommonSelectScene::CheckSceneList(void)
{
	int ninzu1 = m_sceneList->GetSceneCharaKosuu();
	int ninzu2 = m_sceneVoice->GetScenePlayerKosuu();

	if (ninzu1 != ninzu2)
	{
		char mes[1024];
		wsprintf(mes,"spt/scene.datとnya/sceneVoice.xtxの登録人数が違います\n\nscene.dat=%d\nsceneVoice.xtx=%d",ninzu1,ninzu2);
		MessageBox(NULL,mes,"データ警告",MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	for (int i=0;i<ninzu1;i++)
	{
		int kosuu1 = m_sceneList->GetSceneKosuu(i);
		int kosuu2 = m_sceneVoice->GetSceneKosuu(i);
		if (kosuu1 != kosuu2)
		{
			char mes[1024];
			wsprintf(mes,"spt/scene.datとnya/sceneVoice.xtxの%d番目のキャラのシーン数が違います\n\nscene.dat=%d\nsceneVoice.xtx=%d",i+1,kosuu1,kosuu2);
			MessageBox(NULL,mes,"データ警告",MB_OK | MB_ICONEXCLAMATION);

			return;
		}
	}
}



/*_*/

