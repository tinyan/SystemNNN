#if !defined __TINYAN_NNNUTILLIB_CUTINMESSAGEWINDOW__
#define __TINYAN_NNNUTILLIB_CUTINMESSAGEWINDOW__


class CCutinMessageWindow
{
public:
	CCutinMessageWindow(LPSTR tagName = NULL,int buffer = 4);
	~CCutinMessageWindow();
	void End(void);
	
	BOOL LoadPic(int n);
	void Print(POINT pt);

	void SetWindowPercent(int ps){m_windowPercent = ps;}
private:
	static char m_defaultTagName[];

	CPicture** m_pic;
	int* m_bufferNumber;
	int m_bufferKosuu;
	int m_nowBufferNumber;
	char m_tagName[256];

	BOOL LoadPicRoutine(int buffer,int n);

	int m_windowPercent;
};

#endif

/*_*/

