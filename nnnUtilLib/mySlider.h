//
// mySlider.h
//

#if !defined __TINYAN_NNNUTILLIB_MYSLIDER__
#define __TINYAN_NNNUTILLIB_MYSLIDER__

class CPicture;
class CMyMouseStatus;
class CMySlider
{
public:
	CMySlider(CPicture* lpPic, int devide, int printX, int printY, int sizeX, int sizeY, int srcX, int srcY, BOOL transFlag, CPicture* lpBGPic, BOOL tateCutFlag = FALSE);
	~CMySlider();
	void End(void);

	void SetCursor(CPicture* lpPic, int deltaX, int deltaY,int sizeX,int sizeY,BOOL flg = TRUE);
	void SetDevide(int maxData);
	void SetTate(BOOL flg = TRUE){m_tateFlag = flg;}
	void Init(int gaze);
	int Calcu(CMyMouseStatus* lpMouse);
	void Print(BOOL mustPrintFlag = FALSE,BOOL badFlag = FALSE);

	BOOL GetCaptureFlag(void);


private:
	CPicture* m_pic;
	CPicture* m_cursorPic;
	CPicture* m_bgPic;

	int m_devide;
	int m_printX;
	int m_printY;
	int m_sizeX;
	int m_sizeY;
	int m_srcX;
	int m_srcY;
	BOOL m_transFlag;
	BOOL m_tateCutFlag;

	BOOL m_cursorFlag;
	int m_deltaX;
	int m_deltaY;
	int m_cursorSizeX;
	int m_cursorSizeY;

	int m_gaze;
	int m_oldGaze;

	BOOL m_dragFlag;

	void Erase(int printX,int printY,int sizeX,int sizeY);
	BOOL CheckOnGaze(int mouseX,int mouseY);
	int CalcuGaze(int mouseX, int mouseY);

	BOOL m_tateFlag;
};




#endif
/*_*/

