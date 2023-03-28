/*------------------------------------------------------------------------------
automatic_get_cntmon_41.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../sensor38/device38.h"
#include "../sensor38/io38.h"
#include "../sensor38/dff.h"
#include "automatic_get_time_41.h"
#include "automatic_get_cntmon_41.h"



bool    ReadEngDay41_Full(uchar  ibDayRel)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryEngDay38(0);

    if (Input38() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }

  if (r == MaxRepeats()) return false;


  uchar* pbIn = InBuffPtr(10);

  uchar i;
  for (i=0; i<MAX_LINE_41; i++)
  {
    *(pbIn++);

    int64_t ddw = 0;
    pbIn = DffDecodePositive(pbIn, &ddw);

    uchar bStatus = (ddw % 0x100) & 0x03;
    ulong dw = (ddw >> 3) % 0x100000000;

    if (!GoodStatus38(bStatus)) {
      Clear();
      sprintf(szLo+1, "����� -%u (%u) ?", ibDayRel, bStatus);
      Delay(1000);
      return false;
    }

    mpdwChannelsA[i] = dw;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
  }


  for (i=0; i<MAX_LINE_41; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return true;
}



bool    ReadEngMon41_Full(uchar  ibMonRel)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryEngMon38(ibMonRel);

    if (Input38() == SER_GOODCHECK) break;
    if (fKey == true) return false;
  }


  uchar* pbIn = InBuffPtr(10);

  uchar i;
  for (i=0; i<MAX_LINE_41; i++)
  {
    *(pbIn++);

    int64_t ddw = 0;
    pbIn = DffDecodePositive(pbIn, &ddw);

    uchar bStatus = (ddw % 0x100) & 0x03;
    ulong dw = (ddw >> 3) % 0x100000000;

    if (!GoodStatus38(bStatus)) {
      Clear();
      sprintf(szLo+1, "����� -%u (%u) ?", ibMonRel, bStatus);
      Delay(1000);
      return false;
    }

    mpdwChannelsA[i] = dw;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
  }


  for (i=0; i<MAX_LINE_41; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return true;
}



double2 ReadCntMonCan38(uchar  ibMonAbs)
{
  Clear();

  time2 ti2 = ReadTimeCan38();
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMonAbs+1)
  {
    uchar ibMonRel = (bMONTHS+ti.bMonth-2-ibMonAbs) % bMONTHS;
    if (ReadEngMon41_Full(ibMonRel) == false) return GetDouble2Error();
  }
  else
  {
    if (ReadEngDay41_Full(0) == false) return GetDouble2Error();
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}
