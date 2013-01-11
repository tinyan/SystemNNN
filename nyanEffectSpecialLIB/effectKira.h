//
// effectkira.h
//

#if !defined __NYANEFFECTLIB_KIRA__
#define __NYANEFFECTLIB_KIRA__

#define KIRA_KOSUU 20

class CPicture;
class CAllEffect;
class CEffectKira : public CCommonEffect
{
public:
	CEffectKira(CAllEffect* lpAll);
	~CEffectKira();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

	typedef struct tagKIRA
	{
		int count;
		int countMax;
		int x,y;
	} KIRA;


	KIRA m_kira[KIRA_KOSUU];

private:
	CPicture* m_pic;
	void InitKira(LPVOID lpEffect);
	void SetKiraSub(LPVOID lpEffect,int k);
	void PrintKiraSub(int x, int y, int ps);

	int m_kiraTable[64*64];

	BOOL m_picFlag;

};

#endif
/*_*/

