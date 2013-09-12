#include <windows.h>
#include <stdio.h>

#include "commonSystemFile.h"
#include "sceneList.h"
#include "sceneDataControl.h"


CSceneDataControl::CSceneDataControl(CCommonSystemFile* systemFile, CSceneList* sceneList)
{
	m_systemFile = systemFile;
	m_sceneList = sceneList;
	m_sceneCharaNumber = 0;
	m_sceneNumber = 0;

	m_sceneCharaKosuu = m_sceneList->GetSceneCharaKosuu();
}

CSceneDataControl::~CSceneDataControl()
{
}

void CSceneDataControl::End(void)
{
}

BOOL CSceneDataControl::CheckGetScene(int n, int k)
{
	if (m_sceneList == NULL) return FALSE;

	int filmKosuu = m_sceneList->GetFilmKosuu(n,k);
	int sptNum = m_sceneList->GetScriptNumber(n,k);

	BOOL b = TRUE;
	for (int i=0;i<filmKosuu;i++)
	{
		int film = m_sceneList->GetCheckFilmNumber(n,k,i);
		if (film != -1)
		{
			if (m_systemFile->CheckFilm(sptNum,film) == FALSE)
			{
				b = FALSE;
				break;
			}
		}
	}

	return b;
}

int CSceneDataControl::GetTotalScenePercent(void)
{
	int totalKosuu = 0;
	int getKosuu = 0;

	for (int i=0;i<m_sceneCharaKosuu;i++)
	{
		int sceneKosuu = GetSceneKosuu(i);
		totalKosuu += sceneKosuu;

		for (int k=0;k<sceneKosuu;k++)
		{
			if (CheckGetScene(i,k)) getKosuu++;
		}
	}
	if (totalKosuu <= 0) totalKosuu = 1;

	int ps = (getKosuu * 100) / totalKosuu;
	if (ps<0) ps = 0;
	if (ps >=100) ps = 100;

	if (ps == 0)
	{
		if (getKosuu > 0) ps = 1;
	}

	if (ps == 100)
	{
		if (getKosuu < totalKosuu) ps = 99;
	}

	return ps;
}

int CSceneDataControl::GetScenePercent(int sceneCharaNumber)
{
	int totalKosuu = 0;
	int getKosuu = 0;
	int sceneKosuu = GetSceneKosuu(sceneCharaNumber);
	totalKosuu = sceneKosuu;

	for (int k=0;k<sceneKosuu;k++)
	{
		if (CheckGetScene(sceneCharaNumber,k)) getKosuu++;
	}
	if (totalKosuu <= 0) totalKosuu = 1;

	int ps = (getKosuu * 100) / totalKosuu;
	if (ps<0) ps = 0;
	if (ps>=100) ps = 100;

	if (ps == 0)
	{
		if (getKosuu > 0) ps = 1;
	}

	if (ps == 100)
	{
		if (getKosuu < totalKosuu) ps = 99;
	}

	return ps;
}

int CSceneDataControl::GetSceneKosuu(int n)
{
	if (m_sceneList == NULL) return 1;

	return m_sceneList->GetSceneKosuu(n);
}

int CSceneDataControl::GetHSceneKosuu(int n)
{
	if (m_sceneList == NULL) return 0;

	return m_sceneList->GetHSceneKosuu(n);
}

BOOL CSceneDataControl::CheckHScene(int sceneCharaNumber,int sceneNumber)
{
	if (m_sceneList == NULL) return FALSE;

	return m_sceneList->CheckHScene(sceneCharaNumber, sceneNumber);
}


int CSceneDataControl::GetNextSceneFilm(void)
{
	if (m_sceneList == NULL) return -1;

	int filmKosuu = m_sceneList->GetFilmKosuu(m_sceneCharaNumber,m_sceneNumber);

	m_sceneFilmNumber++;

	if (m_sceneFilmNumber<filmKosuu)
	{
		return m_sceneList->GetPlayFilmNumber(m_sceneCharaNumber,m_sceneNumber,m_sceneFilmNumber);
	}

	return -1;
}

void CSceneDataControl::SetAllOn(void)
{
	int totalKosuu = 0;
	int getKosuu = 0;

	for (int n=0;n<m_sceneCharaKosuu;n++)
	{
		int sceneKosuu = GetSceneKosuu(n);

		for (int k=0;k<sceneKosuu;k++)
		{
			int filmKosuu = m_sceneList->GetFilmKosuu(n,k);
			int sptNum = m_sceneList->GetScriptNumber(n,k);

			for (int i=0;i<filmKosuu;i++)
			{
				int film = m_sceneList->GetCheckFilmNumber(n,k,i);
				if (film != -1)
				{
					m_systemFile->SetFilm(sptNum,film);
				}
			}

		}
	}
}

/*_*/

