//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_CENTER__
#define __NYANWIPELIB_CENTER__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeCenter : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeCenter(CAllSimpleWipe* allWipe,int houkou,int trans = 0);
	virtual ~CEffectSimpleWipeCenter();
	virtual void End(void);

//	void SetMoveType(int inOut,int houkou);
	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

protected:
	int m_transFlag;

private:

};


#endif
/*_*/

