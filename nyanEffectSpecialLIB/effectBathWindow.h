//
// effectBathWindow.h
//

#if !defined __NYANEFFECTLIB_BATHWINDOW__
#define __NYANEFFECTLIB_BATHWINDOW__


class CPicture;
class CAllEffect;
class CEffectBathWindow : public CCommonEffect
{
public:
	CEffectBathWindow(CAllEffect* lpAll);
	~CEffectBathWindow();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
	BOOL CheckAllPrint(LPVOID lpEffect,int layer = -1);

	int GetEternalType(void){return 1;}

	//void PreClear(LPVOID lpEffect, int layer);
private:
	char* m_yuge0;
	char* m_yuge;

	char* m_kesu0;
	char* m_kesu;

	int m_lastEraseX;
	int m_lastEraseY;

	char* m_yugeAppear[32];

	void MaskMergeToScreen(CPicture* lpPic);

};

#endif
/*_*/

