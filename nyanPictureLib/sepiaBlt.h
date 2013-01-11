//
// greyblt.h
//

#if !defined __NYANGRAPHICSLIB_SEPIABLT__
#define __NYANGRAPHICSLIB_SEPIABLT__


class CSepiaBlt
{
public:
	CSepiaBlt();
	~CSepiaBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, int ps256,int r,int g,int b,BOOL transFlag = TRUE, LPVOID lpPalette = NULL);

private:
	void SepiaBltBeta(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,int ps256,int r,int g,int b);
	void MaskSepiaBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic,int ps256,int r,int g,int b);
};

#endif
/*_*/
