//
// multi.h
//

#if !defined __NYANGRAPHICSLIB_ADDSUB__
#define __NYANGRAPHICSLIB_ADDSUB__



class CAddSub
{
public:
	CAddSub();
	virtual ~CAddSub();
	void End(void);

	virtual void Print(int deltaR,int deltaG = -9999,int deltaB = -9999);
	virtual void PrintClip(int startX,int startY,int sizeX,int sizeY,int deltaR,int deltaG = -9999,int deltaB = -9999);

protected:
};






#endif
/*_*/

