/*------------------------------------------------------------------------------
log39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../time/rtc.h"
#include "log39_include.h"
#include "log39.h"



static uint             cwLog39;
static log39            mLog39[LOG39_SIZE];


static counter39        mCounter39[COUNTER39_SIZE];



void    InitLog39(void)
{
  cwLog39 = 0;
  memset(&mLog39, 0, sizeof(mLog39));

  memset(&mCounter39, 0, sizeof(mCounter39));
}


void    Log39(uchar  bError, uint  wData)
{
  log39 log;
  log.tiNow = *GetCurrTimeDate();
  log.bError = bError;
  log.wData = wData;

  mLog39[cwLog39++ % LOG39_SIZE] = log;

  ASSERT(bError < COUNTER39_SIZE);

  mCounter39[bError].tiNow = log.tiNow;
  mCounter39[bError].wCounter++;
}



void    OutLog39(void)
{
  InitPushCRC();

  uint wSize = 0;
  wSize += PushIntLtl(cwLog39);

  uint i;
  for (i=0; i<LOG39_SIZE; i++)
  {
    wSize += PushTime(mLog39[i].tiNow);
    wSize += PushChar(mLog39[i].bError);
    wSize += PushIntLtl(mLog39[i].wData);
  }

  Output(wSize);
}


void    OutCounter39(void)
{
  InitPushCRC();

  uint wSize = 0;

  uint i;
  for (i=0; i<COUNTER39_SIZE; i++)
  {
    wSize += PushTime(mCounter39[i].tiNow);
    wSize += PushIntLtl(mCounter39[i].wCounter);
  }

  Output(wSize);
}


void    OutResetLog39(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    InitLog39();
    Result(bRES_OK);
  }
  else
    Result(bRES_NEEDREPROGRAM);
}
