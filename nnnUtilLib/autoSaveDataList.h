#if !defined __NNNUTILLIB_AUTOSAVEDATALIST__
#define __NNNUTILLIB_AUTOSAVEDATALIST__


class CAutoSaveDataList
{
public:
	CAutoSaveDataList();
	~CAutoSaveDataList();
	void End(void);

	int SearchName(LPSTR name);
private:
	static char m_list[][32];
};


#endif
/*_*/

