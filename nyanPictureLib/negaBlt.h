//
//
//

#if !defined __NYANPICTURELIB_NEGABLT__
#define __NYANPICTURELIB_NEGABLT__


class CNegaBlt
{
public:
	CNegaBlt();
	virtual ~CNegaBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int negaPercent);

protected:
private:

};



#endif
/*_*/

