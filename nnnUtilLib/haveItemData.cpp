#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\myFile.h"

#include "..\nnnUtilLib\nameList.h"

#include "haveItemData.h"

char CHaveItemData::m_errorName[] = "エラー";
char CHaveItemData::m_errorVarName[] = "変数名エラー";
char CHaveItemData::m_errorFilename[] = "ta_error";

CHaveItemData::CHaveItemData()
{

	m_descMax = 16;

	m_list = new CNameList();
	m_list->LoadFile("nya\\haveItem.xtx");

	m_typeMax = 256;
	m_typeKosuu = new int[m_typeMax];
	for (int i=0;i<m_typeMax;i++)
	{
		m_typeKosuu[i] = 0;
	}


	int kosuu = m_list->GetNameKosuu();
	//count
	int n = 0;
	m_listKosuu = 0;
	while (n<kosuu)
	{
		LPSTR name = m_list->GetName(n);
		if (*name == '%')
		{
			m_listKosuu++;
		}

		n++;
	}

	m_table = new HAVEITEMDATA[m_listKosuu+1];
	for (int i=0;i<m_listKosuu;i++)
	{
		m_table[i].serial = i;
		m_table[i].type = 0;
		for (int k=0;k<16;k++)
		{
			m_table[i].name[k] = m_errorName;
		}
		m_table[i].varName = m_errorVarName;
		m_table[i].filename = m_errorFilename;
		for (int k=0;k<16;k++)
		{
			m_table[i].descNumber[k] = 0;
		}

		m_table[i].varNumber = -1;
	}

	m_descList = new LPSTR[m_listKosuu*m_descMax*16+1];
	for (int i=0;i<m_listKosuu*m_descMax*16;i++)
	{
		m_descList[i] = NULL;
	}

	n = 0;
	int listNumber = 0;
	int paramNumber = 0;
	int descKosuu[16];
	for (int k=0;k<16;k++)
	{
		descKosuu[k] = 0;
	}
	
	int special = 1;

	while (n<kosuu)
	{
		LPSTR name = m_list->GetName(n);
		if (*name == '%')
		{


			if (n != 0)
			{
				m_table[listNumber].descNumber[0] = descKosuu[1];
				for (int p=0;p<16;p++)
				{
					m_descList[(listNumber * 16 + 0) * m_descMax + p] = m_descList[(listNumber * 16 + 1) * m_descMax + p];
				}
				m_table[listNumber].descNumber[1] = descKosuu[1];
				for (int k=2;k<=special;k++)
				{
					m_table[listNumber].descNumber[k] = descKosuu[k];
				}
				for (int k=special+1;k<16;k++)
				{
					m_table[listNumber].descNumber[k] = descKosuu[1];
					for (int p=0;p<16;p++)
					{
						m_descList[(listNumber * 16 + k) * m_descMax + p] = m_descList[(listNumber * 16 + 1) * m_descMax + p];
					}
				}
				listNumber++;
			}

			paramNumber = 0;
			special = 1;
			for (int k=0;k<16;k++)
			{
				descKosuu[k] = 0;
			}

			name++;
		}
		else if (*name == '!')
		{
			paramNumber = 4;
			special++;
			name++;
		}


		if (paramNumber == 0)
		{
			m_table[listNumber].serial = atoi(name);
		}
		else if (paramNumber == 1)
		{
			int type = atoi(name);
			m_table[listNumber].type = atoi(name);
			if (type < m_typeMax)
			{
				m_typeKosuu[type]++;
			}
		}
		else if (paramNumber == 2)
		{
			m_table[listNumber].varName = name;
		}
		else if (paramNumber == 3)
		{
			m_table[listNumber].filename = name;
		}
		else if (paramNumber == 4)
		{
			m_table[listNumber].name[special] = name;
			if (special == 1)
			{
				for (int p=0;p<16;p++)
				{
					m_table[listNumber].name[p] = name;
				}
			}
		}
		else
		{
			if (descKosuu[special]<m_descMax)
			{
				if (*name != '@')
				{
					m_descList[(listNumber * 16 + special) * m_descMax + descKosuu[special]] = name;
				}
				else
				{
					m_descList[(listNumber * 16 + special) * m_descMax + descKosuu[special]] = NULL;
				}

				descKosuu[special]++;
			}
		}


		paramNumber++;
		n++;
	}


	m_table[listNumber].descNumber[0] = descKosuu[1];
	for (int p=0;p<16;p++)
	{
		m_descList[(listNumber * 16 + 0) * m_descMax + p] = m_descList[(listNumber * 16 + 1) * m_descMax + p];
	}
	m_table[listNumber].descNumber[1] = descKosuu[1];
	for (int k=2;k<=special;k++)
	{
		m_table[listNumber].descNumber[k] = descKosuu[k];
	}
	for (int k=special+1;k<16;k++)
	{
		m_table[listNumber].descNumber[k] = descKosuu[1];
		for (int p=0;p<16;p++)
		{
			m_descList[(listNumber * 16 + k) * m_descMax + p] = m_descList[(listNumber * 16 + 1) * m_descMax + p];
		}
	}



}

CHaveItemData::~CHaveItemData()
{
	End();
}

void CHaveItemData::End(void)
{
	DELETEARRAY(m_descList);
	DELETEARRAY(m_table);
	DELETEARRAY(m_typeKosuu);
	ENDDELETECLASS(m_list);
}

int CHaveItemData::GetDescNumber(int n,int md)
{
	if (!CheckN(n)) return 0;
	return m_table[n].descNumber[md];
}

LPSTR CHaveItemData::GetDesc(int n,int k,int md)
{
	if (!CheckN(n)) return NULL;
	if ((n<0) || (n>=m_descMax)) return NULL;
	return m_descList[(n*16+md)*m_descMax+k];
}

int CHaveItemData::GetSerial(int n)
{
	if (!CheckN(n)) return 0;
	return m_table[n].serial;
}

int CHaveItemData::GetType(int n)
{
	if (!CheckN(n)) return 0;
	return m_table[n].type;
}

LPSTR CHaveItemData::GetName(int n,int md)
{
	if (!CheckN(n)) return m_errorName;
	return m_table[n].name[md];
}

LPSTR CHaveItemData::GetVarName(int n)
{
	if (!CheckN(n)) return m_errorVarName;
	return m_table[n].varName;
}

LPSTR CHaveItemData::GetFilename(int n)
{
	if (!CheckN(n)) return m_errorFilename;
	return m_table[n].filename;
}

int CHaveItemData::GetVarNumber(int n)
{
	if (!CheckN(n)) return -1;
	return m_table[n].varNumber;
}

void CHaveItemData::SetVarNumber(int n,int d)
{
	if (!CheckN(n)) return;
	m_table[n].varNumber = d;
}

BOOL CHaveItemData::CheckN(int n)
{
	if ((n<0) || (n>=m_listKosuu)) return FALSE;
	return TRUE;
}

int CHaveItemData::GetTypeHaveNumber(int type)
{
	if ((type < 0) || (type >= m_typeMax)) return 0;
	return m_typeKosuu[type];
}


int CHaveItemData::GetListKosuu(void)
{
	return m_listKosuu;
}
/*_*/

