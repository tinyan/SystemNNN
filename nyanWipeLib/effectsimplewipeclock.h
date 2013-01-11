//
// effectsimplewipeclock.h
//

#if !defined __NYANWIPELIB_CLOCK__
#define __NYANWIPELIB_CLOCK__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CEffectSimpleWipeShape;
class CAllSimpleWipe;

class CEffectSimpleWipeClock : public CEffectSimpleWipeShape
{
public:
	CEffectSimpleWipeClock(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeClock();
	void End(void);

	void CalcuShapeWork(int count, int countMax);

//	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
