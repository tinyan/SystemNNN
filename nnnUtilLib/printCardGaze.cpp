


#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\nameList.h"


#include "printCard.h"
#include "printCardGaze.h"

char CPrintCardGaze::m_defaultCardGazeFileName[] = "ta_cardBar";

//gage‚ª³‚µ‚¢’Ô‚è


CPrintCardGaze::CPrintCardGaze(CNameList *setup)
{
	m_setup = setup;
	m_tate = 0;
	GetInitGameParam(&m_tate,"cardBarTate");

	m_pic = new CPicture();
	LPSTR fname = m_defaultCardGazeFileName;
	GetInitGameString(&fname,"filenameCardBar");
	if (1)
	{
		char filename[1024];
		wsprintf(filename,"sys\\%s",fname);
		m_pic->LoadDWQ(filename);
	}

	m_typeKosuu = 1;
	GetInitGameParam(&m_typeKosuu,"cardBarTypeNumber");


	m_size = new SIZE[m_typeKosuu];
	int sizeX = 100;
	int sizeY = 30;
	GetInitGameParam(&sizeX,"cardBarSizeX");
	GetInitGameParam(&sizeY,"cardBarSizeY");
	m_size[0].cx = sizeX;
	m_size[0].cy = sizeY;

	for (int i=0;i<m_typeKosuu;i++)
	{
		int sx = sizeX;
		int sy = sizeY;
		if (i>0)
		{
			sx = m_size[i-1].cx;
			sy = m_size[i-1].cy;
		}
		char name[1024];
		
		wsprintf(name,"cardBarSizeX%d",i+1);
		GetInitGameParam(&sx,name);
		m_size[i].cx = sx;

		wsprintf(name,"cardBarSizeY%d",i+1);
		GetInitGameParam(&sy,name);
		m_size[i].cy = sy;

	}

	m_zahyo = new POINT[m_typeKosuu];
	int printX = 0;
	int printY = 0;
	GetInitGameParam(&printX,"cardBarPrintX");
	GetInitGameParam(&printY,"cardBarPrintY");
	m_zahyo[0].x = printX;
	m_zahyo[0].y = printY;

	for (int i=0;i<m_typeKosuu;i++)
	{
		int px = printX;
		int py = printY;
		if (i>0)
		{
			px = m_zahyo[i-1].x;
			py = m_zahyo[i-1].y;
		}

		char name[1024];

		wsprintf(name,"cardBarPrintX%d",i+1);
		GetInitGameParam(&px,name);
		m_zahyo[i].x = px;

		wsprintf(name,"cardBarPrintY%d",i+1);
		GetInitGameParam(&py,name);
		m_zahyo[i].y = py;
	}



}



CPrintCardGaze::~CPrintCardGaze()
{
	End();
}

void CPrintCardGaze::End(void)
{
	DELETEARRAY(m_zahyo);
	DELETEARRAY(m_size);
	ENDDELETECLASS(m_pic);
}



void CPrintCardGaze::Put(POINT cardPoint,int gaze,int st)
{
	int putX = cardPoint.x;
	int putY = cardPoint.y;
	int sizeX = gaze;
	int sizeY = 16;
	int r = 255;
	int g = 192;
	int b = 128;

	CAllGeo::BoxFill(putX,putY,sizeX,sizeY,r,g,b);

}




BOOL CPrintCardGaze::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CPrintCardGaze::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CPrintCardGaze::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CPrintCardGaze::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}
