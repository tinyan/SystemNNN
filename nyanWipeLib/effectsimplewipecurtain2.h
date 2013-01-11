//
// effectsimplewipecurtain2.h
//

#if !defined __NYANWIPELIB_CURTAIN2__
#define __NYANWIPELIB_CURTAIN2__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeCurtain2 : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeCurtain2(CAllSimpleWipe* allWipe);
	~CEffectSimpleWipeCurtain2();
	void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

private:
};

#endif
/*_*/
