//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_RANDOMSTRIP__
#define __NYANWIPELIB_RANDOMSTRIP__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeRandomStrip : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeRandomStrip(CAllSimpleWipe* allWipe);
	virtual ~CEffectSimpleWipeRandomStrip();
	virtual void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

protected:
private:

};


#endif
/*_*/

