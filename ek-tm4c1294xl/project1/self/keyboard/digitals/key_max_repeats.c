/*------------------------------------------------------------------------------
KEY_MAX_REPEATS!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/max_repeats.h"
#include "../common/key_char.h"



//                                            0123456789ABCDEF
static char const       szMessage1[]       = "  ������� ���   ",
                        szMessage2[]       = "������ ���������";

static char const       *pszMessages[]     = { szMessage1, szMessage2, szNumberLimits, "" };



void    key_SetMaxRepeats(void)
{
  key_SetChar(&chMaxRepeats, pszMessages, 1, 20);
}
