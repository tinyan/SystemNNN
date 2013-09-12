//
// effect.h
//

#if !defined __NYANLIB_EFFECT__
#define __NYANLIB_EFFECT__


class CPicture;

//#define EFFECT_SHURUI_MAX 256
//#define PICTURE_KOSUU_MAX 16
//#define LAYER_KOSUU_MAX 16

class CAllEffect;
//#include "effectstruct.h"

//class CCommonEffect;
//class CEffectSimpleWipe;

class CEffect
{
public:
	CEffect();
	~CEffect();
	void End(void);

	BOOL SetEffectScript(int num,int effect,int paraKosuu,int*paraPtr);
	void Calcu(int cnt = 1);
	void CalcuOnly(void);
	void Print(BOOL bScreenFlag = FALSE,BOOL bEyeCheckFlag = FALSE);

	void PrintLayers(int startLayer,int endLayer,BOOL bScreenFlag = FALSE,BOOL bEyeCheckFlag = FALSE);

	void BeginEffect(void);
	void EndEffect(void);

	CPicture* GetPicture(int n);

	BOOL ChangeEffectCommandOnly(int num, int effect);

	void ClearAllEffect(BOOL b = TRUE);
	void ClearEffect(int n,BOOL b = TRUE);
	void ClearMakeCGEffect(int n);
	void SetLayerScript(int n,int d);

	void SkipAllEffectCount(void);
	void CalcuZahyo(void);

	void SkipPrint(void);

	void CheckNeedAllPrint(void);

	int GetParaSize(void);
	void* GetEffectDataPointer(int n);
	void* GetTaihiEffectDataPointer(int n);

	void GetGetScreen(void);
	void PutGetScreen(void);

	void SetMouseZahyo(POINT pt);
	POINT GetMouseZahyo(void);

	void SetEffectFileName(int n, LPSTR filename);
	void SetMakeFileName(int n,LPSTR filename);
	LPSTR GetEffectFileName(int n);
	LPSTR GetTaihiEffectFileName(int n);
	LPSTR GetMakeFileName(int n);

	void PreMakeCG(int n);
	void PostMakeCG(int n);

	void SetEye(int n, BOOL md = TRUE);

	void GetMyRect(int layer, int n, RECT* lpRect);
	void SetMyRect(int layer, int n, RECT* lpRect);

	void ResetCount(int n = -1);
	void SetCountToLast(void);

	void CountUp(int delta = 1);

	int GetEffectEndIsChangeLayer(int effect);

	void PrintSimpleWipe(int n, CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax);

	void ExchangeEffectPic(int layer1, int layer2);

	BOOL ResizePicture(int n, int sizeX = -1, int sizeY = -1);

	BOOL CheckBGLayer(int layer);

	void InitAllParameter(void);
	void InitParameter(int layer);

	CPicture* GetOverrapPic(int n);
	void SetOverrapPic(int n, CPicture* lpPic);

	int* GetGetBuffer(void);

	void SetNowNoClearFlag(BOOL b = TRUE);

	BOOL CheckSpeaking(void);
	void SetSpeakingFlag(BOOL flg = TRUE);

	void SetEffect(int layer,EFFECT* lpEffect);
	int GetPictureNumber(int layer);
	void SetLayerPic(int layer,int pic);

	void TaihiAllEffect(void);
	void FuqueAllEffect(void);

	void TaihiAllEffectToStaticBuffer(void);
	void FuqueAllEffectByStaticBuffer(void);


	static char m_staticFileNameBuffer[][256];
	static EFFECT m_staticEffect[];
	static char m_staticTaihiFileNameBuffer[][256];
	static EFFECT m_staticTaihiEffect[];

	void SetAnimeOff(int offMode);

	void ReCreateAllShader(void);
	static int m_layerKosuuMaxSetup;
	static int m_pictureKosuuMaxSetup;
	CPicture* GetAnimeBuffer(int n);
	LPSTR GetAnimeTag(void);

	LPSTR GetExistEffectFileName(int n);

private:
	CAllEffect* m_allEffect;
	int m_layerKosuuMax;
	int m_pictureKosuuMax;
};

#endif
/*_*/
