//
//
//

#if !defined __NYANPICTURELIB_STRETCHBLT__
#define __NYANPICTURELIB_STRETCHBLT__


class CStretchBlt
{
public:
	CStretchBlt();
	virtual ~CStretchBlt();
	void End(void);

	void Print(POINT dstPoint,POINT srcPoint,SIZE dstSize,SIZE srcSize,LPVOID picData,LPVOID maskData,SIZE picSize,BOOL bTransFlag,int transPercent);

protected:
private:

};



#endif
/*_*/

