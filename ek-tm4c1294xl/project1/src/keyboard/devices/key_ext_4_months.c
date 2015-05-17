/*------------------------------------------------------------------------------
KEY_EXT_4_MONTHS,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../devices/extended_4.h"
#include "../key_char.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " ����� �������  ",
                        szMessage2[]     = "  ��� ��������  ",
                        szMessage3[]     = "����. ��������� ",
                        szMessage4[]     = "   �� ������    ",
                        szMessage5[]     = "   ������� ?    ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szCharLimits, "" };



void    key_SetExt4Months(void)
{
  key_SetChar(&flExt4Months, pszMessages, 1, 12);
}
