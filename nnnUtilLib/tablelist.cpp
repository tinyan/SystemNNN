#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"
#include "nameList.h"

#include "tableList.h"




CTableList::CTableList(LPSTR name,int paraKosuu,BOOL angouFlag,BOOL firstUseFlag,int work)
{
	m_paraKosuu = paraKosuu;
	m_createTableFlag = FALSE;
	m_userWorkKosuu = 0;
	for (int i=0;i<256;i++)
	{
		m_userWork[i] = NULL;
	}

	char filename[1024];
	if (work == -1)
	{
		m_list = new CNameList();
	}
	else
	{
		m_list = new CNameList(work);
	}

	if (angouFlag)
	{
		wsprintf(filename,"%s.fxf",name);
	}
	else
	{
		wsprintf(filename,"%s.xtx",name);
	}
	m_list->LoadFile(filename,angouFlag);

	int kosuu = m_list->GetNameKosuu();
	m_kosuu = kosuu / m_paraKosuu;

	m_min = 0;
	m_max = -1;

	m_table = NULL;
	m_data = NULL;


	m_firstUseFlag = firstUseFlag;
	int first = 1;
	if (firstUseFlag)
	{
		first = 0;
	}

	if ((m_kosuu>0) && (first < m_kosuu))
	{
		m_min = atoi(m_list->GetName(first * m_paraKosuu));
		m_max = m_min;
	}

	for (int i=first;i<m_kosuu;i++)
	{
		int d = atoi(m_list->GetName(i*m_paraKosuu));
		if (d<m_min) m_min = d;
		if (d>m_max) m_max = d;
	}

	m_tableKosuu = m_max - m_min + 1;
	if (m_tableKosuu > 0)
	{
		int i;
		m_table = new int[m_tableKosuu];
		for (i=0;i<m_tableKosuu;i++)
		{
			m_table[i] = -1;
		}

		for (i=first;i<m_kosuu;i++)
		{
			int n = atoi(m_list->GetName(i*m_paraKosuu));
			m_table[n-m_min] = i;
		}

		m_data = new int[m_kosuu * m_paraKosuu];
		for (i=0;i<m_kosuu*m_paraKosuu;i++)
		{
			m_data[i] = 0;
		}
	}
}



CTableList::~CTableList()
{
	End();
}

void CTableList::End(void)
{
	for (int i=0;i<m_userWorkKosuu;i++)
	{
		DELETEARRAY(m_userWork[i]);
	}
	m_userWorkKosuu = 0;

	DELETEARRAY(m_data);
	DELETEARRAY(m_table);
	ENDDELETECLASS(m_list);
}



void CTableList::CreateAtoi(int* lpFlag)
{
	int first = 1;
	if (m_firstUseFlag)
	{
		first = 0;
	}

	for (int i=first;i<m_kosuu;i++)
	{
		for (int k=0;k<m_paraKosuu;k++)
		{
			BOOL f = TRUE;
			if (lpFlag != NULL)
			{
				if ((lpFlag[k]) == 0)
				{
					f = FALSE;
				}
			}

			if (f)
			{
				m_data[i*m_paraKosuu+k] = atoi(m_list->GetName(i*m_paraKosuu+k));
			}
		}
	}
	m_createTableFlag = TRUE;
}


int CTableList::GetParam(int n,int k)
{
	int table = N2Table(n);
	if (m_table == NULL) return 0;

	if (table == -1)
	{
		return 0;	//error!
	}

	if (m_createTableFlag)
	{
		return m_data[table*m_paraKosuu+k];
	}
	return atoi(m_list->GetName(table*m_paraKosuu+k));
}

LPSTR CTableList::GetName(int n,int k)
{
	int table = N2Table(n);
	if (table == -1)
	{
		return NULL;
	}
	return m_list->GetName(table*m_paraKosuu+k);

}

void CTableList::SetParam(int n,int k,int d,BOOL nameSetFlag)
{
	int table = N2Table(n);
	if (m_table == NULL) return;

	if (table == -1)
	{
		return;	//error!
	}


	if (m_createTableFlag)
	{
		m_data[table*m_paraKosuu+k] = d;
	}

	if (nameSetFlag)
	{
		char name[128];
		wsprintf(name,"%d",d);
		m_list->SetName(table*m_paraKosuu+k,name);
	}
}


int CTableList::N2Table(int n)
{
	int table = -1;
	if ((n>=m_min) && (n<=m_max))
	{
		table = m_table[n-m_min];
	}
	
	if (table == -1)
	{
		if (m_min == -1)
		{
			table = m_table[0];
		}
	}

	return table;
}


int CTableList::GetListKosuu(void)
{
	if (m_firstUseFlag)
	{
		return m_kosuu;
	}
	return m_kosuu - 1;
}


int CTableList::GetListNumber(int n)
{
	int kosuu = m_kosuu;
	int st = 0;

	if (m_firstUseFlag == FALSE)
	{
		st = 1;
	}

	int k = n + st;
	if ((k<st) || (k>kosuu)) return -1;

	return 	m_data[k*m_paraKosuu];
}



BOOL CTableList::CreateUserWork(void)
{
	if (m_userWorkKosuu >= 256) return FALSE;

	int k = m_max - m_min + 1;
	m_userWork[m_userWorkKosuu] = new int[k];
	for (int i=0;i<k;i++)
	{
		m_userWork[m_userWorkKosuu][i] = 0;
	}
	m_userWorkKosuu++;

	return TRUE;
}

int CTableList::GetUserData(int n,int workNumber)
{
	if ((workNumber<0) || (workNumber>= m_userWorkKosuu)) return 0;
	int* ptr = m_userWork[workNumber];
	if (ptr == NULL) return 0;
	if ((n<m_min) || (n>m_max)) return 0;

	return ptr[n - m_min];
}

void CTableList::SetUserData(int n,int d,int workNumber)
{
	if ((workNumber<0) || (workNumber>= m_userWorkKosuu)) return;
	int* ptr = m_userWork[workNumber];
	if (ptr == NULL) return;
	if ((n<m_min) || (n>m_max)) return;

	ptr[n - m_min] = d;
}

/*_*/

