//
//
//


#include <windows.h>

#include "nyanLibCompileDesc.h"

char CNyanLibCompileDesc::m_date[] = __DATE__;
char CNyanLibCompileDesc::m_time[] = __TIME__;

CNyanLibCompileDesc::CNyanLibCompileDesc()
{
}


CNyanLibCompileDesc::~CNyanLibCompileDesc()
{
	End();
}

void CNyanLibCompileDesc::End(void)
{
}


LPSTR CNyanLibCompileDesc::GetCompileDate(void)
{
	return m_date;
}


LPSTR CNyanLibCompileDesc::GetCompileTime(void)
{
	return m_time;
}



/*_*/

