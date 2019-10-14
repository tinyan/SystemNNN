#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myFile.h"
#include "autoSelectControl.h"


CAutoSelectControl::CAutoSelectControl()
{
	m_levelMax = 1024;
	m_allEnd = FALSE;
	m_selectNumber = new int[m_levelMax];
	m_selected = new int[m_levelMax];
	m_level = 0;

	ClearPlayLevel();


	SYSTEMTIME tm;
	GetLocalTime(&tm);

	char mes[1024];
	wsprintf(mes,"\n%d”N %dŒŽ %d“ú %d:%d:%d\n",tm.wYear,tm.wMonth,tm.wDay, tm.wHour,tm.wMinute,tm.wSecond);

	FILE* file = CMyFile::OpenFullPath("selectlog.txt","ab");
	if (file != NULL)
	{
		fwrite(mes,sizeof(char),strlen(mes),file);
		fclose(file);
	}

}


CAutoSelectControl::~CAutoSelectControl()
{
	End();
}

void CAutoSelectControl::End(void)
{
	DELETEARRAY(m_selected);
	DELETEARRAY(m_selectNumber);
}

void CAutoSelectControl::ClearPlayLevel(void)
{
	m_playLevel = 0;
}

int CAutoSelectControl::GetSelect(int selectNumber)
{
	if (m_allEnd) return 0;

	if (m_playLevel >= m_level)
	{
		OutputDebugString("add new selectmax\n");
		//new
		m_selected[m_playLevel] = 0;
		m_selectNumber[m_playLevel] = selectNumber;

		m_playLevel++;
		m_level++;
		return 0;
	}


	//create new tree
	if (m_playLevel == 0)
	{
		for (int level=m_level-1;level>=0;level--)
		{
			int kosuu = m_selectNumber[level];
			int n = m_selected[level];
			n++;
			if (n<kosuu)
			{
				m_selected[level] = n;
				break;
			}

			OutputDebugString("remove tail\n");

			m_level--;
			if (level == 0)
			{
				m_allEnd = TRUE;
				return 0;
			}
		}
	}

	int rt = m_selected[m_playLevel];
	m_playLevel++;
	return rt;


	return 0;
}

void CAutoSelectControl::Finish(void)
{
	//log


	char mes[1024];
	mes[0] = 0;
	wsprintf(mes,"\x00d\x00aSELECT:");
	for (int i=0;i<m_playLevel;i++)
	{
		int ln = (int)strlen(mes);
		wsprintf(mes+ln,"-[%d] ",m_selected[i]+1);
	}

	FILE* file = CMyFile::OpenFullPath("selectlog.txt","ab");
	if (file != NULL)
	{
		fwrite(mes,sizeof(char),strlen(mes),file);
		fclose(file);
	}
}



/*_*/

