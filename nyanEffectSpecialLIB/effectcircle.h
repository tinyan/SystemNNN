//
// effectcircle.h
//

#if !defined __NYANEFFECTLIB_CIRCLE__
#define __NYANEFFECTLIB_CIRCLE__


class CPicture;
class CAllEffect;
class CEffectCircle : public CCommonEffect
{
public:
	CEffectCircle(CAllEffect* lpAll);
	~CEffectCircle();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	int GetLayerOrPicType(void){return 1;}
private:
};

#endif
/*_*/

