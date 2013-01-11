//
// effectTarget1.h
//

#if !defined __NYANEFFECTLIB_CHARAMETAL__
#define __NYANEFFECTLIB_CHARAMETAL__


class CPicture;
class CAllEffect;
class CEffectCharaMetal : public CCommonEffect
{
public:
	CEffectCharaMetal(CAllEffect* lpAll);
	~CEffectCharaMetal();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);

	POINT m_polygonDstPoint[6];
	POINT m_polygonSrcPoint[6];
	int m_polygonColor[6];
#if defined _TINYAN3DLIB_
	void PrintBoxSubTate(int startY,int endY,BOOL nonGradFlag = FALSE);
	void PrintBoxSubYoko(int startX,int endX,BOOL nonGradFlag = FALSE);
	void PrintBoxSub(int putX,int putY,int srcX,int srcY,int sizeX,int sizeY,BOOL nonGradFlag = FALSE);

	void PrintSubClip(int startX,int endX,BOOL nonGradFlag = FALSE);
//	void PrintSubTriangle(int x,int xLeft,int xRight);
//	void PrintSubTriangle(int x,int xLeft,int xRight);

	int GetMetalData(int srcX,int srcY);
#endif

	int m_metalStart;
	int m_nowMetal;
	int m_metalHoukou;

	int m_metalSize;

	int m_picSizeX;
	int m_picSizeY;
	int m_putX;
	int m_putY;

private:
};

#endif
/*_*/

