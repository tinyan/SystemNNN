//
// effectrain.h
//

#if !defined __NYANEFFECTLIB_RAIN__
#define __NYANEFFECTLIB_RAIN__

#define RAIN_KOSUU 150

class CPicture;
class CAllEffect;
class CEffectRain : public CCommonEffect
{
public:
	CEffectRain(CAllEffect* lpAll);
	~CEffectRain();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

private:
	void InitRain(void);
	void SetNewRain(int n);
	void CalcuRain(LPVOID lpEffect);


	typedef struct tagRAIN
	{
//		int putX,putY;
		int x,y;
		int houkouX;
		int lenY;
		int speedY;
	} RAIN;
	int m_rainHoukou;
	int m_rainKosuu;
	int m_rainSpeed;
	int m_rainLength;
	int m_rainR;
	int m_rainG;
	int m_rainB;
	RAIN m_rain[RAIN_KOSUU];

};

#endif
/*_*/

