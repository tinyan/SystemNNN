


#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"


#include "..\nnnUtilLib\nameList.h"


#include "printCard.h"
#include "printCardPower.h"


char CPrintCardPower::m_defaultPowerPicFileName[] = "ta_cardPower";


//level1-st1-card1,2,3, st2-card1,2,3 ...
//level2
//level3


CPrintCardPower::CPrintCardPower(CNameList* setup)
{
	m_setup = setup;

	m_cardPowerPicByCard = 0;
	GetInitGameParam(&m_cardPowerPicByCard ,"cardPowerPicByCard");
	m_cardShurui = 1;
	if (m_cardPowerPicByCard)
	{
		GetInitGameParam(&m_cardShurui,"cardNumber");
	}

	m_cardPowerPicByLevel = 1;
	GetInitGameParam(&m_cardPowerPicByLevel,"cardPowerPicByLevel");
	m_levelMax = 1;
	GetInitGameParam(&m_levelMax,"cardLevelMax");

	int useStatusSeat = 0;
	GetInitGameParam(&useStatusSeat,"cardPowerPicByStatus");
	for (int i=0;i<10;i++)
	{
		char name[256];

		int printType = CPrintCard::GetPrintType(i) + 1;
		wsprintf(name,"cardPowerPrintType%d",i+1);
		GetInitGameParam(&printType,name);
		m_printTypeTable[i] = printType - 1;

		int seatTable = 1;
		if (useStatusSeat)
		{
			seatTable = CPrintCard::GetSeatTable(i) + 1;
			wsprintf(name,"cardPowerSeatTable%d",i+1);
			GetInitGameParam(&seatTable,name);
		}
		m_seatTable[i] = seatTable - 1;
	}

	if (1)
	{
		int r = CPrintCard::GetAddColor(0);
		int g = CPrintCard::GetAddColor(1);
		int b = CPrintCard::GetAddColor(2);
		GetInitGameParam(&r,"cardPowerAddColorR");
		GetInitGameParam(&g,"cardPowerAddColorG");
		GetInitGameParam(&b,"cardPowerAddColorB");
		m_addColor[0] = r;
		m_addColor[1] = g;
		m_addColor[2] = b;
		m_percent = CPrintCard::GetPercent();
		GetInitGameParam(&m_percent,"cardPowerTransPercent");
	}

	int printX = 10;
	int printY = 10;
	GetInitGameParam(&printX,"cardPowerPrintX");
	GetInitGameParam(&printY,"cardPowerPrintY");
	int sizeX = 16;
	int sizeY = 16;
	GetInitGameParam(&sizeX,"cardPowerSizeX");
	GetInitGameParam(&sizeY,"cardPowerSizeY");
	int nextX = sizeX;
	int nextY = 0;
	GetInitGameParam(&nextX,"cardPowerNextX");
	GetInitGameParam(&nextY,"cardPowerNextY");

	m_zahyo.x = printX;
	m_zahyo.y = printY;
	m_size.cx = sizeX;
	m_size.cy = sizeY;
	m_next.x = nextX;
	m_next.y = nextY;

	m_pic = new CPicture();
	char filename[1024];
	LPSTR picName = m_defaultPowerPicFileName;
	GetInitGameString(&picName,"filenamecardPowerPic");

	wsprintf(filename,"sys\\%s",picName);
	m_pic->LoadDWQ(filename);
}


CPrintCardPower::~CPrintCardPower()
{
	End();
}

void CPrintCardPower::End(void)
{
	ENDDELETECLASS(m_pic);
}


void CPrintCardPower::Put(POINT cardPoint,int power,int st,int level,int card)
{
	int sizeX = m_size.cx;
	int sizeY = m_size.cy;

	int nn = m_seatTable[st];
	nn *= m_cardShurui;
	if (m_cardPowerPicByCard)
	{
		nn += card;
	}
	int srcX = nn * sizeX;

	int srcY = 0;
	if (m_cardPowerPicByLevel)
	{
		srcY = level * sizeY;
	}


	int putX0 = cardPoint.x + m_zahyo.x;
	int putY0 = cardPoint.y + m_zahyo.y;

	int nextX = m_next.x;
	int nextY = m_next.y;

	int printType = m_printTypeTable[st];

	for (int i=0;i<power;i++)
	{
		int putX = putX0 + i * nextX;
		int putY = putY0 + i * nextY;

		if (printType == 0)	//normal
		{
			m_pic->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
		}
		else if (st == 1)	//addcolor
		{
			m_pic->ColorAddBlt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE,m_addColor[0],m_addColor[1],m_addColor[2]);
		}
		else if (st == 2)	//trans
		{
			m_pic->TransLucentBlt3(putX,putY,srcX,srcY,sizeX,sizeY,m_percent);
		}
		else if (st == 3)//grey
		{
			m_pic->GreyBlt(putX,putY,srcX,srcY,sizeX,sizeY);
		}
		else	//red
		{
			m_pic->RedBlt(putX,putY,srcX,srcY,sizeX,sizeY);
		}

	}

}



BOOL CPrintCardPower::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CPrintCardPower::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CPrintCardPower::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CPrintCardPower::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}
