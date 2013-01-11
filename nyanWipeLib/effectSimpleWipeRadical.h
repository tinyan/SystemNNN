//
// effectsimplewiperadical.h
//

#if !defined __NYANLIB_RADICAL__
#define __NYANLIB_RADICAL__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeRadical : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeRadical(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeRadical();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
