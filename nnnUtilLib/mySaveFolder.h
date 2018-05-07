#if !defined __NNNUTILLIB_MYSAVEFOLDER__
#define __NNNUTILLIB_MYSAVEFOLDER__


#define MYFOLDER_TYPE_CURRENT 0
#define MYFOLDER_TYPE_MYDOCUMENT 1
#define MYFOLDER_TYPE_PERSONAL 1
#define MYFOLDER_TYPE_APPDATA 2
//#define MYFOLDER_TYPE_COMMON_MYDOCUMENT 3

class CMySaveFolder
{
public:
	CMySaveFolder();
	~CMySaveFolder();
	void End(void);


	static void ChangeMyFolder(LPSTR companyFolder,LPSTR gameFolder,int type = MYFOLDER_TYPE_MYDOCUMENT);
//	static void ChangeMyFolder(LPSTR companyFolder, LPSTR gameFolder, int type = MYFOLDER_TYPE_COMMON_MYDOCUMENT);


	static LPSTR GetUserFolder(void);
	static LPSTR GetCompanyFolder(void);
	static LPSTR GetGameFolder(void);
	static LPSTR GetFullFolder(void);

	static LPSTR GetCompanyName(void){return m_companyName;}
	static LPSTR GetGameName(void){return m_gameName;}
	static LPSTR GetSaveName(void){return m_saveName;}

	static int GetFolderType(void){return m_folderType;}

	static void ChangeFolderType(int type,BOOL remakeFlag = FALSE);

	static void ChangeCompanyFolder(LPSTR companyFolder,BOOL remakeFlag = FALSE);
	static void ChangeGameFolder(LPSTR gameFolder,BOOL remakeFlag = FALSE);
	static void ChangeSaveFolder(LPSTR saveFolder,BOOL remakeFlag = FALSE);

	static int m_folderType;
	static char m_companyName[1024];
	static char m_gameName[1024];
	static char m_saveName[1024];


	static char m_userFolder[1024];
	static char m_companyFolder[1024];
	static char m_gameFolder[1024];
	static char m_fullFolder[1024];

	static BOOL m_createFolderNameFlag;

	static void CreateAllFolderName(void);

	static void SetModify(BOOL flg = TRUE);


	static BOOL CreateSubFolder(void);
	static BOOL DeleteSaveData(BOOL deleteFolderFlag = TRUE,BOOL deleteSubFolderFlag = TRUE,BOOL orgDeleteFlag = FALSE,BOOL deleteSavOnly = FALSE);

	static BOOL DeleteSubFolder(LPSTR subFolder,BOOL deleteSubFolderFlag = TRUE,BOOL orgDeleteFlag = FALSE,BOOL deleteSaveOnly = FALSE,BOOL deleteMyselfFlag = TRUE);

	static BOOL CheckEmptyFolder(LPSTR folder);

private:


};


#endif
/*_*/
