//
// effectsimplewipeoverrap.h
//

#if !defined __NYANWIPELIB_MULTI__
#define __NYANWIPELIB_MULTI__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeMulti : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeMulti(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeMulti();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
