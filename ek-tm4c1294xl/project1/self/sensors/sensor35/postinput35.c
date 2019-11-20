/*------------------------------------------------------------------------------
POSTINPUT35!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_profile.h"
//#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
//#include "../../time/timedate.h"
#include "../../hardware/watchdog.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/input_wrapper.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
//#include "../../digitals/digitals.h"
#include "../../digitals/digitals_status.h"
#include "../../digitals/wait_answer.h"
#include "unpack35.h"
#include "device35.h"
#include "automatic35.h"
#include "io35.h"
#include "timer35.h"
#include "timeout35.h"
#include "status35.h"
#include "postinput35.h"



#ifndef SKIP_35

void    PostInput35(void)
{
    if (InBuff(7) == NNCL2_TIME)
    {
      uint w = GetTimer35();
      //Clear(); sprintf(szLo+2,"��������: %u",w);
      sprintf(szHi+10,"%2u",w);
      Delay(300); // Inf
      MonitorString("\n repeat: start");

      cbRepeat = MaxRepeats();
      Query35Internal(250, 0, NNCL2_DATA_GET);
      SetCurr(DEV_DATAGET_35);

      return;
    }
    else if (InBuff(7) == NNCL2_DATA_GET)
    {
      TimeoutHistogram35(GetTimer35());

      if (IndexInBuff() < 15)
      {
        Clear(); sprintf(szLo+1,"����� ? %u",IndexInBuff());
        MonitorString("\n sensor error: bad size "); MonitorIntDec(IndexInBuff());
        Delay(1000); // Inf
      }
      else
      {
        uchar i;
        for (i=0; i<IndexInBuff()-15; i++)
          SetInBuff(i, InBuff(12+i));

        MonitorString("\n unwrap finished");
        MonitorIn();

        if (Checksum35Sensor() == 0)
        {
          MonitorString("\n sensor success");

          InputGoodCheck();
          mpSerial[ibPort] = SER_GOODCHECK;
          return;
        }
      }
    }
    else if (InBuff(7) == NNCL2_ERROR)
    {
      Clear(); sprintf(szLo+1,"������ ? %u",InBuff(8));
      MonitorString("\n router error: "); MonitorCharDec(InBuff(8));
      Delay(1000); // Inf
    }
    else
    {
      Clear(); sprintf(szLo+1,"������� ? %u",InBuff(7));
      MonitorString("\n router unknown command: "); MonitorCharDec(InBuff(7));
      Delay(1000); // Inf
    }

  mpSerial[ibPort] = SER_BADCHECK;
}

#endif
