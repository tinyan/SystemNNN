//
// effectmozaic.h
//

#if !defined __NYANEFFECTLIB_MOZAIC__
#define __NYANEFFECTLIB_MOZAIC__


class CPicture;
class CEffectMozaic : public CCommonEffect
{
public:
	CEffectMozaic(CAllEffect* lpAll);
	~CEffectMozaic();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

private:
	void PrintMozaicMain(int sx, int sy, int ex, int ey,int sizeX,int sizeY);

};

#endif
/*_*/

