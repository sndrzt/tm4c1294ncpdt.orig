/*------------------------------------------------------------------------------
KEY_ENBL_CURRENT.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/profile/profile_core.h"
#include "../key_flag.h"



//                                         0123456789ABCDEF
static char const       szEnbl[]        = "   ���������    ",
                        szCurrent[]     = " 3-���. ������ ?";

static char const       *pszEnblCurrent[] = { szEnbl, szCurrent, "" };



void    key_SetEnblCurrent(void)
{
  key_SetBool(&flEnblCurrent, pszEnblCurrent);
}
