//
//
//

#if !defined __NYANPICTURELIB_BLT__
#define __NYANPICTURELIB_BLT__


class CBlt
{
public:
	CBlt();
	virtual ~CBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize);

protected:
private:

};



#endif
/*_*/

