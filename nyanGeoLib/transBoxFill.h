//
// boxFill.h
//

#if !defined __NYANGEOLIB_TRANSBOXFILL__
#define __NYANGEOLIB_TRANSBOXFILL__


class CTransBoxFill
{
public:
	CTransBoxFill();
	virtual ~CTransBoxFill();
	void End(void);

	virtual void Print(int x,int y,int sizeX,int sizeY,int r,int g,int b,int ps);


protected:
};






#endif
/*_*/

