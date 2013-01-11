//
// 
//


#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGraphics.h"

#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\myMouseStatus.h"
#include "..\nnnUtilLib\myKeyStatus.h"
#include "..\nnnUtilLib\inputStatus.h"

#include "..\nnnUtilLib\namelist.h"

#include "..\nnnUtilLib\printCard.h"
#include "..\nnnUtilLib\printCardPower.h"
#include "..\nnnUtilLib\printCardGaze.h"

#include "commonMode.h"
#include "commonSystemParamName.h"

#include "..\nnnUtilLib\superButtonPicture.h"
#include "..\nnnUtilLib\commonButton.h"

#include "gameCallBack.h"

#include "commonGeneral.h"
#include "commonCardSystem.h"

char CCommonCardSystem::m_defaultAppearFunctionName[] = "appearcard";
char CCommonCardSystem::m_defaultEnableFunctionName[] = "enablecard";
char CCommonCardSystem::m_defaultNoserareruFunctionName[] = "onokcard";


char CCommonCardSystem::m_defaultAppearVarName[] = "カード出現コントロールワーク";
char CCommonCardSystem::m_defaultEnableVarName[] = "カード許可コントロールワーク";
char CCommonCardSystem::m_defaultNoserareruVarName[] = "カードのせコントロールワーク";

char CCommonCardSystem::m_defaultCardNameTag[] = "ta_cardseat";

/*
カード組み合わせ画面を標準機能で追加
結果表示画面


変数:どのカードがどのカードにのっているか
マイナスの場合はかさねられてる

組み合わせ個数
組み合わせ番号
パワー
経験値
レベルアップするかどうか

（パワー最大値）



init:
上下関係維持、上下関係番号順
最大分岐数


表:
レベルごとの必要パワー、被必要パワー
nextレベル
段階ごとの種類

カード出現
選択不可
乗せる不可

nextLevel情報


決定ボタン


パワー不要モード
ゲージ不要モード
レベル不要モード



init
内部段階数




ゲージが1個のときと複数のときで表示をかえる



チェックゲージ個数 1


通し番号,カード番号,レベル,必要パワー,被必要パワー,表示ゲージ番号1-n,分岐先番号,ゲージ番号,条件min,条件max,



cardsystem(),cardsystem(0)	//くみあわせ
cardsystem(1)//経験値取得
cardsystem(2)//levelup
cardsystem(3)//経験値取得＋レベルアップ


function
出現コントロール
選択コントロール
乗せられコントロール

*/


CCommonCardSystem::CCommonCardSystem(CGameCallBack* lpGame) : CCommonGeneral(lpGame)
{
	SetClassNumber(CARDSYSTEM_MODE);

	LoadSetupFile("cardSystem");

	int bt = 1;
	for (int i=0;i<31;i++)
	{
		m_bitPattern[i] = bt;
		bt <<= 1;
	}
	m_bitPattern[31] = 0x80000000;


	m_cardKosuu = 1;
	GetInitGameParam(&m_cardKosuu,"cardNumber");

	m_cardLevelMax = 1;
	GetInitGameParam(&m_cardLevelMax,"cardLevelMax");

	m_cardPlaceVar = new int[m_cardKosuu];
	for (int i=0;i<m_cardKosuu;i++)
	{
		m_cardPlaceVar[i] = -1;
		LPSTR varName = NULL;
		char name[256];
		wsprintf(name,"cardPlaceVar%d",i+1);
		if (GetInitGameString(&varName,name))
		{
			m_cardPlaceVar[i] = m_game->GetVarNumber(varName);
		}
	}

	m_appearControlFlag = 0;
	m_enableControlFlag = 0;
	m_noserareruControlFlag = 0;
	m_appearVarNumber = -1;
	m_enableVarNumber = -1;
	m_noserareruVarNumber = -1;

	GetInitGameParam(&m_appearControlFlag,"appearControlFlag");
	if (m_appearControlFlag)
	{
		LPSTR functionName = m_defaultAppearFunctionName;
		GetInitGameString(&functionName,"appearFunctionName");
		m_game->RegistUserFunction(CARDSYSTEM_MODE,functionName,0);

		LPSTR varName = m_defaultAppearVarName;
		GetInitGameString(&varName,"appearVar");
		m_appearVarNumber = m_game->GetVarNumber(varName);
	}

	GetInitGameParam(&m_enableControlFlag,"enableControlFlag");
	if (m_enableControlFlag)
	{
		LPSTR functionName = m_defaultEnableFunctionName;
		GetInitGameString(&functionName,"enableFunctionName");
		m_game->RegistUserFunction(CARDSYSTEM_MODE,functionName,1);

		LPSTR varName = m_defaultEnableVarName;
		GetInitGameString(&varName,"enableVar");
		m_enableVarNumber = m_game->GetVarNumber(varName);
	}

	GetInitGameParam(&m_noserareruControlFlag,"onOkControlFlag");
	if (m_enableControlFlag)
	{
		LPSTR functionName = m_defaultNoserareruFunctionName;
		GetInitGameString(&functionName,"onokFunctionName");
		m_game->RegistUserFunction(CARDSYSTEM_MODE,functionName,2);

		LPSTR varName = m_defaultNoserareruVarName;
		GetInitGameString(&varName,"onOkVar");
		m_noserareruVarNumber = m_game->GetVarNumber(varName);
	}

	m_appearFlag = new int[m_cardKosuu];
	m_enableFlag= new int[m_cardKosuu];
	m_noserareruFlag = new int[m_cardKosuu];


	m_updownAdjust = 1;
	GetInitGameParam(&m_updownAdjust,"updownAdjust");
/*
	m_cardStatusVarNumber = new int[m_cardKosuu];
	for (int i=0;i<m_cardKosuu;i++)
	{
		int varNumber = -1;
		LPSTR varName = NULL;
		char name[1024];
		wsprintf(name,"cardStatusVarName%d",i+1);
		if (GetInitGameString(&varName,name))
		{
			varNumber = m_game->GetVarNumber(varName);
		}
		m_cardStatusVarNumber[i] = varNumber;
	}
*/

	m_powerMax = 10;
	GetInitGameParam(&m_powerMax,"powerMax");
	m_powerMaxVarNumber = -1;
	if (1)
	{
		LPSTR varName = NULL;
		if (GetInitGameString(&varName,"powerMaxVar"))
		{
			m_powerMaxVarNumber = m_game->GetVarNumber(varName);
		}
	}


	m_cardSizeX = 100;
	m_cardSizeY = 200;
	m_onCardPrintX = -10;
	m_onCardPrintY = -20;
	GetInitGameParam(&m_cardSizeX,"cardSizeX");
	GetInitGameParam(&m_cardSizeY,"cardSizeY");
	GetInitGameParam(&m_onCardPrintX,"onCardPrintX");
	GetInitGameParam(&m_onCardPrintY,"onCardPrintY");
	m_cardZahyo = new POINT[m_cardKosuu];
	for (int i=0;i<m_cardKosuu;i++)
	{
		int x = m_cardSizeX * i;
		int y = 0;
		char name[1024];
		wsprintf(name,"cardPrintX%d",i+1);
		GetInitGameParam(&x,name);
		wsprintf(name,"cardPrintY%d",i+1);
		GetInitGameParam(&y,name);
		m_cardZahyo[i].x = x;
		m_cardZahyo[i].y = y;
	}



	if (1)
	{
		int cardPrintType[7] = {0,1,2,3,4,0,0};
		int cardSeatTable[7] = {0,0,0,0,0,0,0};
		
		for (int i=0;i<7;i++)
		{
			int printType = cardPrintType[i] + 1;
			int seatTable = cardSeatTable[i] + 1;
			char name[256];

			wsprintf(name,"cardPrintType%d",i+1);
			GetInitGameParam(&printType,name);
			CPrintCard::ChangePrintType(i,printType - 1);

			wsprintf(name,"cardSeatTable%d",i+1);
			GetInitGameParam(&seatTable,name);
			CPrintCard::ChangeSaetTable(i,seatTable-1);

//			int cardPowerPrintType = printType;
//			wsprintf(name,"cardPowerPrintType%d",i+1);
//			GetInitGameParam(&cardPowerPrintType,name);
			//CPrintCardPower

		}

		int r = 64;
		int g = 96;	
		int b = 32;
		int ps = 50;
		GetInitGameParam(&r,"cardAddColorR");
		GetInitGameParam(&g,"cardAddColorG");
		GetInitGameParam(&b,"cardAddColorB");
		CPrintCard::ChangeAddColor(r,g,b);

		GetInitGameParam(&ps,"cardTransPercent");
		CPrintCard::ChangePercent(ps);





	}

	m_printCard = new CPrintCard*[m_cardKosuu];
	LPSTR cardNameTag = m_defaultCardNameTag;
	GetInitGameString(&cardNameTag,"tagNameCard");
	for (int i=0;i<m_cardKosuu;i++)
	{
		char tagName[256];
		wsprintf(tagName,"%s%d",cardNameTag,i+1);
		SIZE sz;
		sz.cx = m_cardSizeX;
		sz.cy = m_cardSizeY;
		m_printCard[i] = new CPrintCard(tagName,sz,m_cardLevelMax-1);
	}

	m_printCardPower = NULL;
	if (1)
	{
		m_printCardPower = new CPrintCardPower(m_setup); 
	}

	m_printCardGaze = NULL;
	if (1)
	{
		m_printCardGaze = new CPrintCardGaze(m_setup);
	}

	m_okButton = new CCommonButton(m_setup,"ok");
	m_okButton->SetPicture(CSuperButtonPicture::GetPicture(0));
}



CCommonCardSystem::~CCommonCardSystem()
{
	End();
}

void CCommonCardSystem::End(void)
{
	ENDDELETECLASS(m_okButton);

	ENDDELETECLASS(m_printCardGaze);
	ENDDELETECLASS(m_printCardPower);

	if (m_printCard != NULL)
	{
		for (int i=0;i<m_cardKosuu;i++)
		{
			ENDDELETECLASS(m_printCard[i]);
		}
		DELETEARRAY(m_printCard);
	}

	DELETEARRAY(m_cardZahyo);
//	DELETEARRAY(m_cardStatusVarNumber);
	DELETEARRAY(m_noserareruFlag);
	DELETEARRAY(m_enableFlag);
	DELETEARRAY(m_appearFlag);

	DELETEARRAY(m_cardPlaceVar);
}



int CCommonCardSystem::Init(void)
{
	for (int i=0;i<m_cardKosuu;i++)
	{
		m_appearFlag[i] = CheckAppearByVar(i);
		m_enableFlag[i] = CheckEnableByVar(i);
		m_noserareruFlag[i] = CheckNoserareruByVar(i);
	}

	CheckPowerMaxByVar();


	m_catchNumber = -1;

	CPicture* lpPic = m_okButton->GetPicture();
	char filename[1024];
	wsprintf(filename,"sys\\%s",m_okButton->GetFileName());
	lpPic->LoadDWQ(filename);
	m_okButton->Init();


	return -1;
}

int CCommonCardSystem::Calcu(void)
{
	//catching
	if (m_catchNumber != -1)
	{


		return -1;
	}

	return -1;
}

int CCommonCardSystem::Print(void)
{
	CAreaControl::SetNextAllPrint();
	for (int j=0;j<20;j++)
	{
		CAllGeo::BoxFill(0,j*30,800,30,j*10+10,240-j*5,(j*73) & 0xff);

	}
	//CAllGraphics::FillScreen(64,96,160);


	for (int j=0;j<2;j++)
	{
		for (int i=0;i<2;i++)
		{
			POINT pt;
			pt.x = i * 400 + 200;
			pt.y = j * 300 + 50;
			PutCard(i+j*2,pt,j*2+i);

//			m_printCard[i+j*2]->Put(pt,i+j*2,j);
		}
	}
	return -1;
}

void CCommonCardSystem::PutCard(int card,POINT pt,int st)
{
	int level = 1;
	m_printCard[card]->Put(pt,st,level-1);

	//cardPower
	if (m_printCardPower != NULL)
	{
		m_printCardPower->Put(pt,st+1,st);

	}

	//gaze
	if (m_printCardGaze != NULL)
	{

	}


}



int CCommonCardSystem::CheckAppearByVar(int card)
{
	if (m_appearControlFlag == 0) return 1;
	if (m_appearVarNumber == -1) return 1;

	int varData = m_game->GetVarData(m_appearVarNumber);
	int bit = m_bitPattern[card];

	if (varData & bit) return 0;

	return 1;
}

int CCommonCardSystem::CheckEnableByVar(int card)
{
	if (m_enableControlFlag == 0) return 1;
	if (m_enableVarNumber == -1) return 1;
	
	int varData = m_game->GetVarData(m_enableVarNumber);
	int bit = m_bitPattern[card];

	if (varData & bit) return 0;

	return 1;
}

int CCommonCardSystem::CheckNoserareruByVar(int card)
{
	if (m_noserareruControlFlag == 0) return 1;
	if (m_noserareruVarNumber == -1) return 1;

	int varData = m_game->GetVarData(m_noserareruVarNumber);
	int bit = m_bitPattern[card];

	if (varData & bit) return 0;

	return 1;
}

void CCommonCardSystem::SetAppearCard(int card,int flg)
{
	if (m_appearControlFlag == 0) return;
	if (m_appearVarNumber == -1) return;

	int varData = m_game->GetVarData(m_appearVarNumber);
	int bit = m_bitPattern[card];
	
	if (flg)
	{
		varData &= ~bit;
	}
	else
	{
		varData |= bit;
	}
	m_game->SetVarData(m_appearVarNumber,varData);
}


void CCommonCardSystem::SetEnableCard(int card,int flg)
{
	if (m_enableControlFlag == 0) return;
	if (m_enableVarNumber == -1) return;

	int varData = m_game->GetVarData(m_enableVarNumber);
	int bit = m_bitPattern[card];
	
	if (flg)
	{
		varData &= ~bit;
	}
	else
	{
		varData |= bit;
	}
	m_game->SetVarData(m_enableVarNumber,varData);
}

void CCommonCardSystem::SetNoserareruCard(int card,int flg)
{
	if (m_noserareruControlFlag == 0) return;
	if (m_noserareruVarNumber == -1) return;

	int varData = m_game->GetVarData(m_noserareruVarNumber);
	int bit = m_bitPattern[card];
	
	if (flg)
	{
		varData &= ~bit;
	}
	else
	{
		varData |= bit;
	}
	m_game->SetVarData(m_noserareruVarNumber,varData);
}

void CCommonCardSystem::CheckPowerMaxByVar(void)
{
	if (m_powerMaxVarNumber != -1)
	{
		m_powerMax = m_game->GetVarData(m_powerMaxVarNumber);
	}
}

void CCommonCardSystem::Function(int type,int paraKosuu,int* lpParam)
{
	int para1 = 0;
	int para2 = 0;
	if (paraKosuu >= 1)
	{
		para1 = *lpParam;
	}
	if (paraKosuu >= 2)
	{
		para2 = *(lpParam + 1);
	}

	if (type == 0)
	{
		if ((para1 >= 1) && (para1 <= m_cardKosuu))
		{
			SetAppearCard(para1-1,para2);
		}
	}
	else if (type == 1)
	{
		if ((para1 >= 1) && (para1 <= m_cardKosuu))
		{
			SetEnableCard(para1-1,para2);
		}
	}
	else if (type == 2)
	{
		if ((para1 >= 1) && (para1 <= m_cardKosuu))
		{
			SetNoserareruCard(para1-1,para2);
		}
	}

}

void CCommonCardSystem::StartUserCommand(int paraKosuu,int* paraPtr)
{
}





/*_*/


