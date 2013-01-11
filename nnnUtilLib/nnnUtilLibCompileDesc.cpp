//
//
//

#include <windows.h>

#include "NNNUtilLibCompileDesc.h"

char CNNNUtilLibCompileDesc::m_date[] = __DATE__;
char CNNNUtilLibCompileDesc::m_time[] = __TIME__;

CNNNUtilLibCompileDesc::CNNNUtilLibCompileDesc()
{
}


CNNNUtilLibCompileDesc::~CNNNUtilLibCompileDesc()
{
	End();
}

void CNNNUtilLibCompileDesc::End(void)
{
}


LPSTR CNNNUtilLibCompileDesc::GetCompileDate(void)
{
	return m_date;
}


LPSTR CNNNUtilLibCompileDesc::GetCompileTime(void)
{
	return m_time;
}



/*_*/

