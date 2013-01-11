//
// effectGeoCircle.h
//

#if !defined __NYANEFFECTLIBT_GEOCIRCLEADD__
#define __NYANEFFECTLIB_GEOCIRCLEADD__


class CPicture;
class CAllEffect;
class CEffectGeoCircleAdd : public CCommonEffect
{
public:
	CEffectGeoCircleAdd(CAllEffect* lpAll);
	~CEffectGeoCircleAdd();
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

