#if !defined __NNNUTILLIB_SAIJITSULIST__
#define __NNNUTILLIB_SAIJITSULIST__

class CSaijitsuList
{
public:
	CSaijitsuList();
	~CSaijitsuList();
	void End(void);

	int CheckSaijitsu(int year,int month,int day);

private:
	CNameList* m_list;
	int m_listKosuu;
	int* m_data;

};


#endif
/*_*/
