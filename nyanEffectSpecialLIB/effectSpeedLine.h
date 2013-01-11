//
// effectSpeedLine.h
//

#if !defined __NYANEFFECTLIB_SPEEDLINE__
#define __NYANEFFECTLIB_SPEEDLINE__



class CPicture;
class CAllEffect;
class CEffectSpeedLine : public CCommonEffect
{
public:
	CEffectSpeedLine(CAllEffect* lpAll);
	~CEffectSpeedLine();
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
	int* m_work;
	void ReCreateBuffer(void);

	void SetNewLine(LPVOID lpEffect, int n, BOOL bInScreen = FALSE, int layer = -1);
};

#endif
/*_*/

