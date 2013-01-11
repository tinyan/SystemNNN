//
//
//

#if !defined __NNNUTILLIB_ANIMECONTROL__
#define __NNNUTILLIB_ANIMECONTROL__



class CAnimeControl
{
public:
	CAnimeControl();
	~CAnimeControl();
	void End(void);

	void SetParam(int type = 0,int pattern = 1,int speed = 1);
	void Init(int count = 0);
	int Calcu(int cnt = 1);

	int GetAnimePic1(void);
	int GetAnimePic2(void);
	int GetAnimePercent(void);

private:
	int m_animePattern;
	int m_animeSpeed;
	int m_animeType;

	int m_animeCount;

	int m_picPattern1;
	int m_picPattern2;
	int m_picPercent;

};

#endif
/*_*/

