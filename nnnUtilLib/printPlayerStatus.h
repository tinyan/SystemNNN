#pragma once

#if !defined __TINYAN_NNNUTILLIB_PRINTPLAYERSTATUS__
#define __TINYAN_NNNUTILLIB_PRINTPLAYERSTATUS__


class CNameList;
class CPicture;
class CMyMessage;

class CCommonAnimeParts;
class CSuuji;


class CPrintPlayerStatus
{
public:
	CPrintPlayerStatus(CMyMessage* message);
	virtual ~CPrintPlayerStatus();
	void End(void);

	void Init(void);
	void Calcu(int cnt = 1);
	void Print(int setMax, BOOL placeMustPrint, int* onOffParam, int* onOffSet, POINT* placeList, int* etcOnOff, POINT* etcPlaceList);

	int GetSetNumber(void);
	int GetStatusTypeNumber(void);


	void StartRequestVarNumberName(void);
	bool RequestVarNumberName(LPSTR* varname);
	void SetVarNumber(int n, LPSTR varName);

	void StartRequestVarData(void);
	bool RequestVarData(int* varNumber);
	void SetVarData(int data, int varNumber = -1);

	void CheckUseMode(int mode, LPSTR modeName);
	BOOL IsEnable(int mode);


	int GetEtcNumber(void);

protected:
	CMyMessage * m_message;

	CNameList* m_setup;





	int m_varType;
	int m_varParam1;
	int m_varParam2;
	int m_varTypeSet;
	int m_varParam1Set;
	int m_varParam2Set;



	int m_plateSizeX;
	int m_plateSizeY;
	int m_plateTypeNumber;
	typedef struct _tagSTATUSPLATEPARAM
	{
		int numX, numY;
		int nextX, nextY;
		int printX, printY;
	}STATUSPLATEPARAM;

	STATUSPLATEPARAM* m_statusPlateParam;


	typedef struct _tagSTATUSTEXTPARAM
	{
		int printX, printY;
		int fontSize;
		int fontColorR, fontColorG, fontColorB;
		int messageNumber;
		int textType;
		LPSTR* message;
	}STATUSTEXTPARAM;

	STATUSTEXTPARAM* m_statusTextParam;



	typedef struct _tagSTATUSSUUJIPARAM
	{
		int printX, printY;
		CSuuji* suuji;
	}STATUSSUUJIPARAM;
	STATUSSUUJIPARAM* m_statusSuujiParam;

	typedef struct _tagSTATUSBARPARAM
	{
		int basePrintX, basePrintY;
		int printX, printY;
		int sizeX, sizeY;
		CPicture* basePic;
		CPicture* barPic;
	}STATUSBARPARAM;
	STATUSBARPARAM* m_statusBarParam;


	int m_facePrintX;
	int m_facePrintY;



	int m_charaNumber;


	CCommonAnimeParts** m_faceAnimePic;

	int m_textNumber;
	int m_barNumber;
	int m_suujiNumber;


	int* m_generalVarNumber;
	int* m_generalVarData;
	int m_placeVarNumber;
	int m_placeVarData;
	int* m_faceVarNumber;
	int* m_faceVarData;
	int** m_textVarNumber;
	int** m_textVarData;
	int** m_suujiVarNumber;
	int** m_suujiVarData;
	int** m_barVarNumber;//x2
	int** m_barVarData;//x2

	int* m_etcVarNumber;
	int* m_etcVarData;



	int GetPlaceType(void);
	POINT GetBasePoint(int n);
	POINT GetFacePointDelta(void);
	POINT GetTextPointDelta(int n);
	POINT GetSuujiPointDelta(int n);
	POINT GetBarBasePointDelta(int n);
	POINT GetBarPointDelta(int n);


	BOOL CheckPrint(void);


	CPicture* m_platePic;
	CPicture** m_etcPlatePic;
	POINT* m_etcPointDelta;
	CSuuji** m_etcSuuji;


 


	int m_etcNumber;


	int m_useMode[256];



	BOOL GetInitGameParam(int* lpVar, LPSTR name, int initData);
	BOOL GetInitGameParam(int* lpVar, LPSTR name);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name, LPSTR initString);
	BOOL GetInitGameString(LPSTR* lpStr, LPSTR name);
};


#endif
/*_*/
