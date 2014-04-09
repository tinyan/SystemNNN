#if !defined __NNNUTILLIB_VIEWCONTROL__
#define __NNNUTILLIB_VIEWCONTROL__

class CViewControl
{
public:
	CViewControl();
	~CViewControl();
	void End(void);

	void SetBufferSize(int sizeX,int sizeY);
	void SetRealWindowSize(int sizeX,int sizeY);
	void SetStretchFlag(BOOL flag);
	void CalcuParam(void);


	int GetRealWindowSizeX(void){return m_realWindowSizeX;}
	int GetRealWindowSizeY(void){return m_realWindowSizeY;}
	int GetBackBufferOffsetX(void){return m_backBufferOffsetX;}
	int GetBackBufferOffsetY(void){return m_backBufferOffsetY;}
	int GetViewOffsetX(void){return m_viewOffsetX;}
	int GetViewOffsetY(void){return m_viewOffsetY;}
	int GetViewSizeX(void){return m_viewSizeX;}
	int GetViewSizeY(void){return m_viewSizeY;}
	POINT WindowToGame(int windowMouseX,int windowMouseY);
	RECT GetSrcRect(int x,int y,int sizeX,int sizeY);
	RECT GetDstRect(int x,int y,int sizeX,int sizeY);

	POINT GameToView(POINT pt);
	SIZE GetAspectFitSize(void);

private:
	int m_bufferSizeX;
	int m_bufferSizeY;
	int m_backBufferOffsetX;
	int m_backBufferOffsetY;

	int m_realWindowSizeX;
	int m_realWindowSizeY;
	int m_viewOffsetX;
	int m_viewOffsetY;
	BOOL m_stretchFlag;
	int m_viewSizeX;
	int m_viewSizeY;
};


#endif
/*_*/

