//
// multi.h
//

#if !defined __NYANGEOLIB_MULTI__
#define __NYANGEOLIB_MULTI__



class CMulti
{
public:
	CMulti();
	virtual ~CMulti();
	void End(void);

	virtual void Print(int percentR,int percentG = -1,int percentB = -1);
	virtual void PrintClip(int startX,int startY,int sizeX,int sizeY,int percentR,int percentG = -1,int percentB = -1);


protected:
};






#endif
/*_*/

