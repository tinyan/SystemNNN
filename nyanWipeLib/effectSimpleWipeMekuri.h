//
// effectsimplewipecommon.h
//

#if !defined __NYANLIB_MEKURI__
#define __NYANLIB_MEKURI__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeMekuri : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeMekuri(CAllSimpleWipe* allWipe);
	virtual ~CEffectSimpleWipeMekuri();
	virtual void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

protected:
//	int m_houkou;
private:

};


#endif
/*_*/

