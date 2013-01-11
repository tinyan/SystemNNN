//
// effectsimplewipeHeart.h
//

#if !defined __NYANWIPELIB_HEART__
#define __NYANWIPELIB_HEART__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CEffectSimpleWipeShape;

class CAllSimpleWipe;

class CEffectSimpleWipeHeart : public CEffectSimpleWipeShape
{
public:
	CEffectSimpleWipeHeart(CAllSimpleWipe* allWipe,int houkou);
	~CEffectSimpleWipeHeart();
	void End(void);

	void CalcuShapeWork(int count, int countMax);

//	void Print(CPicture* lpPicHeartt, CPicture* lpPicEnd, int count, int countMax,POINT* lpHearttPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
