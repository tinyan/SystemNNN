//
//
//

#if !defined __NYANPICTURELIB_TRANSLUCENTBLT2__
#define __NYANPICTURELIB_TRANSLUCENTBLT2__


class CTransLucentBlt2
{
public:
	CTransLucentBlt2();
	virtual ~CTransLucentBlt2();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int transPercent);


protected:
private:

};



#endif
/*_*/

