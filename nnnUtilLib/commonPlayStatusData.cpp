#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGeo.h"

#include "..\nyanLib\include\myFile.h"

#include "nameList.h"
#include "systempicture.h"

#include "polygonShape.h"


#include "CommonPlayStatusData.h"

char CCommonPlayStatusData::m_errorName[] = "エラー";
char CCommonPlayStatusData::m_errorVarName[] = "変数名エラー";
char CCommonPlayStatusData::m_errorFilename[] = "ta_error";

CCommonPlayStatusData::CCommonPlayStatusData(CNameList* setup,LPSTR statusName)
{
	m_setupList = setup;

	m_graphNumber = 1;
	char name[256];
	sprintf_s(name,256,"%sGraphNumber",statusName);
	GetInitGameParam(&m_graphNumber,name);
	m_graphType = 1;
	sprintf_s(name,256,"%sGraphType",statusName);
	GetInitGameParam(&m_graphType,name);
	//1:横棒グラフ、2:縦棒グラフ、3:円グラフ、4:折れ線グラフ、5:レーダーチャート

	m_size = new SIZE[m_graphNumber];
	int sizeX = 64;
	int sizeY = 64;
	for (int i=0;i<m_graphNumber;i++)
	{
		sprintf_s(name,256,"%s_%dSizeX",statusName,i+1);
		GetInitGameParam(&sizeX,name);
		sprintf_s(name,256,"%s_%dSizeY",statusName,i+1);
		GetInitGameParam(&sizeY,name);
		m_size[i].cx = sizeX;
		m_size[i].cy = sizeY;
	}

	m_zahyo = new POINT[m_graphNumber];
	int printX = 0;
	int printY = 0;
	int nextX = 0;
	int nextY = 0;

	sprintf_s(name,256,"%sNextX",statusName);
	GetInitGameParam(&nextX,name);
	sprintf_s(name,256,"%sNextY",statusName);
	GetInitGameParam(&nextY,name);

	for (int i=0;i<m_graphNumber;i++)
	{
		sprintf_s(name,256,"%s_%dPrintX",statusName,i+1);
		GetInitGameParam(&printX,name);
		sprintf_s(name,256,"%s_%dPrintY",statusName,i+1);
		GetInitGameParam(&printY,name);
		m_zahyo[i].x = printX;
		m_zahyo[i].y = printY;

		printX += nextX;
		printY += nextY;
	}

	m_varName = new LPSTR[m_graphNumber];
	m_varNumber = new int[m_graphNumber];
	m_data = new int[m_graphNumber];


	for (int i=0;i<m_graphNumber;i++)
	{
		sprintf_s(name,256,"%s_%dVarName",statusName,i+1);
		LPSTR varName = m_errorVarName;
		GetInitGameString(&varName,name);
		m_varName[i] = varName;
	}


	m_max = new int[m_graphNumber];
	int maxValue = 100;
	for (int i=0;i<m_graphNumber;i++)
	{
		sprintf_s(name,256,"%s_%dMax",statusName,i+1);
		GetInitGameParam(&maxValue,name);
		m_max[i] = maxValue;
	}

	m_circleSet = 0;
	sprintf_s(name,256,"%sCircleSet",statusName);
	GetInitGameParam(&m_circleSet,name);

	//file or color
	int lp = m_graphNumber;
	if (m_graphType == 4) lp = 0;
	if (m_graphType == 5) lp = 1;

	m_pic = new CPicture*[m_graphNumber];
	m_color = new int[m_graphNumber * 4];
	int colorR = 255;
	int colorG = 255;
	int colorB = 255;
	int colorA = 255;

	m_picFlag = 0;
	sprintf_s(name,256,"%sPicFlag",statusName);
	GetInitGameParam(&m_picFlag,name);

	LPSTR picname = NULL;
	for (int i=0;i<m_graphNumber;i++)
	{
		m_pic[i] = NULL;

		sprintf_s(name,256,"%s_%dColorR",statusName,i+1);
		GetInitGameParam(&colorR,name);
		sprintf_s(name,256,"%s_%dColorG",statusName,i+1);
		GetInitGameParam(&colorG,name);
		sprintf_s(name,256,"%s_%dColorB",statusName,i+1);
		GetInitGameParam(&colorB,name);
		sprintf_s(name,256,"%s_%dColorA",statusName,i+1);
		GetInitGameParam(&colorA,name);
		if (m_picFlag)
		{
			sprintf_s(name,256,"%s_%dfilename",statusName,i+1);
			GetInitGameString(&picname,name);
			m_pic[i] = CSystemPicture::GetSystemPicture(picname);
		}

		m_color[i*4+0] = colorR;
		m_color[i*4+1] = colorG;
		m_color[i*4+2] = colorB;
		m_color[i*4+3] = colorA;
	}


	m_polygonShape = NULL;
	if ((m_graphType == 3) || (m_graphType == 5))
	{
		m_polygonShape = new CPolygonShape*[m_graphNumber];
		for (int i=0;i<m_graphNumber;i++)
		{
			m_polygonShape[i] = new CPolygonShape(m_size[i].cx,m_size[i].cy);
		}
	}

	m_lineSize = 3;
	sprintf_s(name,256,"%sLineSize",statusName);
	GetInitGameParam(&m_lineSize,name);

	m_perFlag = 0;
	sprintf_s(name,256,"%sPerFlag",statusName);
	GetInitGameParam(&m_perFlag,name);

}

CCommonPlayStatusData::~CCommonPlayStatusData()
{
	End();
}

void CCommonPlayStatusData::End(void)
{
	if (m_polygonShape != NULL)
	{
		for (int i=0;i<m_graphNumber;i++)
		{
			ENDDELETECLASS(m_polygonShape[i]);
		}
		DELETEARRAY(m_polygonShape);
	}

	DELETEARRAY(m_color);
	DELETEARRAY(m_pic);
	DELETEARRAY(m_max);
	DELETEARRAY(m_data);
	DELETEARRAY(m_varNumber);
	DELETEARRAY(m_varName);
	DELETEARRAY(m_zahyo);
	DELETEARRAY(m_size);
}


void CCommonPlayStatusData::Print(int ps)
{
	m_percent = ps;

	switch (m_graphType)
	{
		case 1:
			PrintYokoGraph();
			break;
		case 2:
			PrintTateGraph();
			break;
		case 3:
			PrintCircleGraph();
			break;
		case 4:
			PrintOresenGraph();
			break;
		case 5:
			PrintRadarGraph();
			break;
		default:
			break;
	}
}


void CCommonPlayStatusData::PrintYokoGraph(void)
{
	for (int i=0;i<m_graphNumber;i++)
	{
		int maxSizeX = m_size[i].cx;
		int maxSizeY = m_size[i].cy;
		int d = m_data[i];
		int dv = m_max[i];
		int sizeX = (maxSizeX * d * m_percent) / (dv * 100);
		int sizeY = maxSizeY;
		if (sizeX > 0)
		{
			int putX = m_zahyo[i].x;
			int putY = m_zahyo[i].y;
			int srcX = 0;
			int srcY = 0;
			if (m_picFlag)
			{
				m_pic[i]->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
			}
			else
			{
				int r = m_color[i*4+0];
				int g = m_color[i*4+1];
				int b = m_color[i*4+2];
				int ps = m_color[i*4+3] / 255;
				if (ps == 100)
				{
					CAllGeo::BoxFill(putX,putY,sizeX,sizeY,r,g,b);
				}
				else
				{
					CAllGeo::TransBoxFill(putX,putY,sizeX,sizeY,r,g,b,ps);
				}
			}
		}
	}
}

void CCommonPlayStatusData::PrintTateGraph(void)
{
	for (int i=0;i<m_graphNumber;i++)
	{
		int maxSizeX = m_size[i].cx;
		int maxSizeY = m_size[i].cy;
		int d = m_data[i];
		int dv = m_max[i];
		int sizeY = (maxSizeY * d * m_percent) / (dv * 100);
		int sizeX = maxSizeX;
		if (sizeY > 0)
		{
			int putX = m_zahyo[i].x;
			int putY = m_zahyo[i].y;
			putY -= (sizeY-1);
			int srcX = 0;
			int srcY = maxSizeY-sizeY;
			if (m_picFlag)
			{
				m_pic[i]->Blt(putX,putY,srcX,srcY,sizeX,sizeY,TRUE);
			}
			else
			{
				int r = m_color[i*4+0];
				int g = m_color[i*4+1];
				int b = m_color[i*4+2];
				int ps = m_color[i*4+3] / 255;
				if (ps == 100)
				{
					CAllGeo::BoxFill(putX,putY,sizeX,sizeY,r,g,b);
				}
				else
				{
					CAllGeo::TransBoxFill(putX,putY,sizeX,sizeY,r,g,b,ps);
				}
			}
		}
	}
}

void CCommonPlayStatusData::PrintRadarGraph(void)
{
	int x = m_zahyo[0].x;
	int y = m_zahyo[0].y;

	for (int i=0;i<m_graphNumber;i++)
	{
		int r = m_color[i*4+0];
		int g = m_color[i*4+1];
		int b = m_color[i*4+2];
		int a = m_color[i*4+3];

		int data1 = m_data[i];
		int data2 = m_data[(i+1)%m_graphNumber];
		int mx = m_max[i];
		m_polygonShape[i]->SetRadarShape(m_graphNumber,i,data1,data2,mx);
		if (m_picFlag)
		{
			m_polygonShape[i]->PrintRadar(m_pic[i],x,y);
		}
		else
		{
			m_polygonShape[i]->PrintRadar(r,g,b,a,x,y);
		}
	}
}

void CCommonPlayStatusData::PrintOresenGraph(void)
{
	for (int i=0;i<m_graphNumber;i++)
	{
		int n2 = i+1;
		if (n2 >= m_graphNumber) n2 = 0;

		int x1 = m_zahyo[i].x;
		int y1 = m_zahyo[i].y;
		int x2 = m_zahyo[n2].x;
		int y2 = m_zahyo[n2].y;
		int mx1 = m_max[i];
		int mx2 = m_max[n2];
		int data1 = m_data[i];
		int data2 = m_data[n2];
		if (mx1 < 1) mx1 = 1;
		if (mx2 < 1) mx2 = 1;
		int dy1 = m_size[i].cy;
		int dy2 = m_size[n2].cy;
		dy1 *= data1;
		dy1 /= mx1;
		dy2 *= data2;
		dy2 /= mx1;

		y1 -= dy1;
		y2 -= dy2;

		int r = m_color[i*4+0];
		int g = m_color[i*4+1];
		int b = m_color[i*4+2];
		int a = m_color[i*4+3];

		if (i < m_graphNumber-1)
		{
			int delta = m_lineSize / 2;
			for (int jj=0;jj<m_lineSize;jj++)
			{
				for (int ii=0;ii<m_lineSize;ii++)
				{
					CAllGeo::Line(x1-delta+ii,y1-delta+jj,x2-delta+ii,y2-delta+jj,r,g,b,100);
				}
			}

		}

		if (m_picFlag)
		{
			if (m_pic[i] != NULL)
			{
				SIZE sz = m_pic[i]->GetPicSize();
				m_pic[i]->Put(x1-sz.cx/2,y1-sz.cy/2,TRUE);
			}
		}

	}


}

void CCommonPlayStatusData::PrintCircleGraph(void)
{
	int x = m_zahyo[0].x;
	int y = m_zahyo[0].y;

//	int debug[4] = {60,40};
//	int debugColor[8] = {255,0,0,128,0,255,0,128};
	int start = 0;

	int mx = m_max[0];
	if (m_perFlag)
	{
		mx = 0;
		for (int i=0;i<m_graphNumber;i++)
		{
			mx += m_data[i];
		}
		if (mx<1) mx = 1;
	}

	for (int i=0;i<m_graphNumber;i++)
	{
		int r = m_color[i*4+0];
		int g = m_color[i*4+1];
		int b = m_color[i*4+2];
		int a = m_color[i*4+3];

//		r = debugColor[i*4+0];
//		g = debugColor[i*4+1];
//		b = debugColor[i*4+2];
//		a = debugColor[i*4+3];

		int data1 = m_data[i];

//		data1 = debug[i];

		int end = start + data1;
		//int mx = m_max[i];
		m_polygonShape[i]->SetCircleShape(end,start,mx);
		if (m_picFlag)
		{
			m_polygonShape[i]->PrintCircleGraph(m_pic[i],x,y);
		}
		else
		{
			m_polygonShape[i]->PrintCircleGraph(r,g,b,a,x,y);
		}
		start += data1;
	}
}

int CCommonPlayStatusData::GetGraphNumber(void)
{
	return m_graphNumber;
}


LPSTR CCommonPlayStatusData::GetVarName(int n)
{
	if (!CheckN(n)) return m_errorVarName;
	return m_varName[n];
}

/*
LPSTR CCommonPlayStatusData::GetFilename(int n)
{
	if (!CheckN(n)) return m_errorFilename;
	return m_table[n].filename;
}
*/

int CCommonPlayStatusData::GetVarNumber(int n)
{
	if (!CheckN(n)) return -1;
	return m_varNumber[n];
}

void CCommonPlayStatusData::SetVarNumber(int n,int d)
{
	if (!CheckN(n)) return;
	m_varNumber[n] = d;
}

void CCommonPlayStatusData::SetData(int n,int d)
{
	if (!CheckN(n)) return;
	m_data[n] = d;
}

BOOL CCommonPlayStatusData::CheckN(int n)
{
	if ((n<0) || (n>=m_graphNumber)) return FALSE;
	return TRUE;
}




BOOL CCommonPlayStatusData::GetInitGameParam(int* lpVar, LPSTR name)
{
	if (m_setupList == NULL) return FALSE;

	int rNum = m_setupList->SearchName2(name);
	if (rNum == -1) return FALSE;
	*lpVar = atoi(m_setupList->GetName(rNum + 1));

	return TRUE;
}


BOOL CCommonPlayStatusData::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	if (m_setupList == NULL) return FALSE;

	int rNum = m_setupList->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setupList->GetName(rNum + 1);

	return TRUE;
}

/*_*/

