#include <windows.h>

#include <stdio.h>

#include "..\nyanlib\include\commonMacro.h"
#include "..\nyanlib\include\myfile.h"

#include "..\nnnUtilLib\mySaveFolder.h"

#include "commonResultData.h"


CCommonResultData::CCommonResultData(LPSTR filename,int kosuu,BOOL angouFlag,int paraKosuu,LPSTR subFolderName)
{
	m_filenameOnly = filename;
	m_subFolderName = subFolderName;

	m_dataMax = kosuu;
	m_paraMax = paraKosuu;
	m_angouFlag = angouFlag;

	m_data = new int[m_dataMax * m_paraMax];//
	m_editFlag = TRUE;
	
	if (m_subFolderName != NULL)
	{
		char filename[1024];
		wsprintf(filename,"%s\\%s",CMySaveFolder::GetFullFolder(),m_subFolderName);
		CreateDirectory(filename,NULL);
	}

	ClearData();
	Load();
}

CCommonResultData::~CCommonResultData()
{
	End();
}

void CCommonResultData::End(void)
{
	if (m_editFlag)
	{
		Save();
	}
	DELETEARRAY(m_data);
}

void CCommonResultData::ClearData(void)
{
	ZeroMemory(m_data,sizeof(int)*m_dataMax*m_paraMax);
	m_editFlag = TRUE;
}

void CCommonResultData::SetData(int resultNumber,int d,int para)
{
	if ((resultNumber >= 0) || (resultNumber < m_dataMax))
	{
		if ((para >= 0) && (para < m_paraMax))
		{
			m_data[resultNumber*m_paraMax + para] = d;
			m_editFlag = TRUE;
		}
	}
}

void CCommonResultData::AddData(int resultNumber,int d,int para)
{
	if ((resultNumber >= 0) || (resultNumber < m_dataMax))
	{
		if ((para >= 0) && (para < m_paraMax))
		{
			int dt = GetData(resultNumber,para);
			int d0 = dt;
			dt += d;

			if ((d>=0) && (dt<0) && (d0>=0))
			{
				dt = 0x7fffffff;
			}
			else if ((d<0) && (dt>=0) && (d0<0))
			{
				dt = 0x80000001;
			}
			
			m_data[resultNumber*m_paraMax + para] = dt;
			m_editFlag = TRUE;
		}
	}
}

int CCommonResultData::GetData(int resultNumber,int para)
{
	if ((resultNumber < 0) || (resultNumber >= m_dataMax))
	{
		return 0;//error!
	}

	if ((para < 0) || (para >= m_paraMax))
	{
		return 0;//error!
	}

	return m_data[resultNumber*m_paraMax + para];
}

BOOL CCommonResultData::Load(void)
{
	LPSTR filename = GetFileName();
	FILE* file = CMyFile::OpenFullPath(filename,"rb");
	if (file == NULL)
	{
		filename = GetFileName(TRUE);
		file = CMyFile::OpenFullPath(filename,"rb");
		if (file == NULL)
		{
			return FALSE;
		}
	}

	fread(m_data,sizeof(int),m_dataMax*m_paraMax,file);
	fclose(file);

	m_editFlag = FALSE;
	return TRUE;
}

BOOL CCommonResultData::Save(void)
{
	LPSTR filename = GetFileName();
	FILE* file = CMyFile::OpenFullPath(filename,"wb");
	if (file == NULL)
	{
		return FALSE;
	}


	fwrite(m_data,sizeof(int),m_dataMax*m_paraMax,file);
	fclose(file);

	m_editFlag = FALSE;
	return TRUE;
}

LPSTR CCommonResultData::GetFileName(BOOL orgFlag)
{
	m_filename[0] = 0;
	char extName[4];
	if (orgFlag)
	{
		memcpy(extName,"org",4);
	}
	else
	{
		memcpy(extName,"sav",4);
	}

	if (m_subFolderName == NULL)
	{
		wsprintf(m_filename,"%s\\%s.%s",CMySaveFolder::GetFullFolder(),m_filenameOnly,extName);
	}
	else
	{
		wsprintf(m_filename,"%s\\%s\\%s.%s",CMySaveFolder::GetFullFolder(),m_subFolderName,m_filenameOnly,extName);
	}

	return m_filename;
}

/*_*/

