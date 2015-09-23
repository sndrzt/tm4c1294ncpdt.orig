/*------------------------------------------------------------------------------
KEY_MAX_FLOW_DELAY!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_flow.h"
#include "../../serial/flow.h"
#include "../common/key_char.h"


//                                          0123456789ABCDEF
static char const       szMaxFlowDelay[] = "�������: �������";

static char const       *pszMaxFlowDelay[] = { szMaxFlowDelay, szNumberLimits, "" };



void    key_SetMaxFlowDelay(void)
{
  key_SetChar(&chMaxFlowDelay, pszMaxFlowDelay, 1, 255);
}
