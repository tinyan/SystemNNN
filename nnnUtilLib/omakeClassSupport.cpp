#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"

#include "omakeClassSupport.h"


COmakeClassSupport::COmakeClassSupport(int omakeClassExistFlag)
{
	m_omakeClassExistFlag = omakeClassExistFlag;
	AllClearOmakeClass();
}

COmakeClassSupport::~COmakeClassSupport()
{
	End();
}

void COmakeClassSupport::End(void)
{
}



void COmakeClassSupport::AllClearOmakeClass(void)
{
	for (int i=0;i<MODE_MAX_OMAKE;i++)
	{
		ClearOmakeClass(i);
	}
}

void COmakeClassSupport::ClearOmakeClass(int parentModeNumber)
{
	for (int i=0;i<OMAKEMODE_KOSUU_OMAKE;i++)
	{
		m_omakeClass[parentModeNumber][i] = 0;
	}
}

void COmakeClassSupport::SetOmakeClassDataByLoad(LPVOID ptr)
{
	int* src = (int*)ptr;
	for (int j=0;j<MODE_MAX_OMAKE;j++)
	{
		for (int i=0;i<OMAKEMODE_KOSUU_OMAKE;i++)
		{
			m_omakeClass[j][i] = *src;
			src++;
		}
	}
}

void COmakeClassSupport::GetOmakeClassDataForSave(LPVOID ptr)
{
	int* dst = (int*)ptr;
	for (int j=0;j<MODE_MAX_OMAKE;j++)
	{
		for (int i=0;i<OMAKEMODE_KOSUU_OMAKE;i++)
		{
			*dst = m_omakeClass[j][i];
			dst++;
		}
	}
}


BOOL COmakeClassSupport::AddOmakeClass(int parentModeNumber, int omakeModeNumber,int mode,int place)
{
	int place0 = SearchOmakeMode(parentModeNumber,omakeModeNumber);
	if (place0 != -1) return FALSE;

	if (place == -1)
	{
		for (int i=0;i<OMAKEMODE_KOSUU_OMAKE;i++)
		{
			if (m_omakeClass[parentModeNumber][i] == 0)
			{
				place = i;
				break;
			}
		}
	}

	if (place == -1) return FALSE;

	//insert ok?
	if (m_omakeClass[parentModeNumber][OMAKEMODE_KOSUU_OMAKE-1] != 0) return FALSE;

	for (int i=OMAKEMODE_KOSUU_OMAKE-1;i>place;i--)
	{
		m_omakeClass[parentModeNumber][i] = m_omakeClass[parentModeNumber][i-1];
	}

	m_omakeClass[parentModeNumber][place] = (omakeModeNumber * 256) | mode;

	return TRUE;
}

BOOL COmakeClassSupport::DeleteOmakeClass(int parentModeNumber, int omakeModeNumber)
{
	int place = SearchOmakeMode(parentModeNumber,omakeModeNumber);
	if (place == -1) return FALSE;

	for (int i=place;i<OMAKEMODE_KOSUU_OMAKE-1;i++)
	{
		m_omakeClass[parentModeNumber][i] = m_omakeClass[parentModeNumber][i+1];
	}
	m_omakeClass[parentModeNumber][OMAKEMODE_KOSUU_OMAKE-1] = 0;

	return TRUE;
}


int COmakeClassSupport::GetOmakeMode(int parentModeNumber, int omakeModeNumber, int type)
{
	int place = SearchOmakeMode(parentModeNumber,omakeModeNumber);
	if (place == -1) return -1;

	int dat = m_omakeClass[parentModeNumber][place] & 0xff;

	if (type == -1) return dat;

	if (type == 0) return dat & 1;
	return (dat >> type) & 1;
}


void COmakeClassSupport::SetOmakeMode(int parentModeNumber, int mode, int omakeModeNumber, int type)
{
	for (int i=0;i<OMAKEMODE_KOSUU_OMAKE;i++)
	{
		int omake = m_omakeClass[parentModeNumber][i] / 256;
		if (omake != 0)
		{
			if ((omake == omakeModeNumber) || (omakeModeNumber == -1))
			{
				if (type == -1)
				{
					m_omakeClass[parentModeNumber][i] = (omake * 256) | mode;
				}
				else
				{
					int bitdat = 1;
					if (type>0) bitdat <<= type;
					int mask = ~bitdat;

					int dat = m_omakeClass[parentModeNumber][i] & 0xff;
					dat &= mask;
					if (mode) dat |= bitdat;

					m_omakeClass[parentModeNumber][i] = (omake * 256) | dat;
				}
			}
		}
	}
}


int COmakeClassSupport::SearchOmakeMode(int parentModeNumber, int omakeModeNumber)
{
	for (int i=0;i<OMAKEMODE_KOSUU_OMAKE;i++)
	{
		int omake = m_omakeClass[parentModeNumber][i] / 256;
		if (omake == omakeModeNumber)
		{
			return i;
		}
	}
	return -1;
}


/*_*/


