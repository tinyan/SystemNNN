//
// gameMouse.h
//

#if !defined __NNNUTILLIB_GAMEMOUSE__
#define __NNNUTILLIB_GAMEMOUSE__


class CPicture;
//class CCommonFloatingLayer;
#include "floatingLayer.h"

class CSetupList;
class CAnimeControl;

class CGameMouse : public CFloatingLayer
{
public:
	CGameMouse(CTaihi* lpTaihi, int taihiLayer = 0);
	virtual ~CGameMouse();
	virtual void End(void);

	virtual void CalcuMouseAnime(int count = 1);
	virtual void Print(int x, int y, int type = 0, BOOL taihiFlag = TRUE);

	static char m_defaultMousePicFileName[];

	void SetMouseNumberByConfig(int n){m_mouseNumberConfig = n;}
	void SetMouseNumberByScript(int n){m_mouseNumberScript = n;};

	int GetMouseShuruiConfig(void){return m_mouseShuruiConfig;}
	int GetMouseShuruiScript(void){return m_mouseShuruiScript;}

	void SetSpecialMode(int md){m_specialMode = md;}
//	virtual void Taihi(int x, int y);
//	virtual void Flush(void);
//	virtual void Fuque(void);
	virtual void PrintSpecialMode(int putX,int putY, int type,int pat1,int pat2,int percent);

	void SetZanzouKosuuMax(int mx);
	POINT GetMouseHotPoint(void);

	void SetHadohouType(int type);
protected:
	int m_hotPointX;
	int m_hotPointY;

	int m_mouseSizeX;
	int m_mouseSizeY;

	int m_animeCount;
	int m_animeCountMax;

	CPicture* m_mousePic;

	int m_mousePrintPercent;

	CSetupList* m_setup;
	
	CAnimeControl* m_animeControl;

	int m_animeType;
	int m_animePattern;
	int m_animeSpeed;

	int m_mouseShuruiConfig;
	int m_mouseShuruiScript;

	int m_mouseNumberConfig;
	int m_mouseNumberScript;

	int m_loadedMouseNumberConfig;
	int m_loadedMouseNumberScript;

	BOOL CheckMouseLoaded(void);
	void LoadMyMouse(void);
	LPSTR* m_ppMouseFileName;

	int m_specialMode;
	int m_zanzouNumber;
	int m_zanzouKosuu;
	int m_zanzouKosuuMax;

	POINT m_zanzou[30];

	POINT m_kira[30][10];
	POINT m_kiraSpeed[30][10];

	int m_hadohouType;
	int m_hadohouKosuu;
	int* m_hadohouX;
	int* m_hadohouY;
	int* m_hadohouCount;
	int* m_hadohouSpeed;

	int m_hadohouColorR1;
	int m_hadohouColorG1;
	int m_hadohouColorB1;
	int m_hadohouColorR2;
	int m_hadohouColorG2;
	int m_hadohouColorB2;
	int m_hadohouSizeMin;
	int m_hadohouSizeMax;
	int m_hadohouTime;

	void InitHadohou(void);
	void CalcuMouseHadohou(void);
	void PrintMouseHadohou(int mouseX, int mouseY);
	void SetHadohou(int n);

private:

};



#endif
/*_*/
