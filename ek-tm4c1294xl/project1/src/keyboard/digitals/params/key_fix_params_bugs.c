/*------------------------------------------------------------------------------
KEY_FIX_PARAMS_BUGS.C


------------------------------------------------------------------------------*/

#include        "../../../main.h"
#include        "../../../digitals/params/params.h"
#include        "../../key_flag.h"



//                                           0123456789ABCDEF
static char const       szFixParamBugs1[] = "   ����������   ",
                        szFixParamBugs2[] = "   ������ ���   ",
                        szFixParamBugs3[] = "     ������     ",
                        szFixParamBugs4[] = "  ���������� ?  ";

static char const       *pszFixParamsBugs[] = { szFixParamBugs1, szFixParamBugs2, szFixParamBugs3, szFixParamBugs4, "" };



void    key_SetFixParamsBug(void)
{
  key_SetFlag(&flFixParamsBugs, pszFixParamsBugs);
}
