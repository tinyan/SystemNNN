//
// effectsimplewipeoverrap.h
//

#if !defined __NYANWIPELIB_OVERRAP__
#define __NYANWIPELIB_OVERRAP__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeOverrap : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeOverrap(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeOverrap();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
