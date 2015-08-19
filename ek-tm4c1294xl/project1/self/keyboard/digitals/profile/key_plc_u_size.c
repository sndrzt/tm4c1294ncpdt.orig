/*------------------------------------------------------------------------------
KEY_PLC_U_SIZE,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../../devices/devices_init.h"
#include "../key_char_blocked.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = " ����� �������  ",
                        szMessage2[]     = "  ��� ��������  ",
                        szMessage3[]     = "����. ��������� ",
                        szMessage4[]     = "   �� ������    ",
                        szMessage5[]     = "   ������� ?    ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szCharLimits, "" };



void    key_SetPlcUSize(void)
{
  key_SetCharBlocked(&chExt4Months, pszMessages, 1, 12, fExt4Flag, bSET_EXT4_FLAG);
}
