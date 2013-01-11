//
//
//

#if !defined __NYANPICTURELIB_COLORBLT__
#define __NYANPICTURELIB_COLORBLT__


class CColorBlt
{
public:
	CColorBlt();
	virtual ~CColorBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,char* maskPic,SIZE srcSize,int r,int g,int b);

protected:

private:

};

#endif
/*_*/

