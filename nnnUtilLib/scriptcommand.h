//
// scriptcommand.h
//

#if !defined __NNNLIB_SCRIPTCOMMAND__
#define __NNNLIB_SCRIPTCOMMAND__


#define COMMAND_NOP 0
#define COMMAND_IF 1
#define COMMAND_ELSE 2
#define COMMAND_ELSIF 3
#define COMMAND_SUB 4
//#define COMMAND_GOTO 5
#define COMMAND_NEXT 6
#define COMMAND_RETURN 7
#define COMMAND_SELECT 8
#define COMMAND_CASE 9
#define COMMAND_END 10
#define COMMAND_PRINT 11
#define COMMAND_LPRINT 12
#define COMMAND_APPEND 13
#define COMMAND_DRAW 14
//
//
//
#define COMMAND_WHILE 17
//
//...
//
#define COMMAND_GOTO 32




//
//
//
#define FUNCTION_FILE 3
#define FUNCTION_LAYER 4
#define FUNCTION_EFFECT 5
#define FUNCTION_BGM 6
#define FUNCTION_WAVE 7
//
#define FUNCTION_CLEAREFFECT 9
#define FUNCTION_VOICE 10
#define FUNCTION_SOUND 11
#define FUNCTION_CGSAVE 12
#define FUNCTION_SETLAYER 13
#define FUNCTION_MAKECG 14
#define FUNCTION_NOTRANSLAYER 15
//
//
//
#define FUNCTION_ADJUSTDATE 19
//
#define FUNCTION_ENDFLAG 21
//
//...
//
#define FUNCTION_CLEARMESSAGE 28
#define FUNCTION_WINDOWOFF 29
#define FUNCTION_WINDOWON 30
#define FUNCTION_BGMSTOP 31
//
//...
//
#define FUNCTION_FRAMECONTROL 40
#define FUNCTION_SETDEFAULTFRAME 41

#define FUNCTION_DEBUG 66






#define ENZANSHI_NULL 0
#define ENZANSHI_TRUE 1
#define ENZANSHI_FALSE 2
#define ENZANSHI_AND 3
#define ENZANSHI_XOR 4
#define ENZANSHI_OR 5
#define ENZANSHI_SCREEN 6
#define ENZANSHI_BG 7
#define ENZANSHI_HARE 8
#define ENZANSHI_KUMORI 9
#define ENZANSHI_AME 10
#define ENZANSHI_YUKI 11
#define ENZANSHI_HYO 12
#define ENZANSHI_TAIFU 13




#define CALCU_KAKKO 0x01000000
#define CALCU_CALCUEQUAL 0x02000000
#define CALCU_DOUBLE 0x03000000
#define CALCU_COMPARE 0x04000000
#define CALCU_COMPAREEQUAL 0x05000000


//

#define SCRIPT_COMMAND 0x00000000
#define SCRIPT_FUNCTION 0x10000000
//#define SCRIPT_EFFECT 0x20000000

#define SCRIPT_LABEL 0x40000000
#define SCRIPT_PLACELABEL 0x50000000
//#define SCRIPT_INLABEL 0x60000000
#define SCRIPT_DATA 0x70000000
#define SCRIPT_TABLE (SCRIPT_DATA | 0x01000000)
#define SCRIPT_VAR 0x80000000
#define SCRIPT_NUMBER 0x90000000
#define SCRIPT_NUMBER32 0x91000000
#define SCRIPT_NUMBER_STACK32 0x92000000
//これはスクリプト内部での計算用

#define SCRIPT_CALCU 0xa0000000
//#define SCRIPT_DAINYU 0xb0000000	未使用??
#define SCRIPT_MESSAGE 0xc0000000
#define SCRIPT_MESSAGE2 0xd0000000
#define SCRIPT_BEGINEND 0xe0000000



#define SCRIPT_COMMAND_NOP (SCRIPT_COMMAND | COMMAND_NOP)
#define SCRIPT_COMMAND_IF (SCRIPT_COMMAND | COMMAND_IF)
#define SCRIPT_COMMAND_ELSE (SCRIPT_COMMAND | COMMAND_ELSE)
#define SCRIPT_COMMAND_ELSIF (SCRIPT_COMMAND | COMMAND_ELSIF)
#define SCRIPT_COMMAND_SUB (SCRIPT_COMMAND | COMMAND_SUB)
#define SCRIPT_COMMAND_GOTO (SCRIPT_COMMAND | COMMAND_GOTO)
#define SCRIPT_COMMAND_NEXT (SCRIPT_COMMAND | COMMAND_NEXT)
#define SCRIPT_COMMAND_RETURN 1(SCRIPT_COMMAND | COMMAND_RETURN)
#define SCRIPT_COMMAND_SELECT (SCRIPT_COMMAND | COMMAND_SELECT)
#define SCRIPT_COMMAND_CASE (SCRIPT_COMMAND | COMMAND_CASE)
#define SCRIPT_COMMAND_END (SCRIPT_COMMAND | COMMAND_END)
#define SCRIPT_COMMAND_SELECTPLACE (SCRIPT_COMMAND | COMMAND_SELECTPLACE)
#define SCRIPT_COMMAND_SKIPPLACE (SCRIPT_COMMAND | COMMAND_SKIPPLACE)
#define SCRIPT_COMMAND_STAFFROLL (SCRIPT_COMMAND | COMMAND_STAFFROLL)
#define SCRIPT_COMMAND_DEBUG (SCRIPT_COMMAND | COMMAND_DEBUG)
#define SCRIPT_COMMAND_ENDING (SCRIPT_COMMAND | COMMAND_ENDING)
#define SCRIPT_COMMAND_CGWAIT (SCRIPT_COMMAND | COMMAND_CGWAIT)
#define SCRIPT_COMMAND_CGNEXT (SCRIPT_COMMAND | COMMAND_CGNEXT)
#define SCRIPT_COMMAND_CGSCROLL (SCRIPT_COMMAND | COMMAND_CGSCROLL)
#define SCRIPT_COMMAND_SELECTGARDEN (SCRIPT_COMMAND | COMMAND_SELECTGARDEN)
#define SCRIPT_COMMAND_WHILE (SCRIPT_COMMAND | COMMAND_WHILE)

#define SCRIPT_FUNCTION_ADJUSTDATE (SCRIPT_FUNCTION | FUNCTION_ADJUSTDATE)


#define SCRIPT_BEGIN (SCRIPT_BEGINEND | '{')
#define SCRIPT_END (SCRIPT_BEGINEND | '}')


#define SCRIPT_CALCU_ENZAN (SCRIPT_CALCU)
#define SCRIPT_CALCU_KAKKO (SCRIPT_CALCU | CALCU_KAKKO)
#define SCRIPT_CALCU_CALCUEQUAL (SCRIPT_CALCU | CALCU_CALCUEQUAL)
#define SCRIPT_CALCU_DOUBLE (SCRIPT_CALCU | CALCU_DOUBLE)
#define SCRIPT_CALCU_COMPARE (SCRIPT_CALCU | CALCU_COMPARE)
#define SCRIPT_CALCU_COMPAREEQUAL (SCRIPT_CALCU | CALCU_COMPAREEQUAL)


#define SCRIPT_CODE_EQUAL 0x100
// == *= != += -= *= /= %= &= |=     >= <=    etc

//#define SCRIPT_CODE_NOTEQUAL 0x101
//#define SCRIPT_CODE_GREAT 0x102
//#define SCRIPT_CODE_GREATEQUAL 0x103
//#define SCRIPT_CODE_SMALL 0x104
//#define SCRIPT_CODE_SMALLEQUAL 0x105

//#define SCRIPT_CALCU_NOP 0x200
//#define SCRIPT_CALCU_EQUAL 0x201
//#define SCRIPT_CALCU_PLUS 0x202
//#define SCRIPT_CALCU_MINUS 0x203
//#define SCRIPT_CALCU_MULTI 0x204
//#define SCRIPT_CALCU_DEVIDE 0x205
//#define SCRIPT_CALCU_MOD 0x206
//#define SCRIPT_CALCU_AND 0x207
//#define SCRIPT_CALCU_OR 0x208

//#define SCRIPT_CALCU_PLUSEQUAL 0x212
//#define SCRIPT_CALCU_MINUSEQUAL 0x213
//#define SCRIPT_CALCU_MULTIEQUAL 0x214
//#define SCRIPT_CALCU_DEVIDEEQUAL 0x215
//#define SCRIPT_CALCU_MODEQUAL 0x216
//#define SCRIPT_CALCU_ANDEQUAL 0x217
//#define SCRIPT_CALCU_OREQUAL 0x218






#endif
/*_*/


