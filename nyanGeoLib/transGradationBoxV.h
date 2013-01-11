//
// transGradationBoxV
//

#if !defined __NYANGEOLIB_TRANSGRADATIONBOXV__
#define __NYANGEOLIB_TRANSGRADATIONBOXV__



class CTransGradationBoxV
{
public:
	CTransGradationBoxV();
	virtual ~CTransGradationBoxV();
	void End(void);

	virtual void Print(POINT leftTop,SIZE size,int r1, int g1, int b1, int r4, int g4, int b4);
	virtual void Print(POINT leftTop,POINT rightBottom,int r1, int g1, int b1, int r4, int g4, int b4);
protected:
	int* m_work;
};







#endif
/*_*/

