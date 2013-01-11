//
// effectrain.h
//

#if !defined __NYANEFFECTLIB_RAIN4__
#define __NYANEFFECTLIB_RAIN4__

#define RAIN_KOSUU 150

class CPicture;
class CAllEffect;
class CEffectRain4 : public CCommonEffect
{
public:
	CEffectRain4(CAllEffect* lpAll);
	~CEffectRain4();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
	BOOL CheckAllPrint(LPVOID lpEffect,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

private:
	int m_dist[16];
};

#endif
/*_*/

