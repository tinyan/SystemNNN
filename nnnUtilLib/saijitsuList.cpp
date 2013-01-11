#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanLib\include\commonMacro.h"
#include "nameList.h"

#include "saijitsuList.h"

CSaijitsuList::CSaijitsuList()
{
	m_list = new CNameList();
	m_list->LoadFile("nya\\saijitsu.xtx");
	m_listKosuu = m_list->GetNameKosuu() / 3;
	m_data = new int[m_listKosuu * 3 + 1];
	for (int i=0;i<m_listKosuu*3;i++)
	{
		m_data[i] = atoi(m_list->GetName(i));
	}
}

CSaijitsuList::~CSaijitsuList()
{
	End();
}

void CSaijitsuList::End(void)
{
	DELETEARRAY(m_data);
	ENDDELETECLASS(m_list);
}

int CSaijitsuList::CheckSaijitsu(int year, int month, int day)
{
	for (int i=0;i<m_listKosuu;i++)
	{
		if (m_data[i*3+0] == year)
		{
			if (m_data[i*3+1] == month)
			{
				if (m_data[i*3+2] == day)
				{
					return 1;
				}
			}
		}
	}

	return 0;
}



/*_*/

