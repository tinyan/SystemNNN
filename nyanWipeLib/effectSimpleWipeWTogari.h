//
// effectsimplewipeWTogari.h
//

#if !defined __NYANWIPELIB_WTOGARI__
#define __NYANWIPELIB_WTOGARI__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CEffectSimpleWipeShape;
class CAllSimpleWipe;


class CEffectSimpleWipeWTogari : public CEffectSimpleWipeShape
{
public:
	CEffectSimpleWipeWTogari(CAllSimpleWipe* allWipe,int houkou);
	~CEffectSimpleWipeWTogari();
	void End(void);

	void CalcuShapeWork(int count, int countMax);
private:
};

#endif
/*_*/
