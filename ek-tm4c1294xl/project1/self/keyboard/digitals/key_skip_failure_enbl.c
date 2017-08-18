/*------------------------------------------------------------------------------
KEY_SKIP_FAILURE_ENBL,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/skip_failure.h"
#include "../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "������� ������� ",
                        szMessage2[]    = "  �����������   ",
                        szMessage3[]    = "   ���������    ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetSkipFailureEnbl(void)
{
  key_SetBool(&chSkipFailureEnbl, pszMessages);
}
