/*------------------------------------------------------------------------------
KEY_SKIP_FAILURE_REPEATS!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/skip_failure.h"
#include "../common/key_char_blocked.h"



//                                            0123456789ABCDEF
static char const       szMessage1[]       = "  ������� ���   ",
                        szMessage2[]       = "������� ��������",
                        szMessage3[]       = "  �����������   ",
                        szMessage4[]       = "   ���������    ";

static char const       *pszMessages[]     = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetSkipFailureRepeats(void)
{
  key_SetCharBlocked(&chSkipFailureRepeats, pszMessages, 1, 5, fSkipFailureEnbl, wSET_SKIP_FAILURE_ENBL);
}
