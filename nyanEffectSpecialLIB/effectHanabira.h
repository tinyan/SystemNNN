//
// effectStrytchBlt.h
//

#if !defined __NYANEFFECTLIB_HANABIRA__
#define __NYANEFFECTLIB_HANABIRA__


class CPicture;
class CAllEffect;
class CEffectHanabira : public CCommonEffect
{
public:
	CEffectHanabira(CAllEffect* lpAll);
	~CEffectHanabira();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer);

	typedef struct _tagHANABIRA
	{
		int pic;
		int rev;
		int x;
		int y;
		int speedX;
		int speedY;
		int th;
		int thMax;

	} HANABIRA;
private:
	void CalcuHanabira(int st, int kosuu);
	void SetNewHanabira(int n);

	void CalcuHanabiraSub(int n);

	int m_setX;
	int m_setY;
	int m_setR;
	int m_speedX;
	int m_speedY;
	int m_loopFlag;
	int m_partsKosuu;

	int m_screenClipX1;
	int m_screenClipY1;
	int m_screenClipX2;
	int m_screenClipY2;

	int m_partsSizeX;
	int m_partsSizeY;

	HANABIRA* m_hanabira;

	int m_animePartsKosuu;
	int m_animeRevFlag;

	int m_yureTH;

	double m_yureX;
	double m_yureY;

	int m_animeType;

};


#endif
/*_*/

