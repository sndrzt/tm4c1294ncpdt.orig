/*------------------------------------------------------------------------------
key_recalc3.c


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/schedule/schedule.h"
#include "../../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "   ����������   ",
                        szMessage2[]    = " ����. �������� ",
                        szMessage3[]    = "�� ������� �����",
                        szMessage4[]    = " ����� �������  ",
                        szMessage5[]    = "30-���. ������ ?";


static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, "" };



void    key_SetRecalc3(void)
{
  key_SetBool(&chRecalcMaxPowCurrDay, pszMessages);
}
