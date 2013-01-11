//
// effectGrassPlane.h
//

#if !defined __NYANEFFECTLIB_GRASSPLANE__
#define __NYANEFFECTLIB_GRASSPLANE__

#define SOLITON_KOSUU_MAX 20

class CPicture;
class CAllEffect;
class CEffectGrassPlane : public CCommonEffect
{
public:
	CEffectGrassPlane(CAllEffect* lpAll);
	~CEffectGrassPlane();
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
	int m_solitonWait[SOLITON_KOSUU_MAX];
	int m_solitonSpeed[SOLITON_KOSUU_MAX];
	int m_solitonY[SOLITON_KOSUU_MAX];
	int m_solitonPower[SOLITON_KOSUU_MAX];
	int m_solitonHaba[SOLITON_KOSUU_MAX];

	void SetNewSoliton(LPVOID lpEffect, int n,BOOL inScreenFlag = FALSE);

	double* m_myDoubleWork;
	void CreateMyDoubleWork(void);

	double m_constL;
	double m_constNear;
	double m_constFar;
	double m_constDot;

	double DotToDist(double dot);
	double DistToDot(double dist);
};

#endif
/*_*/

