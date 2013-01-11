//
//
//

#if !defined __NYANPICTURELIB_COLORADDBLT__
#define __NYANPICTURELIB_COLORADDBLT__


class CColorAddBlt
{
public:
	CColorAddBlt();
	virtual ~CColorAddBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize,BOOL transFlag,int r,int g,int b,int ps = 100);

protected:
private:

};



#endif
/*_*/

