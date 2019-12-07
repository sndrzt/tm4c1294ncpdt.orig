/*------------------------------------------------------------------------------
key_test_auto_flow.c

 
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_flow.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "key_test_auto_flow.h"




//                                         0123456789ABCDEF
static char const       szTestFlow[]    = "������� 2       ";



void    key_TestAutoFlow(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szTestFlow);
      Clear();
    }
  }
}


void    auto_TestAutoFlow(void)
{
static uchar cbFlowDelayPrev;

  if (enKeyboard == KBD_POSTENTER)
  {
    Hi(14, cbFlowDelay);

    if (ibFlowPortFrom == 0)
    {
      Lo(0,  cbInFlow0);
      Lo(3,  iwInFlow0 / 0x100);
      Lo(5,  iwInFlow0 % 0x100);

      Lo(9,  cbOutFlow0);
      Lo(12, iwOutFlow0 / 0x100);
      Lo(14, iwOutFlow0 % 0x100);
    }

    if (ibFlowPortFrom == 1)
    {
      Lo(0,  cbInFlow1);
      Lo(3,  iwInFlow1 / 0x100);
      Lo(5,  iwInFlow1 % 0x100);

      Lo(9,  cbOutFlow1);
      Lo(12, iwOutFlow1 / 0x100);
      Lo(14, iwOutFlow1 % 0x100);
    }

    if ((cbFlowDelayPrev > 0) && (cbFlowDelay == 0))
    {
      bKey = 0x07;//bKEY_PROGRAM;
      fKey = true;
    }

    cbFlowDelayPrev = cbFlowDelay;
  }
}
