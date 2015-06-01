#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\myFile.h"

#include "..\nnnUtilLib\nameList.h"

#include "ShopItemData.h"

char CShopItemData::m_errorName[] = "エラー";
char CShopItemData::m_errorVarName[] = "変数名エラー";
char CShopItemData::m_errorFilename[] = "ta_error";

CShopItemData::CShopItemData(BOOL angouFlag)
{

	m_descMax = 16;

	m_list = new CNameList();

	if (angouFlag)
	{
		m_list->LoadFile("nya\\shopItem.xfx",TRUE);
	}
	else
	{
		m_list->LoadFile("nnndir\\shopItem.txt");
	}

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


	m_table = new SHOPITEMDATA[m_listKosuu+1];
	for (int i=0;i<m_listKosuu;i++)
	{
		m_table[i].serial = i;
		m_table[i].type = 0;
		m_table[i].price = 1;
		m_table[i].limit = 1;

		m_table[i].name = m_errorName;

		m_table[i].appearVarName = m_errorVarName;
		m_table[i].targetVarName = m_errorVarName;
		m_table[i].appearVarNumber = -1;
		m_table[i].targetVarNumber = -1;

		m_table[i].filename = m_errorFilename;
		m_table[i].descNumber = 0;

	}

	m_descList = new LPSTR[m_listKosuu*m_descMax+1];
	for (int i=0;i<m_listKosuu*m_descMax;i++)
	{
		m_descList[i] = NULL;
	}

	n = 0;
	int listNumber = 0;
	int paramNumber = 0;
	int descKosuu=0;
	
//	int special = 1;

	while (n<kosuu)
	{
		LPSTR name = m_list->GetName(n);
		if (*name == '%')
		{
			if (n != 0)
			{
				m_table[listNumber].descNumber = descKosuu;

//				for (int p=0;p<16;p++)
//				{
//					m_descList[listNumber * m_descMax + p] = m_descList[(listNumber * 16 + 1) * m_descMax + p];
//				}
				listNumber++;
			}

			paramNumber = 0;
//			special = 1;
			descKosuu = 0;

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
			m_table[listNumber].price = atoi(name);
		}
		else if (paramNumber == 3)
		{
			m_table[listNumber].limit = atoi(name);
		}
		else if (paramNumber == 4)
		{
			m_table[listNumber].name = name;
		}
		else if (paramNumber == 5)
		{
			m_table[listNumber].filename = name;
		}
		else if (paramNumber == 6)
		{
			m_table[listNumber].appearVarName = name;
		}
		else if (paramNumber == 7)
		{
			m_table[listNumber].targetVarName = name;
		}
		else
		{
			if (descKosuu<m_descMax)
			{
				if (*name != '@')
				{
					m_descList[listNumber * m_descMax + descKosuu] = name;
				}
				else
				{
					m_descList[listNumber * m_descMax + descKosuu] = NULL;
				}

				descKosuu++;
			}
		}

		paramNumber++;
		n++;
	}

	m_table[listNumber].descNumber = descKosuu;
}

CShopItemData::~CShopItemData()
{
	End();
}

void CShopItemData::End(void)
{
	DELETEARRAY(m_descList);
	DELETEARRAY(m_table);
	DELETEARRAY(m_typeKosuu);
	ENDDELETECLASS(m_list);
}

int CShopItemData::GetDescNumber(int n,int md)
{
	if (!CheckN(n)) return 0;
	return m_table[n].descNumber;
}

LPSTR CShopItemData::GetDesc(int n,int k,int md)
{
	if (!CheckN(n)) return NULL;
	if ((n<0) || (n>=m_descMax)) return NULL;
	return m_descList[n*m_descMax+k];
}

int CShopItemData::GetSerial(int n)
{
	if (!CheckN(n)) return 0;
	return m_table[n].serial;
}

int CShopItemData::GetType(int n)
{
	if (!CheckN(n)) return 0;
	return m_table[n].type;
}

int CShopItemData::GetPrice(int n)
{
	if (!CheckN(n)) return 0;
	return m_table[n].price;
}

int CShopItemData::GetLimit(int n)
{
	if (!CheckN(n)) return 0;
	return m_table[n].limit;
}

LPSTR CShopItemData::GetName(int n,int md)
{
	if (!CheckN(n)) return m_errorName;
	return m_table[n].name;
}


LPSTR CShopItemData::GetFilename(int n)
{
	if (!CheckN(n)) return m_errorFilename;
	return m_table[n].filename;
}

LPSTR CShopItemData::GetAppearVarName(int n)
{
	if (!CheckN(n)) return m_errorVarName;
	return m_table[n].appearVarName;
}

LPSTR CShopItemData::GetTargetVarName(int n)
{
	if (!CheckN(n)) return m_errorVarName;
	return m_table[n].targetVarName;
}

int CShopItemData::GetAppearVarNumber(int n)
{
	if (!CheckN(n)) return -1;
	return m_table[n].appearVarNumber;
}

int CShopItemData::GetTargetVarNumber(int n)
{
	if (!CheckN(n)) return -1;
	return m_table[n].targetVarNumber;
}

void CShopItemData::SetAppearVarNumber(int n,int d)
{
	if (!CheckN(n)) return;
	m_table[n].appearVarNumber = d;
}

void CShopItemData::SetTargetVarNumber(int n,int d)
{
	if (!CheckN(n)) return;
	m_table[n].targetVarNumber = d;
}



BOOL CShopItemData::CheckN(int n)
{
	if ((n<0) || (n>=m_listKosuu)) return FALSE;
	return TRUE;
}

int CShopItemData::GetTypeShopNumber(int type)
{
	if ((type < 0) || (type >= m_typeMax)) return 0;
	return m_typeKosuu[type];
}


int CShopItemData::GetListKosuu(void)
{
	return m_listKosuu;
}
/*_*/

