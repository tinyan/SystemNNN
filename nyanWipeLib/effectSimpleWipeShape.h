//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_SHAPE__
#define __NYANWIPELIB_SHAPE__

class CPicture;

class CEffectSimpleWipeCommon;
class CAllSimplwWipe;

class CEffectSimpleWipeShape : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeShape(CAllSimpleWipe* allWipe);
	virtual ~CEffectSimpleWipeShape();
	virtual void End(void);

	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);


	void SetMaxDivide(int maxDivide) {m_shapeDivide = maxDivide;}
	void SetGrad(BOOL gradFlag = TRUE,int grad = 64){m_gradFlag = gradFlag;m_gradSize = grad;}

protected:
	virtual void CalcuShapeWork(int count, int countMax);


//	int* m_shapeWork;
	int m_shapeDivide;
	int m_gradSize;
	BOOL m_gradFlag;
//	int m_effectHoukou;	//0: ägëÂ 1:èkè¨
//	void SetMaxDivide(int maxDivide) {m_shapeDivide = maxDivide;}
//	void CreateShapeWork(void);

	
	void PrintShape(void);
	void PrintShape1(void);	//2ï™äÑÇÕÇ±ÇÍÇ≈ÇµÇÂÇËÇ∑ÇÈ

	void PrintGradShape(void);	//2ï™äÑ


//	void PrintShape4(void);
//	void PrintShape6(void);

//	int* m_startSrcPicPtr;
//	int* m_endSrcPicPtr;
//	int m_startSrcPitch;
//	int m_endSrcPitch;


private:

};


#endif
/*_*/

