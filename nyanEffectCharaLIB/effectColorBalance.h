//
// effectcolorBalance.h
//

#if !defined __NYANEFFECTLIB_COLORBALANCE__
#define __NYANEFFECTLIB_COLORBALANCE__


class CPicture;
class CAllEffect;
class CEffectColorBalance : public CCommonEffect
{
public:
	CEffectColorBalance(CAllEffect* lpAll);
	~CEffectColorBalance();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
private:
	int* m_balanceSeat[10];
	int* m_colorTable[3];

};

#endif
/*_*/

