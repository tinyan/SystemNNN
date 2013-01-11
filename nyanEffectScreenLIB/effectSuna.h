//
// effectsuna.h
//

#if !defined __NYANEFFECTLIB_SUNA__
#define __NYANEFFECTLIB_SUNA__


class CPicture;
class CAllEffect;
class CEffectSuna : public CCommonEffect
{
public:
	CEffectSuna(CAllEffect* lpAll);
	~CEffectSuna();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

private:
	void InitSuna(void);

	int m_sunaCount;
//	int m_suna[320*240 / 4];
	int* m_suna;

	CPicture* m_sunaPic;

};

#endif
/*_*/

