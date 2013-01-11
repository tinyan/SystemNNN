//
// transTorusFill
//

#if !defined __NYANGEOLIB_ADDTORUSFILL__
#define __NYANGEOLIB_ADDTORUSFILL__


class CAddTorusFill
{
public:
	CAddTorusFill();
	virtual ~CAddTorusFill();
	void End(void);

	virtual void Print(int x, int y, int rx, int ry, int x2,int y2,int rx2, int ry2,int dr, int dg, int db,int ps = 100);

protected:
	int* m_table;
};


#endif
/*_*/

