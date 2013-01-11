//
// effectsimplewipechecker.h
//

#if !defined __NYANWIPELIB_CHECKER__
#define __NYANWIPELIB_CHECKER__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeChecker : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeChecker(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeChecker();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
