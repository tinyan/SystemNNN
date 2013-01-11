#if !defined __GUNKATA_TABLELIST__
#define __GUNKATA_TABLELIST__

class CNameList;
class CTableList
{
public:
	CTableList(LPSTR name,int paraKosuu,BOOL angouFlag = FALSE,BOOL firstUseFlag = FALSE,int work = -1);
	~CTableList();
	void End(void);

	void CreateAtoi(int* lpFlag = NULL);

	int GetParam(int n,int k);
	LPSTR GetName(int n,int k);
	void SetParam(int n,int k,int d,BOOL nameSetFlag = TRUE);

	int GetListKosuu(void);
	int GetListNumber(int n);

	CNameList* GetList(void){return m_list;}

	BOOL CreateUserWork(void);
	int GetUserData(int n,int workNumber = 0);
	void SetUserData(int ,int d,int workNumber = 0);

private:

	CNameList* m_list;
	int* m_table;
	int* m_data;
	int m_kosuu;

	int N2Table(int n);
	int m_tableKosuu;
	int m_paraKosuu;
	int m_min;
	int m_max;
	BOOL m_firstUseFlag;
	BOOL m_createTableFlag;

	int m_userWorkKosuu;
	int* m_userWork[256];

};

#endif

/*_*/

