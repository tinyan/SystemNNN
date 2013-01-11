//
// transCircleFill
//

#if !defined __NYANGEOLIB_ADDCIRCLEFILL__
#define __NYANGEOLIB_ADDCIRCLEFILL__


class CAddCircleFill
{
public:
	CAddCircleFill();
	virtual ~CAddCircleFill();
	void End(void);

	virtual void Print(int x, int y, int rx, int ry, int dr, int dg, int db,int ps = 100);

protected:
	int* m_table;
};


#endif
/*_*/

