//
//
//

#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanLib\include\commonMacro.h"
#include "nameList.h"

#include "chartList.h"

int CChartList::m_descMax = 3;

CChartList::CChartList(int n,BOOL angouFlag,int blockSize,int* exAngou)
{
	//仕様書を確認のうえ修正


	m_chartNumber = n;
	m_nameList = NULL;
	m_blockSize = blockSize;
	m_exAngou = exAngou;
	m_exAngouKosuu = 0;
	m_exAngouData = NULL;

	if (m_exAngou != NULL)
	{
		m_exAngouKosuu = *m_exAngou;
		m_exAngouData = new int[m_exAngouKosuu];
		for (int i=0;i<m_exAngouKosuu;i++)
		{
			m_exAngouData[i] = *(m_exAngou+i+1);
		}
	}

	m_nameList = new CNameList();

	char filename[256];
	if (angouFlag == FALSE)
	{
		wsprintf(filename,"chart\\chart%d.xtx",n+1);
		m_nameList->LoadFile(filename);
	}
	else
	{
		wsprintf(filename,"chart\\chart%d.fxf",n+1);
		m_nameList->LoadFile(filename,TRUE);
	}


	int kosuu = m_nameList->GetNameKosuu();
	m_slotKosuu = 0;
	int i;

	int nextKosuu = 0;
	int p = 0;
	int nexts = -1;

	m_maxSize = atoi(m_nameList->GetName(0));
	if (m_maxSize < 1800) m_maxSize = 1800;//けすべき

	for (i=1;i<kosuu;i++)
	{
		LPSTR name = m_nameList->GetName(i);
		if ((*name) == '@')
		{
			if (nexts != -1)
			{
				nextKosuu += nexts;
				nexts = -1;
			}

			m_slotKosuu++;
			p = 0;
		}
		else
		{
			p++;
			if (p >= 4)
			{
				int c = ((int)(*name)) & 0xff;
				if (((c<'0') || (c>'9')) && (c != '-'))
				{
					if (nexts != -1)
					{
						nextKosuu += nexts;
						nexts = -1;
					}
				}
				else
				{
					nexts = p - 4 + 1;
				}
			}
		}
	}

	if (nexts != -1)
	{
		nextKosuu += nexts;
		nexts = -1;
	}


	m_zahyo = new POINT[m_slotKosuu+1];
	m_nextTable = new int[m_slotKosuu*2];
	m_next = new int[nextKosuu];
	m_descKosuu = new int[m_slotKosuu*2];
	m_desc = new LPSTR[m_slotKosuu*m_descMax*2];
	m_slotToNTable = new int [m_blockSize+1];
	m_slot = new int[m_slotKosuu];
	m_routeKosuu = new int[m_slotKosuu];
	m_varNumber = new int[m_slotKosuu];
	m_varName = new int[m_slotKosuu];
	m_top = new int[m_slotKosuu];

	for (i=0;i<m_blockSize+1;i++)
	{
		m_slotToNTable[i] = 0;
	}

	int totalNextKosuu = 0;
	p = 0;
	int slotN = -1;
	int descKosuu = 0;
	int descKosuu2 = 0;
	int nowNextKosuu = 0;
	m_maxSlot = m_chartNumber*m_blockSize;

	for (i=1;i<kosuu;i++)
	{
		LPSTR name = m_nameList->GetName(i);
		if ((*name) == '@')
		{
			slotN++;

			int slot = atoi(name+1);
			if (slot > m_maxSlot) m_maxSlot = slot;

			m_slot[slotN] = slot;
			m_slotToNTable[slot - m_chartNumber * m_blockSize] = slotN;
			p=0;
			descKosuu = 0;
			descKosuu2 = 0;
			nowNextKosuu = 0;
			m_nextTable[slotN*2+1] = totalNextKosuu;
			m_nextTable[slotN*2+0] = 0;
			m_descKosuu[slotN*2] = 0;
			m_descKosuu[slotN*2+1] = 0;
			m_varNumber[slotN] = -1;
			m_varName[slotN] = 0;
			m_top[slotN] = 1;
		}
		else
		{
			p++;
			if (p == 1)
			{
				m_routeKosuu[slotN] = atoi(name);
				if (m_routeKosuu[slotN] <= 0)
				{
					m_routeKosuu[slotN] = 1;
				}
			}
			else if (p == 2)
			{
				m_zahyo[slotN].x = atoi(name);
			}
			else if (p == 3)
			{
				m_zahyo[slotN].y = atoi(name);
			}
			else
			{
				int c = ((int)(*name)) & 0xff;
				if (((c>='0') && (c<='9')) || (c=='-'))
				{
					m_next[totalNextKosuu] = atoi(name);

					totalNextKosuu++;
					nowNextKosuu++;
					m_nextTable[slotN*2] = nowNextKosuu;
				}
				else if (c == '$')
				{
					m_varName[slotN] = i;
				}
				else
				{
					if (c != '!')
					{
						m_desc[slotN*m_descMax*2+descKosuu] = name;
						descKosuu++;
						m_descKosuu[slotN*2] = descKosuu;
					}
					else
					{
						m_desc[slotN*m_descMax*2+m_descMax+descKosuu2] = name;
						descKosuu2++;
						m_descKosuu[slotN*2+1] = descKosuu2;
					}
				}
			}
		}
	}

}

CChartList::~CChartList()
{
	End();
}

void CChartList::End(void)
{
	DELETEARRAY(m_top);
	DELETEARRAY(m_varName);
	DELETEARRAY(m_varNumber);
	DELETEARRAY(m_routeKosuu);
	DELETEARRAY(m_slot);
	DELETEARRAY(m_slotToNTable);
	DELETEARRAY(m_desc);
	DELETEARRAY(m_descKosuu);
	DELETEARRAY(m_next);
	DELETEARRAY(m_nextTable);
	DELETEARRAY(m_zahyo);

	ENDDELETECLASS(m_nameList);
	DELETEARRAY(m_exAngouData);
}

POINT CChartList::GetZahyo(int slot)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize))
	{
		POINT pt;
		pt.x = 0;
		pt.y = 0;
		return pt;
	}

	return m_zahyo[n];
}

void CChartList::SetZahyo(int slot,POINT pt)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize)) return;

	m_zahyo[n] = pt;
}

POINT CChartList::GetNextZahyo(int slot,int k)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize))
	{
		POINT pt99;
		pt99.x = 0;
		pt99.y = 0;
		return pt99;
	}

	int slot2 = GetNext(slot,k);
	if ((slot2 >= m_chartNumber*m_blockSize) && (slot2 < (m_chartNumber+1)*m_blockSize))
	{
		return GetZahyo(slot2);
	}

	POINT pt = GetZahyo(slot);
	pt.y = 1600;	//dummy	Out Of range
	return pt;
}

int CChartList::GetNextKosuu(int slot)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize)) return 0;

	return m_nextTable[n*2];
}

int CChartList::GetNext(int slot,int k)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize)) return m_blockSize+1;//dummy eror

	int st = m_nextTable[n*2+1];
	return m_next[st+k];
}

int CChartList::GetDescKosuu(int slot,int md)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize)) return 0;

	return m_descKosuu[n*2+md];
}

LPSTR CChartList::GetDesc(int slot,int k,int md)
{
	int kosuu = GetDescKosuu(slot);
	if ((k<0) || (k >= kosuu)) return NULL;

	int n = GetN(slot);
	LPSTR mes = m_desc[n*m_descMax*2+md*m_descMax+k];
	return mes + md;
}


int CChartList::GetN(int slot)
{
	int k = slot - m_chartNumber * m_blockSize;
	if ((k<0) || (k>m_blockSize)) return m_blockSize+1;	//error

	return m_slotToNTable[k];
}

int CChartList::GetRouteKosuu(int slot)
{
	int n = GetN(slot);
	if ((n < 0) || (n >= m_blockSize)) return 0;	//error

	return m_routeKosuu[n];
}


LPSTR CChartList::GetVarName(int slot)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize)) return NULL;
	int varNumber = m_varName[n];
	if (varNumber <= 0) return NULL;

	char* ptr = m_nameList->GetName(varNumber);
	ptr++;
	return ptr;
}

void CChartList::SetVarNumber(int slot,int varNumber)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize)) return;
	m_varNumber[n] = varNumber;
}

void CChartList::SetNotTop(int slot,BOOL flg)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize)) return;
	m_top[n] = flg;
}

BOOL CChartList::CheckTop(int slot)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize)) return FALSE;
	return m_top[n];
}

int CChartList::GetVarNumber(int slot)
{
	int n = GetN(slot);
	if ((n<0) || (n>m_blockSize)) return -1;
	return m_varNumber[n];
}


int CChartList::GetSlot(int n)
{
	return m_slot[n];
}

int CChartList::GetTotalRouteKosuu(void)
{
	int total = 0;
	int slotKosuu = GetSlotKosuu();
	for (int i=0;i<slotKosuu;i++)
	{
		int d = m_routeKosuu[i];
		if (d == 0) d = 1;	//youjin
		total += d;
	}
	return total;
}

void CChartList::MakeBak(void)
{
	char filename[256];
	char filenameOrg[256];
	wsprintf(filename,"chart\\chart%d.xtx",m_chartNumber+1);
	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);
	int year = systemtime.wYear;
	int month = systemtime.wMonth;
	int date = systemtime.wDay;
	int hour = systemtime.wHour;
	int minute = systemtime.wMinute;
	int second = systemtime.wSecond;
	wsprintf(filenameOrg,"chart\\bak\\chart%d_%d%d%d_%d%d%d.bak",m_chartNumber+1,year,month,date,hour,minute,second);
	CopyFile(filename,filenameOrg,FALSE);
}


void CChartList::Save(void)
{
	int slotKosuu = GetSlotKosuu();

	char filename[256];
//	char filenameOrg[256];
	wsprintf(filename,"chart\\chart%d.xtx",m_chartNumber+1);
//	wsprintf(filenameOrg,"chart\\chart%d.bak",m_chartNumber);
//	CopyFile(filename,filenameOrg,FALSE);

	FILE* file = NULL;
	fopen_s(&file,filename,"wb");
	if (file != NULL)
	{
		char mes[256];
		wsprintf(mes,"%d\x00d\x00a",m_maxSize);
		fwrite(mes,sizeof(char),strlen(mes),file);


		for (int i=0;i<slotKosuu;i++)
		{
			fwrite("@",sizeof(char),1,file);
			int slot = GetSlot(i);
			wsprintf(mes,"%d",slot);
//MessageBox(NULL,mes,"!",MB_OK);
			fwrite(mes,sizeof(char),strlen(mes),file);


			int routeKosuu = GetRouteKosuu(slot);
			wsprintf(mes," %d",routeKosuu);
			fwrite(mes,sizeof(char),strlen(mes),file);

			POINT pt = GetZahyo(slot);
			wsprintf(mes," %d %d",pt.x,pt.y);
			fwrite(mes,sizeof(char),strlen(mes),file);




			int nextKosuu = GetNextKosuu(slot);
			for (int k=0;k<nextKosuu;k++)
			{
				int next = GetNext(slot,k);
				wsprintf(mes," %d",next);
				fwrite(mes,sizeof(char),strlen(mes),file);
			}

			//条件変数
			LPSTR varName = GetVarName(slot);
			if (varName != NULL)
			{
				wsprintf(mes," $%s",varName);
				fwrite(mes,sizeof(char),strlen(mes),file);
			}

			int mesKosuu = GetDescKosuu(slot);
			for (int k2=0;k2<mesKosuu;k2++)
			{
				LPSTR desc = GetDesc(slot,k2);
				wsprintf(mes," %s",desc);
//MessageBox(NULL,mes,"!",MB_OK);
				fwrite(mes,sizeof(char),strlen(mes),file);
			}

			int mesKosuu2 = GetDescKosuu(slot,1);
			for (int k3=0;k3<mesKosuu2;k3++)
			{
				LPSTR desc = GetDesc(slot,k3,1);
//MessageBox(NULL,mes,"!1",MB_OK);
				wsprintf(mes," !%s",desc);
//MessageBox(NULL,mes,"!2",MB_OK);
				fwrite(mes,sizeof(char),strlen(mes),file);
			}

			fwrite("\x00d\x00a",sizeof(char),2,file);
		}

		fclose(file);
	}
}



/*_*/


