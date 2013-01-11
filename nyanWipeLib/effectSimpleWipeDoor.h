//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_DOOR__
#define __NYANWIPELIB_DOOR__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeDoor : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeDoor(CAllSimpleWipe* allWipe,int inOut,int tateyoko);
	virtual ~CEffectSimpleWipeDoor();
	virtual void End(void);

//	void SetMoveType(int inOut,int houkou);
	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

protected:
	int m_tateyoko;
//	int m_inOut;

private:

};


#endif
/*_*/

