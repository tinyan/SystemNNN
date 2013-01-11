//
// sceneList.h
//

#if !defined __NNNUTILLIB_SCENELIST__
#define __NNNUTILLIB_SCENELIST__


class CSceneList
{
public:
	CSceneList();
	~CSceneList();
	void End(void);

	int GetSceneCharaKosuu(void);
	int GetSceneKosuu(int chara);
	int GetHSceneKosuu(int chara);
	int GetScriptNumber(int chara, int scene);
	BOOL CheckHScene(int chara, int scene);
	int GetFilmKosuu(int chara, int scene);
	int GetPlayFilmNumber(int chara, int scene, int n);
	int GetCheckFilmNumber(int chara, int scene, int n);


	BOOL CheckLoadOk(void){return m_loadOk;}
private:
	int* m_data;

	int m_fileSize;
	int m_charaKosuu;

	int* m_offsetTable;
	int* m_charaOffsetNumberTable;
	int* m_sceneKosuu;
	int* m_HSceneKosuu;

	int GetSceneOffset(int chara, int scene);

	BOOL m_loadOk;



};


#endif
/*_*/


