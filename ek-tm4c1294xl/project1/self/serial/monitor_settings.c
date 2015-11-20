/*------------------------------------------------------------------------------
MONITOR_SETTINGS.C


-----------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "monitor_settings.h"



static bool             fMonitorLogHex;
static bool             fMonitorLogChar7;
static bool             fMonitorLogChar8;


cache const             chMonitorLogHex = {MONITOR_LOG_HEX, &fMonitorLogHex, sizeof(bool)};
cache const             chMonitorLogChar7 = {MONITOR_LOG_CHAR7, &fMonitorLogChar7, sizeof(bool)};
cache const             chMonitorLogChar8 = {MONITOR_LOG_CHAR8, &fMonitorLogChar8, sizeof(bool)};



void    InitMonitorSettings(void)
{
  LoadCacheBool(&chMonitorLogHex, true);
  LoadCacheBool(&chMonitorLogChar7, false);
  LoadCacheBool(&chMonitorLogChar8, false);
}


void    ResetMonitorSettings(void)
{
  SaveCacheBool(&chMonitorLogHex, true);
  SaveCacheBool(&chMonitorLogChar7, false);
  SaveCacheBool(&chMonitorLogChar8, false);
}
