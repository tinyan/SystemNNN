//
// effectGet.h
//

#if !defined __NYANEFFECTLIB_GET__
#define __NYANEFFECTLIB_GET__


class CPicture;
class CAllEffect;
class CEffectGet : public CCommonEffect
{
public:
	CEffectGet(CAllEffect* lpAll);
	~CEffectGet();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

//	BOOL CheckNeedPicPrint(LPVOID lpEffect);


	static int* m_effectGetBuffer;
	static CPicture* m_effectGetBufferPicture;

	void GetScreen(void);

private:
};

#endif
/*_*/

