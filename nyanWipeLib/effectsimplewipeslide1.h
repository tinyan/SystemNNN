//
// effectsimplewipeslide1.h
//

#if !defined __NYANWIPELIB_SLIDE1__
#define __NYANWIPELIB_SLIDE1__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeSlide1 : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeSlide1(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeSlide1();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
