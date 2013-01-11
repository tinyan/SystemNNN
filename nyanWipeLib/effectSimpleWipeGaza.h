//
// effectsimplewipeGaza.h
//

#if !defined __NYANWIPELIB_GAZA__
#define __NYANWIPELIB_GAZA__

class CPicture;
class CEffectSimpleWipeCommon;
class CEffectSimpleWipeShape;
class CAllSimpleWipe;

class CEffectSimpleWipeGaza : public CEffectSimpleWipeShape
{
public:
	CEffectSimpleWipeGaza(CAllSimpleWipe* allWipe,int gazaType,BOOL gradFlag = FALSE,int gradSize = 64);
	virtual ~CEffectSimpleWipeGaza();
	virtual void End(void);

	void CalcuShapeWork(int count, int countMax);

//	void SetGazaType(int houkou);
//	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

protected:
//	int m_houkou;
private:

};


#endif
/*_*/

