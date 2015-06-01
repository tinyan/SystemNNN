#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGeo.h"

#include "..\nyanLib\include\myFile.h"

#include "nameList.h"
#include "systempicture.h"

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

		if (m_picFlag == 0)
		{
			sprintf_s(name,256,"%s_%dColorR",statusName,i+1);
			GetInitGameParam(&colorR,name);
			sprintf_s(name,256,"%s_%dColorG",statusName,i+1);
			GetInitGameParam(&colorG,name);
			sprintf_s(name,256,"%s_%dColorB",statusName,i+1);
			GetInitGameParam(&colorB,name);
			sprintf_s(name,256,"%s_%dColorA",statusName,i+1);
			GetInitGameParam(&colorA,name);
		}
		else
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






}

CCommonPlayStatusData::~CCommonPlayStatusData()
{
	End();
}

void CCommonPlayStatusData::End(void)
{
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

