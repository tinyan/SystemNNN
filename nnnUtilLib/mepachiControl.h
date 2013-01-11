//
//
//

#if !defined __NNNUTILLIB_MEPACHICONTROL__
#define __NNNUTILLIB_MEPACHICONTROL__


class CEffect;
class CNameList;

class CMepachiControl
{
public:
	CMepachiControl(CEffect* lpEffect);
	~CMepachiControl();
	void End(void);

	static char m_defaultMeFileName[];
	static char m_defaultMeCharaName[];
	static char m_defaultKuchiFileName[];
	static char m_defaultKuchiCharaName[];

private:
	CEffect* m_effect;
	CNameList* m_mepachiList;

	int m_meKosuu;
	int m_kuchiKosuu;

	int m_fileNameKosuu;

	LPSTR* m_meNameTable;
	int* m_meTable;
	LPSTR* m_meCharaNameTable;
	
	LPSTR* m_kuchiNameTable;
	int* m_kuchiTable;
	LPSTR* m_kuchiCharaNameTable;

	LPSTR* m_fileNameTable;
	int* m_mekuchiTable;
	int InitMeTable(int me,int n);
	int InitKuchiTable(int kuchi,int n);

	void CheckAndAddFileName(LPSTR name,int me,int kuchi);
	int SearchFileName(LPSTR name);
};


#endif
/*_*/

