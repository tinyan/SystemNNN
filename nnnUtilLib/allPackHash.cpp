
#include <windows.h>

#include "..\nyanlib\include\commonMacro.h"

#include "allPackHash.h"

CAllPackHash::CAllPackHash()
{
}

CAllPackHash::~CAllPackHash()
{
	End();
}

void CAllPackHash::End(void)
{
}



int CAllPackHash::CreateHash(LPCSTR name)
{
	int ln = (int)strlen(name);
	int hash = 0;
	int mul = 1;
	for (int i=0;i<ln;i++)
	{
		int d = (int)(*(name+i));
		d &= 0xff;
		hash += (d * mul);
		mul++;
	}

	hash += ln;
	hash &= 0x7fffffff;

	return hash;
}
