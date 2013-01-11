#if !defined __NNNUTILLIB_CGDATACONTROL__
#define __NNNUTILLIB_CGDATACONTROL__

class CCommonSystemFile;
class CNameList;

class CCGDataControl
{
public:
	CCGDataControl(CCommonSystemFile* systemFile);
	~CCGDataControl();
	void End(void);

	void CreateCGList(int kosuu);
	LPSTR GetCGFileName(int cgCharaNumber, int cgNumber, BOOL realnameFlag = TRUE);
	int GetCGScrollSpecial(int houkou, int charaNumber, int cgNumber);

	int GetCGKosuu(int playerNumber);
	int GetTotalCGPercent(void);
	int GetCGPercent(int cgCharaNumber);
	BOOL CheckGetCG(int player, int num);
	int SearchNextCG(void);
	int SearchPreCG(void);

	int GetCGCharaKosuu(void){return m_cgCharaKosuu;}
	void SetCGCharaNumber(int cgChara) {m_cgCharaNumber = cgChara;}
	int GetCGCharaNumber(void) {return m_cgCharaNumber;}
	
	int GetCGNumber(void) {return m_cgNumber;}
	void SetCGNumber(int cgNumber) {m_cgNumber = cgNumber;}

private:
	CCommonSystemFile* m_systemFile;
	CNameList** m_cgList;
	int m_cgCharaKosuu;
	int* m_cgKosuu;

	int m_cgNumber;
	int m_cgCharaNumber;

};

#endif
/*_*/

