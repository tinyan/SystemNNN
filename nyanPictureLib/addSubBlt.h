#if !defined __NYANPICTURELIB_ADDSUBBLT__
#define __NYANPICTURELIB_ADDSUBBLT__


class CAddSubBlt
{
public:
	CAddSubBlt();
	virtual ~CAddSubBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,char* maskData,SIZE srcSize,int percent);

protected:
private:

};



#endif
/*_*/

