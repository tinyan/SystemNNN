//
// effectfill.h
//

#if !defined __NYANEFFECTLIB_HAIKEIYURE__
#define __NYANEFFECTLIB_HAIKEIYURE__


class CPicture;
class CAllEffect;
class CEffectHaikeiYure : public CCommonEffect
{
public:
	CEffectHaikeiYure(CAllEffect* lpAll);
	~CEffectHaikeiYure();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer);

//	static int m_shakeTable[];

private:
	void MoveScreen(int dx, int dy);
};

#endif
/*_*/

