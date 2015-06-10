/*------------------------------------------------------------------------------
 OUT_REALTIME,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_params.h"
#include "../serial/ports.h"
#include "../realtime/realtime.h"
#include "../time/rtc.h"
#include "out_realtime.h"



void    OutRealtime(void)
{
  InitPushCRC();
  uint wSize = 0;

  wSize += PushTime(*GetCurrTimeDate());
  wSize += PushTime(tiCurr);
  wSize += PushTime(tiPrev);

  wSize += PushBool(fSeason);
  wSize += PushBool(fSummer);
  wSize += PushBool(fWinter);

  wSize += PushBool(fActive);

  wSize += PushInt(ibSoftMnt);
  wSize += PushInt(iwHardMnt);
  wSize += PushInt(ibSoftHou);
  wSize += PushInt(iwHardHou);
  wSize += PushInt(ibSoftDay);
  wSize += PushInt(ibHardDay);
  wSize += PushInt(ibSoftMon);
  wSize += PushInt(ibHardMon);
  wSize += PushInt(ibSoftTim);
  wSize += PushInt(iwHardTim);

  wSize += PushLong(cdwSeconds);
  wSize += PushLong(cdwMinutes1);
  wSize += PushLong(cdwMinutes3);
  wSize += PushLong(cdwMinutes30);
  wSize += PushInt(cwDays);
  wSize += PushInt(cwMonths);
  wSize += PushInt(cwYears);

  Output(wSize);
}
