//
// effectWaterDrop.h
//

#if !defined __NYANEFFECTLIB_WATERDROP__
#define __NYANEFFECTLIB_WATERDROP__


class CPicture;
class CAllEffect;
class CEffectWaterDrop : public CCommonEffect
{
public:
	CEffectWaterDrop(CAllEffect* lpAll);
	~CEffectWaterDrop();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
	BOOL CheckAllPrint(LPVOID lpEffect,int layer = -1);
private:
};

#endif
/*_*/

