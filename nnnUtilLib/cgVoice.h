#if !defined __NNNUTILLIB_CGVOICE__
#define __NNNUTILLIB_CGVOICE__

class CNameList;
class CCGVoice
{
public:
	CCGVoice();
	~CCGVoice();
	void End(void);

	LPSTR GetVoice(int playerNumber,int cgNumber);
private:
	CNameList* m_list;
	BOOL m_dataExistFlag;
	int* m_table;
	int* m_playerTable;
	int m_playerTableMax;

};

#endif
/*_*/
