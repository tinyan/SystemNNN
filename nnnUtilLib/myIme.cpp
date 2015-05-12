//
//
//

#include <windows.h>

#include "..\nyanLib\include\\commonMacro.h"

#include "nameList.h"
#include "myIme.h"

char m_test[][64]=
{
	"Œó•â‚P",
	"Œó•â‚Q",	
	"Œó•â‚R",
};

CMyIME::CMyIME()
{
}

CMyIME::~CMyIME()
{
	End();
}

void CMyIME::End(void)
{
	
}


LPSTR CMyIME::Start(LPSTR text)
{
	m_dummy = 0;
	m_max = 3;
	return m_test[m_dummy];
}

LPSTR CMyIME::GetNext(void)
{
	m_dummy++;
	m_dummy %= m_max;
	return m_test[m_dummy];
}

