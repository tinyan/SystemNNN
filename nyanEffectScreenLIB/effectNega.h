//
// effectnega.h
//

#if !defined __NYANEFFECTLIB_NEGA__
#define __NYANEFFECTLIB_NEGA__


class CPicture;
class CAllEffect;
class CEffectNega : public CCommonEffect
{
public:
	CEffectNega(CAllEffect* lpAll);
	~CEffectNega();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

private:
};

#endif
/*_*/

