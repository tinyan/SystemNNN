//
// effectslash.h
//

#if !defined __NYANEFFECTLIB_SLASH__
#define __NYANEFFECTLIB_SLASH__


class CPicture;
class CAllEffect;
class CEffectSlash : public CCommonEffect
{
public:
	CEffectSlash(CAllEffect* lpAll);
	~CEffectSlash();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
//	void InitParameter(LPVOID lpEffect, int layer = -1);

private:
	int* m_work;

};

#endif
/*_*/

