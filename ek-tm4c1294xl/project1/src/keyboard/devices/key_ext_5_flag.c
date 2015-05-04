/*------------------------------------------------------------------------------
KEY_EXT_5_FLAG,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../devices/extended_5.h"
#include "../key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   ���������    ",
                        szMessage2[]     = "����. ��������� ",
                        szMessage3[]     = "  �� ������� ?  ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetExt5Flag(void)
{
  key_SetBool(&flExt5Flag, pszMessages);
}
