//
// effectStrytchBlt.h
//

#if !defined __NYANEFFECTLIB_RAINBOW__
#define __NYANEFFECTLIB_RAINBOW__


class CPicture;
class CAllEffect;
class CEffectRainbow : public CCommonEffect
{
public:
	CEffectRainbow(CAllEffect* lpAll);
	~CEffectRainbow();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

private:
	int* m_color;

	int m_colorOffset;

	int m_rainbowTable[6+1];
};


#endif
/*_*/

