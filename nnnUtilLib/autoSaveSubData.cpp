#include <windows.h>

#include "autoSaveSubData.h"



CAutoSaveSubData::CAutoSaveSubData(int size)
{
	SetDataSize(size);
}

CAutoSaveSubData::~CAutoSaveSubData()
{
	End();
}

void CAutoSaveSubData::End(void)
{
}


/*_*/

