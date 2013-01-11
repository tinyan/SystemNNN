//
// effectgradation.h
//

#if !defined __NYANEFFECTLIB_GRADATION__
#define __NYANEFFECTLIB_GRADATION__


class CPicture;
class CAllEffect;
class CEffectGradation : public CCommonEffect
{
public:
	CEffectGradation(CAllEffect* lpAll);
	~CEffectGradation();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

private:
//	int* m_delta;
};

#endif
/*_*/

