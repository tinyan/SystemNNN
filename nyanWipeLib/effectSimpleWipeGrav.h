//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_GRAV__
#define __NYANWIPELIB_GRAV__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeGrav : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeGrav(CAllSimpleWipe* allWipe,int omoteura=0);
	virtual ~CEffectSimpleWipeGrav();
	virtual void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);
protected:
	int m_omoteura;

private:

};


#endif
/*_*/

