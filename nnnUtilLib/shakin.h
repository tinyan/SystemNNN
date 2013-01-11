//
//
//


#if !defined __TINYAN_NNNUTILLIB_SHAKIN__
#define __TINYAN_NNNUTILLIB_SHAKIN__


class CShakin
{
public:
	CShakin();
	~CShakin();
	void End(void);

	void SetFrame(int frameTime = 50);
	void SetKikan(int kikan = 10);
	void SetMax(int mx = 3);

	void Clear(void);
	void HensaiFrame(int frame = 1);
	void HensaiTime(int tm);

	void BeginFrame(int tm);	//ms
	void EndFrame(void);

	int GetHensaiFrame(int kaeseru = -1);
	int GetShakinTime(int kaeseru);

//	int Calcu(int tm);	//ms

private:
	int m_max;
	int m_frameTime;
	int m_kikan;

	int m_shakin;
	int m_hensaiYotei;


	BOOL m_hensaiFlag;

};

#endif
/*_*/
