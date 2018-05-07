#include <windows.h>

//#define _ASAKI_PATCH_DEBUG_


#if defined _ASAKI_PATCH_DEBUG_
#else
//#include <shfolder.h>
#include <shlobj.h>
#endif

#include "mySaveFolder.h"


int CMySaveFolder::m_folderType = 0;

BOOL CMySaveFolder::m_createFolderNameFlag = FALSE;

char CMySaveFolder::m_userFolder[1024] = {0};
char CMySaveFolder::m_companyFolder[1024] = {0};
char CMySaveFolder::m_gameFolder[1024] = {0};
char CMySaveFolder::m_fullFolder[1024] = "sav";

char CMySaveFolder::m_companyName[1024] = {0};
char CMySaveFolder::m_gameName[1024] = {0};
char CMySaveFolder::m_saveName[1024] = "sav";


CMySaveFolder::CMySaveFolder()
{
}


CMySaveFolder::~CMySaveFolder()
{
	End();
}

void CMySaveFolder::End(void)
{
}

void CMySaveFolder::SetModify(BOOL flg)
{
	if (flg)
	{
		m_createFolderNameFlag = FALSE;
	}
}

LPSTR CMySaveFolder::GetUserFolder(void)
{
	CreateAllFolderName();
	return m_userFolder;
}

LPSTR CMySaveFolder::GetCompanyFolder(void)
{
	CreateAllFolderName();
	return m_companyFolder;
}

LPSTR CMySaveFolder::GetGameFolder(void)
{
	CreateAllFolderName();
	return m_gameFolder;
}

LPSTR CMySaveFolder::GetFullFolder(void)
{
	CreateAllFolderName();
	return m_fullFolder;
}


void CMySaveFolder::ChangeMyFolder(LPSTR companyFolder,LPSTR gameFolder,int type)
{
	if (type == MYFOLDER_TYPE_CURRENT)
	{
		ChangeFolderType(type);
		ChangeCompanyFolder(NULL);
		ChangeGameFolder(NULL);
	}
	else
	{
		ChangeFolderType(type);
		ChangeCompanyFolder(companyFolder);
		ChangeGameFolder(gameFolder);
	}

	SetModify();
	CreateAllFolderName();
}

void CMySaveFolder::ChangeFolderType(int type,BOOL remakeFlag)
{
	m_folderType = type;
	SetModify();

#if defined _ASAKI_PATCH_DEBUG_
		m_userFolder[0] = 0;
#else

	char szPath[_MAX_PATH];
	LPITEMIDLIST pidl;
	HWND hWnd = NULL;

	IMalloc *pMalloc;

	if (m_folderType == MYFOLDER_TYPE_CURRENT)
	{
		m_userFolder[0] = 0;
	}
	else
	{
	    SHGetMalloc( &pMalloc );



		BOOL flg = FALSE;
		if (m_folderType == MYFOLDER_TYPE_MYDOCUMENT)
		{
			
		   if( SUCCEEDED(SHGetSpecialFolderLocation(hWnd,CSIDL_PERSONAL,&pidl)))
		   {
			   flg = TRUE;
		   }
		}
		else if (SUCCEEDED(SHGetSpecialFolderLocation(hWnd,CSIDL_APPDATA,&pidl)))
		{
			flg = TRUE;
		}

		if (flg)
		{
	        SHGetPathFromIDList(pidl,szPath); // パスに変換する
		    pMalloc->Free(pidl);              // 取得したIDLを解放する (CoTaskMemFreeでも可)

			int ln = strlen(szPath);
			if (ln>1022) ln = 1022;

			memcpy(m_userFolder,szPath,ln);
			m_userFolder[ln] = 0;
			m_userFolder[ln+1] = 0;
		}
		pMalloc->Release();
	}
#endif
//	else if (m_folderType == MYFOLDER_TYPE_MYDOCUMENT)
//	{
//		SHGetFolderPath(NULL,CSIDL_PERSONAL ,NULL,0,m_userFolder);
//	}
//	else if (m_folderType == MYFOLDER_TYPE_APPDATA)
//	{
//		SHGetFolderPath(NULL,CSIDL_APPDATA ,NULL,0,m_userFolder);
//	}



	if (remakeFlag)
	{
		CreateAllFolderName();
	}
}

void CMySaveFolder::ChangeCompanyFolder(LPSTR companyFolder,BOOL remakeFlag)
{
	if (companyFolder == NULL)
	{
		m_companyName[0] = 0;
	}
	else
	{
		int ln = strlen(companyFolder);
		if (ln>126) ln = 126;
		memcpy(m_companyName,companyFolder,ln+1);
		m_companyName[ln+1] = 0;
	}
	
	SetModify();
	
	if (remakeFlag)
	{
		CreateAllFolderName();
	}
}

void CMySaveFolder::ChangeGameFolder(LPSTR gameFolder,BOOL remakeFlag)
{
	if (gameFolder == NULL)
	{
		m_gameName[0] = 0;
	}
	else
	{
		int ln = strlen(gameFolder);
		if (ln>254) ln = 254;
		memcpy(m_gameName,gameFolder,ln+1);
		m_gameName[ln+1] = 0;
	}
	
	SetModify();
	
	if (remakeFlag)
	{
		CreateAllFolderName();
	}
}

void CMySaveFolder::ChangeSaveFolder(LPSTR saveFolder,BOOL remakeFlag)
{
	if (saveFolder == NULL)
	{
		m_saveName[0] = 0;
	}
	else
	{
		int ln = strlen(saveFolder);
		if (ln>126) ln = 126;
		memcpy(m_saveName,saveFolder,ln+1);
		m_saveName[ln+1] = 0;
	}
	
	SetModify();
	
	if (remakeFlag)
	{
		CreateAllFolderName();
	}
}


void CMySaveFolder::CreateAllFolderName(void)
{
	if (m_createFolderNameFlag) return;


	if (m_companyName[0] == 0)
	{
		wsprintf(m_companyFolder,"%s",m_userFolder);
	}
	else
	{
		if (m_userFolder[0] == 0)
		{
			wsprintf(m_companyFolder,"%s",m_companyName);
		}
		else
		{
			wsprintf(m_companyFolder,"%s\\%s",m_userFolder,m_companyName);
		}
	}

	if (m_gameName[0] == 0)
	{
		wsprintf(m_gameFolder,"%s",m_companyFolder);
	}
	else
	{
		if (m_companyFolder[0] == 0)
		{
			wsprintf(m_gameFolder,"%s",m_gameName);
		}
		else
		{
			wsprintf(m_gameFolder,"%s\\%s",m_companyFolder,m_gameName);
		}
	}

	if (m_saveName[0] == 0)
	{
		wsprintf(m_fullFolder,"%s",m_gameFolder);
	}
	else
	{
		if (m_gameFolder[0] == 0)
		{
			wsprintf(m_fullFolder,"%s",m_saveName);
		}
		else
		{
			wsprintf(m_fullFolder,"%s\\%s",m_gameFolder,m_saveName);
		}
	}

	m_createFolderNameFlag = TRUE;
}


BOOL CMySaveFolder::CreateSubFolder(void)
{
	if (m_companyName[0] != 0)
	{
		LPSTR dirName = GetCompanyFolder();
		if (dirName == NULL) return FALSE;

		if (CreateDirectory(dirName,NULL) == FALSE)
		{
			int er = GetLastError();
			if (er != ERROR_ALREADY_EXISTS)
			{
				return FALSE;
			}
		}
	}


	if (m_gameName[0] != 0)
	{
		LPSTR dirName = GetGameFolder();
		if (dirName == NULL) return FALSE;

		if (CreateDirectory(dirName,NULL) == FALSE)
		{
			int er = GetLastError();
			if (er != ERROR_ALREADY_EXISTS)
			{
				return FALSE;
			}
		}
	}

	if (m_saveName[0] != 0)
	{
		LPSTR dirName = GetFullFolder();
		if (dirName == NULL) return FALSE;

		if (CreateDirectory(dirName,NULL) == FALSE)
		{
			int er = GetLastError();
			if (er != ERROR_ALREADY_EXISTS)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL CMySaveFolder::DeleteSaveData(BOOL deleteFolderFlag,BOOL deleteSubFolderFlag,BOOL orgDeleteFlag,BOOL deleteSaveOnly)
{

	//first delete save / *.* without *.org
	int cnt = 0;

	if (1)
	{
		LPSTR folder = GetFullFolder();
		BOOL rt = DeleteSubFolder(folder,deleteSubFolderFlag,orgDeleteFlag,deleteSaveOnly,FALSE);
		if (rt == FALSE)
		{
			return FALSE;
		}
	}


char debugMessage[1024];

	//if empty and name[0] != 0
	//user/company/game/sav
	//user/company/game
	//user/company
	if (deleteFolderFlag)
	{
		BOOL empty = TRUE;

		if (empty)
		{
			if (m_saveName[0] != 0)
			{
				LPSTR folder = GetFullFolder();
				if (folder != NULL)
				{
					empty = CheckEmptyFolder(folder);
					if (empty)
					{
						if (RemoveDirectory(folder))
						{
wsprintf(debugMessage,"\n削除したフォルダ:%s\n",folder);
OutputDebugString(debugMessage);
						}
						else
						{
							empty = FALSE;
						}
					}
				}
			}
		}

		if (empty)
		{
			if (m_gameName[0] != 0)
			{
				LPSTR folder = GetGameFolder();
				if (folder != NULL)
				{
					empty = CheckEmptyFolder(folder);
					if (empty)
					{
						if (RemoveDirectory(folder))
						{
wsprintf(debugMessage,"\n削除したフォルダ:%s\n",folder);
OutputDebugString(debugMessage);

						}
						else
						{
							empty = FALSE;
						}
					}
				}
			}
		}

		if (empty)
		{
			if (m_companyName[0] != 0)
			{
				LPSTR folder = GetCompanyFolder();
				if (folder != NULL)
				{
					empty = CheckEmptyFolder(folder);
					if (empty)
					{
						if (RemoveDirectory(folder))
						{
wsprintf(debugMessage,"\n削除したフォルダ:%s\n",folder);
OutputDebugString(debugMessage);
						}
						else
						{
							empty = FALSE;
						}
					}
				}
			}
		}
	}

	return TRUE;
}


BOOL CMySaveFolder::DeleteSubFolder(LPSTR subFolder,BOOL deleteSubFolderFlag,BOOL orgDeleteFlag,BOOL deleteSaveOnly,BOOL deleteMyselfFlag)
{
	//first delete save / *.* without *.org
	int cnt = 0;

	if (1)
	{
		WIN32_FIND_DATA finddata;
		char searchName[1024];
		LPSTR folder = subFolder;

//		if (deleteSaveOnly)
//		{
//			wsprintf(searchName,"%s\\*.sav",folder);
//		}
//		else
//		{
//			wsprintf(searchName,"%s\\*.*",folder);
//		}


		wsprintf(searchName,"%s\\*.*",folder);


		HANDLE hFind = FindFirstFile(searchName,&finddata);
//		if (hFind == INVALID_HANDLE_VALUE)
//		{
//			second = 1;
//			wsprintf(searchName,"%s\\*",folder);
//			hFind = FindFirstFile(searchName,&finddata);
//		}

		if (hFind != INVALID_HANDLE_VALUE)
		{
			while (TRUE)
			{
				BOOL delok = FALSE;

				if (finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{

					delok = TRUE;
					LPSTR filename = finddata.cFileName;
					if (strcmp(filename,".") == 0)
					{
						delok = FALSE;
					}
					if (strcmp(filename,"..") == 0)
					{
						delok = FALSE;
					}


					if (deleteSubFolderFlag && delok)
					{
						char subSubFolderName[1024];
						wsprintf(subSubFolderName,"%s\\%s",subFolder,finddata.cFileName);

						BOOL rt = DeleteSubFolder(subSubFolderName,deleteSubFolderFlag,orgDeleteFlag,deleteSaveOnly);
						if (rt == FALSE)
						{
							break;
						}

						FindClose(hFind);
						hFind = FindFirstFile(searchName,&finddata);
						if (hFind == INVALID_HANDLE_VALUE)
						{
							break;
						}
					}
					else
					{
						if (FindNextFile(hFind,&finddata) == FALSE)
						{
							break;
						}
					}
				}
				else
				{
					LPSTR filename = finddata.cFileName;
					int ln = strlen(filename);

					delok = TRUE;

					if (orgDeleteFlag == FALSE)
					{
						if (ln >= 4)
						{
							char check[6];
							memcpy(check,filename+ln-4,4);
							check[4] = 0;
							check[5] = 0;
							if (_stricmp(check,".org") == 0)
							{
								delok = FALSE;
							}
						}
					}


					if (delok)
					{
						if (deleteSaveOnly)
						{
							if (ln >= 4)
							{
								char check[6];
								memcpy(check,filename+ln-4,4);
								check[4] = 0;
								check[5] = 0;
								if (_stricmp(check,".sav") != 0)
								{
									delok = FALSE;
								}
							}
						}
					}

					if (delok)
					{
						char deleteFileName[1024];
						wsprintf(deleteFileName,"%s\\%s",subFolder,filename);
						if (DeleteFile(deleteFileName))
						{
							cnt++;

							FindClose(hFind);

							hFind = FindFirstFile(searchName,&finddata);
							if (hFind == INVALID_HANDLE_VALUE)
							{
								break;
							}
						}
						else
						{
							//error!
							FindClose(hFind);
							hFind = INVALID_HANDLE_VALUE;
							MessageBox(NULL,filename,"削除エラー",MB_ICONEXCLAMATION | MB_OK);
							return FALSE;
//							break;
						}
					}
					else
					{
						if (FindNextFile(hFind,&finddata) == FALSE)
						{
							break;
						}
					}

				}
			}

			if (hFind != INVALID_HANDLE_VALUE)
			{
				FindClose(hFind);
			}
		}
	}


char debugMessage[1024];
wsprintf(debugMessage,"\n削除したファイル%d個\n",cnt);
OutputDebugString(debugMessage);


	if (deleteMyselfFlag)
	{
		if (RemoveDirectory(subFolder))
		{
wsprintf(debugMessage,"\n削除したフォルダ:%s\n",subFolder);
OutputDebugString(debugMessage);
		}
		else
		{
			return FALSE;
		}

	}
	return TRUE;
}


BOOL CMySaveFolder::CheckEmptyFolder(LPSTR folder)
{
	WIN32_FIND_DATA finddata;
	char searchName[1024];
	wsprintf(searchName,"%s\\*",folder);
	
	HANDLE hFind = FindFirstFile(searchName,&finddata);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return TRUE;
	}

	while (TRUE)
	{
		if (finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

			BOOL current = FALSE;

			LPSTR filename = finddata.cFileName;

			if (strcmp(filename,".") == 0)
			{
				current = TRUE;
			}
			if (strcmp(filename,"..") == 0)
			{
				current = TRUE;
			}

			if (current == FALSE)
			{
				FindClose(hFind);
				return FALSE;
			}

			if (FindNextFile(hFind,&finddata) == FALSE)
			{
				FindClose(hFind);
				return TRUE;
			}
		}
		else
		{
			return FALSE;
		}
	}

	return FALSE;
}



/*_*/



