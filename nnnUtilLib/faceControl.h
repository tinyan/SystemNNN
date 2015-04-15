#if !defined ___NNNUTILLIB_FACECONTROL__
#define ___NNNUTILLIB_FACECONTROL__


class CnameList;
class CPicture;

class CAnimeControl;

class CAutoSaveSubData;

class CFaceControl : public CAutoSaveSubData
{
public:
	CFaceControl(CNameList* nameList,int faceMax = 256);
	~CFaceControl();
	void End(void);

	void Clear(void);
	void ChangeFace(int face,int type);
	void MustFace(int mustFace);
	void Print(LPSTR name);

	static char m_defaultTag[];

	void GetExtDataForSave(LPVOID ptr,int extNumber = 0);
	void SetExtDataByLoad(LPVOID ptr,int extNumber = 0);

private:

	int m_faceMax;
	int m_face[2];
	int m_facePicNumber;//dummy
	int m_facePicSubNumber;
	int m_facePrintNumber;

	BOOL LoadPic(int face,int faceSubNumber);
	BOOL LoadPlayer2Pic(int face,int faceSubNumber);
	CNameList* m_nameList;

	int* m_faceType;
	CPicture* m_pic;
	CPicture* m_player2Pic;


	int m_maxSaveData;

	LPSTR* m_customTagName;
	int m_customTagFlag;

	int m_printX[2];
	int m_printY[2];
	int m_sizeX;
	int m_sizeY;
	LPSTR m_tagName;

	int* m_faceTypeKosuu;
	int** m_faceParam;

	int m_mustFace;
	int m_koteiFace;
	int m_koteiType;
	BOOL m_koteiYoyaku;


	BOOL GetInitGameParam(int* lpVar, LPSTR name,int initData);
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name,LPSTR initString);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);



	CNameList* m_setup;
	CAnimeControl* m_animeControl;
	int m_startCount;
	int m_startCountMax;
//	int m_count;

	int m_animeParamInitFlag;
	int m_lastSetFace;
};




#endif
/*_*/


