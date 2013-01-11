//
//
//

#if !defined __NYANPICTURELIB_ADDBLT__
#define __NYANPICTURELIB_ADDBLT__


class CAddBlt
{
public:
	CAddBlt();
	virtual ~CAddBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize);

protected:
private:

};



#endif
/*_*/

