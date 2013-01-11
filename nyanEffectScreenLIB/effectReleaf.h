//
// effectreleaf.h
//

#if !defined __NYANEFFECTLIB_RELEAF__
#define __NYANEFFECTLIB_RELEAF__


class CPicture;
class CAllEffect;
class CEffectReleaf : public CCommonEffect
{
public:
	CEffectReleaf(CAllEffect* lpAll);
	~CEffectReleaf();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

private:
};


#endif
/*_*/

