



#include <windows.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanEffectLib\effectStruct.h"
#include "..\nyanLib\include\effect.h"


#include "nameList.h"

#include "mepachiControl.h"


//
// @Filename me_filename    name1(dmy) mepachikosuu    x y sizeX sizeY type para...
// #Filename kuchi_filename name2      kuchipakukosuu  x y sizeX sizeY type  para[3]
//

char CMepachiControl::m_defaultMeFileName[]="ta_mepachi";
char CMepachiControl::m_defaultMeCharaName[]="no";
char CMepachiControl::m_defaultKuchiFileName[]="ta_kuchipaku";
char CMepachiControl::m_defaultKuchiCharaName[]="no";


CMepachiControl::CMepachiControl(CEffect* lpEffect)
{
	m_effect = lpEffect;
	m_mepachiList = new CNameList();
	
	if (1)
	{
		m_mepachiList->LoadFile("nnndir\\mepachi.txt");
	}
	else
	{
		m_mepachiList->LoadFile("spt\\mepachi.xtx");
	}

	int kosuu = m_mepachiList->GetNameKosuu();

	m_meKosuu = 0;
	m_kuchiKosuu = 0;

	for (int i=0;i<kosuu;i++)
	{
		LPSTR name = m_mepachiList->GetName(i);
		if ((*name) == '@') m_meKosuu++;
		if ((*name) == '#') m_kuchiKosuu++;
	}

	m_meNameTable = NULL;
	m_kuchiNameTable = NULL;
	m_meTable = NULL;
	m_kuchiTable = NULL;

	if (m_meKosuu > 0)
	{
		m_meNameTable = new LPSTR[m_meKosuu];
		m_meTable = new int[m_meKosuu*16];
		m_meCharaNameTable = new LPSTR[m_meKosuu];
	}

	if (m_kuchiKosuu > 0)
	{
		m_kuchiNameTable = new LPSTR [m_kuchiKosuu];
		m_kuchiTable = new int[m_kuchiKosuu*16];
		m_kuchiCharaNameTable = new LPSTR[m_kuchiKosuu];
	}

	m_fileNameTable = NULL;
	m_mekuchiTable = NULL;
	int mekuchi= m_meKosuu + m_kuchiKosuu;
	if (mekuchi>0)
	{
		m_fileNameTable = new LPSTR[mekuchi];
		m_mekuchiTable = new int[mekuchi*2];
		for (int i=0;i<mekuchi*2;i++)
		{
			m_mekuchiTable[i] = -1;
		}
	}


	int n = 0;
	int me = 0;
	int kuchi = 0;

	m_fileNameKosuu = 0;

	while (n<kosuu)
	{
		LPSTR name = m_mepachiList->GetName(n);
		if ((*name) == '@')
		{
			n += InitMeTable(me,n);
			me++;
		}
		else if ((*name) == '#')
		{
			n += InitKuchiTable(kuchi,n);
			kuchi++;
		}
		else
		{
			n++;	//error?
		}
	}
}

CMepachiControl::~CMepachiControl()
{
	End();
}

void CMepachiControl::End(void)
{
	DELETEARRAY(m_mekuchiTable);
	DELETEARRAY(m_fileNameTable);

	DELETEARRAY(m_kuchiCharaNameTable);
	DELETEARRAY(m_kuchiTable);
	DELETEARRAY(m_kuchiNameTable);
	DELETEARRAY(m_meCharaNameTable);
	DELETEARRAY(m_meTable);
	DELETEARRAY(m_meNameTable);
	ENDDELETECLASS(m_mepachiList);
}

int CMepachiControl::InitMeTable(int me,int n)
{
	int kosuuMax = m_mepachiList->GetNameKosuu();

	int kosuu = 0;
	LPSTR name = m_mepachiList->GetName(n);

	m_meNameTable[me] = name+1;
	m_meNameTable[me] = m_defaultMeFileName;
	m_meCharaNameTable[me] = m_defaultMeCharaName;

	CheckAndAddFileName(name+1,me,-1);
	kosuu++;
	n++;

	
	int nameKosuu = 0;
	int paraKosuu = 0;

	for (int i=0;i<16;i++)
	{
		m_meTable[me*16+i] = 0;
	}


	while (n<kosuuMax)
	{
		LPSTR name = m_mepachiList->GetName(n);
		if ((*name) == '@') break;
		if ((*name) == '#') break;

		if (nameKosuu<2)
		{
			if (nameKosuu == 0)
			{
				m_meNameTable[me] = name;
			}
			else
			{
				m_meCharaNameTable[me] = name;
			}
			nameKosuu++;
		}
		else
		{
			if (paraKosuu<16)
			{
				m_meTable[me*16+paraKosuu] = atoi(name);
				paraKosuu++;
			}
		}

		n++;
		kosuu++;
	}

	return kosuu;
}

int CMepachiControl::InitKuchiTable(int kuchi,int n)
{
	int kosuuMax = m_mepachiList->GetNameKosuu();

	int kosuu = 0;
	LPSTR name = m_mepachiList->GetName(n);

	m_kuchiNameTable[kuchi] = name+1;

	m_kuchiNameTable[kuchi] = m_defaultKuchiFileName;
	m_kuchiCharaNameTable[kuchi] = m_defaultKuchiCharaName;

	CheckAndAddFileName(name+1,-1,kuchi);
	kosuu++;
	n++;

	
	int nameKosuu = 0;
	int paraKosuu = 0;

	for (int i=0;i<16;i++)
	{
		m_kuchiTable[kuchi*16+i] = 0;
	}


	while (n<kosuuMax)
	{
		LPSTR name = m_mepachiList->GetName(n);
		if ((*name) == '@') break;
		if ((*name) == '#') break;

		if (nameKosuu<2)
		{
			if (nameKosuu == 0)
			{
				m_kuchiNameTable[kuchi] = name;
			}
			else
			{
				m_kuchiCharaNameTable[kuchi] = name;
			}
			nameKosuu++;
		}
		else
		{
			if (paraKosuu<16)
			{
				m_meTable[kuchi*16+paraKosuu] = atoi(name);
				paraKosuu++;
			}
		}

		n++;
		kosuu++;
	}

	return kosuu;
}

int CMepachiControl::SearchFileName(LPSTR name)
{
	for (int i=0;i<m_fileNameKosuu;i++)
	{
		if (_stricmp(name,m_fileNameTable[i]) == 0) return i;
	}
	return -1;
}


void CMepachiControl::CheckAndAddFileName(LPSTR name,int me,int kuchi)
{
	int k = SearchFileName(name);
	if (k == -1)
	{
		m_fileNameTable[m_fileNameKosuu] = name;
		if (me != -1) m_mekuchiTable[m_fileNameKosuu*2] = me;
		if (kuchi != -1) m_mekuchiTable[m_fileNameKosuu*2+1] = kuchi;
		m_fileNameKosuu++;
	}
}

/*_*/

