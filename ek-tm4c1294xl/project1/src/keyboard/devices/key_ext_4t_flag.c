/*------------------------------------------------------------------------------
KEY_EXT_4T_FLAG.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../devices/extended_4t.h"
#include "../key_flag.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   ���������    ",
                        szMessage2[]     = "����. ��������� ",
                        szMessage3[]     = "   �� ������    ",
                        szMessage4[]     = "    �������     ",
                        szMessage5[]     = "  �� ������� ?  ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, "" };



void    key_SetExt4TFlag(void)
{
  key_SetFlag(&flExt4TFlag, pszMessages);
}
