//
// effectGeoCircle.h
//

#if !defined __NYANEFFECTLIBT_GEOCIRCLE__
#define __NYANEFFECTLIB_GEOCIRCLE__


class CPicture;
class CAllEffect;
class CEffectGeoCircle : public CCommonEffect
{
public:
	CEffectGeoCircle(CAllEffect* lpAll);
	~CEffectGeoCircle();
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

