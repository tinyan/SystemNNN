//
// effectsimplewipePafe.h
//

#if !defined __NYANWIPELIB_PAGE__
#define __NYANWIPELIB_PAGE__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipePage : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipePage(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipePage();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
