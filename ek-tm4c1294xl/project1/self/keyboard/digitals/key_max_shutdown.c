/*------------------------------------------------------------------------------
KEY_MAX_SHUTDOWN.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/max_shutdown.h"
#include "../common/key_int.h"



//                                            0123456789ABCDEF
static char const       szMessage1[]       = "  ������������  ",
                        szMessage2[]       = "     �����      ",
                        szMessage3[]       = "   ����������   ",
                        szMessage4[]       = "   ���������    ",
                        szMessage5[]       = "  (���������)   ";

static char const       *pszMessages[]     = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szNumberLimits, "" };



void    key_SetMaxShutdown(void)
{
  key_SetInt(&chMaxShutdown, pszMessages, 48, 480);
}
