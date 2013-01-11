//
//
//


#if !defined __NYANGEOLIB_FILLSCREEN__
#define __NYANGEOLIB_FILLSCREEN__


class CFillScreen
{
public:
	CFillScreen();
	virtual ~CFillScreen();
	void End(void);

	virtual void Print(int r = 0,int g = -1, int b = -1);
protected:
};

#endif
/*_*/
