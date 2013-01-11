//
//
//

#if !defined __NNNUTILLIB_NAMECOLOR__
#define __NNNUTILLIB_NAMECOLOR__

class CNameList;

class CNameColor
{
public:
	CNameColor();
	~CNameColor();
	void End(void);

	BOOL Load(LPSTR filename);
	int GetNameKosuu(void) {return m_nameKosuu;}
	int SearchName(LPSTR name);
	int GetColor(int number);
	int GetColor(LPSTR name);

private:
	CNameList* m_nameList;
	int m_nameKosuu;
	int* m_colorTable;
};

#endif
/*_*/
