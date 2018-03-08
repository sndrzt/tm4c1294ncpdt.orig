/*------------------------------------------------------------------------------
panel.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../hardware/led.h"
#include "../output/response_crc.h"
#include "../output/esc/response_esc.h"
#include "panel.h"



#ifdef NO_DISPLAY

void    RunPanel(void)
{
  RunResponseCRC_All_Panel();
  RunResponseEsc_All_Panel(); // TODO
}


void    RunPanel_Cleaning(void)
{
  RunPanel();
  RunLED_Cleaning();
}

void    RunPanel_CleaningHhr(uint iwHhr)
{
  if ((iwHhr % 0x10) == 0)
  {
    RunPanel_Cleaning();
  }
}

#endif
