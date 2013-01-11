//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_SUDARE__
#define __NYANWIPELIB_SUDARE__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeSudare : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeSudare(CAllSimpleWipe* allWipe,int houkou,int centerType);
	virtual ~CEffectSimpleWipeSudare();
	virtual void End(void);

//	void SetEffectHoukou(int centerType, int houkou);
	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

protected:
	int m_centerType;
//	int m_houkou;
//	int m_houkou;
private:

};


#endif
/*_*/

