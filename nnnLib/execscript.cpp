//
// execscript.cpp
//

#include <windows.h>
#include <stdio.h>


#include "..\nyanLib\include\commonmacro.h"
#include "..\nyanLib\include\myFile.h"

#include "..\nnnUtilLib\scriptcommand.h"
#include "..\nnnUtilLib\scriptDefine.h"

#include "scriptCallBack.h"
#include "execscript.h"

int CExecScript::m_xorCode = 0xffffffff;
int CExecScript::m_addXorCode = 0;
int CExecScript::m_addIncCode = 0;




CExecScript::CExecScript(CScriptCallBack* lpCallBack, int sz)
{
	m_callBack = lpCallBack;

	m_filename[0] = 0;
	m_messagePointer1 = 0;
	m_messagePointer2 = 0;
	m_int32Pointer = 0;

	m_messageKosuu1 = 0;
	m_messageKosuu2 = 0;

	m_dataExistFlag = FALSE;
	
	m_pc = 0;
	m_stackPointer = 0;

	//Error関係
	m_errorFlag = FALSE;
	m_errorMessage[0][0] = 0;
	m_errorCount = 0;
	m_errorNum = 0;

	if (sz == -1) sz = 1024*256;	//1.0M

	m_data = new int[sz];

	m_bufferSize = sz;

	m_stateCount = 0;
}



CExecScript::~CExecScript()
{
	End();
}


void CExecScript::End(void)
{
	DELETEARRAY(m_data);
}


int CExecScript::Exec(int n)
{
	if (n == -1) n = m_pc;

	if (m_dataExistFlag == FALSE) return -1;	//error
	if (n>=m_dataSize) return COMMAND_END;	//end

	m_pc = n;

	
	if (m_stackPointer == 0)
	{
		m_stateCount = 0;
	}

//	int tmp;

	while (m_pc < m_dataSize)
	{
		m_stateCount++;
		if (m_stateCount >= 10000)
		{
			//無限ループ???
///			AddError("無限ループの恐れあり");
//			m_stackPointer--;
///			return -1;
		}


		int skp = m_data[m_pc];

		if (skp == 0)
		{
			AddError("これ以上のスクリプトはありません");
			return COMMAND_END;
		}

		int identify = m_data[m_pc+1];
		int code = m_data[m_pc+2];

		if (identify == IDENTIFY_DATA)
		{
			m_pc += m_data[m_pc];
			continue;
		}

		if (identify == IDENTIFY_CONTROL)
		{
			if (code == CODE_CONTROL_NOP)
			{
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_CONTROL_IF)
			{
				//さいしょのじょうけんチェック
				while (1)
				{
					if (Enzan(m_pc+3) > 0)
					{
						m_pc += m_data[m_pc];
						break;
					}

					//なりたっていない場合スキップして次をみる
					m_pc += m_data[m_pc];

					int identify1 = m_data[m_pc+1];
					int code1 = m_data[m_pc+2];
					if ((identify1 == IDENTIFY_CONTROL) && (code1 == COMMAND_OPENCHUKAKKO1))
					{
						m_pc += m_data[m_pc+3];
					}
					else
					{
						m_pc += m_data[m_pc];
					}

					int identify2 = m_data[m_pc+1];
					int code2 = m_data[m_pc+2];

					//else
					if ((identify2 == IDENTIFY_CONTROL) && (code2 == CODE_CONTROL_ELSE))
					{
						m_pc += m_data[m_pc];
						break;
					}

					//elsif
					if ((identify2 == IDENTIFY_CONTROL) && (code2 == CODE_CONTROL_ELSIF))
					{
						continue;
					}

					//etc
					break;
				}
				continue;
			}


			if (code == CODE_CONTROL_WHILE)
			{
				if (Enzan(m_pc+3) > 0)
				{
					m_pc += m_data[m_pc];
				//	break;
					continue;
				}

				//なりたっていない場合スキップ
				m_pc += m_data[m_pc];

				int identify1 = m_data[m_pc+1];
				int code1 = m_data[m_pc+2];
				if ((identify1 == IDENTIFY_CONTROL) && (code1 == COMMAND_OPENCHUKAKKO1))
				{
					m_pc += m_data[m_pc+3];
				}
				else
				{
					m_pc += m_data[m_pc];
				}
				continue;

			}



			if ((code == CODE_CONTROL_ELSE) || (code == CODE_CONTROL_ELSIF) || (code == CODE_CONTROL_CASE))
			{
				m_pc += m_data[m_pc];
				int identify1 = m_data[m_pc+1];
				int code1 = m_data[m_pc+2];
				if ((identify1 == IDENTIFY_CONTROL) && (code1 == COMMAND_OPENCHUKAKKO1))
				{
					m_pc += m_data[m_pc+3];
				}
				else
				{
					m_pc += m_data[m_pc];
				}
				continue;
			}

			if (code == CODE_CONTROL_RETURN)
			{
//char mes[256];sprintf(mes,"ret=%d",m_stackPointer);OutputDebugString(mes);
				if (m_stackPointer <= 0)
				{
					AddError("return without subエラー");
					return -1;
				}

				m_stackPointer--;
				m_pc = m_stack[m_stackPointer];
				continue;
			}

			if (code == CODE_CONTROL_SUB)
			{

				m_stack[m_stackPointer] = m_pc + skp;
				m_ID[m_stackPointer] = m_data[m_pc+4];

				m_stackPointer++;

				if (m_stackPointer >= 250)
				{
					m_stackPointer--;
					AddError("サブルーチンコールが250段を超えました");
					return -1;
				}

				m_pc = m_data[ m_data[9] + m_data[m_pc+3] ];
//char mes[256];sprintf(mes,"call %d stack=%d ",m_pc,m_stackPointer);OutputDebugString(mes);
				continue;
			}

			if (code == CODE_CONTROL_GOTO)
			{
				m_pc = m_data[m_pc+3];
				continue;
			}

			if (code == CODE_CONTROL_END)
			{
				return CODE_CONTROL_END;
			}

			if (code == CODE_CONTROL_EXIT)
			{
				m_pc += m_data[m_pc];
				return CODE_CONTROL_EXIT;
			}

			if (code == CODE_CONTROL_NEXT)
			{
				return CODE_CONTROL_NEXT;
			}

			if (code == CODE_CONTROL_ENDFILM)
			{
				m_pc += m_data[m_pc];
				return CODE_CONTROL_ENDFILM;
			}

			if (code == CODE_CONTROL_ENDKOMA)
			{
				m_pc += m_data[m_pc];
				return CODE_CONTROL_ENDKOMA;
			}

			if (code == CODE_CONTROL_ENDIF)
			{
				m_pc += m_data[m_pc];
				return CODE_CONTROL_ENDIF;
			}

			if (code == CODE_CONTROL_SCRIPT)
			{
				m_callBack->ReceiveScriptCommand(code,0,GetStringPtr(m_data[m_pc+3]));
				m_stack[253] = m_data[m_pc+4];
				m_pc += m_data[m_pc];
				return CODE_CONTROL_SCRIPT;
			}

			if (code == CODE_CONTROL_SUBSCRIPT)
			{
				m_callBack->ReceiveScriptCommand(code,0,GetStringPtr(m_data[m_pc+3]));
				m_stack[253] = m_data[m_pc+4];
				m_pc += m_data[m_pc];
				return CODE_CONTROL_SUBSCRIPT;
			}

			if (code == CODE_CONTROL_SCRIPTJUMP)
			{
				m_callBack->ReceiveScriptCommand(code,0,GetStringPtr(m_data[m_pc+3]));
				m_pc += m_data[m_pc];
				return CODE_CONTROL_SCRIPTJUMP;
			}

		}




		if (identify == IDENTIFY_COMMAND)
		{
			///Enzan();をつかうにゃ

			int paraKosuu = m_data[m_pc+3];
			int para[256];
			if (paraKosuu>256) paraKosuu = 256;

			int skp = 0;
			int pc = m_pc+4;


			for (int ii=0;ii<paraKosuu;ii++)
			{
				para[ii] = Enzan(pc,&skp);
				pc += skp;
			}


			m_stack[254] = m_data[m_pc + m_data[m_pc] - 1];
//			m_stack[254] = m_data[m_pc + 5];

			m_pc += m_data[m_pc];
			m_callBack->ReceiveUserCommand0(code,paraKosuu,para);

//			m_pc += m_data[m_pc];
			return CODE_USERCOMMAND;
		}



		if (identify == IDENTIFY_FUNCTION)
		{
			int paraKosuu = m_data[m_pc+3];
			int para[256];
			if (paraKosuu>256) paraKosuu = 256;

			int skp = 0;
			int pc = m_pc+4;


			for (int ii=0;ii<paraKosuu;ii++)
			{
				para[ii] = Enzan(pc,&skp);
				pc += skp;
			}

			m_callBack->ReceiveUserFunction0(code,paraKosuu,para);

			m_pc += m_data[m_pc];
			continue;
		}


		if (identify == IDENTIFY_CALCU)
		{
			Enzan(m_pc+3);
			m_pc += m_data[m_pc];
			continue;
		}


		if (identify == IDENTIFY_SYSTEMCOMMAND)
		{
			if ((code == CODE_SYSTEMCOMMAND_PRINT) || (code == CODE_SYSTEMCOMMAND_LPRINT) || (code == CODE_SYSTEMCOMMAND_APPEND))
			{
				int cutin = 0;
				if (m_data[m_pc] >= 6)
				{
					cutin = m_data[m_pc+5];
				}



				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4],GetMessagePtr(m_data[m_pc+3]),cutin);
				m_pc += m_data[m_pc];
				return CODE_SYSTEMCOMMAND_PRINT;
			}

			if (code == CODE_SYSTEMCOMMAND_DRAW)
			{
				int count = m_data[m_pc+4];
				m_callBack->ReceiveScriptCommand(code,1,&m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				if (count != 0)
				{
					return CODE_SYSTEMCOMMAND_DRAW;
				}
				else
				{
					continue;
				}
			}

			if (code == CODE_SYSTEMCOMMAND_OVERRAP)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)&m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				return CODE_SYSTEMCOMMAND_OVERRAP;
			}

			if (code == CODE_SYSTEMCOMMAND_SELECT)
			{
//				GetSelectMessage(m_pc+3);
//				m_callBack->ReceiveScriptCommandSelect(cmd,m_selectMessageKosuu,m_selectMessage,m_selectMessageNumber);
				int mesKosuu = 0;
				int selKosuu = m_data[m_pc+3];

				int timeLimit = 0;
				int autoSelect = 0;
				int specialFlag = 0;

				if (m_data[m_pc] != (selKosuu+5))	//new version
				{
					mesKosuu = m_data[m_pc+m_data[m_pc]-1];
				}

				if (m_data[m_pc] > selKosuu+mesKosuu+5)	//new 2 version
				{
					timeLimit = m_data[m_pc+m_data[m_pc]-2];
					autoSelect = m_data[m_pc+m_data[m_pc]-3];
				}

				if (m_data[m_pc] > selKosuu+mesKosuu+6)	//new 2 version
				{
					specialFlag = m_data[m_pc+m_data[m_pc]-4];
				}

				int tmp[256];
				tmp[0] = selKosuu;
				tmp[1] = mesKosuu;
				for (int i=0;i<selKosuu+mesKosuu;i++)
				{
					tmp[2+i] = m_data[m_pc+4+i];
				}

				tmp[2+selKosuu+mesKosuu] = timeLimit;
				tmp[2+selKosuu+mesKosuu+1] = autoSelect;
				tmp[3+selKosuu+mesKosuu+1] = specialFlag;

				m_callBack->ReceiveScriptCommand(code,selKosuu+mesKosuu+2+2,tmp);
//				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)&m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				return CODE_SYSTEMCOMMAND_SELECT;
			}

			//select
		}




		if (identify == IDENTIFY_SYSTEMFUNCTION)
		{
			if (code == CODE_SYSTEMFUNCTION_LOADDWQ)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],GetStringPtr(m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_PRELOADDWQ)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],GetStringPtr(m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_SETEFFECT)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_CLEARALLEFFECT)
			{
				m_callBack->ReceiveScriptCommand(code);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_CLEAREFFECTLAYER)
			{
				m_callBack->ReceiveScriptCommand(code,1,(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_PREPAREOVERRAP)
			{
				m_callBack->ReceiveScriptCommand(code);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_SETEFFECTRECT)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_NOMESSAGEWINDOW)
			{
				m_callBack->ReceiveScriptCommand(code);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_MUSIC)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_VOICE)
			{
				if (m_data[m_pc+4] == -1)
				{
					m_callBack->PreReceiveScriptData(code,1,NULL);
				}
				else
				{
					m_callBack->PreReceiveScriptData(code,1,(LPVOID)GetStringPtr(m_data[m_pc+4]));
				}
				int defVoice = 0;

				int prk = m_data[m_pc+3];
				if (skp > prk+4)
				{
					defVoice = m_data[m_pc+4+prk];//check default voice
				}

				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],&m_data[m_pc+4],defVoice);

				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_SOUND)
			{
//				m_callBack->ReceiveScriptCommand(code,1,(LPVOID)(&m_data[m_pc+4]));
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],&m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_SETCG)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_SETSCENE)
			{
				m_callBack->ReceiveScriptCommand(code,1,(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_SETFILM)
			{
				m_callBack->ReceiveScriptCommand(code,1,(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_STARTMESSAGE)
			{
				int paraKosuu = m_data[m_pc+3];
				m_callBack->ReceiveScriptCommand(code,paraKosuu,(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_STARTKOMA)
			{
				int paraKosuu = m_data[m_pc+3];
				m_callBack->ReceiveScriptCommand(code,paraKosuu,(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_FRAMECONTROL)
			{
				m_callBack->ReceiveScriptCommand(code,1,(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_SETDEFAULTFRAME)
			{
				m_callBack->ReceiveScriptCommand(code);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_DEBUG)
			{
				m_callBack->ReceiveScriptCommand(code,1,GetMessagePtr(m_data[m_pc+3]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_SETDEMOFLAG)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_FILMNAME)
			{
				m_callBack->ReceiveScriptCommand(code,1,GetStringPtr(m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_STORYNAME)
			{
				m_callBack->ReceiveScriptCommand(code,1,GetStringPtr(m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_FILMTYPETIME)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_CONFIGMASK)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_WINDOWNUMBER)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_MOUSENUMBER)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_CURSORNUMBER)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_AUTOMESSAGE)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_CANNOTCLICK)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_CANNOTSKIP)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_OPTIONOFF)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_CUTIN)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_MESSAGEEXPSTATUS)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_FILMENDENABLE)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_FILMEXPSTATUS)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_CHANGEMESSAGEFONTSIZETYPE)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_RENAMELAYER)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+4]);
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_SETCGBYVAR)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_SETVAR)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_VARCONTROLLAYER)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_FACE)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_MUSTFACE)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_VOLUMEONLY_SE)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_VOLUMEONLY_VOICE)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_NEXTFADE_SE)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_NEXTFADE_VOICE)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}

			if (code == CODE_SYSTEMFUNCTION_MUSICVOLUMEONLY)
			{
				m_callBack->ReceiveScriptCommand(code,m_data[m_pc+3],(LPVOID)(&m_data[m_pc+4]));
				m_pc += m_data[m_pc];
				continue;
			}


//				GetParameter(m_pc+2);
		}

		//unknown
		m_pc += m_data[m_pc];
	}

	return COMMAND_END;	//end
}



/*
void CExecScript::GetSelectMessage(int pc)
{
	m_selectMessageKosuu = m_data[pc];
	if (m_selectMessageKosuu>3) m_selectMessageKosuu = 3;

	for (int i=0;i<m_selectMessageKosuu;i++)
	{
		LPSTR mes = GetMessagePtr(m_data[pc+1+i]);
		int num = GetMessageNumber(m_data[pc+1+i]);

		m_selectMessage[i] = mes;
		m_selectMessageNumber[i] = num;
	}
}
*/






LPSTR CExecScript::GetMessagePtr(int mesNum)
{
	return (LPSTR)(&m_data[m_data[m_messagePointer1 + mesNum]]);
}

LPSTR CExecScript::GetStringPtr(int strNum)
{
	return (LPSTR)(&m_data[m_data[m_messagePointer2 + strNum]]);
}

int CExecScript::GetInt32(int n)
{
	return m_data[m_int32Pointer + n];
}

/*
int CExecScript::GetMessageNumber(int script)
{
	int shurui = script & 0xf0000000;
	if (shurui == SCRIPT_MESSAGE)
	{
		return script & 0xffff;
	}
	
	return -1;	//message2 and etc
}
*/


BOOL CExecScript::LoadScript(LPSTR filename)
{
	m_pc = 0;
	m_stackPointer = 0;

	if (filename == NULL) return FALSE;

	if (_stricmp(m_filename,filename) == 0)
	{
		return TRUE;
	}

	memcpy(&m_filename[0],filename,strlen(filename)+1);

	INT64 fileSize = 0;
	FILE* file = CMyFile::Open(filename,"rb",&fileSize);

	int xorCode = m_xorCode;
	int addXorCode = m_addXorCode;
	int addIncCode = m_addIncCode;

	if (file != NULL)
	{
		//万一たりなかったら再確保
		if (fileSize > m_bufferSize)
		{
			delete [] m_data;
			int newSize = ((int)fileSize+3) / 4;
			m_bufferSize = (newSize + 1023+1024) & (~1023);
			m_data = new int[m_bufferSize];

		}
		m_dataSize = (int)fileSize;
		fread(&m_data[0],sizeof(int),m_dataSize,file);

		fclose(file);

		int sz = m_dataSize;
		int* pt = &m_data[0];

		//dis
		__asm
		{
			push eax
			push ebx
			push ecx
			push edx
			push esi
			push edi
			mov ecx,sz
			mov esi,pt
//			mov ebx,0ffffffffh
			mov ebx,xorCode
			mov edx,addXorCode
			mov edi,0
LOOP1:
			mov eax,[esi]
			xor eax,ebx
			add eax,edi
			add ebx,edx
			add edi,addIncCode
			mov [esi],eax
			add esi,4
			dec ecx
			jnz LOOP1

			pop edi
			pop esi
			pop edx
			pop ecx
			pop ebx
			pop eax
		}

		m_dataExistFlag = TRUE;
		m_pc = 0;
		m_stackPointer = 0;
	}
	else
	{
		wsprintf(m_errorMessageTmp,"Script File not found:%s",filename);
		AddError(m_errorMessageTmp);
		return FALSE;
	}

	//get message pointerとりあえず固定位置。あとで修正するかも

	m_messageKosuu1 = m_data[4];
	m_messagePointer1 = m_data[5];
	m_messageKosuu2 = m_data[6];
	m_messagePointer2 = m_data[7];

	m_storyKosuu = m_data[10];

	m_int32Pointer = m_data[18];	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	if (m_data[0] >= 32)
	{
		m_subCallPointer = m_data[20];
		m_selectPointer = m_data[21];
		m_commandCallPointer = m_data[22];
		m_scriptCallPointer = m_data[23];
	}
	else
	{
		m_subCallPointer = 0;
		m_selectPointer = 0;
		m_commandCallPointer = 0;
		m_scriptCallPointer = 0;
	}

	///////////////////////////////////
	return TRUE;

	BOOL flag1 = FALSE;
	BOOL flag2 = FALSE;

	int ptr = 0;
	while ((ptr<m_dataSize) && ((flag1 == FALSE) || (flag2 == FALSE)))
	{
		int skp = m_data[ptr];
		int script = m_data[ptr+1];
		int cmd = script & 0xffff0000;
		int dat = script & 0x0000ffff;

		if ((cmd & 0xffff0000) == SCRIPT_TABLE)
		{
			if (dat == 0)
			{
				m_messageKosuu1 = m_data[ptr+2];
				m_messagePointer1 = m_data[ptr+3];
				flag1 = TRUE;
			}

			if (dat == 1)
			{
				m_messageKosuu2 = m_data[ptr+2];
				m_messagePointer2 = m_data[ptr+3];
				flag2 = TRUE;
			}

			if (0)//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			{
				//m_int32Kosuu = m_data[ptr+2];
				m_int32Pointer = m_data[ptr+3];
			}
		}

		ptr += skp;
	}



	return TRUE;
}


int CExecScript::ExecCase(int nm)
{
	if (m_dataExistFlag == FALSE) return -1;	//用心

	int pc = GetCase(m_pc,nm);
	if (pc <= 0) return -1;	//error

	m_pc = pc;
	return Exec();
}



int CExecScript::SearchLabel(LPSTR labelName)
{
	int pc = 0;
	while (pc < m_dataSize)
	{
		int skp = m_data[pc];
		int script = m_data[pc+1];
		int shurui = script & 0xffff0000;
		if (shurui == SCRIPT_LABEL)
		{
			LPSTR mes = (LPSTR)(&m_data[pc+2]);
			if (strcmp(mes,labelName) == 0)
			{
				return pc;
			}
		}

		pc += skp;
	}
	return -1;
}

int CExecScript::GetPC(void)
{
	return m_pc;
}

void CExecScript::SetPC(int pc)
{
	m_pc = pc;
}


BOOL CExecScript::SetPCByFilmNumber(int filmNumber)
{
	int kosuu = m_data[8];
	int pc = m_data[9];
	int offset = m_data[10];

	int k= offset + filmNumber;
	if (k<kosuu)
	{
		m_pc = m_data[pc+k];
		return TRUE;
	}

	return FALSE;
}



int CExecScript::GetCase(int pc, int n)
{
	if (m_dataExistFlag == FALSE) return -1;	//error

	if (pc == -1) pc = m_pc;

	if (pc>=m_dataSize) return 0;	//end

	int pc0 = pc;

//	int tmp;

	//最初の{をとばす

	int id = m_data[pc+1];
	int cd = m_data[pc+2];


	if ((id == IDENTIFY_CONTROL) && (cd == COMMAND_OPENCHUKAKKO1))
	{
		pc += m_data[pc];
	}

//char mes[256];
//sprintf(mes,"Search Case %d\n",n);
//OutputDebugString(mes);


	while (pc < m_dataSize)
	{
		int skp = m_data[pc];
		if (skp == 0)
		{
			AddError("これ以上のスクリプトはありません");
			return 0;
		}

		id = m_data[pc+1];
		cd = m_data[pc+2];

		if ((id != IDENTIFY_CONTROL) || (cd != CODE_CONTROL_CASE))
		{
//OutputDebugString("not case ");

//sprintf(mes,"not case id=%X cd=%X \n",id,cd);
//OutputDebugString(mes);

			AddError("case以外発見");
			return pc;
		}

		if ((m_data[pc+3] & 0xffff) == n)
		{
//OutputDebugString("found case");
			return pc+skp;
		}

		//skip case
//OutputDebugString("skip case ");

		pc += skp;
		skp = m_data[pc];
		if (skp == 0)
		{
			AddError("case発見できずA");
			return 0;
		}

		id = m_data[pc+1];
		cd = m_data[pc+2];

		if ((id == IDENTIFY_CONTROL) && (cd == COMMAND_OPENCHUKAKKO1))		//'}'までスキップ
		{

//sprintf(mes,"skip { %d",m_data[pc+3]);
//OutputDebugString(mes);

			pc += m_data[pc+3];
			id = m_data[pc+1];
			cd = m_data[pc+2];
			if ((id == IDENTIFY_CONTROL) && (cd == COMMAND_CLOSECHUKAKKO1))
			{
//OutputDebugString("skip } ");
				pc += m_data[pc];
			}
		}
		else
		{
//OutputDebugString("skip unknown ");
			pc += m_data[pc];
		}
	}

	AddError("case発見できずB");
	return 0;
}



int CExecScript::Enzan(int pc, int* pSkip)
{
	int script = m_data[pc];
	int shurui = script & 0xf0000000;
	int subShurui = script & 0xffff0000;
	int dat = script & 0x0000ffff;


	if (script != SCRIPT_CALCU)	//単なる変数や定数文字列
	{
		if (pSkip != NULL) 	*pSkip = 1;

		if (shurui == SCRIPT_VAR)
		{
			return m_callBack->GetCalcuVarData(script & 0xffff);
		}

		if (shurui == SCRIPT_NUMBER)
		{
			if ((dat & 0x8000) == 0) return dat;
			return dat | 0xffff0000;
		}

		if (shurui == SCRIPT_NUMBER32)
		{
			return GetInt32(dat);
		}

		if (shurui == SCRIPT_NUMBER_STACK32)
		{
			return m_int32stack[dat];
		}


		//これをけずる
		if ((shurui == SCRIPT_MESSAGE) || (shurui == SCRIPT_MESSAGE2))
		{
			return script;	//文字列をあらわすコード
		}
	}


	int n = m_data[pc+1];
	if (pSkip != NULL) *pSkip = n + 2;

	//ポーランドしき計算

	pc += 2;

	int stack = 0;

	for (int i=0;i<n;i++)
	{
		script = m_data[pc];
		shurui = script & 0xf0000000;
		subShurui = script & 0xffff0000;
		dat = script & 0x0000ffff;

		pc++;

		if ((shurui == SCRIPT_VAR) || (shurui == SCRIPT_NUMBER) || (shurui == SCRIPT_NUMBER32))
		{
			m_polandStack[stack] = script;

			stack++;
			if (stack >= 256)
			{
				AddError("計算式が複雑すぎますにゃ");
				return 0;
			}
			continue;
		}

		if (shurui == SCRIPT_CALCU)
		{
			if (subShurui == SCRIPT_CALCU_ENZAN)
			{
				// = !, + - * / % & ^ |
				if (dat == '=')
				{
					//代入(できれば)
					if (stack<2)
					{
						AddError("代入演算エラー(パラメータ不足)");
						return 0;
					}

					int dstVar  = ScriptToVarNumber(m_polandStack[stack-2]);
					if (dstVar == -1)
					{
						AddError("代入演算エラー(変数以外に代入しています)");
						return 0;
					}

					int srcData = ScriptToData(m_polandStack[stack-1]);

					m_callBack->SetVarData(dstVar,srcData);
					stack--;
					continue;
				}

				if (dat == '!')
				{
					//単項論理反転演算
					if (stack<1)
					{
						AddError("単項演算エラー(パラメータ不足)");
						return 0;
					}
					int dstVar = ScriptToVarNumber(m_polandStack[stack-1]);
					int d = ScriptToData(m_polandStack[stack-1]);
					if (d == 0) 
					{
						d = 1;
					}
					else
					{
						d = 0;
					}

					if (dstVar != -1)
					{
						m_callBack->SetVarData(dstVar,d);
					}
					else
					{
						m_polandStack[stack-1] = SCRIPT_NUMBER | (d & 0xffff);
					}
//					stack--;
					continue;
				}

				if (stack<2)
				{
					AddError("代入演算エラー(パラメータ不足)");
					return 0;
				}

				//2こうえんざん
				int dat1 = ScriptToData(m_polandStack[stack-2]);
				int dat2 = ScriptToData(m_polandStack[stack-1]);

				switch (dat)
				{
				case '+':
					dat1 += dat2;
					break;
				case '-':
					dat1 -= dat2;
					break;
				case '*':
					dat1 *= dat2;
					break;
				case '/':
					if (dat2 == 0) dat2 = 1;
					dat1 /= dat2;
					break;
				case '%':
					if (dat2 == 0) dat2 = 1;
					dat1 %= dat2;
					break;
				case '&':
					dat1 &= dat2;
					break;
				case '^':
					dat1 ^= dat2;
					break;
				case '|':
					dat1 |= dat2;
					break;
				default:
					AddError("不当な演算子エラー1");
					return 0;
					break;
				}

				if ((dat1 > -32768) && (dat1<32768))
				{
					m_polandStack[stack-2] = SCRIPT_NUMBER | (dat1 & 0xffff);
				}
				else
				{
					m_polandStack[stack-2] = SCRIPT_NUMBER_STACK32 | stack-2;
					m_int32stack[stack-2] = dat1;
				}

//				if (dat1 > 32767) dat1 = 32767;
//				if (dat1<-32767) dat1 = -32767;
//				m_polandStack[stack-2] = SCRIPT_NUMBER | (dat1 & 0xffff);

				stack--;
				continue;
			}

			if (subShurui == SCRIPT_CALCU_CALCUEQUAL)
			{
				// != += -= *= /= %= &= ^= |=
				if (stack<2)
				{
					AddError("代入演算エラー(パラメータ不足)");
					return 0;
				}

				int dat1 = ScriptToData(m_polandStack[stack-2]);
				int dat2 = ScriptToData(m_polandStack[stack-1]);
				int dstVar = ScriptToVarNumber(m_polandStack[stack-2]);

				if (dat == '=')
				{
					if (dat1 == dat2)
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					m_polandStack[stack-2] = SCRIPT_NUMBER | dat1;
					stack--;
					continue;
				}

				if (dstVar == -1)
				{
					AddError("代入演算エラー(変数以外に代入しています)");
					return 0;
				}

				switch (dat)
				{
				case '!':
					if (dat2 == 0)
					{
						dat2 = 1;
					}
					else
					{
						dat2 = 0;
					}
					dat1 = dat2;
					break;
				case '+':
					dat1 += dat2;
					break;
				case '-':
					dat1 -= dat2;
					break;
				case '*':
					dat1 *= dat2;
					break;
				case '/':
					if (dat2 == 0) dat2 = 1;
					dat1 /= dat2;
					break;
				case '%':
					if (dat2 == 0) dat2 = 1;
					dat1 %= dat2;
					break;
				case '&':
					dat1 &= dat2;
					break;
				case '^':
					dat1 ^= dat2;
					break;
				case '|':
					dat1 |= dat2;
					break;
				default:
					AddError("不当な演算子エラー2");
					return 0;
					break;
				}

//				if (dat1 > 32767) dat1 = 32767;
//				if (dat1<-32767) dat1 = -32767;

				m_callBack->SetVarData(dstVar,dat1);
				stack--;
				continue;
			}

			if (subShurui == SCRIPT_CALCU_DOUBLE)
			{
				//	== && ^^ ||
				if (stack<2)
				{
					AddError("演算エラー(パラメータ不足)4");
					return 0;
				}

				int dat1 = ScriptToData(m_polandStack[stack-2]);
				int dat2 = ScriptToData(m_polandStack[stack-1]);

				switch (dat)
				{
				case '=':
					if (dat1 == dat2)
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					break;
				case '&':
					if ((dat1 != 0) && (dat2 != 0))
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					break;
				case '|':
					if ((dat1 != 0) || (dat2 != 0))
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					break;
				case '^':
					if (((dat1 != 0) && (dat2 == 0)) || ((dat1 == 0) && (dat2 != 0)))
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					break;
				default:
					AddError("不当な演算子エラー3");
					return 0;
					break;
				}


				if (dat1 > 32767) dat1 = 32767;
				if (dat1<-32767) dat1 = -32767;
				m_polandStack[stack-2] = SCRIPT_NUMBER | (dat1 & 0xffff);
				stack--;
				continue;
			}

			if (subShurui == SCRIPT_CALCU_COMPARE)
			{
				// < > 
				if (stack<2)
				{
					AddError("演算エラー(パラメータ不足)5");
					return 0;
				}

				int dat1 = ScriptToData(m_polandStack[stack-2]);
				int dat2 = ScriptToData(m_polandStack[stack-1]);

				switch (dat)
				{
				case '<':
					if (dat1 < dat2)
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					break;
				case '>':
					if (dat1 > dat2)
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					break;
				default:
					AddError("不当な演算子エラー4");
					return 0;
					break;
				}

				if (dat1 > 32767) dat1 = 32767;
				if (dat1<-32767) dat1 = -32767;

				m_polandStack[stack-2] = SCRIPT_NUMBER | (dat1 & 0xffff);
				stack--;
				continue;
			}

			if (subShurui == SCRIPT_CALCU_COMPAREEQUAL)
			{
				// <= >= == !=
				if (stack<2)
				{
					AddError("演算エラー(パラメータ不足)6");
					return 0;
				}

				int dat1 = ScriptToData(m_polandStack[stack-2]);
				int dat2 = ScriptToData(m_polandStack[stack-1]);

				switch (dat)
				{
				case '<':
					if (dat1 <= dat2)
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					break;
				case '>':
					if (dat1 >= dat2)
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					break;
				case '=':
					if (dat1 == dat2)
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					break;
				case '!':
					if (dat1 != dat2)
					{
						dat1 = 1;
					}
					else
					{
						dat1 = 0;
					}
					break;
				default:
					AddError("不当な演算子エラー5");
					return 0;
					break;

				}

				if (dat1 > 32767) dat1 = 32767;
				if (dat1<-32767) dat1 = -32767;

				m_polandStack[stack-2] = SCRIPT_NUMBER | (dat1 & 0xffff);
				stack--;

				continue;
			}

			AddError("存在しにゃいかつかえない演算子です");
			return 0;
		}

		AddError("計算式につかえないものがあります");
		return 0;
	}

	if (stack>1)
	{
		AddError("ポーランド演算スタックがへんです");
		return 0;
	}
//sprintf(m_errorMessageTmp,"[演算結果=%d]\n",ScriptToData(m_polandStack[0]));

	return ScriptToData(m_polandStack[0]);
}


int CExecScript::ScriptToVarNumber(int script)
{
	int shurui = script & 0xffff0000;
	if (shurui != SCRIPT_VAR) return -1;

	return script & 0xffff;
}


int CExecScript::ScriptToData(int script)
{
	int shurui = script & 0xffff0000;
	if (shurui == SCRIPT_VAR)
	{
		int var = ScriptToVarNumber(script);
		if (var == -1) return 0;	//youjin
		if (var & 0x8000) return var & 0x7fff;

		if (var < 100)
		{
			return m_callBack->GetCalcuVarData(var);
		}
		return m_callBack->GetVarData(var);
	}

	if (shurui == SCRIPT_NUMBER)
	{
		int d = script & 0xffff;
		if ((d & 0x8000) != 0)
		{
			d |= 0xffff0000;
		}
		return d;
	}

	if (shurui == SCRIPT_NUMBER32)
	{
		int d = script & 0xffff;
		return GetInt32(d);
	}

	if (shurui == SCRIPT_NUMBER_STACK32)
	{
		int d = script & 0x00ff;
		return m_int32stack[d];
	}

	AddError("変数でも数値でもにゃいのに・・・");
	return 0;	//unknown error
}

/*
int CExecScript::GetNextMessageNumber(void)
{
	int pc = m_pc;
	pc += m_data[pc];

	int script = m_data[pc+1];
	if ((script != COMMAND_PRINT) && (script != COMMAND_LPRINT) && (script != COMMAND_APPEND)) return -1;

	return GetMessageNumber(m_data[pc+2]);
}
*/

void CExecScript::AddError(LPSTR mes)
{

	m_errorFlag = TRUE;
	memcpy(&m_errorMessage[m_errorNum][0],mes,strlen(mes)+1);

	if (m_errorCount<15) m_errorCount++;

	m_errorNum++;
	m_errorNum %= 16;
}


int CExecScript::GetErrorKosuu(void)
{
	if (m_errorFlag == FALSE) return 0;

	return m_errorCount;
}

LPSTR CExecScript::GetErrorMessage(int n)
{
	return &m_errorMessage[n & 0xf][0];
}

/*
void CExecScript::GetParameter(int pc)
{
	m_paraKosuu = m_data[pc];
	pc++;

	for (int i=0;i<m_paraKosuu;i++)
	{
		int skp = 0;
		int dat = Enzan(pc,&skp);
		m_paraWork[i] = dat;
		pc += skp;
	}
}
*/



BOOL CExecScript::SearchMessageID(int id)
{
	int pc = 0;
	while (pc < m_dataSize)
	{
		int skp = m_data[pc];
		if (skp == 0) return FALSE;

		int identify = m_data[pc+1];
		int code = m_data[pc+2];

		if (identify == IDENTIFY_SYSTEMCOMMAND)
		{
			if ((code == CODE_SYSTEMCOMMAND_PRINT) || (code == CODE_SYSTEMCOMMAND_LPRINT) || (code == CODE_SYSTEMCOMMAND_APPEND))
			{
				if (m_data[pc+4] == id)
				{
					m_pc = pc;
					m_pc += m_data[m_pc];
					return TRUE;
				}
			}
		}
		pc += skp;
	}
	return FALSE;
}


BOOL CExecScript::SearchSelectID(int id)
{
	int pc = 0;
	while (pc < m_dataSize)
	{
		int skp = m_data[pc];
		if (skp == 0) return FALSE;

		int identify = m_data[pc+1];
		int code = m_data[pc+2];

		if (identify == IDENTIFY_SYSTEMCOMMAND)
		{
			if (code == CODE_SYSTEMCOMMAND_SELECT)
			{
				int kosuu = m_data[pc+3];
				
				if ((kosuu + 5) != skp)	//new data version
				{
					kosuu += m_data[pc+skp-1];
				}

				if (m_data[pc+4+kosuu] == id)
				{
					m_pc = pc;
					m_pc += m_data[m_pc];
					return TRUE;
				}
			}
		}
		pc += skp;
	}
	
	return FALSE;
}


BOOL CExecScript::ChangeIDToAddr(void)
{
	if (m_dataExistFlag == FALSE)
	{
		return FALSE;
	}

	for (int i=0;i<m_stackPointer;i++)
	{
		int id = m_stack[i];
		int pc = m_data[m_subCallPointer+id];
		m_ID[i] = id;
		m_stack[i] = pc+m_data[pc];
	}
	return TRUE;
}

BOOL CExecScript::AdjustScriptCall(void)	//253
{
	m_pc = m_data[m_scriptCallPointer+m_stack[253]];
	m_pc += m_data[m_pc];
	return TRUE;
}

BOOL CExecScript::AdjustCommandCall(void)	//254
{
	m_pc = m_data[m_commandCallPointer+m_stack[254]];
	m_pc += m_data[m_pc];
	return TRUE;
}


/*_*/

