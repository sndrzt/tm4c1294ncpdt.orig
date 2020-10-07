/*------------------------------------------------------------------------------
KEY_SHORT_PROFILE_B!C


------------------------------------------------------------------------------*/

#include "../../console.h"
#include "../../devices/devices_init.h"
#include "../common/key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  ������ �����  ",
                        szMessage2[]    = "   ��� ������   ",
                        szMessage3[]    = "  ��������-230  ",
                        szTrue[]        = " 1 �������      ",
                        szFalse[]       = " 16 ���������   ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetShortProfileB(void)
{
  key_SetFlag(&chShortProfileB, pszMessages, szTrue, szFalse);
}
