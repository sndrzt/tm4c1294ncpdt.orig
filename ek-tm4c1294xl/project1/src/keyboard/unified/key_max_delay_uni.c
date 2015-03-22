/*------------------------------------------------------------------------------
KEY_MAX_DELAY_UNI.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../../output/unified/uni.h"
#include        "../key_char.h"


//                                         0123456789ABCDEF
static char const       szMaxDelayUni[] = "  ������� ����  ";

static char const       *pszMaxDelayUni[] = { szMaxDelayUni, szCharLimits, "" };



void    key_SetMaxDelayUni(void)
{
  key_SetChar(&flMaxDelayUni, pszMaxDelayUni, 10, 250);
}
