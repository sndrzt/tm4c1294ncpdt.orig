/*------------------------------------------------------------------------------
KEY_FIX_PARAMS_BUGS.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../common/key_bool.h"
#include "key_fix_params_bugs.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   ����������   ",
                        szMessage2[]     = "   ������ ���   ",
                        szMessage3[]     = "     ������     ",
                        szMessage4[]     = "  ���������� ?  ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetFixParamsBugs(void)
{
  key_SetBool(&chFixParamsBugs, pszMessages);
}
