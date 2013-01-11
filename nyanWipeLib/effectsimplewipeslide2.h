//
// effectsimplewipeslide2.h
//

#if !defined __NYANWIPELIB_SLIDE2__
#define __NYANWIPELIB_SLIDE2__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeSlide2 : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeSlide2(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeSlide2();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
