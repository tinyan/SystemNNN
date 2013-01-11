//
// effectsimplewipecircle1.h
//

#if !defined __NYANWIPELIB_CIRCLE__
#define __NYANWIPELIB_CIRCLE__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CEffectSimpleWipeShape;
class CAllSimpleWipe;


class CEffectSimpleWipeCircle : public CEffectSimpleWipeShape
{
public:
	CEffectSimpleWipeCircle(CAllSimpleWipe* allWipe,int houkou);
	~CEffectSimpleWipeCircle();
	void End(void);

	void CalcuShapeWork(int count, int countMax);
private:
};

#endif
/*_*/
