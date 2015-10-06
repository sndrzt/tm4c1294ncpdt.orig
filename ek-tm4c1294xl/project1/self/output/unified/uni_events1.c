/*------------------------------------------------------------------------------
UNI_EVENTS1,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../include/flash.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "../../time/calendar.h"
#include "../../time/rtc.h"
#include "response_uni.h"
#include "uni_events0.h"
#include "uni_events1.h"



void    IncEventsCount(uint  i)
{
  i = 6+1+2+2+i*4;
  uint w = 0x100*OutBuff(i+0)+OutBuff(i+1);
  w++;
  SetOutBuff(i+0, w / 0x100);
  SetOutBuff(i+1, w % 0x100);
}


void    PushEventsCounts(void)
{
  MonitorString("\n\n get events table ");
  MonitorString(" index "); MonitorIntDec(0x100*bInBuff8+bInBuff9); MonitorString(" count "); MonitorIntDec(0x100*bInBuffA+bInBuffB);

  time ti = *GetCurrTimeDate();
  ulong dw1 = DateToDayIndex(ti);

  bool f = 0;

  uint iwPage;
  for (iwPage=0; iwPage<GetPagesCount(bInBuff7); iwPage++)
  {
    LoadEventsPage(bInBuff7, iwPage);

    uchar ibBlock;
    for (ibBlock=bRECORD_BLOCK; ibBlock>0; ibBlock--)
    {
      ti = ReadEventBlock(ibBlock);

      MonitorString(" countdown "); MonitorIntDec(bRECORD_BLOCK*iwPage + (bRECORD_BLOCK-ibBlock)); MonitorIntDec(GetRecordsCount(bInBuff7) + bRECORD_BLOCK);
      if (bRECORD_BLOCK*iwPage + (bRECORD_BLOCK-ibBlock) > GetRecordsCount(bInBuff7) + bRECORD_BLOCK)
      {
        MonitorString(" exit ");
        return;
      }
      else
      {
        ulong dw2 = DateToDayIndex(ti);
        MonitorString(" delta "); MonitorLongDec(dw1); MonitorString("-"); MonitorLongDec(dw2); MonitorString("="); MonitorLongDec(dw1 - dw2);

        if ((f == 0) && (dw1 >= dw2))
        {
          if (dw1 - dw2 >= 0x100*bInBuff8+bInBuff9)
          {
            MonitorString(" start ");
            f = 1;
          }
        }

        if (f == 1)
        {
          MonitorString(" add ");
          IncEventsCount(dw1 - dw2);

          if (dw1 - dw2 >= (0x100*bInBuff8+bInBuff9) + (0x100*bInBuffA+bInBuffB))
          {
            MonitorString(" stop ");
            return;
          }
        }
      }
    }
  }

  MonitorString("\n failure");
}


void    GetEventsCountsUni(void)
{
  if (bInBuff6 != 0)
    Result2_Info(bUNI_BADDATA,1);
  else if ((bInBuff7 < 1) || (bInBuff7 > 3))
    Result2_Info(bUNI_BADDATA,2);
  else if (0x100*bInBuffA+bInBuffB == 0)
    Result2_Info(bUNI_BADDATA,3);
  else
  {
    InitPushUni();

    PushChar(bInBuff7);
    PushIntBig(GetMaxRecordsCount(bInBuff7));
    PushIntBig(GetRecordsCount(bInBuff7));

    time ti = *GetCurrTimeDate();
    ulong dw = DateToDayIndex(ti);

    uint i;
    for (i=0; i<0x100*bInBuffA+bInBuffB; i++)
    {
      PushIntBig(0);
      PushChar(ti.bDay);
      PushChar(ti.bMonth);

      ti = DayIndexToDate(--dw);
    }

    PushEventsCounts();

    Output2(1+2+2+(0x100*bInBuffA+bInBuffB)*4);
  }
}
