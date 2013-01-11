//
// fade.h
//

#if !defined __NYANGEOLIB_FADE__
#define __NYANGEOLIB_FADE__


class CFade
{
public:
	CFade();
	virtual ~CFade();
	void End(void);

	virtual void Print(int ps1,int r=0,int g=-1,int b=-1,int ps2 = -1);

protected:

};

#endif
/*_*/


