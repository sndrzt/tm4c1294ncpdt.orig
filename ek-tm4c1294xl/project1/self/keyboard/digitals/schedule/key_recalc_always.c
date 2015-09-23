/*------------------------------------------------------------------------------
KEY_RECALC_ALWAYS!C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_schedule.h"
#include "../../../digitals/schedule/schedule.h"
#include "../../common/key_bool.h"



  //                                         0123456789ABCDEF
static char const       szRecalcAlways1[] = " ������ ������  ",
                        szRecalcAlways2[] = "~������/��������";


static char const       *pszRecalcAlways[] = { szRecalcAlways1, szRecalcAlways2, "" };



void    key_SetRecalcAlways(void)
{
  key_SetBool(&chRecalcAlways, pszRecalcAlways);
}
