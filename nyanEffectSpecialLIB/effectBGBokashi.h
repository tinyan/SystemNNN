//
// effectCharaBokashi.h
//

#if !defined __NYANEFFECTLIB_BGBOKASHI__
#define __NYANEFFECTLIB_VGBOKASHI__


class CPicture;
class CAllEffect;
class CEffectBGBokashi : public CCommonEffect
{
public:
	CEffectBGBokashi(CAllEffect* lpAll);
	~CEffectBGBokashi();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);

private:
	int* m_work;
	int* m_work0;

	int* m_gyakuTable;

};

#endif
/*_*/

