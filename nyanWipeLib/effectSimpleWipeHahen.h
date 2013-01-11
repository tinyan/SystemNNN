//
// effectsimplewipeHahen.h
//

#if !defined __NYANWIPELIB_HAHEN__
#define __NYANWIPELIB_HAHEN__

class CPicture;
class CEffect;

class CEffectSimpleWipeCommon;
class CAllSimpleWipe;

class CEffectSimpleWipeHahen : public CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeHahen(CAllSimpleWipe* allWipe,int houkou);
	~CEffectSimpleWipeHahen();
	void End(void);

//	void SetHoukou(int houkou) {m_houkou = houkou;}
	void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count, int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);

	static int m_vertex0[];
	static int m_vertex[];
	static int m_surface[][1+15];	//max 15äpå`


private:
//	int m_houkou;
	int m_para[16];
	typedef struct _tagHAHEN
	{
		float x,y;
		float speedX,speedY;
		float kasokuX,kasokuY;

	}HAHEN;


	int m_poliKosuu;
	int m_centerXY[32*2];
	HAHEN m_hahen[32];

	void PrintNormalPoligon(int* lpPicSrc, int picSizeX, int n, int putX, int putY, int sizeY, int* lpZahyo);

};

#endif
/*_*/
