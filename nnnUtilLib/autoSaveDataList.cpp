#include <windows.h>

#include "autoSaveDataList.h"


char CAutoSaveDataList::m_list[][32]=
{
	"dummy",

	"face",

	"",//endmark
};


CAutoSaveDataList::CAutoSaveDataList()
{
}


CAutoSaveDataList::~CAutoSaveDataList()
{
	End();
}

void CAutoSaveDataList::End(void)
{
}

int CAutoSaveDataList::SearchName(LPSTR name)
{
	for (int i=1;i<256;i++)
	{
		LPSTR checkName = m_list[i];
		if ((*checkName) == 0)
		{
			return -1;
		}

		if (_stricmp(name,checkName) == 0)
		{
			return i;
		}
	}


	return -1;
}

/*_*/


