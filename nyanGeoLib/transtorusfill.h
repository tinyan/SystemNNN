//
// transTorusFill
//

#if !defined __NYANGEOLIB_TRANSTORUSFILL__
#define __NYANGEOLIB_TRANSTORUSFILL__


class CTransTorusFill
{
public:
	CTransTorusFill();
	virtual ~CTransTorusFill();
	void End(void);

	virtual void Print(int x, int y, int rx, int ry, int x2,int y2,int rx2, int ry2,int r, int g, int b,int ps);

protected:
	int* m_table;
};


#endif
/*_*/

