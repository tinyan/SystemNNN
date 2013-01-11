//
// gameMouse.h
//

#if !defined __NNNUTILLIB_NOTICE__
#define __NNNUTILLIB_NOTICE__


class CPicture;
class CFloatingLayer;
class CSetupList;
class CAnimeControl;

class CNotice : public CFloatingLayer
{
public:
	CNotice(CTaihi* lpTaihi, int taihiLayer = 20);
	virtual ~CNotice();
	virtual void End(void);

	virtual void Start(int n = 0);
	virtual void Clear(void);
//	virtual void Calcu(int count = 1);
	virtual int Print(BOOL taihiFlag = TRUE);

	static char m_defaultNoticePicFileName[];
	static char m_soundTypeName[][32];

protected:
	int m_noticeKosuu;
	POINT* m_startZahyo;
	POINT* m_waitZahyo;
	POINT* m_endZahyo;
	int* m_startTime;
	int* m_waitTime;
	int* m_endTime;
	int* m_startPercent;
	int* m_waitPercent;
	int* m_endPercent;
	int* m_sound;

	int m_count;
//	int m_number;
	int m_printMode;

	int m_sizeX;
	int m_sizeY;

	CPicture* m_pic;
	LPSTR m_filenameTag;

	int m_seatNumber;
	int m_blockX;
	int m_blockY;

	int* m_buffer;
	int m_bufferMax;
	int m_bufferKosuu;

	CSetupList* m_setup;
	int m_sameDontSetFlag;

private:
	void NewPic(void);
	void DecBuffer(void);


};



#endif
/*_*/
