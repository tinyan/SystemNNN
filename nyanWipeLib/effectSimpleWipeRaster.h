//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_RASTER__
#define __NYANWIPELIB_RASTER__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeRaster : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeRaster(CAllSimpleWipe* allWipe,int colorType);
	virtual ~CEffectSimpleWipeRaster();
	virtual void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);
//	void SetRasterOutColorType(int colorType) {m_colorType = colorType;}



protected:
	int m_colorType;
private:

};


#endif
/*_*/

