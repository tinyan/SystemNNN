//
// effectHotaru.h
//

#if !defined __NYANEFFECTLIB_HOTARU__
#define __NYANEFFECTLIB_HOTARU__


class CPicture;
class CAllEffect;
class CEffectHotaru : public CCommonEffect
{
public:
	CEffectHotaru(CAllEffect* lpAll);
	~CEffectHotaru();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

//	BOOL CheckNeedPicPrint(LPVOID lpEffect);
	typedef struct _tagHOTARU
	{
		int x;
		int y;
		int speedX;
		int speedY;
		int th;
		int thMax;

	} HOTARU;

private:
	HOTARU* m_hotaru;
	int* m_lightTable;

	void CalcuHotaru(int st, int kosuu);
	void SetNewHotaru(int n);

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
};

#endif
/*_*/

