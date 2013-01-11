//
//
//

#if !defined __NYANPICTURELIB_GRADATIONSHAPEBLT__
#define __NYANPICTURELIB_GRADATIONSHAPEBLT__


class CGradationShapeBlt
{
public:
	CGradationShapeBlt();
	virtual ~CGradationShapeBlt();
	void End(void);

	void Print(POINT putPoint,POINT srcPoint,SIZE putSize,LPVOID maskData,SIZE srcSize,int r1,int g1,int b1,int r2,int g2,int b2);

protected:
private:

};



#endif
/*_*/

