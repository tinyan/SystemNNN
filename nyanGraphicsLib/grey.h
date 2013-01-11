//
// multi.h
//

#if !defined __NYANGEOLIB_GREY__
#define __NYANGEOLIB_GREY__



class CGrey
{
public:
	CGrey();
	virtual ~CGrey();
	void End(void);

	virtual void Print(void);
	virtual void PrintClip(int startX,int startY,int sizeX,int sizeY);
protected:
};






#endif
/*_*/

