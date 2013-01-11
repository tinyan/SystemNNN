#include <windows.h>

#include "getCommandLineParam.h"


CGetCommandLineParam::CGetCommandLineParam()
{
}

CGetCommandLineParam::~CGetCommandLineParam()
{
}

void CGetCommandLineParam::End(void)
{
}


int CGetCommandLineParam::GetParam(int buffKosuu,int buffSize,char** lplpBuff,LPSTR lpCmd)
{
	if (buffKosuu <= 0) return 0;

	BOOL found = FALSE;
	int ln = strlen(lpCmd);

	int n = 0;
	int start = 0;
	int end = 0;

	int k = 0;

	while (n<ln)
	{
		char c = *(lpCmd+n);
		n++;
		
		if (c == '/')
		{
			if (found)
			{
				SetParamSub(start,n-2,lplpBuff[k],buffSize,lpCmd);
				k++;
				start = n;
				if (k>=buffKosuu) break;
			}
			else
			{
				found = TRUE;
				start = n;
			}
		}
	}

	if (found)
	{
		if (k<buffKosuu)
		{
			SetParamSub(start,ln-1,lplpBuff[k],buffSize,lpCmd);
			k++;
		}
	}

	return k;
}

void CGetCommandLineParam::SetParamSub(int start,int end,char* buf,int buffSize,LPSTR lpCmd)
{
	int ln = end - start + 1;
	buf[0] = 0;
	if (ln>0)
	{
		if (ln>buffSize-2) ln = buffSize-2;
		memcpy(buf,lpCmd+start,ln);
		buf[ln] = 0;
		buf[ln+1] = 0;
	}

	//last erase ' '
	for (int i=ln-1;i>=0;i--)
	{
		char c = *(buf+i);
		if (c != ' ')
		{
			break;
		}
		*(buf+i) = 0;
	}
}
