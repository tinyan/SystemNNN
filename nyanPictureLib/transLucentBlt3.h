//
//
//

#if !defined __NYANPICTURELIB_TRANSLUCENTBLT3__
#define __NYANPICTURELIB_TRANSLUCENTBLT3__


class CTransLucentBlt3
{
public:
	CTransLucentBlt3();
	virtual ~CTransLucentBlt3();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint, SIZE putSize,LPVOID picData,LPVOID maskData,SIZE srcSize, int transPercent);


protected:
private:

};



#endif
/*_*/

