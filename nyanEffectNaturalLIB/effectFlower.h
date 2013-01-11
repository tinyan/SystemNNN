//
// effectflower.h
//

#if !defined __NYANEFFECTLIB_FLOWER__
#define __NYANEFFECTLIB_FLOWER__


#define FLOWER_KOSUU 200


class CPicture;
class CAllEffect;
class CEffectFlower : public CCommonEffect
{
public:
	CEffectFlower(CAllEffect* lpAll);
	~CEffectFlower();
	void End(void);

	BOOL SetParam(LPVOID lpEffect, int paraKosuu, int* paraPtr,int layer = -1);
	BOOL CountIsMax(LPVOID lpEffect,int layer = -1);
	void BeginPrint(LPVOID para = NULL,int layer = -1);
	void Init(LPVOID para = NULL,int layer = -1);
	void Calcu(LPVOID lpEffect = NULL,int layer = -1);
	void Print(LPVOID lpEffect = NULL,int layer = -1);

private:
	
	void CalcunewFlower(int n);
	void CalcuFlowerXY(int n);
	BOOL m_flowerCalcuedFlag;
	void SetNewFlower(int n);
	void CalcuFlower(void);

	CPicture* m_flowerPic;

	typedef struct tagFLOWER
	{
		int typ;
		int pat;
		int putX,putY;
		int x,y;
		int speedX,speedY;
		int count,countMax;
	} FLOWER;

	int m_flowerKosuu;
	FLOWER m_flower[FLOWER_KOSUU];
	int m_flowerMulti[3];
	int m_flowerDeltaX[10][40];
	int m_flowerDeltaY[10][40];
	int m_flowerSize[3];
	int m_flowerStartY[3];


	BOOL m_picFlag;

};

#endif
/*_*/

