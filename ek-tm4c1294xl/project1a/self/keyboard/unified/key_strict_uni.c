/*------------------------------------------------------------------------------
KEY_STRICT_UNI.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../output/unified/uni.h"
#include "../common/key_bool.h"
#include "key_strict_uni.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   ����������   ",
                        szMessage2[]     = "��������� ���� ?";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_SetStrictUni(void)
{
  key_SetBool(&chStrictUni, pszMessages);
}
