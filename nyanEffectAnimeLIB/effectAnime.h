//
// effectanime.h
//

#if !defined __NYANEFFECTLIB_ANIME__
#define __NYANEFFECTLIB_ANIME__


class CAllEffect;
class CPicture;
class CEffectAnime : public CCommonEffect
{
public:
//	CEffectAnime(CEffect* lpCEffect);
	CEffectAnime(CAllEffect* lpAll);
	~CEffectAnime();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);

	int GetEternalType(void){return 2;}
	int GetLayerOrPicType(void){return 1;}

private:
};

#endif
/*_*/

