//
//
//

#if !defined __NYANPICTURELIB_SHAPEBLT__
#define __NYANPICTURELIB_SHAPEBLT__


class CShapeBlt
{
public:
	CShapeBlt();
	virtual ~CShapeBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID maskData,SIZE srcSize,int r,int g,int b);

protected:
private:

};



#endif
/*_*/

