/*------------------------------------------------------------------------------
KEY_ENBL_WDT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_program.h"
#include "../settings.h"
#include "common/key_bool.h"
#include "key_enbl_wdt.h"



//                                          0123456789ABCDEF
static char const       szMessage[]      = "���������� WDT ?";

static char const       *pszMessages[]   = { szMessage, "" };



void    key_SetEnblWDT(void)
{
  key_SetBool(&chEnblWDT, pszMessages);
}
