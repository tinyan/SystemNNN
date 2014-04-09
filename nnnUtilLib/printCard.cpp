

#include <windows.h>
#include <stdio.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\picture.h"
#include "..\nyanlib\include\areaControl.h"

#include "printCard.h"

//0:通常
//1:カーソルオン
//2:移動中
//3:選択不可(灰色)
//4:パワー不足(赤)
//5:乗った
//6:のせられた

//0:nop
//1:addcolor
//2:trans
//3:grey
//4:red

int CPrintCard::m_printType[] = {0,1,2,3,4,0,0,0,0,0};
int CPrintCard::m_seatTable[] = {0,0,0,0,0,0,0,0,0,0};
int CPrintCard::m_addColor[]= {64,96,32};
int CPrintCard::m_percent = 50;

CPrintCard::CPrintCard(LPSTR filenameTag,SIZE size,BOOL useType)
{
	int ln = strlen(filenameTag);
	m_filenameTag = new char[ln + 2];
	memcpy(m_filenameTag,filenameTag,ln+1);

//	m_filenameTag = filenameTag;
	m_cardSize = size;
	m_useType = useType;
	m_picType = -1;
	m_pic = new CPicture();

}

CPrintCard::~CPrintCard()
{
	End();
}

void CPrintCard::End(void)
{
	ENDDELETECLASS(m_pic);
	DELETEARRAY(m_filenameTag);
}

void CPrintCard::ChangePrintType(int n,int printType)
{
	if ((n<0) || (n>=10)) return;
	m_printType[n] = printType;
}

void CPrintCard::ChangeSaetTable(int n,int seatNumber)
{
	if ((n<0) || (n>=10)) return;
	m_seatTable[n] = seatNumber;
}

void CPrintCard::ChangeAddColor(int r,int g, int b)
{
	m_addColor[0] = r;
	m_addColor[1] = g;
	m_addColor[2] = b;
}

void CPrintCard::ChangePercent(int ps)
{
	m_percent = ps;
}

void CPrintCard::Put(POINT pt,int st,int type)
{
	LoadPic(type);
	if (type == -1) type = m_picType;

	int putX = pt.x;
	int putY = pt.y;
	int sizeX = m_cardSize.cx;
	int sizeY = m_cardSize.cy;
	int srcX = sizeX * m_seatTable[st];
	int srcY = 0;

	int printType = m_printType[st];

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


BOOL CPrintCard::LoadPic(int type)
{
	if (type == -1)
	{
		if (m_picType != -1) return TRUE;
	}

	char filename[1024];
	if (m_useType)
	{
		wsprintf(filename,"sys\\%s_%d",m_filenameTag,type+1);
	}
	else
	{
		wsprintf(filename,"sys\\%s",m_filenameTag);
	}

	m_pic->LoadDWQ(filename);

	m_picType = type;

	return TRUE;
}



/*_*/

