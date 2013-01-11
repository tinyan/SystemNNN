//
// effectsimplewipeTurnStar.h
//

#if !defined __NYANWIPELIB_TURNSTAR__
#define __NYANWIPELIB_TURNSTAR__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CEffectSimpleWipeShape;
class CAllSimpleWipe;

class CEffectSimpleWipeTurnStar : public CEffectSimpleWipeShape
{
public:
	CEffectSimpleWipeTurnStar(CAllSimpleWipe* allWipe,int houkou,int speed = 0);
	~CEffectSimpleWipeTurnStar();
	void End(void);
	void CalcuShapeWork(int count, int countMax);

//	void Print(CPicture* lpPicTurnStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpTurnStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
	void AddLeftRightDot(int leftRight, int startX, int startY, int endX,int endY);
	void AddLeftDot(int startX,int startY,int endX,int endY);
	void AddRightDot(int startX,int startY,int endX,int endY);
	int m_turnSpeed;
};

#endif
/*_*/
