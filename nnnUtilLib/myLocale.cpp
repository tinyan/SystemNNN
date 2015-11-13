#include <windows.h>
#include <stdio.h>

#include "..\nyanlib\include\commonMacro.h"

#include "myLocale.h"

char CMyLocale::m_localeString[] = "jp";
int CMyLocale::m_locale = 0;

CMyLocale::CMyLocale()
{
}

CMyLocale::~CMyLocale()
{
	End();
}

void CMyLocale::End(void)
{
}


void CMyLocale::SetLocale(LPSTR name)
{
	int locale = 0;
	char check[3] = "jp";
	if (strlen(name) >= 2)
	{
		check[0] = name[0];
		check[1] = name[1];
		check[2] = 0;
	}

	if (_stricmp(name,"jp") == 0) locale = 0;
	if (_stricmp(name,"en") == 0) locale = 1;

	SetLocale(locale);
}

void CMyLocale::SetLocale(int locale)
{
}



/*_*/


