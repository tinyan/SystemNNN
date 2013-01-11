//
// effectBura.h
//

#if !defined __NYANEFFECTLIB_BURA__
#define __NYANEFFECTLIB_BURA__


class CPicture;
class CAllEffect;
class CEffectBura : public CCommonEffect
{
public:
	CEffectBura(CAllEffect* lpAll);
	~CEffectBura();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
private:

	void PrintBuraSub(LPVOID lpEffect,int startX, int startY,double dSrcX,double dSrcY, int sizeX,int sizeY,int ps);

	int m_cx;
	int m_cy;

};

#endif
/*_*/

