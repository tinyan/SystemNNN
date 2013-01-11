//
// calcuSpeed.h
//

#if !defined __NYANEFFECTLIB_CALCUSPEED__
#define __NYANEFFECTLIB_CALCUSPEED__

class CCalcuSpeed
{
public:
	CCalcuSpeed();
	~CCalcuSpeed();
	void End(void);

	static int calcu(int count, int countMax, int startData = 0, int endData = 100, int delayCount = 0, int speedType = 0, int kasokuType = 0);

private:
};

#endif
/*_*/

