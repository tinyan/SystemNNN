//
// effectrain.h
//

#if !defined __NYANEFFECTLIB_RAIN2__
#define __NYANEFFECTLIB_RAIN2__

#define RAIN_KOSUU 150

class CPicture;
class CAllEffect;
class CEffectRain2 : public CCommonEffect
{
public:
	CEffectRain2(CAllEffect* lpAll);
	~CEffectRain2();
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
	int m_x[16][4];
	int m_y[16][4];
	int m_speedX[16][4];
	int m_speedY[16][4];
	int m_randomX[16][4];
	int m_randomY[16][4];

	int m_initRnd[16];

};

#endif
/*_*/

