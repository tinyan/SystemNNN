//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_MOVE__
#define __NYANWIPELIB_MOVE__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;


class CEffectSimpleWipeMove : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeMove(CAllSimpleWipe* allWipe,int inOut, int direction);
	virtual ~CEffectSimpleWipeMove();
	virtual void End(void);

//	void SetMoveType(int inOut,int houkou);
	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

protected:
//	virtual void CalcuShapeWork(int count, int countMax);

//	void SetMaxDivide(int maxDivide) {m_shapeDivide = maxDivide;}

//	int* m_shapeWork;
//	int m_shapeDivide;

//	void SetMaxDivide(int maxDivide) {m_shapeDivide = maxDivide;}
//	void CreateShapeWork(void);

//	void PrintShape(void);

//	int* m_startSrcPicPtr;
//	int* m_endSrcPicPtr;
//	int m_startSrcPitch;
//	int m_endSrcPitch;

	int m_direction;

	//int m_houkou;
	//int m_inOut;

private:

};


#endif
/*_*/

