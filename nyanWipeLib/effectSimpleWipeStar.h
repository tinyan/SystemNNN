//
// effectsimplewipeStar.h
//

#if !defined __NYANWIPELIB_STAR__
#define __NYANWIPELIB_STAR__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CEffectSimpleWipeShape;

class CAllSimpleWipe;

class CEffectSimpleWipeStar : public CEffectSimpleWipeShape
{
public:
	CEffectSimpleWipeStar(CAllSimpleWipe* allWipe,int houkou);
	~CEffectSimpleWipeStar();
	void End(void);
	void CalcuShapeWork(int count, int countMax);

//	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
