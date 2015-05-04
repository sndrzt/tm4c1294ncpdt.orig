/*------------------------------------------------------------------------------
KEY_FIX_PARAMS_BUGS.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../key_bool.h"



//                                           0123456789ABCDEF
static char const       szFixParamBugs1[] = "   ����������   ",
                        szFixParamBugs2[] = "   ������ ���   ",
                        szFixParamBugs3[] = "     ������     ",
                        szFixParamBugs4[] = "  ���������� ?  ";

static char const       *pszFixParamsBugs[] = { szFixParamBugs1, szFixParamBugs2, szFixParamBugs3, szFixParamBugs4, "" };



void    key_SetFixParamsBugs(void)
{
  key_SetBool(&flFixParamsBugs, pszFixParamsBugs);
}
