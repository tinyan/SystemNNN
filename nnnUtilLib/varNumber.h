//
// varNumber.h
//

#if !defined __NNNUTILLIB_VARNUMBER__
#define __NNNUTILLIB_VARNUMBER__

class CNameList;

class CVarNumber
{
public:
	CVarNumber(CNameList* varList);
	~CVarNumber();
	void End(void);

	int GetVarNumber(LPSTR name);
private:
	CNameList* m_varList;
	int m_kosuu;

	void PrintMyError(LPSTR name);
};


#endif
/*_*/
