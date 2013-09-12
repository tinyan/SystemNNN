//
// commonMiniGame.cpp
//


#include <windows.h>


#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"
#include "..\nyanLib\include\myGraphics.h"


#include "commonMode.h"
#include "..\nnnUtilLib\myMouseStatus.h"

#include "..\nnnUtilLib\namelist.h"
#include "..\nnnUtilLib\superButtonPicture.h"

#include "..\nnnUtilLib\commonButton.h"
#include "..\nnnUtilLib\commonButtonGroup.h"

#include "..\nnnUtilLib\cgDataControl.h"

//#include "..\nnnUtilLib\commonBackButton.h"

#include "..\nnnUtilLib\taihi.h"

#include "gameCallBack.h"


#include "..\nnnMiniGameLib\miniGameBase.h"
#include "..\nnnMiniGameLib\allMiniGame.h"

#include "commonGeneral.h"
#include "..\nnnMiniGameLib\minigameLayoutParamName.h"
#include "commonMiniGame.h"

//#include "miniGameBase.h"


//#include "miniGame1.h"
//#include "miniGame2.h"
//#include "miniGame3.h"
//#include "miniGame4.h"

char CCommonMiniGame::m_defaultCGFileName[] = "nnnlogo";
char CCommonMiniGame::m_defaultCongraFileName[] = "ta_congra";
char CCommonMiniGame::m_defaultDescFileName[] = "bg_desc";


CCommonMiniGame::MINIGAMELAYOUTLIST CCommonMiniGame::m_layoutTypeList[] =
{
	{MINIGAME_LAYOUTPARAM_NEXTX,"nextX"},
	{MINIGAME_LAYOUTPARAM_NEXTY,"nextY"},
	{MINIGAME_LAYOUTPARAM_STARTX,"startX"},
	{MINIGAME_LAYOUTPARAM_STARTY,"startY"},
	{-1,""},
};


CCommonMiniGame::CCommonMiniGame(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(MINIGAME_MODE);
//	m_classNumber = MINIGAME_MODE;

	LoadSetupFile("miniGame",128);

	m_nextMode = OMAKE_MODE;
	m_cgDataControl = m_game->GetCGDataControl();

	GetModeNumberBySetup("nextMode",&m_nextMode);


	m_sabunOkFlag = 0;
	GetInitGameParam(&m_sabunOkFlag,"sabunOkFlag");

	m_allOkFlag = 1;
	GetInitGameParam(&m_allOkFlag,"allOkFlag");

	m_miniGameButtonEnableMode = -1;

//	m_cgCharaKosuu = m_game->GetCGCharaKosuu();
	m_cgCharaKosuu = 1;
	if (m_cgDataControl != NULL)
	{
		m_cgCharaKosuu = m_cgDataControl->GetCGCharaKosuu();
	}
	m_cgKosuu = new int [m_cgCharaKosuu+1];

	m_areaButtonMode = 0;
	GetInitGameParam(&m_areaButtonMode,"areaButtonMode");

	m_allCGKosuu = 0;
	int i = 0;
	for (i=0;i<m_cgCharaKosuu;i++)
	{
		m_cgKosuu[i] = 1;
		if (m_cgDataControl != NULL)
		{
			m_cgKosuu[i] = m_cgDataControl->GetCGKosuu(i);
		}
		m_allCGKosuu += m_cgKosuu[i];
	}
	m_cgTable = new int[m_allCGKosuu+1];
	m_cgFlag = new int*[m_cgCharaKosuu];

	for (i=0;i<m_cgCharaKosuu;i++)
	{
		m_cgFlag[i] = new int[m_cgKosuu[i] + 1];
	}


	m_noCGFileName = m_defaultCGFileName;
	GetInitGameString(&m_noCGFileName,"noCGFileName");

	m_congraFileName = m_defaultCongraFileName;
	GetInitGameString(&m_congraFileName,"congraFileName");

	m_congraPic = new CPicture();
	char cfilename[256];
	wsprintf(cfilename,"sys\\%s",m_congraFileName);
	if (m_congraPic->LoadDWQ(cfilename) == FALSE)
	{
		m_congraPic->ReSize(128,32);	//dummy
	}

	SIZE sz = m_congraPic->GetPicSize();
	m_congraSizeX = sz.cx;
	m_congraSizeY = sz.cy;


//	m_miniGameKosuu = 0;
//	m_miniGameKosuuMax = 16;
//	m_miniGameTypeMax = 4;

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY	= CMyGraphics::GetScreenSizeY();

	m_x = screenSizeX / 2;
	m_y = screenSizeY / 2;
	m_speedX = 4;
	m_speedY = 0;


//	m_miniGameTable = new int[m_miniGameKosuuMax];
//	for (i=0;i<m_miniGameKosuuMax;i++)
//	{
//		m_miniGameTable[i] = -1;
//	}

//	m_miniGame = new CMiniGameBase* [m_miniGameKosuuMax];
//	for (i=0;i<m_miniGameKosuuMax;i++)
//	{
//		m_miniGame[i] = NULL;
//	}

//	m_gameClickSound = 1;
//	m_gameClearSound = -1;
//	m_gameMissSound = -1;
//	m_gameGoodSound = -1;

//	m_userGameKosuu = 0;

	for (i=0;i<16;i++)
	{
		m_soundTable[i] = -1;
	}

//	GetInitGameParam(&m_soundTable[0],"miniGameClickSound");
//	GetInitGameParam(&m_soundTable[1],"miniGameGoodSound");
//	GetInitGameParam(&m_soundTable[2],"miniGameBadSound");
//	GetInitGameParam(&m_soundTable[3],"miniGameStartSound");
//	GetInitGameParam(&m_soundTable[4],"miniGameClearSound");
//	GetInitGameParam(&m_soundTable[5],"miniGameGameoverSound");

//	GetInitGameParam(&m_gameClickSound,"miniGameClickSound");
//	GetInitGameParam(&m_gameClearSound,"miniGameClearSound");
//	GetInitGameParam(&m_gameMissSound,"miniGameMissSound");
//	GetInitGameParam(&m_gameGoodSound,"miniGameGoodSound");





	m_allMiniGame = new CAllMiniGame(m_inputStatus);
	int sn = m_allMiniGame->GetSoundKosuu();
	for (i=0;i<sn;i++)
	{
		LPSTR sname = m_allMiniGame->GetSoundName(i);
		if (sname != NULL)
		{
			char name[256];
			wsprintf(name,"miniGame%sSound",sname);
			int soundNumber = -1;
			if (GetInitGameParam(&soundNumber,name))
			{
				if (soundNumber > 0)
				{
					m_soundTable[i] = soundNumber;
				}
			}
		}
	}

	//トランプ、麻雀などの共通グラを設定

	int cp = m_allMiniGame->GetCommonPicKosuu();
	for (i=0;i<cp;i++)
	{
		LPSTR cname = m_allMiniGame->GetCommonPicName(i);
		char name[256];
		wsprintf(name,"%sPicFileName",cname);
		LPSTR fname = NULL;
		if (GetInitGameString(&fname,name))
		{
			CPicture* pic = m_game->GetSystemPicture(fname);
			m_allMiniGame->SetCommonPic(i,pic);
			SIZE sz = m_allMiniGame->GetCommonPicSize(i);
			int sx = sz.cx;
			int sy = sz.cy;
			wsprintf(name,"%sPicSizeX",cname);
			GetInitGameParam(&sx,name);
			wsprintf(name,"%sPicSizeY",cname);
			GetInitGameParam(&sy,name);
			sz.cx = sx;
			sz.cy = sy;
			m_allMiniGame->SetCommonPicSize(i,sz);

			if (i == 0)
			{
				SIZE szz = pic->GetPicSize();
				if (sx*13 > szz.cx)
				{
					m_allMiniGame->SetPicType(i,1);
				}
			}
		}
	}


	//ミニゲーム追加

	int addMiniGameKosuu = 0;
	GetInitGameParam(&addMiniGameKosuu,"addMiniGame");
	for (i=0;i<addMiniGameKosuu;i++)
	{
		char name[256];
		wsprintf(name,"miniGame%d",i+1);
		int nm = -1;
		GetInitGameParam(&nm,name);
		if (nm>0)
		{
			int layoutParamKosuu = 0;
			int layOutParam[256];
			int param = 0;

			for (int k=0;k<4;k++)
			{
				if (m_layoutTypeList[k].type == -1) break;

				wsprintf(name,"miniGame%d%s",i+1,m_layoutTypeList[k].name);
				if (GetInitGameParam(&param,name))
				{
					layOutParam[layoutParamKosuu*2+0] = m_layoutTypeList[k].type;
					layOutParam[layoutParamKosuu*2+1] = param;
					layoutParamKosuu++;
				}
			}

			AddMiniGame(nm-1,layoutParamKosuu,layOutParam);
		}
	}

	m_miniGameCheckKosuu = addMiniGameKosuu;
	GetInitGameParam(&m_miniGameCheckKosuu,"miniGameCheckNumber");
	m_miniGameCheckPoint = new POINT[m_miniGameCheckKosuu+1];
	m_miniGameCheckSize = new SIZE[m_miniGameCheckKosuu+1];
	m_miniGameCheckMode = new int[m_miniGameCheckKosuu+1];
	m_miniGameCheckVar = new int[m_miniGameCheckKosuu+1];
	m_miniGameSetVar = new int[m_miniGameCheckKosuu+1];
	m_miniGameSetType = new int[m_miniGameCheckKosuu+1];
	m_miniGameDescKosuu = new int[m_miniGameCheckKosuu+1];
	m_miniGameDescFileName = new LPSTR* [m_miniGameCheckKosuu+1];

	m_miniGameExitButtonZahyo = new POINT[m_miniGameCheckKosuu+1];
	m_miniGameSetCGSceneWork = new int[(m_miniGameCheckKosuu+1)*512];
	int miniGameMode = OMAKE_MODE;

	int xx = 0;
	int yy = 0;
	int sx = 16;
	int sy = 16;

	for (i=0;i<m_miniGameCheckKosuu;i++)
	{
		char name[256];
	
		wsprintf(name,"miniGameCheckMode%d",i+1);
		GetModeNumberBySetup(name,&miniGameMode);

		wsprintf(name,"miniGameCheckX%d",i+1);
		GetInitGameParam(&xx,name);
		wsprintf(name,"miniGameCheckY%d",i+1);
		GetInitGameParam(&yy,name);
		wsprintf(name,"miniGameCheckSizeX%d",i+1);
		GetInitGameParam(&sx,name);
		wsprintf(name,"miniGameCheckSizeY%d",i+1);
		GetInitGameParam(&sy,name);

		m_miniGameCheckPoint[i].x = xx;
		m_miniGameCheckPoint[i].y = yy;
		m_miniGameCheckSize[i].cx = sx;
		m_miniGameCheckSize[i].cy = sy;

		m_miniGameCheckMode[i] = miniGameMode;


		//-1使用可能 0-:変数でチェック

		LPSTR varName = NULL;
		int varNum = -1;
		wsprintf(name,"checkVarName%d",i+1);
		if (GetInitGameString(&varName,name))
		{
			if (varName != NULL)
			{
				if ((*varName) != 0)
				{
					varNum = m_game->GetVarNumber(varName);
				}
			}
		}
		m_miniGameCheckVar[i] = varNum;

		//クリアーでフラグをたてるかどうか 0:たてない 1:たてる 2:+1する 3:or(bit)

		varName = NULL;
		varNum = -1;
		wsprintf(name,"setVarName%d",i+1);
		if (GetInitGameString(&varName,name))
		{
			if (varName != NULL)
			{
				if ((*varName) != 0)
				{
					varNum = m_game->GetVarNumber(varName);
				}
			}
		}

		int md = 0;
		if (varNum != -1)
		{
			md = 1;
			wsprintf(name,"setVarType%d",i+1);
			GetInitGameParam(&md,name);
		}

		m_miniGameSetVar[i] = varNum;
		m_miniGameSetType[i] = md;

		int descKosuu = 0;
		wsprintf(name,"miniGameDescNumber%d",i+1);
		GetInitGameParam(&descKosuu,name);
		m_miniGameDescKosuu[i] = descKosuu;

		m_miniGameDescFileName[i] = NULL;
		if (descKosuu > 0)
		{
			m_miniGameDescFileName[i] = new LPSTR[descKosuu];
			for (int d=0;d<descKosuu;d++)
			{
				LPSTR descName = m_defaultDescFileName;
				wsprintf(name,"miniGameDescFileName%d_%d",i+1,d+1);
				GetInitGameString(&descName,name);
				LPSTR* ptr = m_miniGameDescFileName[i];
				*(ptr+d) = descName;
			}
		}

		int setCGNumber = 0;
		sprintf_s(name,sizeof(name),"setCGNumber%d",i+1);
		GetInitGameParam(&setCGNumber,name);
		if (setCGNumber > 127) setCGNumber = 127;

		m_miniGameSetCGSceneWork[i*512+0] = setCGNumber;
		for (int d=0;d<setCGNumber;d++)
		{
			int setCGPlayer = 0;
			int setCGParam = 0;
			if (d == 0)
			{
				sprintf_s(name,sizeof(name),"setCGPlayer%d",i+1);
				GetInitGameParam(&setCGPlayer,name);
				sprintf_s(name,sizeof(name),"setCGParam%d",i+1);
				GetInitGameParam(&setCGParam,name);
			}

			sprintf_s(name,sizeof(name),"setCGPlayer%d_%d",i+1,d+1);
			GetInitGameParam(&setCGPlayer,name);
			sprintf_s(name,sizeof(name),"setCGParam%d_%d",i+1,d+1);
			GetInitGameParam(&setCGParam,name);
			m_miniGameSetCGSceneWork[i*512+1+d*2] = setCGPlayer;
			m_miniGameSetCGSceneWork[i*512+1+d*2+1] = setCGParam;
		}

		int setSceneNumber = 0;
		sprintf_s(name,sizeof(name),"setSceneNumber%d",i+1);
		GetInitGameParam(&setSceneNumber,name);
		if (setSceneNumber > 127) setSceneNumber = 127;

		m_miniGameSetCGSceneWork[i*512+256] = setSceneNumber;
		for (int d=0;d<setSceneNumber;d++)
		{
			int setScenePlayer = 0;
			int setSceneParam = 0;
			sprintf_s(name,sizeof(name),"setScenePlayer%d_%d",i+1,d+1);
			GetInitGameParam(&setScenePlayer,name);
			sprintf_s(name,sizeof(name),"setSceneParam%d_%d",i+1,d+1);
			GetInitGameParam(&setSceneParam,name);
			m_miniGameSetCGSceneWork[i*512+256+1+d*2] = setScenePlayer;
			m_miniGameSetCGSceneWork[i*512+256+1+d*2+1] = setSceneParam;
		}



		xx += sx;
	}




	//CreateBackButton();
	m_exitButtonPrintX = 0;
	m_exitButtonPrintY = 0;
	GetInitGameParam(&m_exitButtonPrintX,"exitPrintX");
	GetInitGameParam(&m_exitButtonPrintY,"exitPrintY");
	m_filenameExit = m_defaultBackButtonFileName;
	GetInitGameString(&m_filenameBack,"ExitFileName");

	m_exitButton = new CCommonButton(m_setup,"exit");
	m_exitButton->SetPicture(CSuperButtonPicture::GetPicture(0));

	POINT exitZahyo = m_exitButton->GetZahyo();
	for (int i=0;i<m_miniGameCheckKosuu;i++)
	{
		int exitX = exitZahyo.x;
		int exitY = exitZahyo.y;

		char name[256];
		wsprintf(name,"exitPrintX%d",i+1);
		GetInitGameParam(&exitX,name);
		wsprintf(name,"exitPrintY%d",i+1);
		GetInitGameParam(&exitY,name);

		m_miniGameExitButtonZahyo[i].x = exitX;
		m_miniGameExitButtonZahyo[i].y = exitY;
	}




	m_taihi = new CTaihi();
	SIZE sz2 = m_exitButton->GetSize();
	m_exitButtonSizeX = sz2.cx;
	m_exitButtonSizeY = sz2.cy;

	m_taihi->CreateBuffer(0,m_exitButtonSizeX,m_exitButtonSizeY);

	//buttonmode?
	m_buttonGroup = NULL;

	if (m_areaButtonMode)
	{
//		CPicture* lpBG = m_commonBG;
//		if (m_backScriptFlag || m_mustAllPrintFlag) lpBG = NULL;

		m_buttonGroup = new CCommonButtonGroup(m_setup,m_miniGameCheckKosuu,NULL,"minigameButton");

		for (i=0;i<m_miniGameCheckKosuu;i++)
		{
			CPicture* lpPic = CSuperButtonPicture::GetPicture(i+1);
			m_buttonGroup->SetPicture(i,lpPic);
		}
	}





	GetBGMSetup();
	GetFadeInOutSetup();
//	GetEnterExitVoiceFileName();

}


CCommonMiniGame::~CCommonMiniGame()
{
	End();
}

void CCommonMiniGame::End(void)
{
	int i;

	ENDDELETECLASS(m_buttonGroup);


	ENDDELETECLASS(m_taihi);
	ENDDELETECLASS(m_exitButton);

	ENDDELETECLASS(m_allMiniGame);

	DELETEARRAY(m_miniGameSetCGSceneWork);
	DELETEARRAY(m_miniGameExitButtonZahyo);

	if (m_miniGameDescFileName != NULL)
	{
		for (i=0;i<m_miniGameCheckKosuu;i++)
		{
			DELETEARRAY(m_miniGameDescFileName[i]);
		}

		DELETEARRAY(m_miniGameDescFileName);
	}

	DELETEARRAY(m_miniGameDescKosuu);
	DELETEARRAY(m_miniGameSetType);
	DELETEARRAY(m_miniGameSetVar);
	DELETEARRAY(m_miniGameCheckVar);
	DELETEARRAY(m_miniGameCheckMode);
	DELETEARRAY(m_miniGameCheckSize);
	DELETEARRAY(m_miniGameCheckPoint);

//	if (m_miniGame != NULL)
//	{
///		for (i=0;i<m_miniGameKosuuMax;i++)
//		{
//			ENDDELETECLASS(m_miniGame[i]);
//		}
//	}
//	DELETEARRAY(m_miniGame);

//	DELETEARRAY(m_miniGameTable);

	ENDDELETECLASS(m_congraPic);
	if (m_cgFlag != NULL)
	{
		for (i=0;i<m_cgCharaKosuu;i++)
		{
			DELETEARRAY(m_cgFlag[i]);
		}
	}

	DELETEARRAY(m_cgFlag);
	DELETEARRAY(m_cgTable);
	DELETEARRAY(m_cgKosuu);
}



int CCommonMiniGame::Init(void)
{
	m_clearToSetFlag = FALSE;

	m_miniGameNumber = m_game->GetMiniGameNumber();


	m_exitButtonPrintX = m_miniGameExitButtonZahyo[m_miniGameNumber].x;
	m_exitButtonPrintY = m_miniGameExitButtonZahyo[m_miniGameNumber].y;

	POINT exitZahyo;
	exitZahyo.x = m_exitButtonPrintX;
	exitZahyo.y = m_exitButtonPrintY;

	m_exitButton->SetZahyo(exitZahyo);

	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY	= CMyGraphics::GetScreenSizeY();

	m_x = screenSizeX / 2;
	m_y = screenSizeY / 2;
	m_speedX = 4;
	m_speedY = 0;


	m_getCGKosuu = 0;
	for (int j=0;j<m_cgCharaKosuu;j++)
	{
		int* ptr = m_cgFlag[j];
		for (int i=0;i<m_cgKosuu[j];i++)
		{
			int fl0 = 0;
			if (m_cgDataControl != NULL)
			{
				fl0 = m_cgDataControl->CheckGetCG(j,i);
			}
			*(ptr+i) = fl0;

//			*(ptr+i) = m_game->CheckGetCG(j,i);


			if (*(ptr+i))
			{
				if (m_sabunOkFlag == 0)
				{
					if (m_cgDataControl != NULL)
					{
						LPSTR name = m_cgDataControl->GetCGFileName(j,i,FALSE);
						if ((*name) == '@')
						{
							continue;
						}
					}
				}

				if (m_allOkFlag == 0)
				{
					if (m_cgDataControl != NULL)
					{
						LPSTR name = m_cgDataControl->GetCGFileName(j,i,FALSE);
						if ((*name) == '@') name++;
						if ((*name) == '!')
						{
							continue;
						}
					}
				}

				char tas[4];
//				LPSTR frm = m_game->GetCGFileName(j,i);
				LPSTR frm = m_cgDataControl->GetCGFileName(j,i);

				memcpy(tas,frm,2);
				tas[2] = 0;
				tas[3] = 0;
				if (_stricmp(tas,"ta") == 0)
				{
					continue;
				}


				m_cgTable[m_getCGKosuu] = j*100000 + i;
				m_getCGKosuu++;
			}
		}
	}


	int r0;
	for (int i=0;i<2;i++)
	{
		LPSTR filename = m_noCGFileName;

		if (m_getCGKosuu > 0)
		{
			int r = rand() % m_getCGKosuu;
			if (i == 0)
			{
				r0 = r;
			}
			else
			{
				if (r == r0)
				{
					r++;
					r %= m_getCGKosuu;
				}
			}



			int d = m_cgTable[r];
			int chara = d / 100000;
			int nn = d % 100000;
			filename = m_cgDataControl->GetCGFileName(chara,nn);

		}

		char allfilename[256];
		char c1 = *filename;
		char c2 = *(filename+1);
		if (c1 <= 'Z') c1 += 0x20;
		if (c2 <= 'Z') c2 += 0x20;

		if ((c1 == 'e') && (c2 == 'v'))
		{
			wsprintf(allfilename,"ev\\%s",filename);
		}
		else if ((c1 == 'b') && (c2 == 'g'))
		{
			wsprintf(allfilename,"bg\\%s",filename);
		}
		else if ((c1 == 't') && (c2 == 'a'))
		{
			wsprintf(allfilename,"ta\\%s",filename);
		}
		else
		{
			wsprintf(allfilename,"sys\\%s",filename);
		}

		CPicture* pic = m_game->GetEffectPicture(i);
		pic->LoadDWQ(allfilename);
	}

	if (m_getCGKosuu < 2)
	{
		CPicture* pic = m_game->GetEffectPicture(1);
		
		pic->ReSize(screenSizeX,screenSizeY);

		CAllGraphics::FillScreen(0,64,128);
		pic->GetScreen();
		pic->Flush();
	}

//	CMiniGameBase* miniGame = m_miniGame[m_miniGameNumber];
//	if (miniGame != NULL) miniGame->GeneralInit();
	///LoadBackButtonPic();
	CPicture* lpPic = m_exitButton->GetPicture();
	if (lpPic != NULL)
	{
		LPSTR name = m_exitButton->GetFileName();
		char filename[256];
		wsprintf(filename,"sys\\%s",name);
		lpPic->LoadDWQ(filename);
	}

	m_exitButton->Init();

	m_allMiniGame->SetPicture(m_game->GetEffectPicture(0),0);
	m_allMiniGame->SetPicture(m_game->GetEffectPicture(1),1);
	m_allMiniGame->SetPicture(m_game->GetEffectPicture(2),2);	//???
	m_allMiniGame->SetCommonBG(m_commonBG);
	m_allMiniGame->SetCommonParts(m_commonParts);

	m_allMiniGame->SetGameNumber(m_miniGameNumber);
	m_allMiniGame->Init();

	m_miniGameDescCountMax = m_miniGameDescKosuu[m_miniGameNumber];
	m_miniGameDescCount = 0;

	if (m_miniGameDescCountMax > 0)
	{
		LoadDescFile();
	}


	return -1;
}

int CCommonMiniGame::Calcu(void)
{
	//desc
	if (m_miniGameDescCount < m_miniGameDescCountMax)
	{
		if (m_mouseStatus->CheckClick())
		{
			m_miniGameDescCount++;
			if (m_miniGameDescCount < m_miniGameDescCountMax)
			{
				LoadDescFile();
			}
			else
			{
				CAreaControl::SetNextAllPrint();
			}
		}

		return -1;
	}

	//check exit
	int rt = m_exitButton->Calcu(m_inputStatus);
	if (rt != NULL)
	{
		int nm = ProcessCommonButton(rt);
		if (nm == 0)
		{
//			return ReturnFadeOut(m_nextMode);
			return ReturnFadeOut(m_backMode);
		}
	}

	if (m_allMiniGame->Calcu() != -1)
	{
//		return ReturnFadeOut(m_nextMode);
		return ReturnFadeOut(m_backMode);
	}

	if (m_allMiniGame->CheckClear())
	{
		CalcuCongra();


		if (m_clearToSetFlag == FALSE)
		{
			m_clearToSetFlag = TRUE;
			int varNum = m_miniGameSetVar[m_miniGameNumber];
			if (varNum != -1)
			{
				int type = m_miniGameSetType[m_miniGameNumber];
				if (type == 1)
				{
					m_game->SetVarData(varNum,1);
				}
				else if (type == 2)
				{
					int d = m_game->GetVarData(varNum);
					d++;
					m_game->SetVarData(varNum,d);
				}
				else if (type == 3)
				{
					int d = m_game->GetVarData(varNum);
					d |= (1<<(m_miniGameNumber & 31));
					m_game->SetVarData(varNum,d);
				}
			}
		}


		int setCGKosuu = m_miniGameSetCGSceneWork[m_miniGameNumber*512+0];
		if (setCGKosuu > 0)
		{
			for (int i=0;i<setCGKosuu;i++)
			{
				int setCGPlayer = m_miniGameSetCGSceneWork[m_miniGameNumber*512+1+i*2+0];
				int setCGParam = m_miniGameSetCGSceneWork[m_miniGameNumber*512+1+i*2+1];

				if ((setCGPlayer > 0) && (setCGParam > 0))
				{
					m_game->SetCG(setCGPlayer,setCGParam);
				}
			}
		}


		int setSceneKosuu = m_miniGameSetCGSceneWork[m_miniGameNumber*512+256];
		if (setSceneKosuu > 0)
		{
			for (int i=0;i<setSceneKosuu;i++)
			{
				int setScenePlayer = m_miniGameSetCGSceneWork[m_miniGameNumber*512+256+1+i*2+0];
				int setSceneParam = m_miniGameSetCGSceneWork[m_miniGameNumber*512+256+1+i*2+1];

				if ((setScenePlayer > 0) && (setSceneParam > 0))
				{
					//set scene はフィルムによるコントロールにかわったため、これはダミー
//					m_game->SetScene(setScenePlayer,setSceneParam);
				}
			}
		}




	}


	if (m_allMiniGame->CheckGameover())
	{
		CalcuGameover();
	}

	int sound = m_allMiniGame->GetSoundNumber();
	if (sound >= 0)
	{
		if (sound < 16)
		{
			int soundData = m_soundTable[sound];
			if (soundData > 0)
			{
				m_game->PlaySystemSound(soundData-1);
			}
		}
	}




	return -1;
}

int CCommonMiniGame::Print(void)
{
	if (m_miniGameDescCount < m_miniGameDescCountMax)
	{
		if (CAreaControl::CheckAllPrintMode())
		{
			m_commonBG->Put(0,0,FALSE);
		}
		return -1;
	}

	//fuque
	m_taihi->Fuque(0);
	m_allMiniGame->Print();


	//clear,gameover
	if (m_allMiniGame->CheckClear())
	{
		PrintCongra();
	}

	if (m_allMiniGame->CheckGameover())
	{
		PrintGameover();
	}

	//taihi
	m_taihi->Taihi(0,m_exitButtonPrintX,m_exitButtonPrintY);
	m_exitButton->Print(TRUE);

	return -1;
}


BOOL CCommonMiniGame::AddMiniGame(CMiniGameBase* lpMiniGame,int layoutParamKosuu,int* layoutParam )
{
	return m_allMiniGame->AddMiniGame(lpMiniGame,layoutParamKosuu,layoutParam);
}


BOOL CCommonMiniGame::AddMiniGame(int n,int layoutParamKosuu,int* layoutParam)
{
	return m_allMiniGame->AddMiniGame(n,layoutParamKosuu,layoutParam);
}


CPicture* CCommonMiniGame::GetPicture(int n)
{
	return m_game->GetEffectPicture(n);
}


CInputStatus* CCommonMiniGame::GetInputStatus(void)
{
	return m_game->GetInputStatus();
}

void CCommonMiniGame::CalcuCongra(void)
{
	int screenSizeX = CMyGraphics::GetScreenSizeX();
	int screenSizeY	= CMyGraphics::GetScreenSizeY();

	m_x += m_speedX;
	if (m_x<0)
	{
		m_x = 0;
		m_speedX = (rand() % 10) + 3;
	}

	if (m_x > screenSizeX-m_congraSizeX)
	{
		m_x = screenSizeX-m_congraSizeX;
		m_speedX = (rand() % 10) + 3;
		m_speedX *= -1;
	}

	m_speedY += 2;
	m_y += m_speedY;

	if (m_y < 0)
	{
		m_y = 0;
		m_speedY = 1;
	}
	
	if (m_y > screenSizeY - m_congraSizeY)
	{
		m_y = screenSizeY - m_congraSizeY;

		m_speedY *= (70 + (rand() % 30));
		m_speedY /= 100;

		if (m_speedY < 10)
		{
			m_speedY = 20 + (rand() % 50);
		}

		m_speedY *= -1;
	}

}

void CCommonMiniGame::PrintCongra(void)
{
	m_congraPic->Put(m_x,m_y,TRUE);
}

void CCommonMiniGame::CalcuGameover(void)
{
}

void CCommonMiniGame::PrintGameover(void)
{
}
/*
void CCommonMiniGame::PlayClickSound(void)
{
	if (m_gameClickSound > 0)
	{
		m_game->PlaySystemSound(m_gameClickSound-1);
	}
}


void CCommonMiniGame::PlayClearSound(void)
{
	if (m_gameClearSound > 0)
	{
		m_game->PlaySystemSound(m_gameClearSound-1);
	}
}


void CCommonMiniGame::PlayMissSound(void)
{
	if (m_gameMissSound > 0)
	{
		m_game->PlaySystemSound(m_gameMissSound-1);
	}
}

void CCommonMiniGame::PlayGoodSound(void)
{
	if (m_gameGoodSound > 0)
	{
		m_game->PlaySystemSound(m_gameGoodSound-1);
	}
}
*/

int CCommonMiniGame::GetOnMiniGame(int mode)
{
	if (m_miniGameButtonEnableMode == -1)
	{
		return -1;
	}

	POINT pt = m_mouseStatus->GetZahyo();

	for (int i=0;i<m_miniGameCheckKosuu;i++)
	{
		if (m_miniGameCheckMode[i] == mode)
		{
			int varNum = m_miniGameCheckVar[i];
			if (varNum != -1)
			{
				if (m_game->GetVarData(varNum) == 0)
				{
					continue;
				}
			}

			int x = pt.x - m_miniGameCheckPoint[i].x;
			int y = pt.y - m_miniGameCheckPoint[i].y;
			int sx = m_miniGameCheckSize[i].cx;
			int sy = m_miniGameCheckSize[i].cy;

			if ((x>=0) && (y>=0) && (x<sx) && (y<sy))
			{
				return i;
			}
		}
	}

	return -1;
}

void CCommonMiniGame::LoadDescFile(void)
{
	char filename[256];
	LPSTR* ptr = m_miniGameDescFileName[m_miniGameNumber];
	LPSTR name = *(ptr+m_miniGameDescCount);
	if (name != NULL)
	{
		wsprintf(filename,"sys\\%s",name);
		m_commonBG->LoadDWQ(filename);
	}
	CAreaControl::SetNextAllPrint();
}



void CCommonMiniGame::InitMiniGameButton(int md)
{
	m_miniGameButtonEnableMode = md;
	if (md == -1) return;
	if (m_areaButtonMode == 0) return;

	//check exist
	for (int i=0;i<m_miniGameCheckKosuu;i++)
	{
		BOOL f = FALSE;

		if (m_miniGameCheckMode[i] == md)
		{
			f = TRUE;

			int varNum = m_miniGameCheckVar[i];
			if (varNum != -1)
			{
				if (m_game->GetVarData(varNum) == 0)
				{
					f = FALSE;
				}
			}
		}

		if (f == FALSE)
		{
			m_buttonGroup->SetExist(i,FALSE);
		}
		else
		{
			m_buttonGroup->SetExist(i,TRUE);
			m_buttonGroup->SetEnable(i,TRUE);

			//load pic
			CPicture* lpPic = m_buttonGroup->GetPicture(i);
			LPSTR name = m_buttonGroup->GetFileName(i);

			char filename[256];
			wsprintf(filename,"sys\\%s",name);
			lpPic->LoadDWQ(filename);
		}
	}

	//init
	m_buttonGroup->Init();
}

int CCommonMiniGame::CalcuMiniGameButton(void)
{
	if (m_miniGameButtonEnableMode == -1) return -1;

	return m_buttonGroup->Calcu(m_inputStatus);
}

void CCommonMiniGame::PrintMiniGameButton(void)
{
	if (m_buttonGroup == NULL) return;
	
	if (m_miniGameButtonEnableMode == -1)
	{
		return;
	}

	m_buttonGroup->Print(TRUE);
}



/*_*/


