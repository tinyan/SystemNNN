//
//
//

#if !defined __NYANPICTURELIB_LIGHTBLT__
#define __NYANPICTURELIB_LIGHTBLT__


class CLightBlt
{
public:
	CLightBlt();
	virtual ~CLightBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID picData,SIZE srcSize,int lightPercent);

protected:
private:

};



#endif
/*_*/

