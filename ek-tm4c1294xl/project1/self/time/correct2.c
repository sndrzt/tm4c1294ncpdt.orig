/*------------------------------------------------------------------------------
CORRECT2!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_correct2.h"
#include "../serial/ports.h"
#include "../nvram/cache.h"
#include "correct1.h"
#include "correct2.h"



cache const             chCorrect2Flag = {CORRECT2_FLAG, &boCorrect2Flag, sizeof(bool)};
cache const             chCorrect2Status15 = {CORRECT2_STATUS, &mpcwCorrect2Status15, sizeof(mpcwCorrect2Status15)};



void    InitCorrect2(void)
{
  LoadCache(&chCorrect2Flag);

  LoadCache(&chCorrect2Status15);
}


void    ResetCorrect2(void)
{
  boCorrect2Flag = false;
  SaveCache(&chCorrect2Flag);

  memset(&mpcwCorrect2Status15, 0, sizeof(mpcwCorrect2Status15));
  SaveCache(&chCorrect2Status15);

  memset(&mpbPassCorrect2, 0, sizeof(mpbPassCorrect2));

  cdwCorrect20 = 0;
  cdwCorrect21 = 0;
  cdwCorrect22 = 0;
  cdwCorrect23 = 0;
  cdwCorrect24 = 0;
}



bool    Correct2Disabled(void)
{
  return boCorrect2Flag == true;
}



bool    SuperUserCorrect2(void)
{
  return( (mpbPassCorrect2[0] == 2) &&
          (mpbPassCorrect2[1] == 6) &&
          (mpbPassCorrect2[2] == 1) &&
          (mpbPassCorrect2[3] == 1) &&
          (mpbPassCorrect2[4] == 3) &&
          (mpbPassCorrect2[5] == 7) &&
          (mpbPassCorrect2[6] == 9) &&
          (mpbPassCorrect2[7] == 1) );
}



bool    Correct2Allowed(void)
{
  cdwCorrect20++;

  Pop(mpbPassCorrect2, sizeof(mpbPassCorrect2));
  mpbPassCorrect2[0] ^= 0x45;
  mpbPassCorrect2[1] ^= 0xF6;
  mpbPassCorrect2[2] ^= 0x57;
  mpbPassCorrect2[3] ^= 0x27;
  mpbPassCorrect2[4] ^= 0xE6;
  mpbPassCorrect2[5] ^= 0x16;
  mpbPassCorrect2[6] ^= 0xD6;
  mpbPassCorrect2[7] ^= 0x56;
  mpbPassCorrect2[8] ^= 0xE6;
  mpbPassCorrect2[9] ^= 0x47;

  if (boCorrect2Flag == false) { cdwCorrect21++; return true; }
  if (SuperUserCorrect2()) { cdwCorrect22++; return true; }

  if (memcmp(mpbPassOne, mpbPassCorrect2, 10) == 0)
    { cdwCorrect23++; return true; }
  else
    { cdwCorrect24++; return false; }
}



void    Correct2(event  ev)
{
  uchar i;
  if ((i = GetCorrectIndex(ev)) == 0) return;

  mpcwCorrect2Status15[0]++;
  mpcwCorrect2Status15[i]++;

  SaveCache(&chCorrect2Status15);
}



void    OutCorrectExt21(void)
{
  InitPushCRC();

  uchar i;
  for (i=0; i<100; i++) PushChar(0);

  InitPushCRC();

  PushBool(boCorrect2Flag);
  Push(&mpbPassCorrect2, sizeof(mpbPassCorrect2));
  PushIntBigArray(mpcwCorrect2Status15, 15);

  PushLongBig(cdwCorrect20);
  PushLongBig(cdwCorrect21);
  PushLongBig(cdwCorrect22);
  PushLongBig(cdwCorrect23);
  PushLongBig(cdwCorrect24);

  Output(100);
}
