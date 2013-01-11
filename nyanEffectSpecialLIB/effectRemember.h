//
// effectremember.h
//

#if !defined __NYANEFFECTLIB_REMEMBER__
#define __NYANEFFECTLIB_REMEMBER__


class CPicture;
class CAllEffect;
class CEffectRemember : public CCommonEffect
{
public:
	CEffectRemember(CAllEffect* lpAll);
	~CEffectRemember();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

private:
	int* m_left;
	int* m_right;

	int m_rememberCount;
};

#endif
/*_*/

