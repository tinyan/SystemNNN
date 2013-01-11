//
// greyblt.h
//

#if !defined __NYANGRAPHICSLIB_GREYBLT2__
#define __NYANGRAPHICSLIB_GREYBLT2__


class CGreyBlt2
{
public:
	CGreyBlt2();
	~CGreyBlt2();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, int ps256,BOOL transFlag = TRUE, LPVOID lpPalette = NULL);

private:
//	void GreyBltTrans256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize, LPVOID lpPalette);
//	void GreyBltBeta256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize, LPVOID lpPalette);
//	void GreyBltTrans(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize);
	void GreyBltBeta(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,int ps256);

	void MaskGreyBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic,int ps256);
};

#endif
/*_*/
