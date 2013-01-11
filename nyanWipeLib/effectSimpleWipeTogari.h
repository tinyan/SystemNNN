//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_TOGARI__
#define __NYANWIPELIB_TOGARI__

class CPicture;
class CEffectSimpleWipeCommon;
class CEffectSimpleWipeShape;
class CAllSimpleWipe;

class CEffectSimpleWipeTogari : public CEffectSimpleWipeShape
{
public:
	CEffectSimpleWipeTogari(CAllSimpleWipe* allWipe,int houkou,BOOL gradFlag = FALSE,int gradSize = 64);
	virtual ~CEffectSimpleWipeTogari();
	virtual void End(void);

	void CalcuShapeWork(int count, int countMax);

protected:
private:

};


#endif
/*_*/

