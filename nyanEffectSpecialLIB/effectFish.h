//
// effectTarget1.h
//

#if !defined __NYANEFFECTLIB_FISH__
#define __NYANEFFECTLIB_FISH__


class CPicture;
class CAllEffect;
class CEffectFish : public CCommonEffect
{
public:
	CEffectFish(CAllEffect* lpAll);
	~CEffectFish();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);

private:
	void InitFish(LPVOID lpEffect,int n,BOOL startFlag = FALSE);

};

#endif
/*_*/

