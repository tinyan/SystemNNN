//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_ZOOM__
#define __NYANWIPELIB_ZOOM__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeZoom : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeZoom(CAllSimpleWipe* allWipe,int scale,int placeType);
	virtual ~CEffectSimpleWipeZoom();
	virtual void End(void);

//	void SetMoveType(int inOut,int houkou);
	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

protected:
	int m_scale;
	int m_placeType;

private:

};


#endif
/*_*/

