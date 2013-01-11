//
// effectHahen.h
//

#if !defined __NYANEFFECTLIB_HAHEN__
#define __NYANEFFECTLIB_HAHEN__


class CPicture;
class CAllEffect;
class CEffectHahen : public CCommonEffect
{
public:
	CEffectHahen(CAllEffect* lpAll);
	~CEffectHahen();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

	static int m_vertex0[];
//	static int m_vertex[];
	static int m_surface[][1+15];	//max 15ŠpŒ`

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);

	typedef struct _tagHAHEN
	{
		float x,y;
		float speedX,speedY;
		float kasokuX,kasokuY;

	}HAHEN;

private:
//	int m_poliKosuu;
//	int m_centerXY[32*2];
	int m_hahenWorkKosuu;
	//HAHEN m_hahen[32];
	HAHEN* m_hahen;


	void ExpandBunkatsuWork(int add = 10);
	int m_createdBunkatsuKosuu;
	int m_bunkatsuWorkKosuu;
	int m_nowBunkatsu;
	int* m_bunkatsuTypeTable;//x16 4‚Â‚Ä‚¢‚Ç‚Â‚©‚¤‚Ì‚©
	int** m_vertexTable;
	int** m_surfaceTable;


	void SetTypeTable(int type,int paraKosuu = 0,int* lpParam = NULL);

	void CreateBuffer(int vertexKosuu,int surfaceKosuu);
	int* GetVertexBuffer(int n);
	int* GetSurfaceBuffer(int n);

	int SearchOrCreateBunkatsu(int type,int* param);
	void CreateNewBunkatsu(int type,int* param);

	int SearchBunkatsu(int type,int* lpParam);

	void PrintNormalPoligon(int* lpPicSrc, int picSizeX, int n, int putX, int putY, int sizeY, int* lpZahyo,int ps256=256);
//	void PrintTransPoligon(int* lpPicSrc, int picSizeX, int n, int putX, int putY, int sizeY, int* lpZahyo,int trans256);
};

#endif
/*_*/

