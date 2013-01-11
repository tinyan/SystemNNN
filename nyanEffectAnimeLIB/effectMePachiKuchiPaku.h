//
// effectMePachiKuchiPaku.h
//

#if !defined __NYANEFFECTLIB_MEPACHIKUCHIPAKU__
#define __NYANEFFECTLIB_MEPACHIKUCHIPAKU__


class CPicture;
class CAllEffect;
class CEffectMePachiKuchiPaku : public CCommonEffect
{
public:
	CEffectMePachiKuchiPaku(CAllEffect* lpAll);
	~CEffectMePachiKuchiPaku();
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
	void SetNewAnimeCountMax(LPVOID lpEffect, int layer);
};

#endif
/*_*/

