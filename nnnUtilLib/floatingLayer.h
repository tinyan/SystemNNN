//
// floatingLayer.h
//

#if !defined __NNNUTILLIB_FLOATINGLAYER__
#define __NNNUTILLIB_FLOATINGLAYER__


//class CNameList;
class CSetupList;

class CTaihi;


class CFloatingLayer
{
public:
	CFloatingLayer(CTaihi* lpTaihi, int layerNumber, int layerKosuu = 1);
	virtual ~CFloatingLayer();
	virtual void End(void);

	virtual void Taihi(int x, int y, int subNumber = 0);

	virtual void CreateLayer(int sizeX = 64, int sizeY = 64, int subNumber = 0);
	virtual void ChangeLayerKosuu(int kosuu);
	
protected:
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);
	BOOL LoadSetupFile(LPSTR filenameonly, int varKosuu = 64);

//	CNameList* m_setup;
	CSetupList* m_setup;


	CTaihi* m_taihi;
	int m_layerNumber;
	int m_layerKosuu;

	int* m_pSizeX;
	int* m_pSizeY;
private:

};

#endif
/*_*/

