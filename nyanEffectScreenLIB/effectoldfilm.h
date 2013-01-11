//
// effectoldfilm.h
//

#if !defined __NYANEFFECTLIB_OLDFILM__
#define __NYANEFFECTLIB_OLDFILM__

class CPicture;
class CCommonEffect;
//class CEffect;
class CAllEffect;
class CEffectOldFilm : public CCommonEffect
{
public:
	CEffectOldFilm(CAllEffect* lpAll);
	~CEffectOldFilm();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int kosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID para = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

//	struct
//	{
//		int x256;
//		int speedX256;
////		int countX;
//		int count;
//	} _m_lines[10];

private:
	void InitLine(LPVOID lpEffect,int n);
//	POINT m_point;
//	SIZE m_size;
//	int m_lineSize;
};
#endif
/*_*/

