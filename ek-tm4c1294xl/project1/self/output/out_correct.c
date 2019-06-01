/*------------------------------------------------------------------------------
OUT_CORRECT,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_correct1.h"
#include "../serial/ports.h"
#include "../time/rtc.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../time/calendar2.h"
#include "../time/correct1.h"
#include "../time/correct2.h"
#include "../time/correct3.h"
#include "../flash/records.h"
#include "../nvram/cache.h"
#include "out_correct.h"



void    OutCorrect1(void)
{
  if (Correct2Disabled()) { Correct2(EVE_INQ_CORRECT1); LongResult(bRES_BADACCESS); }
  if (Correct3Disabled()) { Correct3(EVE_INQ_CORRECT1); LongResult(bRES_BADCORRECTION); }

  if (CorrectTime_Full(EVE_INQ_CORRECT1) == 1)
    LongResult(bRES_OK);
  else
    LongResult(bRES_BADMODE);
}


void    OutCorrect2(void)
{
  if (Correct2Disabled()) { Correct2(EVE_INQ_CORRECT2); LongResult(bRES_BADACCESS); }
  if (Correct3Disabled()) { Correct3(EVE_INQ_CORRECT2); LongResult(bRES_BADCORRECTION); }

  CorrectTime_Full(EVE_INQ_CORRECT2);
}


void    OutCorrect3(void)
{
  InitPushCRC();
  PushIntBig(Correct1.mpwPosValueCurr[0]);
  PushIntBig(Correct1.mpwNegValueCurr[0]);
  Output(4);
}


void    OutCorrect4(void)
{
  if (Correct2Disabled()) { Correct2(EVE_INQ_CORRECT4); LongResult(bRES_BADACCESS); }
  if (Correct3Disabled()) { Correct3(EVE_INQ_CORRECT4); LongResult(bRES_BADCORRECTION); }

  time ti;
  ti.bSecond = bInBuff5;
  ti.bMinute = bInBuff6;
  ti.bHour   = bInBuff7;
  ti.bDay    = tiCurr.bDay;
  ti.bMonth  = tiCurr.bMonth;
  ti.bYear   = tiCurr.bYear;
  time ti2 = ti;

  ulong dwSecI = TimeToSecIndex(ti);
  ulong dwSecC = TimeToSecIndex(tiCurr);

  if (dwSecI > dwSecC)
  {
    ulong dw = dwSecI - dwSecC; // ��������� ������� ������

    if (dw < wMAXCORRECT)
    {
      if (TimeToHouIndex(ti) != TimeToHouIndex(tiCurr))
      {
        ti2 = HouIndexToDate(DateToHouIndex(tiCurr) + 1);
        ti2 = SecIndexToDate(DateToSecIndex(ti2) - 1);

        dwSecI = TimeToSecIndex(ti2);
        dw = dwSecI - dwSecC;
      }

      tiRecordTime = ti;
      tiRecordTime2 = ti2;
      AddKeyRecord(EVE_INQ_CORRECT4);
      SetCurrTime(ti2);
      tiPrev = ti2;
      AddKeyRecord(EVE_TIME_OK);

      uchar i = GetCorrectIndex(EVE_INQ_CORRECT4);

      Correct1.mpwNegValueCurr[0] += (uint)dw;
      Correct1.mpwNegValueCurr[i] += (uint)dw;
      Correct1.mpwNegCountCurr[0]++;
      Correct1.mpwNegCountCurr[i]++;

      SaveCache(&chCorrect1);

      LongResult(bRES_OK);
    }
    else LongResult(bRES_BADDATA);
  }
  else
  {
    ulong dw = dwSecC - dwSecI; // ��������� ������� �����

    if (dw < wMAXCORRECT)
    {
      if (TimeToHouIndex(ti) != TimeToHouIndex(tiCurr))
      {
        ti2 = HouIndexToDate(DateToHouIndex(tiCurr));
        ti2 = SecIndexToDate(DateToSecIndex(ti2) + 1);

        dwSecI = TimeToSecIndex(ti2);
        dw = dwSecC - dwSecI;
      }

      tiRecordTime = ti;
      tiRecordTime2 = ti2;
      AddKeyRecord(EVE_INQ_CORRECT4);
      SetCurrTime(ti2);
      tiPrev = ti2;
      AddKeyRecord(EVE_TIME_OK);

      uchar i = GetCorrectIndex(EVE_INQ_CORRECT4);

      Correct1.mpwPosValueCurr[0] += (uint)dw;
      Correct1.mpwPosValueCurr[i] += (uint)dw;
      Correct1.mpwPosCountCurr[0]++;
      Correct1.mpwPosCountCurr[i]++;

      SaveCache(&chCorrect1);

      LongResult(bRES_OK);
    }
    else LongResult(bRES_BADDATA);
  }
}


/*
void    OutCorrectExt1(void)
{
  if (Correct2Disabled()) { Correct2(EVE_EXT_CORRECT2); Result(bRES_BADACCESS); return; }
  if (Correct3Disabled()) { Correct3(EVE_EXT_CORRECT2); Result(bRES_BADCORRECTION); return; }

  InitPop(6);

  time ti;
  Pop(&ti, sizeof(time));

  if (ValidTimeDate(ti) == true)
  {
    SetCurrTimeDate(ti);
    Result(bRES_OK);
  }
  else Result(bRES_BADDATA);
}
*/


void    OutCorrectExt2(void)
{
  if (Correct2Disabled()) { Correct2(EVE_EXT_CORRECT2); Result(bRES_BADACCESS); return; }
  if (Correct3Disabled()) { Correct3(EVE_EXT_CORRECT2); Result(bRES_BADCORRECTION); return; }

  InitPop(6);

  time ti;
  Pop(&ti, sizeof(time));

  if (ValidTimeDate(ti) == true)
  {
    if ((tiCurr.bDay   != ti.bDay)   ||
        (tiCurr.bMonth != ti.bMonth) ||
        (tiCurr.bYear  != ti.bYear))
      Result(bRES_BADMODE);
    else if ((tiCurr.bHour*2 + tiCurr.bMinute/30) != (ti.bHour*2 + ti.bMinute/30))
      Result(bRES_BADMODE);
    else
    {
      SetCurrTime_Full(ti, EVE_EXT_CORRECT2);
      Result(bRES_OK);
    }
  }
  else Result(bRES_BADDATA);
}



void    OutCorrectExt20(void)
{
  if (Correct3Disabled()) { Correct3(EVE_EXT_CORRECT2); Result(bRES_BADCORRECTION); return; }

  InitPop(6);

  time ti;
  Pop(&ti, sizeof(time));

  if (ValidTimeDate(ti) == true)
  {
    if ((tiCurr.bDay   != ti.bDay)   ||
        (tiCurr.bMonth != ti.bMonth) ||
        (tiCurr.bYear  != ti.bYear))
      Result(bRES_BADMODE);
    else if ((tiCurr.bHour*2 + tiCurr.bMinute/30) != (ti.bHour*2 + ti.bMinute/30))
      Result(bRES_BADMODE);
    else
    {
      if (Correct2Allowed())
      {
        SetCurrTime_Full(ti, EVE_EXT_CORRECT2);
        Result(bRES_OK);
      }
      else Result(bRES_BADACCESS);
    }
  }
  else Result(bRES_BADDATA);
}
