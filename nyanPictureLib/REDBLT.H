//
// redBlt.h
//

#if !defined __NYANGRAPHICSLIB_REDBLT__
#define __NYANGRAPHICSLIB_REDBLT__

class CPicture;
class CRedBlt
{
public:
	CRedBlt();
	~CRedBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic, BOOL transFlag = TRUE, LPVOID lpPalette = NULL);

private:
	void RedBltTrans256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize, LPVOID lpPalette);
	void RedBltBeta256(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize, LPVOID lpPalette);

	void RedBltTrans(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize);
	void RedBltBeta(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize);

	void MaskRedBlt(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID srcPic,SIZE picSize,char* maskPic);
};


#endif
/*_*/

