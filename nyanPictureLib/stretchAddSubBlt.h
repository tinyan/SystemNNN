//
//
//

#if !defined __NYANPICTURELIB_STRETCHADDSUBBLT__
#define __NYANPICTURELIB_STRETCHADDSUBBLT__


class CStretchAddSubBlt
{
public:
	CStretchAddSubBlt();
	virtual ~CStretchAddSubBlt();
	void End(void);

	void Print(POINT dstPoint,POINT srcPoint,SIZE dstSize,SIZE srcSize,LPVOID picData,LPVOID maskData,SIZE picSize,BOOL bTransFlag,int transPercent,int deltaR = 0,int deltaG = 0,int deltaB = 0);

protected:
private:

};



#endif
/*_*/

