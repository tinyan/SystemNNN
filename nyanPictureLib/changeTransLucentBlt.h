//
//
//

#if !defined __NYANPICTURELIB_CHANGETRANSLUCENTBLT__
#define __NYANPICTURELIB_CHANGETRANSLUCENTBLT__


class CChangeTransLucentBlt
{
public:
	CChangeTransLucentBlt();
	virtual ~CChangeTransLucentBlt();
	void End(void);

//	void Print(POINT dstPoint,POINT srcPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID maskData1,LPVOID maskData2,SIZE picSize,int ps1,int ps2);
	void Print(POINT dstPoint,SIZE putSize,LPVOID picData1,LPVOID picData2,LPVOID maskData1,LPVOID maskData2,SIZE picSize,SIZE picSize2,int ps1,int ps2);

protected:
private:

};



#endif
/*_*/

