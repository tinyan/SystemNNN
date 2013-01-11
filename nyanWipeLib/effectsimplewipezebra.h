//
// effectsimplewipezebra.h
//

#if !defined __NYANWIPELIB_ZEBRA__
#define __NYANWIPELIB_ZEBRA__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeZebra : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeZebra(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeZebra();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
