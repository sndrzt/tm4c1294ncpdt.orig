/*------------------------------------------------------------------------------
PROFILE34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../digitals/digitals.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../special/special.h"
#include "../../digitals/profile/profile_frac8.h"
#include "../../time/calendar.h"
#include "../../time/unix_time.h"
#include "../../display/display.h"
#include "unix_time_gmt34.h"
#include "profile34.h"



#ifndef SKIP_34

static  uchar           ibJournal34;
static  time            tiProfile34;
static  uchar           ibDay34;
static  uint            iwProfile34;
static  uint            cwOffline;



void    InitProfileOpen34(void)
{
  ibJournal34 = diCurr.ibLine / 4;
  tiProfile34 = tiCurr;
  ibDay34 = 0;
  cwOffline = 0;
}


void    QueryProfileOpen34(void)
{
  time ti1 = DayIndexToDate(DateToDayIndex(tiProfile34) - ibDay34);
  time ti2 = DayIndexToDate(DateToDayIndex(ti1)         + 1);

  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x6B);
  PushChar(0);
  PushChar(ibJournal34);
  PushLongLtl(TimeToUnixTime(ti1));
  PushLongLtl(TimeToUnixTime(ti2));

  QueryIO(3+1+2, 1+11+2);
}



void    InitProfileRead34(void)
{
  iwProfile34 = 0;
}


void    QueryProfileRead34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x6B);
  PushChar(1);
  PushChar(ibJournal34);
  PushChar(iwProfile34 % 0x100);
  PushChar(iwProfile34 / 0x100);

  QueryIO(1000, 1+5+2);
}


bool    ReadProfileRead34(void)
{
  InitPop(4);

  uint wCount = PopIntLtl();
  if (wCount == 0) {
    sprintf(szLo," ���������: %-2u  ",++cwOffline);
  } else {
    cwOffline = 0;
  }

  iwProfile34 = PopIntLtl();

  uchar j;
  for (j=0; j<wCount; j++)
  {
    uchar k;
    for (k=0; k<4; k++)
    {
      uchar i = ibJournal34*4 + k;

      long dw = PopLongLtl();
      mpdbEngFracDigCan8[ibDig][i] += (double)dw/100;

      uint w = (uint)(mpdbEngFracDigCan8[ibDig][i]);
      mpwChannels[i] = w;

      mpdbEngFracDigCan8[ibDig][i] -= (double)w;
    }

    time tm = UnixTimeToTimeFromGMT34(PopLongLtl());
    sprintf(szLo," %02u:%02u %02u.%02u.%02u", tm.bHour,tm.bMinute, tm.bDay,tm.bMonth,tm.bYear);

    SearchDefHouIndex(tm);

    MakeSpecial(tm);

    uint w1 = PopIntLtl();
    uint w2 = PopIntLtl();
  }

  SaveProfileFrac8(ibDig);

  if (wCount > 0)
    return 1;
  else
    return 0;
}



void    QueryProfileClose34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x6B);
  PushChar(2);
  PushChar(ibJournal34);

  QueryIO(3+1+2, 1+3+2);
}


bool    ReadProfileClose34(void)
{
  ShowProgressDigHou();

  ibDay34++;

  if (cwOffline > 30)
    return 0;
  else
    return MakeStopHou(0);
}



bool    ActualLine34(uchar  ibDig, uchar  ibCan)
{
  return ((GetDigitalDevice(ibDig) != 34) ||
          (GetDigitalLine(ibDig) / 4 == GetDigitalLine(ibCan) / 4));
}

#endif
