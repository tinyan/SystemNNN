//
// effectBeach.h
//

#if !defined __NYANEFFECTLIB_BEACH__
#define __NYANEFFECTLIB_BEACH__


class CPicture;
class CAllEffect;
class CEffectBeach : public CCommonEffect
{
public:
	CEffectBeach(CAllEffect* lpAll);
	~CEffectBeach();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
	typedef struct _tagBEACH
	{
		double r;
		double w;
		int th;
	}BEACH;

	int GetEternalType(void){return 1;}
	int GetLayerOrPicType(void){return 1;}
	int GetOnlyOneType(void){return 1;}

private:
	static BEACH m_rwt[2][3];

	int m_th[2][3];
	int m_move[2];

};

#endif
/*_*/

