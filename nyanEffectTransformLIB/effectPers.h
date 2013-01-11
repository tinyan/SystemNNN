//
// effectStrytchBlt.h
//

#if !defined __NYANEFFECTLIB_PERS__
#define __NYANEFFECTLIB_PERS__


class CPicture;
class CAllEffect;
class CEffectPers : public CCommonEffect
{
public:
	CEffectPers(CAllEffect* lpAll);
	~CEffectPers();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);

private:
};

#endif
/*_*/

