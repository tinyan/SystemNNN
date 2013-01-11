//
// simplewipe.h
//

#if !defined __NYANEFFECTLIB_SIMPLEWIPE__
#define __NYANEFFECTLIB_SIMPLEWIPE__

class CEffect;
class CPicture;
class CAllEffect;

//
//

class CAllSimpleWipe;
class CEffectSimpleWipeCommon;
//#define WIPES_KOSUU 256


class CEffectSimpleWipe : public CCommonEffect
{
public:
	CEffectSimpleWipe(CAllEffect* lpAll);
	~CEffectSimpleWipe();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
	CEffectSimpleWipeCommon* GetWipeObject(int n);

	void ReCreateAllShader(void);

private:
	CAllSimpleWipe* m_allWipe;
};

#endif

/*_*/
