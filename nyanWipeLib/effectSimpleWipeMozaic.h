//
// effectsimplewipecurtain.h
//

#if !defined __NYANWIPELIB_MOZAIC__
#define __NYANWIPELIB_MOZAIC__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;

class CAllSimpleWipe;

class CEffectSimpleWipeMozaic : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeMozaic(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeMozaic();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
