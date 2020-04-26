//
// effectHamon.h
//

#if !defined __NYANEFFECTLIB_HAMON__
#define __NYANEFFECTLIB_HAMON__


class CPicture;
class CAllEffect;
class CEffectHamon : public CCommonEffect
{
public:
	CEffectHamon(CAllEffect* lpAll);
	~CEffectHamon();
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
	int* m_table;
	//int* m_calcuTable;
	//int* m_calcuTable2;

	int* m_vector;

	BOOL m_vectorMakedFlag;
	int m_vectorCenterX;
	int m_vectorCenterY;
	int m_clipY1;
	int m_sizeY1;
	int m_clipX1;
	int m_sizeX1;
	int* m_vectorAdjusted;

	int m_hamonKyoriMax;
};

#endif
/*_*/

