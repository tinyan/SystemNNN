//
// effectfill.h
//

#if !defined __NYANEFFECTLIB_SHAKE__
#define __NYANEFFECTLIB_SHAKE__


class CPicture;
class CAllEffect;
class CEffectShake : public CCommonEffect
{
public:
	CEffectShake(CAllEffect* lpAll);
	~CEffectShake();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
//	void InitParameter(LPVOID lpEffect, int layer = -1);

	static int m_shakeTable[];

private:
};

#endif
/*_*/

