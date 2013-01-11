//
//
//

#if !defined __NNNUTILLIB_SCENEVOICE__
#define __NNNUTILLIB_SCENEVOICE__


class CNameList;


class CSceneVoice
{
public:
	CSceneVoice();
	~CSceneVoice();
	void End(void);

	BOOL CheckLoadOk(void){return m_loadOk;}

	int GetScenePlayerKosuu(void){return m_scenePlayerKosuu;}
	int GetSceneKosuu(int player){return m_sceneKosuuPerPlayer[player];}

	int GetSceneOffsetStart(int player);
	int GetSceneOffset(int player, int scene);
	int GetSceneVoiceParaKosuu(int player, int scene);
	int GetSceneVoiceKosuu(int plyaer);
	int GetLayerOff(int player,int scene);

	LPSTR GetSceneVoiceFileName(int player, int scene);
	LPSTR GetSceneFileName(int sceneCharaNumber, int sceneNumber);
	LPSTR GetSceneVoiceMessage(int player, int scene, int mesNum);

private:
	CNameList* m_sceneVoiceList;
	int m_scenePlayerKosuu;

	BOOL m_loadOk;

	int m_scenePlayerOffsetStart[100];
	int m_sceneKosuuPerPlayer[100];
	int m_sceneOffset[1000];	
	int m_layerOff[1000];
};





#endif

/*_*/

