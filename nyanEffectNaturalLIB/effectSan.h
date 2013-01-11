//
// effectsan.h
//

#if !defined __NYANEFFECTLIB_SAN__
#define __NYANEFFECTLIB_SAN__


#define SAN_KOSUU 7

class CPicture;
class CAllEffect;
class CEffectSan : public CCommonEffect
{
public:
	CEffectSan(CAllEffect* lpAll);
	~CEffectSan();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	typedef struct tagSAN
	{
		BOOL mode;
		int count;

		int startX;
		int deltaX;

//		int light;

		int startLightConst;
	} SAN;

	SAN m_san[SAN_KOSUU];
	void InitParameter(LPVOID lpEffect, int layer = -1);

private:
	void InitSan(int h);
};

#endif
/*_*/

