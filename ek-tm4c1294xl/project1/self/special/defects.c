/*------------------------------------------------------------------------------
DEFECTS!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../time/timedate.h"
#include "../time/rtc.h"
#include "defects.h"



void    MakeDefectDay(uchar  ibDay, time  ti)
{
  ti.bHour   = 0;
  ti.bMinute = 0;
  ti.bSecond = 0;

  mpdeDay[ (bDAYS + ibHardDay - ibDay) % bDAYS ] = ti;
}


void    MakeDefectMon(uchar  ibMon, time  ti)
{
  ti.bDay    = 1;
  ti.bHour   = 0;
  ti.bMinute = 0;
  ti.bSecond = 0;

  mpdeMon[ (bMONTHS + ibHardMon - ibMon) % bMONTHS ] = ti;
}



void    MakeAllDefects(const time  ti)
{
  ASSERT(ValidTimeDateRTC(ti));

  time ti1 = ti;

  uchar d;
  for (d=0; d<bDAYS; d++)
  {
    MakeDefectDay(d, ti1);

    if (ti1.bDay > 1)
      ti1.bDay--;
    else
    {
      if (ti1.bMonth > 1)
        ti1.bMonth--;
      else
      {
        ti1.bMonth = 12;
        ti1.bYear--;
      }
      ti1.bDay = GetDaysInMonthYM(ti1.bYear, ti1.bMonth);
    }
  }

  time ti2 = ti;

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    MakeDefectMon(m, ti2);

    if (ti2.bMonth > 1)
      ti2.bMonth--;
    else
    {
      ti2.bMonth = 12;
      ti2.bYear--;
    }
  }
}



void    InitDefects_Custom(void)
{
  if (enGlobal == GLB_PROGRAM)
  {
    memset(&mpdeDay, 0, sizeof(mpdeDay));
    memset(&mpdeMon, 0, sizeof(mpdeMon));
  }
  else
  {
    MakeAllDefects(tiCurr);
  }
}


void    StartDefects(void)
{
  MakeAllDefects(*GetCurrTimeDate());
}
