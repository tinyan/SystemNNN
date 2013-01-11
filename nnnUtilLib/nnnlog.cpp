#include <windows.h>
#include <stdio.h>

#include "nnnlog.h"

char CNNNLog::m_logFileName[1024] = "_";
BOOL CNNNLog::m_errorLogFlag = FALSE;

CNNNLog::CNNNLog()
{
}

CNNNLog::~CNNNLog()
{
	End();
}

void CNNNLog::End(void)
{
}

void CNNNLog::StartLog(void)
{
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	wsprintf(m_logFileName,"%d”N%dŒŽ%d“ú%dŽž%d•ª%d•b.txt",tm.wYear,tm.wMonth,tm.wDay,tm.wHour,tm.wMinute,tm.wSecond);
	m_errorLogFlag = TRUE;
}

void CNNNLog::AddLog(LPSTR mes)
{
	if (m_errorLogFlag == 0) return;

	FILE* file = NULL;
	fopen_s(&file,m_logFileName,"ab");
	if (file != NULL)
	{
		fwrite(mes,sizeof(char),strlen(mes),file);
		fwrite("\x00d\x00a",sizeof(char),2,file);
		fclose(file);
	}

}

/*_*/

