#if !defined ___NNNUTILLIB_POLYGONSHAPE__
#define ___NNNUTILLIB_POLYGONSHAPE__



class CPicture;

class CPolygonShape
{
public:
	CPolygonShape(int sizeX,int sizeY = -1);
	~CPolygonShape();
	void End(void);

	void SetCircleShape(int end,int start = 0,int mx=100);
	void SetRadarShape(int n,int n1,int data1,int data2,int mx = 100);


	void PrintCircleGraph(CPicture* lpPic,int x,int y);
	void PrintCircleGraph(int r,int g,int b,int a,int x,int y);
	void PrintRadar(CPicture* lpPic,int x,int y);
	void PrintRadar(int r,int g,int b,int a,int x,int y);


private:
	int m_sz;
	int* m_work;
	int m_sizeX;
	int m_sizeY;

	int m_type;

	int m_start;
	int m_end;

	int m_n;
	int m_n1;
	//int m_n2;
	int m_data1;
	int m_data2;
	int m_max;

	BOOL Clip(int& srcX,int& srcY,int& dstX,int& dstY, int& sizeX,int& sizeY);

	void PrintPolygon(int r,int g, int b, int a,int x,int y);
	void PrintPic(CPicture* lpPic,int x,int y);

	int m_leftX1;
	int m_leftY1;
	int m_leftX2;
	int m_leftY2;
	int m_rightX1;
	int m_rightY1;
	int m_rightX2;
	int m_rightY2;


	void MakeTable(int baseY,int loop,int leftStart,int rightStart);
	void MakeCircleTableRight(int baseY,int loop,int skp = 0);
	void MakeCircleTableLeft(int baseY,int loop,int skp = 0);

};




#endif
/*_*/


