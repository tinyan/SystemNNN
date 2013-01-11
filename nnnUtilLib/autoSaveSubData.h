#if !defined __NNNUTILLIB_AUTOSAVESUBDATA__
#define __NNNUTILLIB_AUTOSAVESUBDATA__


class CAutoSaveSubData
{
public:
	CAutoSaveSubData(int size = 1024);
	virtual ~CAutoSaveSubData();
	virtual void End(void);

	void SetDataSize(int size){m_dataSize = size;}
	int GetDataSize(void){return m_dataSize;}

	virtual void GetExtDataForSave(LPVOID ptr,int extNumber = 0) {};
	virtual void SetExtDataByLoad(LPVOID ptr,int extNumber = 0) {};

protected:
	int m_dataSize;

};


#endif
/*_*/


