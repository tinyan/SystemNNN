#if !defined __NNNUTILLIB_CALCUWEEK__
#define __NNNUTILLIB_CALCUWEEK__


class CCalcuWeek
{
public:
	CCalcuWeek();
	~CCalcuWeek();
	void End(void);

	static int CalcuWeek(int date);
	static int CalcuWeek(int month,int day);
	static int CalcuWeek(int year,int month,int day,BOOL year0is2000 = TRUE);

private:
};
#endif
/*_*/

