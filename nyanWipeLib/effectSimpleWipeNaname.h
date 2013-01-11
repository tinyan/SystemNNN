//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_NANAME__
#define __NYANWIPELIB_NANAME__

class CPicture;
class CEffectSimpleWipeCommon;
class CEffectSimpleWipeShape;
class CAllSimpleWipe;

class CEffectSimpleWipeNaname : public CEffectSimpleWipeShape
{
public:
	CEffectSimpleWipeNaname(CAllSimpleWipe* allWipe,int houkou,BOOL gradFlag = FALSE,int gradSize = 64);
	virtual ~CEffectSimpleWipeNaname();
	virtual void End(void);

	void CalcuShapeWork(int count, int countMax);

protected:
	int m_nanameHoukou;
private:

};


#endif
/*_*/

