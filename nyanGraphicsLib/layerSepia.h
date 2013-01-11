//
// multi.h
//

#if !defined __NYANGRAPHICSLIB_LAYERSEPIA__
#define __NYANGRAPHICSLIB_LAYERSEPIA__



class CLayerSepia
{
public:
	CLayerSepia();
	virtual ~CLayerSepia();
	void End(void);

	virtual void Print(int ps256, int r,int g,int b);
protected:
};






#endif
/*_*/

