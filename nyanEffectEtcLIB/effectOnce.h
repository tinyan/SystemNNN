//
// effectOnce.h
//

#if !defined __NYANEFFECTLIB_ONCE__
#define __NYANEFFECTLIB_ONCE__


class CPicture;
class CAllEffect;

class CEffectOnce : public CCommonEffect
{
public:
	CEffectOnce(CAllEffect* lpAll);
	~CEffectOnce();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);

private:
	BOOL* m_onceFlag;

};

#endif
/*_*/

