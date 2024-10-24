/*------------------------------------------------------------------------------
REALTIME_SPEC!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_settings.h"
#include "../time/rtc.h"
#include "../hardware/watchdog.h"
#include "realtime.h"
#include "next_minute3.h"
#include "next_minute30.h"
#include "realtime_spec.h"



static void ProcessTimeMnt(void)
{
  // ������� �� ��������� ��� ������
  if ((tiCurr.bMinute % 3 == 0) && (tiPrev.bMinute % 3 != 0))
  {
  	NextMinute3();
    fCurrent = 1;
  }

  // ������� �� ��������� �������� �����
  if ((tiCurr.bMinute % 30 == 0) && (tiPrev.bMinute % 30 != 0))
  {
  	NextMinute30();
    bHhrInc++;
  }
}


void    NexttimeMnt(void)
{
  ResetWatchdog();

  if (GetLabelRTC() == false) return;

  time ti = *GetCurrTimeDate();
  if (ValidTimeDateRTC(ti) == false) return;

  if (tiCurr.bSecond != ti.bSecond)
  {
    tiCurr = ti;

    if (enGlobal != GLB_PROGRAM)
      ProcessTimeMnt();

    tiPrev = tiCurr;
  }
}
