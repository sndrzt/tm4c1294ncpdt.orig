/*------------------------------------------------------------------------------
KEY_SHORT_PROFILE_C.C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  ������ �����  ",
                        szMessage2[]    = "   ��� ������   ",
                        szMessage3[]    = "     ��-301     ",
                        szTrue[]        = " 1 �������      ",
                        szFalse[]       = " 6 ���������    ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetShortProfileC(void)
{
  key_SetFlag(&chShortProfileC, pszMessages, szTrue, szFalse);
}

