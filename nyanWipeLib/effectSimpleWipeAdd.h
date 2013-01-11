//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_ADD__
#define __NYANWIPELIB_ADD__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;
class CEffectSimpleWipeAdd : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeAdd(CAllSimpleWipe* allWipe);
	virtual ~CEffectSimpleWipeAdd();
	virtual void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

protected:
//	int m_houkou;
private:

};


#endif
/*_*/

