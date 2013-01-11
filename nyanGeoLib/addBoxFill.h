//
// boxFill.h
//

#if !defined __NYANGEOLIB_ADDBOXFILL__
#define __NYANGEOLIB_ADDBOXFILL__


class CAddBoxFill
{
public:
	CAddBoxFill();
	virtual ~CAddBoxFill();
	void End(void);

	virtual void Print(int x,int y,int sizeX,int sizeY,int r,int g,int b,int ps = 100);


protected:
};






#endif
/*_*/

