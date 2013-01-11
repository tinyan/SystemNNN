//
//
//

#if !defined __NYANPICTURELIB_TRANSLUCENTBLT0__
#define __NYANPICTURELIB_TRANSLUCENTBLT0__


class CTransLucentBlt0
{
public:
	CTransLucentBlt0();
	virtual ~CTransLucentBlt0();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int transPercent);

protected:
private:

};



#endif
/*_*/

