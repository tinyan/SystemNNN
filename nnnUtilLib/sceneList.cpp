//
// sceneList.cpp
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"
#include "..\nyanLib\include\myFile.h"

#include "sceneList.h"


//
// scene.dat 仕様
//
// int fileSize
// int charaKosuu
// SCENEDATA[charaKosuu]
//

//
// SCENEDATA
// 
// int sceneKosuu
// FILMDATA[sceneKosuu]
//
//

//
// FILMDATA
//
// int sptNumber(1-n)	//マイナスはHシーンを意味する
// int filmKosuu
// int filmNumber[filmKosuu]	//マイナスは、チェックに使わない
//




CSceneList::CSceneList()
{
	m_offsetTable = NULL;
	m_charaOffsetNumberTable = NULL;
	m_sceneKosuu = NULL;


//	m_fileSize = 4*6;
//	m_charaKosuu = 1;

	m_loadOk = FALSE;

	FILE* file = CMyFile::Open("spt\\scene.dat","rb");
	if (file != NULL)
	{
		int sz;
		fread(&sz,sizeof(int),1,file);
		if (sz<4) sz = 4000 * sizeof(int);	//for 0
		int k = sz / sizeof(int);
		m_data = new int[k];
		fread(m_data+1,sizeof(int),k-1,file);
		m_data[0] = sz;
		fclose(file);

		m_loadOk = TRUE;
	}
	else
	{
		m_data = new int[6];
		m_data[0] = 0;	//filesize
		m_data[1] = 1;	//charaKosuu
		m_data[2] = 1;	//char1-sceneKosuu
		m_data[3] = 2;	//chara1-scene1-sptNum
		m_data[4] = 1;	//chara1-scene1-filmKosuu
		m_data[5] = 1;	//chara1-scene1-film1

		MessageBox(NULL,"spt\\scene.datがみつからにゃいよ","ERROR",MB_OK);
	}

	m_fileSize = m_data[0];
	m_charaKosuu = m_data[1];

	m_charaOffsetNumberTable = new int[m_charaKosuu];
	m_sceneKosuu = new int[m_charaKosuu];
	m_HSceneKosuu = new int[m_charaKosuu];

	//calcu need offset table
	int pc = 2;
	int tableKosuu = 0;
	
	int i,k;

	for (i=0;i<m_charaKosuu;i++)
	{
		m_charaOffsetNumberTable[i] = tableKosuu;
		int sceneKosuu = m_data[pc];
		m_sceneKosuu[i] = sceneKosuu;

		pc++;

		for (k=0;k<sceneKosuu;k++)
		{
			pc += m_data[pc+1];
			pc += 2;
			tableKosuu++;
		}
	}


	m_offsetTable = new int[tableKosuu];


	pc = 2;
	int tableNumber = 0;
	for (i=0;i<m_charaKosuu;i++)
	{
		int sceneKosuu = m_data[pc];
		pc++;

		for (k=0;k<sceneKosuu;k++)
		{
			m_offsetTable[tableNumber] = pc;
			pc += m_data[pc+1];
			pc += 2;
			tableNumber++;
		}
	}

	for (i=0;i<m_charaKosuu;i++)
	{
		int hKosuu = 0;
		int sceneKosuu = m_sceneKosuu[i];
		for (k=0;k<sceneKosuu;k++)
		{
			if (CheckHScene(i,k)) hKosuu++;
		}
		m_HSceneKosuu[i] = hKosuu;
	}
}


CSceneList::~CSceneList()
{
	End();
}


void CSceneList::End(void)
{
	DELETEARRAY(m_data);
	DELETEARRAY(m_offsetTable);
	DELETEARRAY(m_charaOffsetNumberTable);
	DELETEARRAY(m_sceneKosuu);
	DELETEARRAY(m_HSceneKosuu);

}




int CSceneList::GetSceneCharaKosuu(void)
{
	return m_charaKosuu;
}


int CSceneList::GetSceneKosuu(int chara)
{
	if (chara>=m_charaKosuu) return 0;

	return m_sceneKosuu[chara];
}

int CSceneList::GetHSceneKosuu(int chara)
{
	if (chara>=m_charaKosuu) return 0;

	return m_HSceneKosuu[chara];
}

int CSceneList::GetScriptNumber(int chara, int scene)
{
	if (chara>=m_charaKosuu) return 0;

	int pc = GetSceneOffset(chara,scene);
	
	int d = m_data[pc];
	if (d<0) d *= -1;

	return d;
}

BOOL CSceneList::CheckHScene(int chara, int scene)
{
	if (chara>=m_charaKosuu) return 0;

	int pc = GetSceneOffset(chara,scene);
	
	int d = m_data[pc];

	if (d<0) return TRUE;

	return FALSE;
}


int CSceneList::GetFilmKosuu(int chara, int scene)
{
	if (chara>=m_charaKosuu) return 0;

	int pc = GetSceneOffset(chara,scene);

	return m_data[pc+1];
}


int CSceneList::GetPlayFilmNumber(int chara, int scene, int n)
{
	if (chara>=m_charaKosuu) return 0;

	int pc = GetSceneOffset(chara,scene);
	int d = m_data[pc+2+n];

	if (d<0) d *= -1;

	return d-1;
}

int CSceneList::GetCheckFilmNumber(int chara, int scene, int n)
{
	if (chara>=m_charaKosuu) return 0;

	int pc = GetSceneOffset(chara,scene);
	int d = m_data[pc+2+n];

	if (d<0) return -1;

	return d-1;
}


int CSceneList::GetSceneOffset(int chara, int scene)
{
	int n = m_charaOffsetNumberTable[chara];
	int pc = m_offsetTable[n+scene];

	return pc;
}


/*_*/

