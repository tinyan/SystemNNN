//
//
//

#include <windows.h>


#include "NNNLibCompileDesc.h"

char CNNNLibCompileDesc::m_date[] = __DATE__;
char CNNNLibCompileDesc::m_time[] = __TIME__;

CNNNLibCompileDesc::CNNNLibCompileDesc()
{
}


CNNNLibCompileDesc::~CNNNLibCompileDesc()
{
	End();
}

void CNNNLibCompileDesc::End(void)
{
}


LPSTR CNNNLibCompileDesc::GetCompileDate(void)
{
	return m_date;
}


LPSTR CNNNLibCompileDesc::GetCompileTime(void)
{
	return m_time;
}



/*_*/

