//
// effectnop.h
//

#if !defined __NYANEFFECTLIB_NOP__
#define __NYANEFFECTLIB_NOP__


class CPicture;
class CAllEffect;
class CEffectNop : public CCommonEffect
{
public:
	CEffectNop(CAllEffect* lpAll);
	~CEffectNop();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	BOOL CheckAllPrint(LPVOID lpEffect,int layer = -1);

private:
};

#endif
/*_*/

