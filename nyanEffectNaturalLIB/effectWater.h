//
// effectwater.h
//

#if !defined __NYANEFFECTLIB_WATER__
#define __NYANEFFECTLIB_WATER__


class CPicture;
class CAllEffect;
class CEffectWater : public CCommonEffect
{
public:
	CEffectWater(CAllEffect* lpAll);
	~CEffectWater();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

private:
	void CalcuEffectWater(LPVOID lpEffect);
	int* m_effectWaterY;

	int m_effectWaterCount;


};

#endif
/*_*/

