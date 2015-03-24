/*------------------------------------------------------------------------------
KEY_SEPARATE_CAN.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../../digitals/digitals_run.h"
#include        "../key_flag.h"



//                                         0123456789ABCDEF
static char const       szSeparateCan[] = "���������� �����";

static char const       *pszSeparateCan[] = { szSeparateCan, "" };



void    key_SetSeparateCan(void)
{
  key_SetFlag(&flSeparateCan, pszSeparateCan);
}
