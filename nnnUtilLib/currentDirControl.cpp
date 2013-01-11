#include <windows.h>

#include "currentDirControl.h"

char CCurrentDirControl::m_dir[_MAX_PATH] = {0};

CCurrentDirControl::CCurrentDirControl()
{
}

CCurrentDirControl::~CCurrentDirControl()
{
	End();
}

void CCurrentDirControl::End(void)
{
}

void CCurrentDirControl::ChangeCurrentToExe(void)
{
	char fullPath[_MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char filename[_MAX_FNAME];
	char ext[_MAX_EXT];
	char exeDir[_MAX_PATH*5+1024];

	if (GetModuleFileName(NULL,fullPath,sizeof(fullPath)) == 0)
	{
		return;//error
	}
	_splitpath_s(fullPath,drive,dir,filename,ext);

	GetCurrentDirectory(sizeof(m_dir),m_dir);
	wsprintf(exeDir,"%s%s",drive,dir);

#if _DEBUG
	OutputDebugString("\n\n起動時のフォルダー:");
	OutputDebugString(m_dir);
	OutputDebugString("\nexeのフォルダー");
	OutputDebugString(exeDir);
	OutputDebugString("\n");
#else
	SetCurrentDirectory(exeDir);
#endif

}

void CCurrentDirControl::RestoreCurrent(void)
{
	if (m_dir[0] == 0) return;

#if _DEBUG
	OutputDebugString("\n\n復旧フォルダー:");
	OutputDebugString(m_dir);
	OutputDebugString("\n");
#else
	SetCurrentDirectory(m_dir);
#endif
}

/*_*/


