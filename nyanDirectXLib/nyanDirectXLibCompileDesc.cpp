//
//
//

#include <windows.h>

#include "NyanDirectXLibCompileDesc.h"

char CNyanDirectXLibCompileDesc::m_date[] = __DATE__;
char CNyanDirectXLibCompileDesc::m_time[] = __TIME__;

CNyanDirectXLibCompileDesc::CNyanDirectXLibCompileDesc()
{
}


CNyanDirectXLibCompileDesc::~CNyanDirectXLibCompileDesc()
{
	End();
}

void CNyanDirectXLibCompileDesc::End(void)
{
}


LPSTR CNyanDirectXLibCompileDesc::GetCompileDate(void)
{
	return m_date;
}


LPSTR CNyanDirectXLibCompileDesc::GetCompileTime(void)
{
	return m_time;
}



/*_*/

