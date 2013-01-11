#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanLib\include\commonMacro.h"
#include "nameList.h"

#include "cgVoice.h"

CCGVoice::CCGVoice()
{
	m_list = NULL;
	m_dataExistFlag = FALSE;
	m_table = NULL;
	m_playerTable = NULL;

	FILE* file = NULL;
	fopen_s(&file,"spt\\cgVoice.xtx","rb");
	if (file == NULL)
	{
		return;
	}
	fclose(file);

	m_list = new CNameList();
	m_list->LoadFile("spt\\cgVoice.xtx");

	int kosuu = m_list->GetNameKosuu() / 3;
	if (kosuu == 0) return;
	m_dataExistFlag = TRUE;

	m_table = new int[kosuu*2];
	int mx = 0;

	for (int i=0;i<kosuu;i++)
	{
		int player = atoi(m_list->GetName(i*3+0));
		int cg = atoi(m_list->GetName(i*3+1));
		m_table[i*2+0] = player-1;
		m_table[i*2+1] = cg-1;
		if (player > mx)
		{
			mx = player;
		}
	}

	m_playerTableMax = mx;
	m_playerTable = new int[m_playerTableMax*2];
	for (int i=0;i<m_playerTableMax;i++)
	{
		m_playerTable[i*2] = -1;
		m_playerTable[i*2+1] = -1;
	}

	int oldPlayer = -1;
	int start = 0;

	for (int i=0;i<kosuu;i++)
	{
		int player = m_table[i*2];
		int cg = m_table[i*2+1];
		if (player != oldPlayer)
		{
			start = i;
			oldPlayer = player;
			m_playerTable[player*2] = i;
			m_playerTable[player*2+1] = i-start+1;
		}
		else
		{
			m_playerTable[player*2+1] = i-start+1;
		}
	}
}


CCGVoice::~CCGVoice()
{
	End();
}

void CCGVoice::End(void)
{
	DELETEARRAY(m_playerTable);
	DELETEARRAY(m_table);
	ENDDELETECLASS(m_list);
}


LPSTR CCGVoice::GetVoice(int playerNumber,int cgNumber)
{
	if (m_dataExistFlag == FALSE) return NULL;
	if (m_table == NULL) return NULL;
	if (m_playerTable == NULL) return NULL;

	if (playerNumber >= m_playerTableMax) return NULL;
	int start = m_playerTable[playerNumber*2];
	int ln = m_playerTable[playerNumber*2+1];
	if (ln<=0) return NULL;

//	for (int i=0;i<ln;i++)
	for (int i=ln-1;i>=0;i--)
	{
		//check?
		int pl2 = m_table[(start+i)*2];
		int cg2 = m_table[(start+i)*2+1];
		if (pl2 == playerNumber)
		{
			//‚¨‚È‚¶‚Í‚¸
			if (cgNumber >= cg2)
			{
				return m_list->GetName((start+i)*3+2);
			}
		}
	}

	return NULL;
}