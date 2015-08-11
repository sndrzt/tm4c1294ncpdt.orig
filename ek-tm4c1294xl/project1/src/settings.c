/*------------------------------------------------------------------------------
SETTINGS,C


------------------------------------------------------------------------------*/

#include "main.h"
#include "memory/mem_settings.h"
#include "memory/mem_program.h"
#include "flash/files.h"
#include "nvram/cache.h"
#include "label_global.h"
#include "settings.h"



file const              flPrivate = {PRIVATE, &wPrivate, sizeof(uint)};
cache const             chLogical = {LOGICAL, &bLogical, sizeof(uchar)};

cache const             chFirstReset = {FIRST_RESET, &boFirstReset, sizeof(bool)};
cache const             chEnblWDT = {ENBL_WDT, &boEnblWDT, sizeof(bool)};

cache const             chSetTime = {SET_TIME, &boSetTime, sizeof(bool)};
cache const             chSetDate = {SET_DATE, &boSetDate, sizeof(bool)};
cache const             chSetGroups = {SET_GROUPS, &boSetGroups, sizeof(bool)};
cache const             chSetPassword = {SET_PASSWORD, &boSetPassword, sizeof(bool)};



void    InitSettings(void)
{
  enGlobal = GetLabelGlobal() ? GLB_WORK : GLB_PROGRAM;

  if (LoadFile(&flPrivate) == false)
  {
    wPrivate = 1;
    SaveFile(&flPrivate);
  }

  LoadCache(&chLogical);

  LoadCache(&chFirstReset);
  LoadCache(&chEnblWDT);

  LoadCache(&chSetTime);
  LoadCache(&chSetDate);
  LoadCache(&chSetGroups);
  LoadCache(&chSetPassword);
}


void    ResetSettings(bool  fFull)
{
  if (fFull)
  {
    bLogical = 1;
    SaveCache(&chLogical);
  }

  boFirstReset = false;
  SaveCache(&chFirstReset);

  if (fFull)
  {
    boEnblWDT = true;
    SaveCache(&chEnblWDT);

    boSetTime = false;
    SaveCache(&chSetTime);

    boSetDate = false;
    SaveCache(&chSetDate);

    boSetPassword = true;
    SaveCache(&chSetPassword);
  }
}
