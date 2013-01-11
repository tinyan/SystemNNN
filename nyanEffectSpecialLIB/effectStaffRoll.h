//
// effectSTaffRoll.h
//

#if !defined __NYANEFFECTLIB_STAFFROLL__
#define __NYANEFFECTLIB_STAFFROLL__


class CPicture;
class CAllEffect;
class CEffectStaffRoll : public CCommonEffect
{
public:
	CEffectStaffRoll(CAllEffect* lpAll);
	~CEffectStaffRoll();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);
	void InitParameter(LPVOID lpEffect, int layer = -1);

	BOOL CheckNeedPicPrint(LPVOID lpEffect,int layer = -1);
private:
	int* m_percent;
	void MakeTableSub(int yStart, int yEnd, int percent1, int percent2);

	void PrintStaffRollSub(LPVOID lpEffect,int layerStart, int deltaLayer);

};

#endif
/*_*/

