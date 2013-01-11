//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_SLOT__
#define __NYANWIPELIB_SLOT__

class CPicture;
class CEffectSimpleWipeCommon;
class CAllSimpleWipe;


class CEffectSimpleWipeSlot : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeSlot(CAllSimpleWipe* allWipe,int slot,int tateyoko = 0);
	virtual ~CEffectSimpleWipeSlot();
	virtual void End(void);

//	void SetMoveType(int inOut,int houkou);
	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

//	static int m_tokorotenHoukou[];
	static int m_slotKaiten[];

protected:
	int m_slot;
	int m_tateyoko;
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

