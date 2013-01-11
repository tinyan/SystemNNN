//
// effecttaiyo.h
//

#if !defined __NYANEFFECTLIB_TAIYO__
#define __NYANEFFECTLIB_TAIYO__


class CPicture;
class CAllEffect;
class CEffectTaiyo : public CCommonEffect
{
public:
	CEffectTaiyo(CAllEffect* lpAll);
	~CEffectTaiyo();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

private:
	void InitTaiyo(int* lpPara);
	void PrintLightCircle(int x, int y, int r, int colR, int colG, int colB);
	void PrintLightTorus(int x, int y, int r, int hole, int colR, int colG, int colB);




	int m_taiyoKyoriPercent[20];
	int m_taiyoR[20];
	int m_taiyoR2[20];
	int m_taiyoColorR[20];
	int m_taiyoColorG[20];
	int m_taiyoColorB[20];
	int m_taiyoKieru[20];
	int m_taiyoType[20];

	int* m_printTable;

};

#endif
/*_*/

