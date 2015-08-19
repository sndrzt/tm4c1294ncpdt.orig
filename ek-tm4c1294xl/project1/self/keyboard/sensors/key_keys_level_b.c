/*------------------------------------------------------------------------------
KEY_KEYS_LEVEL_B.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../key_char.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "������� ������� ",
                        szMessage2[]    = "��� ��������-230";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szNumberLimits, "" };



void    key_SetKeysLevelB(void)
{
  key_SetChar(&chKeysLevelB, pszMessages, 1, 2);
}
