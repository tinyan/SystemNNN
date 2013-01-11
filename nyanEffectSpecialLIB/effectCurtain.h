//
// 
//

#if !defined __NYANEFFECTLIB_CURTAIN__
#define __NYANEFFECTLIB_CURTAIN__


class CPicture;
class CAllEffect;
class CEffectCurtain : public CCommonEffect
{
public:
	CEffectCurtain(CAllEffect* lpAll);
	~CEffectCurtain();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

//	BOOL CheckNeedPicPrint(LPVOID lpEffect);

private:
};

#endif
/*_*/

