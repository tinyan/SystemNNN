//
// effectflash.h
//

#if !defined __NYANEFFECTLIB_FLASH__
#define __NYANEFFECTLIB_FLASH__


class CPicture;
class CAllEffect;
class CEffectFlash : public CCommonEffect
{
public:
	CEffectFlash(CAllEffect* lpAll);
	~CEffectFlash();
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

