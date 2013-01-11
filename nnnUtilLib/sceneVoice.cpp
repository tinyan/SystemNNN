//
// sceneVoice.cpp
//

#include <windows.h>
#include <stdio.h>

#include "..\nyanLib\include\commonMacro.h"

#include "nameList.h"
#include "sceneVoice.h"



CSceneVoice::CSceneVoice()
{
	m_loadOk = FALSE;

	m_sceneVoiceList = new CNameList();
	if (m_sceneVoiceList->LoadFile("nya\\sceneVoice.xtx"))
	{
		m_loadOk = TRUE;
	}

	//
	// [がプレイヤーきりかえ
	// @が行頭
	// サムネイルファイル名 音声ファイル名 メッセージ1 メッセージ2.. #offlayernumber
	//
	//offset[pl][n]

	int scenePlayerKosuu = 0;
	int kosuu = m_sceneVoiceList->GetNameKosuu();
	int sceneKosuu = 0;
	int sceneKosuuPerPlayer = 0;

	int bitPattern[32];
	int bt = 1;
	int i;
	for (i=0;i<31;i++)
	{
		bitPattern[i] = bt;
		bt <<= 1;
	}
	bitPattern[31] = 0x80000000;

	for (i=0;i<kosuu;i++)
	{
		LPSTR name = m_sceneVoiceList->GetName(i);
		char c = *name;
		if (c == '[')
		{
			m_scenePlayerOffsetStart[scenePlayerKosuu] = sceneKosuu;


			if (scenePlayerKosuu>0)
			{
				m_sceneKosuuPerPlayer[scenePlayerKosuu - 1] = sceneKosuuPerPlayer;
			}

			sceneKosuuPerPlayer = 0;
			scenePlayerKosuu++;
		}

		if (c == '#')
		{
			int layer = atoi(name+1);
			m_layerOff[sceneKosuu-1] |= bitPattern[layer];
		}

		if (c == '@')
		{
			m_sceneOffset[sceneKosuu] = i;
			m_layerOff[sceneKosuu] = 0;
			sceneKosuu++;
			sceneKosuuPerPlayer++;
		}
	}

	m_scenePlayerKosuu = scenePlayerKosuu;

	m_scenePlayerOffsetStart[scenePlayerKosuu] = sceneKosuu;
	m_sceneKosuuPerPlayer[scenePlayerKosuu - 1] = sceneKosuuPerPlayer;
	m_sceneOffset[sceneKosuu] = kosuu + 1;

}


CSceneVoice::~CSceneVoice()
{
	End();
}


void CSceneVoice::End(void)
{
	ENDDELETECLASS(m_sceneVoiceList);
}



int CSceneVoice::GetSceneOffsetStart(int player)
{
	return m_scenePlayerOffsetStart[player];
}

int CSceneVoice::GetSceneOffset(int player, int scene)
{
	int n = GetSceneOffsetStart(player);
	return m_sceneOffset[n + scene];
}

int CSceneVoice::GetSceneVoiceParaKosuu(int player, int scene)
{
	int n1 = GetSceneOffset(player,scene);
	int kosuu = GetSceneVoiceKosuu(player);

	if (scene >= kosuu-1)
	{
		int n2 = GetSceneOffset(player+1,0);
		return n2 - 1 - n1;
	}

	int n2 = GetSceneOffset(player,scene+1);
	return n2 - n1;
}


int CSceneVoice::GetSceneVoiceKosuu(int player)
{
	return m_sceneKosuuPerPlayer[player];
}


LPSTR CSceneVoice::GetSceneFileName(int sceneCharaNumber,int sceneNumber)
{
	int n = GetSceneOffset(sceneCharaNumber,sceneNumber);
	LPSTR name = m_sceneVoiceList->GetName(n);
	return name + 1;
}


LPSTR CSceneVoice::GetSceneVoiceFileName(int player, int scene)
{
	int n = GetSceneOffset(player, scene);
	int paraKosuu = GetSceneVoiceParaKosuu(player,scene);
	if (paraKosuu < 2) return NULL;

	LPSTR name = m_sceneVoiceList->GetName(n + 1);
	char c = *name;
	if (c == '!') return NULL;

	return name;
}


LPSTR CSceneVoice::GetSceneVoiceMessage(int player, int scene, int mesNum)
{
	int kosuu = GetSceneVoiceParaKosuu(player, scene);
	if (mesNum >= kosuu - 2) return NULL;

	int n = GetSceneOffset(player, scene);
	LPSTR mes = m_sceneVoiceList->GetName(n + 2 + mesNum);
	if ((*mes) == '#') return NULL;

	return mes;
}

int CSceneVoice::GetLayerOff(int player,int scene)
{
	int n = m_scenePlayerOffsetStart[player] + scene;
//	int n = GetSceneOffset(player,scene);
	return m_layerOff[n];
}


/*_*/

