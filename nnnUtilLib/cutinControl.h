#if !defined __NNNUTILLIB_CUTINCONTROL__
#define __NNNUTILLIB_CUTINCONTROL__


class CNameList;

class CCutinControl
{
public:
	CCutinControl(BOOL editorFlag = FALSE);
	~CCutinControl();
	void End(void);


	POINT GetZahyo(int layer);
	POINT GetNextZahyo(int layer);

	unsigned int GetColorRGBAPack(int layer);
	int GetColorR(int layer);
	int GetColorG(int layer);
	int GetColorB(int layer);
	int GetColorA(int layer);

	int GetFukidashiType(int layer);//0:col 1-window -1:nothing
	SIZE GetFukidashiDeltaSize(int layer);
	int GetFontDeltaSize(int layer);

	int OnNewFile(int layer,LPSTR filename);
	void OnClearAllEffect(void);
	void OnClearEffect(int layer);

	int SearchCharaLayer(LPSTR name);


private:

	CNameList* m_cutinChara;
	CNameList* m_nameList;
	int* m_tagLength;
	int* m_cutinCharaNumber;

	POINT* m_zahyo;
	int m_cutinKosuu;
	int m_cutinParamKosuu;

	int* m_windowColorRGBA;
	unsigned int* m_windowColorRGBAPack;
	int* m_windowType;
	SIZE* m_windowDeltaSize;
	POINT* m_nextZahyo;
	int* m_fontDeltaSize;

	int m_layerData[16];

	int SearchCharaName(LPSTR name);

//	int m_L1Chache[16];
//	int m_L2ChacheKosuu[16];
//	int m_L2Chache[16][4];


//	BOOL CheckHitL1Cache(int layer);

	//iranai
//	POINT m_layerZahyo[16];
//	unsigned int m_layerColorRGBAPack[16];
//	int m_layerColorRGBA[16*4];

//	CNameList* m_cutinFile;

	//ç≈å„ÇÃ1Ç¬ÇÃÇ›cacheÇµÇƒÇ®Ç≠

};

#endif
/*_*/

