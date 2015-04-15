#include <windows.h>

#include "commonSystemModeList.h"



char CCommonSystemModeList::m_systemClassNameList[][32]=
{
	"","nothing","logo","opening","title",
	"load","save","backlog","listenbgm","selectmessage",
	"printmessage","draw","config","systemmenu","printoverrap",
	"omake","selectcgchara","selectcg","selectscene","",
	"selectscenechara","","selectplace","printcg","selectzukan",
	"selectmoviechara","selectmovie","printmovie","","nameinput",
	"printcalendar","selectheroin","codecerror","printresult","selectchart",
	"selectplace2","","","","",
	"minigame","selectobject","","","",
	"cardsystem","","","","",

	"","","","","",
	"","","","","",
	"","","","","",
	"","","","","",
	"","","","","",
	"","","","","",
	"","","","","",
	"","","","","",
	"","","","","",
	"","","","","",
};

CCommonSystemModeList::CCommonSystemModeList()
{
}

CCommonSystemModeList::~CCommonSystemModeList()
{
	End();
}

void CCommonSystemModeList::End(void)
{
}


int CCommonSystemModeList::GetModeNumberByName(LPSTR name)
{
	int nm = -1;
	for (int i=1;i<100;i++)
	{
		LPSTR name2 = m_systemClassNameList[i];
		if ((*name2) != 0)
		{
			if (_stricmp(name,m_systemClassNameList[i]) == 0)
			{
				nm = i;
				break;
			}
		}
	}

	if (nm == -1)
	{
		nm = atoi(name);
	}

	return nm;
}

LPSTR CCommonSystemModeList::GetModeName(int n)
{
	if ((n<0) || (n>=100))
	{
		return m_systemClassNameList[0];
	}

	return m_systemClassNameList[n];
}

/*_*/

