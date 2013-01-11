


#include <windows.h>
#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myGraphics.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"
#include "..\nyanLib\include\allGeo.h"

#include "..\nnnUtilLib\nameList.h"


#include "printSpectrum.h"




CPrintSpectrum::CPrintSpectrum(int printKosuu,CNameList *setup)
{
	m_setup = setup;
//	GetInitGameParam(&m_printKosuu,"spectrumPrintNumber",16);
	m_printKosuu = printKosuu;
	GetInitGameParam(&m_printType,"spectrumPrintType",2);


	m_data = new int[m_printKosuu];
	m_maxData = new int[m_printKosuu];
	m_maxWait = new int[m_printKosuu];
	m_maxG = new int[m_printKosuu];

	GetInitGameParam(&m_maxWaitTime,"spectrumMaxWaitTime",15);
	GetInitGameParam(&m_maxGrav,"spectrumMaxGrav",1);

	GetInitGameParam(&m_printX,"spectrumPrintX",0);
	GetInitGameParam(&m_printY,"spectrumPrintY",600);
	
	GetInitGameParam(&m_sizeX,"spectrumSizeX",4);
	GetInitGameParam(&m_sizeY,"spectrumSizeY",60);
	GetInitGameParam(&m_nextX,"spectrumNextX",m_sizeX+1);

	GetInitGameParam(&m_maxSizeY,"spectrumMaxSizeY",2);


	GetInitGameParam(&m_colorR,"spectrumColorR",128);
	GetInitGameParam(&m_colorG,"spectrumColorG",255);
	GetInitGameParam(&m_colorB,"spectrumColorB",192);
	GetInitGameParam(&m_percent,"spectrumPercent",100);

	GetInitGameParam(&m_maxColorR,"spectrumMaxColorR",255);
	GetInitGameParam(&m_maxColorG,"spectrumMaxColorG",0);
	GetInitGameParam(&m_maxColorB,"spectrumMaxColorB",0);
	GetInitGameParam(&m_maxPercent,"spectrumMaxPercent",100);




	Init();
}



CPrintSpectrum::~CPrintSpectrum()
{
	End();
}

void CPrintSpectrum::End(void)
{
	DELETEARRAY(m_maxG);
	DELETEARRAY(m_maxWait);
	DELETEARRAY(m_maxData);
	DELETEARRAY(m_data);
}


void CPrintSpectrum::Init(void)
{
	for (int i=0;i<m_printKosuu;i++)
	{
		m_data[i] = 0;
		m_maxData[i] = 0;
		m_maxWait[i] = 0;
		m_maxG[i] = 0;
	}
}

void CPrintSpectrum::Print(int* data)
{
	//set
	for (int i=0;i<m_printKosuu;i++)
	{
		//max
		int d = *(data+i);
		if (d > m_maxData[i])
		{
			m_maxData[i] = d;
			m_maxWait[i] = m_maxWaitTime;
			m_maxG[i] = 0;
		}
		m_data[i] = d;
	}

	//down
	for (int i=0;i<m_printKosuu;i++)
	{
		int maxCount = m_maxWait[i];
		if (maxCount > 0)
		{
			maxCount--;
			m_maxWait[i] = maxCount;
		}
		else
		{
			int maxData = m_maxData[i];
			int nowData = m_data[i];
			maxData -= m_maxG[i];
			if (maxData < nowData)
			{
				maxData = nowData;
				m_maxG[i] = 0;
				m_maxData[i] = maxData;
				m_maxWait[i] = m_maxWaitTime;
			}
			else
			{
				m_maxData[i] = maxData;
				m_maxG[i] += m_maxGrav;
			}
		}
	}

	//print
	if (m_printType >= 1)
	{
		for (int i=0;i<m_printKosuu;i++)
		{
			int putX = m_printX + m_nextX * i;
			int putY = m_printY;
			int sizeX = m_sizeX;
			int d = m_data[i];
			if (d>100) d = 100;
			int sizeY = (m_sizeY * d)/100;
			putY -= sizeY;
			CAllGeo::TransBoxFill(putX,putY,sizeX,sizeY,m_colorR,m_colorG,m_colorB,m_percent);
		}
	}

	//max
	if (m_printType >= 2)
	{
		for (int i=0;i<m_printKosuu;i++)
		{
			int putX = m_printX + m_nextX * i;
			int putY = m_printY;
			int sizeX = m_sizeX;
			int sizeY = m_maxSizeY;
			int d = m_maxData[i];
			if (d>100) d = 100;
			int deltaY = (m_sizeY * d)/100;
			putY -= deltaY;
			putY -= sizeY;
			CAllGeo::TransBoxFill(putX,putY,sizeX,sizeY,m_maxColorR,m_maxColorG,m_maxColorB,m_maxPercent);
		}
	}

}



BOOL CPrintSpectrum::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CPrintSpectrum::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_setup->GetName(rNum + 1));

	return TRUE;
}

BOOL CPrintSpectrum::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CPrintSpectrum::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_setup->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setup->GetName(rNum + 1);

	return TRUE;
}
