//
//
//

#if !defined __NYANPICTURELIB_OVERRAPBLT__
#define __NYANPICTURELIB_OVERRAPBLT__


class COverrapBlt
{
public:
	COverrapBlt();
	virtual ~COverrapBlt();
	void End(void);

	void PrintWithScreen(POINT nextPoint,LPVOID nextPic,SIZE nextPicSize,int startPercent,int endPercent);
	void Print(POINT startPoint,LPVOID startPic,SIZE startPicSize,POINT endPoint,LPVOID endPic,SIZE endPicSize,int startPercent,int endPercent);

protected:
private:

};



#endif
/*_*/

