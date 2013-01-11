//
//
//

#if !defined __NYANWIPELIB_ALLSIMPLEWIPE__
#define __NYANWIPELIB_ALLSIMPLEWIPE__

class CEffectSimpleWipeCommon;
class CAllSimpleWipe
{
public:
	CAllSimpleWipe();
	~CAllSimpleWipe();
	void End(void);

	int* GetShapeWork(void);
	
	int* GetRandomTableX(void);
	int* GetRandomTableY(void);

	void CreateRandomTableX(void);
	void CreateRandomTableY(void);

	CEffectSimpleWipeCommon* GetWipeObject(int n);
	void PrintWipe(int n,CPicture* lpPicStart,CPicture* lpPicEnd,int count,int countMax,POINT* lpStartPoint = NULL,POINT* lpEndPoint = NULL);

	void SetGetBuffer(int* buf){m_getBuffer = buf;}
	int* GetGetBuffer(void){return m_getBuffer;}
private:
	int m_wipeKosuuMax;
	CEffectSimpleWipeCommon** m_wipes;

	int* m_shapeWork;
	int* m_randomTableX2;
	int* m_randomTableY2;

	int* m_getBuffer;
};


#endif
/*_*/

