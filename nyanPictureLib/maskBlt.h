//
//
//

#if !defined __NYANPICTURELIB_MASKBLT__
#define __NYANPICTURELIB_MASKBLT__


class CMaskBlt
{
public:
	CMaskBlt();
	virtual ~CMaskBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize);

protected:
private:

};



#endif
/*_*/

