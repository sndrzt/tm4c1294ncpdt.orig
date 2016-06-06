/*------------------------------------------------------------------------------
review_warning.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/monitor.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "review.h"
#include "review_core.h"
#include "review_buff.h"
#include "review_warning.h"



//                                         0123456789ABCDEF
static char const       szZero[]        = "   �������� ?   ",
                        szRepeat[]      = "    ������ ?    ",
                        szTop[]         = "    ������ ?    ",
                        szTrendTop[]    = " ��������� %3u%% ",
                        szTrendBottom[] = " ��������� %3u%% ";



static void Show(char const  *sz)
{
  ShowLo(sz); DelayInf(); Clear();
}

static void ShowTrend(char const  *sz, uint  wPercent)
{
  sprintf(szLo, sz, wPercent); DelayInf(); Clear();
}

static review_wrn WarningCommon2(uint  wPrev, uint  wCurr)
{
  MonitorString(" "); MonitorIntDec(wPrev); MonitorString(" -> "); MonitorIntDec(wCurr);

  if ((wPrev != 0) && (wCurr == 0)) {
    Show(szZero);
    MonitorString(" WARNING: value 0");
    return REVIEW_WRN_ZERO;
  }

  if (wCurr > wReviewWrnTop) {
    Show(szTop);
    MonitorString(" WARNING: value > "); MonitorIntDec(wReviewWrnTop);
    return REVIEW_WRN_TOP;
  }

  ulong dwCurrMax = wPrev*(100 + bReviewWrnTrend) / 100;
  ulong dwCurrMin = wPrev*(100 - bReviewWrnTrend) / 100;

  if ((wPrev != 0) && (wCurr > dwCurrMax)) {
    ulong dwPercent = (ulong)100*wCurr/wPrev - 100;
    ShowTrend(szTrendTop, dwPercent);
    MonitorString(" WARNING: value > "); MonitorLongDec(dwCurrMax); MonitorString(" "); MonitorIntDec(bReviewWrnTrend); MonitorString("%%");
    return REVIEW_WRN_TREND_TOP;
  }

  if ((wPrev != 0) && (wCurr < dwCurrMin)) {
    Show(szTrendBottom);
    MonitorString(" WARNING: value < "); MonitorLongDec(dwCurrMin); MonitorString(" "); MonitorIntDec(bReviewWrnTrend); MonitorString("%%");
    return REVIEW_WRN_TREND_BOTTOM;
  }

  return REVIEW_WRN_OK;
}

static review_wrn WarningRepeats2(uint  wPrev, uint  wCurr)
{
  MonitorString(" "); MonitorIntDec(wPrev); MonitorString(" => "); MonitorIntDec(wCurr);

  if ((wPrev != 0) && (wCurr == wPrev)) {
    Show(szRepeat);
    MonitorString(" WARNING: repeat ?");
    return REVIEW_WRN_REPEAT;
  }

  return REVIEW_WRN_OK;
}


static bool WarningCommon(uint  wPrev, uint  wCurr)
{
  review_wrn rw = WarningCommon2(wPrev, wCurr);
  if (rw != REVIEW_WRN_OK) {
    bMaxRepeats = bReviewBorders;
    fIdRepeat = true;

    mcwReviewWarnings[rw]++;
    return true;
  }

  return false;
}

static bool WarningRepeats(uint  wPrev, uint  wCurr)
{
  review_wrn rw = WarningRepeats2(wPrev, wCurr);
  if (rw != REVIEW_WRN_OK) {
    bMaxRepeats = bReviewBorders;
    fIdRepeat = true;

    mcwReviewWarnings[rw]++;
    return true;
  }

  return false;
}


static bool WarningReviewBuffX6(void)
{
  MonitorString("\n");

  uchar i;
  for (i=0; i<4; i++) {
    if (WarningCommon(PrevReviewInt(5*4+i), CurrReviewInt(0*4+i))) return true;
  }

  uchar j;
  for (j=0; j<6-1; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (WarningCommon(CurrReviewInt(j*4+i), CurrReviewInt((j+1)*4+i))) return true;
    }
  }

  for (j=0; j<6; j++) {
    MonitorString("\n");

    uchar i;
    for (i=0; i<4; i++) {
      if (WarningRepeats(PrevReviewInt(j*4+i), CurrReviewInt(j*4+i))) return true;
    }
  }

  return false;
}

static bool WarningReviewBuffX1(void)
{
  MonitorString("\n");

  uchar i;
  for (i=0; i<4; i++) {
    if (WarningCommon(PrevReviewInt(i), CurrReviewInt(i))) return true;
  }

  MonitorString("\n");

  for (i=0; i<4; i++) {
    if (WarningRepeats(PrevReviewInt(i), CurrReviewInt(i))) return true;
  }

  return false;
}

bool WarningReviewBuff(uchar  bSize)
{
  switch(bSize) {
    case 0: return false;
    case 6: return WarningReviewBuffX6();
    case 1: return WarningReviewBuffX1();
    default: ASSERT(false); return false;
  }
}
