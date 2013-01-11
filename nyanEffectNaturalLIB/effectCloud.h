//
// effectCloud.h
//

#if !defined __NYANEFFECTLIB_CLOUD__
#define __NYANEFFECTLIB_CLOUD__


class CPicture;
class CAllEffect;
class CEffectCloud : public CCommonEffect
{
public:
	CEffectCloud(CAllEffect* lpAll);
	~CEffectCloud();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
private:
	int m_x;
	int m_y;
#if defined _TINYAN3DLIB_
	D3DXHANDLE m_hTechniqueCloud;
#endif

};

#endif
/*_*/

