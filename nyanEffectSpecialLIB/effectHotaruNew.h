//
// effectHotaru.h
//

#if !defined __NYANEFFECTLIB_HOTARUNEW__
#define __NYANEFFECTLIB_HOTARUNEW__


class CPicture;
class CAllEffect;
class CEffectHotaruNew : public CCommonEffect
{
public:
	CEffectHotaruNew(CAllEffect* lpAll);
	~CEffectHotaruNew();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr, int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect, int layer = -1);
	void BeginPrint(LPVOID para = NULL, int layer = -1);
	void Init(LPVOID para = NULL, int layer = -1);
	void Calcu(LPVOID lpEffect = NULL, int layer = -1);
	void Print(LPVOID lpEffect = NULL, int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect, int layer);


	//	BOOL CheckNeedPicPrint(LPVOID lpEffect);
	typedef struct _tagHOTARUNew
	{
		int frame;
		int frameIn;
		int frameKeep;
		int frameOut;

		float x;
		float y;
		float speedX;
		float speedY;
		int th;
		int thMax;

	} HOTARUNew;

private:
	HOTARUNew* m_hotaru;
	
	int* m_lightTable;


	void CalcuHotaru(int st, int kosuu);
	void SetNewHotaru(int n,int randomStartFrame = 0);

	void CalcuHotaruSub(int n);

	int m_setX;
	int m_setY;
	//	int m_setR;
	int m_setSizeX;
	int m_setSizeY;
	int m_speedX;
	int m_speedY;
	int m_loopFlag;

	int m_screenClipX1;
	int m_screenClipY1;
	int m_screenClipX2;
	int m_screenClipY2;

	int m_yure;
	int m_yureKakudo;
	int m_yureHaba;
	double m_yureCos;
	double m_yureSin;

	void CalcuYureCosSin(void);
	CPicture* m_hotaruPic;

	int m_speedRandom;
	int m_partsSizeX;
	int m_partsSizeY;
	int m_animeSpeed;

	void GetInitParam(void* lp);
	int m_totalFrame;
	int m_kosuu;
	int m_transLow;
	int m_transHigh;
	int m_inFrame;
	int m_outFrame;
	int m_frameLengthRandom;
	int m_frameStartRandom;
	int m_frameLoopFlag;
	int m_repopFlag;

	int m_printType;

};

#endif
/*_*/


