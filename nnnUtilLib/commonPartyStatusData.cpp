#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\areaControl.h"
#include "..\nyanLib\include\picture.h"

#include "..\nyanLib\include\allGeo.h"

#include "..\nyanLib\include\myFile.h"

#include "nameList.h"
#include "systempicture.h"
#include "suuji.h"
#include "systempicture.h"
#include "autoSaveSubData.h"
#include "okikaeData.h"
#include "mymessage.h"

#include "CommonPartyStatusData.h"

char CCommonPartyStatusData::m_suujiName[] = "ta_suuji";

char CCommonPartyStatusData::m_errorName[] = "エラー";
char CCommonPartyStatusData::m_errorVarName[] = "変数名エラー";
char CCommonPartyStatusData::m_errorFilename[] = "ta_error";

CCommonPartyStatusData::CCommonPartyStatusData(CNameList* setup,CMyMessage* message)
{
	m_setupList = setup;
	m_message = message;

	m_partyNumber = 1;
	m_etcNumber = 0;
	m_statusNumber = 1;
	m_printNumberMax = 1;

	char name[256];
	GetInitGameParam(&m_printNumberMax,"printNumber");//表示パーティの数
	GetInitGameParam(&m_statusNumber,"statusNumber");//パーティごとの表示ステータスの数
	m_partyNumber = m_printNumberMax;
	GetInitGameParam(&m_partyNumber,"partyNumber");

	GetInitGameParam(&m_etcNumber,"etcNumber");

	LPSTR plateFilename = NULL;
	m_platePic = NULL;

	if (GetInitGameString(&plateFilename,"filenamePlate"))
	{
		m_platePic = CSystemPicture::GetSystemPicture(plateFilename);
	}

	m_partyAreaSizeX = 400;
	m_partyAreaSizeY = 150;
	GetInitGameParam(&m_partyAreaSizeX,"partyAreaSizeX");
	GetInitGameParam(&m_partyAreaSizeY,"partyAreaSizeY");

	m_partyZahyo = new POINT[m_printNumberMax];
	int printX = 0;
	int printY = 0;
	int nextX = 0;
	int nextY = m_partyAreaSizeY;
	GetInitGameParam(&nextX,"partyAreaNextX");
	GetInitGameParam(&nextY,"partyAreaNextY");

	for (int i=0;i<m_printNumberMax;i++)
	{
		sprintf_s(name,256,"party%dPrintX",i+1);
		GetInitGameParam(&printX,name);
		sprintf_s(name,256,"party%dPrintY",i+1);
		GetInitGameParam(&printY,name);
		m_partyZahyo[i].x = printX;
		m_partyZahyo[i].y = printY;

		printX += nextX;
		printY += nextY;
	}


	m_statusParam = new STATUSPARAM[m_statusNumber+1];

	int fontSize = 24;
	int fontColorR = 255;
	int fontColorG = 255;
	int fontColorB = 255;
	int left = 0;
	int upzero = 0;
	int keta = 3;
	int suujiSizeX = 16;
	int suujiSizeY = 16;
	int suujiNextX = suujiSizeX;
	LPSTR suujiFilename = m_suujiName;
	int type = 3;

	for (int i=0;i<=m_statusNumber;i++)
	{
		m_statusParam[i].suuji = NULL;

		printX = 0;
		printY = 0;
		sprintf_s(name,256,"status%dPrintX",i);
		GetInitGameParam(&printX,name);
		sprintf_s(name,256,"status%dPrintY",i);
		GetInitGameParam(&printY,name);
		m_statusParam[i].zahyo.x = printX;
		m_statusParam[i].zahyo.y = printY;

		if (i == 1) type = 1;

		sprintf_s(name,256,"status%dType",i);
		GetInitGameParam(&type,name);
		m_statusParam[i].type = type;

		if (type == 1)
		{
			sprintf_s(name,256,"status%dLeftFlag",i);
			GetInitGameParam(&left,name);
			sprintf_s(name,256,"status%dUpZero",i);
			GetInitGameParam(&upzero,name);
			sprintf_s(name,256,"status%dketa",i);
			GetInitGameParam(&keta,name);

			sprintf_s(name,256,"status%dSuujiSizeX",i);
			GetInitGameParam(&suujiSizeX,name);
			sprintf_s(name,256,"status%dSuujiSizeY",i);
			GetInitGameParam(&suujiSizeY,name);
			sprintf_s(name,256,"status%dSuujiNextX",i);
			suujiNextX = suujiSizeX;
			GetInitGameParam(&suujiNextX,name);

			sprintf_s(name,256,"status%dsuujiFilename",i);
			GetInitGameString(&suujiFilename,name);

			CPicture* pic = CSystemPicture::GetSystemPicture(suujiFilename);
	
			m_statusParam[i].suuji = new CSuuji(pic,suujiSizeX,suujiSizeY,keta,suujiNextX,upzero,TRUE,left);
		}
		else if ((type == 2) || (type == 3))
		{
			sprintf_s(name,256,"status%dfontColorR",i);
			GetInitGameParam(&fontColorR,name);
			sprintf_s(name,256,"status%dfontColorG",i);
			GetInitGameParam(&fontColorG,name);
			sprintf_s(name,256,"status%dfontColorB",i);
			GetInitGameParam(&fontColorB,name);
			sprintf_s(name,256,"status%dfontSize",i);
			GetInitGameParam(&fontSize,name);

			m_statusParam[i].fontSize = fontSize;
			m_statusParam[i].colorR = fontColorR;
			m_statusParam[i].colorG = fontColorG;
			m_statusParam[i].colorB = fontColorB;
		}
	}

	m_partyParam = new PARTYPARAM[m_partyNumber];
	for (int i=0;i<m_partyNumber;i++)
	{
		m_partyParam[i].pic = NULL;

		LPSTR faceFilename = NULL;
		sprintf_s(name,256,"party%dFilename",i+1);
		if (GetInitGameString(&faceFilename,name))
		{
			m_partyParam[i].pic = CSystemPicture::GetSystemPicture(faceFilename);
		}



		m_partyParam[i].data = new int[m_statusNumber+1];
		m_partyParam[i].statusVar = new int[m_statusNumber+1];
		for (int k=0;k<=m_statusNumber;k++)
		{

			int varNumber = -1;
			int textNumber = -1;
			int type = m_statusParam[k].type;
		//	m_partyParam[i].data = 0;
			if ((type == 2) || (type == 3))
			{
				sprintf_s(name,256,"party%d_%dtextNumber",i+1,k);
				GetInitGameParam(&textNumber,name);
			}


			m_partyParam[i].data[k] = textNumber;
			m_partyParam[i].statusVar[k] = varNumber;
		}




	}


	m_printNumberTable = new int[m_printNumberMax];
	m_printNumberVarData = new int[m_printNumberMax];
	m_printByVar = 0;
	GetInitGameParam(&m_printByVar,"printByVar");

	for (int i=0;i<m_printNumberMax;i++)
	{
		m_printNumberVarData[i] = -1;
		m_printNumberTable[i] = i+1;
	}


	m_etcParam = new ETCPARAM[m_etcNumber+1];
	for (int i=0;i<m_etcNumber;i++)
	{
		sprintf_s(name,256,"etc%dPrintX",i+1);
		GetInitGameParam(&printX,name);
		sprintf_s(name,256,"etc%dPrintY",i+1);
		GetInitGameParam(&printY,name);
		m_etcParam[i].zahyo.x = printX;
		m_etcParam[i].zahyo.y = printY;

		sprintf_s(name,256,"etc%dLeftFlag",i+1);
		GetInitGameParam(&left,name);
		sprintf_s(name,256,"etc%dUpZero",i+1);
		GetInitGameParam(&upzero,name);
		sprintf_s(name,256,"etc%dketa",i+1);
		GetInitGameParam(&keta,name);

		sprintf_s(name,256,"etc%dSuujiSizeX",i+1);
		GetInitGameParam(&suujiSizeX,name);
		sprintf_s(name,256,"etc%dSuujiSizeY",i+1);
		GetInitGameParam(&suujiSizeY,name);
		sprintf_s(name,256,"etc%dSuujiNextX",i+1);
		suujiNextX = suujiSizeX;
		GetInitGameParam(&suujiNextX,name);

		sprintf_s(name,256,"etc%dsuujiFilename",i+1);
		GetInitGameString(&suujiFilename,name);

		CPicture* pic = CSystemPicture::GetSystemPicture(suujiFilename);
	
		m_etcParam[i].suuji = new CSuuji(pic,suujiSizeX,suujiSizeY,keta,suujiNextX,upzero,TRUE,left);

		m_etcParam[i].varNumber = -1;
	}











}

CCommonPartyStatusData::~CCommonPartyStatusData()
{
	End();
}

void CCommonPartyStatusData::End(void)
{
	if (m_etcParam != NULL)
	{
		for (int i=0;i<m_etcNumber;i++)
		{
			ENDDELETECLASS(m_etcParam[i].suuji);
		}
		DELETEARRAY(m_etcParam);
	}

	DELETEARRAY(m_printNumberTable);
	DELETEARRAY(m_printNumberVarData);

	if (m_partyParam != NULL)
	{
		for (int i=0;i<m_partyNumber;i++)
		{
			DELETEARRAY(m_partyParam[i].data);
			DELETEARRAY(m_partyParam[i].statusVar);
		}

		DELETEARRAY(m_partyParam);
	}

	if (m_statusParam != NULL)
	{
		for (int i=0;i<m_statusNumber;i++)
		{
			ENDDELETECLASS(m_statusParam[i].suuji);
		}
		DELETEARRAY(m_statusParam);
	}

	DELETEARRAY(m_partyZahyo);


}


void CCommonPartyStatusData::Print(int ps)
{
	m_percent = ps;

	for (int i=0;i<m_printNumberMax;i++)
	{
		POINT baseZahyo = m_partyZahyo[i];
		int party = m_printNumberTable[i];
		if (party > 0)
		{
			party--;


			//print base
			if (m_platePic != NULL)
			{
				m_platePic->Put(baseZahyo.x,baseZahyo.y,TRUE);
			}


			//print pic
			CPicture* pic = m_partyParam[party].pic;
			if (pic != NULL)
			{
				POINT pt = m_statusParam[0].zahyo;
				int x = baseZahyo.x + pt.x;
				int y = baseZahyo.y + pt.y;
				pic->Put(x,y,TRUE);
			}


			for (int k=1;k<=m_statusNumber;k++)
			{
				int type = m_statusParam[k].type;
				if (type == 1)
				{
					CSuuji* suuji = m_statusParam[k].suuji;
					if (suuji != NULL)
					{
						POINT pt = m_statusParam[k].zahyo;
						int x = baseZahyo.x + pt.x;
						int y = baseZahyo.y + pt.y;
						int d = m_partyParam[party].data[k];
						suuji->Print(x,y,d);
					}
				}
				else if ((type == 2) || (type == 3))
				{
					POINT pt = m_statusParam[k].zahyo;
					int x = baseZahyo.x + pt.x;
					int y = baseZahyo.y + pt.y;

					int fontSize = m_statusParam[k].fontSize;
					int colorR = m_statusParam[k].colorR;
					int colorG = m_statusParam[k].colorG;
					int colorB = m_statusParam[k].colorB;

					int d = m_partyParam[party].data[k];

					LPSTR text = NULL;
					if (type == 2)
					{
						text = CMyMessage::m_okikaeData->GetOkikaeMessage(d);
					}
					else if (type == 3)
					{
						text = CMyMessage::m_okikaeData->GetSystemOkikaeMessage(d);
					}

					if (text != NULL)
					{
						m_message->PrintMessage(x,y,text,fontSize,colorR,colorG,colorB);
					}
				}
			}
		}
	}

	//etc
	for (int i=0;i<m_etcNumber;i++)
	{
		POINT pt = m_etcParam[i].zahyo;
		int d = m_etcParam[i].data;
		CSuuji* suuji = m_etcParam[i].suuji;

		int x = pt.x;
		int y = pt.y;

		if (suuji != NULL)
		{
			suuji->Print(x,y,d);
		}
	}
}



int CCommonPartyStatusData::GetType(int n,int k)
{
	if (!CheckNK(n,k)) return 0;
	return m_statusParam[k].type;
}


LPSTR CCommonPartyStatusData::GetVarName(int n,int k)
{
	if (!CheckNK(n,k)) return NULL;

	char name[256];
	sprintf_s(name,256,"party%d_%dVar",n+1,k);
	LPSTR varName = NULL;
	GetInitGameString(&varName,name);
	return varName;
}

int CCommonPartyStatusData::GetVarNumber(int n,int k)
{
	if (!CheckNK(n,k)) return -1;
	return m_partyParam[n].statusVar[k];
}

void CCommonPartyStatusData::SetVarNumber(int n,int k,int d)
{
	if (!CheckNK(n,k)) return;
	m_partyParam[n].statusVar[k] = d;
}

void CCommonPartyStatusData::SetData(int n,int k,int d)
{
	if (!CheckNK(n,k)) return;
	m_partyParam[n].data[k] = d;
}


LPSTR CCommonPartyStatusData::GetEtcVarName(int n)
{
	if (!CheckEtcN(n)) return NULL;

	char name[256];
	sprintf_s(name,256,"etc%dVar",n+1);
	LPSTR varName = m_errorVarName;
	GetInitGameString(&varName,name);
	return varName;
}

int CCommonPartyStatusData::GetEtcVarNumber(int n)
{
	if (!CheckEtcN(n)) return -1;
	return m_etcParam[n].varNumber;
}

void CCommonPartyStatusData::SetEtcVarNumber(int n,int d)
{
	if (!CheckEtcN(n)) return;
	m_etcParam[n].varNumber = d;
}

void CCommonPartyStatusData::SetEtcData(int n,int d)
{
	if (!CheckEtcN(n)) return;
	m_etcParam[n].data = d;
}

LPSTR CCommonPartyStatusData::GetPrintVarName(int n)
{
	if (!CheckEtcNP(n)) return NULL;

	char name[256];
	sprintf_s(name,256,"print%dVar",n+1);
	LPSTR varName = m_errorVarName;
	GetInitGameString(&varName,name);
	return varName;
}

int CCommonPartyStatusData::GetPrintVarNumber(int n)
{
	if (!CheckEtcNP(n)) return -1;
	return m_printNumberVarData[n];
}

void CCommonPartyStatusData::SetPrintVarNumber(int n,int d)
{
	if (!CheckEtcNP(n)) return;
	m_printNumberVarData[n] = d;
}

void CCommonPartyStatusData::SetPrintData(int n,int d)
{
	if (!CheckEtcNP(n)) return;
	m_printNumberTable[n] = d;
}

BOOL CCommonPartyStatusData::CheckNK(int n,int k)
{
	if ((n<0) || (n>=m_partyNumber)) return FALSE;
	if ((n<0) || (n>m_statusNumber)) return FALSE;
	return TRUE;
}

BOOL CCommonPartyStatusData::CheckEtcN(int n)
{
	if ((n<0) || (n>=m_etcNumber)) return FALSE;
	return TRUE;
}


BOOL CCommonPartyStatusData::CheckEtcNP(int n)
{
	if ((n<0) || (n>=m_printNumberMax)) return FALSE;
	return TRUE;
}





BOOL CCommonPartyStatusData::GetInitGameParam(int* lpVar, LPSTR name)
{
	if (m_setupList == NULL) return FALSE;

	int rNum = m_setupList->SearchName2(name);
	if (rNum == -1) return FALSE;
	*lpVar = atoi(m_setupList->GetName(rNum + 1));

	return TRUE;
}


BOOL CCommonPartyStatusData::GetInitGameString(LPSTR* lpStr, LPSTR name)
{
	if (m_setupList == NULL) return FALSE;

	int rNum = m_setupList->SearchName2(name);
	if (rNum == -1) return FALSE;

	*lpStr = m_setupList->GetName(rNum + 1);

	return TRUE;
}

/*_*/

