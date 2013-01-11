//
//
//

#if !defined __NYANEFFECTLIB_ALLEFFECT__
#define __NYANEFFECTLIB_ALLEFFECT__


#define EFFECT_SHURUI_MAX 256
//#define PICTURE_KOSUU_MAX 16
//#define LAYER_KOSUU_MAX 16
#define PICTURE_KOSUU_MAX 32
#define LAYER_KOSUU_MAX 32

#include "effectstruct.h"


class CPicture;
class CCommonEffect;
class CAllEffect
{
public:
	CAllEffect();
	~CAllEffect();
	void End(void);


	BOOL SetEffectScript(int num,int effect,int paraKosuu,int*paraPtr);
	void Print(BOOL bScreenFlag = FALSE,BOOL bEyeCheckFlag = FALSE);
	void PrintLayers(int startLayer,int endLayer,BOOL bScreenFlag = FALSE,BOOL bEyeCheckFlag = FALSE);




	POINT GetSrcPoint(int layer);
	POINT GetDstPoint(int layer);
	CPicture* GetPicture(int layer);
	SIZE GetDstSize(int layer);
	BOOL CheckBGLayer(int layer);

//	POINT GetMouseZahyo(void);

	void ExchangeEffectPic(int layer1,int layer2);
	BOOL ChangeEffectCommandOnly(int layer,int cmd);
	
	int GetOtherLayerPic(int layer);


	int* GetTempWork(void){return m_tempWork;}

//	BOOL CheckSpeaking(void);
	int* GetGetBuffer(void);






	void SetEye(int n, BOOL md = TRUE);
	void ClearAllEffect(BOOL b = FALSE);
	void ClearEffect(int n);
	void ClearMakeCGEffect(int n);
	void SetLayerScript(int n,int d);
	void SkipAllEffectCount(void);
	void CalcuZahyo(void);
	void Calcu(int cnt = 1);
	void CalcuOnly(void);
	void SkipPrint(void);
	void CheckNeedAllPrint(void);
	int GetParaSize(void);
	void* GetEffectDataPointer(int n);
	void GetGetScreen(void);
	void PutGetScreen(void);

	void SetMouseZahyo(POINT pt) {m_mousePoint = pt;}
	POINT GetMouseZahyo(void) {return m_mousePoint;}
	void EndEffect(void);

	EFFECT m_effect[LAYER_KOSUU_MAX];
	EFFECT m_makeEffect[LAYER_KOSUU_MAX];
	EFFECT m_taihiEffect[LAYER_KOSUU_MAX];

	char m_filename[PICTURE_KOSUU_MAX][256];
	char m_makeFilename[PICTURE_KOSUU_MAX][256];
	char m_taihiFilename[PICTURE_KOSUU_MAX][256];


	void SetEffectFileName(int n, LPSTR filename);
	void SetMakeFileName(int n,LPSTR filename);
	LPSTR GetEffectFileName(int n);
	LPSTR GetMakeFileName(int n);

	void PreMakeCG(int n);
	void PostMakeCG(int n);

	int m_makeCGPicNum;
	void GetMyRect(int layer, int n, RECT* lpRect);
	void SetMyRect(int layer, int n, RECT* lpRect);

	void ResetCount(int n = -1);
	void SetCountToLast(void);
	void BeginEffect(void);

	void CountUp(int delta = 1);
	int GetEffectEndIsChangeLayer(int effect);
	static BOOL m_renzokuEffectFlag[];
	void PrintSimpleWipe(int n, CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax);
	BOOL ResizePicture(int n, int sizeX = -1, int sizeY = -1);

	void InitAllParameter(void);
	void InitParameter(int layer);

	CPicture* GetOverrapPic(int n);
	void SetOverrapPic(int n, CPicture* lpPic);

	void SetNowNoClearFlag(BOOL b = TRUE);

	BOOL CheckSpeaking(void) {return m_speakingFlag;}
	void SetSpeakingFlag(BOOL flg = TRUE) {m_speakingFlag = flg;}

/////


	//void ExchangeEffectPic(int layer1, int layer2);


//	BOOL CheckBGLayer(int layer);



	//int* GetGetBuffer(void);

	void TaihiAllEffect(void);
	void FuqueAllEffect(void);
	LPSTR GetTaihiEffectFileName(int n);
	void* GetTaihiEffectDataPointer(int n);


	void ReCreateAllShader(void);
	/////
private:
	int* m_tempWork;

	CCommonEffect** m_ppEffects;
	int m_effectKosuu;

	CPicture* m_pic[PICTURE_KOSUU_MAX+1];
	BOOL m_eyeFlag[PICTURE_KOSUU_MAX];

	CPicture* m_overrapPic0;
	CPicture* m_overrapPic1;

	BOOL m_nowNoClearFlag;
	POINT m_mousePoint;

	BOOL m_speakingFlag;
};







#endif
/*_*/

