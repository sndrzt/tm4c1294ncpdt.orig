/*------------------------------------------------------------------------------
KEY_PROFILE_INTERVAL!C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "����������������",
                        szMessage2[]    = "     �����      ",
                        szMessage3[]    = "  ��� ��������  ",
                        szMessage4[]    = " ����� �������  ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetProfileInterval(void)
{
  key_SetBool(&chProfileInterval, pszMessages);
}
