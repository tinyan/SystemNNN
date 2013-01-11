#if !defined __NNNUTILLIB_SUUJIPAIR__
#define __NNNUTILLIB_SUUJIPAIR__


class CSuuji;
class CSuujiPair
{
public:
	CSuujiPair(CSuuji* suuji,CSuuji* upSuuji = NULL);
	~CSuujiPair();
	void End(void);

	void Print(POINT rightUpPoint,int up,int base,int upColor = 0,int baseColor = -1,int slashFlag=TRUE,int slashColor = -1);

private:
	CSuuji* m_suuji;
	CSuuji* m_upSuuji;

	int m_suujiSizeX;
	int m_suujiNextX;
	int m_upSuujiSizeX;
	int m_upSuujiNextX;


};

#endif
/*_*/


