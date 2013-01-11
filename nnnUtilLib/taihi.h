//
// taihi.h
//

#if !defined __NNNUTILLIB_TAIHI__
#define __NNNUTILLIB_TAIHI__

class CPicture;

class CTaihi
{
public:
	CTaihi();
	~CTaihi();
	void End(void);

	int CreateBuffer(int n, int sizeX, int sizeY);

	BOOL Taihi(int n, int x, int y);
	BOOL Fuque(int n);
	BOOL Flush(int n);
	void AllFuque(void);
	void AllFlush(void);

private:
	CPicture** m_lpTaihi;
	int m_bufferKosuu;
	BOOL* m_lpExistFlag;
	POINT* m_lpZahyo;
	SIZE* m_lpSize;
	SIZE* m_lpBufferSize;


	BOOL SetExist(int n,int x, int y);

	CPicture* GetCPicture(int n);

};


#endif
/*_*/
