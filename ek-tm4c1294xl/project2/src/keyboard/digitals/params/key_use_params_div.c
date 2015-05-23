/*------------------------------------------------------------------------------
KEY_USE_PARAMS_DIV,C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../key_bool.h"



//                                           0123456789ABCDEF
static char const       szMessage1[]      = "  ������������  ",
                        szMessage2[]      = "����������� P104",
                        szMessage3[]      = "  ��� �������   ",
                        szMessage4[]      = "    CRC52 ?     ";

static char const       *pszMessages[]    = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetUseParamsDiv(void)
{
  key_SetBool(&flUseParamsDiv, pszMessages);
}
