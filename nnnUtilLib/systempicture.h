//
// systempicture.h
//

#if !defined __NNNUTILLIB_SYSTEMPICTURE__
#define __NNNUTILLIB_SYSTEMPICTURE__

class CPicture;

#define SYSTEM_PICKOSUU_MAX 200
#define SYSTEMPICFILENAME_MAX 64

class CSystemPicture
{
public:
	CSystemPicture();
	~CSystemPicture();
	void End(void);

	CPicture* GetPicture(LPSTR filename,BOOL b256Mode = FALSE);
	static CSystemPicture* m_this;

	static CPicture* GetSystemPicture(LPSTR filename, BOOL b256Mode = FALSE);
	BOOL ExpandWork(int n = 100);
private:
	int m_systemPictureWorkKosuu;

	CPicture** m_ppPic;
	char* m_ppPicName;


//	CPicture* m_pic[SYSTEM_PICKOSUU_MAX];
	int m_picKosuu;
//	char m_picName[SYSTEM_PICKOSUU_MAX][SYSTEMPICFILENAME_MAX];
};



#endif
/*_*/

