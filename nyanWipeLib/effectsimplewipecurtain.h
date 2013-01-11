//
// effectsimplewipecurtain.h
//

#if !defined __NYANWIPELIB_CURTAIN__
#define __NYANWIPELIB_CURTAIN__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeCurtain : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeCurtain(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeCurtain();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
