//
// varNumber.cpp
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonmacro.h"

#include "namelist.h"
#include "varNumber.h"


CVarNumber::CVarNumber(CNameList* varList)
{
	m_varList = varList;
	m_kosuu = m_varList->GetNameKosuu();
}

CVarNumber::~CVarNumber()
{
	End();
}

void CVarNumber::End(void)
{
}


int CVarNumber::GetVarNumber(LPSTR name)
{
	for (int i=0;i<m_kosuu;i++)
	{
		LPSTR varName = m_varList->GetName(i);
		if (varName != NULL)
		{
			if ((*varName) != 0)
			{
				if (strcmp(varName,name) == 0)
				{
					return i;
				}
			}
		}
	}

	PrintMyError(name);
	return -1;
}

void CVarNumber::PrintMyError(LPSTR name)
{
#if !defined _DEBUG
	MessageBox(NULL,name,"var not found",MB_OK);
#else
	OutputDebugString("\nvar not found[");
	OutputDebugString(name);
	OutputDebugString("]");
#endif

}
