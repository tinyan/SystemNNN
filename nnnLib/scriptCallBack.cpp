//
// scriptCallBack.cpp
//

#include <windows.h>


#include "..\nyanLib\include\commonMacro.h"
#include "scriptCallBack.h"


CScriptCallBack::CScriptCallBack()
{
}

CScriptCallBack::~CScriptCallBack()
{
	End();
}

void CScriptCallBack::End(void)
{
}

/*
void CScriptCallBack::ReceiveScriptCommand(int cmd, int para1, LPVOID para2)
{
	OutputDebugString("");
}

void CScriptCallBack::ReceiveUserCommand(int cmd, int paraKosuu, int* paraPtr)
{
	OutputDebugString("");
}

void CScriptCallBack::ReceiveUserFunction(int cmd, int paraKosuu, int* paraPtr)
{
	OutputDebugString("");
}

int CScriptCallBack::GetVarData(int varNum)
{
	OutputDebugString("");
	return 0;
}

int CScriptCallBack::GetCalcuVarData(int varNum)
{
	OutputDebugString("");
	return 0;
}

void CScriptCallBack::SetVarData(int varNum, int dat)
{
	OutputDebugString("");
}
*/


