//
// effectsimplewipecircle1.h
//

#if !defined __NYANWIPELIB_WARP1__
#define __NYANWIPELIB_WARP1__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeWarp1 : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeWarp1(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeWarp1();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
