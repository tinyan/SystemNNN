//
// namelist.h
//

#if !defined __NNNUTILLIB_NAMELIST__
#define __NNNUTILLIB_NAMELIST__



class CNameList
{
public:
	CNameList();
	CNameList(int n);
	virtual ~CNameList();

	void End(void);
	BOOL ExpandWork(int n = 100);
	BOOL LoadFile(LPSTR filename,BOOL angouFlag = FALSE,BOOL silent = FALSE,BOOL fullPathFlag = FALSE);
	BOOL SaveFile(LPSTR filename,BOOL angouFlag = FALSE);
	BOOL SaveFile2(LPSTR filename,BOOL angouFlag = FALSE);


	BOOL LoadInit(LPSTR filenameonly);

	int SkipSpace(LPSTR ptr);
	int GetToken(LPSTR ptr);

	int GetNameKosuu(void);
	LPSTR GetName(int n);
	void SetName(int n,LPSTR name);

	int GetNameNumber(LPSTR nam,int skip = 1,int start = 0);

	void AddName(LPSTR name, BOOL bNoCheckFlag = FALSE);
	LPSTR CheckSameNameExist(void);

	int SearchName(LPSTR name, int searchStart = -1, BOOL backSearchFlag = FALSE);
	int SearchName2(LPSTR name, BOOL stricmpFlag = TRUE, int searchStart = -1, BOOL backSearchFlag = FALSE);

	int SearchBlock(LPSTR name,int skip = 2,BOOL stricmpFlag = TRUE,int searchDelta = 0);



	BOOL CheckModify(void);
	void SetModify(BOOL b = TRUE);

	BOOL MoveBlock(int from, int to, int size);

	void SetNameKosuuIsMax(void);

	void AdjustNameKosuu(int kosuu);

	void ChangeNameKosuu(int kosuu);
	void InsertBlock(int n,int kosuu = 1);
	void DeleteBlock(int n,int kosuu = 1);

	static int m_init2ExistFlag;

	void SaveAngouRoutine(LPSTR filename);
protected:
	int m_nameKosuuMax;
	int m_nameKosuu;
	char* m_nameData;
	BOOL m_editFlag;

private:

};

#endif
/*_*/

