//
//
//

#if !defined __NYANPICTURELIB_YUVCHANGEBLT__
#define __NYANPICTURELIB_YUVCHANGEBLT__


class CYUVChangeBlt
{
public:
	CYUVChangeBlt();
	virtual ~CYUVChangeBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize,BOOL yuvReverseFlag,int betaTransPercent255 = 255);

protected:
//	int m_table256[256];
	int* m_table256;
private:

};



#endif
/*_*/

