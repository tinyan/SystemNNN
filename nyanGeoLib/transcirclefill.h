//
// transCircleFill
//

#if !defined __NYANGEOLIB_TRANSCIRCLEFILL__
#define __NYANGEOLIB_TRANSCIRCLEFILL__


class CTransCircleFill
{
public:
	CTransCircleFill();
	virtual ~CTransCircleFill();
	void End(void);

	virtual void Print(int x, int y, int rx, int ry, int r, int g, int b,int ps);

protected:
	int* m_table;
};


#endif
/*_*/

