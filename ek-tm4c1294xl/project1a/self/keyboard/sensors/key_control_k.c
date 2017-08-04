/*------------------------------------------------------------------------------
KEY_CONTROL_K.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "�������� �������",
                        szMessage2[]    = "  ��� ��6850�   ",
                        szTrue[]        = " ���������      ",
                        szFalse[]       = " ���������      ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetControlK(void)
{
  key_SetFlag(&chControlK, pszMessages, szTrue, szFalse);
}

