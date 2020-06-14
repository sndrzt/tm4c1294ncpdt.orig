/*------------------------------------------------------------------------------
KEY_CONTROL_Q.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "�������� �������",
                        szMessage2[]    = "    ��� CE3xx   ",
                        szTrue[]        = " ���������      ",
                        szFalse[]       = " ���������      ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetControlQ(void)
{
  key_SetFlag(&chControlQ, pszMessages, szTrue, szFalse);
}

