#include <windows.h>
#include <stdio.h>

#include "..\..\systemNNN\nyanLib\include\commonMacro.h"
#include "nameList.h"
#include "Myfont.h"

#include "commonSystemFile.h"
#include "CGDataControl.h"

CCGDataControl::CCGDataControl(CCommonSystemFile* systemFile)
{
	m_systemFile = systemFile;

	m_cgCharaKosuu = 0;
	m_cgKosuu = NULL;
	m_cgList = NULL;

	m_animeTable = NULL;

	m_cgNumber = 0;
	m_cgCharaNumber = 0;

	int cgCharaKosuu = CCommonSystemFile::GetCGCharaNinzu();
	if (cgCharaKosuu > 0) CreateCGList(cgCharaKosuu);
}


CCGDataControl::~CCGDataControl()
{
	End();
}

void CCGDataControl::End(void)
{
	if (m_animeTable != NULL)
	{
		for (int i=0;i<m_cgCharaKosuu;i++)
		{
			DELETEARRAY(m_animeTable[i]);
		}
		DELETEARRAY(m_animeTable);
		m_animeTable = NULL;
	}


	if (m_cgList != NULL)
	{
		for (int i=0;i<m_cgCharaKosuu;i++)
		{
			ENDDELETECLASS(m_cgList[i]);
		}
	}
	DELETEARRAY(m_cgList);

	DELETEARRAY(m_cgKosuu);
}




void CCGDataControl::CreateCGList(int kosuu)
{
	if (m_cgCharaKosuu != 0) return;

	m_cgCharaKosuu = kosuu;

	m_cgKosuu = new int[m_cgCharaKosuu];
	m_cgList = new CNameList*[m_cgCharaKosuu];
	for (int i=0;i<m_cgCharaKosuu;i++)
	{
		m_cgList[i] = new CNameList();
		char cgname[32];
		wsprintf(cgname,"spt\\cglist%d%d.xtx",(i+1) / 10,(i+1) % 10);
		m_cgList[i]->LoadFile(cgname);
		m_cgKosuu[i] = m_cgList[i]->GetNameKosuu();
	}

	m_animeTable = new int*[m_cgCharaKosuu];
	for (int i=0;i<m_cgCharaKosuu;i++)
	{
		m_animeTable[i] = new int[m_cgKosuu[i]*2+1];
		for (int k=0;k<m_cgKosuu[i]*2;k++)
		{
			m_animeTable[i][k]=-1;
		}
	}
}


LPSTR CCGDataControl::GetCGFileName(int player, int cg,BOOL realnameFlag)
{
	if ((player<0) || (player>=m_cgCharaKosuu)) return NULL;
	LPSTR name = m_cgList[player]->GetName(cg);

	if (realnameFlag)
	{
		if ((*name) == '@') name++;
		if ((*name) == '!') name++;
		if ((*name) == '#')
		{
			name++;
			int lna = (int)strlen(name);
			while (lna>0)
			{
				char c = *name;
				if (c == '/')
				{
					name++;
					break;
				}
				name++;
				lna--;
			}
		}


		int ln = (int)strlen(name);
		if (ln > 0)
		{
			if ((*name) == '[')
			{
				name++;
				ln--;

				while(ln>0)
				{
					if ((*name) == ']')
					{
						name++;
						ln--;
						break;
					}

					int d = (int)(*name);
					d &= 0xff;

					if (((*name) >= '0') && ((*name) <= '9'))
					{
						name+=1;
						ln -= 1;
					}
					else if (((d >= 0x80) && (d < 0xa0)) || ((d >= 0xe0) && (d < 0x100)))
//					else if ((*name) & 0x80)
					{
						name += 2;
						ln -= 2;
					}
					else
					{
						name+=1;
						ln -= 1;
					}
				}
			}
		}
	}

	return name;
}

BOOL CCGDataControl::CheckCGIsAnime(int player,int num)
{
	if ((player<0) || (player>=m_cgCharaKosuu)) return FALSE;
	int cgKosuu = GetCGKosuu(player);
	if ((num<0) || (num>=cgKosuu)) return FALSE;
	int maisuu = m_animeTable[player][num*2+1];
	if (maisuu == 0) return FALSE;
	if (maisuu > 0) return TRUE;

	return GetAnimeParam(player,num);
}

int CCGDataControl::GetAnimeStart(int player,int num)
{
	if (CheckCGIsAnime(player,num))
	{
		return m_animeTable[player][num*2];
	}

	return 0;//error
}

int CCGDataControl::GetAnimeMaisuu(int player,int num)
{
	if (CheckCGIsAnime(player,num))
	{
		return m_animeTable[player][num*2+1];
	}

	return 1;//error
}

BOOL CCGDataControl::GetAnimeParam(int player,int num)
{
	LPSTR name = m_cgList[player]->GetName(num);
	int animeStart = 0;
	int animeMaisuu = 0;

	if (1)
	{
		if ((*name) == '@') name++;
		if ((*name) == '!') name++;
		if ((*name) == '#')
		{
			name++;

			int lna = (int)strlen(name);
			int moji = 0;
			char suuji[256];
			char suuji2[256];
			suuji[0] = '0';
			suuji[1] = 0;
			suuji2[0] = '1';
			suuji2[1] = 0;

			while (lna>0)
			{
				char c = *name;
				name++;
				lna--;
				if ((c <'0') || (c>'9'))
				{
					break;
				}
				suuji[moji]=c;
				moji++;
			}
			suuji[moji] = 0;

			int moji2 = 0;
			while (lna>0)
			{
				char c = *name;
				name++;
				lna--;
				if ((c <'0') || (c>'9'))
				{
					break;
				}
				suuji2[moji2]=c;
				moji2++;
			}
			suuji2[moji2] = 0;

			animeStart = atoi(suuji);
			animeMaisuu = atoi(suuji2);

		}
	}

	m_animeTable[player][num*2] = animeStart;
	m_animeTable[player][num*2+1] = animeMaisuu;

	if (animeMaisuu > 0) return TRUE;

	return FALSE;
}


int CCGDataControl::GetCGScrollSpecial(int houkou, int charaNumber, int cgNumber)
{
	int houkouX = -1;
	int houkouY = -1;

	int lastHoukou = -1;

	LPSTR name = GetCGFileName(charaNumber,cgNumber,FALSE);
	if ((*name) == '@') name++;
	if ((*name) == '!') name++;

	int maisuuX = 1;
	int maisuuY = 1;

	int waitX = -1;
	int waitY = -1;
	int speedX = -1;
	int speedY = -1;

	int lastSubCommand = -1;

	int codeByte = CMyFont::m_codeByte;



	int ln = (int)strlen(name);
	if (ln > 0)
	{
		int upArrow = 'Å™';
		int downArrow = 'Å´';
		int leftArrow = 'Å©';
		int rightArrow = 'Å®';

		char upArrow1Byte = '^';
		char downArrow1Byte = '|';
		char leftArrow1Byte = '<';
		char rightArrow1Byte = '>';


		if ((*name) == '[')
		{
			name++;
			ln--;
			if (ln>0)
			{
				while (ln > 0)
				{
					if ((*name) == ']')
					{
						name++;
						ln--;
						break;
					}

					if ((*name) == ':')
					{
						name++;
						ln--;
						lastSubCommand = 1;
					}

					if ((*name) == '_')
					{
						name++;
						ln--;
						lastSubCommand = 2;
					}

					if (((*name) >= '0') && ((*name) <= '9'))
					{
						char suuji[256];
						int suujilen = 0;
						while (((*name) >= '0') && ((*name) <= '9') && (ln>0))
						{
							suuji[suujilen] = *name;
							suuji[suujilen+1] = 0;
							suujilen++;
							ln--;
							name++;
						}

						if (lastSubCommand == 0)
						{
							if ((lastHoukou == 0) || (lastHoukou == 1))
							{
								maisuuY = atoi(suuji);
							}

							if ((lastHoukou == 2) || (lastHoukou == 3))
							{
								maisuuX = atoi(suuji);
							}
						}
						else if (lastSubCommand == 1)
						{
							if ((lastHoukou == 0) || (lastHoukou == 1))
							{
								speedY = atoi(suuji);
							}
							if ((lastHoukou == 2) || (lastHoukou == 3))
							{
								speedX = atoi(suuji);
							}
						}
						else if (lastSubCommand == 2)
						{
							if ((lastHoukou == 0) || (lastHoukou == 1))
							{
								waitY = atoi(suuji);
							}
							if ((lastHoukou == 2) || (lastHoukou == 3))
							{
								waitX = atoi(suuji);
							}
						}
					}
					else
					{
						if (ln>=2)
						{
							int c1 = (int)(*(name)) & 0xff;
							int c2 = (int)(*(name+1)) & 0xff;
							int cc = ((c1 << 8) | c2);

							if (codeByte == 2)
							{
								if (cc == upArrow)
								{
									houkouY = 0;
									name += 2;
									ln -= 2;
									lastHoukou = 0;
									lastSubCommand = 0;
								}
								if (cc == downArrow)
								{
									houkouY = 1;
									name += 2;
									ln -= 2;
									lastHoukou = 1;
									lastSubCommand = 0;
								}
								if (cc == leftArrow)
								{
									houkouX = 0;
									name += 2;
									ln -= 2;
									lastHoukou = 2;
									lastSubCommand = 0;
								}
								if (cc == rightArrow)
								{
									houkouX = 1;
									name += 2;
									ln -= 2;
									lastHoukou = 3;
									lastSubCommand = 0;
								}
							}
							else
							{
								if (c1 == upArrow1Byte)
								{
									houkouY = 0;
									name += 1;
									ln -= 1;
									lastHoukou = 0;
									lastSubCommand = 0;
								}
								if (c1 == downArrow1Byte)
								{
									houkouY = 1;
									name += 1;
									ln -= 1;
									lastHoukou = 1;
									lastSubCommand = 0;
								}
								if (c1 == leftArrow1Byte)
								{
									houkouX = 0;
									name += 1;
									ln -= 1;
									lastHoukou = 2;
									lastSubCommand = 0;
								}
								if (c1 == rightArrow1Byte)
								{
									houkouX = 1;
									name += 1;
									ln -= 1;
									lastHoukou = 3;
									lastSubCommand = 0;
								}
							}

						}
					}
				}
			}
		}
	}


	if (houkou == 0) return houkouX;
	if (houkou == 1) return houkouY;

	if (houkou == 2) return maisuuX;
	if (houkou == 3) return maisuuY;

	if (houkou == 4) return speedX;
	if (houkou == 5) return speedY;

	if (houkou == 6) return waitX;
	if (houkou == 7) return waitY;

	return 1;
}


int CCGDataControl::GetCGKosuu(int playerNumber)
{
	return m_cgKosuu[playerNumber];
}

int CCGDataControl::GetTotalCGPercent(void)
{
	int totalKosuu = 0;
	int getKosuu = 0;

	for (int i=0;i<m_cgCharaKosuu;i++)
	{
		int cgKosuu = GetCGKosuu(i);
		totalKosuu += cgKosuu;

		for (int k=0;k<cgKosuu;k++)
		{
			if (CheckGetCG(i,k)) getKosuu++;
		}
	}
	if (totalKosuu <= 0) totalKosuu = 1;

	int ps = (getKosuu * 100) / totalKosuu;
	if (ps<0) ps = 0;
	if (ps>=100) ps = 100;

	if (ps == 0)
	{
		if (getKosuu > 0) ps = 1;
	}

	if (ps == 100)
	{
		if (getKosuu < totalKosuu) ps = 99;
	}

	return ps;
}

int CCGDataControl::GetCGPercent(int cgCharaNumber)
{
	int totalKosuu = 0;
	int getKosuu = 0;

	int cgKosuu = GetCGKosuu(cgCharaNumber);
	totalKosuu += cgKosuu;

	for (int k=0;k<cgKosuu;k++)
	{
		if (CheckGetCG(cgCharaNumber,k)) getKosuu++;
	}
	if (totalKosuu <= 0) totalKosuu = 1;

	int ps = (getKosuu * 100) / totalKosuu;
	if (ps<0) ps = 0;
	if (ps>=100) ps = 100;

	if (ps == 0)
	{
		if (getKosuu > 0) ps = 1;
	}

	if (ps == 100)
	{
		if (getKosuu < totalKosuu) ps = 99;
	}

	return ps;
}

BOOL CCGDataControl::CheckGetCG(int player, int num)
{
	return m_systemFile->CheckCG(player,num);
}


int CCGDataControl::SearchNextCG(void)
{
	int pl = GetCGCharaNumber();
	int kosuu = GetCGKosuu(pl);
	int cg = GetCGNumber();

	if (kosuu == 0) kosuu = 1;

	int found = cg;
	for (int i=0;i<kosuu;i++)
	{
		cg++;
		cg %= kosuu;
		if (CheckGetCG(pl,cg))
		{
			found = cg;
			break;
		}
	}

	SetCGNumber(found);
	return found;
}



int CCGDataControl::SearchPreCG(void)
{
	int pl = GetCGCharaNumber();
	int kosuu = GetCGKosuu(pl);
	int cg = GetCGNumber();

	if (kosuu == 0) kosuu = 1;

	int found = cg;
	for (int i=0;i<kosuu;i++)
	{
		cg--;
		cg += kosuu;
		cg %= kosuu;
		if (CheckGetCG(pl,cg))
		{
			found = cg;
			break;
		}
	}

	SetCGNumber(found);
	return found;
}

void CCGDataControl::SetAllOn(void)
{

	for (int i=0;i<m_cgCharaKosuu;i++)
	{
		int cgKosuu = GetCGKosuu(i);

		for (int k=0;k<cgKosuu;k++)
		{
			m_systemFile->SetCG(i,k);
		}
	}

}

/*_*/


