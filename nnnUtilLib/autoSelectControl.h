#if !defined __TINYAN_NNNUTILLIB_AUTOSELECTCONTROL__
#define __TINYAN_NNNUTILLIB_AUTOSELECTCONTROL__


class CAutoSelectControl
{
public:
	CAutoSelectControl();
	~CAutoSelectControl();
	void End(void);

	void ClearPlayLevel(void);
	int GetSelect(int selectNumber);
	
	
	
	
	void Finish(void);

//	int GetPlayLevel(void){return m_playLevel;}
//	int GetLevel(void){return m_level;}





	BOOL CheckAllEnd(void){return m_allEnd;}
private:
	int m_levelMax;
	int m_playLevel;
	int m_level;
	BOOL m_allEnd;

	int* m_selectNumber;
	int* m_selected;


};

#endif
/*_*/
