/*------------------------------------------------------------------------------
KEY_PLC_U_SHUTDOWN,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../devices/devices_init.h"
#include "../key_int_blocked.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "����� ����������",
                        szMessage2[]     = "   ���������    ",
                        szMessage3[]     = "   ��� ������   ",
                        szMessage4[]     = "    ��������    ",
                        szMessage5[]     = "��������� ��301 ",
                        szMessage6[]     = " �� ������. PLC ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szMessage6, szCharLimits, "" };



void    key_SetPlcUShutdown(void)
{
  key_SetIntBlocked(&chPlcUShutdown, pszMessages, 10, 500, boPlcUFlag, wSET_PLC_U_FLAG);
}
