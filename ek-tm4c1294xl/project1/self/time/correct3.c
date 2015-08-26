/*------------------------------------------------------------------------------
CORRECT3.C

 ('����� � 49 �� 07.09.2009')
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../time/gps.h"
#include "correct1.h"
#include "correct3.h"



cache const             chCorrect3Flag = {CORRECT3_FLAG, &boCorrect3Flag, sizeof(bool)};
cache const             chCorrect3SuccessMax = {CORRECT3_SUCCESS_MAX, &bCorrect3SuccessMax, sizeof(uchar)};
cache const             chCorrect3Total = {CORRECT3_TOTAL, &dwCorrect3Total, sizeof(ulong)};
cache const             chCorrect3Success = {CORRECT3_SUCCESS, &dwCorrect3Success, sizeof(ulong)};



void    InitCorrect3(void)
{
  LoadCacheBool(&chCorrect3Flag,false);
  LoadCacheChar(&chCorrect3SuccessMax, 1, 100, 3);

  LoadCache(&chCorrect3Total);
  LoadCache(&chCorrect3Success);
}


void    ResetCorrect3(void)
{
  boCorrect3Flag = false;
  SaveCache(&chCorrect3Flag);

  bCorrect3SuccessMax = 3;
  SaveCache(&chCorrect3SuccessMax);

  dwCorrect3Total = 0;
  SaveCache(&chCorrect3Total);

  dwCorrect3Success = 0;
  SaveCache(&chCorrect3Success);

  memset(&tiPosCorrect3, 0, sizeof(tiPosCorrect3));
  memset(&tiNegCorrect3, 0, sizeof(tiNegCorrect3));

  memset(&mpcwCorrect3, 0, sizeof(mpcwCorrect3));
}

/*
bit     Correct3Allowed(void)
{
  return (cdwPosCorrect3 < bCorrect3Max);
}
*/

bool    Correct3Disabled(void)
{
//  if ((bPortGPS == 0) || (bPortGPS > bPORTS)) return 0;
//  if (boCorrect3 == false) return 0;
//
//  return !Correct3Allowed();
  return false;
}


void    Correct3(event  ev)
{
  uchar i;
  if ((i = GetCorrectIndex(ev)) == 0) return;

  mpcwCorrect3[0]++;
  mpcwCorrect3[i]++;
}



void    OutCorrect3(void)
{
  InitPushCRC();

  uchar i;
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();

  PushBool(UseGps());
  PushBool(boCorrect3Flag);
  PushLong(dwCorrect3Total);
  PushLong(dwCorrect3Success);
  PushChar(bCorrect3SuccessMax);
  PushTime(tiPosCorrect3);
  PushTime(tiNegCorrect3);
  PushBool(Correct3Disabled());
  Push(&mpcwCorrect3, sizeof(mpcwCorrect3)); // TODO

  Output(100);
}
