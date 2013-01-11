//
// effectTarget1.h
//

#if !defined __NYANEFFECTLIB_OLDLAMP__
#define __NYANEFFECTLIB_OLDLAMP__


class CPicture;
class CAllEffect;
class CEffectOldLamp : public CCommonEffect
{
public:
	CEffectOldLamp(CAllEffect* lpAll);
	~CEffectOldLamp();
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

