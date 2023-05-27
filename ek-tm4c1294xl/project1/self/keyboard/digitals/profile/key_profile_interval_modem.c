/*------------------------------------------------------------------------------
key_profile_interval_modem.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../devices/devices_init.h"
#include "../common/key_char_blocked.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "    �������     ",
                        szMessage3[]     = "  �� ��������   ",
                        szMessage4[]     = " ����� �������  ";
                        szMessage4[]     = "�� ������ ����� ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetProfileIntervalDirect(void)
{
  key_SetCharBlocked(&chProfileIntervalDirect, pszMessages, 1, 250, boProfileInterval, wSET_PROFILE_INTERVAL);
}
