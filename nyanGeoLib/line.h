//
// boxFill.h
//

#if !defined __NYANGEOLIB_LINE__
#define __NYANGEOLIB_LINE__


class CLine
{
public:
	CLine();
	virtual ~CLine();
	void End(void);

	virtual void Print(POINT startPoint,POINT endPoint,int r,int g,int b);
	virtual void Print(int startX,int startY,int endX,int endY,int r,int g,int b);

	virtual void TransPrint(POINT startPoint,POINT endPoint,int r,int g,int b,int ps);
	virtual void TransPrint(int startX,int startY,int endX,int endY,int r,int g,int b,int ps);

	virtual void PrintF(float startX,float startY,float endX,float endY, int r,int g,int b,int ps);

protected:
};






#endif
/*_*/

