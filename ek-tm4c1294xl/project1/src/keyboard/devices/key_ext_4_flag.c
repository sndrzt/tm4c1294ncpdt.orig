/*------------------------------------------------------------------------------
KEY_EXT_4_FLAG,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/extended/extended_4.h"
#include "../key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   ���������    ",
                        szMessage2[]     = "����. ��������� ",
                        szMessage3[]     = "   �� ������    ",
                        szMessage4[]     = "   ������� ?    ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetExt4Flag(void)
{
  key_SetBool(&flExt4Flag, pszMessages);
}
