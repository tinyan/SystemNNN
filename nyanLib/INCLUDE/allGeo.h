//
//
//

#if !defined __NYANGEOLIB_ALLGEO__
#define __NYANGEOLIB_ALLGEO__


class CBoxFill;
class CDaikei;
//class CFade;
//class CFillScreen;
//class CMulti;
class CTransBoxFill;
class CTransCircleFill;
class CTransGradationBoxV;
class CTransTorusFill;
class CAddCircleFill;
class CAddTorusFill;

class CLine;
class CAddBoxFill;

class CAllGeo
{
public:
	CAllGeo();
	virtual ~CAllGeo();
	void End();

	static void BoxFill(int x,int y,int sizeX,int sizeY,int r,int g,int b);
	static void Daikei(POINT leftUpperPoint, int sizeUpperX, POINT leftBottomPoint, int sizeBottomX, int r, int g, int b);
//	static void Fade(int ps1,int r=0,int g=-1,int b=-1,int ps2 = -1);
//	static void FillScreen(int r = 0,int g = -1, int b = -1);
//	static void Multi(int percentR,int percentG = -1,int percentB = -1);
	static void TransBoxFill(int x,int y,int sizeX,int sizeY,int r,int g,int b,int ps);
	static void TransCircleFill(int x, int y, int rx, int ry, int r, int g, int b,int ps);
	static void TransGradationBoxV(POINT leftTop,SIZE size,int r1, int g1, int b1, int r4, int g4, int b4);
	static void TransGradationBoxV(POINT leftTop,POINT rightBottom,int r1, int g1, int b1, int r4, int g4, int b4);
	static void TransTorusFill(int x, int y, int rx, int ry, int x2,int y2,int rx2, int ry2,int r, int g, int b,int ps);
	static void AddCircleFill(int x, int y, int rx, int ry, int dr, int dg, int db,int ps=100);
	static void AddTorusFill(int x, int y, int rx, int ry, int x2,int y2,int rx2, int ry2,int dr, int dg, int db,int ps = 100);
	static void Line(int startX,int startY,int endX,int endY,int r,int g,int b,int ps = 100);
	static void LineF(float startX,float startY,float endX,float endY,int r,int g,int b,int ps = 100);
	static void AddBoxFill(int x,int y,int sizeX,int sizeY,int dr,int dg,int db,int ps = 100);

	void ReCreateAllShader(void);


protected:
	static CBoxFill* m_boxFill;
	static CDaikei* m_daikei;
//	static CFade* m_fade;
//	static CFillScreen* m_fillScreen;
//	static CMulti* m_multi;
	static CTransBoxFill* m_transBoxFill;
	static CTransCircleFill* m_transCircleFill;
	static CTransGradationBoxV* m_transGradationBoxV;
	static CTransTorusFill* m_transTorusFill;
	static CAddCircleFill* m_addCircleFill;
	static CAddTorusFill* m_addTorusFill;
	static CLine* m_line;
	static CAddBoxFill* m_addBoxFill;

private:
};

#endif
/*_*/

