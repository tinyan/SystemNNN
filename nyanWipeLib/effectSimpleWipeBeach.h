//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_BEACH__
#define __NYANWIPELIB_BEACH__

class CPicture;
class CEffectSimpleWipeCommon;
class CEffectSimpleWipeShape;
class CAllSimpleWipe;

class CEffectSimpleWipeBeach : public CEffectSimpleWipeShape
{
public:
	CEffectSimpleWipeBeach(CAllSimpleWipe* allWipe,int houkou,BOOL gradFlag = FALSE,int gradSize = 64);
	virtual ~CEffectSimpleWipeBeach();
	virtual void End(void);

	void CalcuShapeWork(int count, int countMax);

protected:
private:

};


#endif
/*_*/

