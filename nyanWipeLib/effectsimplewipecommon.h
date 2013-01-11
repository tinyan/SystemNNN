//
// effectsimplewipecommon.h
//

#if !defined __NYANWIPELIB_COMMON__
#define __NYANWIPELIB_COMMON__

class CPicture;

class CAllSimpleWipe;

class CEffectSimpleWipeCommon
{
public:
	CEffectSimpleWipeCommon(CAllSimpleWipe* allWipe = NULL);
	virtual ~CEffectSimpleWipeCommon();
	virtual void End(void) {}

//	virtual void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL) {}
	virtual void Print(CPicture* lpPicStart, CPicture* lpPicEnd, int count ,int countMax,POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);


protected:
	BOOL ClipAndCheck(CPicture* lpPicStart, CPicture* lpPicEnd, int count,int countMax, POINT* lpStartPoint = NULL, POINT* lpEndPoint = NULL);
	void SetEffectHoukou(int houkou);

	CPicture* m_startPic;
	CPicture* m_endPic;
	POINT m_startPoint;
	POINT m_endPoint;
	int m_countMax;
	int m_count;
	SIZE m_startPicSize;
	SIZE m_endPicSize;

	BOOL m_256OkFlag;

	void SwapPic(void);

	CAllSimpleWipe* m_allSimpleWipe;

	int m_startPitch;
	int m_endPitch;
	LPVOID m_startBuffer;
	LPVOID m_endBuffer;

	int m_effectHoukou;	//0: í èÌ 1:ãtÉpÉ^Å[Éì
};



#endif
/*_*/

