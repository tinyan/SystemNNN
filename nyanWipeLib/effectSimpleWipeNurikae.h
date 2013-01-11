//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_NURIKAE__
#define __NYANWIPELIB_NURIKAE__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeNurikae : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeNurikae(CAllSimpleWipe* allWipe);
	virtual ~CEffectSimpleWipeNurikae();
	virtual void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

protected:

private:

};


#endif
/*_*/

