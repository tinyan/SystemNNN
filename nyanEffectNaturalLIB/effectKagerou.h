//
// effectkagerou.h
//

#if !defined __NYANEFFECTLIB_KAGEROU__
#define __NYANEFFECTLIB_KAGEROU__


class CPicture;
class CAllEffect;
class CEffectKagerou : public CCommonEffect
{
public:
	CEffectKagerou(CAllEffect* lpAll);
	~CEffectKagerou();
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

