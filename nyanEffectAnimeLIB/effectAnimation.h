//
// effectanime.h
//

#if !defined __NYANEFFECTLIB_ANIMATION__
#define __NYANEFFECTLIB_ANIMATION__


class CAllEffect;
class CPicture;
class CCommonEffect;

class CEffectAnimation : public CCommonEffect
{
public:
//	CEffectAnimation(CEffect* lpCEffect);
	CEffectAnimation(CAllEffect* lpAll);
	~CEffectAnimation();
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

	void SetAnimeTageName(LPSTR name);
//	void SetAnimeBufferMax(int mx);

	static char m_animeTag[256];
	static int m_animationBufferMax;
	static int m_bufferDepth;

	static int m_animeEffectEnable;

	CPicture* GetAnimeBuffer(int n);
	LPSTR GetAnimeTag(void){return m_animeTag;}

	static void SetAnimeBufferMax(int mx);
	static void SetBufferDepth(int depth);
	static void SetAnimeEffectEnable(BOOL flg = TRUE);
	static BOOL Check256(void);


private:
	int m_lastAnimeNumber;

	CPicture* m_oldAnimationPic;


	CPicture** m_ppAnimationPic;
};

#endif
/*_*/

