/*------------------------------------------------------------------------------
KEY_ENBL_KEYS,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/digitals.h"
#include "../key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "������ ?        ";

static char const       *pszMessages[]  = { szMessage, "" };



void    key_SetEnblKeys(void)
{
  key_SetBool(&flEnblKeys, pszMessages);
}
