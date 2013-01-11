//
// greyblt.h
//

#if !defined __NYANGRAPHICSLIB_GREYBLT__
#define __NYANGRAPHICSLIB_GREYBLT__


class CGreyBlt
{
public:
	CGreyBlt();
	~CGreyBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, BOOL transFlag = TRUE, LPVOID lpPalette = NULL);

private:
	void GreyBltTrans256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize, LPVOID lpPalette);
	void GreyBltBeta256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize, LPVOID lpPalette);

	void GreyBltTrans(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize);
	void GreyBltBeta(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize);

	void MaskGreyBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic);
};

#endif
/*_*/
