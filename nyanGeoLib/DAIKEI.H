//
// daikei.h
//

#if !defined __NYANGEOLIB_DAIKEI__
#define __NYANGEOLIB_DAIKEI__

class CDaikei
{
public:
	CDaikei();
	virtual ~CDaikei();
	void End(void);

	virtual void Print(POINT leftUpperPoint, int sizeUpperX, POINT leftBottomPoint, int sizeBottomX, int r, int g, int b);

protected:
	int* m_work;
};

#endif
/*_*/

