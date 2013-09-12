#if !defined __NNNUTILLIB_SCENEDATACONTROL__
#define __NNNUTILLIB_SCENEDATACONTROL__

class CSceneList;
class CCommonSystemFile;

class CSceneDataControl
{
public:
	CSceneDataControl(CCommonSystemFile* systemFile,CSceneList* sceneList);
	~CSceneDataControl();
	void End(void);

	BOOL CheckGetScene(int n, int k);
	int GetTotalScenePercent(void);
	int GetScenePercent(int sceneCharaNumber);

	int GetSceneKosuu(int n);
	int GetHSceneKosuu(int n);
	BOOL CheckHScene(int sceneCharaNumber,int sceneNumber);

	void SetSceneNumber(int sceneNumber) {m_sceneNumber = sceneNumber;}
	
	
	
	//
	int GetNextSceneFilm(void);

	int GetSceneCharaNumber(void){return m_sceneCharaNumber;}
	int GetSceneNumber(void){return m_sceneNumber;}
	int GetSceneFilmNumber(void){return m_sceneFilmNumber;}
	int GetSceneCharaKosuu(void){return m_sceneCharaKosuu;}

	void SetSceneCharaNumber(int n){m_sceneCharaNumber = n;}
	void SetSceneFilmNumber(int sceneFilmNumber){m_sceneFilmNumber = sceneFilmNumber;}

	void SetAllOn(void);

private:
	CCommonSystemFile* m_systemFile;
	CSceneList* m_sceneList;

	int m_sceneFilmNumber;
	int m_sceneCharaNumber;
	int m_sceneNumber;
	int m_sceneCharaKosuu;
};

#endif
/*_*/

