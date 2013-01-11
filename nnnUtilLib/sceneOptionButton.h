//
// SceneOptionButton.h
//

#if !defined __NNNUTILLIB_SCENEOPTIONBUTTON__
#define __NNNUTILLIB_SCENEOPTIONBUTTON__


class CPicture;
//#include "floatingLayer.h"
class CFloatingLayer;

class CCommonButton;

class CSceneOptionButton : public CFloatingLayer
{
public:
	CSceneOptionButton(LPSTR initName, CTaihi* lpTaihi, int taihiLayer = 0);
	virtual ~CSceneOptionButton();
	virtual void End(void);

	virtual void Init(void);
	virtual int Calcu(CInputStatus* lpInput);
	virtual void Print(BOOL taihiFlag = TRUE);

//	virtual void CalcuAnime(int count = 1);	//nothing to do
//	virtual void Print(int type = 0, BOOL taihiFlag = TRUE);

	static char m_defaultButtonFileName[];

//	BOOL CheckOn(int mouseX, int mouseY);
//	void MoveZahyo(int deltaX, int deltaY);

	void SetExist(BOOL flg = TRUE);
	void SetEnable(BOOL flg = TRUE);
	void SetReturnCannotClick(BOOL flg = TRUE);

protected:
	int m_kazariKosuu;

	POINT* m_zahyo;
	SIZE* m_size;

//	int* m_pPrintX;
//	int* m_pPrintY;
//	int* m_pSizeX;
//	int* m_pSizeY;

	int m_printX;
	int m_printY;

//	int m_animeCount;
//	int m_animeCountMax;
//	int m_animeSpeed;
//	int m_animePatternKosuu;

	CPicture** m_ppPic;
//	int* m_pPercent;

protected:
	CCommonButton* m_button;
private:
	
};



#endif
/*_*/
