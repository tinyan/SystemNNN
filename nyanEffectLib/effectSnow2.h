//
// effectsnow.h
//

#if !defined __NYANEFFECTLIB_SNOW2__
#define __NYANEFFECTLIB_SNOW2__


#define SNOW_KOSUU_MAX 100

class CPicture;
class CAllEffect;
class CEffectSnow2 : public CCommonEffect
{
public:
	CEffectSnow2(CAllEffect* lpAll);
	~CEffectSnow2();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

private:
	void InitSnow(void);
	void SetNewSnow(int n);
	void CalcuSnow(void);
	void CalcuSnowXY(int n);
//	void PrintSnow(int n);


	int m_kosuuMax;
	int m_kosuu;

	CPicture* m_snowPic;


	BOOL m_snowCalcuedFlag;

	typedef struct tagSNOW
	{
		int typ;
		int pat;
		int putX,putY;
		int x,y;
		int speedX,speedY;
		int count;
		int countMax;
	} SNOW;

	//int m_snowKosuu;
	SNOW m_snow[SNOW_KOSUU_MAX];
	int m_snowMulti[6];
	int m_snowDelta[10][30];
	int m_snowSize[6];
	int m_snowStartY[6];


	BOOL m_picFlag;
};

#endif
/*_*/

