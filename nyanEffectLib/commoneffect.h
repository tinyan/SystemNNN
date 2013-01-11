//
// commoneffect.h
//

#if !defined __NYANEFFECTLIB_COMMON__
#define __NYANEFFECTLIB_COMMON__


#if defined _TINYAN3DLIB_
class CMyPixelShader;
#endif

//class CEffect;
class CAllEffect;
#if defined _TINYAN3DLIB_
class CCommonEffect : public CCommonShader
#else
class CCommonEffect
#endif
{
public:
//	CCommonEffect(CEffect* lpCEffect);
	CCommonEffect(CAllEffect* lpAll,int shaderKosuu = 1);
	virtual ~CCommonEffect();
	void End(void);


//	void GeneralSetParam(int paraKosuu, int* paraPtr);
	void GeneralBeginPrint(LPVOID para = NULL,int layer = -1);
	void GeneralInit(LPVOID para = NULL,int layer = -1);
	void GeneralCalcu(LPVOID para = NULL,int layer = -1);
	void GeneralPrint(LPVOID para = NULL,int layer = -1);

	BOOL CheckRenzokuEffect(void);

	virtual BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	virtual BOOL CountIsMax(LPVOID lpEffect, int layer = -1);
	virtual void BeginPrint(LPVOID para = NULL,int layer = -1);
	virtual void Init(LPVOID para = NULL, int layer = -1);
	virtual void Calcu(LPVOID para = NULL, int layer = -1);
	virtual void Print(LPVOID para = NULL, int layer = -1);
	virtual BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
	virtual BOOL CheckAllPrint(LPVOID lpEffect,int layer = -1);

	virtual void InitParameter(LPVOID lpEffect, int layer = -1);

	virtual int GetEternalType(void);
	virtual int GetLayerOrPicType(void);
	virtual int GetOnlyOneType(void);
#if defined _TINYAN3DLIB_
	virtual void ShaderPass(int n,POINT* lpDstPoint,SIZE* lpDstSize,POINT* lpSrcPoint,SIZE* lpSrcSize);
#endif

protected:
	BOOL m_calcuedFlag;
	BOOL m_renzokuEffectFlag;
	//int countMax;
//	CEffect* m_effect;
	CAllEffect* m_allEffect;

#if defined _TINYAN3DLIB_
	CMyPixelShader* m_pixelShader;
#endif

private:
};


#endif
/*_*/

