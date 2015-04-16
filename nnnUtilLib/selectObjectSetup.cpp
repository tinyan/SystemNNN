#include <windows.h>
#include <stdio.h>

#include "..\nyanlib\include\commonMacro.h"
#include "nameList.h"

#include "selectObjectSetup.h"

CSelectObjectSetup::CSelectObjectSetup(int n)
{
	m_nameList = new CNameList();
	char filename[256];
	sprintf_s(filename,256,"selectobjecttype%d",n);
	m_nameList->LoadInit(filename);

	m_objectNumber = 0;
	m_addObjectNumber = 0;
	GetInitGameParam(&m_objectNumber,"objectNumber");
	GetInitGameParam(&m_addObjectNumber,"addObjectNumber");

	m_filenameBG = NULL;
	GetInitGameString(&m_filenameBG,"filenameBG");


	m_addPrintX = 0;
	m_addPrintY = 0;
	GetInitGameParam(&m_addPrintX,"addPrintX");
	GetInitGameParam(&m_addPrintY,"addPrintY");

	m_addPrint = new POINT[m_objectNumber+1];
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	for (int i=0;i<m_objectNumber;i++)
	{
		m_addPrint[i] = pt;
	}

	m_placeExistVarNumber = new int[m_objectNumber+1];
	m_placeSelectOkVarNumber = new int[m_objectNumber+1];
	for (int i=0;i<m_objectNumber;i++)
	{
		m_placeExistVarNumber[i] = -1;
		m_placeSelectOkVarNumber[i] = -1;
	}

	m_addVarNumber = new int[m_addObjectNumber+1];
	for (int i=0;i<m_addObjectNumber;i++)
	{
		m_addVarNumber[i] = -1;
	}

	m_addOnlyFlag = 0;
	GetInitGameParam(&m_addOnlyFlag,"addOnlyFlag");
}

CSelectObjectSetup::~CSelectObjectSetup()
{
	End();
}

void CSelectObjectSetup::End(void)
{
	DELETEARRAY(m_addVarNumber);
	DELETEARRAY(m_placeSelectOkVarNumber);
	DELETEARRAY(m_placeExistVarNumber);
	DELETEARRAY(m_addPrint);
	ENDDELETECLASS(m_nameList);
}

BOOL CSelectObjectSetup::GetInitGameParam(int* lpVar, LPSTR name,int initData)
{
	*lpVar = initData;
	return GetInitGameParam(lpVar,name);
}

BOOL CSelectObjectSetup::GetInitGameParam(int* lpVar, LPSTR name)
{
	int rNum = m_nameList->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpVar = atoi(m_nameList->GetName(rNum + 1));

	return TRUE;
}

BOOL CSelectObjectSetup::GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString)
{
	*lpStr = initString;
	return GetInitGameString(lpStr,name);
}

BOOL CSelectObjectSetup::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	int rNum = m_nameList->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_nameList->GetName(rNum + 1);

	return TRUE;
}

POINT CSelectObjectSetup::GetAddPrint(int n)
{
	POINT pt;
	pt.x = 0;
	pt.y = 0;
	if ((n>=0) && (n<m_objectNumber))
	{
		pt = m_addPrint[n];
	}

	pt.x += m_addPrintX;
	pt.y += m_addPrintY;

	return pt;
}


/*_*/


