//
// maskwipe.h
//

#if !defined __NYANEFFECTLIB_MASKWIPE__
#define __NYANEFFECTLIB_MASKWIPE__

//class CEffect;
class CPicture;
class CCommonEffect;
class CAllEffect;
class CEffectMaskWipe : public CCommonEffect
{
public:
	CEffectMaskWipe(CAllEffect* lpAll);
	~CEffectMaskWipe();
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
