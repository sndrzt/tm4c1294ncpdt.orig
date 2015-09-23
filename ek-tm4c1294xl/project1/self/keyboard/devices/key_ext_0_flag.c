/*------------------------------------------------------------------------------
KEY_EXT_0_FLAG!CS


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../digitals/extended/extended_0.h"
#include "../common/key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   ���������    ",
                        szMessage2[]     = "�������� ����� ?";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_SetExt0Flag(void)
{
  key_SetBool(&chExt0Flag, pszMessages);
}
