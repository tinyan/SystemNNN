//
//
//

#if !defined __NYANPICTURELIB_TRANSLUCENTBLT__
#define __NYANPICTURELIB_TRANSLUCENTBLT__


class CTransLucentBlt
{
public:
	CTransLucentBlt();
	virtual ~CTransLucentBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int transPercent);

protected:
private:

};



#endif
/*_*/

