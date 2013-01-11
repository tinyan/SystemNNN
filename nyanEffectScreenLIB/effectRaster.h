//
// effectRaster.h
//

#if !defined __NYANEFFECTLIB_RASTER__
#define __NYANEFFECTLIB_RASTER__


class CPicture;
class CAllEffect;
class CEffectRaster : public CCommonEffect
{
public:
	CEffectRaster(CAllEffect* lpAll);
	~CEffectRaster();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

private:
};

#endif
/*_*/

